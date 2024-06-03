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
 *			Specific object creation module			    *
 ****************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"



/*
 * Make a fire.
 */
void make_fire(ROOM_INDEX_DATA *in_room, sh_int timer)
{
    OBJ_DATA *fire;

    fire = create_object( get_obj_index( OBJ_VNUM_FIRE ), 0 );
    fire->timer = number_fuzzy(timer);
    obj_to_room( fire, in_room );
    return;
}

/*
 * Make a trap.
 */
OBJ_DATA *make_trap(int v0, int v1, int v2, int v3)
{
    OBJ_DATA *trap;

    trap = create_object( get_obj_index( OBJ_VNUM_TRAP ), 0 );
    trap->timer = 0;
    trap->value[0] = v0;
    trap->value[1] = v1;
    trap->value[2] = v2;
    trap->value[3] = v3;
    return trap;
}


/*
 * Turn an object into scraps.		-Thoric
 */
void make_scraps( OBJ_DATA *obj )
{
  char buf[MAX_STRING_LENGTH];
  OBJ_DATA  *scraps, *tmpobj;
  CHAR_DATA *ch = NULL;

  separate_obj( obj );
  scraps	= create_object( get_obj_index( OBJ_VNUM_SCRAPS ), 0 );
  scraps->timer = number_range( 5, 15 );

  /* don't make scraps of scraps of scraps of ... */
  if ( obj->pIndexData->vnum == OBJ_VNUM_SCRAPS )
  {
     STRFREE( scraps->short_descr );
     scraps->short_descr = STRALLOC( "some debris" );
     STRFREE( scraps->description );
     scraps->description = STRALLOC( "Bits of debris lie on the ground here." );
  }
  else
  {
     sprintf( buf, scraps->short_descr, obj->short_descr );
     STRFREE( scraps->short_descr );
     scraps->short_descr = STRALLOC( buf );
     sprintf( buf, scraps->description, obj->short_descr );
     STRFREE( scraps->description );
     scraps->description = STRALLOC( buf );
  }

  if ( obj->carried_by )
  {
    act( AT_OBJECT, "$p falls to the ground in scraps!",
		  obj->carried_by, obj, NULL, TO_CHAR );
    if ( obj == get_eq_char( obj->carried_by, WEAR_WIELD )
    &&  (tmpobj = get_eq_char( obj->carried_by, WEAR_DUAL_WIELD)) != NULL )
       tmpobj->wear_loc = WEAR_WIELD;

    obj_to_room( scraps, obj->carried_by->in_room);
  }
  else
  if ( obj->in_room )
  {
    if ( (ch = obj->in_room->first_person ) != NULL )
    {
      act( AT_OBJECT, "$p is reduced to little more than scraps.",
	   ch, obj, NULL, TO_ROOM );
      act( AT_OBJECT, "$p is reduced to little more than scraps.",
	   ch, obj, NULL, TO_CHAR );
    }
    obj_to_room( scraps, obj->in_room);
  }
  if ( (obj->item_type == ITEM_CONTAINER || obj->item_type == ITEM_KEYRING
  ||    obj->item_type == ITEM_QUIVER    || obj->item_type == ITEM_CORPSE_PC)
  &&    obj->first_content )
  {
    if ( ch && ch->in_room )
    {
	act( AT_OBJECT, "The contents of $p fall to the ground.",
	   ch, obj, NULL, TO_ROOM );
	act( AT_OBJECT, "The contents of $p fall to the ground.",
	   ch, obj, NULL, TO_CHAR );
    }
    if ( obj->carried_by )
	empty_obj( obj, NULL, obj->carried_by->in_room );
    else
    if ( obj->in_room )
	empty_obj( obj, NULL, obj->in_room );
    else
    if ( obj->in_obj )
	empty_obj( obj, obj->in_obj, NULL );
  }
  extract_obj( obj );
}

bool iskeeper( CHAR_DATA *ch);
/*
 * Make a corpse out of a character.
 */
