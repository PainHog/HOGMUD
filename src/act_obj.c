/****************************************************************************
 * [S]imulated [M]edieval [A]dventure multi[U]ser [G]ame      |   \\._.//   *
 * -----------------------------------------------------------|   (0...0)   *
 * SMAUG 1.4 (C) 1994, 1995, 1996, 1998  by Derek Snider      |    ).:.(    *
 * -----------------------------------------------------------|    {o o}    *
 * SMAUG code team: Thoric, Altrag, Blodkai, Narn, Haus,      |   / ' ' \   *
 * Scryn, Rennard, Swordbearer, Gorog, Grishnakh, Nivek,      |~'~.VxvxV.~'~*
 * Tricops and Fireblade                                      |             *
 * ------------------------------------------------------------------------ *
 * Merc 2.1 Diku Mud improvments copyright (C) 1992, 1993 by Michael        *
 * Chastain, Michael Quan, and Mitchell Tse.                                *
 * Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,          *
 * Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.     *
 * ------------------------------------------------------------------------ *
 *			   Object manipulation module			    *
 ****************************************************************************/

#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "mud.h"
#include "bet.h"

/*double sqrt( double x );*/

/*
 * External functions
 */

void    show_list_to_char  args( ( OBJ_DATA *list, CHAR_DATA *ch,
				bool fShort, bool fShowNothing ) );
void    write_corpses   args( ( CHAR_DATA *ch, char *name, OBJ_DATA *objrem ) );
void call_lua_char_num  args( (CHAR_DATA * ch, const char * fname, const char * victim, const int argument) );
void call_lua_mob_num   args( (CHAR_DATA * ch, const char * fname, const int victim, const int argument) );

/*
 * Local functions.
 */
void	get_obj		args( ( CHAR_DATA *ch, OBJ_DATA *obj, OBJ_DATA *container ) );
void	wear_obj	args( ( CHAR_DATA *ch, OBJ_DATA *obj, bool fReplace, sh_int wear_bit ) );

char* 	get_chance_verb args( ( OBJ_DATA *obj ) );
char*  	get_ed_number	args( ( OBJ_DATA *obj, int number ) );

void    wield_random_armor   args( (CHAR_DATA *mob ) );
void    wield_random_magic   args( (CHAR_DATA *mob ) );
void    wield_random_relic   args( (CHAR_DATA *mob ) );
void    wield_random_component args( (CHAR_DATA *mob ) );
void	wield_random_artifact  args( (CHAR_DATA *mob ) );
bool	check_container_contents	args( ( OBJ_DATA *obj ) );

OBJ_DATA* recursive_note_find	args( ( OBJ_DATA *obj, char* argument) );

/*
 * how resistant an object is to damage				-Thoric
 */
sh_int get_obj_resistance( OBJ_DATA *obj )
{
    sh_int resist;

    resist = number_fuzzy(MAX_ITEM_IMPACT);

    /* magical items are more resistant */
    if ( IS_OBJ_STAT( obj, ITEM_MAGIC ) || IS_OBJ_STAT( obj, ITEM_ENCHANTED) )
      resist += number_fuzzy(12);
    /* metal objects are definately stronger */
    if ( IS_OBJ_STAT( obj, ITEM_METAL ) )
      resist += number_fuzzy(5);
    /* organic objects are most likely weaker */
    if ( IS_OBJ_STAT( obj, ITEM_ORGANIC ) )
      resist -= number_fuzzy(5);
    /* blessed objects should have a little bonus */
    if ( IS_OBJ_STAT( obj, ITEM_BLESS ) )
      resist += number_fuzzy(5);
    /* lets make store inventory pretty tough */
    if ( IS_OBJ_STAT( obj, ITEM_INVENTORY ) )
      resist += 20;

    /* okay... let's add some bonus/penalty for item level... */
    //~ resist += (obj->level / 10) - 2;

    /* and lasty... take armor or weapon's condition into consideration */
    if (obj->item_type == ITEM_ARMOR || obj->item_type == ITEM_WEAPON ||
        obj->item_type == ITEM_ARTARMOR || obj->item_type == ITEM_ARTWEAPON)
      resist += (obj->value[0] / 2) - 2;

    return URANGE(10, resist, 99);
}


void get_obj( CHAR_DATA *ch, OBJ_DATA *obj, OBJ_DATA *container )
{
    CLAN_DATA *clan;
    int weight;
    int amt; /* gold per-race multipliers */

    if ( !CAN_WEAR(obj, ITEM_TAKE) && IS_NPC(ch) )
    {
	send_to_char( "Mobs can't pick it up either!\n\r", ch );
	return;
    }

    if ( !CAN_WEAR(obj, ITEM_TAKE)
       && (ch->level < sysdata.level_getobjnotake ) )
    {
	send_to_char( "You can't take that.\n\r", ch );
	return;
    }

    /*
    //~ if ( IS_SET( obj->magic_flags, ITEM_PKDISARMED )
    //~ &&  !IS_NPC( ch ) && !IS_IMMORTAL(ch) )
    //~ {
	//~ if ( CAN_PKILL( ch ) && !get_timer( ch, TIMER_PKILLED ) )
	//~ {
	    //~ if ( ch->level - obj->value[5] > 5
	    //~ ||   obj->value[5] - ch->level > 5 )
	    //~ {
		//~ send_to_char_color( "\n\r&bA godly force freezes your outstretched hand.\n\r", ch );
		//~ return;
	    //~ }
	    //~ else
	    //~ {
		//~ REMOVE_BIT( obj->magic_flags, ITEM_PKDISARMED );
		//~ obj->value[5] = 0;
	    //~ }
	//~ }
	//~ else
	//~ {
	    //~ send_to_char_color( "\n\r&BA godly force freezes your outstretched hand.\n\r", ch );
 	    //~ return;
	//~ }
    //~ }
    */
	
    if ( IS_OBJ_STAT( obj, ITEM_PROTOTYPE )
    &&  !can_take_proto( ch ) )
    {
	send_to_char( "A godly force prevents you from getting close to it.\n\r", ch );
	return;
    }

    if ( !IS_IMMORTAL(ch) && (obj->owner)&& str_cmp( ch->name, obj->owner ) )
    {
        act( AT_PLAIN, "This is tied to another owner.", ch, obj, 0, TO_CHAR ); 
        return; 
    } 

    if ( ch->carry_number + get_obj_number( obj ) > can_carry_n( ch ) )
    {
	act( AT_PLAIN, "$d: you can't carry that many items.",
		ch, NULL, obj->name, TO_CHAR );
	return;
    }

    if ( IS_OBJ_STAT(obj, ITEM_COVERING) )
	weight = obj->weight;
    else
	weight = get_obj_weight( obj );

    if ( ch->carry_weight + weight > can_carry_w( ch ) )
    {
	act( AT_PLAIN, "$d: you can't carry that much weight.",
	    ch, NULL, obj->name, TO_CHAR );
	return;
    }

    if ( container )
    {
	if ( container->item_type == ITEM_KEYRING && !IS_OBJ_STAT(container, ITEM_COVERING) )
	{
	    act( AT_ACTION, "You remove $p from $P", ch, obj, container, TO_CHAR );
	    act( AT_ACTION, "$n removes $p from $P", ch, obj, container, TO_ROOM );
	}
	else
	{
	    act( AT_ACTION, IS_OBJ_STAT(container, ITEM_COVERING) ? 
		"You get $p from beneath $P." : "You get $p from $P",
		ch, obj, container, TO_CHAR );
	    act( AT_ACTION, IS_OBJ_STAT(container, ITEM_COVERING) ?
		"$n gets $p from beneath $P." : "$n gets $p from $P",
		ch, obj, container, TO_ROOM );
	}
	if ( IS_OBJ_STAT( container, ITEM_CLANCORPSE )
	&&  !IS_NPC( ch ) && str_cmp( container->name+7, ch->name ) )
                container->value[5]++;
	obj_from_obj( obj );
    }
    else
    {
	act( AT_ACTION, "You get $p.", ch, obj, container, TO_CHAR );
	act( AT_ACTION, "$n gets $p.", ch, obj, container, TO_ROOM );
	obj_from_room( obj );
    }

    /* Clan storeroom checks */
    if ( IS_SET(ch->in_room->room_flags, ROOM_CLANSTOREROOM) 
    && (!container || container->carried_by == NULL) )
    {
/*	if (!char_died) save_char_obj(ch); */
	for ( clan = first_clan; clan; clan = clan->next )
	  if ( clan->storeroom == ch->in_room->vnum )
	    save_clan_storeroom(ch, clan);
    }

    if ( obj->item_type != ITEM_CONTAINER )
	check_for_trap( ch, obj, TRAP_GET );
    if ( char_died(ch) )
	return;

    if ( obj->item_type == ITEM_MONEY )
    {

        amt = obj->value[0];

	ch->gold += taxed(amt);
	tax(ch, amt);
	extract_obj( obj );
    }
    else
    {
	obj = obj_to_char( obj, ch );
    }

    if ( char_died(ch) || obj_extracted(obj) )
      return;
    oprog_get_trigger(ch, obj);
    return;
}

void do_cleanup( CHAR_DATA *ch, char *argument )
{ 
    OBJ_DATA *obj;
     
    set_char_color( AT_IMMORT, ch );
          
    OBJ_DATA  *obj_next;
         
    for ( obj = ch->in_room->first_content; obj; obj = obj_next )
    {
        obj_next = obj->next_content;
        if ( (obj->owner)&& str_cmp( ch->name, obj->owner ) )
            continue;
        //~ {
            //~ act( AT_IMMORT, "$n attempts to clean things up, but runs into an Owned object.", ch, NULL, NULL, TO_ROOM); 
            //~ act( AT_IMMORT, "You attempt to clean things up, but run into an Owned object.", ch, NULL, NULL, TO_CHAR );    
            //~ return;
        //~ }
        if ( !IS_IMMORTAL(ch) && IS_OBJ_STAT(obj, ITEM_CLANOBJECT ) )
            continue;
        //~ { 
            //~ act( AT_PLAIN, "This is a clan object...don't sacrifice it!", ch, obj, 0, TO_CHAR );
            //~ return; 
        //~ } 
        if ( obj->item_type == ITEM_CORPSE_PC )
            continue;
        //~ {   
            //~ act( AT_PLAIN, "You can't clean up the corpse of another player!.", ch, NULL, NULL, TO_CHAR );
            //~ act( AT_PLAIN, "$n's attempt to clean things up is stopped by a player corpse.",ch, NULL, NULL, TO_ROOM);
            //~ return;
        //~ } 
        else if ( IS_SET(obj->wear_flags, ITEM_TAKE) )
            extract_obj( obj );
    }
         
    act( AT_IMMORT, "$n cleans all the stuff from the room!", ch, NULL, NULL, TO_ROOM);
    act( AT_IMMORT, "You clean all the stuff from the room!", ch, NULL, NULL, TO_CHAR );
    return;
} 


/* Connect pieces of an ITEM -- Originally from ACK!  *
 * Modified for Smaug by Zarius 5/19/2000             */
void do_connect( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA *first_ob, *second_ob, *new_ob;
  //~ char arg1[MAX_STRING_LENGTH], arg2[MAX_STRING_LENGTH];
    char *arg1, *arg2;
//  char buf[MAX_STRING_LENGTH];

  //~ argument = one_argument( argument, arg1 );
  //~ argument = one_argument( argument, arg2 );
    call_va(L_mud, "one_arg", "s>ss", argument, &arg1, &argument);
    call_va(L_mud, "one_arg", "s>ss", argument, &arg2, &argument);

  if ( arg1[0] == '\0' || arg2[0] == '\0' )
  {
    send_to_char( "Syntax: Connect <firstobj> <secondobj>.\n\r", ch );
    return;
  }

  if ( ( first_ob = get_obj_carry( ch, arg1 ) ) == NULL )
  {
    send_to_char( "You must be holding both parts!!\n\r", ch );
    return;
  }

  if ( ( second_ob = get_obj_carry( ch, arg2 ) ) == NULL )
  {
    send_to_char( "You must be holding both parts!!\n\r", ch );
    return;
  }

  if ( first_ob->item_type != ITEM_PIECE || second_ob->item_type !=ITEM_PIECE )
  {
    send_to_char( "Both items must be pieces of another item!\n\r", ch );
    return;
  }

  /* check to see if the pieces connect */

  if ( ( first_ob->value[0] == second_ob->pIndexData->vnum )
  && ( second_ob->value[0] == first_ob->pIndexData->vnum )
  && ( first_ob->value[1] == second_ob->value[1]  )
  && ( first_ob->pIndexData->vnum != second_ob->pIndexData->vnum ) )
  /* good connection  */
  {
    new_ob = create_object( get_obj_index( first_ob->value[1] ), ch->level );
    extract_obj( first_ob );
    extract_obj( second_ob );
    obj_to_char( new_ob, ch );
    act( AT_ACTION, "$n jiggles some pieces together...\r\n ...suddenly they snap in place, creating $p!", ch, new_ob, NULL, TO_ROOM );
    act( AT_ACTION, "You jiggle the pieces together...\r\n ...suddenly they snap into place, creating $p!", ch, new_ob, NULL, TO_CHAR );
  }
  else
  {
    act( AT_ACTION, "$n jiggles some pieces together, but can't seem to make them connect.", ch, NULL, NULL, TO_ROOM );
    act( AT_ACTION, "You try to fit them together every which way, but they just don't want to fit together.", ch, NULL, NULL, TO_CHAR );
    return;
  }
  return;
}

