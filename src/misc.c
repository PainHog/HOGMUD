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
 *	    Misc module for general commands: not skills or spells	    *
 ****************************************************************************
 * Note: Most of the stuff in here would go in act_obj.c, but act_obj was   *
 * getting big.								    *
 ****************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"


extern int	top_exit;

void get_targetmob	args(( CHAR_DATA *ch ));
void get_targetmob_expert args(( CHAR_DATA *ch ));
void mobmaster_update	args(( void ));

void do_eat( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    OBJ_DATA *obj;
    ch_ret retcode;
    int foodcond;
    bool hgflag = TRUE;

    if ( argument[0] == '\0' )
    {
	send_to_char( "Eat what?\n\r", ch );
	return;
    }

    if ( IS_NPC(ch) || ch->pcdata->condition[COND_FULL] > 5 )
	if ( ms_find_obj(ch) )
	    return;

    if ( (obj = find_obj(ch, argument, TRUE)) == NULL )
	return;

    if ( !IS_IMMORTAL(ch) )
    {
	if ( obj->item_type != ITEM_FOOD && obj->item_type != ITEM_PILL &&
	     obj->item_type != ITEM_COOK)
	{
	    act( AT_ACTION, "$n starts to nibble on $p... ($e must really be hungry)",  ch, obj, NULL, TO_ROOM );
	    act( AT_ACTION, "You try to nibble on $p...", ch, obj, NULL, TO_CHAR );
	    return;
	}

	/*if ( !IS_NPC(ch) && obj->item_type != ITEM_PILL && ch->pcdata->condition[COND_FULL] > 95 )
	{
	    send_to_char( "You are too full to eat more.\n\r", ch );
	    return;
	}*/
    }

    if ( !IS_NPC(ch) && (!IS_PKILL(ch) || (IS_PKILL(ch) && !IS_SET(ch->pcdata->flags, PCFLAG_HIGHGAG) ) ) )
	hgflag = FALSE;

    /* required due to object grouping */
    separate_obj( obj );
    if ( obj->in_obj )
    {
	if ( !hgflag )
	  act( AT_PLAIN, "You take $p from $P.", ch, obj, obj->in_obj, TO_CHAR );
	act( AT_PLAIN, "$n takes $p from $P.", ch, obj, obj->in_obj, TO_ROOM );
    }
    if ( ch->fighting && number_percent( ) > (get_curr_dex(ch) * 3) )
    {
	sprintf( buf, "%s",
	( ch->in_room->sector_type == SECT_UNDERWATER ||
	  ch->in_room->sector_type == SECT_WATER_SWIM ||
	  ch->in_room->sector_type == SECT_WATER_NOSWIM )   ? "dissolves in the water" :
	( ch->in_room->sector_type == SECT_AIR        ||
	  IS_SET( ch->in_room->room_flags, ROOM_NOFLOOR ) ) ? "falls far below" :
							      "is trampled underfoot" );
        act( AT_MAGIC, "$n drops $p, and it $T.", ch, obj, buf, TO_ROOM );
	if ( !hgflag )
	  act( AT_MAGIC, "Oops, $p slips from your hand and $T!", ch, obj, buf, TO_CHAR );
    }
    else
    {
        if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
        {
          if ( !obj->action_desc || obj->action_desc[0]=='\0' )
          {
            act( AT_ACTION, "$n eats $p.",  ch, obj, NULL, TO_ROOM );
	    if ( !hgflag )
		act( AT_ACTION, "You eat $p.", ch, obj, NULL, TO_CHAR );
          }
          else
            actiondesc( ch, obj, NULL ); 
        }

    switch ( obj->item_type )
    {

    case ITEM_COOK:
    case ITEM_FOOD:
	WAIT_STATE( ch, PULSE_PER_SECOND/3 );
	if ( obj->timer > 0 && obj->value[1] > 0 )
	   foodcond = (obj->timer * 10) / obj->value[1];
	else
	   foodcond = 10;

	if ( !IS_NPC(ch) )
	{
	    int condition;

	    condition = ch->pcdata->condition[COND_FULL];
	    gain_condition( ch, COND_FULL, (obj->value[0] * foodcond) / 5 );
	    if ( condition <= 1 && ch->pcdata->condition[COND_FULL] > 1 )
		send_to_char( "You are no longer hungry.\n\r", ch );
	    else if ( ch->pcdata->condition[COND_FULL] > 85 )
		send_to_char( "You are full.\n\r", ch );
	}

	if (  obj->value[3] != 0
	||   (foodcond < 4 && number_range( 0, foodcond + 1 ) == 0) 
	|| (obj->item_type == ITEM_COOK && obj->value[2] == 0 ) )
	{
	    /* The food was poisoned! */
	    AFFECT_DATA af;

	    if ( obj->value[3] != 0 )
	    {
		act( AT_POISON, "$n chokes and gags.", ch, NULL, NULL, TO_ROOM );
		act( AT_POISON, "You choke and gag.", ch, NULL, NULL, TO_CHAR );
		ch->mental_state = URANGE( 20, ch->mental_state + 5, 100 );
	    }
	    else
	    {
		act( AT_POISON, "$n gags on $p.", ch, obj, NULL, TO_ROOM );
		act( AT_POISON, "You gag on $p.", ch, obj, NULL, TO_CHAR );
		ch->mental_state = URANGE( 15, ch->mental_state + 5, 100 );
	    }

	    af.type      = gsn_poison;
	    af.duration  = 2 * obj->value[0]
	    		 * (obj->value[3] > 0 ? obj->value[3] : 1);
	    af.location  = APPLY_NONE;
	    af.modifier  = 0;
	    af.bitvector = meb(AFF_POISON);
	    affect_join( ch, &af );
	}
	break;

    case ITEM_PILL:
	sysdata.upill_val += obj->cost/100;
	if ( who_fighting( ch ) && IS_PKILL( ch ) )
          WAIT_STATE( ch, PULSE_PER_SECOND/4 );
        else
          WAIT_STATE( ch, PULSE_PER_SECOND/3 );
	/* allow pills to fill you, if so desired */
	if ( !IS_NPC(ch) && obj->value[4] )
	{
	    int condition;

	    condition = ch->pcdata->condition[COND_FULL];
	    gain_condition( ch, COND_FULL, obj->value[4] );
	    if ( condition <= 1 && ch->pcdata->condition[COND_FULL] > 1 )
		send_to_char( "You are no longer hungry.\n\r", ch );
	    else if ( ch->pcdata->condition[COND_FULL] > 85 )
		send_to_char( "You are full.\n\r", ch );
	}
	retcode = obj_cast_spell( obj->value[1], obj->value[0], ch, ch, NULL );
	if ( retcode == rNONE )
	  retcode = obj_cast_spell( obj->value[2], obj->value[0], ch, ch, NULL );
	if ( retcode == rNONE )
	  retcode = obj_cast_spell( obj->value[3], obj->value[0], ch, ch, NULL );
	break;
    }

    }
    if ( obj->serial == cur_obj )
      global_objcode = rOBJ_EATEN;
    extract_obj( obj );
    return;
}