void make_corpse( CHAR_DATA *ch, CHAR_DATA *killer )
{
    char buf[MAX_STRING_LENGTH];
    OBJ_DATA *corpse = NULL;
    OBJ_DATA *obj;
    OBJ_DATA *obj_next;
	OBJ_DATA *locker = NULL;
    char *name = NULL;
	bool fkeeper = FALSE;

    if ( IS_NPC(ch) )
    {
		if(!xIS_SET(ch->act, ACT_NO_CORPSE))
		{
			name		= ch->short_descr;
			corpse		= create_object(get_obj_index(OBJ_VNUM_CORPSE_NPC), 0);
			corpse->timer	= 6;
			corpse->value[3]  = 100;  /* So the slice skill will work */
			corpse->value[4]  = ch->level;
			corpse->value[5]  = ch->race;
			corpse->weight = (int)ch->level*2; // make corpse weight twice the npc's level
											   // this will be used for job skills later -Darwin
				fkeeper = iskeeper(ch);

			if ( ch->gold > 0 )
			{
				if ( ch->in_room )
				{
				  ch->in_room->area->gold_looted += ch->gold;
				  sysdata.global_looted += ch->gold/100;
				}
				obj_to_obj( create_money( ch->gold ), corpse );
				ch->gold = 0;
			}

		/* Cannot use these!  They are used.
			corpse->value[0] = (int)ch->pIndexData->vnum;
			corpse->value[1] = (int)ch->max_hit;
		*/
		/*	Using corpse cost to cheat, since corpses not sellable */
			corpse->cost     = (-(int)ch->pIndexData->vnum);
			corpse->value[2] = corpse->timer;
            
            if(xIS_SET(ch->act, ACT_PET) && ch->master)
            {
                corpse->timer *= 3;
                corpse->value[0] = ch->master->pcdata->pc_id;
                corpse->value[1] = ch->level;
                corpse->value[2] = ch->exp;
                corpse->value[3] = ch->max_hit;
                corpse->value[4] = ch->alignment;
                corpse->value[5] = ch->perm_str;
                corpse->value[6] = ch->perm_int;
                corpse->value[7] = ch->perm_wis;
                corpse->value[8] = ch->perm_dex;
                corpse->value[9] = ch->perm_con;
                corpse->value[10] = ch->perm_lck;
                corpse->value[11] = ch->pIndexData->vnum;
                if(xIS_SET(ch->master->act, PLR_BOUGHT_PET))
                    xREMOVE_BIT(ch->master->act, PLR_BOUGHT_PET);
            }
		}
	}
    else
    {
	name		= ch->name;
	corpse		= create_object(get_obj_index(OBJ_VNUM_CORPSE_PC), 0);
    
    if ( in_arena( ch ) )
	  corpse->timer	= 0;
	else
	  corpse->timer = 60;
        corpse->value[2] = (int)(corpse->timer/8);
	corpse->value[4] = ch->level;
/*    For stopping PKers picking up non-pk corpses */
/*
	if ( !CAN_PKILL( ch ) )
	  corpse->owner = ch->name;
*/
	if ( CAN_PKILL( ch ) && sysdata.pk_loot )
	  xSET_BIT( corpse->extra_flags, ITEM_CLANCORPSE );
	/* Pkill corpses get save timers, in ticks (approx 70 seconds)
	   This should be anough for the killer to type 'get all corpse'. */
	if ( !IS_NPC(ch) && !IS_NPC(killer) )
	  corpse->value[3] = 1;
	else
	  corpse->value[3] = 0;
    }

 if(corpse)
 {
    if ( CAN_PKILL( ch ) && CAN_PKILL( killer ) && ch != killer )
    {
	sprintf( buf, "pk" );
	STRFREE( corpse->action_desc );
	corpse->action_desc = STRALLOC( buf );
    }

    /* Added corpse name - make locate easier , other skills */
	if(xIS_SET(ch->act, ACT_PLANT) && IS_NPC(ch))
		sprintf( buf, "corpse trunk roots %s", name);
	else
	    sprintf( buf, "corpse %s", name );

    STRFREE( corpse->name );
    corpse->name = STRALLOC( buf );

	if(xIS_SET(ch->act, ACT_PLANT) && IS_NPC(ch))
		sprintf( buf, "The trunk and roots of %s", name);
	else
	    sprintf( buf, corpse->short_descr, name );
    STRFREE( corpse->short_descr );
    corpse->short_descr = STRALLOC( buf );

	if(xIS_SET(ch->act, ACT_PLANT) && IS_NPC(ch))
		sprintf( buf, "The trunk and roots of %s are decaying here.", name);
	else
	    sprintf( buf, corpse->description, name );
    STRFREE( corpse->description );
    corpse->description = STRALLOC( buf );

    /* Added Bag name...hopefully fix crash */
    OBJ_DATA *questbag = 0;

  if (!IS_NPC(ch))
  {
    questbag    = create_object(get_obj_index(OBJ_VNUM_QUESTBAG), 0);

    sprintf( buf, "bag questbag %s", name );
    STRFREE( questbag->name ); 
    questbag->name = STRALLOC( buf );
           
    sprintf( buf, questbag->short_descr, name ); 
    STRFREE( questbag->short_descr );  
    questbag->short_descr = STRALLOC( buf ); 
           
    sprintf( buf, questbag->description, name ); 
    STRFREE( questbag->description ); 
    questbag->description = STRALLOC( buf );

    questbag->owner = ch->name;
	xSET_BIT(questbag->extra_flags, ITEM_NOJUNK);  // prevents players from junking bag accidentally -Darwin
  }
    for ( obj = ch->first_carrying; obj; obj = obj_next )
    {
		obj_next = obj->next_content;
		obj_from_char( obj );

		/*
        if ( obj->pIndexData->rent >= MIN_RENT ) 
            obj->pIndexData->count += obj->count;
		*/
        /*if ( IS_OBJ_STAT( obj, ITEM_DEATHROT ) ) 
		{
		   if ( IS_OBJ_STAT(obj, ITEM_CONJURER) )
		   {
				int rotchance = 40;
				if ( number_range(1, 100) < ( (ch->level / 10) + rotchance + get_curr_int(ch)) )
					obj_to_obj( obj, corpse );
		   }
        }
        else*/ 
		
		/* Several changes below - allows immortals to slay/kill a pc 
		   or shopkeeper and retain all items in the corpse - allows pc
		   to kill pc and retain quest items in corpse - if pc is killed
		   by npc then they still get their quest items back. - Darwin */
        if ( !IS_NPC( ch ) && ( obj->pIndexData->vnum == OBJ_VNUM_VR_LOCKER ) )
		{
			locker = obj;
			obj_to_obj( locker, questbag );
		}
		else if ( IS_OBJ_STAT( obj, ITEM_INVENTORY ) )
		{
			if( !IS_IMMORTAL( killer ) )
	            extract_obj( obj );
			else
				obj_to_obj( obj, corpse );
		}
		else if ( IS_OBJ_STAT( obj, ITEM_CONJURER ) )
		{
			if(!IS_NPC(killer) && !IS_IMMORTAL(killer))
			{
				xSET_BIT( obj->extra_flags, ITEM_INVENTORY );
				obj->timer = 5;
				STRFREE( obj->owner );
			}
			obj_to_obj(obj, corpse);
		}
        else if ( !IS_NPC( ch ) && IS_OBJ_STAT( obj, ITEM_QUEST ))
		{
			if((IS_NPC(killer)) || (!IS_NPC(killer) && !IS_IMMORTAL(killer)))
				obj_to_obj( obj, questbag );
			else
				obj_to_obj( obj, corpse );
		}
		else 
		{
			if(fkeeper)
			{
				if( !IS_IMMORTAL( killer ) )
					extract_obj( obj );
				else
					obj_to_obj( obj, corpse );
			}
			else
				obj_to_obj( obj, corpse );
		}
    }
    if ( ch->gold > 0 )   
    { 
		if((CH_LEVEL(ch) > 10 && !IS_NPC(ch)) || (IS_IMMORTAL(killer)) || (IS_NPC(ch)) )
		{
		   if ( ch->in_room )
		   { 
			   ch->in_room->area->gold_looted += ch->gold;
			   sysdata.global_looted += ch->gold/100;
		   } 
		   obj_to_obj( create_money( ch->gold ), corpse );
		   ch->gold = 0; 
		}
    } 

    obj_to_room( corpse, ch->in_room );
    if (!IS_NPC(ch) )
	{   // let's just get rid of the questbag
		for ( obj = questbag->first_content; obj; obj = obj_next )
		{
			obj_next = obj->next_content;
			obj_from_obj( obj );
			obj_to_char(obj, ch);
		}
		extract_obj(questbag); // and dispose of it -Darwin
		
		/*
		obj_to_char( questbag, ch );
		if(locker)
		{
			obj_from_obj(locker);
			obj_to_char(locker, ch);
		}*/
	/* This is done to prevent players from doing stupid things
	   such as dying again with all their quest eq still in the bag
	   which was somehow destroying the quest eq -Darwin */
	 //	do_get(ch, "all questbag");
	}
 }
 else
 {
    for ( obj = ch->first_carrying; obj; obj = obj_next )
    {
		obj_next = obj->next_content;
		obj_from_char( obj );
		obj_to_room(obj, ch->in_room);
	}

	obj_to_room(create_money(ch->gold), ch->in_room);
	act( AT_PLAIN, "$n's equipment and gold fall to the ground.", ch, NULL, NULL, TO_ROOM );
 }

    return;
}