void do_get( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;
    OBJ_DATA *container;
    sh_int number;
    bool found;

    argument = one_argument( argument, arg1 );
    if ( is_number(arg1) )
    {
	number = atoi(arg1);
	if ( number < 1 )
	{
	    send_to_char( "That was easy...\n\r", ch );
	    return;
	}
	if ( (ch->carry_number + number) > can_carry_n(ch) )
	{
	    send_to_char( "You can't carry that many.\n\r", ch );
	    return;
	}
	argument = one_argument( argument, arg1 );
    }
    else
	number = 0;
    argument = one_argument( argument, arg2 );
    /* munch optional words */
    if ( !str_cmp( arg2, "from" ) && argument[0] != '\0' )
	argument = one_argument( argument, arg2 );

    /* Get type. */
    if ( arg1[0] == '\0' )
    {
	send_to_char( "Get what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( arg2[0] == '\0' )
    {
	if ( number <= 1 && str_cmp( arg1, "all" ) && str_prefix( "all.", arg1 ) )
	{
	    /* 'get obj' */
	    obj = get_obj_list( ch, arg1, ch->in_room->first_content );
	    if ( !obj )
	    {
		act( AT_PLAIN, "I see no $T here.", ch, NULL, arg1, TO_CHAR );
		return;
	    }
            if ( !IS_IMMORTAL(ch) && (obj->owner)&& str_cmp( ch->name, obj->owner ) )
            {
                act( AT_PLAIN, "This is tied to another owner.", ch, obj, 0, TO_CHAR );
                return;
            } 
	    separate_obj(obj);
	    get_obj( ch, obj, NULL );
	    if ( char_died(ch) )
		return;
	    if ( IS_SET( sysdata.save_flags, SV_GET ) )
		save_char_obj( ch );
	}
	else
	{
	    sh_int cnt = 0;
	    bool fAll;
	    char *chk;

	    if ( IS_SET( ch->in_room->room_flags, ROOM_DONATION ) )
	    {
		send_to_char( "The gods frown upon such a display of greed!\n\r", ch );
		return;
	    }
	    if ( !str_cmp(arg1, "all") )
		fAll = TRUE;
	    else
		fAll = FALSE;
	    if ( number > 1 )
		chk = arg1;
	    else
		chk = &arg1[4];

	    /* 'get all' or 'get all.obj' */
	    found = FALSE;
	    for ( obj = ch->in_room->last_content; obj; obj = obj_next )
	    {
			obj_next = obj->prev_content;
			if(!IS_NPC(ch) || (IS_NPC(ch) && !fAll))
			{
				if ( ( fAll || nifty_is_name( chk, obj->name ) )
				&&   can_see_obj( ch, obj ) )
				{
					found = TRUE;
					if ( number && (cnt + obj->count) > number )
					split_obj( obj, number - cnt );
					cnt += obj->count;
					get_obj( ch, obj, NULL );
					if ( char_died(ch)
					||   ch->carry_number >= can_carry_n( ch )
					||   ch->carry_weight >= can_carry_w( ch )
					||   (number && cnt >= number) )
					{
					if ( IS_SET(sysdata.save_flags, SV_GET)
					&&  !char_died(ch) )
						save_char_obj(ch);
					return;
					}
				}
			}
			else // special case for pit room mobs 'get all' 'put all pit' programs -Darwin
			{
				if( IS_OBJ_STAT( obj, ITEM_RANDOM ) && can_see_obj( ch, obj ) )
				{
					bool goahead = TRUE;
					if(obj->pIndexData->item_type == ITEM_CONTAINER)
					{
						OBJ_DATA *cont;

						for(cont = obj->first_content; cont; cont = cont->next_content)
						{
							if( !IS_OBJ_STAT( cont, ITEM_RANDOM ) )
							{
								goahead = FALSE;
								break;
							}
						}

					}
					if(goahead)
					{
						found = TRUE;
						if ( number && (cnt + obj->count) > number )
						split_obj( obj, number - cnt );
						cnt += obj->count;
						get_obj( ch, obj, NULL );
					}
				}
			}
	    }

	    if ( !found )
	    {
		if ( fAll )
		  send_to_char( "I see nothing here.\n\r", ch );
		else
		  act( AT_PLAIN, "I see no $T here.", ch, NULL, chk, TO_CHAR );
	    }
	    else
	    if ( IS_SET( sysdata.save_flags, SV_GET ) )
		save_char_obj( ch );
	}
    }
    else
    {
	/* 'get ... container' */
	if ( !str_cmp( arg2, "all" ) || !str_prefix( "all.", arg2 ) )
	{
	    send_to_char( "You can't do that.\n\r", ch );
	    return;
	}

	if ( ( container = get_obj_here( ch, arg2 ) ) == NULL )
	{
	    act( AT_PLAIN, "I see no $T here.", ch, NULL, arg2, TO_CHAR );
	    return;
	}

	switch ( container->item_type )
	{
	default:
	    if ( !IS_OBJ_STAT( container, ITEM_COVERING ) )
	    {
		send_to_char( "That's not a container.\n\r", ch );
		return;
	    }
	    if ( ch->carry_weight + container->weight > can_carry_w( ch ) )
	    {
		send_to_char( "It's too heavy for you to lift.\n\r", ch );
		return;
	    }
	    break;

	case ITEM_CONTAINER:
		if(container->pIndexData->vnum == OBJ_VNUM_VR_LOCKER && !IS_NPC(ch))
		{
			if(ch->fighting)
			{
				send_to_char("&WYou can't do that while fighting!\n\r", ch);
				return;
			}
			TIMER *timer;
			timer = get_timerptr( ch, TIMER_RECENTFIGHT );
			if(timer)
			{
				send_to_char("&WYou can't do that... &Yyet&W.\n\r", ch);
				return;
			}		
		}
	case ITEM_CORPSE_NPC:
	case ITEM_KEYRING:
        case ITEM_CORPSE_PC:
	case ITEM_QUIVER:
          break;

	}

	if ( !IS_OBJ_STAT(container, ITEM_COVERING )
	&&    IS_SET(container->value[1], CONT_CLOSED) )
	{
	    act( AT_PLAIN, "The $d is closed.", ch, NULL, container->name, TO_CHAR );
	    return;
	}

	if ( number <= 1 && str_cmp( arg1, "all" ) && str_prefix( "all.", arg1 ) )
	{
	    /* 'get obj container' */
	    obj = get_obj_list( ch, arg1, container->first_content );
	    if ( !obj )
	    {
			if(container->pIndexData->vnum == OBJ_VNUM_VR_LOCKER)
				send_to_char("&WNothing like that is in your locker.\n\r", ch);
			else
				act( AT_PLAIN, IS_OBJ_STAT(container, ITEM_COVERING) ?
					"I see nothing like that beneath the $T." :
					"I see nothing like that in the $T.",
					ch, NULL, arg2, TO_CHAR );
		return;
	    }
	    separate_obj(obj);
	    get_obj( ch, obj, container );
	    /* Oops no wonder corpses were duping oopsie did I do that
	     * --Shaddai
             */
	    if ( container->item_type == ITEM_CORPSE_PC )
		write_corpses( NULL, container->short_descr+14, NULL );
	    check_for_trap( ch, container, TRAP_GET );
	    if ( char_died(ch) )
		return;
	    if ( IS_SET( sysdata.save_flags, SV_GET ) )
		save_char_obj( ch );
	}
	else
	{
	    int cnt = 0;
	    bool fAll;
	    char *chk;

	    /* 'get all container' or 'get all.obj container' */
	    if ( IS_OBJ_STAT( container, ITEM_DONATION ) )
	    {
		send_to_char( "The gods frown upon such an act of greed!\n\r", ch );
		return;
	    }
/*
            if ( IS_OBJ_STAT( container, ITEM_CLANCORPSE )
            &&  !IS_IMMORTAL(ch)
            &&  !IS_NPC(ch)
            &&  str_cmp( ch->name, container->name+7 ) )
            {
                send_to_char( "The gods frown upon such wanton greed!\n\r", ch );
                return;
            }
*/
	    if ( !str_cmp(arg1, "all") )
		fAll = TRUE;
	    else
		fAll = FALSE;
	    if ( number > 1 )
		chk = arg1;
	    else
		chk = &arg1[4];
	    found = FALSE;
	    for ( obj = container->first_content; obj; obj = obj_next )
	    {
		obj_next = obj->next_content;
		if ( ( fAll || nifty_is_name( chk, obj->name ) )
		&&   can_see_obj( ch, obj ) )
		{
		    found = TRUE;
		    if ( number && (cnt + obj->count) > number )
			split_obj( obj, number - cnt );
		    cnt += obj->count;
		    get_obj( ch, obj, container );
		    if ( char_died(ch)
		    ||   ch->carry_number >= can_carry_n( ch )
		    ||   ch->carry_weight >= can_carry_w( ch )
		    ||   (number && cnt >= number) )
		      return;
		}
	    }

	    if ( !found )
	    {
		if ( fAll )
		{
		    if ( container->item_type == ITEM_KEYRING && !IS_OBJ_STAT(container, ITEM_COVERING) )
			act( AT_PLAIN, "The $T holds no keys.",
			    ch, NULL, arg2, TO_CHAR );
		    else
			if(container->pIndexData->vnum == OBJ_VNUM_VR_LOCKER)
				send_to_char("&WNothing like that is in your locker.\n\r", ch);
			else
			act( AT_PLAIN, IS_OBJ_STAT(container, ITEM_COVERING) ?
			    "I see nothing beneath the $T." :
			    "I see nothing in the $T.",
			    ch, NULL, arg2, TO_CHAR );
		}
		else
		{
		    if ( container->item_type == ITEM_KEYRING && !IS_OBJ_STAT(container, ITEM_COVERING) )
			act( AT_PLAIN, "The $T does not hold that key.",
			    ch, NULL, arg2, TO_CHAR );
		    else
			if(container->pIndexData->vnum == OBJ_VNUM_VR_LOCKER)
				send_to_char("&WNothing like that is in your locker.\n\r", ch);
			else
			act( AT_PLAIN, IS_OBJ_STAT(container, ITEM_COVERING) ?
			    "I see nothing like that beneath the $T." :
			    "I see nothing like that in the $T.",
			    ch, NULL, arg2, TO_CHAR );
		}
	    }
	    else
		check_for_trap( ch, container, TRAP_GET );
	    if ( char_died(ch) )
		return;
	    /* Oops no wonder corpses were duping oopsie did I do that
	     * --Shaddai
             */
	    if ( container->item_type == ITEM_CORPSE_PC )
		write_corpses( NULL, container->short_descr+14, NULL );
	    if ( found && IS_SET( sysdata.save_flags, SV_GET ) )
		save_char_obj( ch );
	}
    }
    return;
}

/* Function to check a conainer and sub-containers for non-random
 * items. Returns FALSE if non-random is found -Darwin 
 */
bool check_container_contents( OBJ_DATA *obj )
{
	if(obj->pIndexData->item_type == ITEM_CONTAINER)
		if(obj->first_content)
		{
			OBJ_DATA *cont;
			for(cont = obj->first_content; cont; cont = cont->next_content)
			{
				if(!IS_OBJ_STAT(cont, ITEM_RANDOM))
					return FALSE;

				if(cont->pIndexData->item_type == ITEM_CONTAINER)
					return check_container_contents(cont);
			}
		}
	return TRUE;
}

void do_put( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    OBJ_DATA *container;
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;
    CLAN_DATA *clan;
    sh_int	count;
    int		number;
    bool	save_char = FALSE;

    argument = one_argument( argument, arg1 );
    if ( is_number(arg1) )
    {
	number = atoi(arg1);
	if ( number < 1 )
	{
	    send_to_char( "That was easy...\n\r", ch );
	    return;
	}
	argument = one_argument( argument, arg1 );
    }
    else
	number = 0;
    argument = one_argument( argument, arg2 );
    /* munch optional words */
    if ( (!str_cmp(arg2, "into") || !str_cmp(arg2, "inside")
    ||    !str_cmp(arg2, "in") || !str_cmp(arg2, "under")
    ||    !str_cmp(arg2, "onto") || !str_cmp(arg2, "on"))
    &&     argument[0] != '\0' )
	argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Put what in what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( !str_cmp(arg2, "all") || !str_prefix("all.", arg2) )
    {
	send_to_char( "You can't do that.\n\r", ch );
	return;
    }

    if ( (container=get_obj_here(ch, arg2)) == NULL )
    {
	act( AT_PLAIN, "I see no $T here.", ch, NULL, arg2, TO_CHAR );
	return;
    }

    if ( !container->carried_by && IS_SET(sysdata.save_flags, SV_PUT) )
	save_char = TRUE;

    if ( IS_OBJ_STAT(container, ITEM_COVERING) )
    {
	if ( ch->carry_weight + container->weight > can_carry_w(ch) )
	{
	    send_to_char( "It's too heavy for you to lift.\n\r", ch );
	    return;
	}
    }
    else
    {
	if ( container->item_type != ITEM_CONTAINER
	&&   container->item_type != ITEM_KEYRING
	&&   container->item_type != ITEM_QUIVER )
	{
	    send_to_char( "That's not a container.\n\r", ch );
	    return;
	}

	if ( IS_SET(container->value[CONTAINER_FLAGS], CONT_CLOSED) )
	{
	    act( AT_PLAIN, "The $d is closed.", ch, NULL, container->name, TO_CHAR );
	    return;
	}
    }

    if ( number <= 1 && str_cmp(arg1, "all") && str_prefix("all.", arg1) )
    {
	/* 'put obj container' */
	if ( (obj=get_obj_carry(ch, arg1)) == NULL )
	{
	    send_to_char( "You do not have that item.\n\r", ch );
	    return;
	}

	if ( obj == container )
	{
	    send_to_char( "You can't fold it into itself.\n\r", ch );
	    return;
	}

	if ( !can_drop_obj(ch, obj) )
	{
	    send_to_char( "You can't let go of it.\n\r", ch );
	    return;
	}

        //~ if (obj->pIndexData->rent >= MIN_RENT )
           //~ {
               //~ send_to_char( "That item is limited, and cannot go in a container.\n\r", ch);
               //~ return;
           //~ }

	if ( container->pIndexData->vnum == 8 && !IS_OBJ_STAT(obj, ITEM_QUEST) )
	{
	    send_to_char( "Only Quest items can go in a Quest Bag!\n\r", ch );
	    return;
	}

	if ( obj->item_type == ITEM_CORPSE_PC )
	{
	    send_to_char( "Corpses cannot be placed into containers.\n\r", ch );
	    return;
	}

	if ( obj->item_type == ITEM_CORPSE_NPC )
	{
		send_to_char( "Corpses cannot be placed into containers.\n\r", ch );
		return; 
	} 

	if ( container->item_type == ITEM_KEYRING && obj->item_type != ITEM_KEY )
	{
	    send_to_char( "That's not a key.\n\r", ch );
	    return;
	}

	if ( container->item_type == ITEM_QUIVER && obj->item_type != ITEM_PROJECTILE )
	{
	    send_to_char( "That's not a projectile.\n\r", ch );
	    return;
	}

	if ( (IS_OBJ_STAT(container, ITEM_COVERING)
	&&   (get_obj_weight(obj) / obj->count)
	  > ((get_obj_weight(container) / container->count)
	  -   container->weight)) )
	{
	    send_to_char( "It won't fit under there.\n\r", ch );
	    return;
	}

	/* the following if is for preventing the stock-piling of stock items -Darwin */
	if (IS_OBJ_STAT(container, ITEM_DONATION))
	{
		if( !IS_OBJ_STAT( obj, ITEM_RANDOM ) )
		{
			send_to_char( "You can only put randoms into the donation pit.\n\r", ch );
			return;
		}

		if (obj->pIndexData->item_type == ITEM_CONTAINER)
		{
			if(!check_container_contents(obj))
			{
				send_to_char("There are item inside this container that cannot be placed in a donation pit.\n\r", ch);
				return;
			}
		}
	}

	if(container->pIndexData->vnum == OBJ_VNUM_VR_LOCKER && !IS_NPC(ch))
	{
		if(ch->fighting)
		{
			send_to_char("&WYou can't do that while fighting!\n\r", ch);
			return;
		}
		TIMER *timer;
		timer = get_timerptr( ch, TIMER_RECENTFIGHT );
		if(timer)
		{
			send_to_char("&WYou can't do that... &Yyet&W.\n\r", ch);
			return;
		}		
	}

	/* note use of get_real_obj_weight */
	if ( (get_real_obj_weight(obj) / obj->count)
	   + (get_real_obj_weight(container) /*/ container->count*/)
	   >=  container->value[CONTAINER_CAPACITY] )
	{
	    send_to_char( "It won't fit.\n\r", ch );
	    return;
	}

	if( obj == container )
	{
		ch_printf(ch, "You can't put %s inside itself.\n\r", obj->short_descr);
		return;
	}
	separate_obj(obj);
	separate_obj(container);
	obj_from_char( obj );
	obj = obj_to_obj( obj, container );
	check_for_trap ( ch, container, TRAP_PUT );
	if ( char_died(ch) )
	    return;
	count = obj->count;
	obj->count = 1;
	if ( container->item_type == ITEM_KEYRING && !IS_OBJ_STAT(container, ITEM_COVERING) )
	{
	    act( AT_ACTION, "$n slips $p onto $P.", ch, obj, container, TO_ROOM );
	    act( AT_ACTION, "You slip $p onto $P.", ch, obj, container, TO_CHAR );
	}
	else
	{
	    act( AT_ACTION, IS_OBJ_STAT(container, ITEM_COVERING)
		? "$n hides $p beneath $P." : "$n puts $p in $P.",
		ch, obj, container, TO_ROOM );
	    act( AT_ACTION, IS_OBJ_STAT(container, ITEM_COVERING)
		? "You hide $p beneath $P." : "You put $p in $P.",
		ch, obj, container, TO_CHAR );
	}
	obj->count = count;

       /* Oops no wonder corpses were duping oopsie did I do that
        * --Shaddai
        */
        if ( container->item_type == ITEM_CORPSE_PC )
		write_corpses( NULL, container->short_descr+14, NULL );

	if ( save_char )
	  save_char_obj(ch);
	/* Clan storeroom check */
	if ( IS_SET(ch->in_room->room_flags, ROOM_CLANSTOREROOM) 
	&&   container->carried_by == NULL)
	{
/*	   if (!char_died && !save_char ) save_char_obj(ch); */
	   for ( clan = first_clan; clan; clan = clan->next )
	      if ( clan->storeroom == ch->in_room->vnum )
		save_clan_storeroom(ch, clan);
	}
    }
    else
    {
	bool found = FALSE;
	int cnt = 0;
	bool fAll;
	char *chk;

	if ( !str_cmp(arg1, "all") )
	    fAll = TRUE;
	else
	    fAll = FALSE;
	if ( number > 1 )
	    chk = arg1;
	else
	    chk = &arg1[4];


	separate_obj(container);
	/* 'put all container' or 'put all.obj container' */
	for ( obj = ch->first_carrying; obj; obj = obj_next )
	{
	    obj_next = obj->next_content;

		if(IS_OBJ_STAT(container, ITEM_DONATION) && !IS_NPC(ch))
		{
			send_to_char("You cannot donate everything at once.\n\r", ch);
			return;
		}

		if( obj == container )
			continue;

		if(!IS_NPC(ch) || (IS_NPC(ch) && !IS_OBJ_STAT(container, ITEM_DONATION)))
		{
			if ( ( fAll || nifty_is_name( chk, obj->name ) )
			&&   can_see_obj( ch, obj )
			&&   obj->wear_loc == WEAR_NONE
			&&   obj != container
			//~ &&   obj->pIndexData->rent < MIN_RENT
			&&  ( container->pIndexData->vnum != 8 && !IS_OBJ_STAT(obj, ITEM_QUEST) )
			&&  ( obj->item_type != ITEM_CORPSE_PC || obj->item_type != ITEM_CORPSE_NPC )
			&&  can_drop_obj( ch, obj )
			&&  (container->item_type != ITEM_KEYRING || obj->item_type == ITEM_KEY)
			&&  (container->item_type != ITEM_QUIVER  || obj->item_type == ITEM_PROJECTILE)
			&&  get_real_obj_weight( obj ) + get_real_obj_weight( container ) <= container->value[0])
			{
			if ( number && (cnt + obj->count) > number )
				split_obj(obj, number - cnt);
			cnt += obj->count;
			obj_from_char(obj);
			act( AT_ACTION, "$n puts $p in $P.", ch, obj, container, TO_ROOM );
			act( AT_ACTION, "You put $p in $P.", ch, obj, container, TO_CHAR );
			obj = obj_to_obj( obj, container );
			found = TRUE;

			check_for_trap( ch, container, TRAP_PUT );
			if ( char_died(ch) )
				return;
			if ( number && cnt >= number )
				break;
			}
		}
		else // special case for pit room mobs -Darwin
		{
			if(IS_OBJ_STAT( obj, ITEM_RANDOM ))
			{
				if(obj->pIndexData->item_type != ITEM_CONTAINER)
				{
					obj_from_char(obj);
					if ( container->item_type == ITEM_KEYRING )
					{
						act( AT_ACTION, "$n slips $p onto $P.", ch, obj, container, TO_ROOM );
						act( AT_ACTION, "You slip $p onto $P.", ch, obj, container, TO_CHAR );
					}
					else
					{
						act( AT_ACTION, "$n puts $p in $P.", ch, obj, container, TO_ROOM );
						act( AT_ACTION, "You put $p in $P.", ch, obj, container, TO_CHAR );
					}
					obj = obj_to_obj( obj, container );
					found = TRUE;
				}
				else // found container - search for stock items
				{
					bool goahead = TRUE;
					if(obj->first_content)
					{
						OBJ_DATA *cont;
						for(cont = obj->first_content; cont; cont = cont->next_content)
						{
							if(!IS_OBJ_STAT(cont, ITEM_RANDOM))
							{
								do_drop(ch, obj->name);
								goahead = FALSE;
								break;
							}
						}
					}
					// get this far item and contents are ok
					if(goahead)
					{
						obj_from_char(obj);
						if ( container->item_type == ITEM_KEYRING )
						{
							act( AT_ACTION, "$n slips $p onto $P.", ch, obj, container, TO_ROOM );
							act( AT_ACTION, "You slip $p onto $P.", ch, obj, container, TO_CHAR );
						}
						else
						{
							act( AT_ACTION, "$n puts $p in $P.", ch, obj, container, TO_ROOM );
							act( AT_ACTION, "You put $p in $P.", ch, obj, container, TO_CHAR );
						}
						obj = obj_to_obj( obj, container );
						found = TRUE;
					}
				}
			}
			else
			{
				do_drop(ch, obj->name);
			}
		}

	}

	/*
	 * Don't bother to save anything if nothing was dropped   -Thoric
	 */
	if ( !found )
	{
	    if ( fAll )
	      act( AT_PLAIN, "You are not carrying anything or your container is full.",
		    ch, NULL, NULL, TO_CHAR );
	    else
	      act( AT_PLAIN, "You are not carrying any $T, or your container is full.",
		    ch, NULL, chk, TO_CHAR );
	    return;
	}

	if ( save_char )
	    save_char_obj(ch);
       /* Oops no wonder corpses were duping oopsie did I do that
        * --Shaddai
        */
        if ( container->item_type == ITEM_CORPSE_PC )
		write_corpses( NULL, container->short_descr+14, NULL );

	/* Clan storeroom check */
        if ( IS_SET(ch->in_room->room_flags, ROOM_CLANSTOREROOM) 
	&& container->carried_by == NULL )
	{
/*	  if (!char_died && !save_char) save_char_obj(ch); */
	  for ( clan = first_clan; clan; clan = clan->next )
	     if ( clan->storeroom == ch->in_room->vnum )
        	save_clan_storeroom(ch, clan);
	}
    }

    return;
}


void do_drop( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;
    bool found;
    CLAN_DATA *clan;
    int number;

    argument = one_argument( argument, arg );
    if ( is_number(arg) )
    {
	number = atoi(arg);
	if ( number < 1 )
	{
	    send_to_char( "That was easy...\n\r", ch );
	    return;
	}
	argument = one_argument( argument, arg );
    }
    else
	number = 0;

    if ( arg[0] == '\0' )
    {
	send_to_char( "Drop what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( IS_SET( ch->in_room->room_flags, ROOM_NODROP )
    &&   ch != supermob )
    {
       set_char_color( AT_MAGIC, ch );
       send_to_char( "A magical force stops you!\n\r", ch );
       set_char_color( AT_TELL, ch );
       send_to_char( "Someone tells you, 'No littering here!'\n\r", ch );
       return;
    }

    if ( number > 0 )
    {
	/* 'drop NNNN coins' */

	if ( !str_cmp( arg, "coins" ) || !str_cmp( arg, "coin" ) )
	{
	    if ( ch->gold < number )
	    {
		send_to_char( "You haven't got that many coins.\n\r", ch );
		return;
	    }

	    ch->gold -= number;

	    for ( obj = ch->in_room->first_content; obj; obj = obj_next )
	    {
		obj_next = obj->next_content;

		switch ( obj->pIndexData->vnum )
		{
		case OBJ_VNUM_MONEY_ONE:
		   number += 1;
		   extract_obj( obj );
		   break;

		case OBJ_VNUM_MONEY_SOME:
		   number += obj->value[MONEY_AMOUNT];
		   extract_obj( obj );
		   break;
		}
	    }

	    act( AT_ACTION, "$n drops some gold.", ch, NULL, NULL, TO_ROOM );
	    obj_to_room( create_money( number ), ch->in_room );
	    send_to_char( "You let the gold slip from your hand.\n\r", ch );
	    if ( IS_SET( sysdata.save_flags, SV_DROP ) )
		save_char_obj( ch );
	    return;
	}
    }

    if ( number <= 1 && str_cmp( arg, "all" ) && str_prefix( "all.", arg ) )
    {
	/* 'drop obj' */
	if ( ( obj = get_obj_carry( ch, arg ) ) == NULL )
	{
	    send_to_char( "You do not have that item.\n\r", ch );
	    return;
	}

	if ( !can_drop_obj( ch, obj ) )
	{
	    send_to_char( "You can't let go of it.\n\r", ch );
	    return;
	}

	separate_obj( obj );
	act( AT_ACTION, "$n drops $p.", ch, obj, NULL, TO_ROOM );
	act( AT_ACTION, "You drop $p.", ch, obj, NULL, TO_CHAR );

	obj_from_char( obj );
	obj = obj_to_room( obj, ch->in_room );
	oprog_drop_trigger ( ch, obj );   /* mudprogs */

        if( char_died(ch) || obj_extracted(obj) )
          return;

	/* Clan storeroom saving */
	if ( IS_SET(ch->in_room->room_flags, ROOM_CLANSTOREROOM) )
	{
/*	   if (!char_died) save_char_obj(ch); */
	   for ( clan = first_clan; clan; clan = clan->next )
 	      if ( clan->storeroom == ch->in_room->vnum )
		save_clan_storeroom(ch, clan);
	}
    }
    else
    {
	int cnt = 0;
	char *chk;
	bool fAll;

	if ( !str_cmp(arg, "all") )
	    fAll = TRUE;
	else
	    fAll = FALSE;
	if ( number > 1 )
	    chk = arg;
	else
	    chk = &arg[4];
	/* 'drop all' or 'drop all.obj' */
	if ( IS_SET( ch->in_room->room_flags, ROOM_NODROPALL ) 
        ||   IS_SET( ch->in_room->room_flags, ROOM_CLANSTOREROOM ) )
	{
	    send_to_char( "You can't seem to do that here...\n\r", ch );
	    return;
	}
	found = FALSE;
	for ( obj = ch->first_carrying; obj; obj = obj_next )
	{
	    obj_next = obj->next_content;

	    if ( (fAll || nifty_is_name( chk, obj->name ) )
	    &&   can_see_obj( ch, obj )
	    &&   obj->wear_loc == WEAR_NONE
	    &&   can_drop_obj( ch, obj ) )
	    {
		found = TRUE;
		if ( HAS_PROG(obj->pIndexData, DROP_PROG) && obj->count > 1 ) 
		{
		   ++cnt;
		   separate_obj( obj );
		   obj_from_char( obj );
		   if ( !obj_next )
		     obj_next = ch->first_carrying;
		}
		else
		{
		   if ( number && (cnt + obj->count) > number )
		     split_obj( obj, number - cnt );
		   cnt += obj->count;
		   obj_from_char( obj );
		}
		act( AT_ACTION, "$n drops $p.", ch, obj, NULL, TO_ROOM );
		act( AT_ACTION, "You drop $p.", ch, obj, NULL, TO_CHAR );
		obj = obj_to_room( obj, ch->in_room );
		oprog_drop_trigger( ch, obj );		/* mudprogs */
                if ( char_died(ch) )
                    return;
		if ( number && cnt >= number )
		    break;
	    }
	}

	if ( !found )
	{
	    if ( fAll )
	      act( AT_PLAIN, "You are not carrying anything.",
		    ch, NULL, NULL, TO_CHAR );
	    else
	      act( AT_PLAIN, "You are not carrying any $T.",
		    ch, NULL, chk, TO_CHAR );
	}
    }
    if ( IS_SET( sysdata.save_flags, SV_DROP ) )
	save_char_obj( ch );	/* duping protector */
    return;
}



void do_give( CHAR_DATA *ch, char *argument )
{
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];
    char buf  [MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA  *obj;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    if ( !str_cmp( arg2, "to" ) && argument[0] != '\0' )
	argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Give what to whom?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( is_number( arg1 ) )
    {
	/* 'give NNNN coins victim' */
	int amount;

	amount   = atoi(arg1);
	if ( amount <= 0
	|| ( str_cmp( arg2, "coins" ) && str_cmp( arg2, "coin" ) ) )
	{
	    send_to_char( "Sorry, you can't do that.\n\r", ch );
	    return;
	}

	argument = one_argument( argument, arg2 );
	if ( !str_cmp( arg2, "to" ) && argument[0] != '\0' )
	    argument = one_argument( argument, arg2 );
	if ( arg2[0] == '\0' )
	{
	    send_to_char( "Give what to whom?\n\r", ch );
	    return;
	}

	if ( ( victim = get_char_room( ch, arg2 ) ) == NULL )
	{
	    send_to_char( "They aren't here.\n\r", ch );
	    return;
	}

	if ( ch->gold < amount )
	{
	    send_to_char( "Very generous of you, but you haven't got that much gold.\n\r", ch );
	    return;
	}

	ch->gold     -= amount;
	victim->gold += amount;
        strcpy(buf, "$n gives you ");
        strcat(buf, arg1 );
        strcat(buf, (amount > 1) ? " coins." : " coin.");

	act( AT_ACTION, buf, ch, NULL, victim, TO_VICT    );
/*	sprintf(buf, "You are taxed %d gold coins.", amount-taxed(amount));
	act( AT_GOLD, buf, ch, NULL, victim, TO_VICT);
	tax(victim, amount); */ //don't tax players recieving money from another player -Darwin
	act( AT_ACTION, "$n gives $N some gold.",  ch, NULL, victim, TO_NOTVICT );
	act( AT_ACTION, "You give $N some gold.",  ch, NULL, victim, TO_CHAR    );
	mprog_bribe_trigger( victim, ch, amount );

	if(!IS_NPC(ch)) 
    {
        if (IS_NPC (victim))
            call_lua_mob_num (ch, "bribe", victim->pIndexData->vnum, amount);
        else
            call_lua_char_num (ch, "bribe", ch->name, amount);
    }

   if ( IS_SET( sysdata.save_flags, SV_GIVE ) && !char_died(ch) )
	    save_char_obj(ch);
	if ( IS_SET( sysdata.save_flags, SV_RECEIVE ) && !char_died(victim) )
	    save_char_obj(victim);
	return;
    }

    if ( ( obj = get_obj_carry( ch, arg1 ) ) == NULL )
    {
	send_to_char( "You do not have that item.\n\r", ch );
	return;
    }

    if ( obj->wear_loc != WEAR_NONE )
    {
	send_to_char( "You must remove it first.\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg2 ) ) == NULL )
    {
	send_to_char( "They aren't here.\n\r", ch );
	return;
    }

    if ( !can_drop_obj( ch, obj ) )
    {
	send_to_char( "You can't let go of it.\n\r", ch );
	return;
    }

    if ( victim->carry_number + (get_obj_number(obj)/obj->count) > can_carry_n( victim ) && (victim != ch) )
    {
	act( AT_PLAIN, "$N has $S hands full.", ch, NULL, victim, TO_CHAR );
	return;
    }

    if ( victim->carry_weight + (get_obj_weight(obj)/obj->count) > can_carry_w( victim ) && (victim != ch) )
    {
	act( AT_PLAIN, "$N can't carry that much weight.", ch, NULL, victim, TO_CHAR );
	return;
    }

    if ( !can_see_obj( victim, obj ) )
    {
	act( AT_PLAIN, "$N can't see it.", ch, NULL, victim, TO_CHAR );
	return;
    }

    if (IS_OBJ_STAT( obj, ITEM_PROTOTYPE ) && !can_take_proto( victim ) )
    {
	act( AT_PLAIN, "You cannot give that to $N!", ch, NULL, victim, TO_CHAR );
	return;
    }

    separate_obj(obj);
    obj_from_char(obj);
    act(AT_ACTION, "$n gives $p to $N.", ch, obj, victim, TO_NOTVICT);
    act(AT_ACTION, "$n gives you $p.",   ch, obj, victim, TO_VICT   );
    act(AT_ACTION, "You give $p to $N.", ch, obj, victim, TO_CHAR   );
    obj = obj_to_char(obj, victim);
    mprog_give_trigger(victim, ch, obj);

	if(!IS_NPC(ch)) 
    {
        if (IS_NPC (victim))
            call_lua_mob_num (ch, "give", victim->pIndexData->vnum, obj->pIndexData->vnum);
        else
            call_lua_char_num (ch, "give", ch->name, obj->pIndexData->vnum);
    }

    if ( IS_SET(sysdata.save_flags, SV_GIVE) && !char_died(ch) )
	save_char_obj(ch);
    if ( IS_SET(sysdata.save_flags, SV_RECEIVE) && !char_died(victim) )
	save_char_obj(victim);
    return;
}

/*
 * Damage an object.						-Thoric
 * Affect player's AC if necessary.
 * Make object into scraps if necessary.
 * Send message about damaged object.
 */
obj_ret damage_obj( OBJ_DATA *obj )
{
    CHAR_DATA *ch;
    obj_ret objcode;

    ch = obj->carried_by;
    objcode = rNONE;
  
    separate_obj( obj );
    if ( !IS_NPC(ch) && (!IS_PKILL(ch) || (IS_PKILL(ch) && !IS_SET(ch->pcdata->flags, PCFLAG_GAG))) )
	act( AT_OBJECT, "($p gets damaged)", ch, obj, NULL, TO_CHAR );
    else
    if ( obj->in_room && ( ch = obj->in_room->first_person ) != NULL )
    {
	act( AT_OBJECT, "($p gets damaged)", ch, obj, NULL, TO_ROOM );
	act( AT_OBJECT, "($p gets damaged)", ch, obj, NULL, TO_CHAR );
	ch = NULL;
    }

    if ( (obj->item_type != ITEM_LIGHT || obj->item_type != ITEM_ARTLIGHT) )
    	oprog_damage_trigger(ch, obj);
    else if ( !in_arena( ch ) )
    	oprog_damage_trigger(ch, obj);

    if ( obj_extracted(obj) )
	return global_objcode;

    switch( obj->item_type )
    {
	default:
	  make_scraps( obj );
	  objcode = rOBJ_SCRAPPED;
	  break;
	case ITEM_CONTAINER:
	case ITEM_KEYRING:
	case ITEM_QUIVER:
	  if (--obj->value[3] <= 0) 
	  {
	    if ( !in_arena( ch ) )
	    {
		make_scraps( obj );
		objcode = rOBJ_SCRAPPED;
	    }
	    else
		obj->value[3] = 1;
	  }
	  break;
        case ITEM_ARTLIGHT:
	case ITEM_LIGHT:
	  if (--obj->value[0] <= 0)
	  {
	    if ( !in_arena( ch ) )
	    {
		make_scraps( obj );
		objcode = rOBJ_SCRAPPED;
	    }
	    else
		obj->value[0] = 1;
	  }
	  break; 
	case ITEM_ARMOR:
	case ITEM_ARTARMOR:
	  if ( ch && obj->value[0] >= 1 )
	    ch->armor += apply_ac( obj, obj->wear_loc );
	    ch->armorworn += apply_ac( obj, obj->wear_loc );
	  if (--obj->value[0] <= 0)
	  {
	    if ( !IS_PKILL( ch ) && !in_arena( ch ) )
	    {
		make_scraps( obj );
		objcode = rOBJ_SCRAPPED;
	    }
	    else
	    {
		obj->value[0] = 1;
		ch->armor -= apply_ac( obj, obj->wear_loc );
		ch->armorworn -= apply_ac( obj, obj->wear_loc );
	    }
	  }
	  else
	  if ( ch && obj->value[0] >= 1 )
	    ch->armor -= apply_ac( obj, obj->wear_loc );
	    ch->armorworn -= apply_ac( obj, obj->wear_loc );
	  break;
	case ITEM_WEAPON:
	case ITEM_ARTWEAPON:
	  if (--obj->value[0] <= 0)
	  {
	     if ( !IS_PKILL( ch ) && !in_arena( ch ) )
	     {
		make_scraps( obj );
		objcode = rOBJ_SCRAPPED;
	     }
	     else
		obj->value[0] = 1;
	  }
	  break;
    }
    return objcode;
}


/*
 * Remove an object.
 */
bool remove_obj( CHAR_DATA *ch, int iWear, bool fReplace )
{
    OBJ_DATA *obj, *tmpobj;

    if ( ( obj = get_eq_char( ch, iWear ) ) == NULL )
	return TRUE;

    if ( !fReplace
    &&   ch->carry_number + get_obj_number( obj ) > can_carry_n( ch ) )
    {
	act( AT_PLAIN, "$d: you can't carry that many items.",
	    ch, NULL, obj->name, TO_CHAR );
	return FALSE;
    }

    if ( !fReplace )
	return FALSE;

    if ( IS_OBJ_STAT(obj, ITEM_NOREMOVE) )
    {
	act( AT_PLAIN, "You can't remove $p.", ch, obj, NULL, TO_CHAR );
	return FALSE;
    }

    if ( obj == get_eq_char( ch, WEAR_WIELD )
    && ( tmpobj = get_eq_char( ch, WEAR_DUAL_WIELD)) != NULL )
       tmpobj->wear_loc = WEAR_WIELD;

    unequip_char( ch, obj );

    act( AT_ACTION, "$n stops using $p.", ch, obj, NULL, TO_ROOM );
    act( AT_ACTION, "You stop using $p.", ch, obj, NULL, TO_CHAR );
    oprog_remove_trigger( ch, obj );
    return TRUE;
}

/*
 * See if char could be capable of dual-wielding		-Thoric
 */
bool could_dual( CHAR_DATA *ch )
{
    if ( IS_NPC(ch) || ch->pcdata->learned[gsn_dual_wield] || ch->pcdata->learned[gsn_enhanced_dual_wield] )
	return TRUE;

    return FALSE;
}

bool could_2hand( CHAR_DATA *ch )
{
   if (IS_2HANDER(ch) || ch->pcdata->learned[gsn_enhanced_dual_wield] )
	return TRUE;

   return FALSE;
}

/*
 * See if char can dual wield at this time			-Thoric
 */
bool can_dual( CHAR_DATA *ch )
{
    if ( !could_dual(ch) )
	return FALSE;

    if ( get_eq_char( ch, WEAR_DUAL_WIELD ) )
    {
	send_to_char( "You are already wielding two weapons!\n\r", ch );
	return FALSE;
    }
    if ( get_eq_char( ch, WEAR_SHIELD ) )
    {
	send_to_char( "You cannot dual wield while holding a shield!\n\r", ch );
	return FALSE;
    }
    if ( get_eq_char( ch, WEAR_HOLD ) )
    {
	send_to_char( "You cannot dual wield while holding something!\n\r", ch );
	return FALSE;
    }
    return TRUE;
}

bool can_2hand( CHAR_DATA *ch )
{            
    if ( !IS_2HANDER(ch) )
    {
	send_to_char( "Your profession hasn't taught you how to wield big weapons.\n\r",ch );
	return FALSE;
    }  
    if ( get_eq_char( ch, WEAR_DUAL_WIELD ) ) 
    { 
        send_to_char( "You are already wielding two weapons!\n\r", ch );
        return FALSE;
    }        
    if ( get_eq_char( ch, WEAR_SHIELD ) && !ch->pcdata->learned[gsn_enhanced_dual_wield] )
    { 
        send_to_char( "You cannot wield a two-handed weapon while holding a shield!\n\r", ch );
        return FALSE; 
    } 
    if ( get_eq_char( ch, WEAR_HOLD ) && !ch->pcdata->learned[gsn_enhanced_dual_wield] ) 
    { 
        send_to_char( "You cannot wield a two-handed weapon while holding something!\n\r", ch );
        return FALSE;
    } 
    return TRUE; 
} 
   

/*
 * Wear one object.
 * Optional replacement of existing objects.
 * Big repetitive code, ick.
 *
 * Restructured a bit to allow for specifying body location	-Thoric
 * & Added support for layering on certain body locations
 */
void wear_obj( CHAR_DATA *ch, OBJ_DATA *obj, bool fReplace, sh_int wear_bit )
{
    OBJ_DATA *tmpobj = NULL;
    sh_int bit, tmp;

    separate_obj( obj );

    if( (( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_WARRIOR(ch)                                           )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_MONK(ch)                                              )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_RANGER(ch)                                            )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_CHAMPION(ch)                                          )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_DRUID(ch)                                             )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_MAGE(ch)                                              )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_CONJURER(ch)                                          )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_ARCHMAGI(ch)                                          ) 
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_THIEF(ch)                                             )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_THUG(ch)                                              )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_JESTER(ch)                                            )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_ROGUE(ch)                                             )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_CLERIC(ch)                                            )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_DIABOLIST(ch)                                         )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_SHAMAN(ch)                                            )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_BISHOP(ch)                                            )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_GOOD)     && IS_GOOD(ch)                                              )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_EVIL)     && IS_EVIL(ch)                                              )
    ||   ( IS_OBJ_STAT(obj, ITEM_ANTI_NEUTRAL)  && IS_NEUTRAL(ch)                                           )
    ||   ( IS_OBJ_STAT(obj, ITEM_GOLEM)         && !IS_NPC(ch)                                              )
    ||   ( IS_OBJ_STAT(obj, ITEM_GOLEM)         && (IS_NPC(ch) && ch->pIndexData->vnum != MOB_VNUM_GOLEM)   )
    ||   ( IS_OBJ_STAT(obj, ITEM_CONJURER)      && (!IS_CONJURER(ch) && !IS_ARCHMAGI(ch))                   )                  
    ||   ( IS_PET(ch)                           && !PET_CAN_WEAR(obj))                                      )
    &&   !IS_IMMORTAL(ch)
      )
    {
        /*
        if( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_WARRIOR(ch))
            send_to_char("Obj is anti_warrior and you are a warrior.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_MONK(ch))
            send_to_char("Obj is anti_warrior and you are a monk.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_RANGER(ch))
            send_to_char("Obj is anti_warrior and you are a ranger.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_WARRIOR)  && IS_CHAMPION(ch))
            send_to_char("Obj is anti_warrior and you are a champion.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_DRUID(ch))
            send_to_char("Obj is anti_mage and you are a druid.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_MAGE(ch))
            send_to_char("Obj is anti_mage and you are a druid.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_CONJURER(ch))
            send_to_char("Obj is anti_mage and you are a conjurer.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_MAGE)     && IS_ARCHMAGI(ch)) 
            send_to_char("Obj is anti_mage and you are a archmagi.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_THIEF(ch))
            send_to_char("Obj is anti_thief and you are a thief.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_THUG(ch))
            send_to_char("Obj is anti_thief and you are a thug.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_JESTER(ch))
            send_to_char("Obj is anti_thief and you are a jester.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_THIEF)    && IS_ROGUE(ch))
            send_to_char("Obj is anti_thief and you are a rogue.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_CLERIC(ch))
            send_to_char("Obj is anti_cleric and you are a cleric.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_DIABOLIST(ch))
            send_to_char("Obj is anti_cleric and you are a diabolist.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_SHAMAN(ch))
            send_to_char("Obj is anti_cleric and you are a shaman.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_CLERIC)   && IS_BISHOP(ch))
            send_to_char("Obj is anti_cleric and you are a bishop.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_GOOD)     && IS_GOOD(ch))
            send_to_char("Obj is anti_good and you are a good.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_EVIL)     && IS_EVIL(ch))
            send_to_char("Obj is anti_evil and you are a evil.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_ANTI_NEUTRAL)  && IS_NEUTRAL(ch))
            send_to_char("Obj is anti_neutral and you are a neutral.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_GOLEM)         && !IS_NPC(ch))
            send_to_char("Obj is item_golem and you are not npc.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_GOLEM)         && (IS_NPC(ch) && ch->pIndexData->vnum != MOB_VNUM_GOLEM))
            send_to_char("Obj is item_golem and you are not golem.\n\r", ch);
        if( IS_OBJ_STAT(obj, ITEM_CONJURER)      && (!IS_CONJURER(ch) && !IS_ARCHMAGI(ch)))                  
            send_to_char("Obj is item_conjurer and you are not conjurer or archmagi.\n\r", ch);
        if( IS_PET(ch)                           && !PET_CAN_WEAR(obj))
            send_to_char("Obj is not for pets and you are a pet.\n\r", ch);
        if(!IS_IMMORTAL(ch))
            send_to_char("You are not immortal.\n\r", ch);
        */
        
        act( AT_MAGIC, "You are forbidden to use that item.", ch, NULL, NULL, TO_CHAR );
        act( AT_ACTION, "$n tries to use $p, but is forbidden to do so.", ch, obj, NULL, TO_ROOM );
        return;
    }

    if( IS_WEAPON(obj) )
    {
        if( !IS_MONK_WEAPON(obj) && !IS_IMMORTAL(ch) && IS_MONK(ch) )
        {
            act( AT_ACTION, "Your class would not use that type of weapon!", ch, NULL, NULL, TO_CHAR );
            act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM ); 
            return;
        }
        if( !xIS_SET(obj->extra_flags, ITEM_2HAND) && IS_SET(obj->wear_flags, ITEM_WIELD)  ) 
        if( !IS_NPC(ch) && !IS_IMMORTAL(ch) && IS_THUG(ch) )
        { 
            act( AT_ACTION, "Your class would not use that type of weapon!", ch, NULL, NULL, TO_CHAR );
            act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM );
            return; 
        }
        if ( IS_OBJ_STAT(obj, ITEM_2HAND) && !IS_2HANDER(ch) )
        {  
            act( AT_ACTION, "Your class isn't proficient with two-handed weapons.", ch, NULL, NULL, TO_CHAR );
            act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM );
            return;
        } 
    }
   
    if ( wear_bit > -1 )
    {
        bit = wear_bit;
        if ( !CAN_WEAR(obj, 1 << bit) )
        {
            if ( fReplace )
            {
                switch( 1 << bit )
                {
                    case ITEM_HOLD:
                        send_to_char( "You cannot hold that.\n\r", ch );
                        break;
                    case ITEM_WIELD:
                        send_to_char( "You cannot wield that.\n\r", ch );
                        break;
                    default:
                        ch_printf( ch, "You cannot wear that on your %s.\n\r", w_flags[bit] );
                        break;
                }
            }
            return;
        }
    }
    else
    {
        for ( bit = -1, tmp = 1; tmp < 31; tmp++ )
        {
            if ( CAN_WEAR(obj, 1 << tmp) )
            {
                bit = tmp;
                break;
            }
        }
    }

    /* currently cannot have a light in non-light position */
    if ( IS_LIGHT(obj) )
    {
        if ( !remove_obj( ch, WEAR_LIGHT, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n holds $p as a light.", ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You hold $p as your light.",  ch, obj, NULL, TO_CHAR );
        }
        equip_char( ch, obj, WEAR_LIGHT );
        oprog_wear_trigger( ch, obj );
        return;
    }

    if ( bit == -1 )
    {
        if ( fReplace )
            send_to_char( "You can't wear, wield, or hold that.\n\r", ch );
        return;
    }

    switch ( 1 << bit )
    {
	default:
	    bug( "wear_obj: uknown/unused item_wear bit %d", bit );
	    if ( fReplace )
            send_to_char( "You can't wear, wield, or hold that.\n\r", ch );
	    return;

	case ITEM_WEAR_FINGER:
	    if ( get_eq_char( ch, WEAR_FINGER_L )
	    &&   get_eq_char( ch, WEAR_FINGER_R )
	    &&   !remove_obj( ch, WEAR_FINGER_L, fReplace )
	    &&   !remove_obj( ch, WEAR_FINGER_R, fReplace ) )
		return;

	    if ( !get_eq_char( ch, WEAR_FINGER_L ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n slips $s left finger into $p.",    ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You slip your left finger into $p.",  ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_FINGER_L );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    if ( !get_eq_char( ch, WEAR_FINGER_R ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n slips $s right finger into $p.",   ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You slip your right finger into $p.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_FINGER_R );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    bug( "Wear_obj: no free finger.", 0 );
	    send_to_char( "You already wear something on both fingers.\n\r", ch );
	    return;

	case ITEM_WEAR_NECK:
	    if ( get_eq_char( ch, WEAR_NECK_1 ) != NULL
	    &&   get_eq_char( ch, WEAR_NECK_2 ) != NULL
	    &&   !remove_obj( ch, WEAR_NECK_1, fReplace )
	    &&   !remove_obj( ch, WEAR_NECK_2, fReplace ) )
		return;

	    if ( !get_eq_char( ch, WEAR_NECK_1 ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n wears $p around $s neck.",   ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You wear $p around your neck.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_NECK_1 );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    if ( !get_eq_char( ch, WEAR_NECK_2 ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n wears $p around $s neck.",   ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You wear $p around your neck.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_NECK_2 );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    bug( "Wear_obj: no free neck.", 0 );
	    send_to_char( "You already wear two neck items.\n\r", ch );
	    return;

	case ITEM_WEAR_BODY:
	    if ( !remove_obj( ch, WEAR_BODY, fReplace ) )
            return;

        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n fits $p on $s body.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You fit $p on your body.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_BODY );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_HEAD:
	    if ( !remove_obj( ch, WEAR_HEAD, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n dons $p upon $s head.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You don $p upon your head.", ch, obj, NULL, TO_CHAR );
        }
        equip_char( ch, obj, WEAR_HEAD );
        oprog_wear_trigger( ch, obj );
        return;

	case ITEM_WEAR_EYES:
	    if ( !remove_obj( ch, WEAR_EYES, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n places $p on $s eyes.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You place $p on your eyes.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_EYES );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_FACE:
	    if ( !remove_obj( ch, WEAR_FACE, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n places $p on $s face.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You place $p on your face.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_FACE );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_EARS:
	    if ( !remove_obj( ch, WEAR_EARS, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n wears $p on $s ears.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You wear $p on your ears.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_EARS );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_LEGS:
	    if ( !remove_obj( ch, WEAR_LEGS, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n slips into $p.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You slip into $p.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_LEGS );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_FEET:
	    if ( !remove_obj( ch, WEAR_FEET, fReplace ) )
	      return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n wears $p on $s feet.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You wear $p on your feet.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_FEET );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_HANDS:
	    if ( !remove_obj( ch, WEAR_HANDS, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n wears $p on $s hands.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You wear $p on your hands.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_HANDS );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_ARMS:
	    if ( !remove_obj( ch, WEAR_ARMS, fReplace ) )
            return;
	    if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n wears $p on $s arms.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You wear $p on your arms.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_ARMS );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_ABOUT:
	    if ( !remove_obj( ch, WEAR_ABOUT, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n wears $p about $s body.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You wear $p about your body.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_ABOUT );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_BACK:
	    if ( !remove_obj( ch, WEAR_BACK, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n slings $p on $s back.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You sling $p on your back.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_BACK );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_WAIST:
	    if ( !remove_obj( ch, WEAR_WAIST, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n wears $p about $s waist.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You wear $p about your waist.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_WAIST );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_WRIST:
	    if ( get_eq_char( ch, WEAR_WRIST_L )
	    &&   get_eq_char( ch, WEAR_WRIST_R )
	    &&   !remove_obj( ch, WEAR_WRIST_L, fReplace )
	    &&   !remove_obj( ch, WEAR_WRIST_R, fReplace ) )
	       return;

	    if ( !get_eq_char( ch, WEAR_WRIST_L ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n fits $p around $s left wrist.", ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You fit $p around your left wrist.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_WRIST_L );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    if ( !get_eq_char( ch, WEAR_WRIST_R ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n fits $p around $s right wrist.", ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You fit $p around your right wrist.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_WRIST_R );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    bug( "Wear_obj: no free wrist.", 0 );
	    send_to_char( "You already wear two wrist items.\n\r", ch );
	    return;

	case ITEM_WEAR_ANKLE:
	    if ( get_eq_char( ch, WEAR_ANKLE_L )
	    &&   get_eq_char( ch, WEAR_ANKLE_R )
	    &&   !remove_obj( ch, WEAR_ANKLE_L, fReplace )
	    &&   !remove_obj( ch, WEAR_ANKLE_R, fReplace ) )
	       return;

	    if ( !get_eq_char( ch, WEAR_ANKLE_L ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n fits $p around $s left ankle.", ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You fit $p around your left ankle.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_ANKLE_L );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    if ( !get_eq_char( ch, WEAR_ANKLE_R ) )
	    {
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n fits $p around $s right ankle.", ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You fit $p around your right ankle.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_ANKLE_R );
            oprog_wear_trigger( ch, obj );
            return;
	    }

	    bug( "Wear_obj: no free ankle.", 0 );
	    send_to_char( "You already wear two ankle items.\n\r", ch );
	    return;

	case ITEM_WEAR_SHIELD:
        if ( get_eq_char(ch, WEAR_DUAL_WIELD) ) 
        { 
            send_to_char( "You can't use a shield AND two weapons!\n\r", ch );
            return;
        }

        tmpobj = NULL;
	    tmpobj = get_eq_char( ch, WEAR_WIELD);
	    if ( tmpobj && IS_OBJ_STAT(tmpobj, ITEM_2HAND) )
	    {
            send_to_char( "You can't wear a shield while using a two-handed weapon!\n\r", ch);
            return;
	    }

	    if ( !remove_obj( ch, WEAR_SHIELD, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n uses $p as a shield.", ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You use $p as a shield.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_SHIELD );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WIELD:	
	    if ( !could_dual(ch) )
	    {
            if ( !remove_obj(ch, WEAR_WIELD, fReplace) )
                return;
            tmpobj = NULL;
	    }
	    else
	    {
            OBJ_DATA *dw, *hd;

            tmpobj = get_eq_char(ch, WEAR_WIELD);
            dw = get_eq_char(ch, WEAR_DUAL_WIELD);
            if ( tmpobj && (dw) )
            {
                send_to_char( "You're already wielding two weapons.\n\r", ch );
                return;
            }
            if ( tmpobj && IS_OBJ_STAT(tmpobj, ITEM_2HAND) && !ch->pcdata->learned[gsn_enhanced_dual_wield] )
            {
               send_to_char( "You can't dual wield when holding a two-handed weapon!\n\r",ch);
               return;
            }
            hd = get_eq_char(ch, WEAR_HOLD);
            if ( (dw && hd) || (tmpobj && hd) )
            {
                send_to_char( "You're already wielding a weapon AND holding something.\n\r", ch );
                return;
            }
	    }

	    if ( tmpobj )
	    {
            if ( can_dual(ch) )
            {
                if ( get_obj_weight(obj) + get_obj_weight(tmpobj) > str_app[get_curr_str(ch)].wield )
                {
                    send_to_char( "It is too heavy for you to wield.\n\r", ch );
                    return;
                }
                if ( IS_OBJ_STAT(obj, ITEM_2HAND) && !ch->pcdata->learned[gsn_enhanced_dual_wield] ) 
                { 
                    send_to_char( "This weapon is large enough that you need to remove your current weapon first.\n\r", ch); 
                    return; 
                } 
                if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
                {
                    act( AT_ACTION, "$n dual-wields $p.", ch, obj, NULL, TO_ROOM );
                    act( AT_ACTION, "You dual-wield $p.", ch, obj, NULL, TO_CHAR );
                }
                equip_char( ch, obj, WEAR_DUAL_WIELD );
                oprog_wear_trigger( ch, obj );
            }
            return;
	    }

	    if ( get_obj_weight(obj) > str_app[get_curr_str(ch)].wield )
	    {
            send_to_char( "It is too heavy for you to wield.\n\r", ch );
            return;
	    }
        if ( IS_OBJ_STAT(obj, ITEM_2HAND) && get_eq_char(ch, WEAR_SHIELD) && !ch->pcdata->learned[gsn_enhanced_dual_wield] )
	    {
            send_to_char( "You can't use a two-handed weapon with a shield!\n\r", ch );
            return;
	    }
	    if ( IS_OBJ_STAT(obj, ITEM_2HAND) && get_eq_char(ch, WEAR_HOLD) && !ch->pcdata->learned[gsn_enhanced_dual_wield] )
        {
            send_to_char( "You can't use a two-handed weapon with a held item!\n\r", ch );
            return;
        }
	    if ( IS_OBJ_STAT(obj, ITEM_2HAND) && get_eq_char(ch, WEAR_DUAL_WIELD) && !ch->pcdata->learned[gsn_enhanced_dual_wield] )
        {
            send_to_char( "You can't use a two-handed weapon with offhand weapons!\n\r", ch );
            return;
        }
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n wields $p.", ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You wield $p.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_WIELD );
	    oprog_wear_trigger( ch, obj );
	    return;

	case ITEM_WEAR_WWP:
		if ( get_eq_char( ch, WEAR_WWP_1 ) != NULL
		&&   get_eq_char( ch, WEAR_WWP_2 ) != NULL
		&&   !remove_obj( ch, WEAR_WWP_1, fReplace )
		&&   !remove_obj( ch, WEAR_WWP_2, fReplace ) )
		   return;

		if ( !get_eq_char( ch, WEAR_WWP_1 ) )
		{
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n wears $p with pride.", ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You wear $p with pride.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_WWP_1 );
            oprog_wear_trigger( ch, obj );
            return;
		}

		if ( !get_eq_char( ch, WEAR_WWP_2 ) )
		{
            if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
            {
                act( AT_ACTION, "$n wears $p with pride.", ch, obj, NULL, TO_ROOM );
                act( AT_ACTION, "You wear $p with pride.", ch, obj, NULL, TO_CHAR );
            }
            equip_char( ch, obj, WEAR_WWP_2 );
            oprog_wear_trigger( ch, obj );
            return;
		}
		bug( "Wear_obj: no free WWP.", 0 );
		send_to_char( "You already wear two pride items.\n\r", ch );
		return;

    case ITEM_WEAR_AURA:
        if ( !remove_obj( ch, WEAR_AURA, fReplace ) )
            return;
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) ) 
        { 
            act( AT_ACTION, "$p emanates from $n's body.", ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "$p emanates from your body.", ch, obj, NULL, TO_CHAR );
        } 
        equip_char( ch, obj, WEAR_AURA );   
        oprog_wear_trigger( ch, obj );
        return; 


	case ITEM_HOLD:
	    if ( get_eq_char(ch, WEAR_DUAL_WIELD) )
	    {
            send_to_char( "You cannot hold something AND two weapons!\n\r", ch );
            return;
	    }

 	    tmpobj = NULL;          
        tmpobj = get_eq_char( ch, WEAR_WIELD);
        if ( tmpobj && IS_OBJ_STAT(tmpobj, ITEM_2HAND) )
        {
            send_to_char( "You hold an item while using a two-handed weapon!\n\r", ch);
            return;
        }

	    if ( !remove_obj( ch, WEAR_HOLD, fReplace ) )
		return;
        if ( obj->item_type == ITEM_WAND
           || obj->item_type == ITEM_STAFF
           || obj->item_type == ITEM_FOOD 
	       || obj->item_type == ITEM_COOK
           || obj->item_type == ITEM_PILL
           || obj->item_type == ITEM_POTION
           || obj->item_type == ITEM_SCROLL
           || obj->item_type == ITEM_DRINK_CON 
           || obj->item_type == ITEM_BLOOD
           || obj->item_type == ITEM_PIPE
           || obj->item_type == ITEM_HERB
           || obj->item_type == ITEM_KEY
           || !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
            act( AT_ACTION, "$n holds $p in $s hands.",   ch, obj, NULL, TO_ROOM );
            act( AT_ACTION, "You hold $p in your hands.", ch, obj, NULL, TO_CHAR );
        }
	    equip_char( ch, obj, WEAR_HOLD );
	    oprog_wear_trigger( ch, obj );
	    return;
    }
}


void do_wear( CHAR_DATA *ch, char *argument )
{
    char *arg1, *arg2;
    OBJ_DATA *obj;
    sh_int wear_bit;

    call_va(L_mud, "one_arg", "s>ss", argument, &arg1, &argument);
    call_va(L_mud, "one_arg", "s>ss", argument, &arg2, &argument);
    if ( (!str_cmp(arg2, "on")  || !str_cmp(arg2, "upon") || !str_cmp(arg2, "around")) && argument[0] != '\0' )
        call_va(L_mud, "one_arg", "s>ss", argument, &arg2, &argument);


    if ( arg1[0] == '\0' )
    {
        send_to_char( "Wear, wield, or hold what?\n\r", ch );
        return;
    }

    if ( ms_find_obj(ch) )
        return;

    if ( !str_cmp( arg1, "all" ) )
    {
        OBJ_DATA *obj_next;

        for ( obj = ch->first_carrying; obj; obj = obj_next )
        {
            obj_next = obj->next_content;
            if ( obj->wear_loc == WEAR_NONE && can_see_obj( ch, obj ) )
            {
            if ( IS_DEMI(ch) && !xIS_SET(obj->extra_flags, ITEM_RANDOM)
                        // && (obj->pIndexData->vnum < 29000 || obj->pIndexData->vnum > 30000 )
                 && obj->value[ENCHANT_VALUE] != 0 )
            {
               act( AT_ACTION, "This item is not allowed to be worn by FLI's.", ch, NULL, NULL, TO_CHAR );
               return;
            }
        
            if ( IS_OBJ_STAT(obj, ITEM_METAL) && IS_NONMETAL(ch) )
            {  
               act( AT_ACTION, "Your class cannot use metal equipment!", ch, NULL, NULL, TO_CHAR );
               act( AT_ACTION, "$n tries to use $p, but looks uncomfortable with it.", ch, obj, NULL, TO_ROOM );
               return;
            }

            if( IS_WEAPON(obj) )
            {
                if( !xIS_SET(obj->extra_flags, ITEM_2HAND) && !IS_IMMORTAL(ch) && IS_THUG(ch) )
                {
                    act( AT_ACTION, "Your class would not use that type of weapon!", ch, NULL, NULL, TO_CHAR );
                    act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM );
                    return; 
                } 
                if( !IS_IMMORTAL(ch) && !IS_MONK_WEAPON(obj) && IS_MONK(ch) )
                {
                    act( AT_ACTION, "Your class would not use that type of weapon!", ch, NULL, NULL, TO_CHAR );
                    act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM );
                    return;
                }
                if ( IS_OBJ_STAT(obj, ITEM_2HAND) && !IS_2HANDER(ch) )
                {
                    act( AT_ACTION, "Your class isn't proficient with two-handed weapons.", ch, NULL, NULL, TO_CHAR );
                    act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM );
                    return;
                }
            }

            wear_obj( ch, obj, FALSE, -1 );
            if ( char_died(ch) )
                return;
            }
        }
        return;
    }
    else
    {
        if ( ( obj = get_obj_carry( ch, arg1 ) ) == NULL )
        {
            send_to_char( "You do not have that item.\n\r", ch );
            return;
        }
        
        if ( IS_OBJ_STAT( obj, ITEM_METAL) && IS_NONMETAL(ch) )
        {
            act( AT_ACTION, "Your class cannot use metal equipment!", ch, NULL, NULL, TO_CHAR );
            act( AT_ACTION, "$n tries to use $p, but looks uncomfortable with it.", ch, obj, NULL, TO_ROOM );
            return;
        } 
        
        if( IS_WEAPON(obj) )
        {
            if( !xIS_SET(obj->extra_flags, ITEM_2HAND) && !IS_IMMORTAL(ch) && IS_THUG(ch) )
            {
                act( AT_ACTION, "Your class would not use that type of weapon!", ch, NULL, NULL, TO_CHAR );
                act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM );
                return; 
            } 
            if( !IS_IMMORTAL(ch) && !IS_MONK_WEAPON(obj) && IS_MONK(ch) )
            {
                act( AT_ACTION, "Your class would not use that type of weapon!", ch, NULL, NULL, TO_CHAR );
                act( AT_ACTION, "$n studies the $p, but decides not to use it.", ch, obj, NULL, TO_ROOM );
                return;
            }
            if ( IS_OBJ_STAT(obj, ITEM_2HAND) && (!IS_IMMORTAL(ch) && !IS_2HANDER(ch)) )
            {     
                act( AT_ACTION, "Your class isn't proficient with two-handed weapons.", ch, NULL, NULL, TO_CHAR );
                act( AT_ACTION, "$n studies the $p, but decides not to useit.", ch, obj, NULL, TO_ROOM );
                return;
            }
        }

        if ( arg2[0] != '\0' )
          wear_bit = get_wflag(arg2);
        else
          wear_bit = -1;
        wear_obj( ch, obj, TRUE, wear_bit );
    }

    return;
}



void do_remove( CHAR_DATA *ch, char *argument )
{
    //~ char arg[MAX_INPUT_LENGTH];
    char *arg;
    OBJ_DATA *obj, *obj_next;


    //~ one_argument( argument, arg );
    call_va(L_mud, "one_arg", "s>ss", argument, &arg, &argument);

    if ( arg[0] == '\0' )
    {
	send_to_char( "Remove what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

   if ( !str_cmp( arg, "all" ) )  /* SB Remove all */
    {
      for ( obj = ch->first_carrying; obj != NULL ; obj = obj_next )
      {
        obj_next = obj->next_content;
        if ( obj->wear_loc != WEAR_NONE && can_see_obj ( ch, obj ) )
          remove_obj ( ch, obj->wear_loc, TRUE );
      }
      return;
    }

    if ( ( obj = get_obj_wear( ch, arg ) ) == NULL )
    {
	send_to_char( "You are not using that item.\n\r", ch );
	return;
    }
    if ( (obj_next=get_eq_char(ch, obj->wear_loc)) != obj )
    {
	act( AT_PLAIN, "You must remove $p first.", ch, obj_next, NULL, TO_CHAR );
	return;
    }

    remove_obj( ch, obj->wear_loc, TRUE );
    return;
}


void do_bury( CHAR_DATA *ch, char *argument )
{
    //~ char arg[MAX_INPUT_LENGTH];
    char *arg;
    OBJ_DATA *obj;
    bool shovel;
    sh_int move;

    //~ one_argument( argument, arg );
    call_va(L_mud, "one_arg", "s>ss", argument, &arg, &argument);

    if ( arg[0] == '\0' )
    {    
        send_to_char( "What do you wish to bury?\n\r", ch );
        return;
    }
    
    if ( ms_find_obj(ch) )
        return;
 
    shovel = FALSE;
    for ( obj = ch->first_carrying; obj; obj = obj->next_content )
      if ( obj->item_type == ITEM_SHOVEL )
      {
	  shovel = TRUE;
	  break;
      }

    obj = get_obj_list_rev( ch, arg, ch->in_room->last_content );
    if ( !obj )
    {
        send_to_char( "You can't find it.\n\r", ch );
        return;
    }

    separate_obj(obj);
    if ( !CAN_WEAR(obj, ITEM_TAKE) )
    {
	if ( !IS_OBJ_STAT( obj, ITEM_CLANCORPSE )
	|| IS_NPC(ch) )
	   {	
		act( AT_PLAIN, "You cannot bury $p.", ch, obj, 0, TO_CHAR );
        	return;
           }
    }
  
    switch( ch->in_room->sector_type )
    {
	case SECT_CITY:
	case SECT_INSIDE:
	case SECT_BOAT:
	    send_to_char( "The floor is too hard to dig through.\n\r", ch );
	    return;
	case SECT_WATER_SWIM:
	case SECT_WATER_NOSWIM:
	case SECT_UNDERWATER:
	    send_to_char( "You cannot bury something here.\n\r", ch );
	    return;
	case SECT_AIR:
	    send_to_char( "What?  In the air?!\n\r", ch );
	    return;
    }

    if ( obj->weight > (UMAX(5, (can_carry_w(ch) / 10)))
    &&  !shovel )
    {
	send_to_char( "You'd need a shovel to bury something that big.\n\r", ch );
	return;
    }
    
    move = (obj->weight * 50 * (shovel ? 1 : 5)) / UMAX(1, can_carry_w(ch));
    move = URANGE( 2, move, 1000 );
    if ( move > ch->move )
    {
	send_to_char( "You don't have the energy to bury something of that size.\n\r", ch );
	return;
    }
    ch->move -= move;
    if ( obj->item_type == ITEM_CORPSE_NPC
    ||   obj->item_type == ITEM_CORPSE_PC )
	adjust_favor( ch, 6, 1 );

    act( AT_ACTION, "You solemnly bury $p...", ch, obj, NULL, TO_CHAR );
    act( AT_ACTION, "$n solemnly buries $p...", ch, obj, NULL, TO_ROOM );
    xSET_BIT( obj->extra_flags, ITEM_BURIED );
    WAIT_STATE( ch, URANGE( 10, move / 2, 100 ) );
    return;
}

void do_sacrifice( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];
    char name[50];
    OBJ_DATA *obj;
    CLAN_DATA *clan;
	bool items_found = FALSE;

    one_argument( argument, arg );

    if ( arg[0] == '\0' || !str_cmp( arg, ch->name ) )
    {
	act( AT_ACTION, "$n offers $mself to $s deity, who graciously declines.",
	    ch, NULL, NULL, TO_ROOM );
	send_to_char( "Your deity appreciates your offer and may accept it later.\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

	/*
	 * "sac all"
	 * If argument to sacrifice is exactly "all" then all the item in the room
	 * that the player can legally pick up will be sacrificed. One message total
	 * is displayed to the room and to the character. This is a much less
	 * spammy version of a sac all command than I've seen elsewhere. -Darwin
	 */
	if(!str_cmp( arg, "all"))
	{
		for ( obj = ch->in_room->first_content; obj; obj = obj->next_content )
		{
			if ( can_see_obj( ch, obj ) && IS_SET( obj->wear_flags, ITEM_TAKE ) )
			{
				if ( !IS_IMMORTAL(ch) && (obj->owner)&& str_cmp( ch->name, obj->owner ) ) 
                    continue;   // do nothing
				else if ( obj->item_type == ITEM_CORPSE_PC ) 
                    continue;   // dito
				else if ( !IS_IMMORTAL(ch) && IS_OBJ_STAT(obj, ITEM_CLANOBJECT ) ) 
                    continue;	// dito
				else
				{
					if(obj->pIndexData->vnum == 2 || obj->pIndexData->vnum == 3)
					{
						ch->gold += taxed(obj->value[MONEY_AMOUNT]);
						tax(ch,obj->value[MONEY_AMOUNT]);
					}
					else
						ch->gold += 1;
                    separate_obj(obj);
					items_found = TRUE;
					oprog_sac_trigger( ch, obj );
					if ( cur_obj == obj->serial )
						global_objcode = rOBJ_SACCED;
					extract_obj( obj );
					if ( IS_SET(ch->in_room->room_flags, ROOM_CLANSTOREROOM) )
					{
					   for ( clan = first_clan; clan; clan = clan->next )
						  if ( clan->storeroom == ch->in_room->vnum )
						save_clan_storeroom(ch, clan);
					}
				}
			}
		}
		if(items_found) // if items were found and sacrificed, display appropriate message
		{
			if ( !IS_NPC( ch ) && ch->pcdata->deity && ch->pcdata->deity->name[0] != '\0' )
			{
			strcpy( name, ch->pcdata->deity->name );
			}
			else if ( !IS_NPC( ch ) && IS_GUILDED(ch) && sysdata.guild_overseer[0] != '\0' ) 
			{
			strcpy( name, sysdata.guild_overseer );
			}
			else if ( !IS_NPC( ch ) && ch->pcdata->clan && ch->pcdata->clan->deity[0] != '\0' )
			{
			strcpy( name, ch->pcdata->clan->deity );
			}
			else
			{
			strcpy( name, "Darwin" );
			}
			sprintf( buf, "%s gives you one gold coin for each of your sacrifices.\n\r", name );
			send_to_char( buf, ch );
			sprintf( buf, "$n sacrifices everything to %s.", name );
			act( AT_ACTION, buf, ch, NULL, NULL, TO_ROOM );
		}
	return;
	}// end of "sac all"

    obj = get_obj_list_rev( ch, arg, ch->in_room->last_content );
    if ( !obj )
    {
	send_to_char( "You can't find it.\n\r", ch );
	return;
    }
    
    separate_obj(obj);
    if ( !CAN_WEAR(obj, ITEM_TAKE) )
    {
	act( AT_PLAIN, "$p is not an acceptable sacrifice.", ch, obj, 0, TO_CHAR );
	return;
    }
    
    if ( obj->item_type == ITEM_CORPSE_PC )
    {
	act( AT_PLAIN, "You can't sacrifice the corpse of another player!.", ch, obj, 0, TO_CHAR );
        return;
    }

    if ( !IS_IMMORTAL(ch) && IS_OBJ_STAT(obj, ITEM_CLANOBJECT ) )
    {
	act( AT_PLAIN, "This is a clan object...don't sacrifice it!", ch, obj, 0, TO_CHAR );
	return;
    }

    if ( !IS_IMMORTAL(ch) && (obj->owner)&& str_cmp( ch->name, obj->owner ) )
    {
	act( AT_PLAIN, "This is tied to another owner.", ch, obj, 0, TO_CHAR );
	return;
    }
    
    if ( !IS_NPC( ch ) && ch->pcdata->deity && ch->pcdata->deity->name[0] != '\0' )
    {
	strcpy( name, ch->pcdata->deity->name );
    }
    else if ( !IS_NPC( ch ) && IS_GUILDED(ch) && sysdata.guild_overseer[0] != '\0' ) 
    {
	strcpy( name, sysdata.guild_overseer );
    }
    else if ( !IS_NPC( ch ) && ch->pcdata->clan && ch->pcdata->clan->deity[0] != '\0' )
    {
	strcpy( name, ch->pcdata->clan->deity );
    }
    else
    {
	strcpy( name, "Darwin" );
    }
    ch->gold += 1;	  
    sprintf( buf, "%s gives you one gold coin for your sacrifice.\n\r", name );
    send_to_char( buf, ch );
    sprintf( buf, "$n sacrifices $p to %s.", name );
    act( AT_ACTION, buf, ch, obj, NULL, TO_ROOM );
    oprog_sac_trigger( ch, obj );
    if ( obj_extracted(obj) )
      return;
    if ( cur_obj == obj->serial )
      global_objcode = rOBJ_SACCED;
    separate_obj( obj );
    extract_obj( obj );
    /* Clan storeroom check */
	if ( IS_SET(ch->in_room->room_flags, ROOM_CLANSTOREROOM) )
	{
/*	   if (!char_died && !save_char ) save_char_obj(ch); */
	   for ( clan = first_clan; clan; clan = clan->next )
	      if ( clan->storeroom == ch->in_room->vnum )
		save_clan_storeroom(ch, clan);
	}
    return;
}

void do_rinvoke( CHAR_DATA *ch, char *argument )
{
    char *arg;

    call_va(L_mud, "str_lower", "s>s", argument, &argument);
    call_va(L_mud, "one_arg", "s>ss", argument, &arg, &argument);
    
    if ( !IS_NPC(ch) )
    {
        if ( !IS_IMMORTAL(ch) )
        {
            send_to_char( "Huh?\n\r", ch );
            return;
        }
    }

    if ( IS_NPC(ch) && IS_AFFECTED( ch, AFF_CHARM ) ) 
    { 
        send_to_char( "You can't concentrate enough for that.\n\r", ch ); 
        return; 
    }

    if( arg[0] == '\0' )
    {
        send_to_char( "&WInvoke an EQUIPMENT, MAGIC, COMPONENT or ARTIFACT random item?\n\r&D", ch );
        return;
    }
    if ( !strcmp(arg, "equipment") ) 
    {
        send_to_char( "&WEquipment created!\n\r&D", ch );
        wield_random_armor( ch );
    }
    if ( !strcmp(arg, "magic") ) 
    {
        send_to_char( "&WMagic invoked!\n\r&D", ch );
        wield_random_magic( ch );
    }
    if ( !strcmp(arg, "artifact") ) 
    {
        send_to_char( "&WArtifact invoked!\n\r&D", ch );
        wield_random_artifact( ch );
    }
    if ( !strcmp(arg, "component") ) 
    {
        send_to_char( "&WComponent invoked!\n\r&D", ch );
        wield_random_component( ch );
    }
    if ( !strcmp(arg, "relic") ) 
    {
        send_to_char( "&WRelic invoked!\n\r&D", ch );
        wield_random_relic( ch );
    }
}

        

void do_junk( CHAR_DATA *ch, char *argument )    // Added by Drazuk
{
    OBJ_DATA *obj, *obj_prev;
    bool found = FALSE;

    if ( !argument || argument[0] == '\0' )
    {
	send_to_char( "Junk what?\n\r", ch );
	return;
    }

    for( obj = ch->last_carrying; obj; obj = obj_prev )
    {
	obj_prev = obj->prev_content;
	if ( ( nifty_is_name( argument, obj->name ) ) && can_see_obj( ch, obj ) && obj->wear_loc == WEAR_NONE )
	{
	    found = TRUE;
	    break;
	}
    }
    if( found )
    {
	if( !can_drop_obj( ch, obj ) && ch->level < LEVEL_IMMORTAL )
	{
	    send_to_char( "You cannot junk that, it's cursed!\n\r", ch );
	    return;
	}
        if ( !IS_IMMORTAL(ch) && (obj->owner)&& str_cmp( ch->name, obj->owner ) )
        {
           act( AT_PLAIN, "This is tied to another owner.", ch, obj, 0, TO_CHAR );
           return; 
        }
        if ( !IS_IMMORTAL(ch) && IS_OBJ_STAT(obj, ITEM_CLANOBJECT ) )
        { 
           act( AT_PLAIN, "This is a clan object...don't junk it!", ch, obj, 0, TO_CHAR );
           return; 
        }
		if (IS_OBJ_STAT(obj, ITEM_NOJUNK))
		{
			act( AT_PLAIN, "You cannot junk this item. Sacrifice it instead.", ch, obj, 0, TO_CHAR );
			return;
		}
	separate_obj( obj );
	act( AT_ACTION, "$n junks $p.", ch, obj, NULL, TO_ROOM );
	act( AT_ACTION, "You junk $p.", ch, obj, NULL, TO_CHAR );
	obj_from_char( obj );
	extract_obj( obj );
    }
    else
    {
	send_to_char( "Junk what?\n\r", ch );
    }
    return;
}

/* Donate command created by Samson 2-6-98
   Coded by unknown author.  Players can donate items for others to use.

   Modified by Whir for multiple donation rooms - 3/25/98 
   Slight bug corrected, objects weren't being seperated from each other - Whir 3/25/98 
   Updated to use internal Smaug random number generator - Samson 9/11/98 
*/
void do_donate( CHAR_DATA *ch, char *argument)
{
    OBJ_DATA *obj;

    if( !argument || argument[0] == '\0' )
    {
        send_to_char( "Donate what?\n\r",ch );
        return;
    }

    if ( ch->position == POS_FIGHTING )
    {
        send_to_char( "You cannot donate while fighting!\n\r",ch );
        return;
    }

    if ( ( obj = get_obj_carry (ch, argument) ) == NULL )
    {
        send_to_char("You do not have that!\n\r",ch );
        return;
    }
    else
    {
	if ( !can_drop_obj(ch, obj) && ch->level < LEVEL_IMMORTAL )
	{
	    send_to_char( "You cannot donate that, it's cursed!\n\r", ch);
	    return;
 	}

	if ( ( obj->item_type == ITEM_CORPSE_NPC ) || ( obj->item_type == ITEM_CORPSE_PC ) )
	{
	    send_to_char( "You cannot donate corpses!\n\r", ch);
	    return;
	}

    if ( !IS_IMMORTAL(ch) && IS_OBJ_STAT(obj, ITEM_CLANOBJECT ) )
    { 
       act( AT_PLAIN, "This is a clan object...don't donate it!", ch, obj, 0, TO_CHAR );
       return; 
    }

	if ( obj->timer > 0 )
	{
	    send_to_char( "You cannot donate that.\n\r",ch );
	    return;
	}

	/* the following 2 ifs are to prevent stock piling of stock items -Darwin */
	if ( !IS_OBJ_STAT( obj, ITEM_RANDOM ) )
	{
		act( AT_PLAIN, "You can only donate randoms!", ch, NULL, NULL, TO_CHAR );
		return;
	}

	if (obj->pIndexData->item_type == ITEM_CONTAINER)
	{
		if(!check_container_contents(obj))
		{
			send_to_char("There are item inside this container that cannot be donated.\n\r", ch);
			return;
		}
	}


	/* Smaug random number generator */
	if ( number_range( 1,9 ) >= 5 )
	{
	    act( AT_ACTION, "You generously donate $p!", ch, obj, NULL, TO_CHAR );
	    //~ act( AT_ACTION, "$n donates $p, how generous of $m!", ch, obj, ch, TO_ROOM ); // Added by Drazuk
	    separate_obj(obj);
	    obj_from_char(obj);
	    obj_to_room(obj, get_room_index(ROOM_VNUM_DONATION));
	    /* Bleh, forgot this to stop item duping. Samson 4-4-01 */
		save_char_obj( ch );
	    return;
	}
	else
	{
	    act( AT_ACTION, "You generously donate $p!", ch, obj, NULL, TO_CHAR );
	    //~ act( AT_ACTION, "$n donates $p, how generous of $m!", ch, obj, ch, TO_ROOM );  // Added by Drazuk
	    separate_obj(obj);
	    obj_from_char(obj);
	    obj_to_room(obj, get_room_index(ROOM_VNUM_DONATIONTWO));
	    /* Bleh, forgot this to stop item duping. Samson 4-4-01 */
		save_char_obj( ch );
	    return;
	}
    }
}

void do_fstore( CHAR_DATA *ch, char *argument)
{
    OBJ_DATA *obj;
    
    if(IS_NPC(ch))
        return;

    if ( ch->pcdata->clan )
    {
        if( !argument || argument[0] == '\0' )
        {
            send_to_char( "Store what?\n\r",ch );
            return;
        }

        if ( ch->position == POS_FIGHTING )
        {
            send_to_char( "You cannot store items while fighting!\n\r",ch );
            return;
        }

        if ( ( obj = get_obj_carry (ch, argument) ) == NULL )
        {
            send_to_char("You do not have that!\n\r",ch );
            return;
        }
        else
        {
            if ( !can_drop_obj(ch, obj) && ch->level < LEVEL_IMMORTAL )
            {
                send_to_char( "You cannot store that, it's cursed!\n\r", ch);
                return;
            }

            if ( ( obj->item_type == ITEM_CORPSE_NPC ) || ( obj->item_type == ITEM_CORPSE_PC ) )
            {
                send_to_char( "You cannot store corpses!\n\r", ch);
                return;
            }

            if ( obj->timer > 0 )
            {
                send_to_char( "You cannot store that.\n\r",ch );
                return;
            }

            /* the following 2 ifs are to prevent the stock piling of stock items -Darwin */
            if ( !IS_OBJ_STAT( obj, ITEM_RANDOM ) )
            {
                act( AT_PLAIN, "You can only fstore randoms!", ch, NULL, NULL, TO_CHAR );
                return;
            }

            if (obj->pIndexData->item_type == ITEM_CONTAINER)
            {
                if(!check_container_contents(obj))
                {
                    send_to_char("There are item inside this container that cannot be fstored.\n\r", ch);
                    return;
                }
            }
            act( AT_ACTION, "You store $p, how generous of you!", ch, obj, NULL, TO_CHAR );
            act( AT_ACTION, "$n stores $p, how generous of $m!", ch, obj, ch, TO_ROOM );  // Added by Drazuk
            separate_obj(obj);
            obj_from_char(obj);
            obj_to_room(obj, get_room_index(ch->pcdata->clan->storeroom));
            /* Bleh, forgot this to stop item duping. Samson 4-4-01 */
            save_char_obj( ch );
            return;
	   }
    }
    else
    {
        send_to_char( "You do not belong to a following!\n\r", ch );
    }
}

void do_brandish( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *vch;
    CHAR_DATA *vch_next;
    OBJ_DATA *staff;
    ch_ret retcode;
    int sn;

    if (    !IS_IMMORTAL(ch)
        &&  !IS_MAGE(ch)
        &&  !IS_DRUID(ch)
        &&  !IS_CLERIC(ch)
        &&  !IS_DIABOLIST(ch)
        &&  !IS_ARCHMAGI(ch)
        &&  !IS_BISHOP(ch)    )
    {
        send_to_char( "You aren't magically inclined enough to use this item.\n\r", ch );
        return;
    }	    

    if ( ( staff = get_eq_char( ch, WEAR_HOLD ) ) == NULL )
    {
        send_to_char( "You hold nothing in your hand.\n\r", ch );
        return;
    }

    if ( staff->item_type != ITEM_STAFF )
    {
        send_to_char( "You can brandish only with a staff.\n\r", ch );
        return;
    }

    if ( ( sn = staff->value[STAFF_SN] ) < 0
    ||   sn >= top_sn
    ||   skill_table[sn]->spell_fun == NULL )
    {
        bug( "Do_brandish: bad sn %d.", sn );
        return;
    }

    WAIT_STATE( ch, 1 * PULSE_VIOLENCE );

    if ( staff->value[STAFF_CHARGES] > 0 )
    {
        if ( !oprog_use_trigger( ch, staff, NULL, NULL, NULL ) )
        {
            act( AT_MAGIC, "$n brandishes $p.", ch, staff, NULL, TO_ROOM );
            act( AT_MAGIC, "You brandish $p.",  ch, staff, NULL, TO_CHAR );
        }
        for ( vch = ch->in_room->first_person; vch; vch = vch_next )
        {
            vch_next	= vch->next_in_room;
            if(!IS_NPC(vch) && xIS_SET(vch->act, PLR_WIZINVIS) && vch->pcdata->wizinvis >= LEVEL_IMMORTAL)
                continue;
            else
                switch ( skill_table[sn]->target )
                {
                    default:
                        bug( "Do_brandish: bad target for sn %d.", sn );
                        return;
                    case TAR_IGNORE:
                        if ( vch != ch )
                            continue;
                        break;
                    case TAR_CHAR_OFFENSIVE:
                        if ( IS_NPC(ch) ? IS_NPC(vch) : !IS_NPC(vch) )
                            continue;
                        break;
                    case TAR_CHAR_DEFENSIVE:
                        if ( IS_NPC(ch) ? !IS_NPC(vch) : IS_NPC(vch) )
                            continue;
                        break;
                    case TAR_CHAR_SELF:
                        if ( vch != ch )
                            continue;
                        break;
                }
            retcode = obj_cast_spell( staff->value[3], staff->value[0], ch, vch, NULL );
            if ( retcode == rCHAR_DIED || retcode == rBOTH_DIED )
            {
                bug( "do_brandish: char died", 0 );
                return;
            }  
        }
    }

    if ( --staff->value[STAFF_CHARGES] <= 0 )
    {
        act( AT_MAGIC, "$p blazes bright and vanishes from $n's hands!", ch, staff, NULL, TO_ROOM );
        act( AT_MAGIC, "$p blazes bright and is gone!", ch, staff, NULL, TO_CHAR );
        if ( staff->serial == cur_obj )
            global_objcode = rOBJ_USED;
        extract_obj( staff );
    }

    return;
}



void do_zap( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *wand;
    OBJ_DATA *obj;
    ch_ret retcode;



    if(     !IS_IMMORTAL(ch)
        &&  !IS_MAGE(ch)
        &&  !IS_THIEF(ch)
        &&  !IS_DIABOLIST(ch)
        &&  !IS_CONJURER(ch)
        &&  !IS_JESTER(ch)
        &&  !IS_ARCHMAGI(ch)
        &&  !IS_ROGUE(ch)
        &&  !IS_BISHOP(ch)  )
    {
        send_to_char( "You aren't magically inclined enough to use this item.\n\r", ch );
        return;
    }	

    one_argument( argument, arg );
    if ( arg[0] == '\0' && !ch->fighting )
    {
        send_to_char( "Zap whom or what?\n\r", ch );
        return;
    }

    if ( ( wand = get_eq_char( ch, WEAR_HOLD ) ) == NULL )
    {
        send_to_char( "You hold nothing in your hand.\n\r", ch );
        return;
    }

    if ( wand->item_type != ITEM_WAND )
    {
        send_to_char( "You can zap only with a wand.\n\r", ch );
        return;
    }

    obj = NULL;
    if ( arg[0] == '\0' )
    {
        if ( ch->fighting )
            victim = who_fighting( ch );
        else
        {
            send_to_char( "Zap whom or what?\n\r", ch );
            return;
        }
    }
    else
    {
        if((victim = get_char_room(ch, arg)) == NULL && (obj = get_obj_here(ch, arg)) == NULL)
        {
            send_to_char( "You can't find it.\n\r", ch );
            return;
        }
    }

    WAIT_STATE( ch, 1 * PULSE_VIOLENCE );

    if ( wand->value[WAND_CHARGES] > 0 )
    {
        if ( victim )
        {
            if ( !oprog_use_trigger( ch, wand, victim, NULL, NULL ) )
            {
                act( AT_MAGIC, "$n aims $p at $N.", ch, wand, victim, TO_ROOM );
                act( AT_MAGIC, "You aim $p at $N.", ch, wand, victim, TO_CHAR );
            }
        }
        else
        {
            if ( !oprog_use_trigger( ch, wand, NULL, obj, NULL ) )
            {
                act( AT_MAGIC, "$n aims $p at $P.", ch, wand, obj, TO_ROOM );
                act( AT_MAGIC, "You aim $p at $P.", ch, wand, obj, TO_CHAR );
            }
        }

        retcode = obj_cast_spell( wand->value[WAND_SN], wand->value[WAND_LEVEL], ch, victim, obj );
        if ( retcode == rCHAR_DIED || retcode == rBOTH_DIED )
        {
           bug( "do_zap: char died", 0 );
           return;
        }
    }

    if ( --wand->value[WAND_CHARGES] <= 0 )
    {
        act( AT_MAGIC, "$p explodes into fragments.", ch, wand, NULL, TO_ROOM );
        act( AT_MAGIC, "$p explodes into fragments.", ch, wand, NULL, TO_CHAR );
        if ( wand->serial == cur_obj )
            global_objcode = rOBJ_USED;
        extract_obj( wand );
    }

    return;
}

/*
 * Save items in a clan storage room			-Scryn & Thoric
 */
void save_clan_storeroom( CHAR_DATA *ch, CLAN_DATA *clan )
{
    FILE *fp;
    char filename[256];
    sh_int templvl;
    OBJ_DATA *contents;

    if ( !clan )
    {
	bug( "save_clan_storeroom: Null clan pointer!", 0 );
	return;
    }

    if ( !ch )
    {
	bug ("save_clan_storeroom: Null ch pointer!", 0);
	return;
    }

    sprintf( filename, "%s%s.vault", CLAN_DIR, clan->filename );
    if ( ( fp = fopen( filename, "w" ) ) == NULL )
    {
	bug( "save_clan_storeroom: fopen", 0 );
	perror( filename );
    }
    else
    {
	templvl = ch->level;
	ch->level = LEVEL_HERO;		/* make sure EQ doesn't get lost */
        contents = ch->in_room->last_content;
        if (contents)
	  fwrite_obj(ch, contents, fp, 0, OS_CARRY, FALSE );
	fprintf( fp, "#END\n" );
	ch->level = templvl;
	fclose( fp );
	return;
    }
    return;
}

/* put an item on auction, or see the stats on the current item or bet */
void do_auction (CHAR_DATA *ch, char *argument)
{
    OBJ_DATA *obj;
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char arg3[MAX_INPUT_LENGTH];
    char buf[MAX_STRING_LENGTH];

    argument = one_argument (argument, arg1);
    argument = one_argument (argument, arg2);
    argument = one_argument (argument, arg3);

    set_char_color( AT_LBLUE, ch );

    if (IS_NPC(ch)) /* NPC can be extracted at any time and thus can't auction! */
	return;

    if ( ch->level < 2 )
    {
	send_to_char( "You must be at least level two to use the auction...\n\r", ch );
	return;
    }

    if (arg1[0] == '\0')
    {
        if (auction->item != NULL)
        {
	    AFFECT_DATA *paf;	    
  	    obj = auction->item;

            /* show item data here */
            if (auction->bet > 0)
                sprintf (buf, "\n\rCurrent bid on this item is %s gold.\n\r", num_punct( auction->bet ) );
            else
                sprintf (buf, "\n\rNo bids on this item have been received.\n\r");
	    set_char_color ( AT_BLUE, ch );
            send_to_char (buf,ch);
/*          spell_identify (0, LEVEL_HERO - 1, ch, auction->item); */

	    sprintf( buf,
		"Object '%s' is %s, special properties: %s\n\rIts weight is %d, value is %d.\n\r",
		obj->name,
		aoran( item_type_name( obj ) ),
		extra_bit_name( &obj->extra_flags ),
/*		magic_bit_name( obj->magic_flags ), -- currently unused */
		obj->weight,
		obj->cost );
	    set_char_color( AT_LBLUE, ch );
	    send_to_char( buf, ch );
	    if ( (obj->item_type != ITEM_LIGHT && obj->item_type != ITEM_ARTLIGHT) && obj->wear_flags-1 > 0 )
	      ch_printf( ch, "Item's wear location: %s\n\r",
		flag_string(obj->wear_flags -1, w_flags ) );

	    set_char_color( AT_BLUE, ch );

	    switch ( obj->item_type )
	    {
		case ITEM_CONTAINER:
		case ITEM_KEYRING:
		case ITEM_QUIVER:
                  ch_printf( ch, "%s appears to %s.\n\r", capitalize(obj->short_descr),
   	                obj->value[CONTAINER_CAPACITY] < 76  ? "have a small capacity"           :
	                obj->value[CONTAINER_CAPACITY] < 150 ? "have a small to medium capacity" :
			obj->value[CONTAINER_CAPACITY] < 300 ? "have a medium capacity"          :
	                obj->value[CONTAINER_CAPACITY] < 500 ? "have a medium to large capacity" :
	                obj->value[CONTAINER_CAPACITY] < 751 ? "have a large capacity"           :
	                                      "have a giant capacity" );
	          break;

		case ITEM_PILL:
		case ITEM_SCROLL:
		case ITEM_POTION:
		  sprintf( buf, "Level %d spells of:", obj->value[POTION_LEVEL] );
		  send_to_char( buf, ch );
        
		  if ( obj->value[POTION_SN1] >= 0 && obj->value[POTION_SN1] < top_sn )
		  {
		     send_to_char( " '", ch );
		     send_to_char( skill_table[obj->value[POTION_SN1]]->name, ch );
		     send_to_char( "'", ch );
		  }
    
		  if ( obj->value[POTION_SN2] >= 0 && obj->value[POTION_SN2] < top_sn )
		  {
		     send_to_char( " '", ch );
		     send_to_char( skill_table[obj->value[POTION_SN2]]->name, ch );
		     send_to_char( "'", ch );
		  }
    
		  if ( obj->value[POTION_SN3] >= 0 && obj->value[POTION_SN3] < top_sn )
		  {
		     send_to_char( " '", ch );
		     send_to_char( skill_table[obj->value[POTION_SN3]]->name, ch );
		     send_to_char( "'", ch );
		  }

		  send_to_char( ".\n\r", ch );
		  break;
    
		case ITEM_WAND:
		case ITEM_STAFF:
		  sprintf( buf, "Has %d(%d) charges of level %d",
			obj->value[STAFF_MAX_CHARGES], obj->value[STAFF_CHARGES], obj->value[STAFF_LEVEL] );
		  send_to_char( buf, ch );
         
		  if ( obj->value[STAFF_SN] >= 0 && obj->value[STAFF_SN] < top_sn )
		  {
		     send_to_char( " '", ch );
		     send_to_char( skill_table[obj->value[3]]->name, ch );
		     send_to_char( "'", ch );
		  }

		  send_to_char( ".\n\r", ch );
		  break;

                case ITEM_COMP:
                   ch_printf( ch, "Has %d uses", obj->value[COMPONENT_USES]);
                   send_to_char( ".\n\r", ch );
                   break;

		case ITEM_WEAPON:
		case ITEM_ARTWEAPON:
		  sprintf( buf, "Damage is %d to %d (average %d).%s\n\r",
			obj->value[WEAPON_NUMDICE], obj->value[WEAPON_SIZEDICE],
			( obj->value[WEAPON_NUMDICE] + obj->value[WEAPON_SIZEDICE] ) / 2,
			IS_OBJ_STAT( obj, ITEM_POISONED) ?
			"\n\rThis weapon is poisoned." : "" );
		  send_to_char( buf, ch );
		  break;

		case ITEM_ARMOR:
		case ITEM_ARTARMOR:
		  sprintf( buf, "Armor class is %d.\n\r", obj->value[ARMOR_CURRENT_AC] );
		  send_to_char( buf, ch );
		  break;
	    }
         
	    for ( paf = obj->pIndexData->first_affect; paf; paf = paf->next )
		showaffect( ch, paf );
        
	    for ( paf = obj->first_affect; paf; paf = paf->next )
		showaffect( ch, paf );
	    if ( ( obj->item_type == ITEM_CONTAINER || obj->item_type == ITEM_KEYRING
	    ||     obj->item_type == ITEM_QUIVER)   && obj->first_content )
	    {
		set_char_color( AT_OBJECT, ch );
		send_to_char( "Contents:\n\r", ch );
		show_list_to_char( obj->first_content, ch, TRUE, FALSE );
	    }

	    if (IS_IMMORTAL(ch))
	    {
		sprintf(buf, "Seller: %s.  Bidder: %s.  Round: %d.\n\r",
                        auction->seller->name, auction->buyer->name,
                        (auction->going + 1));
		send_to_char(buf, ch);
		sprintf(buf, "Time left in round: %d.\n\r", auction->pulse);
		send_to_char(buf, ch);
	    }
            return;
	}
	else
	{
	    set_char_color ( AT_LBLUE, ch );
	    send_to_char ( "\n\rThere is nothing being auctioned right now.  What would you like to auction?\n\r", ch );
	    return;
	}
    }

    if ( IS_IMMORTAL(ch) && !str_cmp(arg1,"stop"))
    {
       if (auction->item == NULL)
       {
           send_to_char ("There is no auction to stop.\n\r",ch);
           return;
       }
       else /* stop the auction */
       {
	   set_char_color ( AT_LBLUE, ch );
           sprintf (buf,"Sale of %s has been stopped by an Immortal.",
                        auction->item->short_descr);
           talk_auction (buf);
           obj_to_char (auction->item, auction->seller);
	   if ( IS_SET( sysdata.save_flags, SV_AUCTION ) )
	       save_char_obj(auction->seller);
           auction->item = NULL;
           if (auction->buyer != NULL && auction->buyer != auction->seller) /* return money to the buyer */
           {
               auction->buyer->gold += auction->bet;
               send_to_char ("Your money has been returned.\n\r",auction->buyer);
           }
           return;
       }
    }
    if (!str_cmp(arg1,"bid") )
    {
        if (auction->item != NULL)
        {
            int newbet;

/*	    if ( ch->level < auction->item->level )
	    {
		send_to_char("This object's level is too high for your use.\n\r", ch );
		return;
	    }
*/
	    if ( ch == auction->seller)
	    {
		send_to_char("You can't bid on your own item!\n\r", ch);
		return;
	    }

            /* make - perhaps - a bet now */
            if (arg2[0] == '\0')
            {
                send_to_char ("Bid how much?\n\r",ch);
                return;
            }

            newbet = parsebet (auction->bet, arg2);
/*	    ch_printf( ch, "Bid: %d\n\r",newbet);	*/

	    if (newbet < auction->starting)
	    {
		send_to_char("You must place a bid that is higher than the starting bet.\n\r", ch);
		return;
	    }

	    /* to avoid slow auction, use a bigger amount than 100 if the bet
 	       is higher up - changed to 10000 for our high economy
            */

            if (newbet < (auction->bet + 100))
            {
                send_to_char ("You must at least bid 100 coins over the current bid.\n\r",ch);
                return;
            }

            if (newbet > ch->gold)
            {
                send_to_char ("You don't have that much money!\n\r",ch);
                return;
            }

	    if (newbet > 2000000000)
	    {
		send_to_char("You can't bid over 2 billion coins.\n\r", ch);
		return;
	    }

	    /* Is it the item they really want to bid on? --Shaddai */
	    if ( arg3[0] != '\0' &&
	 	 !nifty_is_name( arg3, auction->item->name ) )
	    {
	     send_to_char("That item is not being auctioned right now.\n\r",ch);
	     return;
	    }
            /* the actual bet is OK! */

            /* return the gold to the last buyer, if one exists */
            if (auction->buyer != NULL && auction->buyer != auction->seller)
                auction->buyer->gold += auction->bet;

            ch->gold -= newbet; /* substract the gold - important :) */
	    if ( IS_SET( sysdata.save_flags, SV_AUCTION ) )
		save_char_obj(ch);
            auction->buyer = ch;
            auction->bet   = newbet;
            auction->going = 0;
            auction->pulse = PULSE_AUCTION; /* start the auction over again */

            sprintf (buf,"A bid of %s gold has been received on %s.\n\r",num_punct(newbet),auction->item->short_descr);
            talk_auction (buf);
            return;


        }
        else
        {
            send_to_char ("There isn't anything being auctioned right now.\n\r",ch);
            return;
        }
    }
/* finally... */
    if ( ms_find_obj(ch) )
	return;

    obj = get_obj_carry (ch, arg1); /* does char have the item ? */

    if (obj == NULL)
    {
        send_to_char ("You aren't carrying that.\n\r",ch);
        return;
    }

    if (obj->timer > 0)
    {
	send_to_char ("You can't auction objects that are decaying.\n\r", ch);
	return;
    }

    /* prevent repeat auction items */	
/*
    for(i = 0; i < AUCTION_MEM && auction->history[i]; i++)
    {
    	if(auction->history[i] == obj->pIndexData)
    	{
	    send_to_char("Such an item has been auctioned "
	    	"recently, try again later.\n\r", ch);
	    return;
    	}
    }
*/    

    if (arg2[0] == '\0')
    {
      auction->starting = 0;
      strcpy(arg2, "0");
    }


    if ( !is_number(arg2) )
    {
	send_to_char("You must input a number at which to start the auction.\n\r", ch);
	return;
    }

    if ( atoi(arg2) < 0 )
    {
	send_to_char("You can't auction something for less than 0 gold!\n\r", ch);
 	return;
    }

    if ( IS_OBJ_STAT( obj, ITEM_NODROP ) )
    {
	send_to_char( "You can't seem to let go of this item!\n\r", ch);
	return;
    }

    if ( xIS_SET(obj->extra_flags, ITEM_GOLEM) )
    {
	send_to_char( "You can't auction Golem items.\n\r", ch);
	return;
    }

    if ( xIS_SET(obj->extra_flags, ITEM_CONJURER) ) 
    { 
        send_to_char( "You can't auction Conjurer items.\n\r", ch);
        return;
    }

	if ( xIS_SET(obj->extra_flags, ITEM_INVENTORY) )
	{
		send_to_char( "You can't auction inventory items.\n\r", ch);
		return;
	}

    if (auction->item == NULL)
    switch (obj->item_type)
    {

    default:
        act (AT_TELL, "You cannot auction $Ts.",ch, NULL, item_type_name (obj), TO_CHAR);
        return;

/* insert any more item types here... items with a timer MAY NOT BE 
   AUCTIONED! 
*/
    case ITEM_LIGHT:
    case ITEM_ARTLIGHT:
    case ITEM_WORN:
    case ITEM_ARTWORN:
    case ITEM_TREASURE:    
    case ITEM_ARTTREASURE:
    case ITEM_POTION:
    case ITEM_CONTAINER:
    case ITEM_KEYRING:
    case ITEM_DRINK_CON:
    case ITEM_FOOD:
    case ITEM_BOAT:
    case ITEM_PILL:
    case ITEM_PIPE:
    case ITEM_HERB_CON:
    case ITEM_INCENSE:
    case ITEM_FIRE:
    case ITEM_RUNEPOUCH:
    case ITEM_MAP:
    case ITEM_BOOK:
    case ITEM_RUNE:
    case ITEM_MATCH:
    case ITEM_HERB:
    case ITEM_WEAPON:
    case ITEM_ARTWEAPON:
    case ITEM_ARMOR:
    case ITEM_ARTARMOR:
    case ITEM_STAFF:
    case ITEM_WAND:
    case ITEM_SCROLL:
	separate_obj(obj);
	obj_from_char (obj);
	if ( IS_SET( sysdata.save_flags, SV_AUCTION ) )
	    save_char_obj(ch);
	auction->item = obj;
	auction->bet = 0;
	auction->buyer = ch;
	auction->seller = ch;
	auction->pulse = PULSE_AUCTION;
	auction->going = 0;
	auction->starting = atoi(arg2);
	if(auction->item->owner)
		auction->starting += 20000;

    	/* add the new item to the history */
    	if(AUCTION_MEM > 0)
        {
     		memmove((char *) auction->history+sizeof(OBJ_INDEX_DATA *),
                      	auction->history, (AUCTION_MEM - 1)*sizeof(OBJ_INDEX_DATA *));
                auction->history[0] = obj->pIndexData;
	}

	/* reset the history timer */
	auction->hist_timer = 0;
                                                        

	if (auction->starting > 0)
	  auction->bet = auction->starting;

	sprintf (buf, "A new item is being auctioned: %s at %d gold.", obj->short_descr, auction->starting);
	talk_auction (buf);

	return;

    } /* switch */
    else
    {
        act (AT_TELL, "Try again later - $p is being auctioned right now!",ch,auction->item,NULL,TO_CHAR);
	if ( !IS_IMMORTAL(ch) )
          WAIT_STATE( ch, PULSE_VIOLENCE );
        return;
    }
}



/* Make objects in rooms that are nofloor fall - Scryn 1/23/96 */
void obj_fall( OBJ_DATA *obj, bool through )
{
    EXIT_DATA *pexit;
    ROOM_INDEX_DATA *to_room;
    static int fall_count;
    char buf[MAX_STRING_LENGTH];
    static bool is_falling; /* Stop loops from the call to obj_to_room()  -- Altrag */
	
    if ( !obj->in_room || is_falling )
    	return;

    if (fall_count > 30)
    {
    	bug( "object falling in loop more than 30 times", 0 );
	extract_obj(obj);
    	fall_count = 0;
	return;
     }

     if ( IS_SET( obj->in_room->room_flags, ROOM_NOFLOOR )
     &&   CAN_GO( obj, DIR_DOWN )
     &&   !IS_OBJ_STAT( obj, ITEM_MAGIC ) )
     {

	pexit = get_exit( obj->in_room, DIR_DOWN );
    	to_room = pexit->to_room;

    	if (through)
	  fall_count++;
	else
	  fall_count = 0;

	if (obj->in_room == to_room)
	{
	    sprintf(buf, "Object falling into same room, room %d",
		to_room->vnum);
	    bug( buf, 0 );
	    extract_obj( obj );
            return;
	}

	if (obj->in_room->first_person)
	{
	  	act( AT_PLAIN, "$p falls far below...",
			obj->in_room->first_person, obj, NULL, TO_ROOM );
		act( AT_PLAIN, "$p falls far below...",
			obj->in_room->first_person, obj, NULL, TO_CHAR );
	}
	obj_from_room( obj );
	is_falling = TRUE;
	obj = obj_to_room( obj, to_room );
	is_falling = FALSE;

	if (obj->in_room->first_person)
	{
	  	act( AT_PLAIN, "$p falls from above...", 
			obj->in_room->first_person, obj, NULL, TO_ROOM );
		act( AT_PLAIN, "$p falls from above...",
			obj->in_room->first_person, obj, NULL, TO_CHAR );
	}

 	if (!IS_SET( obj->in_room->room_flags, ROOM_NOFLOOR ) && through )
	{
/*		int dam = (int)9.81*sqrt(fall_count*2/9.81)*obj->weight/2;
*/		int dam = fall_count*obj->weight/2;
		/* Damage players */
		if ( obj->in_room->first_person && number_percent() > 15 )
		{
			CHAR_DATA *rch;
			CHAR_DATA *vch = NULL;
			int chcnt = 0;
			
			for ( rch = obj->in_room->first_person; rch;
				rch = rch->next_in_room, chcnt++ )
				if ( number_range( 0, chcnt ) == 0 )
					vch = rch;
			act( AT_WHITE, "$p falls on $n!", vch, obj, NULL, TO_ROOM );
			act( AT_WHITE, "$p falls on you!", vch, obj, NULL, TO_CHAR );

   		        damage( vch, vch, dam*vch->level, TYPE_UNDEFINED );
		}
    	/* Damage objects */
	    switch( obj->item_type )
     	    {
	     	case ITEM_WEAPON:
		case ITEM_ARTWEAPON:
		case ITEM_ARMOR:
		case ITEM_ARTARMOR:
		    if ( (obj->value[0] - dam) <= 0 )
 		    {
   			if (obj->in_room->first_person)
			{
			act( AT_PLAIN, "$p is destroyed by the fall!", 
				obj->in_room->first_person, obj, NULL, TO_ROOM );
			act( AT_PLAIN, "$p is destroyed by the fall!",
				obj->in_room->first_person, obj, NULL, TO_CHAR );
			}
			make_scraps(obj);
	 	    }
		    else
	           	obj->value[0] -= dam;
		    break;
		default:
		    if ( (dam*15) > get_obj_resistance(obj) )
		    {
	              if (obj->in_room->first_person)
		      {
 			    act( AT_PLAIN, "$p is destroyed by the fall!",
			    	obj->in_room->first_person, obj, NULL, TO_ROOM );
			    act( AT_PLAIN, "$p is destroyed by the fall!",
		    		obj->in_room->first_person, obj, NULL, TO_CHAR );
		      }
		      make_scraps(obj);
		    }
		    break;
	    }
     	}
     	obj_fall( obj, TRUE );
    }
    return;
}

/* Scryn, by request of Darkur, 12/04/98 */
/* Reworked recursive_note_find to fix crash bug when the note was left 
 * blank.  7/6/98 -- Shaddai
 */

void do_findnote( CHAR_DATA *ch, char *argument )
{
  OBJ_DATA* obj;

  if ( IS_NPC(ch) )  
  {
    send_to_char( "Huh?\n\r", ch );
    return;
  }

  if( argument[0] == '\0' )
  {
    send_to_char( "You must specify at least one keyword.\n\r", ch);
    return;
  }

  obj = recursive_note_find(ch->first_carrying, argument);
   
  if(obj)
  {
    if(obj->in_obj)
    {  
      obj_from_obj(obj);
      obj = obj_to_char(obj, ch);
    }
    wear_obj(ch, obj, TRUE, -1);
  }
  else
    send_to_char("Note not found.\n\r", ch);
  return;
}

OBJ_DATA* recursive_note_find( OBJ_DATA *obj, char *argument )
{
  OBJ_DATA* returned_obj;
  bool match = TRUE;
  char* argcopy;
  char* subject;

  char arg[MAX_INPUT_LENGTH];
  char subj[MAX_STRING_LENGTH];

  if(!obj)
    return NULL;

  switch(obj->item_type)
  {
    case ITEM_PAPER:

      if ((subject = get_extra_descr( "_subject_", obj->first_extradesc))==NULL)
        break;
      sprintf(subj, "%s", strlower(subject) );
      subject = strlower(subj);

      argcopy = argument;

      while(match)
      {
	argcopy = one_argument(argcopy, arg);

        if(arg[0] == '\0')
          break;

	if(!strstr(subject, arg)) 
          match = FALSE;
      }


      if(match)
        return obj;
      break;

    case ITEM_CONTAINER:
    case ITEM_CORPSE_NPC:
    case ITEM_CORPSE_PC:
      if(obj->first_content)
      {
      	returned_obj = recursive_note_find(obj->first_content, argument); 
        if(returned_obj)
          return returned_obj;  
      }
      break;

    default:
      break;
  }

  return recursive_note_find(obj->next_content, argument);
}

void do_rolldie(CHAR_DATA *ch, char *argument)
{
  OBJ_DATA* die;

  char output_string[MAX_STRING_LENGTH];
  char roll_string[MAX_STRING_LENGTH];
  char total_string[MAX_STRING_LENGTH];

  char* verb;

/*  char* face_string = NULL;
  char** face_table = NULL;*/
  int rollsum = 0;
  int roll_count = 0;
 
  int numsides;
  int numrolls;

  bool* face_seen_table = NULL;

  if ( IS_NPC(ch) )  
  {
    send_to_char( "Huh?\n\r", ch );
    return;
  }

  if ( ( die = get_eq_char(ch, WEAR_HOLD) ) == NULL
  ||     die->item_type != ITEM_CHANCE )
  {
    ch_printf(ch, "You must be holding an item of chance!\n\r");
    return;
  }

  numrolls = (is_number(argument)) ? atoi(argument) : 1;
  verb = get_chance_verb(die);

  if(numrolls > 100)
  {
    ch_printf(ch, "You can't %s more than 100 times!\n\r", verb);
    return;
  }
  
  numsides = die->value[0];

  if(numsides <= 1)
  {
    ch_printf(ch, "There is no element of chance in this game!\n\r");
    return;
  }

  if(die->value[3] == 1)
  {
    if(numrolls > numsides)
    {
      ch_printf(ch, "Nice try, but you can only %s %d times.\n\r", verb, numsides);
      return;
    }
    face_seen_table = calloc(numsides, sizeof(bool));
    if(!face_seen_table)
    {
      bug("do_rolldie: cannot allocate memory for face_seen_table array, terminating.\n\r",0);
      return;
    }
  }

  sprintf(roll_string, " ");

  while(roll_count++ < numrolls)
  {
    int current_roll;
    char current_roll_string[MAX_STRING_LENGTH];

    do
    {  
      current_roll = number_range(1, numsides);
    } while(die->value[3] == 1 && face_seen_table[current_roll - 1] == TRUE);

    if(die->value[3] == 1)
      face_seen_table[current_roll - 1] = TRUE;    

    rollsum += current_roll;

    if(roll_count > 1)
       strcat(roll_string, ", ");
    if(numrolls > 1 && roll_count == numrolls)
         strcat(roll_string, "and ");

    if(die->value[1] == 1)
    {
      char* face_name = get_ed_number(die, current_roll);
      if(face_name)
      {
        char* face_name_copy = strdup(face_name); /* Since I want to tokenize without modifying the original string */
        sprintf(current_roll_string, "%s", strtok(face_name_copy, "\n"));
        free(face_name_copy);
      }
      else
        sprintf(current_roll_string, "%d",  current_roll);
    }
    else
      sprintf(current_roll_string, "%d",  current_roll);
    strcat(roll_string, current_roll_string);
  }

  if(numrolls > 1 && die->value[2] == 1)
  {
    sprintf(total_string, ", for a total of %d", rollsum);
    strcat(roll_string, total_string);
  }

  strcat(roll_string, ".\n\r");

  sprintf(output_string, "You %s%s", verb, roll_string);
  act( AT_GREEN, output_string, ch, NULL, NULL, TO_CHAR);

  sprintf(output_string, "$n %s%s", verb, roll_string);
  act( AT_GREEN, output_string, ch, NULL, NULL, TO_ROOM);

  if(face_seen_table)
    free(face_seen_table);
  return;
}

char* get_ed_number(OBJ_DATA* obj, int number)
{
  EXTRA_DESCR_DATA* ed;
  int count;

  for(ed = obj->first_extradesc, count = 1; ed; ed = ed->next, count++)
  {
    if(count == number)
      return ed->description;
  }

  return NULL;
}

char* get_chance_verb(OBJ_DATA* obj)
{
  return (obj->action_desc[0] != '\0') ? obj->action_desc : "roll$q";  
}

/*dice chance deal throw*/

/* Added by Drazuk -- RANDOM ITEMS! -- from Slash's MERC Site RANCODE */
/*
    This one is real nifty.  The idea comes from a Mr. Peckham whose
    address I have lost, this is my own reimplementation of it, as I
    never got to see his code.

    To get this to work you have to either modify your area file format
    to have resets for random objects and your DB.C loader.  I'll leave
    that as an exercise for you.

    If you want to see how this works without all the fuss, put something
    like this in your create_mobile() in DB.C.  This gives any mobile a
    random chance to have something special.

    if (number_percent() <= 10)
       wield_random_magic( mob );
    else if (number_percent() <= 10)
       wield_random_armor( mob );
*/
/* commented out. relevant code ported to Lua so this macro is no longer needed
   -Darwin 2008-03-17
#define nelems(a) (sizeof (a)/sizeof (a)[0])
*/

// Calculate a meaningful modifier and amount
void random_apply( OBJ_DATA *obj, CHAR_DATA *mob )
{
    AFFECT_DATA *paf;   
	int value;

    separate_obj( obj );
    CREATE( paf, AFFECT_DATA, 1 );
    paf->type	     = -1;
    paf->duration     = -1;

    call_va(L_mud, "random_get_loc_mod", "i>ii", number_range(1,4), &paf->location, &value);
	xCLEAR_BITS( paf->bitvector );
	if(paf->location == APPLY_EXT_AFFECT)
	{
		paf->modifier = value;
		xSET_BIT(paf->bitvector, paf->modifier);
	}
	else
		paf->modifier = value;

	LINK( paf, obj->first_affect, obj->last_affect, next, prev );

    xSET_BIT(obj->extra_flags, ITEM_MAGIC);

    if (number_percent() <= 10)
        xSET_BIT(obj->extra_flags, ITEM_GLOW);
    if (number_percent() <= 10)
        xSET_BIT(obj->extra_flags, ITEM_HUM);
	xSET_BIT(obj->extra_flags, ITEM_RANDOM); // Set random flag -Darwin

    // Is item cursed?
    if (number_range(1,100) < 3)
    {
        xSET_BIT(obj->extra_flags, ITEM_NODROP);
        if (number_range(1,100) < 3)
            xSET_BIT(obj->extra_flags, ITEM_NOREMOVE);
    }
  
    if (number_range(1, 100) < 5
        && ( !xIS_SET(obj->extra_flags, ITEM_ANTI_EVIL)
        &&   !xIS_SET(obj->extra_flags, ITEM_ANTI_GOOD)
        &&   !xIS_SET(obj->extra_flags, ITEM_ANTI_NEUTRAL) ) )
    {
        switch(number_range(1,3))
        {
            case 1:
                xSET_BIT(obj->extra_flags, ITEM_ANTI_EVIL);
                break;
            case 2:
                xSET_BIT(obj->extra_flags, ITEM_ANTI_GOOD);
                break;
            case 3:
                xSET_BIT(obj->extra_flags, ITEM_ANTI_NEUTRAL);
                break;
            default:
                break;
        }
    }

}

void random_artifact_apply( OBJ_DATA *obj, CHAR_DATA *mob )
{
	AFFECT_DATA *paf;   
	int value;

	separate_obj( obj );
	CREATE( paf, AFFECT_DATA, 1 );
	paf->type	     = -1;
	paf->duration     = -1;
	call_va(L_mud, "random_get_art_loc_mod", "i>ii", number_range(1,4), &paf->location, &value);
	xCLEAR_BITS( paf->bitvector );
	if(paf->location == APPLY_EXT_AFFECT)
	{
		paf->modifier = value;
		xSET_BIT(paf->bitvector, paf->modifier);
	}
	else
		paf->modifier = value;

	LINK( paf, obj->first_affect, obj->last_affect, next, prev );

	xSET_BIT(obj->extra_flags, ITEM_MAGIC);
	xSET_BIT(obj->extra_flags, ITEM_NOLOCATE);
	xSET_BIT(obj->extra_flags, ITEM_BLESS);
	xSET_BIT(obj->extra_flags, ITEM_RANDOM); // Set random flag -Darwin

   if (number_range(1, 100) < 3
    && ( !xIS_SET(obj->extra_flags, ITEM_ANTI_EVIL)
    && !xIS_SET(obj->extra_flags, ITEM_ANTI_GOOD)
    && !xIS_SET(obj->extra_flags, ITEM_ANTI_NEUTRAL) ) )
   { 
        switch(number_range(1,3))
        {
            case 1:
                xSET_BIT(obj->extra_flags, ITEM_ANTI_EVIL);
                break;
            case 2:
                xSET_BIT(obj->extra_flags, ITEM_ANTI_GOOD);
                break;
            case 3:
                xSET_BIT(obj->extra_flags, ITEM_ANTI_NEUTRAL);
                break;
            default:
                break;
        }
   }
 
}


// Wands/Staves/Potions/Pills and bags
void wield_random_magic( CHAR_DATA *mob )
{
    OBJ_INDEX_DATA *pObjIndex = get_obj_index( number_range(21140, 21199) );
    OBJ_DATA *obj = create_object( pObjIndex, number_fuzzy( mob->level ) );
    char *buf;

    obj->value[0] = -1;
    obj->value[1] = -1;
    obj->value[2] = -1;
    obj->value[3] = -1;
    obj->value[4] = -1;
    obj->value[5] = -1;

    switch (pObjIndex->vnum)
    {
		case 21140: case 21150: case 21151: case 21152: case 21153: case 21154:     // scroll
		case 21155: case 21156: case 21157: case 21158: case 21159:                 // scroll
            call_va(L_mud, "generate_random_scroll", "s>iiiiis", obj->name, &obj->value[0], &obj->cost, 
                &obj->value[1], &obj->value[2], &obj->value[3], &buf);
            STRFREE( obj->name );
            obj->name = STRALLOC( buf );

            xSET_BIT(obj->extra_flags, ITEM_NOLOCATE);
			break;
		case 21148: case 21141: case 21170: case 21171: case 21172: case 21173:     // potion 
		case 21174: case 21175: case 21176: case 21177: case 21178: case 21179:     // potion 
		case 21180: case 21181: case 21182: case 21183: case 21184:                 // potion 
		case 21185: case 21186: case 21187: case 21188: case 21189: case 21190:     // pill
		case 21191: case 21192: case 21193: case 21194: case 21144: case 21145:     // pill
		case 21149:                                                                 // pill
            call_va(L_mud, "generate_random_potion", "s>iiiiis", obj->name, &obj->value[0], &obj->cost, 
                &obj->value[1], &obj->value[2], &obj->value[3], &buf);
            STRFREE( obj->name );
            obj->name = STRALLOC( buf );

			xSET_BIT(obj->extra_flags, ITEM_NOLOCATE);
			break;
		case 21142: // salve
            call_va(L_mud, "generate_random_salve", "s>iiiiis", obj->name, &obj->value[0], &obj->cost, 
                &obj->value[1], &obj->value[4], &obj->value[5], &buf);
            obj->value[2] = obj->value[1];
            STRFREE( obj->name );
            obj->name = STRALLOC( buf );
			xSET_BIT(obj->extra_flags, ITEM_NOLOCATE);
			break;
		case 21143: case 21147: case 21160: case 21161:     // wand
		case 21162: case 21163: case 21164:                 // wand
            call_va(L_mud, "generate_random_wand", "s>iiiis", obj->name, &obj->value[0], &obj->cost, 
                &obj->value[1], &obj->value[3], &buf);
            obj->value[2] = obj->value[1];
            STRFREE( obj->name );
            obj->name = STRALLOC( buf );
			xSET_BIT(obj->extra_flags, ITEM_NOLOCATE);
			break;
		case 21146: case 21165: case 21166:     // staff
		case 21167: case 21168: case 21169:     // staff
            call_va(L_mud, "generate_random_staff", "s>iiiis", obj->name, &obj->value[0], &obj->cost, 
                &obj->value[1], &obj->value[3], &buf);
            obj->value[2] = obj->value[1];
            STRFREE( obj->name );
            obj->name = STRALLOC( buf );
			xSET_BIT(obj->extra_flags, ITEM_NOLOCATE);
			break;
		case 21195:  // bag
			obj->value[0] = number_range(25, 60);
			obj->value[1] = number_range(0, 1);
			obj->value[2] = -1;
			break;
		case 21196:  // backpack
			obj->value[0] = number_range(35, 85);
			obj->value[1] = number_range(0, 1);
			obj->value[2] = -1;
			break;
		case 21197:  // pouch
			obj->value[0] = number_range(20, 40);
			obj->value[1] = number_range(0, 1);
			obj->value[2] = -1;
			break;
		case 21198:  // bag
			obj->value[0] = number_range(25, 60);
			obj->value[1] = number_range(0, 1);
			obj->value[2] = -1;
			break;
		case 21199:  // hole
			obj->value[0] = number_range(100, 200);
			obj->value[1] = number_range(0, 1);
			obj->value[2] = -1;
			break;
	}
	xSET_BIT(obj->extra_flags, ITEM_RANDOM); // Set random flag -Darwin

    if ( obj->item_type  == ITEM_CONTAINER )
    {
        if (number_range(1,100) < 3) 
        {   
            xSET_BIT(obj->extra_flags, ITEM_NODROP);
            if (number_range(1,100) < 3)
                xSET_BIT(obj->extra_flags, ITEM_NOREMOVE);
        } 
        if (number_range(1, 100) < 3
            && !xIS_SET(obj->extra_flags, ITEM_ANTI_EVIL)
            && !xIS_SET(obj->extra_flags, ITEM_ANTI_GOOD) 
            && !xIS_SET(obj->extra_flags, ITEM_ANTI_NEUTRAL) )
            {
                switch(number_range(1,3))
                {
                case 1:
                    xSET_BIT(obj->extra_flags, ITEM_ANTI_EVIL);
                    break;
                case 2:
                    xSET_BIT(obj->extra_flags, ITEM_ANTI_GOOD);
                    break;
                case 3:
                    xSET_BIT(obj->extra_flags, ITEM_ANTI_NEUTRAL);
                    break;
                }
            } 
    }
    obj_to_char( obj, mob );
}

// Special spell components for Conjurer
void wield_random_component( CHAR_DATA *mob )
{
    // Get template obj from DRAZVILLE.ARE
    OBJ_INDEX_DATA *pObjIndex = get_obj_index( number_range(21450, 21464) );
    OBJ_DATA *obj = create_object( pObjIndex, number_fuzzy( mob->level ) );

    switch (pObjIndex->vnum)
    {
        case 21450:   // pine sap
        case 21451:   // iron shavings
        case 21452:   // diamond dust
        case 21453:   // gold flakes
        case 21454:   // ruby powder
        case 21455:   // steel cube
        case 21456:   // silver orb
        case 21457:   // oak leaves
            obj->value[0] = number_range( 1, 5 ); 
            break;
        case 21458:   // rose essence
        case 21459:   // fish scales
        case 21460:   // emerald shards
        case 21461:   // mithril cylinder
            obj->value[0] = number_range( 1, 4 ); 
            break;
        case 21462:   // dragon tooth
        case 21463:   // demon horn
        case 21464:   // angel feather
            obj->value[0] = number_range( 1, 3 );
            break;
    }

    xSET_BIT(obj->extra_flags, ITEM_RANDOM); // Set random flag -Darwin
    obj_to_char( obj, mob );
}

// Special spell components for Relics
void wield_random_relic( CHAR_DATA *mob )
{ 
    // Get template obj from UNIVERSE.ARE
    OBJ_INDEX_DATA *pObjIndex = get_obj_index( number_range(29300, 29347) );
    OBJ_DATA *obj = create_object( pObjIndex, number_fuzzy( mob->level ) );
        
/*
    switch (obj->pObjIndex->vnum) // left this in here because it lables all the parts
    { 
        case 29300: // axe spike 
        case 29301: // axe blade 
        case 29302:	// axe haft
        case 29303:	// axe handle
        case 29304:	// axe wrapping
        case 29305:	// axe ruby
        case 29306:	// mace handle
        case 29307:	// mace shaft
        case 29308:	// mace wrapping
        case 29309:	// mace sapphire
        case 29310:	// mace weight
        case 29311:	// mace dragon head figurine
        case 29312:	// sword foible
        case 29313: // sword prime
        case 29314:	// sword grip
        case 29315:	// sword cross
        case 29316:	// sword setting
        case 29317:	// sword diamond
        case 29318:	// dagger tip
        case 29319:	// dagger tang
        case 29320:	// dagger guard
        case 29321:	// dagger grip
        case 29322:	// dagger setting
        case 29323:	// dagger emerald
        case 29324:	// flail weight
        case 29325:	// flail chain
        case 29326:	// flail shaft
        case 29327:	// flail haft
        case 29328:	// flail wrapping
        case 29329: // flail pearl
        case 29330:	// polearm blade
        case 29331:	// polearm spike
        case 29332:	// polearm langet
        case 29333:	// polearm shaft
        case 29334:	// polearm wrapping
        case 29335:	// polearm moonstone
        case 29336:	// crossbow arms
        case 29337:	// crossbow string
        case 29338:	// crossbow bowarm
        case 29339:	// crossbow stirrup
        case 29340:	// crossbow handle
        case 29341:	// crossbow silver star
        case 29342:	// claw blade 1
        case 29343:	// claw blade 2
        case 29344:	// claw mithril thread
        case 29345:	// claw plating
        case 29346: // claw wrapping
        case 29347:	// claw jade
            break;
    }; 
*/
	xSET_BIT(obj->extra_flags, ITEM_RANDOM); // Set random flag -Darwin
    obj_to_char( obj, mob );     // Put the item in the mob's inventory
}  

/* 
    large amounts of the following code has been commented out. This part of the
    code has been moved to Lua scripts to allow more flexability with these
    random items. -Darwin 2007-12-06

    Commented out code removed on 2008-01-24  -Darwin

    calls to call_va run Lua functions from script files.
    call_va(lua_State, "lua function to call", "input>output", variable list)
    input: i for integer, s for string, d for double.
    pass output vars byref
*/
// Anything wearable, and trinkets
void wield_random_armor( CHAR_DATA *mob )
{
    OBJ_INDEX_DATA *pObjIndex = get_obj_index( number_range(29000, 29113) );
    OBJ_DATA *obj = create_object( pObjIndex, number_fuzzy( mob->level ) );
    char *name, *buf;

    if (obj->item_type == ITEM_ARMOR)
    {
        int weight = 0;
        if( xIS_SET(obj->extra_flags, ITEM_METAL))
            call_va(L_mud, "generate_random_item", "isi>siis", obj->item_type, obj->short_descr, TRUE, &name, &obj->value[0], &weight, &buf);
        else // not metal
            call_va(L_mud, "generate_random_item", "isi>siis", obj->item_type, obj->short_descr, FALSE, &name, &obj->value[0], &weight, &buf);	   
        obj->weight += weight;
        obj->cost = 250;
        if (number_percent() < 51 )
        {
            random_apply(obj, mob);
            obj->cost += 250;
            if (number_percent() < 41 )
            {
                random_apply(obj, mob);
                obj->cost += 500;
                if (number_percent() < 26 )
                {
                    random_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 16 )
                    {
                        random_apply(obj, mob);
                        obj->cost += 1000;
                        if ( number_percent() < 11 )
                        {
                            random_apply(obj, mob);
                            obj->cost += 1250;
                        }
                    }
                }
            }
        }
    } // not armor
    else if (obj->item_type == ITEM_WORN)
    {
        call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, FALSE, &name, &buf);
        obj->cost = 250;
        if (number_percent() < 76 )
        {
            random_apply(obj, mob);
            obj->cost += 250;
            if (number_percent() < 51 )
            {
                random_apply(obj, mob);
                obj->cost += 500;
                if (number_percent() < 26 )
                {
                    random_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 16 )
                    {
                        random_apply(obj, mob);
                        obj->cost += 1000;
                    }
                }
            }
        }
    } // not worn
    else if (obj->item_type == ITEM_WEAPON)
    {
        int weight = 0;
        int roll = 0;
        int dam = 0;
        call_va(L_mud, "generate_random_item", "isi>siiis", obj->item_type, obj->short_descr, FALSE, &name, &weight, &roll, &dam, &buf);
        obj->value[1] = (number_range( 1, 4) + (weight/3));
        obj->value[2] = (roll + (weight/3));
        obj->value[3] = dam;
        obj->weight = weight;
        obj->cost = 250;
        if (obj->weight >= 10)
        {
            xSET_BIT(obj->extra_flags, ITEM_2HAND);
            obj->value[2] += 5;
        }
        if (number_percent() < 51 )
        {
            random_apply(obj, mob);
            obj->cost += 250;
            if (number_percent() < 41 )
            {
                random_apply(obj, mob);
                obj->cost += 500;
                if (number_percent() < 21 )
                {
                    random_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 6 )
                    {
                        random_apply(obj, mob);
                        obj->cost += 1000;
                    }
                }
            }
        }
    } // not weapon
    else if (obj->item_type == ITEM_TREASURE)
    {
        if (obj->wear_flags & ITEM_HOLD) /* trinket? */
            call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, TRUE, &name, &buf);
        else /* no, necklace or something */
            call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, FALSE, &name, &buf);
        obj->cost = 250;
        if (number_percent() < 76 )
        {
            random_apply(obj, mob);
            obj->cost += 250;
            if (number_percent() < 66 )
            {
                random_apply(obj, mob);
                obj->cost += 500;
                if (number_percent() < 51 )
                {
                    random_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 26 )
                    {
                        random_apply(obj, mob);
                        obj->cost += 1000;
                    }
                }
            }
        }
    } // not treasure
    else if (obj->item_type == ITEM_LIGHT)
    {
        call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, FALSE, &name, &buf);
        obj->cost = 100;
        if (number_percent() < 90 )
        {
            random_apply(obj, mob);
            obj->cost += 500;
            if (number_percent() < 51 )
            {
                random_apply(obj, mob);
                obj->cost += 1000;
                if (number_percent() < 16 )
                {
                    random_apply(obj, mob);
                    obj->cost += 1500;
                }
            }
        }
    }

    STRFREE( obj->short_descr );
    obj->short_descr = str_alloc( name );

    STRFREE( obj->name );
    obj->name = str_alloc( name );

    STRFREE( obj->description );
    obj->description = str_alloc( buf ); 

    xSET_BIT(obj->extra_flags, ITEM_RANDOM); // set random flag -Darwin

    obj_to_char( obj, mob );
    if( IS_NPC(mob) /*&& number_range(1, 100) < 60*/ )
    {
        if ( IS_SET(obj->wear_flags, ITEM_WEAR_HEAD ) )
                equip_char( mob, obj, WEAR_HEAD );
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_EYES) )
            equip_char( mob, obj, WEAR_EYES);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_EARS) )
            equip_char( mob, obj, WEAR_EARS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_FACE) )
            equip_char( mob, obj, WEAR_FACE);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_NECK) )
            equip_char( mob, obj, WEAR_NECK_2);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_BODY) )
            equip_char( mob, obj, WEAR_BODY);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_ARMS) )
            equip_char( mob, obj, WEAR_ARMS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_WRIST) )
            equip_char( mob, obj, WEAR_WRIST_R);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_HANDS) )
            equip_char( mob, obj, WEAR_HANDS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_FINGER) )
            equip_char( mob, obj, WEAR_FINGER_R);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_ABOUT) )
            equip_char( mob, obj, WEAR_ABOUT);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_BACK) )
            equip_char( mob, obj, WEAR_BACK);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_WAIST) )
            equip_char( mob, obj, WEAR_WAIST);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_LEGS) )
            equip_char( mob, obj, WEAR_LEGS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_ANKLE) )
            equip_char( mob, obj, WEAR_ANKLE_R);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_FEET) )
            equip_char( mob, obj, WEAR_FEET);
        else if ( IS_SET(obj->wear_flags, ITEM_WIELD) )
            equip_char( mob, obj, WEAR_WIELD);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_SHIELD) )
            equip_char( mob, obj, WEAR_SHIELD);
        else if ( IS_SET(obj->wear_flags, ITEM_HOLD) )
            equip_char( mob, obj, WEAR_HOLD);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_WWP) )
            equip_char( mob, obj, WEAR_WWP_2);
    } 
}