void do_impale( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *corpse = NULL;
    char arg[MAX_INPUT_LENGTH];
    char buf[MAX_INPUT_LENGTH];

    one_argument(argument, arg);

    if( ch->mount )
    {
        send_to_char( "Not from this mount you can't!\n\r", ch );
        return;
    }

	   if (arg[0] == '\0')
    {
	    send_to_char( "You cannot impale yourself!\n\r", ch );
	    return;
    }

    if( !( corpse = get_obj_here( ch, arg ) ) )
    {
        send_to_char( "Where did that carcass go?\n\r", ch );
        return;
    }

    if( corpse->item_type != ITEM_CORPSE_PC && corpse->item_type != ITEM_CORPSE_NPC )
    {
        send_to_char( "Interesting concept ... but let's stick with corpses, shall we?\n\r", ch );
        return;
    }

    if( corpse->value[1] == 15 )
    { 
        send_to_char( "That corpse is already on a pike!\n\r", ch );
        return; 
    }

    if( corpse->value[5] == 1 )
    {
        send_to_char( "It's no good if there's no skin on it so people can see what it was!\n\r", ch );
        return;
    }

    separate_obj( corpse ); /* No need to destroy ALL corpses of this type */


   act( AT_PLAIN, "You impale $p on a bloodied pike for all to see.", ch, corpse, NULL, TO_CHAR );
   act( AT_PLAIN, "$n impales $p on a bloodied pike for all to see.", ch, corpse, NULL, TO_ROOM );

   sprintf( buf, "bloodied pike %s", ch->name );
   STRFREE( corpse->name );
   corpse->name = str_alloc( buf );

   sprintf( buf, "Dripping blood, %s hangs here, impaled on a bloodied pike by %s.", corpse->short_descr, ch->name );
   STRFREE( corpse->description );
   corpse->description = str_alloc( buf );

   sprintf( buf, "%s, impaled upon a bloodied pike by %s", corpse->short_descr, ch->name );
   STRFREE( corpse->short_descr );
   corpse->short_descr = str_alloc( buf );


   corpse->value[1] = 15;
   corpse->timer = 30;
//   if(IS_SET(corpse->wear_flags, ITEM_TAKE))
//	   REMOVE_BIT(corpse->wear_flags, ITEM_TAKE);

    /* Tanning won't destroy what the corpse was carrying - Samson 11-20-99 */
   if( corpse->carried_by )
        empty_obj( corpse, NULL, corpse->carried_by->in_room );
    else if ( corpse->in_room )
      empty_obj( corpse, NULL, corpse->in_room );

}

void do_quaff( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    ch_ret retcode;
    bool hgflag = TRUE;

    if ( argument[0] == '\0' || !str_cmp(argument, "") )
    {
	send_to_char( "Quaff what?\n\r", ch );
	return;
    }

    if ( (obj = find_obj(ch, argument, TRUE)) == NULL )
	return;

    if ( !IS_NPC(ch) && IS_AFFECTED( ch, AFF_CHARM) )
    	return;

    if ( obj->item_type != ITEM_POTION )
    {
	if ( obj->item_type == ITEM_DRINK_CON )
	   do_drink( ch, obj->name );
	else
	{
	   act( AT_ACTION, "$n lifts $p up to $s mouth and tries to drink from it...", ch, obj, NULL, TO_ROOM );
	   act( AT_ACTION, "You bring $p up to your mouth and try to drink from it...", ch, obj, NULL, TO_CHAR );
	}
	return;
    }

    /*
     * Empty container check 					-Shaddai
     */
     if ( obj->value[1] == -1 && obj->value[2] == -1 && obj->value[3] == -1 )
     {
       send_to_char( "You suck in nothing but air.\n\r", ch );
       return;
     }

    if ( !IS_NPC(ch) && (!IS_PKILL(ch) || (IS_PKILL(ch) && !IS_SET(ch->pcdata->flags, PCFLAG_HIGHGAG) ) ) )
	hgflag = FALSE;

    separate_obj( obj );
    if ( obj->in_obj )
    {
        act( AT_PLAIN, "You take $p from $P.", ch, obj, obj->in_obj, TO_CHAR );
	act( AT_PLAIN, "$n takes $p from $P.", ch, obj, obj->in_obj, TO_ROOM );
    }

    /*
     * If fighting, chance of dropping potion			-Thoric
     */
    if ( (ch->fighting && number_percent( ) > (get_curr_dex(ch) * 3)) && ( !IS_OBJ_STAT( obj, ITEM_NOBURN ) )  )
    {
	act( AT_MAGIC, "$n fumbles $p and shatters it into fragments.", ch, obj, NULL, TO_ROOM );
	if ( !hgflag )
	  act( AT_MAGIC, "Oops... $p is knocked from your hand and shatters!", ch, obj, NULL ,TO_CHAR );
    }
    else
    {
	if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
	{
          if ( !CAN_PKILL( ch ) || !obj->in_obj )
          {
	    act( AT_ACTION, "$n quaffs $p.",  ch, obj, NULL, TO_ROOM );
	    if ( !hgflag )
	      act( AT_ACTION, "You quaff $p.", ch, obj, NULL, TO_CHAR );
          }
          else if ( obj->in_obj )
          {
            act( AT_ACTION, "$n quaffs $p from $P.", ch, obj, obj->in_obj, TO_ROOM );
	    if ( !hgflag )
	      act( AT_ACTION, "You quaff $p from $P.", ch, obj, obj->in_obj, TO_CHAR );
          }
	}

        if ( who_fighting( ch ) && IS_PKILL( ch ) )
          WAIT_STATE( ch, PULSE_PER_SECOND );
        else
          WAIT_STATE( ch, PULSE_PER_SECOND );
/*
	gain_condition( ch, COND_THIRST, 1 );
	if ( !IS_NPC(ch) && ch->pcdata->condition[COND_THIRST] > 43 )
	  act( AT_ACTION, "Your stomach is nearing its capacity.", ch, NULL, NULL, TO_CHAR );*/
	retcode = obj_cast_spell( obj->value[1], obj->value[0], ch, ch, NULL );
	if ( retcode == rNONE )
	  retcode = obj_cast_spell( obj->value[2], obj->value[0], ch, ch, NULL );
	if ( retcode == rNONE )
	  retcode = obj_cast_spell( obj->value[3], obj->value[0], ch, ch, NULL );
    }
    if ( obj->pIndexData->vnum == OBJ_VNUM_FLASK_BREWING )
	sysdata.brewed_used++;
    else
	sysdata.upotion_val += obj->cost/100;
    if ( cur_obj == obj->serial )
      global_objcode = rOBJ_QUAFFED;
    extract_obj( obj );
    return;
}