void make_blood( CHAR_DATA *ch )
{
	OBJ_DATA *obj;

	obj		= create_object( get_obj_index( OBJ_VNUM_BLOOD ), 0 );
	obj->timer	= number_range( 2, 4 );
	obj->value[1]   = number_range( 3, UMIN(5, ch->level) );
	obj_to_room( obj, ch->in_room );
}


void make_bloodstain( CHAR_DATA *ch )
{
	OBJ_DATA *obj;

	obj		= create_object( get_obj_index( OBJ_VNUM_BLOODSTAIN ), 0 );
	obj->timer	= number_range( 1, 2 );
	obj_to_room( obj, ch->in_room );
}


/*
 * make some coinage
 */
OBJ_DATA *create_money( int amount )
{
    char buf[MAX_STRING_LENGTH];
    OBJ_DATA *obj;

    if ( amount <= 0 )
    {
	bug( "Create_money: zero or negative money %d.", amount );
	amount = 1;
    }

    if ( amount == 1 )
    {
	obj = create_object( get_obj_index( OBJ_VNUM_MONEY_ONE ), 0 );
    }
    else
    {
	obj = create_object( get_obj_index( OBJ_VNUM_MONEY_SOME ), 0 );
	sprintf( buf, obj->short_descr, amount );
	STRFREE( obj->short_descr );
	obj->short_descr = STRALLOC( buf );
	obj->value[0]	 = amount;
    }

    return obj;
}