void wield_random_artifact( CHAR_DATA *mob )
{
    OBJ_INDEX_DATA *pObjIndex = get_obj_index( number_range(29500, 29610) );
    OBJ_DATA *obj = create_object( pObjIndex, number_fuzzy( mob->level ) );
    char *name, *buf;

    if (obj->item_type == ITEM_ARTARMOR)
    {
        int weight = 0;
        if( xIS_SET(obj->extra_flags, ITEM_METAL))
            call_va(L_mud, "generate_random_item", "isi>siis", obj->item_type, obj->short_descr, TRUE, &name, &obj->value[0], &weight, &buf);
        else
            call_va(L_mud, "generate_random_item", "isi>siis", obj->item_type, obj->short_descr, FALSE, &name, &obj->value[0], &weight, &buf);	   
        obj->weight += weight;
        obj->cost = 1000;
        if (number_percent() < 101 )
        {
            random_artifact_apply(obj, mob);
            obj->cost += 250;
            if (number_percent() < 85 )
            {
                random_artifact_apply(obj, mob);
                obj->cost += 500;
                if (number_percent() < 70 )
                {
                    random_artifact_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 55 )
                    {
                        random_artifact_apply(obj, mob);
                        obj->cost += 1000;
                        if (number_percent() < 40 )
                        {
                            random_artifact_apply(obj, mob);
                            obj->cost +=1000;
                            if (number_percent() < 25 )
                            {
                                random_artifact_apply(obj, mob);
                                obj->cost +=1000;
                                if (number_percent() < 10 )
                                {
                                    random_artifact_apply(obj, mob);
                                    obj->cost +=1500;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else if (obj->item_type == ITEM_ARTWEAPON)
    {
        int weight = 0;
        int roll = 0;
        int dam = 0;
        call_va(L_mud, "generate_random_item", "isi>siiis", obj->item_type, obj->short_descr, FALSE, &name, &weight, &roll, &dam, &buf);
        obj->value[1] = (number_range( 1, 4) + (weight/3));
        obj->value[2] = (roll + (weight/3));
        obj->value[3] = dam;
        obj->weight = weight;
        obj->cost = 1000;
        obj->value[1] += 1;
        obj->value[2] += 2;
        if (obj->weight >= 10)
        {
            xSET_BIT(obj->extra_flags, ITEM_2HAND);
            obj->value[2] += 5;
        }
        if (number_percent() < 90 )
        { 
            random_artifact_apply(obj, mob);
            obj->cost += 250; 
            if (number_percent() < 75 )
            { 
                random_artifact_apply(obj, mob);
                obj->cost += 500; 
                if (number_percent() < 60 )
                { 
                    random_artifact_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 45 )
                    {
                        random_artifact_apply(obj, mob);
                        obj->cost += 1000;
                        if (number_percent() < 30 ) 
                        { 
                            random_artifact_apply(obj, mob); 
                            obj->cost +=1000;
                            if (number_percent() < 15 )
                            { 
                                random_artifact_apply(obj, mob);
                                obj->cost +=1000;
                                if (number_percent() < 5 )
                                {
                                    random_artifact_apply(obj, mob);
                                    obj->cost +=1500;
                                }
                            } 
                        } 
                    }
                } 
            } 
        }
    }
    else if (obj->item_type == ITEM_ARTTREASURE)
    {                                          
        if (obj->wear_flags & ITEM_HOLD) /* trinket? */
            call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, TRUE, &name, &buf);
        else /* no, necklace or something */
            call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, FALSE, &name, &buf);
        obj->cost = 1000;
        if (number_percent() < 101 )
        { 
            random_artifact_apply(obj, mob);
            obj->cost += 250; 
            if (number_percent() < 90 )
            { 
                random_artifact_apply(obj, mob);
                obj->cost += 500; 
                if (number_percent() < 75 )
                { 
                    random_artifact_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 60 )
                    {
                        random_artifact_apply(obj, mob);
                        obj->cost += 1000;
                        if (number_percent() < 45 ) 
                        { 
                            random_artifact_apply(obj, mob); 
                            obj->cost +=1000;
                            if (number_percent() < 30 )
                            { 
                                random_artifact_apply(obj, mob);
                                obj->cost +=1000;
                                if (number_percent() < 15 )
                                {
                                    random_artifact_apply(obj, mob);
                                    obj->cost +=1500;
                                }
                            } 
                        } 
                    }
                } 
            } 
        }
    }
    else if (obj->item_type == ITEM_ARTLIGHT)
    { 
        call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, FALSE, &name, &buf);
        obj->cost = 100; 
        if (number_percent() < 101 )
        { 
            random_artifact_apply(obj, mob);
            obj->cost += 250; 
            if (number_percent() < 90 )
            { 
                random_artifact_apply(obj, mob);
                obj->cost += 500; 
                if (number_percent() < 75 )
                { 
                    random_artifact_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 60 )
                    {
                        random_artifact_apply(obj, mob);
                        obj->cost += 1000;
                        if (number_percent() < 45 ) 
                        { 
                            random_artifact_apply(obj, mob); 
                            obj->cost +=1000;
                            if (number_percent() < 30 )
                            { 
                                random_artifact_apply(obj, mob);
                                obj->cost +=1000;
                                if (number_percent() < 15 )
                                {
                                    random_artifact_apply(obj, mob);
                                    obj->cost +=1500;
                                }
                            } 
                        } 
                    }
                } 
            } 
        } 
    }
    else if (obj->item_type == ITEM_ARTWORN)
    {    
        call_va(L_mud, "generate_random_item", "isi>ss", obj->item_type, obj->short_descr, FALSE, &name, &buf);
        obj->cost = 1000;
        if (number_percent() < 101 )
        { 
            random_artifact_apply(obj, mob);
            obj->cost += 250; 
            if (number_percent() < 85 )
            { 
                random_artifact_apply(obj, mob);
                obj->cost += 500; 
                if (number_percent() < 70 )
                { 
                    random_artifact_apply(obj, mob);
                    obj->cost += 750;
                    if (number_percent() < 55 )
                    {
                        random_artifact_apply(obj, mob);
                        obj->cost += 1000;
                        if (number_percent() < 40 ) 
                        { 
                            random_artifact_apply(obj, mob); 
                            obj->cost +=1000;
                            if (number_percent() < 25 )
                            { 
                                random_artifact_apply(obj, mob);
                                obj->cost +=1000;
                                if (number_percent() < 10 )
                                {
                                    random_artifact_apply(obj, mob);
                                    obj->cost +=1500;
                                }
                            } 
                        } 
                    }
                } 
            } 
        }
    }          

    STRFREE( obj->short_descr );
    obj->short_descr = str_alloc( name );

    STRFREE( obj->name );
    obj->name = str_alloc( name );

    STRFREE( obj->description );
    obj->description = str_alloc( buf ); 

    xSET_BIT(obj->extra_flags, ITEM_RANDOM); // set random flag -Darwin

    obj_to_char( obj, mob );
    if( IS_NPC(mob) /*&& number_range(1, 100) < 60 */ )
    {
        if ( IS_SET(obj->wear_flags, ITEM_WEAR_HEAD ) )
            equip_char( mob, obj, WEAR_HEAD );
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_EYES) )
            equip_char( mob, obj, WEAR_EYES);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_EARS) )
            equip_char( mob, obj, WEAR_EARS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_FACE) )
            equip_char( mob, obj, WEAR_FACE);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_NECK) )
            equip_char( mob, obj, WEAR_NECK_2);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_BODY) )
            equip_char( mob, obj, WEAR_BODY);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_ARMS) )
            equip_char( mob, obj, WEAR_ARMS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_WRIST) )
            equip_char( mob, obj, WEAR_WRIST_R);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_HANDS) )
            equip_char( mob, obj, WEAR_HANDS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_FINGER) )
            equip_char( mob, obj, WEAR_FINGER_R);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_ABOUT) )
            equip_char( mob, obj, WEAR_ABOUT);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_BACK) )
            equip_char( mob, obj, WEAR_BACK);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_WAIST) )
            equip_char( mob, obj, WEAR_WAIST);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_LEGS) )
            equip_char( mob, obj, WEAR_LEGS);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_ANKLE) )
            equip_char( mob, obj, WEAR_ANKLE_R);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_FEET) )
            equip_char( mob, obj, WEAR_FEET);
        else if ( IS_SET(obj->wear_flags, ITEM_WIELD) )
            equip_char( mob, obj, WEAR_WIELD);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_SHIELD) )
            equip_char( mob, obj, WEAR_SHIELD);
        else if ( IS_SET(obj->wear_flags, ITEM_HOLD) )
            equip_char( mob, obj, WEAR_HOLD);
        else if ( IS_SET(obj->wear_flags, ITEM_WEAR_WWP) )
            equip_char( mob, obj, WEAR_WWP_2);
    } 
}