void do_recite( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *scroll;
    OBJ_DATA *obj;
    ch_ret    retcode;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' )
    {
	send_to_char( "Recite what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( ( scroll = get_obj_carry( ch, arg1 ) ) == NULL )
    {
	send_to_char( "You do not have that scroll.\n\r", ch );
	return;
    }

    if ( scroll->item_type != ITEM_SCROLL )
    {
	act( AT_ACTION, "$n holds up $p as if to recite something from it...",  ch, scroll, NULL, TO_ROOM );
	act( AT_ACTION, "You hold up $p and stand there with your mouth open.  (Now what?)", ch, scroll, NULL, TO_CHAR );
	return;
    }

	if(IS_NPC(ch))
	{
		send_to_char("You can't make heads or tails of this scroll.\n\r", ch);
		return;
	}

	if( 	!IS_MAGE(ch)
		&&	!IS_DIABOLIST(ch)
		&&	!IS_CLERIC(ch)
		&&	!IS_CONJURER(ch)
		&&	!IS_SHAMAN(ch)
		&&	!IS_ARCHMAGI(ch)
		&&	!IS_BISHOP(ch)
		&&	!IS_IMMORTAL(ch) 	)
    {
		if ( scroll->value[0] > 10 )
		{
			send_to_char( "This scroll is too complex for you to understand.\n\r", ch);
			return;
		}
    }

    obj = NULL;
    if ( arg2[0] == '\0' )
	victim = ch;
    else
    {
	if ( ( victim = get_char_room ( ch, arg2 ) ) == NULL
	&&   ( obj    = get_obj_carry  ( ch, arg2 ) ) == NULL )
	{
	    send_to_char( "You can't find it.\n\r", ch );
	    return;
	}
    }

    if ( scroll->pIndexData->vnum == OBJ_VNUM_SCROLL_SCRIBING )
	sysdata.scribed_used++;
    separate_obj( scroll );
    act( AT_MAGIC, "$n recites $p.", ch, scroll, NULL, TO_ROOM );
    act( AT_MAGIC, "You recite $p.", ch, scroll, NULL, TO_CHAR );

    if ( victim != ch )
	WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
    else
        WAIT_STATE( ch, PULSE_PER_SECOND/2 );

    retcode = obj_cast_spell( scroll->value[1], scroll->value[0], ch, victim, obj );
    if ( retcode == rNONE )
      retcode = obj_cast_spell( scroll->value[2], scroll->value[0], ch, victim, obj );
    if ( retcode == rNONE )
      retcode = obj_cast_spell( scroll->value[3], scroll->value[0], ch, victim, obj );

    if ( scroll->serial == cur_obj )
      global_objcode = rOBJ_USED;
    extract_obj( scroll );
    return;
}


/*
 * Function to handle the state changing of a triggerobject (lever)  -Thoric
 */
void pullorpush( CHAR_DATA *ch, OBJ_DATA *obj, bool pull )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA		*rch;
    bool		 isup;
    ROOM_INDEX_DATA	*room,  *to_room;
    EXIT_DATA		*pexit, *pexit_rev;
    int			 edir;
    char		*txt;

    if ( IS_SET( obj->value[0], TRIG_UP ) )
      isup = TRUE;
    else
      isup = FALSE;
    switch( obj->item_type )
    {
	default:
	  sprintf( buf, "You can't %s that!\n\r", pull ? "pull" : "push" );
	  send_to_char( buf, ch );
	  return;
	  break;
	case ITEM_SWITCH:
	case ITEM_LEVER:
	case ITEM_PULLCHAIN:
	  if ( (!pull && isup) || (pull && !isup) )
	  {
		sprintf( buf, "It is already %s.\n\r", isup ? "up" : "down" );
		send_to_char( buf, ch );
		return;
 	  }
	case ITEM_BUTTON:
	  if ( (!pull && isup) || (pull && !isup) )
	  {
		sprintf( buf, "It is already %s.\n\r", isup ? "in" : "out" );
		send_to_char( buf, ch );
		return;
	  }
	  break;
    }
    if( (pull) && HAS_PROG(obj->pIndexData,PULL_PROG) )
    {
	if ( !IS_SET(obj->value[0], TRIG_AUTORETURN ) )
 	  REMOVE_BIT( obj->value[0], TRIG_UP );
 	oprog_pull_trigger( ch, obj );
        return;
    }
    if( (!pull) && HAS_PROG(obj->pIndexData,PUSH_PROG) )
    {
	if ( !IS_SET(obj->value[0], TRIG_AUTORETURN ) )
	  SET_BIT( obj->value[0], TRIG_UP );
	oprog_push_trigger( ch, obj );
        return;
    }

    if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
    {
      sprintf( buf, "$n %s $p.", pull ? "pulls" : "pushes" );
      act( AT_ACTION, buf,  ch, obj, NULL, TO_ROOM );
      sprintf( buf, "You %s $p.", pull ? "pull" : "push" );
      act( AT_ACTION, buf, ch, obj, NULL, TO_CHAR );
    }

    if ( !IS_SET(obj->value[0], TRIG_AUTORETURN ) )
    {
	if ( pull )
	  REMOVE_BIT( obj->value[0], TRIG_UP );
	else
	  SET_BIT( obj->value[0], TRIG_UP );
    }
    if ( IS_SET( obj->value[0], TRIG_TELEPORT )
    ||   IS_SET( obj->value[0], TRIG_TELEPORTALL )
    ||   IS_SET( obj->value[0], TRIG_TELEPORTPLUS ) )
    {
	int flags;

	if ( ( room = get_room_index( obj->value[1] ) ) == NULL )
	{
	    bug( "PullOrPush: obj points to invalid room %d", obj->value[1] );
	    return;
	}
	flags = 0;
	if ( IS_SET( obj->value[0], TRIG_SHOWROOMDESC ) )
	  SET_BIT( flags, TELE_SHOWDESC );
	if ( IS_SET( obj->value[0], TRIG_TELEPORTALL ) )
	  SET_BIT( flags, TELE_TRANSALL );
	if ( IS_SET( obj->value[0], TRIG_TELEPORTPLUS ) )
	  SET_BIT( flags, TELE_TRANSALLPLUS );

	teleport( ch, obj->value[1], flags );
	return;
    }

    if ( IS_SET( obj->value[0], TRIG_RAND4 )
    ||	 IS_SET( obj->value[0], TRIG_RAND6 ) )
    {
	int maxd;

	if ( ( room = get_room_index( obj->value[1] ) ) == NULL )
	{
	    bug( "PullOrPush: obj points to invalid room %d", obj->value[1] );
	    return;
	}

	if ( IS_SET( obj->value[0], TRIG_RAND4 ) )
	  maxd = 3;
	else
	  maxd = 5;

	randomize_exits( room, maxd );
	for ( rch = room->first_person; rch; rch = rch->next_in_room )
	{
	   send_to_char( "You hear a loud rumbling sound.\n\r", rch );
	   send_to_char( "Something seems different...\n\r", rch );
	}
    }
    if ( IS_SET( obj->value[0], TRIG_DOOR ) )
    {
	room = get_room_index( obj->value[1] );
	if ( !room )
	  room = obj->in_room;
	if ( !room )
	{
	  bug( "PullOrPush: obj points to invalid room %d", obj->value[1] );
	  return;
	}	
	if ( IS_SET( obj->value[0], TRIG_D_NORTH ) )
	{
	  edir = DIR_NORTH;
	  txt = "to the north";
	}
	else
	if ( IS_SET( obj->value[0], TRIG_D_SOUTH ) )
	{
	  edir = DIR_SOUTH;
	  txt = "to the south";
	}
	else
	if ( IS_SET( obj->value[0], TRIG_D_EAST ) )
	{
	  edir = DIR_EAST;
	  txt = "to the east";
	}
	else
	if ( IS_SET( obj->value[0], TRIG_D_WEST ) )
	{
	  edir = DIR_WEST;
	  txt = "to the west";
	}
	else
	if ( IS_SET( obj->value[0], TRIG_D_UP ) )
	{
	  edir = DIR_UP;
	  txt = "from above";
	}
	else
	if ( IS_SET( obj->value[0], TRIG_D_DOWN ) )
	{
	  edir = DIR_DOWN;
	  txt = "from below";
	}
	else
	{
	  bug( "PullOrPush: door: no direction flag set.", 0 );
	  return;
	}
	pexit = get_exit( room, edir );
	if ( !pexit )
	{
	    if ( !IS_SET( obj->value[0], TRIG_PASSAGE ) )
	    {
		bug( "PullOrPush: obj points to non-exit %d", obj->value[1] );
		return;
	    }
	    to_room = get_room_index( obj->value[2] );
	    if ( !to_room )
	    {
		bug( "PullOrPush: dest points to invalid room %d", obj->value[2] );
		return;
	    }
	    pexit = make_exit( room, to_room, edir );
	    pexit->keyword	= STRALLOC( "" );
	    pexit->description	= STRALLOC( "" );
	    pexit->key		= -1;
	    pexit->exit_info	= 0;
	    top_exit++;
	    act( AT_PLAIN, "A passage opens!", ch, NULL, NULL, TO_CHAR );
	    act( AT_PLAIN, "A passage opens!", ch, NULL, NULL, TO_ROOM );
	    return;
	}
	if ( IS_SET( obj->value[0], TRIG_UNLOCK )
	&&   IS_SET( pexit->exit_info, EX_LOCKED) )
	{
	    REMOVE_BIT(pexit->exit_info, EX_LOCKED);
	    act( AT_PLAIN, "You hear a faint click $T.", ch, NULL, txt, TO_CHAR );
	    act( AT_PLAIN, "You hear a faint click $T.", ch, NULL, txt, TO_ROOM );
	    if ( ( pexit_rev = pexit->rexit ) != NULL
	    &&   pexit_rev->to_room == ch->in_room )
		REMOVE_BIT( pexit_rev->exit_info, EX_LOCKED );
	    return;
	}
	if ( IS_SET( obj->value[0], TRIG_LOCK   )
	&&  !IS_SET( pexit->exit_info, EX_LOCKED) )
	{
	    SET_BIT(pexit->exit_info, EX_LOCKED);
	    act( AT_PLAIN, "You hear a faint click $T.", ch, NULL, txt, TO_CHAR );
	    act( AT_PLAIN, "You hear a faint click $T.", ch, NULL, txt, TO_ROOM );
	    if ( ( pexit_rev = pexit->rexit ) != NULL
	    &&   pexit_rev->to_room == ch->in_room )
		SET_BIT( pexit_rev->exit_info, EX_LOCKED );
	    return;
	}
	if ( IS_SET( obj->value[0], TRIG_OPEN   )
	&&   IS_SET( pexit->exit_info, EX_CLOSED) )
	{
	    REMOVE_BIT(pexit->exit_info, EX_CLOSED);
	    for ( rch = room->first_person; rch; rch = rch->next_in_room )
		act( AT_ACTION, "The $d opens.", rch, NULL, pexit->keyword, TO_CHAR );
	    if ( ( pexit_rev = pexit->rexit ) != NULL
	    &&   pexit_rev->to_room == ch->in_room )
	    {
		REMOVE_BIT( pexit_rev->exit_info, EX_CLOSED );
		/* bug here pointed out by Nick Gammon */
		for ( rch = pexit->to_room->first_person; rch; rch = rch->next_in_room )
		    act( AT_ACTION, "The $d opens.", rch, NULL, pexit_rev->keyword, TO_CHAR );
	    }
	    check_room_for_traps( ch, trap_door[edir]);
	    return;
	}
	if ( IS_SET( obj->value[0], TRIG_CLOSE   )
	&&  !IS_SET( pexit->exit_info, EX_CLOSED) )
	{
	    SET_BIT(pexit->exit_info, EX_CLOSED);
	    for ( rch = room->first_person; rch; rch = rch->next_in_room )
		act( AT_ACTION, "The $d closes.", rch, NULL, pexit->keyword, TO_CHAR );
	    if ( ( pexit_rev = pexit->rexit ) != NULL
	    &&   pexit_rev->to_room == ch->in_room )
	    {
		SET_BIT( pexit_rev->exit_info, EX_CLOSED );
		/* bug here pointed out by Nick Gammon */
		for ( rch = pexit->to_room->first_person; rch; rch = rch->next_in_room )
		    act( AT_ACTION, "The $d closes.", rch, NULL, pexit_rev->keyword, TO_CHAR );
	    }
	    check_room_for_traps( ch, trap_door[edir]);
	    return;
	}
    }
}

void do_mobmaster(CHAR_DATA *ch, char *argument)
{
    MOB_INDEX_DATA *mobmastertarget;
    char buf [MAX_STRING_LENGTH];
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];

    argument = one_argument(argument, arg1);
    argument = one_argument(argument, arg2);

    if (!strcmp(arg1, "check"))
    {
	    if (xIS_SET(ch->act, PLR_MOBM) || xIS_SET(ch->act, PLR_MOBM_EXPERT))
	    {
            mobmastertarget = get_mob_index(ch->mobmaster);
			if (mobmastertarget != NULL)
			{
			   pager_printf_color(ch, "You are to kill %s\n\r",mobmastertarget->short_descr);
			   pager_printf_color(ch, "You have %d minutes left.\n\r", ch->mobmticks);
			   return;
			}
	    }
	    else
	    {
		send_to_char("You aren't currently on a quest.\n\r",ch);
		return;
	    }
     }

     if (!strcmp(arg1, "quit"))
     {
		if (!xIS_SET(ch->act, PLR_MOBM) && !xIS_SET(ch->act, PLR_MOBM_EXPERT))
		{
		   pager_printf_color(ch, "You have to have a target before you can quit the MobMaster!\n\r");
		   return;
		}
        else if(xIS_SET(ch->act, PLR_MOBM))
		{
		   send_to_char("You quit your MobMaster quest...you may try again in 30 minutes.\n\r",ch);
		   xREMOVE_BIT(ch->act, PLR_MOBM);
		   ch->nextmobm = 30;
		   return;
		}
		else if(xIS_SET(ch->act, PLR_MOBM_EXPERT))
		{
			send_to_char("You quit your expert MobMaster quest. You may try again in 30 minutes.\n\r", ch);
			xREMOVE_BIT(ch->act, PLR_MOBM_EXPERT);
			ch->nextmobm = 30;
			extract_char(get_mob(ch->mobmaster), TRUE);
			return;
		}
     }		

     if (!strcmp(arg1, "start"))
     {
	if ( ch->level < 1 )
	{
	  pager_printf_color(ch, "&RYou may not quest until level 1.\n\r" );
	  return;
	}
	if ( IS_IMMORTAL(ch) ) // No need for immortals to do mobmaster quests -Darwin
	{
		pager_printf_color( ch, "&WYou may not engage in such mortal activities.\n\r" );
		return;
	}

    if (sysdata.DENY_NEW_PLAYERS == TRUE) 
    { 
        sprintf(buf, "&CReboot in the near future...try again after the reboot/hotboot.&w\n\r");
        send_to_char(buf, ch); 
        return; 
    } 

	if (xIS_SET(ch->act, PLR_MOBM))
	{
	    pager_printf_color(ch, "You already have a target.\n\r" );
	    return;
	}

	if(xIS_SET(ch->act, PLR_MOBM_EXPERT))
	{
		pager_printf_color(ch, "You already have a target.\n\r" );
		return;
	}

	if ( ch->mobmastercomplete < 400 && !strcmp(arg2, "expert"))
	{
	    pager_printf_color(ch, "You have not completed the maximum normal mobmasteries.\n\r" );
		pager_printf_color(ch, "You shouldn't try mobmaster start expert until you are experienced enough.\n\r");
	    return;
	}

	if ( ch->mobmastercomplete >= 400 && strcmp(arg2, "expert"))
	{
	    pager_printf_color(ch, "You have completed the maximum mobmasteries.\n\r" );
		pager_printf_color(ch, "You should try mobmaster start expert for another challenge.\n\r");
	    return;
	}

	if (ch->nextmobm > 0)
	{
	   pager_printf_color(ch, "You may MobMaster again in %d minutes.\n\r", ch->nextmobm );
	   return;
	}

	if(ch->mobmastercomplete >= 400 && !strcmp(arg2, "expert"))
	{
		get_targetmob_expert(ch);
		return;
	}

	get_targetmob(ch);
	return;
    }
    else
    {
       send_to_char("Syntax: mobmaster start, mobmaster quit, mobmaster start expert or mobmaster check.\n\r",ch);
       return;
    }
}


   
void get_targetmob(CHAR_DATA *ch)
{
    CHAR_DATA *victim;
    MOB_INDEX_DATA *vsearch;
    long mcounter;
    int mob_vnum;

	/* This portion taken from Vassago's Mob Quest Generator and modified
	slightly to suit Mobmaster code) */

	for (mcounter = 0; mcounter < 99999; mcounter ++) 
	{ 
		mob_vnum = number_range(100, 32600); 
        
		if ( (vsearch = get_mob_index(mob_vnum) ) != NULL  
			&& (vsearch->vnum < 10300 || vsearch->vnum > 10499) 
			&& (vsearch->vnum < 7648 || vsearch->vnum > 7999) )
		{		
			if ( (vsearch->level <= (ch->mobmastercomplete + 3)) 
				&& vsearch->level >= UMIN( ((ch->mobmastercomplete / 3) +1), 64 )
				&& !xIS_SET(vsearch->act,ACT_PACIFIST)
				&& !xIS_SET(vsearch->act,ACT_IMMORTAL)
				&& !xIS_SET(vsearch->act, ACT_PET)) 
			break;
			else 
				vsearch = NULL;
		}
    }
 
    if ( vsearch == NULL 
		|| ( victim = get_char_world( ch, vsearch->player_name ) ) == NULL 
		|| !IS_NPC(victim)
		|| IS_SET(victim->in_room->room_flags, ROOM_SAFE))
    {
		pager_printf_color( ch, "&zCould not find a suitable target.\n\r" );
                ch->nextmobm = number_fuzzy(4);
		if(IS_IMMORTAL(ch))
		   ch->nextmobm = 0;
		return;
    }
	ch->mobmticks = 30;
	xSET_BIT(ch->act, PLR_MOBM);
	pager_printf_color( ch, "&wYou are to kill &c%s&w.\n\r", victim->short_descr );
	pager_printf_color( ch, "&wYou have &W%d&w minutes to complete this task.\n\r", ch->mobmticks );
	ch->mobmaster = victim->pIndexData->vnum;

    return;
}

