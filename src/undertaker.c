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
 * Win32 port by Nick Gammon                                                *
 * ------------------------------------------------------------------------ *
 *                          Undertaker Module                               *
 * ------------------------------------------------------------------------ *
 * Part of this code is from act_wiz.c : do_owhere(). Structure follows     *
 * that of the ROM healer port by Desden, el Chaman Tibetano.               *
 * Brought together by Cyrus & Robcon (ROC2). Please send suggestions to    *
 *    cyrus@cx.net                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mud.h"

/* Checks room to see if an Undertaker mob is present */
CHAR_DATA *find_undertaker( CHAR_DATA *ch )
{
  CHAR_DATA *undertaker = NULL;
  
  /* NOTE TO SMAUG 1.02a USERS: This line is likely to cause errors on compile.
     Remove the "x" before the IS_SET and the error will be resolved.
     Smaug 1.4 users should not need to modify this in any way. - Samson */
  for ( undertaker = ch->in_room->first_person; undertaker; undertaker = undertaker->next_in_room )
    if ( IS_NPC( undertaker ) && xIS_SET( undertaker->act, ACT_UNDERTAKER ) )
      break;

  return undertaker;
}

void do_corpse( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
	//OBJ_DATA *outer_obj;
    CHAR_DATA *mob;
    bool found = FALSE;
    int cost = 0;

    /* Avoids the potential for filling the room with hundreds of mob corpses */
    if( IS_NPC(ch) )
    {
	send_to_char( "Mobs cannot retreive corpses.\n\r", ch );
	return;
    }

    /* Search for an act_undertaker */
    if ( !( mob = find_undertaker( ch ) ) )
    {
        send_to_char( "There's no undertaker here!\n\r", ch );
        return;
    }
/*
    if ( IS_SET( ch->pcdata->flags, PCFLAG_DEADLY ) )
    {
	act(AT_PLAIN, "$N says 'Ooo Noooo!  I cannot help a deadly foe such as yourself!", ch, NULL, mob, TO_CHAR);
	return;
    }

    if ( CH_LEVEL(ch) > 25 )
    {
	act(AT_PLAIN, "$N says 'Sorry my friend, I only help those under level 25!", ch, NULL, mob, TO_CHAR);
	return;
    }
*/
    argument = one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
        act(AT_PLAIN,"$N says 'Ooo Yesss ... I can helpss you.'",ch,NULL,mob,TO_CHAR);
		if(CH_LEVEL(ch) < 26)
			send_to_char("  retrieve: Retrieves your corpse   50gp / level\n\r",ch);
		else if ( (CH_LEVEL(ch) > 25) && IS_SET( ch->pcdata->flags, PCFLAG_DEADLY ))
			send_to_char("  retrieve: Retrieves your corpse   15qp / level\n\r",ch);
		else
			send_to_char("  retrieve: Retrieves your corpse   10qp / level\n\r",ch);

		send_to_char(" Type corpse <type> for the service.\n\r",ch);
        return;
    }

    if (!str_cmp(arg,"retrieve"))
	{
		if(CH_LEVEL(ch) < 26)
	        cost  = 50 * CH_LEVEL(ch);
		else if(IS_SET(ch->pcdata->flags, PCFLAG_DEADLY) && CH_LEVEL(ch) > 25)
			cost  = 15 * CH_LEVEL(ch);
		else
			cost  = 10 * CH_LEVEL(ch);
	}
    else
    {
        act(AT_PLAIN,"$N says ' Type 'corpse' for help on what I do.'", ch,NULL,mob,TO_CHAR);
        return;
    }

	if(CH_LEVEL(ch) < 26 && cost > ch->gold)
    {
        act(AT_PLAIN,"$N says 'Pah! You do not have enough gold for my services!'",ch,NULL,mob,TO_CHAR);
        return;
    }
	else if(CH_LEVEL(ch) > 25 && cost > ch->pcdata->quest_curr )
    {
        act(AT_PLAIN,"$N says 'Pah! You are not glorious enough for my services!'",ch,NULL,mob,TO_CHAR);
        return;
    }

    strcpy( buf, "the corpse of " );
    strcat( buf, ch->name ); 			/* Bug fix here by Samson 12-21-00 See below */
    for ( obj = first_object; obj; obj = obj->next )
    {
        if ( !nifty_is_name( buf, obj->short_descr ) ) /* Fix here - Samson 1-26-01 */
              continue;

	  /* This will prevent NPC corpses from being retreived if the person has a mob's name */
	  if ( obj->item_type != ITEM_CORPSE_PC )
		continue;
          if ( obj->carried_by && !IS_NPC(obj->carried_by) )
		continue;

        found = TRUE;
        
        /* Could be carried by act_scavengers, or other idiots so ... */
		// this stuff doesn't make sense - just get the corpse and return it to the room -Darwin
		/*
        outer_obj = obj;
        while ( outer_obj->in_obj )
              outer_obj = outer_obj->in_obj;

        separate_obj( outer_obj );
        obj_from_room( outer_obj );
        obj_to_room( outer_obj, ch->in_room );
		*/

		if(obj->in_obj) // corpses end up in strange places... just return the corpse -Darwin
			obj_from_obj(obj);
		if(obj->carried_by)
			obj_from_char(obj);
		if(obj->in_room)
			obj_from_room(obj);

		obj_to_room(obj, ch->in_room);

		if(CH_LEVEL(ch) < 26)
	        ch->gold -= cost;
		else
			ch->pcdata->quest_curr -= cost;

        act(AT_PLAIN,"$N creepily carts in your corpse and dumps it in front of you.",ch,NULL,mob,TO_CHAR);
        act(AT_PLAIN,"$n creepily carts in the $T and dumps it off.",mob,NULL,buf,TO_ROOM);
    }

    /* Could've been extracted, so do this */
    if ( !found )
        act(AT_PLAIN,"$N says 'Sorry I can't find your corpse. There's nothing more I can do.'",ch,NULL,mob,TO_CHAR);

    return;
}