void get_magvalue( OBJ_DATA *obj ) 
{  
    int valuea = 0;
    int valueb = 0;
    int valuec = 0;
    int valued = 0;
    int valuee = 0;
    int tvalue = 0;
    AFFECT_DATA *paf;

    for ( paf = obj->first_affect; paf; paf = paf->next )
    {
        switch(paf->location)
        {
            case APPLY_HIT:
            case APPLY_MANA:
            case APPLY_MOVE:
            case APPLY_AC:
            case APPLY_AGE:
                if (paf->modifier >= 0 )
                    valuea += (paf->modifier / 5);
                if (paf->modifier < 0 )
                    valuea += (paf->modifier / -5);
                break;
            case APPLY_PICK:
            case APPLY_TRACK:
            case APPLY_DODGE:
            case APPLY_PARRY:
            case APPLY_BACKSTAB:
            case APPLY_STEAL:
            case APPLY_SNEAK:
            case APPLY_HIDE:
            case APPLY_SCAN:
            case APPLY_PEEK:
            case APPLY_DISARM:
            case APPLY_CLIMB:
            case APPLY_GRIP:
            case APPLY_SCRIBE:
            case APPLY_BREW:
            case APPLY_DIG:
            case APPLY_SEARCH:
            case APPLY_GOUGE:
            case APPLY_DETRAP:
                if (paf->modifier >= 0 ) 
                    valuee += (paf->modifier / 5);
                if (paf->modifier < 0 )
                    valuee += (paf->modifier / -5);
                break;
            case APPLY_AFFECT:
            case APPLY_EXT_AFFECT:
            case APPLY_RESISTANT:
                valued += 6;
                break;
            case APPLY_DAMROLL:
            case APPLY_SPELLDAM:
            case APPLY_HITROLL:
            case APPLY_SAVING_DAMAGE:
            case APPLY_SAVING_ROD:
            case APPLY_SAVING_PARA:
            case APPLY_SAVING_BREATH:
            case APPLY_SAVING_SPELL:
            case APPLY_DEX:
            case APPLY_INT:
            case APPLY_STR:
            case APPLY_CHA:
            case APPLY_LCK:
            case APPLY_WIS:
            case APPLY_CON:
                if (paf->modifier >= 0)
                    valueb += paf->modifier;
                if (paf->modifier < 0)
                    valueb += paf->modifier * -1;
                break;
            default: 
                break;
        }
        if (paf == obj->last_affect)
            break;
    }

    for ( paf = obj->pIndexData->first_affect; paf; paf = paf->next )
    {
        switch(paf->location)
        {
            case APPLY_HIT:
            case APPLY_MANA:
            case APPLY_MOVE:
            case APPLY_AC:
            case APPLY_AGE:
                valuea += (paf->modifier / 5);
                break;
            case APPLY_PICK:
            case APPLY_TRACK:
            case APPLY_DODGE:
            case APPLY_PARRY:
            case APPLY_BACKSTAB:
            case APPLY_STEAL:
            case APPLY_SNEAK:
            case APPLY_HIDE:
            case APPLY_SCAN:
            case APPLY_PEEK:
            case APPLY_DISARM:
            case APPLY_CLIMB:
            case APPLY_GRIP:
            case APPLY_SCRIBE:
            case APPLY_BREW:
            case APPLY_DIG:
            case APPLY_SEARCH:
            case APPLY_GOUGE:
            case APPLY_DETRAP:
                valuee += (paf->modifier / 5);
                break;
            case APPLY_AFFECT:
            case APPLY_EXT_AFFECT:
            case APPLY_RESISTANT:
                valued += 6;
                break;
            case APPLY_DAMROLL:
            case APPLY_SPELLDAM:
            case APPLY_HITROLL:
            case APPLY_SAVING_DAMAGE:
            case APPLY_SAVING_ROD:
            case APPLY_SAVING_PARA:
            case APPLY_SAVING_BREATH:
            case APPLY_SAVING_SPELL:
            case APPLY_DEX:
            case APPLY_INT:
            case APPLY_STR:
            case APPLY_CHA:
            case APPLY_LCK:
            case APPLY_WIS:
            case APPLY_CON:
                if (paf->modifier >= 0)
                    valueb += paf->modifier;
                if (paf->modifier < 0)
                    valueb += paf->modifier * -1;
                break;
            default: 
                break;
        }
        if (paf == obj->last_affect)
        break;
    }

    if ( obj->item_type == ITEM_WAND || obj->item_type == ITEM_STAFF )
    {
        valuec += (obj->value[2] + obj->value[0])/5;
    }

    if ( obj->item_type == ITEM_SCROLL || obj->item_type == ITEM_POTION || obj->item_type == ITEM_PILL )
    {
        valuec += (obj->value[0])/2;
    }

    //Calculate Total Value
    tvalue += (valuea + valueb + valuec + valued + valuee);
    obj->tmag = tvalue;
    return;
}