void get_targetmob_expert(CHAR_DATA *ch)
{
    CHAR_DATA *victim;
    MOB_INDEX_DATA *vsearch;
    long mcounter;
    int mob_vnum;

	/* This portion taken from Vassago's Mob Quest Generator and modified
	slightly to suit Mobmaster code) */

	/* This has been altered to only provide very high level mobs for
	 * expert mode mobmasteries -Darwin
	 */

	for (mcounter = 0; mcounter < 99999; mcounter ++) 
	{ 
		mob_vnum = number_range(100, 32600); 
        
		if((vsearch = get_mob_index(mob_vnum)) != NULL  && (vsearch->vnum < 10300 || vsearch->vnum > 10499))
		{		
			if((vsearch->level >= 60 ) 
				&& !xIS_SET(vsearch->act,ACT_PACIFIST) 
				&& !xIS_SET(vsearch->act,ACT_IMMORTAL)
				&& !xIS_SET(vsearch->act, ACT_PET))
				break;
			else
				vsearch = NULL;
		}
	}
 
    if ( vsearch == NULL 
		|| ( victim = get_char_world( ch, vsearch->player_name ) ) == NULL 
		|| !IS_NPC(victim)
		|| IS_SET(victim->in_room->room_flags, ROOM_SAFE))
    {
		pager_printf_color( ch, "&zCould not find a suitable target.\n\r" );
        ch->nextmobm = number_fuzzy(4);
		return;
    }
	ch->mobmticks = 45;
	xSET_BIT(ch->act, PLR_MOBM_EXPERT);
	pager_printf_color( ch, "&wYou are to kill &c%s&w.\n\r", victim->short_descr );
	pager_printf_color( ch, "&wYou have &W%d&w minutes to complete this task.\n\r", ch->mobmticks );
	ch->mobmaster = victim->pIndexData->vnum;

	/* lets increase the difficulty of the mob -Darwin */
	victim->max_hit *= 1.5;
	victim->hit = victim->max_hit;
	victim->hitroll += 100;
	victim->damroll += 100;
	xSET_BIT(victim->act, ACT_ASTRALBLOCK);
	if(xIS_SET(victim->act, ACT_SENTINEL)) xREMOVE_BIT(victim->act, ACT_SENTINEL);
	if(xIS_SET(victim->act, ACT_STAY_AREA)) xREMOVE_BIT(victim->act, ACT_STAY_AREA);
	start_hating(victim, ch);
	start_hunting(victim, ch);

    return;
}


void mobmaster_update(void)
{
    CHAR_DATA *ch;
	DESCRIPTOR_DATA *d, *d_next;
	
	// change this to just loop through descriptors since
	// they should be the only characters able to mobmaster
	for( d = first_descriptor; d != NULL; d = d_next )
    {
	    if ( d == d->next )
	    {
			bug( "descriptor_loop: loop found & fixed" );
			d->next = NULL;
	    }
		d_next = d->next;
		ch = d->character;
		
		if(!ch)
			continue;
		
		if (IS_NPC(ch))
		{
			// just to make sure no npc's in descriptor list
			bug( "mobmaster_update: NPC found in descriptor loop" );
			continue;
		}
		
		if (ch->nextmobm > 0) 
		{
			ch->nextmobm--;
			if (ch->nextmobm == 0)
			{
				pager_printf_color( ch, "&WYou may request another &Cmobmaster&W target.&D\n\r" );
				return;
			}
		}
        else if (xIS_SET(ch->act,PLR_MOBM) || xIS_SET(ch->act, PLR_MOBM_EXPERT))
        {
			if (--ch->mobmticks <= 0)
			{
				ch->nextmobm = 20;
				pager_printf_color( ch, "You have failed!\n\r" );
				pager_printf_color( ch, "You may quest again in %d minutes.\n\r",ch->nextmobm);
				if(xIS_SET(ch->act, PLR_MOBM))
					xREMOVE_BIT(ch->act, PLR_MOBM);
				else if(xIS_SET(ch->act, PLR_MOBM_EXPERT))
				{
					xREMOVE_BIT(ch->act, PLR_MOBM_EXPERT);
					extract_char(get_mob(ch->mobmaster), TRUE);
				}
			}
        }
    }
    return;
}


void do_pull( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Pull what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( ( obj = get_obj_here( ch, arg ) ) == NULL )
    {
	act( AT_PLAIN, "I see no $T here.", ch, NULL, arg, TO_CHAR );
	return;
    }

    pullorpush( ch, obj, TRUE );
}

void do_push( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Push what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( ( obj = get_obj_here( ch, arg ) ) == NULL )
    {
	act( AT_PLAIN, "I see no $T here.", ch, NULL, arg, TO_CHAR );
	return;
    }

    pullorpush( ch, obj, FALSE );
}

void do_rap( CHAR_DATA *ch, char *argument )
{
        EXIT_DATA *pexit;
        char       arg [ MAX_INPUT_LENGTH ];

        one_argument( argument, arg );
 
        if ( arg[0] == '\0' )
        {
          send_to_char( "Rap on what?\n\r", ch );
          return;
        }
        if ( ch->fighting )
        {
          send_to_char( "You have better things to do with your hands right now.\n\r", ch );
          return;
        }
        if ( ( pexit = find_door( ch, arg, FALSE ) ) != NULL )
        {
          ROOM_INDEX_DATA *to_room;
          EXIT_DATA       *pexit_rev;
          char            *keyword;
          if ( !IS_SET( pexit->exit_info, EX_CLOSED ) )
          {
            send_to_char( "Why knock?  It's open.\n\r", ch );
            return;
          }
          if ( IS_SET( pexit->exit_info, EX_SECRET ) )
            keyword = "wall";
          else
            keyword = pexit->keyword;
          act( AT_ACTION, "You rap loudly on the $d.", ch, NULL, keyword, TO_CHAR );
          act( AT_ACTION, "$n raps loudly on the $d.", ch, NULL, keyword, TO_ROOM );
          if ( (to_room = pexit->to_room) != NULL
          &&   (pexit_rev = pexit->rexit) != NULL 
          &&    pexit_rev->to_room        == ch->in_room )
          {
            CHAR_DATA *rch;
            for ( rch = to_room->first_person; rch; rch = rch->next_in_room )
            {
              act( AT_ACTION, "Someone raps loudly from the other side of the $d.",
                rch, NULL, pexit_rev->keyword, TO_CHAR );
            }
          }
        }
        else
        {
          act( AT_ACTION, "You make knocking motions through the air.",
	    ch, NULL, NULL, TO_CHAR );
          act( AT_ACTION, "$n makes knocking motions through the air.",
	    ch, NULL, NULL, TO_ROOM );
        }
        return;
}