void get_mflag( OBJ_DATA *obj, char *buf ) 
{
    char *buf2;
    buf[0] = '\0';
    
    get_magvalue(obj);
    call_va(L_mud, "get_mflag", "i>s", obj->tmag, &buf2);
    strcat(buf, buf2);
}

void do_book( CHAR_DATA *ch, char *argument )
{
   int cost; /* Cost to change */
   cost = 0;

   if ( argument[0] == '\0' )
   {
        send_to_char("&RSyntax: book sign\n\r", ch);
        send_to_char("&RSee &YHELP BOOK &Rfor more info.\n\r", ch);
        return;
   }
   if ( IS_SET(ch->in_room->room_flags, ROOM_BLOODROOM) )
   {
     if ( !str_cmp( argument, "sign" ) )
     {
        if ( get_age( ch ) < 18 )
        {
           send_to_char("&rYou are too young to be a Player Killer.\n\r", ch);
	   return;
        }
        if ( ch->level > 25 )
	{
	   send_to_char("&rYour level is too high to switch to Deadly now!\n\r", ch);
	   return;
        }
        if ( xIS_SET(ch->act, PLR_TIER ) )
	{
	   send_to_char("&rSorry, the level 25 limit applied way before you Tiered up!\n\r", ch);
	   return;
	}
        else
        {
            if ( CAN_PKILL ( ch ) )
            {
               send_to_char("&rYou are already a Player Killer!\n\r", ch);
            }
            else
            {
               send_to_char("&rYou sign your name in the Book of Blood.\n\r", ch);
               send_to_char("&rYou are now a Player Killer!\n\r", ch);
               SET_BIT(ch->pcdata->flags, PCFLAG_DEADLY);
	       xREMOVE_BIT(ch->act, PLR_NICE);
               save_char_obj( ch );
               saving_char = NULL;
               send_to_char( "&rDone.\n\r", ch );
            }
       }
       return;
    }


    if ( !str_cmp( argument, "erase" ) )
    {
     	if ( !CAN_PKILL ( ch ))
        {
          send_to_char( "&rYou are already peaceful!\n\r", ch );
          return;
        }
        else
        {
          if( ch->gold < cost)
          {
            send_to_char( "&rYou do not have enough money to erase your name!\n\r", ch);
            return;
          }
          else
          {
            send_to_char( "&rSorry...there is no turning back once you've signed!\n\r", ch);
	    return;
          }
        }
     return;
     }
    return;
    }
    else
    {
    send_to_char( "&rYou can't sign that!\n\r", ch );
    }
}