/* pipe commands (light, tamp, smoke) by Thoric */
void do_tamp( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *pipe;
    char arg[MAX_INPUT_LENGTH];

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Tamp what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( (pipe = get_obj_carry( ch, arg )) == NULL )
    {
	send_to_char( "You aren't carrying that.\n\r", ch );
	return;
    }
    if ( pipe->item_type != ITEM_PIPE )
    {
	send_to_char( "You can't tamp that.\n\r", ch );
	return;
    }
    if ( !IS_SET( pipe->value[3], PIPE_TAMPED ) )
    {
	act( AT_ACTION, "You gently tamp $p.", ch, pipe, NULL, TO_CHAR );
	act( AT_ACTION, "$n gently tamps $p.", ch, pipe, NULL, TO_ROOM );
	SET_BIT( pipe->value[3], PIPE_TAMPED );
	return;
    }
    send_to_char( "It doesn't need tamping.\n\r", ch );
}

void do_smoke( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *pipe;
    char arg[MAX_INPUT_LENGTH];

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Smoke what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( (pipe = get_obj_carry( ch, arg )) == NULL )
    {
	send_to_char( "You aren't carrying that.\n\r", ch );
	return;
    }
    if ( pipe->item_type != ITEM_PIPE )
    {
	act( AT_ACTION, "You try to smoke $p... but it doesn't seem to work.", ch, pipe, NULL, TO_CHAR );
	act( AT_ACTION, "$n tries to smoke $p... (I wonder what $e's been putting in $s pipe?)", ch, pipe, NULL, TO_ROOM );
	return;
    }
    if ( !IS_SET( pipe->value[3], PIPE_LIT ) )
    {
	act( AT_ACTION, "You try to smoke $p, but it's not lit.", ch, pipe, NULL, TO_CHAR );
	act( AT_ACTION, "$n tries to smoke $p, but it's not lit.", ch, pipe, NULL, TO_ROOM );
	return;
    }
    if ( pipe->value[1] > 0 )
    {
	if ( !oprog_use_trigger( ch, pipe, NULL, NULL, NULL ) )
	{
	   act( AT_ACTION, "You draw thoughtfully from $p.", ch, pipe, NULL, TO_CHAR );
	   act( AT_ACTION, "$n draws thoughtfully from $p.", ch, pipe, NULL, TO_ROOM );
	}

	if ( IS_VALID_HERB( pipe->value[2] ) && pipe->value[2] < top_herb )
	{
	    int sn		= pipe->value[2] + TYPE_HERB;
	    SKILLTYPE *skill	= get_skilltype( sn );

	    WAIT_STATE( ch, skill->beats );
	    if ( skill->spell_fun )
		obj_cast_spell( sn, UMIN(skill->min_level, ch->level),
			ch, ch, NULL );
	    if ( obj_extracted( pipe ) )
		return;
	}
	else
	    bug( "do_smoke: bad herb type %d", pipe->value[2] );

	SET_BIT( pipe->value[3], PIPE_HOT );
	if ( --pipe->value[1] < 1 )
	{
	   REMOVE_BIT( pipe->value[3], PIPE_LIT );
	   SET_BIT( pipe->value[3], PIPE_DIRTY );
	   SET_BIT( pipe->value[3], PIPE_FULLOFASH );
	}
    }
}

void do_light( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *pipe;
    char arg[MAX_INPUT_LENGTH];

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
	send_to_char( "Light what?\n\r", ch );
	return;
    }

    if ( ms_find_obj(ch) )
	return;

    if ( (pipe = get_obj_carry( ch, arg )) == NULL )
    {
	send_to_char( "You aren't carrying that.\n\r", ch );
	return;
    }
    if ( pipe->item_type != ITEM_PIPE )
    {
	send_to_char( "You can't light that.\n\r", ch );
	return;
    }
    if ( !IS_SET( pipe->value[3], PIPE_LIT ) )
    {
	if ( pipe->value[1] < 1 )
	{
	  act( AT_ACTION, "You try to light $p, but it's empty.", ch, pipe, NULL, TO_CHAR );
	  act( AT_ACTION, "$n tries to light $p, but it's empty.", ch, pipe, NULL, TO_ROOM );
	  return;
	}
	act( AT_ACTION, "You carefully light $p.", ch, pipe, NULL, TO_CHAR );
	act( AT_ACTION, "$n carefully lights $p.", ch, pipe, NULL, TO_ROOM );
	SET_BIT( pipe->value[3], PIPE_LIT );
	return;
    }
    send_to_char( "It's already lit.\n\r", ch );
}

/*
 * Apply a salve/ointment					-Thoric
 * Support for applying to others.  Pkill concerns dealt with elsewhere.
 */
void do_apply( CHAR_DATA *ch, char *argument )
{

    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_DATA *salve;
    OBJ_DATA *obj;
    ch_ret    retcode;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    if ( arg1[0] == '\0' )
    {
	send_to_char( "Apply what?\n\r", ch );
	return;
    }
    if ( ch->fighting )
    {
	send_to_char( "You're too busy fighting ...\n\r", ch );
	return;
    }
    if ( ms_find_obj(ch) )
	return;
    if ( ( salve = get_obj_carry( ch, arg1 ) ) == NULL )
    {
	send_to_char( "You do not have that.\n\r", ch );
	return;
    }

    obj = NULL;
    if ( arg2[0] == '\0' )
	victim = ch;
    else
    {
	if ( ( victim = get_char_room ( ch, arg2 ) ) == NULL
	&&   ( obj    = get_obj_here  ( ch, arg2 ) ) == NULL )
	{
	    send_to_char( "Apply it to what or who?\n\r", ch );
	    return;
	}
   }

   /* apply salve to another object */
   if ( obj )
   {
	send_to_char( "You can't do that... yet.\n\r", ch );
	return;
   }

   if ( victim->fighting )
   {
	send_to_char( "Wouldn't work very well while they're fighting ...\n\r", ch );
	return;
   }

   if ( salve->item_type != ITEM_SALVE )
   {
	if ( victim == ch )
	{
	    act( AT_ACTION, "$n starts to rub $p on $mself...", ch, salve, NULL, TO_ROOM );
            act( AT_ACTION, "You try to rub $p on yourself...", ch, salve, NULL, TO_CHAR );
	}
	else
	{
	    act( AT_ACTION, "$n starts to rub $p on $N...", ch, salve, victim, TO_NOTVICT );
	    act( AT_ACTION, "$n starts to rub $p on you...", ch, salve, victim, TO_VICT );
	    act( AT_ACTION, "You try to rub $p on $N...", ch, salve, victim, TO_CHAR );
	}
        return;
    }        
    separate_obj( salve );
    --salve->value[1];

    if ( !oprog_use_trigger( ch, salve, NULL, NULL, NULL ) )
    {
	if ( !salve->action_desc || salve->action_desc[0]=='\0' )
	{
	    if ( salve->value[1] < 1 )
	    {
		if ( victim != ch )
		{
		    act( AT_ACTION, "$n rubs the last of $p onto $N.",
			ch, salve, victim, TO_NOTVICT );
		    act( AT_ACTION, "$n rubs the last of $p onto you.",
			ch, salve, victim, TO_VICT );
		    act( AT_ACTION, "You rub the last of $p onto $N.",
			ch, salve, victim, TO_CHAR );
		}
		else
		{
		    act( AT_ACTION, "You rub the last of $p onto yourself.",
			ch, salve, NULL, TO_CHAR );
		    act( AT_ACTION, "$n rubs the last of $p onto $mself.",
			ch, salve, NULL, TO_ROOM );
		}
	    }
	    else
	    {
		if ( victim != ch )
        	{
		    act( AT_ACTION, "$n rubs $p onto $N.",
			ch, salve, victim, TO_NOTVICT );
		    act( AT_ACTION, "$n rubs $p onto you.",
			ch, salve, victim, TO_VICT );
		    act( AT_ACTION, "You rub $p onto $N.",
			ch, salve, victim, TO_CHAR );
		}
		else
		{
		    act( AT_ACTION, "You rub $p onto yourself.",
			ch, salve, NULL, TO_CHAR );
		    act( AT_ACTION, "$n rubs $p onto $mself.",
			ch, salve, NULL, TO_ROOM );
		}                                   
	    }
	}
	else
	    actiondesc( ch, salve, NULL ); 
    }

    WAIT_STATE( ch, salve->value[3] );
    retcode = obj_cast_spell( salve->value[4], salve->value[0], ch, victim, NULL );
    if ( retcode == rNONE )
	retcode = obj_cast_spell( salve->value[5], salve->value[0], ch, victim, NULL );
    if ( retcode == rCHAR_DIED || retcode == rBOTH_DIED )
    {
	bug( "do_apply:  char died", 0 );
        return;
    }    

    if ( !obj_extracted(salve) && salve->value[1] <= 0 )
	extract_obj( salve );
    return;
}

void do_advancetier( CHAR_DATA *ch, char *argument )
{
	char buf[MAX_STRING_LENGTH];
	
	if( IS_NPC(ch) )
	{
		send_to_char("Huh?\n\r", ch);
		return;
	}

	if( ch->level < 50 )
	{
		send_to_pager("You have to be level 50 to advance to the next tier.\n\r", ch);
		return;
	}

	if( ch->class != ch->dualclass )
	{
		send_to_pager("Dualclass characters cannot raise to another tier.\n\r", ch);
		return;
	}

	if( ch->pcdata->tier > 1 )
	{
		send_to_pager("You have already advanced to the next tier!\n\r", ch);
		return;
	}

	if( ch->gold < 500000 )
	{
		send_to_pager("You need at least 500,000 gold to advance to the next tier.\n\r", ch);
		return;
	}

	if( ch->level > 50 )
	{
		send_to_pager("Immortals may not advance tiers.\n\r", ch);
		return;
	}

	if(	(ch->class == CLASS_WARRIOR && ch->dualclass == CLASS_WARRIOR && ch->level == 50)	||
		(ch->class == CLASS_RANGER && ch->dualclass == CLASS_RANGER && ch->level == 50)		||
		(ch->class == CLASS_MONK && ch->dualclass == CLASS_MONK && ch->level == 50)			)
	{
		ch->class = 12;
		//ch->dualclass = 12;
		ch->level = 2;
		ch->gold -= 500000;
		xSET_BIT(ch->act, PLR_TIER);
		ch->hit = ch->max_hit;
		ch->mana = ch->max_mana;
		ch->move = ch->max_move;
		ch->practice += 20;
		ch->tierexp = ch->exp + ch->tierexp;
		ch->exp = 130;
		ch->pcdata->tier += 1;
		sprintf( buf, "the %s", title_table[ch->class][ch->level][ch->sex == SEX_FEMALE ? 1 : 0] );
		set_title( ch, buf );
		send_to_pager("You have advanced to the next tier!\n\r", ch);
		send_to_pager("The gods have restored you!\n\r", ch);
		sprintf(buf, "[INFO] %s has become a %s!", ch->name, class_table[ch->class]->who_name );
		echo_to_all(AT_YELLOW, buf, ECHOTAR_ALL);
		return;
	}


	if( (ch->class == CLASS_DIABOLIST && ch->dualclass == CLASS_DIABOLIST && ch->level == 50)	||
		(ch->class == CLASS_CLERIC && ch->dualclass == CLASS_CLERIC && ch->level == 50)		||
		(ch->class == CLASS_SHAMAN && ch->dualclass == CLASS_SHAMAN && ch->level == 50)		)
	{ 
		ch->class = 13; 
		//ch->dualclass = 13;
		ch->level = 2; 
		ch->gold -= 500000; 
		xSET_BIT(ch->act, PLR_TIER);
		ch->hit = ch->max_hit;   
		ch->mana = ch->max_mana;
		ch->move = ch->max_move;
		ch->practice += 20;
		ch->tierexp = ch->exp + ch->tierexp;
		ch->exp = 150;
		ch->pcdata->tier += 1;
		sprintf( buf, "the %s", title_table[ch->class][ch->level][ch->sex == SEX_FEMALE ? 1 : 0] );
		set_title( ch, buf );
		send_to_pager("You have advanced to the next tier!\n\r", ch);
		send_to_pager("The gods have restored you!\n\r", ch);
		sprintf(buf, "[INFO] %s has become a %s!", ch->name, class_table[ch->class]->who_name );
		echo_to_all(AT_YELLOW, buf, ECHOTAR_ALL);
		return;
	}

	if( (ch->class == CLASS_THIEF && ch->dualclass == CLASS_THIEF && ch->level == 50)		||
		(ch->class == CLASS_THUG && ch->dualclass == CLASS_THUG && ch->level == 50)		||
		(ch->class == CLASS_JESTER && ch->dualclass == CLASS_JESTER && ch->level == 50)	)
	{ 
		ch->class = 14;
		//ch->dualclass = 14;
		ch->level = 2;
		ch->gold -= 500000; 
		xSET_BIT(ch->act, PLR_TIER);
		ch->hit = ch->max_hit;
		ch->mana = ch->max_mana;
		ch->move = ch->max_move;
		ch->practice += 20;
		ch->tierexp = ch->exp + ch->tierexp;
		ch->exp = 130; 
		ch->pcdata->tier += 1;
		sprintf( buf, "the %s", title_table[ch->class][ch->level][ch->sex == SEX_FEMALE ? 1 : 0] );
		set_title( ch, buf ); 
		send_to_pager("You have advanced to the next tier!\n\r", ch);
		send_to_pager("The gods have restored you!\n\r", ch);
		sprintf(buf, "[INFO] %s has become a %s!", ch->name, class_table[ch->class]->who_name );
		echo_to_all(AT_YELLOW, buf, ECHOTAR_ALL);
		return;
	} 

	if( (ch->class == CLASS_MAGE && ch->dualclass == CLASS_MAGE && ch->level == 50)			||
		(ch->class == CLASS_DRUID && ch->dualclass == CLASS_DRUID && ch->level == 50)			||
		(ch->class == CLASS_CONJURER && ch->dualclass == CLASS_CONJURER && ch->level == 50)	)
	{ 
		ch->class = 15; 
		//ch->dualclass = 15;
		ch->level = 2;
		ch->gold -= 500000;
		xSET_BIT(ch->act, PLR_TIER);
		ch->hit = ch->max_hit;
		ch->mana = ch->max_mana; 
		ch->move = ch->max_move;
		ch->practice += 20;
		ch->tierexp = ch->exp + ch->tierexp;
		ch->exp = 150;   
		ch->pcdata->tier += 1;
		sprintf( buf, "the %s", title_table[ch->class][ch->level][ch->sex == SEX_FEMALE ? 1 : 0] );
		set_title( ch, buf );
		send_to_pager("You have advanced to the next tier!\n\r", ch);
		send_to_pager("The gods have restored you!\n\r", ch);
		sprintf(buf, "[INFO] %s has become an %s!", ch->name, class_table[ch->class]->who_name );
		echo_to_all(AT_YELLOW, buf, ECHOTAR_ALL);
		return;
	}

	return;
}

/* generate an action description message */
void actiondesc( CHAR_DATA *ch, OBJ_DATA *obj, void *vo )
{
    char charbuf[MAX_STRING_LENGTH];
    char roombuf[MAX_STRING_LENGTH];
    char *srcptr = obj->action_desc;
    char *charptr = charbuf;
    char *roomptr = roombuf;
    const char *ichar = "You";
    const char *iroom = "Someone";

while ( *srcptr != '\0' )
{
  if ( *srcptr == '$' ) 
  {
    srcptr++;
    switch ( *srcptr )
    {
      case 'e':
        ichar = "you";
        iroom = "$e";
        break;

      case 'm':
        ichar = "you";
        iroom = "$m";
        break;

      case 'n':
        ichar = "you";
        iroom = "$n";
        break;

      case 's':
        ichar = "your";
        iroom = "$s";
        break;

      /*case 'q':
        iroom = "s";
        break;*/

      default: 
        srcptr--;
        *charptr++ = *srcptr;
        *roomptr++ = *srcptr;
        break;
    }
  }
  else if ( *srcptr == '%' && *++srcptr == 's' ) 
  {
    ichar = "You";
    iroom = IS_NPC( ch ) ? ch->short_descr : ch->name;
  }
  else
  {
    *charptr++ = *srcptr;
    *roomptr++ = *srcptr;
    srcptr++;
    continue;
  }

  while ( ( *charptr = *ichar ) != '\0' )
  {
    charptr++;
    ichar++;
  }

  while ( ( *roomptr = *iroom ) != '\0' )
  {
    roomptr++;
    iroom++;
  }
  srcptr++;
}

*charptr = '\0';
*roomptr = '\0';

/*
sprintf( buf, "Charbuf: %s", charbuf );
log_string_plus( buf, LOG_HIGH, LEVEL_LESSER ); 
sprintf( buf, "Roombuf: %s", roombuf );
log_string_plus( buf, LOG_HIGH, LEVEL_LESSER ); 
*/

switch( obj->item_type )
{
  case ITEM_BLOOD:
  case ITEM_FOUNTAIN:
    act( AT_ACTION, charbuf, ch, obj, ch, TO_CHAR );
    act( AT_ACTION, roombuf, ch, obj, ch, TO_ROOM );
    return;

  case ITEM_DRINK_CON:
    act( AT_ACTION, charbuf, ch, obj, liq_table[obj->value[2]].liq_name, TO_CHAR );
    act( AT_ACTION, roombuf, ch, obj, liq_table[obj->value[2]].liq_name, TO_ROOM );
    return;

  case ITEM_PIPE:
    return;

  case ITEM_ARMOR:
  case ITEM_ARTARMOR:
  case ITEM_WEAPON:
  case ITEM_ARTWEAPON:
  case ITEM_LIGHT:
  case ITEM_ARTLIGHT:
    return;
 
  case ITEM_COOK:
  case ITEM_FOOD:
  case ITEM_PILL:
    act( AT_ACTION, charbuf, ch, obj, ch, TO_CHAR );
    act( AT_ACTION, roombuf, ch, obj, ch, TO_ROOM );
    return;

  default:
    return;
}
return;
}

/*
 * Extended Bitvector Routines					-Thoric
 */

/* check to see if the extended bitvector is completely empty */
bool ext_is_empty( EXT_BV *bits )
{
    int x;

    for ( x = 0; x < XBI; x++ )
	if ( bits->bits[x] != 0 )
	    return FALSE;

    return TRUE;
}

void ext_clear_bits( EXT_BV *bits )
{
    int x;

    for ( x = 0; x < XBI; x++ )
	bits->bits[x] = 0;
}

/* for use by xHAS_BITS() -- works like IS_SET() */
int ext_has_bits( EXT_BV *var, EXT_BV *bits )
{
    int x, bit;

    for ( x = 0; x < XBI; x++ )
	if ( (bit=(var->bits[x] & bits->bits[x])) != 0 )
	    return bit;

    return 0;
}

/* for use by xSAME_BITS() -- works like == */
bool ext_same_bits( EXT_BV *var, EXT_BV *bits )
{
    int x;

    for ( x = 0; x < XBI; x++ )
	if ( var->bits[x] != bits->bits[x] )
	    return FALSE;

    return TRUE;
}

/* for use by xSET_BITS() -- works like SET_BIT() */
void ext_set_bits( EXT_BV *var, EXT_BV *bits )
{
    int x;

    for ( x = 0; x < XBI; x++ )
	var->bits[x] |= bits->bits[x];
}

/* for use by xREMOVE_BITS() -- works like REMOVE_BIT() */
void ext_remove_bits( EXT_BV *var, EXT_BV *bits )
{
    int x;

    for ( x = 0; x < XBI; x++ )
	var->bits[x] &= ~(bits->bits[x]);
}

/* for use by xTOGGLE_BITS() -- works like TOGGLE_BIT() */
void ext_toggle_bits( EXT_BV *var, EXT_BV *bits )
{
    int x;

    for ( x = 0; x < XBI; x++ )
	var->bits[x] ^= bits->bits[x];
}

/*
 * Read an extended bitvector from a file.			-Thoric
 */
EXT_BV fread_bitvector( FILE *fp )
{
    EXT_BV ret;
    int c, x = 0;
    int num = 0;
    
    memset( &ret, '\0', sizeof(ret) );
    for ( ;; )
    {
	num = fread_number(fp);
	if ( x < XBI )
	    ret.bits[x] = num;
	++x;
	if ( (c=getc(fp)) != '&' )
	{
	    ungetc(c, fp);
	    break;
	}
    }

    return ret;
}

/* return a string for writing a bitvector to a file */
char *print_bitvector( EXT_BV *bits )
{
    static char buf[XBI * 12];
    char *p = buf;
    int x, cnt = 0;

    for ( cnt = XBI-1; cnt > 0; cnt-- )
	if ( bits->bits[cnt] )
	    break;
    for ( x = 0; x <= cnt; x++ )
    {
	sprintf(p, "%d", bits->bits[x]);
	p += strlen(p);
	if ( x < cnt )
	    *p++ = '&';
    }
    *p = '\0';

    return buf;
}

/*
 * Write an extended bitvector to a file			-Thoric
 */
void fwrite_bitvector( EXT_BV *bits, FILE *fp )
{
    fputs( print_bitvector(bits), fp );
}


EXT_BV meb( int bit )
{
    EXT_BV bits;

    xCLEAR_BITS(bits);
    if ( bit >= 0 )
	xSET_BIT(bits, bit);

    return bits;
}


EXT_BV multimeb( int bit, ... )
{
    EXT_BV bits;
    va_list param;
    int b;
    
    xCLEAR_BITS(bits);
    if ( bit < 0 )
	return bits;

    xSET_BIT(bits, bit);

    va_start(param, bit);

    while ((b = va_arg(param, int)) != -1)
	xSET_BIT(bits, b);

    va_end(param);

    return bits;
}


#ifdef WIN32

/* routines not in Windows runtime libraries */

void gettimeofday(struct timeval *tv, struct timezone *tz)
{
    tv->tv_sec = time (0);
    tv->tv_usec = 0;
}

/* directory parsing stuff */

DIR * opendir (char * sDirName)
{
    DIR * dp = malloc (sizeof (DIR));

    dp->hDirectory = 0;      /* if zero, we must do a FindFirstFile */
    strcpy (dp->sDirName, sDirName);  /* remember for FindFirstFile */
    return dp;
}

struct dirent * readdir (DIR * dp)
{

    /* either read the first entry, or the next entry */
    do
    {
	if (dp->hDirectory == 0)
	{
	    dp->hDirectory = FindFirstFile (dp->sDirName, &dp->Win32FindData);
	    if (dp->hDirectory == INVALID_HANDLE_VALUE)
		return NULL;
	}
	else
	if (!FindNextFile (dp->hDirectory, &dp->Win32FindData))
	    return NULL;

	/* skip directories */

    } while (dp->Win32FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

    /* make a copy of the name string */
    dp->dirinfo.d_name = dp->Win32FindData.cFileName;

/* return a pointer to the DIR structure */

    return &dp->dirinfo;
}

void closedir(DIR * dp)
{
    if (dp->hDirectory)
	FindClose (dp->hDirectory);
    free (dp);
}

#endif

void do_task( CHAR_DATA * ch, char *argument )
{
  if(!IS_NPC(ch)) call_lua (ch, "task", argument); 
}

void do_whereis( CHAR_DATA *ch, char *argument )
{
  if(!IS_NPC(ch)) call_lua (ch, "whereis", argument);
}
