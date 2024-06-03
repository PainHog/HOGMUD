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
 *			     Informational module			    *
 ****************************************************************************/


#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "mud.h"

/*
 * Keep players from defeating examine progs -Druid
 * False = do not trigger
 * True = Trigger
 */
bool EXA_prog_trigger = TRUE;

/* Had to add unknowns because someone added new positions and didn't
 * update them.  Just a band-aid till I have time to fix it right.
 * This was found thanks to mud@mini.axcomp.com pointing it out :)
 * --Shaddai
 */

char *	const	where_name	[] =
{
    "&R<&Gused as &Wlight&R>&G     ",
    "&R<&Gworn on &Chead&R>&G      ",
    "&R<&Gworn on &Ceyes&R>&G      ",
    "&R<&Gworn on &Cears&R>&G      ",
    "&R<&Gworn on &Cface&R>&G      ",
    "&R<&Gworn around &Cneck&R>&G  ",
    "&R<&Gworn around &Cneck&R>&G  ",
    "&R<&Gworn on &Cbody&R>&G      ",
    "&R<&Gworn on &Carms&R>&G      ",
    "&R<&Gworn around &Cwrist&R>&G ",
    "&R<&Gworn around &Cwrist&R>&G ",
    "&R<&Gworn on &Chands&R>&G     ",
    "&R<&Gworn on &Cfinger&R>&G    ",
    "&R<&Gworn on &Cfinger&R>&G    ",
    "&R<&Gworn &Cabout body&R>&G   ",
    "&R<&Gworn on &Cback&R>&G      ",
    "&R<&Gworn around &Cwaist&R>&G ",
    "&R<&Gworn on &Clegs&R>&G      ",
    "&R<&Gworn around &Cankle&R>&G ",
    "&R<&Gworn around &Cankle&R>&G ",
    "&R<&Gworn on &Cfeet&R>&G      ",
    "&R<&Ywielded&R>&G           ",
    "&R<&Ydual wielded&R>&G      ",
    "&R<&Gheld as &Cshield&R>&G    ",
    "&R<&Yheld&R>&G              ",  
    "&R<&Gworn with &Cpride&R>&G   ",
    "&R<&Gworn with &Cpride&R>&G   ",
    "&R<&Gsurrounding &Yaura&R>&G  "
};


/*
 * Local functions.
 */
void	show_char_to_char_0	args( ( CHAR_DATA *victim, CHAR_DATA *ch ) );
void	show_char_to_char_1	args( ( CHAR_DATA *victim, CHAR_DATA *ch ) );
void	show_char_to_char	args( ( CHAR_DATA *list, CHAR_DATA *ch ) );
bool	check_blind		args( ( CHAR_DATA *ch ) );
void    show_condition          args( ( CHAR_DATA *ch, CHAR_DATA *victim ) );
int call_mud_lua    args( (const char * fname, const char * argument) );


char *format_obj_to_char( OBJ_DATA *obj, CHAR_DATA *ch, bool fShort )
{
    static char buf[MAX_STRING_LENGTH];
    bool glowsee = FALSE;

    /* can see glowing invis items in the dark */
    if ( IS_OBJ_STAT(obj, ITEM_GLOW) && IS_OBJ_STAT(obj, ITEM_INVIS)
    &&  !IS_AFFECTED(ch, AFF_TRUESIGHT) && !IS_AFFECTED(ch, AFF_DETECT_INVIS) )
	glowsee = TRUE;

    buf[0] = '\0';

/*New Way of displaying magical flags, Sirus */
/* Reworked -Darwin */
    if (( ( IS_IMMORTAL(ch) || IS_ARCHMAGI(ch) || IS_MAGE(ch) ) ||
	   ( IS_AFFECTED(ch, AFF_DETECT_MAGIC)  || IS_AFFECTED(ch, AFF_TRUESIGHT) || IS_AFFECTED(ch, AFF_AURALINK) )) &&
         IS_OBJ_STAT(obj, ITEM_MAGIC) ) 
      get_mflag(obj, buf); 
    else if ( (IS_AFFECTED(ch, AFF_DETECT_MAGIC) || IS_AFFECTED(ch, AFF_TRUESIGHT) || xIS_SET(ch->act, PLR_HOLYLIGHT))
         && IS_OBJ_STAT(obj, ITEM_MAGIC) && !IS_NPC(ch) )   strcat( buf, "&G(&PMagical&G) "   );

    if ( (IS_IMMORTAL(ch) || IS_ARCHMAGI(ch) || IS_MAGE(ch) || IS_AFFECTED(ch, AFF_DETECT_MAGIC) ) &&
	IS_OBJ_STAT(obj, ITEM_ENCHANTED) )
	strcat( buf, "&G(&YEnchanted&G) " );
    if( !IS_NPC(ch) && ch->pcdata->questobj > 0 && obj->pIndexData->vnum == ch->pcdata->questobj)
	strcat( buf, "[&RTarget&G] " );
    if ( IS_OBJ_STAT(obj, ITEM_INVIS)     )   strcat( buf, "&G(&CInvis&G) "     );
    if (  (IS_AFFECTED(ch, AFF_DETECT_EVIL) || IS_AFFECTED(ch, AFF_TRUESIGHT) || IS_AFFECTED(ch, AFF_DEMONSIGHT) )
	 && IS_OBJ_STAT(obj, ITEM_EVIL)   )   strcat( buf, "&G(&RRed Aura&G) "  );
    if (  (IS_AFFECTED(ch, AFF_DETECT_GOOD) || IS_AFFECTED(ch, AFF_TRUESIGHT) || IS_AFFECTED(ch, AFF_DEMONSIGHT) )
         && IS_OBJ_STAT(obj, ITEM_GOOD)   )   strcat( buf, "&G(&BBlue Aura&G) " );

    if ( !glowsee && IS_OBJ_STAT(obj, ITEM_GLOW) )   strcat( buf, "&G(&WGlowing&G) "   );
    if ( IS_OBJ_STAT(obj, ITEM_HUM)       )   strcat( buf, "&G(&cHumming&G) "   );
    if ( IS_OBJ_STAT(obj, ITEM_HIDDEN)	  )   strcat( buf, "&G(&zHidden&G) "	  );
    if ( IS_OBJ_STAT(obj, ITEM_BURIED)	  )   strcat( buf, "&G(&OBuried&G) "	  );
    if ( IS_AFFECTED(ch, AFF_DETECTTRAPS)
	 && is_trapped(obj)   )   strcat( buf, "&G(&RTrap&G) "  );

    if ( fShort )
    {
	if ( glowsee && !IS_IMMORTAL(ch) )
	    strcat( buf, "the faint glow of something" );
	else
	if ( obj->short_descr )
	    strcat( buf, obj->short_descr );
    }
    else
    {
	if ( glowsee )
	    strcat( buf, "You see the faint glow of something nearby." );
	if ( obj->description )
	    strcat( buf, obj->description );
    }

    return buf;
}


/*
 * Some increasingly freaky hallucinated objects		-Thoric
 * (Hats off to Albert Hoffman's "problem child")
 */
char *hallucinated_object( int ms, bool fShort )
{
    int sms = URANGE( 1, (ms+10)/5, 20 );

    if ( fShort )
    switch( number_range( 6-URANGE(1,sms/2,5), sms ) )
    {
	case  1: return "a sword";
	case  2: return "a stick";
	case  3: return "something shiny";
	case  4: return "something";
	case  5: return "something interesting";
	case  6: return "something colorful";
	case  7: return "something that looks cool";
	case  8: return "a nifty thing";
	case  9: return "a cloak of flowing colors";
	case 10: return "a mystical flaming sword";
	case 11: return "a swarm of insects";
	case 12: return "a deathbane";
	case 13: return "a figment of your imagination";
	case 14: return "your gravestone";
	case 15: return "the long lost boots of Ranger Daot";
	case 16: return "a glowing tome of arcane knowledge";
	case 17: return "a long sought secret";
	case 18: return "the meaning of it all";
	case 19: return "the answer";
	case 20: return "the key to life, the universe and everything";
    }
    switch( number_range( 6-URANGE(1,sms/2,5), sms ) )
    {
	case  1: return "A nice looking sword catches your eye.";
	case  2: return "The ground is covered in small sticks.";
	case  3: return "Something shiny catches your eye.";
	case  4: return "Something catches your attention.";
	case  5: return "Something interesting catches your eye.";
	case  6: return "Something colorful flows by.";
	case  7: return "Something that looks cool calls out to you.";
	case  8: return "A nifty thing of great importance stands here.";
	case  9: return "A cloak of flowing colors asks you to wear it.";
	case 10: return "A mystical flaming sword awaits your grasp.";
	case 11: return "A swarm of insects buzzes in your face!";
	case 12: return "The extremely rare Deathbane lies at your feet.";
	case 13: return "A figment of your imagination is at your command.";
	case 14: return "You notice a gravestone here... upon closer examination, it reads your name.";
	case 15: return "The long lost boots of Ranger Thoric lie off to the side.";
	case 16: return "A glowing tome of arcane knowledge hovers in the air before you.";
	case 17: return "A long sought secret of all mankind is now clear to you.";
	case 18: return "The meaning of it all, so simple, so clear... of course!";
	case 19: return "The answer.  One.  It's always been One.";
	case 20: return "The key to life, the universe and everything awaits your hand.";
    }
    return "Whoa!!!";
}


/* This is the punct snippet from Desden el Chaman Tibetano - Nov 1998
   Email: jlalbatros@mx2.redestb.es

   This changed to use a Lua function, much simplier, possibly faster.
   -Darwin (2008-03-16)
*/
char *num_punct(int foo)
{
    char *buf;
    call_va(L_mud, "num_punct", "i>s", foo, &buf);
    
    return buf;
}


/*
 * Show a list to a character.
 * Can coalesce duplicated items.
 */
void show_list_to_char_type( OBJ_DATA *list, CHAR_DATA *ch, bool fShort, bool fShowNothing, int itemtype )
{
    char **prgpstrShow;
    int *prgnShow;
    int *pitShow;
    char *pstrShow;
    OBJ_DATA *obj;
    int nShow;
    int iShow;
    int type = 0;
    int count, offcount, tmp, ms, cnt;
    bool fCombine;

    if ( !ch->desc )
	return;

     if (itemtype > 0)
        type = 1;

    /*
     * if there's no list... then don't do all this crap!  -Thoric
     */
    if ( !list )
    {
    	if ( fShowNothing )
    	{
	   if ( IS_NPC(ch) || xIS_SET(ch->act, PLR_COMBINE) )
	      send_to_char( "     ", ch );
	   set_char_color( AT_OBJECT, ch );
	   send_to_char( "Nothing.\n\r", ch );
	}
	return;
    }
    /*
     * Alloc space for output lines.
     */
    count = 0;
    for ( obj = list; obj; obj = obj->next_content )
	count++;

    ms  = (ch->mental_state ? ch->mental_state : 1)
	* (IS_NPC(ch) ? 1 : (ch->pcdata->condition[COND_DRUNK] ? (ch->pcdata->condition[COND_DRUNK]/12) : 1));

    /*
     * If not mentally stable...
     */
    if ( abs(ms) > 40 )
    {
	offcount = URANGE( -(count), (count * ms) / 100, count*2 );
	if ( offcount < 0 )
	  offcount += number_range(0, abs(offcount));
	else
	if ( offcount > 0 )
	  offcount -= number_range(0, offcount);
    }
    else
	offcount = 0;

    if ( count + offcount <= 0 )
    {
    	if ( fShowNothing )
    	{
	   if ( IS_NPC(ch) || xIS_SET(ch->act, PLR_COMBINE) )
	      send_to_char( "     ", ch );
	   set_char_color( AT_OBJECT, ch );
	   send_to_char( "Nothing.\n\r", ch );
	}
	return;
    }

    CREATE( prgpstrShow,	char*,	count + ((offcount > 0) ? offcount : 0) );
    CREATE( prgnShow,		int,	count + ((offcount > 0) ? offcount : 0) );
    CREATE( pitShow,		int,	count + ((offcount > 0) ? offcount : 0) );
    nShow	= 0;
    tmp		= (offcount > 0) ? offcount : 0;
    cnt		= 0;

    /*
     * Format the list of objects.
     */
    for ( obj = list; obj; obj = obj->next_content )
    {
	if ( offcount < 0 && ++cnt > (count + offcount) )
	    break;
        if ( type == 1) // For Examine, will only show a certain itemtype if prompted
        {
           if (obj->item_type != itemtype)
           continue;
        }
	if ( tmp > 0 && number_bits(1) == 0 )
	{
	    prgpstrShow [nShow] = str_dup( hallucinated_object(ms, fShort) );
	    prgnShow	[nShow] = 1;
	    pitShow	[nShow] = number_range( ITEM_LIGHT, ITEM_BOOK );
	    nShow++;
	    --tmp;
	}
	if ( obj->wear_loc == WEAR_NONE
	&& can_see_obj( ch, obj )
	&& (obj->item_type != ITEM_TRAP || IS_AFFECTED(ch, AFF_DETECTTRAPS) ) )
	{
	    pstrShow = format_obj_to_char( obj, ch, fShort );
	    fCombine = FALSE;

	    if ( IS_NPC(ch) || xIS_SET(ch->act, PLR_COMBINE) )
	    {
		/*
		 * Look for duplicates, case sensitive.
		 * Matches tend to be near end so run loop backwords.
		 */
		for ( iShow = nShow - 1; iShow >= 0; iShow-- )
		{
		    if ( !strcmp( prgpstrShow[iShow], pstrShow ) )
		    {
			prgnShow[iShow] += obj->count;
			fCombine = TRUE;
			break;
		    }
		}
	    }

	    pitShow[nShow] = obj->item_type;
	    /*
	     * Couldn't combine, or didn't want to.
	     */
	    if ( !fCombine )
	    {
		prgpstrShow [nShow] = str_dup( pstrShow );
		prgnShow    [nShow] = obj->count;
		nShow++;
	    }
	}
    }
    if ( tmp > 0 )
    {
	int x;
	for ( x = 0; x < tmp; x++ )
	{
	    prgpstrShow [nShow] = str_dup( hallucinated_object(ms, fShort) );
	    prgnShow	[nShow] = 1;
	    pitShow	[nShow] = number_range( ITEM_LIGHT, ITEM_BOOK );
	    nShow++;
	}
    }

    /*
     * Output the formatted list.		-Color support by Thoric
     */
    for ( iShow = 0; iShow < nShow; iShow++ )
    {
	switch(pitShow[iShow]) {
	default:
	  set_char_color( AT_OBJECT, ch );
	  break;
	case ITEM_BLOOD:
	  set_char_color( AT_BLOOD, ch );
	  break;
	case ITEM_MONEY:
	  set_char_color( AT_YELLOW, ch );
	  break;
	case ITEM_COOK:
	case ITEM_FOOD:
	  set_char_color( AT_HUNGRY, ch );
	  break;
	case ITEM_DRINK_CON:
	case ITEM_FOUNTAIN:
	  set_char_color( AT_THIRSTY, ch );
	  break;
	case ITEM_FIRE:
	  set_char_color( AT_FIRE, ch );
	  break;
	case ITEM_SCROLL:
	case ITEM_WAND:
	case ITEM_STAFF:
	  set_char_color( AT_MAGIC, ch );
	  break;
	}
	if ( fShowNothing )
	    send_to_char( "     ", ch );
	send_to_char( prgpstrShow[iShow], ch );
/*	if ( IS_NPC(ch) || xIS_SET(ch->act, PLR_COMBINE) ) */
	{
	    if ( prgnShow[iShow] != 1 )
		ch_printf( ch, " (%d)", prgnShow[iShow] );
	}

	send_to_char( "\n\r", ch );
	DISPOSE( prgpstrShow[iShow] );
    }

    if ( fShowNothing && nShow == 0 )
    {
	if ( IS_NPC(ch) || xIS_SET(ch->act, PLR_COMBINE) )
	    send_to_char( "     ", ch );
	set_char_color( AT_OBJECT, ch );
	send_to_char( "Nothing.\n\r", ch );
    }

    /*
     * Clean up.
     */
    DISPOSE( prgpstrShow );
    DISPOSE( prgnShow	 );
    DISPOSE( pitShow	 );
    return;
}

// So we do not have to declare show_list_to_char_type in mud.h
void show_list_to_char( OBJ_DATA *list, CHAR_DATA *ch, bool fShort, bool fShowNothing )
{ 
    show_list_to_char_type( list, ch, fShort, fShowNothing, 0);
    return;
}

void show_char_to_char_0( CHAR_DATA *victim, CHAR_DATA *ch )
{
    char buf[MAX_STRING_LENGTH];
    char buf1[MAX_STRING_LENGTH];
	char buf2[MAX_STRING_LENGTH];
    char message[MAX_STRING_LENGTH]; /* Output for the furniture -- Xerves */
	bool has_visible_affects = FALSE;

    buf[0] = '\0';
	buf2[0] = '\0';

    set_char_color( AT_PERSON, ch );
    if ( !IS_NPC(victim) && !victim->desc )
    {
	if ( !victim->switched )         send_to_char_color( "&P[&RLD&P] ", ch );
	else if ( !IS_AFFECTED(victim, AFF_POSSESS) )
						strcat( buf, "&W(&PSwitched&W) " );
    }
    if ( IS_NPC(victim) && IS_AFFECTED(victim, AFF_POSSESS) && IS_IMMORTAL(ch)
	 && victim->desc )
    {
			sprintf( buf1, "(%s)",victim->desc->original->name );
			strcat( buf, buf1 );
    }

    if(IS_NPC(victim) && !IS_NPC(ch) && ch->pcdata->questmob > 0 && victim->pIndexData->vnum == ch->pcdata->questmob)
	strcat( buf, "[&RTarget&P] ");

    if ( !IS_NPC(victim)
    &&   xIS_SET(victim->act, PLR_AFK) )	strcat( buf, "[AFK] ");        

    if ( (!IS_NPC(victim) && xIS_SET(victim->act, PLR_WIZINVIS))
      || (IS_NPC(victim) && xIS_SET(victim->act, ACT_MOBINVIS)) ) 
    {
        if (!IS_NPC(victim))
	sprintf( buf1,"(&CInvis&P &R%d&P) ", victim->pcdata->wizinvis );
        else sprintf( buf1,"(&CMobinvis&P %d) ", victim->mobinvis);
	strcat( buf, buf1 );
    }
 

    if ( !IS_NPC( victim) )
    {
	if ( IS_IMMORTAL( victim ) && victim->level > 51 )
	  send_to_char_color( "&P(&WImmortal&P) ", ch );
    }

    set_char_color( AT_PERSON, ch );

/*  First 7 added by Drazuk and removed from the above section */
/*  Added proper spacing -Darwin */

	if(xIS_SET(ch->act, PLR_ABBAFFS))
	{
		strcat( buf2, "&P( ");
		if ( IS_AFFECTED(victim, AFF_SANCTUARY)   ) {strcat( buf2, "&WS " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_FIRESHIELD)  ) {strcat( buf2, "&RF " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_SHOCKSHIELD) ) {strcat( buf2, "&BK " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_ICESHIELD)   ) {strcat( buf2, "&CI " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_INVISIBLE) || 
			 IS_AFFECTED(victim, AFF_IMP_INVIS) )   {strcat( buf2, "&WV " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_HIDE)        ) {strcat( buf2, "&BH " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_CAMO)	      ) {strcat( buf2, "&GC " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_PASS_DOOR)   ) {strcat( buf2, "&YT " ); has_visible_affects = TRUE;}
		if ( IS_AFFECTED(victim, AFF_FAERIE_FIRE) ) {strcat( buf2, "&PP " ); has_visible_affects = TRUE;}
		if (has_visible_affects)
		{
			strcat( buf2, "&P) ");
			strcat( buf, buf2);
		}
	}
	else
	{
		if ( IS_AFFECTED(victim, AFF_SANCTUARY)   ) strcat( buf, "(&WSanct&P) "      );
		if ( IS_AFFECTED(victim, AFF_FIRESHIELD)  ) strcat( buf, "(&RFS&P) "         );
		if ( IS_AFFECTED(victim, AFF_SHOCKSHIELD) ) strcat( buf, "(&BSS&P) "         );
		if ( IS_AFFECTED(victim, AFF_ICESHIELD)   ) strcat( buf, "(&CIS&P) "         );
		if ( IS_AFFECTED(victim, AFF_INVISIBLE) || IS_AFFECTED(victim, AFF_IMP_INVIS)  ) strcat( buf, "(&CInvis&P) "      );
		if ( IS_AFFECTED(victim, AFF_HIDE)        ) strcat( buf, "(&BHide&P) "       );
		if ( IS_AFFECTED(victim, AFF_CAMO)	      ) strcat( buf, "(&GCamo&P) "	 );
		if ( IS_AFFECTED(victim, AFF_PASS_DOOR)   ) strcat( buf, "(&WTranslucent&P) ");
		if ( IS_AFFECTED(victim, AFF_FAERIE_FIRE) ) strcat( buf, "(&PPink Aura&P) "  );
	}

    if ( IS_AFFECTED(victim, AFF_CHARM)       ) strcat( buf, "(&rCharmed&P) "    );
    if ( IS_AFFECTED(victim, AFF_POSSESS)     ) strcat( buf, "(&YPossess&P) "    );
    if ( IS_AFFECTED(victim, AFF_BERSERK)     ) strcat( buf, "(&GWild-eyed&P) "  );
    if ( !IS_NPC(victim) && xIS_SET(victim->act, PLR_ATTACKER ) )
						strcat( buf, "(&RATTACKER&P) "   );
    if ( !IS_NPC(victim) && xIS_SET(victim->act, PLR_KILLER ) )
						strcat( buf, "(&RKILLER&P) "     );
    if ( !IS_NPC(victim) && xIS_SET(victim->act, PLR_THIEF  ) )
						strcat( buf, "(&RTHIEF&P) "      );
    if ( !IS_NPC(victim) && xIS_SET(victim->act, PLR_BULLY  ) )
						strcat( buf, "(&RBULLY&P) "  );
    if ( IS_NPC(victim) && ch->mount && ch->mount == victim
         && ch->in_room == ch->mount->in_room ) strcat( buf, "(&OMount&P) "      );
    if ( victim->desc && victim->desc->connected == CON_EDITING )
						strcat( buf, "(&CWriting&P) "    );
    if ( victim->morph != NULL )
      strcat (buf, "(Morphed) ");
    if ( IS_EVIL(victim) && (IS_AFFECTED(ch, AFF_DETECT_EVIL) || IS_AFFECTED(ch, AFF_TRUESIGHT) || IS_AFFECTED(ch, AFF_DEMONSIGHT) ) )
	{
		if(xIS_SET(ch->act, PLR_ABBAFFS))
			strcat( buf, "(&RE&P) " );
		else
	        strcat( buf, "(&RRed Aura&P) "   );
	}
    if ( IS_NEUTRAL(victim) && (IS_AFFECTED(ch, AFF_TRUESIGHT) || IS_AFFECTED(ch, AFF_DEMONSIGHT) || ( IS_AFFECTED(ch, AFF_DETECT_EVIL) && IS_AFFECTED(ch, AFF_DETECT_GOOD) ) ) )
	{
		if(xIS_SET(ch->act, PLR_ABBAFFS))
			strcat( buf, "(&zN&P) " );
		else
			strcat( buf, "(&zGrey Aura&P) "   ); 
	}
    if ( IS_GOOD(victim) && (IS_AFFECTED(ch, AFF_DETECT_GOOD) || IS_AFFECTED(ch, AFF_TRUESIGHT) || IS_AFFECTED(ch, AFF_DEMONSIGHT) ) )
	{
		if(xIS_SET(ch->act, PLR_ABBAFFS))
			strcat( buf, "(&BG&P) " );
		else
			strcat( buf, "(&BBlue Aura&P) "   );
	}

//	strcat(buf, " " ); /* Propper spacing eliminates need for this space -Darwin */

    set_char_color( AT_PERSON, ch );
  if ((victim->position == victim->defposition && victim->long_descr[0] != '\0')
      || ( victim->morph && victim->morph->morph &&
           victim->morph->morph->defpos == victim->position ) )
    {
      if ( victim->morph != NULL )
      {
        if ( !IS_IMMORTAL(ch) )
        {
          if ( victim->morph->morph != NULL)
                strcat ( buf, victim->morph->morph->long_desc );
          else
                strcat ( buf, victim->long_descr );
        }
        else
	{
           strcat (buf, capitalize(PERS(victim, ch)) );
//    	   if ( !IS_NPC(victim) && !xIS_SET(ch->act, PLR_BRIEF) )
//		strcat( buf, victim );     // Took out ->pcdata->title - Drazuk
	   strcat( buf, ".\n\r" );
	}
      }
      else
           strcat (buf, victim->long_descr);
	send_to_char( buf, ch );
//	show_visible_affects_to_char( victim, ch );
	return;
    }
    else {
    if ( victim->morph != NULL && victim->morph->morph != NULL &&
	 !IS_IMMORTAL( ch ) )
	strcat( buf, MORPHPERS( victim, ch ) );
    else 
    	strcat( buf, capitalize(PERS( victim, ch )) );
    }

//    if ( !IS_NPC(victim) && !xIS_SET(ch->act, PLR_BRIEF) )
//	strcat( buf, victim->name );   // Took out ->pcdata->title -Drazuk

    switch ( victim->position )
    {
    case POS_DEAD:     strcat( buf, " is DEAD!!" );			break;
    case POS_MORTAL:   strcat( buf, " is mortally wounded." );		break;
    case POS_INCAP:    strcat( buf, " is incapacitated." );		break;
    case POS_STUNNED:  strcat( buf, " is lying here stunned." );	break;
/* Furniture ideas taken from ROT
   Furniture 1.01 is provided by Xerves
   Info rewrite for sleeping/resting/standing/sitting on Objects -- Xerves */
   case POS_SLEEPING:
    if (victim->on != NULL)
        {
            if (IS_SET(victim->on->value[2],SLEEP_AT))
            {
                sprintf(message,"&P is sleeping at %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else if (IS_SET(victim->on->value[2],SLEEP_ON))
            {
                sprintf(message,"&P is sleeping on %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else
            {
                sprintf(message, "&P is sleeping in %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
        }
        else
        {
          if (ch->position == POS_SITTING
          ||  ch->position == POS_RESTING )
              strcat( buf, "&P is sleeping nearby.&G" );
	  else
              strcat( buf, "&P is deep in slumber here.&G" );
        }
          break;
    case POS_RESTING:
        if (victim->on != NULL)
        {
            if (IS_SET(victim->on->value[2],REST_AT))
            {
                sprintf(message,"&P is resting at %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else if (IS_SET(victim->on->value[2],REST_ON))
            {
                sprintf(message,"&P is resting on %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else
            {
                sprintf(message, "&P is resting in %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
        }
        else
        {
          if (ch->position == POS_RESTING)
              strcat ( buf, "&P is sprawled out alongside you.&G" );
          else
	  if (ch->position == POS_MOUNTED)
	      strcat ( buf, "&P is sprawled out at the foot of your mount.&G" );
	  else
              strcat (buf, "&P is sprawled out here.&G" );
        }
          break;
    case POS_SITTING:
        if (victim->on != NULL)
        {
            if (IS_SET(victim->on->value[2],SIT_AT))
            {
                sprintf(message,"&P is sitting at %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else if (IS_SET(victim->on->value[2],SIT_ON))
            {
                sprintf(message,"&P is sitting on %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else
            {
                sprintf(message, "&P is sitting in %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
        }
        else
	    strcat(buf, "&P is sitting here.");
	break;
    case POS_STANDING:
     if (victim->on != NULL)
        {
            if (IS_SET(victim->on->value[2],STAND_AT))
            {
                sprintf(message,"&P is standing at %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else if (IS_SET(victim->on->value[2],STAND_ON))
            {
                sprintf(message,"&P is standing on %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
            else
            {
                sprintf(message, "&P is standing in %s.",
                    victim->on->short_descr);
                strcat(buf,message);
            }
        }
      else
        if ( IS_IMMORTAL(victim) )
            strcat( buf, "&P is here before you.&G" );
	else
        if ( ( victim->in_room->sector_type == SECT_UNDERWATER )
        && !IS_AFFECTED(victim, AFF_AQUA_BREATH) && !IS_NPC(victim) )
            strcat( buf, "&P is drowning here.&G" );
	else
	if ( victim->in_room->sector_type == SECT_UNDERWATER )
            strcat( buf, "&P is here in the water.&G" );
	else
	if ( ( victim->in_room->sector_type == SECT_OCEANFLOOR )
	&& !IS_AFFECTED(victim, AFF_AQUA_BREATH) && !IS_NPC(victim) )
	    strcat( buf, "&P is drowning here.&G" );
	else
	if ( victim->in_room->sector_type == SECT_OCEANFLOOR )
	    strcat( buf, "&P is standing here in the water.&G" );
	else
	if ( IS_AFFECTED(victim, AFF_FLOATING)
        || IS_AFFECTED(victim, AFF_FLYING) )
          strcat( buf, "&P is hovering here.&G" );
        else
          strcat( buf, "&P is standing here.&G" );
          break;
    case POS_SHOVE:    strcat( buf, " is being shoved around." );	break;
    case POS_DRAG:     strcat( buf, " is being dragged around." );	break;
    case POS_MOUNTED:
	strcat( buf, " is here, upon " );
	if ( !victim->mount )
	    victim->position = POS_STANDING;
	else
	if ( victim->mount == ch )
	    strcat( buf, "your back." );
	else
	if ( victim->in_room == victim->mount->in_room )
	{
	    strcat( buf, capitalize(PERS( victim->mount, ch )) );
	    strcat( buf, "." );
	}
	else
	    strcat( buf, "someone who left??" );
	break;
    case POS_FIGHTING:
    case POS_EVASIVE:
    case POS_DEFENSIVE:
    case POS_AGGRESSIVE:
    case POS_BERSERK:
	strcat( buf, " is here, fighting " );
	if ( !victim->fighting ) 
        {
	    strcat( buf, "thin air???" );

            /* some bug somewhere.... kinda hackey fix -h */
            if(! victim->mount)
               victim->position = POS_STANDING;
            else
               victim->position = POS_MOUNTED;
        }
	else if ( who_fighting( victim ) == ch )
	    strcat( buf, "YOU!" );
	else if ( victim->in_room == victim->fighting->who->in_room )
	{
	    strcat( buf, PERS( victim->fighting->who, ch ) );
	    strcat( buf, "." );
	}
	else
	    strcat( buf, "someone who left??" );
	break;
    }

    strcat( buf, "\n\r" );
    buf[0] = UPPER(buf[0]);
    send_to_char( buf, ch );
//  show_visible_affects_to_char( victim, ch );
    return;
}



void show_char_to_char_1( CHAR_DATA *victim, CHAR_DATA *ch )
{
    OBJ_DATA *obj;
    int iWear;
    bool found;

    if ( can_see( victim, ch ) && !IS_NPC( ch ) && !xIS_SET( ch->act, PLR_WIZINVIS ) )
    {
      act( AT_ACTION, "$n looks at you.", ch, NULL, victim, TO_VICT    );
      if ( victim != ch )
	act( AT_ACTION, "$n looks at $N.",  ch, NULL, victim, TO_NOTVICT );
      else
        act( AT_ACTION, "$n looks at $mself.", ch, NULL, victim, TO_NOTVICT );
    }

    if ( victim->description[0] != '\0' )
    {
      if ( victim->morph != NULL && victim->morph->morph != NULL)
        send_to_char ( victim->morph->morph->description , ch );
      else
        send_to_char (victim->description, ch);
    }
    else
    {
        if ( victim->morph != NULL && victim->morph->morph != NULL)
           send_to_char ( victim->morph->morph->description , ch );
	else if ( IS_NPC( victim ) )
	  act( AT_PLAIN, "You see nothing special about $M.", ch, NULL, victim, TO_CHAR );
	else if ( ch != victim )
	  act( AT_PLAIN, "$E isn't much to look at...", ch, NULL, victim, TO_CHAR );
	else
	  act( AT_PLAIN, "You're not much to look at...", ch, NULL, NULL, TO_CHAR );
    }

    show_race_line( ch, victim );
    show_condition( ch, victim );

    found = FALSE;
    set_char_color( AT_OBJECT, ch );
    for ( iWear = 0; iWear < MAX_WEAR; iWear++ )
    {
	if ( ( obj = get_eq_char( victim, iWear ) ) != NULL
	&&   can_see_obj( ch, obj ) )
	{
	    if ( !found )
	    {
		send_to_char_color( "\n\r", ch );
		if ( victim != ch )
		  act( AT_PLAIN, "$N is using:", ch, NULL, victim, TO_CHAR );
		else
		  act( AT_PLAIN, "You are using:", ch, NULL, NULL, TO_CHAR );
		found = TRUE;
	    }
            //   if( (!IS_NPC(victim)) && (victim->race>0) && (victim->race < MAX_PC_RACE)) --Hmm, Drazuk
	    //  	send_to_char_color(race_table[victim->race]->where_name[iWear], ch);
	    //   else
	        send_to_char_color( where_name[iWear], ch );
	    send_to_char_color( format_obj_to_char( obj, ch, TRUE ), ch );
	    send_to_char( "\n\r", ch );
	}
    }

    /*
     * Crash fix here by Thoric
     */
    if ( IS_NPC(ch) || victim == ch )
      return;

    if ( IS_IMMORTAL( ch ) )
    {
      if ( IS_NPC( victim ) )
	ch_printf( ch, "\n\rMobile #%d '%s' ",
	    victim->pIndexData->vnum,
	    victim->name );
	else
	  ch_printf( ch, "\n\r%s ", victim->name );
      ch_printf( ch, "is a level %d %s %s.\n\r",
	victim->level,
	IS_NPC(victim)?victim->race<MAX_NPC_RACE&&victim->race>=0?
	npc_race[victim->race]:"unknown":victim->race<MAX_PC_RACE&&
	race_table[victim->race]->race_name&&
	race_table[victim->race]->race_name[0] != '\0'?
	race_table[victim->race]->race_name:"unknown",
	IS_NPC(victim)?victim->class<MAX_NPC_CLASS&&victim->class>=0?
	npc_class[victim->class] : "unknown":victim->class<MAX_PC_CLASS&&
	class_table[victim->class]->who_name&&
	class_table[victim->class]->who_name[0] != '\0'?
	class_table[victim->class]->who_name:"unknown");
/* Fix so it shows what is in class table
	victim->race<MAX_NPC_RACE&&victim->race>=0?npc_race[victim->race] : "unknown",
	victim->class<MAX_NPC_CLASS&&victim->class>=0?npc_class[victim->class] : "unknown" );
*/
    }

    if ( number_percent( ) < LEARNED(ch, gsn_peek) )
    {
	ch_printf( ch, "\n\rYou peek at %s inventory:\n\r",
	  victim->sex == 1 ? "his" : victim->sex == 2 ? "her" : "its" );
	show_list_to_char( victim->first_carrying, ch, TRUE, TRUE );
	learn_from_success( ch, gsn_peek );
    }
    else
      if ( ch->pcdata->learned[gsn_peek] > 0 )
        learn_from_failure( ch, gsn_peek );

    return;
}


void show_char_to_char( CHAR_DATA *list, CHAR_DATA *ch )
{
    CHAR_DATA *rch;

    for ( rch = list; rch; rch = rch->next_in_room )
    {
	if ( rch == ch )
	    continue;

	if ( can_see( ch, rch ) )
	{
	    show_char_to_char_0( rch, ch );
	}
	else if ( room_is_dark( ch->in_room )
	&&        IS_AFFECTED(rch, AFF_INFRARED ) 
        && !(!IS_NPC(rch) && IS_IMMORTAL(rch)) )
	{
	    set_char_color( AT_BLOOD, ch );
	    send_to_char( "The red form of a living creature is here.\n\r", ch );
	}
    }

    return;
}



bool check_blind( CHAR_DATA *ch )
{
    if ( !IS_NPC(ch) && xIS_SET(ch->act, PLR_HOLYLIGHT) )
	return TRUE;

/*	
    if ( IS_AFFECTED(ch, AFF_TRUESIGHT) )
      return TRUE;
*/

    if ( IS_AFFECTED(ch, AFF_BLIND) )
    {
	send_to_char( "You can't see a thing!\n\r", ch );
	return FALSE;
    }

    return TRUE;
}

/*
 * Returns classical DIKU door direction based on text in arg	-Thoric
 */
int get_door( char *arg )
{
    int door;

	 if ( !str_cmp( arg, "n"  ) || !str_cmp( arg, "north"	  ) ) door = 0;
    else if ( !str_cmp( arg, "e"  ) || !str_cmp( arg, "east"	  ) ) door = 1;
    else if ( !str_cmp( arg, "s"  ) || !str_cmp( arg, "south"	  ) ) door = 2;
    else if ( !str_cmp( arg, "w"  ) || !str_cmp( arg, "west"	  ) ) door = 3;
    else if ( !str_cmp( arg, "u"  ) || !str_cmp( arg, "up"	  ) ) door = 4;
    else if ( !str_cmp( arg, "d"  ) || !str_cmp( arg, "down"	  ) ) door = 5;
    else if ( !str_cmp( arg, "ne" ) || !str_cmp( arg, "northeast" ) ) door = 6;
    else if ( !str_cmp( arg, "nw" ) || !str_cmp( arg, "northwest" ) ) door = 7;
    else if ( !str_cmp( arg, "se" ) || !str_cmp( arg, "southeast" ) ) door = 8;
    else if ( !str_cmp( arg, "sw" ) || !str_cmp( arg, "southwest" ) ) door = 9;
    else door = -1;
    return door;
}

void print_compass( CHAR_DATA *ch )
{
    EXIT_DATA *pexit;
    int exit_info[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    static char * const exit_colors [] = { "&w", "&Y", "&C", "&P", "&R", "&r" };
    for( pexit = ch->in_room->first_exit; pexit; pexit = pexit->next )
    {
	if( !pexit->to_room || IS_SET( pexit->exit_info, EX_HIDDEN ) ||
	    ( IS_SET( pexit->exit_info, EX_SECRET ) && IS_SET( pexit->exit_info, EX_CLOSED ) ) )
	   continue;
	if( IS_SET( pexit->exit_info, EX_WINDOW ) )
	    exit_info[pexit->vdir] = 2;
	else if( IS_SET( pexit->exit_info, EX_SECRET ) )
	    exit_info[pexit->vdir] = 3;
	else if( IS_SET( pexit->exit_info, EX_CLOSED ) )
	    exit_info[pexit->vdir] = 4;
	else if( IS_SET( pexit->exit_info, EX_LOCKED ) )
	    exit_info[pexit->vdir] = 5;
	else
	    exit_info[pexit->vdir] = 1;
    }
    set_char_color( AT_RMNAME, ch );
    ch_printf_color( ch, "\n\r%-38s&W  %s%s    %s%s    %s%s\n\r",
	ch->in_room->name,
	exit_colors[exit_info[DIR_NORTHWEST]], exit_info[DIR_NORTHEAST] ? "NW" : "- ",
	exit_colors[exit_info[DIR_NORTH]], exit_info[DIR_NORTH] ? "N" : "-", exit_colors[exit_info[DIR_NORTHEAST]],
	exit_info[DIR_NORTHEAST] ? "NE" : " -" );
    if( IS_IMMORTAL( ch ) && xIS_SET( ch->act, PLR_ROOMVNUM ) )
	ch_printf_color( ch, "&W-<---- &YVnum: %6d &W----------------->- ", ch->in_room->vnum );
    else
	send_to_char_color( "&W-&R>>>>>&W--------------------------------&z>&W ", ch );
    ch_printf_color( ch, "%s%s&W<-%s%s&W-&B(*)&W-%s%s&W->%s%s\n\r", exit_colors[exit_info[DIR_WEST]], exit_info[DIR_WEST] ? "W" : "-",
	exit_colors[exit_info[DIR_UP]], exit_info[DIR_UP] ? "U" : "-", exit_colors[exit_info[DIR_DOWN]], exit_info[DIR_DOWN] ? "D" : "-",
	exit_colors[exit_info[DIR_EAST]], exit_info[DIR_EAST] ? "E" : "-" );
    ch_printf_color( ch, "                                        %s%s    %s%s    %s%s\n\r\n\r",
	exit_colors[exit_info[DIR_SOUTHWEST]], exit_info[DIR_SOUTHWEST] ? "SW" : "- ", exit_colors[exit_info[DIR_SOUTH]],
	exit_info[DIR_SOUTH] ? "S" : "-", exit_colors[exit_info[DIR_SOUTHEAST]], exit_info[DIR_SOUTHEAST] ? "SE" : " -" );
    return;
}


void show_identified_obj(CHAR_DATA *ch, OBJ_DATA *obj)
{
    AFFECT_DATA *paf;
    SKILLTYPE *sktmp;

    ch_printf( ch, "&CObject '&R%s&C' is &Y%s&D", obj->short_descr, aoran(item_type_name(obj)));
    if ( !IS_LIGHT(obj) && obj->wear_flags-1 > 0 )
        ch_printf(ch, "&C, with wear location:  &Y%s&D\n\r", flag_string(obj->wear_flags-1, w_flags) );
    else
        send_to_char( "&C.&D\n\r", ch );
    ch_printf( ch, "&CObject key words: &Y%s&D\n\r", obj->name);
    ch_printf( ch, "&CSpecial properties:  %s\n\rIts weight is &W%d&C and value is &W%d&D.\n\r", 
        extra_bit_name(&obj->extra_flags), obj->weight, obj->cost);

    switch ( obj->item_type )
    {
        case ITEM_CONTAINER:
            ch_printf( ch, "&G%s appears to be %s.\n\r", capitalize(obj->short_descr),
            obj->value[0] < 76  ? "of a &Ysmall capacity&D"           :
            obj->value[0] < 150 ? "of a &Ysmall to medium capacity&D" :
            obj->value[0] < 300 ? "of a &Ymedium capacity&D"          :
            obj->value[0] < 550 ? "of a &Ymedium to large capacity&D" :
            obj->value[0] < 751 ? "of a &Ylarge capacity&D"           :
            "of a &Ygiant capacity&D" );
            break;	

        case ITEM_PILL:
        case ITEM_SCROLL:
        case ITEM_POTION:
            ch_printf( ch, "&GLevel &W%d&G spells of:", obj->value[0] );

            if ( obj->value[1] >= 0 && (sktmp=get_skilltype(obj->value[1])) != NULL )
                ch_printf(ch, " &C'&Y%s&C'", sktmp->name);

            if ( obj->value[2] >= 0 && (sktmp=get_skilltype(obj->value[2])) != NULL )
                ch_printf(ch, " &C'&Y%s&C'", sktmp->name);

            if ( obj->value[3] >= 0 && (sktmp=get_skilltype(obj->value[3])) != NULL )
                ch_printf(ch, " &C'&Y%s&C'", sktmp->name);

            send_to_char( ".&D\n\r", ch );
            break;

        case ITEM_SALVE:
            ch_printf( ch, "&GHas &w%d&C(&W%d&C)&G applications of level &W%d",
            obj->value[1], obj->value[2], obj->value[0] );
            if ( obj->value[4] >= 0 && (sktmp=get_skilltype(obj->value[4])) != NULL )
                ch_printf(ch, " &C'&Y%s&C'", sktmp->name);
            if ( obj->value[5] >= 0 && (sktmp=get_skilltype(obj->value[5])) != NULL )
                ch_printf(ch, " &C'&Y%s&C'", sktmp->name);
            send_to_char( ".&D\n\r", ch );
            break;

        case ITEM_WAND:
        case ITEM_STAFF:
            ch_printf( ch, "&GHas &w%d&C(&W%d&C)&G charges of level &W%d",
            obj->value[1], obj->value[2], obj->value[0] );

            if ( obj->value[3] >= 0 && (sktmp=get_skilltype(obj->value[3])) != NULL )
                ch_printf(ch, " &C'&Y%s&C'", sktmp->name);

            send_to_char( ".&D\n\r", ch );
            break;

        case ITEM_WEAPON:
        case ITEM_ARTWEAPON:
            ch_printf( ch, "&GDamage is &W%d&G to &W%d&G &c(&Caverage &W%d&c)%s\n\r", obj->value[1], obj->value[2],
                ( obj->value[1] + obj->value[2] ) / 2, IS_OBJ_STAT( obj, ITEM_POISONED) ? "&G, and is &Rpoisonous&G.&D" : "&G.&D" );

            // Begin Weapon Identification Snippet by Joe Fabiano 
            switch(obj->value[3])
            {
                case 0: case 10:
                    ch_printf( ch, "&GWeapon Type: &WPugilism&D\n\r" ); break;
                case 1: case 3:
                    ch_printf( ch, "&GWeapon Type: &WLong Blade&D\n\r" ); break;
                case 2: case 11:
                    ch_printf( ch, "&GWeapon Type: &WShort Blade&D\n\r" ); break;
                case 4:
                    ch_printf( ch, "&GWeapon Type: &WFlexible Arms&D\n\r" ); break;
                case 5: case 22: case 23:
                    ch_printf( ch, "&GWeapon Type: &WTalonous Arms&D\n\r" ); break;
                case 6: case 7: case 8:
                    ch_printf( ch, "&GWeapon Type: &WBludgeon&D\n\r" ); break;
                case 9: case 18: case 19: case 25:
                    ch_printf( ch, "&GWeapon Type: &WAxes&D\n\r" ); break;
                case 12: case 17: case 24:
                    ch_printf( ch, "&GWeapon Type: &WPolearms&D\n\r" ); break;
                case 13: case 14: case 15: case 16:
                    ch_printf( ch, "&GWeapon Type: &WMissile Weapon&D\n\r" ); break;
                case 20:
                    ch_printf( ch, "&GWeapon Type: &WExotic Arms&D\n\r" ); break;
                case 21:
                    ch_printf( ch, "&GWeapon Type: &WShieldwork&D\n\r" ); break;
            }
            break;

        case ITEM_ARMOR:
        case ITEM_ARTARMOR:
            ch_printf( ch, "&GArmor class is &W%d&G.&D\n\r", obj->value[0] );
            break;
        }

    for ( paf = obj->pIndexData->first_affect; paf; paf = paf->next )
        showaffect( ch, paf );

    for ( paf = obj->first_affect; paf; paf = paf->next )
        showaffect( ch, paf );
}
void do_look( CHAR_DATA *ch, char *argument )
{
    char arg  [MAX_INPUT_LENGTH];
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];
    char arg3 [MAX_INPUT_LENGTH];
    EXIT_DATA *pexit;
    CHAR_DATA *victim;
    OBJ_DATA *obj;
    ROOM_INDEX_DATA *original;
    char *pdesc;
    sh_int door;
    int number, cnt;

    if ( !ch->desc )
	return;

    if ( ch->position < POS_SLEEPING )
    {
	send_to_char( "You can't see anything but stars!\n\r", ch );
	return;
    }

    if ( ch->position == POS_SLEEPING )
    {
	send_to_char( "You can't see anything, you're sleeping!\n\r", ch );
	return;
    }

    if ( !check_blind( ch ) )
	return;

    if ( !IS_NPC(ch)
    &&   !xIS_SET(ch->act, PLR_HOLYLIGHT)
    &&   room_is_dark( ch->in_room ) )
    {
	set_char_color( AT_DGREY, ch );
	send_to_char( "It is pitch black ... \n\r", ch );
	show_char_to_char( ch->in_room->first_person, ch );
	return;
    }

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    argument = one_argument( argument, arg3 );

    if ( arg1[0] == '\0' || !str_cmp( arg1, "auto" ) )
    {
/*	switch ( ch->inter_page )    / rmenu /
	{ 
	   case ROOM_PAGE_A : do_rmenu(ch,"a");
			      break;
	   case ROOM_PAGE_B : do_rmenu(ch,"b");
			      break;
	   case ROOM_PAGE_C : do_rmenu(ch,"c");
			      break;
        }
*/
	/* 'look' or 'look auto' */
	if( xIS_SET( ch->act, PLR_COMPASS ) )
        {
	    print_compass( ch );
	    set_char_color( AT_RMDESC, ch );
	}
	else
	{
	    set_char_color( AT_RMNAME, ch );
		if(IS_IMMORTAL(ch))
		{
			send_to_char( ch->in_room->name, ch );
		    ch_printf_color( ch, " &W[&C%8d&W]&D\n\r", ch->in_room->vnum );
		}
		else
		{
			send_to_char( ch->in_room->name, ch );
			send_to_char( "\n\r", ch );
		}
		if(IS_IMMORTAL(ch)) 
		{
			char *sect;
			ch_printf_color( ch, "&cArea: &C%-25s &cFilename: &C%-25s&D\n\r",
				ch->in_room->area->name, ch->in_room->area->filename );
			switch( ch->in_room->sector_type ) {
			default:			sect = "??\?!";		break;
			case SECT_INSIDE:		sect = "Inside";	break;
			case SECT_CITY:			sect = "City";		break;
			case SECT_FIELD:		sect = "Field";		break;
			case SECT_FOREST:		sect = "Forest";	break;
			case SECT_HILLS:		sect = "Hills";		break;
			case SECT_MOUNTAIN:		sect = "Mountains";	break;
			case SECT_WATER_SWIM:		sect = "Swim";		break;
			case SECT_WATER_NOSWIM:		sect = "Noswim";	break;
			case SECT_UNDERWATER:		sect = "Underwater";	break;
			case SECT_AIR:			sect = "Air";		break;
			case SECT_DESERT:		sect = "Desert";	break;
			case SECT_OCEANFLOOR:		sect = "Oceanfloor";	break;
			case SECT_UNDERGROUND:		sect = "Underground";	break;
			case SECT_LAVA:			sect = "Lava";		break;
			case SECT_SWAMP:		sect = "Swamp";		break;
			case SECT_BOAT:			sect = "Boat";		break;
			}
			ch_printf_color( ch, "&cSector: &C%-15s&D\n\r", sect);
			ch_printf_color( ch, "&cLighting: &C%-3d &cFlags: &C%s&D\n\r", 
				ch->in_room->light, flag_string(ch->in_room->room_flags, r_flags) );
		}
	    set_char_color( AT_RMDESC, ch );
	}

	if ( arg1[0] == '\0'
	|| ( !IS_NPC(ch) && !xIS_SET(ch->act, PLR_BRIEF) ) )
	    send_to_char_color( ch->in_room->description, ch );
		
	if ( !IS_NPC(ch) && xIS_SET(ch->act, PLR_AUTOMAP) )   /* maps */
	{
	    if(ch->in_room->map != NULL)
	    {
	       do_lookmap(ch, NULL);
	    }
	}

	if ( !IS_NPC(ch) && xIS_SET(ch->act, PLR_AUTOEXIT) )
	    do_exits( ch, "auto" );
	if(IS_IMMORTAL(ch))
	{
	    EXIT_DATA *pexit;
		int cnt;
		static char *dir_text[] = { "n", "e", "s", "w", "u", "d", "ne", "nw", "se", "sw", "?" };
		for(cnt = 0, pexit = ch->in_room->first_exit; pexit; pexit = pexit->next )
			ch_printf_color( ch,
			  "&c%2d) &W%-2s &cto &W%-5d&c.  Key: &C%-2d&D\n\r",
				++cnt,
				dir_text[pexit->vdir],
				pexit->to_room ? pexit->to_room->vnum : 0,
				pexit->key );

	}

 	if ( xIS_SET(ch->act, PLR_STALK) && !IS_NPC(ch)) /* ARE we tracking */
        {
            do_track( ch, ch->pcdata->stalking );
        }

	send_to_char( "\n\r", ch );
	show_list_to_char( ch->in_room->first_content, ch, FALSE, FALSE );
	show_char_to_char( ch->in_room->first_person,  ch );
	if(!IS_NPC(ch)) call_lua (ch, "looking", NULL);
	return;
    }

	if ( !str_cmp( arg1, "under" ) )
    {
	int count;

	/* 'look under' */
	if ( arg2[0] == '\0' )
	{
	    send_to_char( "Look beneath what?\n\r", ch );
	    return;
	}

	if ( ( obj = get_obj_here( ch, arg2 ) ) == NULL )
	{
	    send_to_char( "You do not see that here.\n\r", ch );
	    return;
	}
	if ( !CAN_WEAR( obj, ITEM_TAKE ) && ch->level < sysdata.level_getobjnotake )
	{
	    send_to_char( "You can't seem to get a grip on it.\n\r", ch );
	    return;
	}
	if ( ch->carry_weight + obj->weight > can_carry_w( ch ) )
	{
	    send_to_char( "It's too heavy for you to look under.\n\r", ch );
	    return;
	}
	count = obj->count;
	obj->count = 1;
	act( AT_PLAIN, "You lift $p and look beneath it:", ch, obj, NULL, TO_CHAR );
	act( AT_PLAIN, "$n lifts $p and looks beneath it:", ch, obj, NULL, TO_ROOM );
	obj->count = count;
	if ( IS_OBJ_STAT( obj, ITEM_COVERING ) )
	   show_list_to_char( obj->first_content, ch, TRUE, TRUE );
	else
	   send_to_char( "Nothing.\n\r", ch );
	if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
	return;
    }

    if ( !str_cmp( arg1, "i" ) || !str_cmp( arg1, "in" ) )
    {
	int count;

	/* 'look in' */
	if ( arg2[0] == '\0' )
	{
	    send_to_char( "Look in what?\n\r", ch );
	    return;
	}

	if ( ( obj = get_obj_here( ch, arg2 ) ) == NULL )
	{
	    send_to_char( "You do not see that here.\n\r", ch );
	    return;
	}

	switch ( obj->item_type )
	{
	default:
	    send_to_char( "That is not a container.\n\r", ch );
	    break;

	case ITEM_DRINK_CON:
	    if ( obj->value[1] == 0 )
	    {
		send_to_char( "It is empty.\n\r", ch );
	        if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
		break;
	    }

	    	/* exam addition for the new liquidtable	-Nopey */
	{
	  LIQ_TABLE *liq = get_liq_vnum(obj->value[2]);
	  if(obj->value[1] < 0) // hack to create endless drink containers -Darwin
		  ch_printf(ch, "It's filled with a %s liquid and looks bottomless.\n\r", liq->color);
	  else
		ch_printf(ch, "It's %s full of a %s liquid.\n\r",
	    obj->value[1] <	obj->value[0] / 4 ? "less than" :
	    obj->value[1] < 3 * obj->value[0] / 4 ? "about"	: "more than",
	    liq->color );
	}

	    if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
	    break;

	case ITEM_PORTAL:
	    for ( pexit = ch->in_room->first_exit; pexit; pexit = pexit->next )
	    {
		if ( pexit->vdir == DIR_PORTAL
		&&   IS_SET(pexit->exit_info, EX_PORTAL) )
		{
		    if ( room_is_private( pexit->to_room )
		    &&   get_trust(ch) < sysdata.level_override_private )
		    {
			set_char_color( AT_WHITE, ch );
			send_to_char( "That room is private buster!\n\r", ch );
			return;
		    }
		    original = ch->in_room;
		    char_from_room( ch );
		    char_to_room( ch, pexit->to_room );
		    do_look( ch, "auto" );
		    char_from_room( ch );
		    char_to_room( ch, original );
		    return;
		}
	    }
	    send_to_char( "You see swirling chaos...\n\r", ch );
	    break;
	case ITEM_CONTAINER:
	case ITEM_QUIVER:
	case ITEM_CORPSE_NPC:
	case ITEM_CORPSE_PC:
	    if ( IS_SET(obj->value[1], CONT_CLOSED) )
	    {
		send_to_char( "It is closed.\n\r", ch );
		break;
	    }

	case ITEM_KEYRING:
	    count = obj->count;
	    obj->count = 1;
	    if ( obj->item_type == ITEM_CONTAINER )
		act( AT_PLAIN, "$p contains:", ch, obj, NULL, TO_CHAR );
	    else
		act( AT_PLAIN, "$p holds:", ch, obj, NULL, TO_CHAR );
	    obj->count = count;
	    show_list_to_char_type( obj->first_content, ch, TRUE, TRUE, atoi(argument));
	    if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
	    break;
	}
	return;
    }

    if ( (pdesc=get_extra_descr(arg1, ch->in_room->first_extradesc)) != NULL )
    {
	send_to_char_color( pdesc, ch );
	return;
    }

    door = get_door(arg1);
    if ( (pexit=find_door(ch, arg1, TRUE)) != NULL )
    {
	if ( IS_SET(pexit->exit_info, EX_CLOSED)
	&&  !IS_SET(pexit->exit_info, EX_WINDOW) )
	{
	    if ( (IS_SET(pexit->exit_info, EX_SECRET)
	    ||    IS_SET(pexit->exit_info, EX_DIG)) && door != -1 )
		send_to_char( "Nothing special there.\n\r", ch );
	    else
		act( AT_PLAIN, "The $d is closed.", ch, NULL, pexit->keyword, TO_CHAR );
	    return;
	}
	if ( IS_SET( pexit->exit_info, EX_BASHED ) )
	    act(AT_RED, "The $d has been bashed from its hinges!",ch, NULL, pexit->keyword, TO_CHAR);

	if ( pexit->description && pexit->description[0] != '\0' )
	    send_to_char( pexit->description, ch );
	else
	    send_to_char( "Nothing special there.\n\r", ch );

	/*
	 * Ability to look into the next room			-Thoric
	 */
	if ( pexit->to_room
	&& ( IS_AFFECTED( ch, AFF_SCRYING )
	||   ch->class == CLASS_THIEF
        ||   ch->dualclass == CLASS_THIEF
	||   IS_SET( pexit->exit_info, EX_xLOOK )
	||   get_trust(ch) >= LEVEL_IMMORTAL ) )
	{
	    if ( !IS_SET( pexit->exit_info, EX_xLOOK )
	    &&    get_trust( ch ) < LEVEL_IMMORTAL )
	    {
		set_char_color( AT_MAGIC, ch );
		send_to_char( "You attempt to scry...\n\r", ch );
		/*
		 * Change by Narn, Sept 96 to allow characters who don't have the
		 * scry spell to benefit from objects that are affected by scry.
		 */
		if (!IS_NPC(ch) )
		{
		    int percent = LEARNED(ch, skill_lookup("scry") );
		    if ( !percent )
		    {
			if ( ch->class == CLASS_THIEF )
			    percent = 95;
			else
			    percent = 55;	/* 95 was too good -Thoric */
		    }
 
		    if ( number_percent( ) > percent ) 
		    {
			send_to_char( "You fail.\n\r", ch );
			return;
		    }
		}
	    }
	    if ( room_is_private( pexit->to_room )
	    &&   get_trust(ch) < sysdata.level_override_private )
	    {
		set_char_color( AT_WHITE, ch );
		send_to_char( "That room is private buster!\n\r", ch );
		return;
	    }
	    original = ch->in_room;
	    char_from_room( ch );
	    char_to_room( ch, pexit->to_room );
	    do_look( ch, "auto" );
	    char_from_room( ch );
	    char_to_room( ch, original );
	}
	return;
    }
    else
    if ( door != -1 )
    {
	send_to_char( "Nothing special there.\n\r", ch );
	return;
    }

    if ( (victim = get_char_room(ch, arg1)) != NULL )
    {
	show_char_to_char_1( victim, ch );
	return;
    }


    /* finally fixed the annoying look 2.obj desc bug	-Thoric */
    number = number_argument( arg1, arg );
    for ( cnt = 0, obj = ch->last_carrying; obj; obj = obj->prev_content )
    {
	if ( can_see_obj( ch, obj ) )
	{
	    if ( (pdesc=get_extra_descr(arg, obj->first_extradesc)) != NULL )
	    {
		if ( (cnt += obj->count) < number )
		  continue;
		send_to_char_color( pdesc, ch );
        if(IS_OBJ_STAT(obj, ITEM_IDED))
            show_identified_obj(ch, obj);
        if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
            return;
	    }

	    if ( (pdesc=get_extra_descr(arg, obj->pIndexData->first_extradesc)) != NULL )
	    {
		if ( (cnt += obj->count) < number )
		  continue;
		send_to_char_color( pdesc, ch );
        if(IS_OBJ_STAT(obj, ITEM_IDED))
            show_identified_obj(ch, obj);
	        if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
		return;
	    }
	    if ( nifty_is_name_prefix( arg, obj->name ) )
	    {
		if ( (cnt += obj->count) < number )
		  continue;
		pdesc = get_extra_descr( obj->name, obj->pIndexData->first_extradesc );
		if ( !pdesc )
		  pdesc = get_extra_descr( obj->name, obj->first_extradesc );
		if ( !pdesc )
		  send_to_char_color( "You see nothing special.\r\n", ch );
		else
		  send_to_char_color( pdesc, ch );
        if(IS_OBJ_STAT(obj, ITEM_IDED))
            show_identified_obj(ch, obj);

		if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
		  return;
	    }
	}
    }

    for ( obj = ch->in_room->last_content; obj; obj = obj->prev_content )
    {
	if ( can_see_obj( ch, obj ) )
	{
	    if ( (pdesc=get_extra_descr(arg, obj->first_extradesc)) != NULL )
	    {
		if ( (cnt += obj->count) < number )
		  continue;
		send_to_char_color( pdesc, ch );
        if(IS_OBJ_STAT(obj, ITEM_IDED))
            show_identified_obj(ch, obj);

	        if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
		return;
	    }

	    if ( (pdesc=get_extra_descr(arg, obj->pIndexData->first_extradesc)) != NULL )
	    {
		if ( (cnt += obj->count) < number )
		  continue;
		send_to_char_color( pdesc, ch );
        if(IS_OBJ_STAT(obj, ITEM_IDED))
            show_identified_obj(ch, obj);

	        if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
		return;
	    }
	    if ( nifty_is_name_prefix( arg, obj->name ) )
	    {
		if ( (cnt += obj->count) < number )
		  continue;
		pdesc = get_extra_descr( obj->name, obj->pIndexData->first_extradesc );
		if ( !pdesc )
		  pdesc = get_extra_descr( obj->name, obj->first_extradesc );
		if ( !pdesc )
		  send_to_char( "You see nothing special.\r\n", ch );
		else
		  send_to_char_color( pdesc, ch );
        if(IS_OBJ_STAT(obj, ITEM_IDED))
            show_identified_obj(ch, obj);

		if( EXA_prog_trigger ) oprog_examine_trigger( ch, obj );
		  return;
	    }
	}
    }

    send_to_char( "You do not see that here.\n\r", ch );
    return;
}

void show_race_line( CHAR_DATA *ch, CHAR_DATA *victim )
{
    if(IS_NPC(victim))
        return;

    char *buf;

    call_va(L_mud, "show_race_line", "sii>s", victim != ch? PERS(victim, ch): "You" , victim->height, victim->weight, &buf);
    send_to_char(buf, ch);
    return;
    
}


void show_condition( CHAR_DATA *ch, CHAR_DATA *victim )
{
    char *buf;

    set_char_color( AT_IMMORT, ch );
    call_va(L_mud, "show_condition", "sii>s", victim != ch? PERS(victim, ch) : "You", victim->hit, victim->max_hit, &buf);
    send_to_char( buf, ch );
    return;
}

/* A much simpler version of look, this function will show you only
the condition of a mob or pc, or if used without an argument, the
same you would see if you enter the room and have config +brief.
-- Narn, winter '96
*/
void do_glance( CHAR_DATA *ch, char *argument )
{
  char arg1 [MAX_INPUT_LENGTH];
  CHAR_DATA *victim;
  bool brief;
 
  if ( !ch->desc )
    return;
 
  if ( ch->position < POS_SLEEPING )
  {
    send_to_char( "You can't see anything but stars!\n\r", ch );
    return;
  }
 
  if ( ch->position == POS_SLEEPING )
  {
    send_to_char( "You can't see anything, you're sleeping!\n\r", ch );
    return;
  }
 
  if ( !check_blind( ch ) )
    return;

  set_char_color( AT_ACTION, ch ); 
  argument = one_argument( argument, arg1 );
 
  if ( arg1[0] == '\0' )
  {
    if ( xIS_SET(ch->act, PLR_BRIEF) )
	brief = TRUE;
    else
	brief = FALSE;
    xSET_BIT( ch->act, PLR_BRIEF );
    do_look( ch, "auto" );
    if ( !brief )
	xREMOVE_BIT(ch->act, PLR_BRIEF);
    return;
  }
 
  if ( ( victim = get_char_room( ch, arg1 ) ) == NULL )
  {
    send_to_char( "They're not here.\n\r", ch );
    return;
  }
  else
  {
    if ( can_see( victim, ch ) )
    {
	act( AT_ACTION, "$n glances at you.", ch, NULL, victim, TO_VICT );
	act( AT_ACTION, "$n glances at $N.",  ch, NULL, victim, TO_NOTVICT );
    }
    if ( IS_IMMORTAL( ch ) && victim != ch )
    {
	if ( IS_NPC( victim ) )
	    ch_printf( ch, "Mobile #%d '%s' ",
		victim->pIndexData->vnum, victim->name );
	else
	    ch_printf( ch, "%s ", victim->name );
	ch_printf( ch, "is a level %d %s %s.\n\r",
	    victim->level,
	    IS_NPC(victim)?victim->race<MAX_NPC_RACE&&victim->race>=0?
            npc_race[victim->race] : "unknown":victim->race<MAX_PC_RACE&&
            race_table[victim->race]->race_name&&
            race_table[victim->race]->race_name[0] != '\0'?
            race_table[victim->race]->race_name:"unknown",
            IS_NPC(victim)?victim->class<MAX_NPC_CLASS&&victim->class>=0?
            npc_class[victim->class] : "unknown":victim->class<MAX_PC_CLASS&&
            class_table[victim->class]->who_name&&
            class_table[victim->class]->who_name[0] != '\0'?
            class_table[victim->class]->who_name:"unknown");
/* New Change
	    victim->race<MAX_NPC_RACE&&victim->race>=0?npc_race[victim->race] : "unknown",
	    victim->class<MAX_NPC_CLASS&&victim->class>=0?npc_class[victim->class] : "unknown" );
*/
    }
    show_condition( ch, victim );

    return;
  }

  return;
}


void do_examine( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    BOARD_DATA *board;
    sh_int dam;
    sh_int value;

    if ( !argument )
    {
	bug( "do_examine: null argument.", 0);
	return;
    }

    if ( !ch )
    {
	bug( "do_examine: null ch.", 0);
	return;
    }

    argument = one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
	send_to_char( "Examine what?\n\r", ch );
	return;
    }

    EXA_prog_trigger = FALSE;
    do_look( ch, arg );
    EXA_prog_trigger = TRUE;

    /*
     * Support for looking at boards, checking equipment conditions,
     * and support for trigger positions by Thoric
     */
    if ( (obj = get_obj_here(ch, arg)) != NULL )
    {
	if ( (board = get_board(obj)) != NULL )
	{
	    if ( board->num_posts )
		ch_printf( ch, "There are about %d notes posted here.  Type 'note list' to list them.\n\r", board->num_posts );
	    else
		send_to_char( "There aren't any notes posted here.\n\r", ch );
	}

	switch ( obj->item_type )
	{
	default:
	    break;
	case ITEM_FIRE:
		sprintf( buf, "The fire is burning at %d degrees.\n\r", obj->timer * 50);
		send_to_char( buf, ch);
		break;

    case ITEM_COMP:
		switch(obj->pIndexData->vnum)
		{
		default:
			ch_printf( ch, "Has %d uses.\n\r", obj->value[0]);
			break;
		case 23: // skins
			ch_printf( ch, "Is made from %s flesh.\n\r", npc_race[obj->value[5]]);
			break;
		case 70: // woods
		case 71:
		case 72:
			ch_printf( ch, "Has a rarity value of %d and a combustion value of %d.\n\r",
				obj->value[4], obj->value[0] * (obj->value[4]+1));
			break;
		case 73: // mined mineral
		case 74: // mined gem
			ch_printf( ch, "Has a rarity value of %d.\n\r", obj->value[4]);
			break;
		case 75: // mined coal
			ch_printf( ch, "Has a combustion value of %d.\n\r", obj->value[0] * (obj->value[4]+1));
			break;
		}
		break;

	case ITEM_ARMOR:
	case ITEM_ARTARMOR:
	    if ( obj->value[1] == 0 )
	      obj->value[1] = obj->value[0];
	    if ( obj->value[1] == 0 )
	      obj->value[1] = 1;
	    dam = (sh_int) ((obj->value[0] * 10) / obj->value[1]);
	    strcpy( buf, "As you look more closely, you notice that it is ");
	    if (dam >= 10) strcat( buf, "in superb condition.");
       else if (dam ==  9) strcat( buf, "in very good condition.");
       else if (dam ==  8) strcat( buf, "in good shape.");
       else if (dam ==  7) strcat( buf, "showing a bit of wear.");
       else if (dam ==  6) strcat( buf, "a little run down.");
       else if (dam ==  5) strcat( buf, "in need of repair.");
       else if (dam ==  4) strcat( buf, "in great need of repair.");
       else if (dam ==  3) strcat( buf, "in dire need of repair.");
       else if (dam ==  2) strcat( buf, "very badly worn.");
       else if (dam ==  1) strcat( buf, "practically worthless.");
       else if (dam <=  0) strcat( buf, "broken.");
	    strcat( buf, "\n\r" );
	    send_to_char( buf, ch );
	    break;

	case ITEM_WEAPON:
	case ITEM_ARTWEAPON:
	    dam = INIT_WEAPON_CONDITION - obj->value[0];
	    strcpy( buf, "As you look more closely, you notice that it is ");
	    if (dam ==  0) strcat( buf, "in superb condition.");
       else if (dam ==  1) strcat( buf, "in excellent condition.");
       else if (dam ==  2) strcat( buf, "in very good condition.");
       else if (dam ==  3) strcat( buf, "in good shape.");
       else if (dam ==  4) strcat( buf, "showing a bit of wear.");
       else if (dam ==  5) strcat( buf, "a little run down.");
       else if (dam ==  6) strcat( buf, "in need of repair.");
       else if (dam ==  7) strcat( buf, "in great need of repair.");
       else if (dam ==  8) strcat( buf, "in dire need of repair.");
       else if (dam ==  9) strcat( buf, "very badly worn.");
       else if (dam == 10) strcat( buf, "practically worthless.");
       else if (dam == 11) strcat( buf, "almost broken.");
       else if (dam == 12) strcat( buf, "broken.");
	    strcat( buf, "\n\r" );
	    send_to_char( buf, ch );
	    break;

	case ITEM_COOK:
	    strcpy( buf, "As you examine it carefully you notice that it " );
	    dam = obj->value[2];
	     if (dam >= 3) strcat( buf, "is burned to a crisp.");
	else if (dam == 2) strcat( buf, "is a little over cooked.");
	else if (dam == 1) strcat( buf, "is perfectly roasted.");
	else		   strcat( buf, "is raw.");
	    strcat( buf, "\n\r" );
	    send_to_char( buf, ch );
	case ITEM_FOOD:
	    if ( obj->timer > 0 && obj->value[1] > 0 )
	      dam = (obj->timer * 10) / obj->value[1];
	    else
	      dam = 10;
	    if ( obj->item_type == ITEM_FOOD )	
	      strcpy( buf, "As you examine it carefully you notice that it " );
	    else
	      strcpy( buf, "Also it " );
	    if (dam >= 10) strcat( buf, "is fresh.");
       else if (dam ==  9) strcat( buf, "is nearly fresh.");
       else if (dam ==  8) strcat( buf, "is perfectly fine.");
       else if (dam ==  7) strcat( buf, "looks good.");
       else if (dam ==  6) strcat( buf, "looks ok.");
       else if (dam ==  5) strcat( buf, "is a little stale.");
       else if (dam ==  4) strcat( buf, "is a bit stale.");
       else if (dam ==  3) strcat( buf, "smells slightly off.");
       else if (dam ==  2) strcat( buf, "smells quite rank.");
       else if (dam ==  1) strcat( buf, "smells revolting!");
       else if (dam <=  0) strcat( buf, "is crawling with maggots!");
	    strcat( buf, "\n\r" );
	    send_to_char( buf, ch );
	    break;


	case ITEM_SWITCH:
	case ITEM_LEVER:
	case ITEM_PULLCHAIN:
	    if ( IS_SET( obj->value[0], TRIG_UP ) )
		send_to_char( "You notice that it is in the up position.\n\r", ch );
	    else
		send_to_char( "You notice that it is in the down position.\n\r", ch );
	    break;
	case ITEM_BUTTON:
	    if ( IS_SET( obj->value[0], TRIG_UP ) )
		send_to_char( "You notice that it is depressed.\n\r", ch );
	    else
		send_to_char( "You notice that it is not depressed.\n\r", ch );
	    break;

/* Not needed due to check in do_look already
	case ITEM_PORTAL:
	    sprintf( buf, "in %s noprog", arg );
	    do_look( ch, buf );
	    break;
*/

        case ITEM_CORPSE_PC:
	case ITEM_CORPSE_NPC:
            {
		sh_int timerfrac = obj->timer;
		if ( obj->item_type == ITEM_CORPSE_PC )
		timerfrac = (int)obj->timer / 8 + 1; 

		switch (timerfrac)
		{
		    default:
			send_to_char( "This corpse has recently been slain.\n\r", ch );
			break;
		    case 4:
			send_to_char( "This corpse was slain a little while ago.\n\r", ch );
			break;
		    case 3:
			send_to_char( "A foul smell rises from the corpse, and it is covered in flies.\n\r", ch );
			break;
		    case 2:
			send_to_char( "A writhing mass of maggots and decay, you can barely go near this corpse.\n\r", ch );
			break;
		    case 1:
		    case 0:
			send_to_char( "Little more than bones, there isn't much left of this corpse.\n\r", ch );
			break;
		}
           }
           case ITEM_CONTAINER:
	       if ( IS_OBJ_STAT( obj, ITEM_COVERING ) )
	   	  break;
	   case ITEM_DRINK_CON:
	   case ITEM_QUIVER:
	       send_to_char( "When you look inside, you see:\n\r", ch );
	   case ITEM_KEYRING:
	       value = get_otype( argument );
	       if ( value > 0 )
	          sprintf( buf, "in %s noprog %d", arg, value);
	       else
                EXA_prog_trigger = FALSE;
                sprintf( buf, "in %s",arg );
                do_look( ch, buf );
                EXA_prog_trigger = TRUE;
	       break;
	}
	if ( IS_OBJ_STAT( obj, ITEM_COVERING ) )
	{
        EXA_prog_trigger = FALSE;
        sprintf( buf, "under %s", arg );
        do_look( ch, buf );
        EXA_prog_trigger = TRUE;
    }
	oprog_examine_trigger( ch, obj );
	if ( char_died(ch) || obj_extracted(obj) )
	    return;

	check_for_trap( ch, obj, TRAP_EXAMINE );
    }
    return;
}


void do_exits( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    EXIT_DATA *pexit;
    bool found;
    bool fAuto;

    set_char_color( AT_EXITS, ch );
    buf[0] = '\0';
    fAuto  = !str_cmp( argument, "auto" );

    if ( !check_blind(ch) )
	return;

    strcpy( buf, fAuto ? "Exits:" : "Obvious exits:\n\r" );

    found = FALSE;
    for ( pexit = ch->in_room->first_exit; pexit; pexit = pexit->next )
    {
	if ( pexit->to_room
	&&  !IS_SET(pexit->exit_info, EX_CLOSED)
	&& (!IS_SET(pexit->exit_info, EX_WINDOW)
	||   IS_SET(pexit->exit_info, EX_ISDOOR))
	&&  !IS_SET(pexit->exit_info, EX_HIDDEN) )
	{
	    found = TRUE;
	    if ( fAuto )
	    {
		strcat( buf, " " );
		strcat( buf, dir_name[pexit->vdir] );
	    }
	    else
	    {
		sprintf( buf + strlen(buf), "%-5s - %s\n\r",
		    capitalize( dir_name[pexit->vdir] ),
		    room_is_dark( pexit->to_room )
			?  "Too dark to tell"
			: pexit->to_room->name
		    );
	    }
	}
    }

    if ( !found )
	strcat( buf, fAuto ? " none.\n\r" : "None.\n\r" );
    else
      if ( fAuto )
	strcat( buf, ".\n\r" );
    send_to_char( buf, ch );
    return;
}

char *	const	day_name	[] =
{
    "the Moon", "the Twins", "the Couple", "the Storm", "the Heat",
    "the Party", "the Sun"
};

char *	const	month_name	[] =
{
    "Winter", "the Winter Wolf", "the Frost Giant", "the Old Forces",
    "the Grand Struggle", "the Spring", "Nature", "Futility", "the Dragon",
    "the Sun", "the Heat", "the Battle", "the Dark Shades", "the Shadows",
    "the Long Shadows", "the Ancient Darkness", "the Great Evil"
};

void do_time( CHAR_DATA *ch, char *argument )
{
    extern char str_boot_time[];
    extern char reboot_time[];
    char *suf;
    int day;

    day     = time_info.day + 1;

	 if ( day > 4 && day <  20 ) suf = "th";
    else if ( day % 10 ==  1       ) suf = "st";
    else if ( day % 10 ==  2       ) suf = "nd";
    else if ( day % 10 ==  3       ) suf = "rd";
    else                             suf = "th";

    set_char_color( AT_YELLOW, ch );
    ch_printf( ch,
	"It is %d o'clock %s, Day of %s, %d%s the Month of %s.\n\r"  
        "\tThe mud started up at.: %s\r"
        "\tThe system time.......: %s\r"
        "\tNext Reboot is set for: %s\n\r",

	(time_info.hour % 12 == 0) ? 12 : time_info.hour % 12,
	time_info.hour >= 12 ? "pm" : "am",
	day_name[day % 7],
	day, suf,
	month_name[time_info.month],
	str_boot_time,
	(char *) ctime( &current_time ),
	reboot_time
	);
	ch_printf(ch, "Compiled on %s at %s.\n\r", __DATE__, __TIME__);

        if( sysdata.CLEANPFILES )
	ch_printf( ch, "Next pfile cleanup is scheduled for: %s\n\r", (char *)ctime( &new_pfile_time_t ) );
	ch_printf( ch, "House of Ghouls version %s.%s.%s\n\r", HOG_VERSION_MAJOR, HOG_VERSION_MINOR, HOG_VERSION_REVISION );
    ch_printf( ch, "See &CHELP VERSION%s.%s.%s&Y for version information.\n\r", HOG_VERSION_MAJOR, HOG_VERSION_MINOR, HOG_VERSION_REVISION);

    return;
}

/*
 * Produce a description of the weather based on area weather using
 * the following sentence format:
 *		<combo-phrase> and <single-phrase>.
 * Where the combo-phrase describes either the precipitation and
 * temperature or the wind and temperature. The single-phrase
 * describes either the wind or precipitation depending upon the
 * combo-phrase.
 * Last Modified: July 31, 1997
 * Fireblade - Under Construction
 */
void do_weather(CHAR_DATA *ch, char *argument)
{
	char *combo, *single;
	//~ char buf[MAX_INPUT_LENGTH];
    char *buf;
	int temp, precip, wind;	

	if ( !IS_OUTSIDE(ch) )
	{
	    ch_printf(ch, "You can't see the sky from here.\n\r");
	    return;
	}

	temp = (ch->in_room->area->weather->temp + 3*weath_unit - 1)/
		weath_unit;
	precip = (ch->in_room->area->weather->precip + 3*weath_unit - 1)/
		weath_unit;
	wind = (ch->in_room->area->weather->wind + 3*weath_unit - 1)/
		weath_unit;
	
	if ( precip >= 3 )
	{
	    combo = preciptemp_msg[precip][temp];
	    single = wind_msg[wind];
	}
	else
	{
	    combo = windtemp_msg[wind][temp];
	    single = precip_msg[precip];
	}
	
	//~ sprintf(buf, "%s and %s.\n\r", combo, single);
    call_va(L_mud, "sprintf", "sss>s", "%s and %s.\n\r", combo, single, &buf);
	
	set_char_color(AT_BLUE, ch);
	
	ch_printf(ch, buf);
}

/*
 * Moved into a separate function so it can be used for other things
 * ie: online help editing				-Thoric
 */
HELP_DATA *get_help( CHAR_DATA *ch, char *argument )
{
    char argall[MAX_INPUT_LENGTH];
    char argone[MAX_INPUT_LENGTH];
    char argnew[MAX_INPUT_LENGTH];
    HELP_DATA *pHelp;
    int lev;

    if ( argument[0] == '\0' )
	argument = "summary";

    if ( isdigit(argument[0]) )
    {
	lev = number_argument( argument, argnew );
	argument = argnew;
    }
    else
	lev = -2;
    /*
     * Tricky argument handling so 'help a b' doesn't match a.
     */
    argall[0] = '\0';
    while ( argument[0] != '\0' )
    {
	argument = one_argument( argument, argone );
	if ( argall[0] != '\0' )
	    strcat( argall, " " );
	strcat( argall, argone );
    }

    for ( pHelp = first_help; pHelp; pHelp = pHelp->next )
    {
	if ( pHelp->level > get_trust( ch ) )
	    continue;
	if ( lev != -2 && pHelp->level != lev )
	    continue;

	if ( is_name( argall, pHelp->keyword ) )
	    return pHelp;
    }

    return NULL;
}

/*
 * LAWS command
 */
void do_laws( CHAR_DATA *ch, char *argument )
{
    //~ char buf[1024];
    char *buf;
    
    if ( argument == NULL)
	do_luahelp( ch, "laws" );
    else
    {
	//~ sprintf( buf, "law %s", argument );
    call_va(L_mud, "sprintf", "ss>s", "law %s", argument, &buf);
	do_luahelp( ch, buf );
    }
}

/*
 * Now this is cleaner
 */
void do_help( CHAR_DATA *ch, char *argument )
{
    HELP_DATA *pHelp;
    char nohelp[MAX_STRING_LENGTH];

    strcpy(nohelp, argument);

    if ( (pHelp = get_help( ch, argument )) == NULL )
    {
	send_to_char( "No help on that word.  If you are looking for help on a topic that has\n\r", ch );
        send_to_char( "multiple words, try putting those words between the ' symbols.\n\r", ch );
        append_file( ch, HELP_FILE, nohelp );
	return;
    }

    /* Make newbies do a help start. --Shaddai */ 
    if ( !IS_NPC(ch) && !str_cmp( argument, "start" ) )
	SET_BIT(ch->pcdata->flags, PCFLAG_HELPSTART);

    if ( pHelp->level >= 0 && str_cmp( argument, "imotd" ) )
    {
	send_to_pager( pHelp->keyword, ch );
	send_to_pager( "\n\r", ch );
    }

    /*
     * Strip leading '.' to allow initial blanks.
     */
    if ( pHelp->text[0] == '.' )
	send_to_pager_color( pHelp->text+1, ch );
    else
	send_to_pager_color( pHelp->text  , ch );
    return;
}

void do_news( CHAR_DATA *ch, char *argument )
{
    set_pager_color( AT_NOTE, ch );
    do_help( ch, "news" );
}

extern char * help_greeting;	/* so we can edit the greeting online */

/*
 * Help editor							-Thoric
 */
void do_hedit( CHAR_DATA *ch, char *argument )
{
    HELP_DATA *pHelp;

    if ( !ch->desc )
    {
	send_to_char( "You have no descriptor.\n\r", ch );
	return;
    }

    switch( ch->substate )
    {
	default:
	  break;
	case SUB_HELP_EDIT:
	  if ( (pHelp = ch->dest_buf) == NULL )
	  {
		bug( "hedit: sub_help_edit: NULL ch->dest_buf", 0 );
		stop_editing( ch );
		return;
	  }
	  if ( help_greeting == pHelp->text )
		help_greeting = NULL;
	  STRFREE( pHelp->text );
	  pHelp->text = copy_buffer( ch );
	  if ( !help_greeting )
		help_greeting = pHelp->text;
	  stop_editing( ch );
	  return;
    }
    if ( (pHelp = get_help(ch, argument)) == NULL )     /* new help */
    {
        HELP_DATA *tHelp;
        char argnew[MAX_INPUT_LENGTH];
        int lev;
        bool new_help = TRUE;

        for ( tHelp=first_help; tHelp; tHelp = tHelp->next )
           if ( !str_cmp( argument, tHelp->keyword) )
           {
                pHelp = tHelp;
                new_help = FALSE;
                break;
           }
        if ( new_help ) {
        if ( isdigit(argument[0]) )
        {
            lev = number_argument( argument, argnew );
            argument = argnew;
        }
        else
            lev = get_trust(ch);
        CREATE( pHelp, HELP_DATA, 1 );
        pHelp->keyword = STRALLOC( strupper(argument) );
        pHelp->text    = STRALLOC( "" );
        pHelp->level   = lev;
        add_help( pHelp );
        }
    }

    ch->substate = SUB_HELP_EDIT;
    ch->dest_buf = pHelp;
    start_editing( ch, pHelp->text );
    editor_desc_printf( ch, "Help topic, keyword '%s', level %d.", pHelp->keyword, pHelp->level );
}

/*
 * Stupid leading space muncher fix				-Thoric
 */
char *help_fix( char *text )
{
    char *fixed;

    if ( !text )
	return "";
    fixed = strip_cr(text);
    if ( fixed[0] == ' ' )
	fixed[0] = '.';
    return fixed;
}

void do_hset( CHAR_DATA *ch, char *argument )
{
    HELP_DATA *pHelp;
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];

    smash_tilde( argument );
    argument = one_argument( argument, arg1 );
    if ( arg1[0] == '\0' )
    {
	send_to_char( "Syntax: hset <field> [value] [help page]\n\r",	ch );
	send_to_char( "\n\r",						ch );
	send_to_char( "Field being one of:\n\r",			ch );
	send_to_char( "  level keyword remove save\n\r",		ch );
	return;
    }

    if ( !str_cmp( arg1, "save" ) )
    {
	FILE *fpout;

	log_string_plus( "Saving help.are...", LOG_NORMAL, LEVEL_GREATER );

	rename( "help.are", "help.are.bak" );
	fclose( fpReserve );
	if ( ( fpout = fopen( "help.are", "w" ) ) == NULL )
	{
	   bug( "hset save: fopen", 0 );
	   perror( "help.are" );
	   fpReserve = fopen( NULL_FILE, "r" );
	   return;
	}
    
	fprintf( fpout, "#HELPS\n\n" );
	for ( pHelp = first_help; pHelp; pHelp = pHelp->next )
	    fprintf( fpout, "%d %s~\n%s~\n\n",
		pHelp->level, pHelp->keyword, help_fix(pHelp->text) );

	fprintf( fpout, "0 $~\n\n\n#$\n" );
	fclose( fpout );
	fpReserve = fopen( NULL_FILE, "r" );
	send_to_char( "Saved.\n\r", ch );
	return;
    }
    if ( str_cmp( arg1, "remove" ) )
	argument = one_argument( argument, arg2 );

    if ( (pHelp = get_help(ch, argument)) == NULL )
    {
	send_to_char( "Cannot find help on that subject.\n\r", ch );
	return;
    }
    if ( !str_cmp( arg1, "remove" ) )
    {
	UNLINK( pHelp, first_help, last_help, next, prev );
	STRFREE( pHelp->text );
	STRFREE( pHelp->keyword );
	DISPOSE( pHelp );
	send_to_char( "Removed.\n\r", ch );
	return;
    }
    if ( !str_cmp( arg1, "level" ) )
    {
	pHelp->level = atoi( arg2 );
	send_to_char( "Done.\n\r", ch );
	return;
    }
    if ( !str_cmp( arg1, "keyword" ) )
    {
	STRFREE( pHelp->keyword );
	pHelp->keyword = STRALLOC( strupper(arg2) );
	send_to_char( "Done.\n\r", ch );
	return;
    }

    do_hset( ch, "" );
}

void do_hl( CHAR_DATA *ch, char *argument )
{
    send_to_char( "If you want to use HLIST, spell it out.\n\r", ch );
    return;
}

/*
 * Show help topics in a level range				-Thoric
 * Idea suggested by Gorog
 * prefix keyword indexing added by Fireblade
 */
void do_hlist( CHAR_DATA *ch, char *argument )
{
    int min, max, minlimit, maxlimit, cnt;
    char arg[MAX_INPUT_LENGTH];
    HELP_DATA *help;
    bool minfound, maxfound;
    char *idx;

    maxlimit = get_trust(ch);
    minlimit = maxlimit >= LEVEL_GREATER ? -1 : 0;
    
    min = minlimit;
    max  = maxlimit;
    
    idx = NULL;
    minfound = FALSE;
    maxfound = FALSE;
    
    for ( argument = one_argument(argument, arg); arg[0] != '\0';
	  argument = one_argument(argument, arg))
    {
	if( !isdigit(arg[0]) )
	{
 	    if ( idx )
	    {
		set_char_color(AT_GREEN, ch);
		ch_printf(ch, "You may only use a single keyword to index the list.\n\r");
		return;
	    }
	    idx = STRALLOC(arg);
    	}
	else
	{
	    if ( !minfound )
	    {
		min = URANGE(minlimit, atoi(arg), maxlimit);
		minfound = TRUE;
	    }
	    else
	    if ( !maxfound )
	    {
		max = URANGE(minlimit, atoi(arg), maxlimit);
		maxfound = TRUE;
	    }
	    else
	    {
		set_char_color(AT_GREEN, ch);
		ch_printf(ch, "You may only use two level limits.\n\r");
		return;
	    }
	}
    }
    
    if ( min > max )
    {
	int temp = min;

	min = max;
	max = temp;
    }
    
    set_pager_color( AT_GREEN, ch );
    pager_printf( ch, "Help Topics in level range %d to %d:\n\r\n\r", min, max );
    for ( cnt = 0, help = first_help; help; help = help->next )
	if ( help->level >= min && help->level <= max
	&&  (!idx || nifty_is_name_prefix(idx, help->keyword)) )
	{
	    pager_printf( ch, "  %3d %s\n\r", help->level, help->keyword );
	    ++cnt;
	}
    if ( cnt )
	pager_printf( ch, "\n\r%d pages found.\n\r", cnt );
    else
	send_to_char( "None found.\n\r", ch );

    if ( idx )
    	STRFREE(idx);
    
    return;
}


void do_who( CHAR_DATA *ch, char *argument )
{
    if(IS_NPC(ch))
        return;
	call_lua( ch, "who", argument);
    return;
}

void do_compare( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    OBJ_DATA *obj1;
    OBJ_DATA *obj2;
    int value1;
    int value2;
    char *msg;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    if ( arg1[0] == '\0' )
    {
	send_to_char( "Compare what to what?\n\r", ch );
	return;
    }

    if ( ( obj1 = get_obj_carry( ch, arg1 ) ) == NULL )
    {
	send_to_char( "You do not have that item.\n\r", ch );
	return;
    }

    if ( arg2[0] == '\0' )
    {
	for ( obj2 = ch->first_carrying; obj2; obj2 = obj2->next_content )
	{
	    if ( obj2->wear_loc != WEAR_NONE
	    &&   can_see_obj( ch, obj2 )
	    //~ &&   obj1->item_type == obj2->item_type 
	    && ( obj1->wear_flags & obj2->wear_flags & ~ITEM_TAKE) != 0 )
		break;
	}

	if ( !obj2 )
	{
	    send_to_char( "You aren't wearing anything comparable.\n\r", ch );
	    return;
	}
    }
    else
    {
	if ( ( obj2 = get_obj_carry( ch, arg2 ) ) == NULL )
	{
	    send_to_char( "You do not have that item.\n\r", ch );
	    return;
	}
    }

    msg		= NULL;
    value1	= 0;
    value2	= 0;

    if ( obj1 == obj2 )
    {
	msg = "You compare $p to itself.  It looks about the same.";
    }
    else if (obj1->wear_flags != obj2->wear_flags /*obj1->item_type != obj2->item_type*/ )
    {
	msg = "You can't compare $p and $P.";
    }
    else
    {
	switch ( obj1->item_type )
	{
	default:
	    msg = "You can't compare $p and $P.";
	    break;

	case ITEM_ARMOR:
	case ITEM_ARTARMOR:
        if(obj2->item_type == ITEM_ARMOR || obj2->item_type == ITEM_ARTARMOR)
        {
            value1 = obj1->value[0];
            value2 = obj2->value[0];
        }
        else
            msg = "You can't compare $p and $P.";
	    break;

	case ITEM_WEAPON:
	case ITEM_ARTWEAPON:
        if(obj2->item_type == ITEM_WEAPON || obj2->item_type == ITEM_ARTWEAPON)
        {
            value1 = obj1->value[1] + obj1->value[2];
            value2 = obj2->value[1] + obj2->value[2];
        }
        else
            msg = "You can't compare $p and $P.";
	    break;
	}
    }

    if ( !msg )
    {
	     if ( value1 == value2 ) msg = "$p and $P look about the same.";
	else if ( value1  > value2 ) msg = "$p looks better than $P.";
	else                         msg = "$p looks worse than $P.";
    }

    act( AT_PLAIN, msg, ch, obj1, obj2, TO_CHAR );
    if(value1 && value2)
    {
        if(obj1->tmag == obj2->tmag) 
            msg = "$p and $P have similar magic values.";
        else if (obj1->tmag > obj2->tmag) 
            msg = "$p has a higher magic value than $P."; 
        else 
            msg = "$p has a lower magic value than $P.";
        act( AT_PLAIN, msg, ch, obj1, obj2, TO_CHAR );
    }
    return;
}



void do_where( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    DESCRIPTOR_DATA *d;
    bool found;

    one_argument( argument, arg );

/*
    if ( arg[0]!='\0' 
    &&   (victim=get_char_world(ch, arg)) && !IS_NPC(victim)
    &&   IS_SET(victim->pcdata->flags, PCFLAG_DND)
    &&   get_trust(ch) < get_trust(victim) )
    {
         act( AT_PLAIN, "You didn't find any $T.", ch, NULL, arg, TO_CHAR );
         return;
   }
*/

    set_pager_color( AT_PERSON, ch );

        pager_printf( ch, "\n\rPlayers near you in %s:\n\r", ch->in_room->area->name );
	found = FALSE;
	for ( d = first_descriptor; d; d = d->next )
	    if ( (d->connected == CON_PLAYING || d->connected == CON_EDITING )
	    && ( victim = d->character ) != NULL
	    &&   !IS_NPC(victim)
	    &&   victim->in_room
	    &&   victim->in_room->area == ch->in_room->area
	    &&   can_see( ch, victim )
            //~ && ( get_trust(ch) >= get_trust(victim) 
            //~ ||   !IS_SET(victim->pcdata->flags, PCFLAG_DND) ) 
               ) /* if victim has the DND flag ch must outrank them */ 

	    {
		found = TRUE;
 		if ( CAN_PKILL( victim ) )
		  set_pager_color( AT_RED, ch );
		else
		  set_pager_color( AT_PURPLE, ch );
    
        pager_printf_color( ch, "&P%-25s ", victim->name );
		if ( IS_IMMORTAL( victim ) && victim->level > 50 )
		  send_to_pager_color( "&P(&WImmortal&P)", ch );
		//~ else
		  //~ send_to_pager( "\t\t", ch );
		pager_printf_color( ch, "&D\n\r" );
	    }
	if ( !found )
	    send_to_char( "None&D\n\r", ch );
/*
    else
    {
	found = FALSE;
	for ( victim = first_char; victim; victim = victim->next )
	    if ( victim->in_room
	    &&   victim->in_room->area == ch->in_room->area
	    &&   !IS_AFFECTED(victim, AFF_HIDE)
	    &&   !IS_AFFECTED(victim, AFF_CAMO)
	    &&   !IS_AFFECTED(victim, AFF_SNEAK)
	    &&   can_see( ch, victim )
	    &&   is_name( arg, victim->name ) )
	    {
		found = TRUE;
		pager_printf( ch, "%-28s %s\n\r",
		    PERS(victim, ch), victim->in_room->name );
		break;
	    }
	if ( !found )
	    act( AT_PLAIN, "You didn't find any $T.", ch, NULL, arg, TO_CHAR );
    }
*/

    return;
}




void do_consider( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    char *msg;
    int diff;

    one_argument( argument, arg );

    if ( arg[0] == '\0' )
    {
	send_to_char( "Consider whom?\n\r", ch );
	return;
    }

    if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
	send_to_char( "They're not here.\n\r", ch );
	return;
    }
    if ( victim == ch )
    {
	send_to_char( "You decide you're pretty sure you could take yourself in a fight.\n\r", ch );
	return;
    }
    diff = CH_LEVEL(victim) - CH_LEVEL(ch);

         if ( diff <= -10 ) msg = "You are far more experienced than $N.";
    else if ( diff <=  -5 ) msg = "$N is not nearly as experienced as you.";
    else if ( diff <=  -2 ) msg = "You are more experienced than $N.";
    else if ( diff <=   1 ) msg = "You are just about as experienced as $N.";
    else if ( diff <=   4 ) msg = "You are not nearly as experienced as $N.";
    else if ( diff <=   9 ) msg = "$N is far more experienced than you!";
    else                    msg = "$N would make a great teacher for you!";
    act( AT_CONSIDER, msg, ch, NULL, victim, TO_CHAR );

    diff = (int) (victim->max_hit - ch->max_hit) / 6;

	     if ( diff <= -200) msg = "You could squash $N under your thumb!";
    else if ( diff <= -150) msg = "You could kill $N with your hands tied!";
    else if ( diff <= -100) msg = "$N trembles at the sight of you!";
    else if ( diff <=  -50) msg = "$N is a wimp.";
    else if ( diff <=    0) msg = "$N looks weaker than you.";
    else if ( diff <=   50) msg = "$N looks about as strong as you.";
    else if ( diff <=  100) msg = "It would take a bit of luck...";
    else if ( diff <=  150) msg = "It would take a lot of luck, and equipment!";
    else if ( diff <=  200) msg = "Why don't you dig a grave for yourself first?";
    else                    msg = "You don't stand a chance against $N!";
    act( AT_CONSIDER, msg, ch, NULL, victim, TO_CHAR );

    return;
}



/*
 * Place any skill types you don't want them to be able to practice
 * normally in this list.  Separate each with a space.
 * (Uses an is_name check). -- Altrag
 */
#define CANT_PRAC "Tongue"

void do_practice( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    int sn;

    if ( IS_NPC(ch) )
	return;

/*
    if ( ch->level < 2 )
    {
	send_to_char(
	"You must be second level to practice.  Seek out monsters to kill!\n\r",
	    ch );
	return;
    }
*/
    if ( argument[0] == '\0' )
    {
	int	col;
	sh_int	lasttype, cnt;

	col = cnt = 0;	lasttype = SKILL_SPELL;
	set_pager_color( AT_MAGIC, ch );
	for ( sn = 0; sn < top_sn; sn++ )
	{
	    if ( !skill_table[sn]->name )
		break;

	    if ( strcmp(skill_table[sn]->name, "reserved") == 0 )
	    {
		if ( col % 3 != 0 )
		    send_to_pager( "\n\r", ch );
	      set_pager_color( AT_MAGIC, ch );
	      send_to_pager_color(
" ----------------------------------[&CSpells&G]----------------------------------\n\r", ch);
		col = 0;
	    }
	    if ( skill_table[sn]->type != lasttype )
	    {
		if ( !cnt )
		    send_to_pager( "                                   (none)\n\r", ch );
		else
		if ( col % 3 != 0 )
		    send_to_pager( "\n\r", ch );
		set_pager_color( AT_MAGIC, ch );
		pager_printf_color( ch,
" ----------------------------------[&C%ss&G]----------------------------------\n\r",
			 skill_tname[skill_table[sn]->type]);
		col = cnt = 0;
	    }
	    lasttype = skill_table[sn]->type;

		if(ch->pcdata->learned[sn] < 1)
		{
	    if (!IS_IMMORTAL(ch) 
	    && ( skill_table[sn]->guild != CLASS_NONE 
	       && ( !IS_GUILDED(ch)
		  || (ch->pcdata->clan->class != skill_table[sn]->guild) ) ) )
		continue;

	    if ( (ch->level < skill_table[sn]->skill_level[ch->class] && !DUAL_SKILL(ch, sn) )
	    || (!IS_IMMORTAL(ch) && skill_table[sn]->skill_level[ch->class] == 0
	         && !DUAL_SKILL(ch, sn) ) )
 	        continue;

	    if ( ch->pcdata->learned[sn] <= 0
	    &&   SPELL_FLAG(skill_table[sn], SF_SECRETSKILL) )
		continue;
		}

	    ++cnt;
	    set_pager_color( AT_MAGIC, ch );
	    pager_printf( ch, "%20.20s", skill_table[sn]->name );
	    if ( ch->pcdata->learned[sn] > 0 )
		set_pager_color( AT_SCORE, ch );
	    pager_printf( ch, " %3d%% ", ch->pcdata->learned[sn] );
	    if ( ++col % 3 == 0 )
		send_to_pager( "\n\r", ch );
	}

	if ( col % 3 != 0 )
	    send_to_pager( "\n\r", ch );
        set_pager_color( AT_MAGIC, ch );
	pager_printf( ch, "You have %d practice sessions left.\n\r",
	    ch->practice );
    }
    else
    {
	CHAR_DATA *mob;
	int adept;
	bool can_prac = TRUE;

	if ( !IS_AWAKE(ch) )
	{
	    send_to_char( "In your dreams, or what?\n\r", ch );
	    return;
	}

	for ( mob = ch->in_room->first_person; mob; mob = mob->next_in_room )
	    if ( IS_NPC(mob) && xIS_SET(mob->act, ACT_PRACTICE) )
		break;

	if ( !mob )
	{
	    send_to_char( "You can't do that here.\n\r", ch );
	    return;
	}

	if ( ch->practice <= 0 )
	{
	    act( AT_TELL, "$n tells you 'You must earn some more practice sessions.'",
		mob, NULL, ch, TO_VICT );
	    return;
	}

	sn = skill_lookup( argument );

	if ( can_prac 
          && ( ( sn == -1 )
       	       || ( !IS_NPC(ch)
	            &&  ch->level < skill_table[sn]->skill_level[ch->class] 
		    &&  !DUAL_SKILL(ch, sn))))
	{
	    act( AT_TELL, "$n tells you 'You're not ready to learn that yet...'",
		mob, NULL, ch, TO_VICT );
	    return;
	}

	if ( is_name( skill_tname[skill_table[sn]->type], CANT_PRAC ) )
	{
	    act( AT_TELL, "$n tells you 'I do not know how to teach that.'",  
		  mob, NULL, ch, TO_VICT );
	    return;
	}

	/*
	 * Skill requires a special teacher
	 */
	if ( skill_table[sn]->teachers && skill_table[sn]->teachers[0] != '\0' )
	{
	    sprintf( buf, "%d", mob->pIndexData->vnum );
	    if ( !is_name( buf, skill_table[sn]->teachers ) )
	    {
		act( AT_TELL, "$n tells you, 'I know not know how to teach that.'",
		    mob, NULL, ch, TO_VICT );
		return;
	    }
	}
	if( SPELL_FLAG(skill_table[sn], SF_NOCLASS) )
	{
		act( AT_TELL, "$n tells you, 'You have to learn that elsewhere.'", mob, NULL, ch, TO_VICT );
		return;
	}
/*
 * Guild checks - right now, cant practice guild skills - done on 
 * induct/outcast
 */
/*	
	if ( !IS_NPC(ch) && !IS_GUILDED(ch)
	&&    skill_table[sn]->guild != CLASS_NONE)
	{
	    act( AT_TELL, "$n tells you 'Only guild members can use that..'"
		mob, NULL, ch, TO_VICT );
	    return;
	}

	if ( !IS_NPC(ch) && skill_table[sn]->guild != CLASS_NONE 
	     && ch->pcdata->clan->class != skill_table[sn]->guild )
	{
	    act( AT_TELL, "$n tells you 'That can not be used by your guild.'"
		mob, NULL, ch, TO_VICT );
	    return;
	}
*/
	if ( !IS_NPC(ch) && skill_table[sn]->guild != CLASS_NONE)
	{
	    act( AT_TELL, "$n tells you 'That is only for members of guilds...'",
		mob, NULL, ch, TO_VICT );
	    return;
	}

	/*
	 * Disabled for now
	if ( mob->level < skill_table[sn]->skill_level[ch->class]
	||   mob->level < skill_table[sn]->skill_level[mob->class] )
	{
	    act( AT_TELL, "$n tells you 'You must seek another to teach you that...'",
		mob, NULL, ch, TO_VICT );
	    return;
	}
	 */
        
        if ( class_table[ch->class]->skill_adept >= class_table[ch->dualclass]->skill_adept)
        {
	   adept = class_table[ch->class]->skill_adept;    //hmm, changed by Drazuk
        }
        else
	   adept = class_table[ch->dualclass]->skill_adept;

	if ( ch->pcdata->learned[sn] >= adept )
	{
	    sprintf( buf, "$n tells you, 'I've taught you everything I can about %s.'",
		skill_table[sn]->name );
	    act( AT_TELL, buf, mob, NULL, ch, TO_VICT );
	    act( AT_TELL, "$n tells you, 'You'll have to practice it on your own now...'",
		mob, NULL, ch, TO_VICT );
	}
	else
	{
	    ch->practice--;
	    ch->pcdata->learned[sn] += int_app[get_curr_int(ch)].learn;
	    act( AT_ACTION, "You practice $T.",
		    ch, NULL, skill_table[sn]->name, TO_CHAR );
	    act( AT_ACTION, "$n practices $T.",
		    ch, NULL, skill_table[sn]->name, TO_ROOM );
	    if ( ch->pcdata->learned[sn] >= adept )
	    {
		ch->pcdata->learned[sn] = adept;
		act( AT_TELL,
		 "$n tells you. 'You'll have to practice it on your own now...'",
		 mob, NULL, ch, TO_VICT );
	    }
	}
    }
    return;
}


void do_wimpy( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    int wimpy;

    set_char_color( AT_YELLOW, ch );
    one_argument( argument, arg );
    if ( !str_cmp( arg, "max" ) )
    {
      if ( IS_PKILL( ch ) )
	wimpy = (int) ch->max_hit / 2.25;
      else
	wimpy = (int) ch->max_hit / 1.2;
    }
    else    
    if ( arg[0] == '\0' )
      wimpy = (int) ch->max_hit / 5;
    else
      wimpy = atoi( arg );

    if ( wimpy < 0 ) {
	send_to_char( "Your courage exceeds your wisdom.\n\r", ch );
	return;
    }
    if ( IS_PKILL( ch ) && wimpy > (int) ch->max_hit / 2.25 )
    {
	send_to_char( "Such cowardice ill becomes you.\n\r", ch );
	return;
    }
    else if ( wimpy > (int) ch->max_hit / 1.2 )
    {
	send_to_char( "Such cowardice ill becomes you.\n\r", ch );
	return;
    }
    ch->wimpy	= wimpy;
    ch_printf( ch, "Wimpy set to %d hit points.\n\r", wimpy );
    return;
}



void do_password( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    char log_buf[MAX_STRING_LENGTH];
    char *pArg;
    char *pwdnew;
    char *p;
    char cEnd;

    if ( IS_NPC(ch) )
	return;

    /*
     * Can't use one_argument here because it smashes case.
     * So we just steal all its code.  Bleagh.
     */
    pArg = arg1;
    while ( isspace(*argument) )
	argument++;

    cEnd = ' ';
    if ( *argument == '\'' || *argument == '"' )
	cEnd = *argument++;

    while ( *argument != '\0' )
    {
	if ( *argument == cEnd )
	{
	    argument++;
	    break;
	}
	*pArg++ = *argument++;
    }
    *pArg = '\0';

    pArg = arg2;
    while ( isspace(*argument) )
	argument++;

    cEnd = ' ';
    if ( *argument == '\'' || *argument == '"' )
	cEnd = *argument++;

    while ( *argument != '\0' )
    {
	if ( *argument == cEnd )
	{
	    argument++;
	    break;
	}
	*pArg++ = *argument++;
    }
    *pArg = '\0';

    if ( arg1[0] == '\0' || arg2[0] == '\0' )
    {
	send_to_char( "Syntax: password <new> <again>.\n\r", ch );
	return;
    }

/*
    if ( strcmp( crypt( arg1, ch->pcdata->pwd ), ch->pcdata->pwd ) )
    {
	WAIT_STATE( ch, 40 );
	send_to_char( "Wrong password.  Wait 10 seconds.\n\r", ch );
	return;
    }
*/

/* This should stop all the mistyped password problems --Shaddai */
    if ( strcmp( arg1, arg2 ))
    {
	send_to_char("Passwords don't match try again.\n\r", ch );
	return;
    }
    if ( strlen(arg2) < 5 )
    {
	send_to_char(
	    "New password must be at least five characters long.\n\r", ch );
	return;
    }

    /*
     * No tilde allowed because of player file format.
     */
    pwdnew = crypt( arg2, ch->name );
    for ( p = pwdnew; *p != '\0'; p++ )
    {
	if ( *p == '~' )
	{
	    send_to_char(
		"New password not acceptable, try again.\n\r", ch );
	    return;
	}
    }

    DISPOSE( ch->pcdata->pwd );
    ch->pcdata->pwd = str_dup( pwdnew );
    if ( IS_SET(sysdata.save_flags, SV_PASSCHG) )
	save_char_obj( ch );
    if ( ch->desc && ch->desc->host[0]  != '\0' )
       sprintf(log_buf, "%s changing password from site %s\n", ch->name, 
       		ch->desc->host );
    else
       sprintf(log_buf, "%s changing thier password with no descriptor!", ch->name);
    log_string( log_buf );
    send_to_char( "Ok.\n\r", ch );
    return;
}



void do_socials( CHAR_DATA *ch, char *argument )
{
    int iHash;
    int col = 0;
    SOCIALTYPE *social;

    set_pager_color( AT_PLAIN, ch );
    for ( iHash = 0; iHash < 27; iHash++ )
	for ( social = social_index[iHash]; social; social = social->next )
	{
	    pager_printf( ch, "%-12s", social->name );
	    if ( ++col % 6 == 0 )
		send_to_pager( "\n\r", ch );
	}

    if ( col % 6 != 0 )
	send_to_pager( "\n\r", ch );
    return;
}


void do_commands( CHAR_DATA *ch, char *argument )
{
    int col;
    bool found;
    int hash;
    CMDTYPE *command;

    col = 0;
    set_pager_color( AT_PLAIN, ch );
    if ( argument[0] == '\0' )
    {
	for ( hash = 0; hash < 126; hash++ )
	    for ( command = command_hash[hash]; command; command = command->next )
		if ( command->level <  LEVEL_HERO
		&&   command->level <= get_trust( ch )
		&&  (command->name[0] != 'm'
		||   command->name[1] != 'p') )
		{
		    pager_printf( ch, "%-12s", command->name );
		    if ( ++col % 6 == 0 )
			send_to_pager( "\n\r", ch );
		}
	if ( col % 6 != 0 )
	    send_to_pager( "\n\r", ch );
    }
    else
    {
	found = FALSE;
	for ( hash = 0; hash < 126; hash++ )
	    for ( command = command_hash[hash]; command; command = command->next )
		if ( command->level <  LEVEL_HERO
		&&   command->level <= get_trust( ch )
		&&  !str_prefix(argument, command->name)
		&&  (command->name[0] != 'm'
		||   command->name[1] != 'p') )
		{
		    pager_printf( ch, "%-12s", command->name );
		    found = TRUE;
		    if ( ++col % 6 == 0 )
			send_to_pager( "\n\r", ch );
		}

	if ( col % 6 != 0 )
	    send_to_pager( "\n\r", ch );
	if ( !found )
	    ch_printf( ch, "No command found under %s.\n\r", argument);
    }
    return;
}

void do_channels( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    one_argument( argument, arg );

    if ( IS_NPC( ch ) )
	return;

    if ( arg[0] == '\0' )
    {
        if ( !IS_NPC(ch) && xIS_SET(ch->act, PLR_SILENCE) )
        {
	    set_char_color( AT_GREEN, ch );
            send_to_char( "You are silenced.\n\r", ch );
            return;
        }
    
	/* Channels everyone sees regardless of affiliation --Blodkai */
        send_to_char_color( "\n\r &gPublic channels  (severe penalties for abuse)&G:\n\r  ", ch );
	ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_RACETALK )?
						" &G+RACETALK" :
						" &g-racetalk" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_GOSSIP )    ?
				                " &G+GOSSIP" 	          :
						" &g-gossip" );
        if ( get_trust( ch ) > 2 && !NOT_AUTHED( ch ) )
          ch_printf_color( ch, "%s", !IS_SET( ch->deaf, CHANNEL_AUCTION ) ?
				                " &G+AUCTION" 	          :
						" &g-auction" );
	ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_TRAFFIC ) ?
						" &G+TRAFFIC"		  :
						" &g-traffic" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_QUEST )   ?
				                " &G+QUEST" 	          :
						" &g-quest" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_WARTALK ) ?
				                " &G+WARTALK" 	          :
						" &g-wartalk" );
        if ( IS_HERO( ch ) )
          ch_printf_color( ch, "%s", !IS_SET( ch->deaf, CHANNEL_AVTALK )  ?
				                " &G+AVATAR"	          :
						" &g-avatar" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_MUSIC )   ?
				                " &G+MUSIC" 	          :
						" &g-music" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_ASK )     ?
					        " &G+ASK"                 :
						" &g-ask" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_SHOUT )   ?
						" &G+SHOUT"	          :
						" &g-shout" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_YELL )    ?
				                " &G+YELL"	          :
						" &g-yell" );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_OOC )    ?
				                " &G+OOC"	          :
						" &g-ooc" );
  
	/* For organization channels (orders, followings, guilds, councils) */
        send_to_char_color( "\n\r &gPrivate channels (severe penalties for abuse)&G:\n\r ", ch );
        ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_TELLS )   ?
                                                " &G+TELLS"               :
                                                " &g-tells" );
        ch_printf_color( ch, "%s", !IS_SET( ch->deaf, CHANNEL_WHISPER )   ?
						" &G+WHISPER"		  :
						" &g-whisper" );
        if ( !IS_NPC( ch ) && ch->pcdata->clan )
        {
          if ( ch->pcdata->clan->clan_type == CLAN_ORDER )
	    send_to_char_color( !IS_SET( ch->deaf, CHANNEL_ORDER ) ?
		" &G+ORDER"	:	" &g-order", ch );

          else if ( ch->pcdata->clan->clan_type == CLAN_GUILD )
	    send_to_char_color( !IS_SET( ch->deaf, CHANNEL_GUILD ) ?
		" &G+GUILD"	:	" &g-guild", ch );
          else
	    send_to_char_color( !IS_SET( ch->deaf, CHANNEL_FTELL )  ?
		" &G+FTELL"	:	" &g-ftell", ch );
         /*   send_to_char_color( !IS_SET( ch->deaf, CHANNEL_PRAY )       ?
                " &G+PRAY"      :       " &g-pray", ch );  */
        }
        if ( IS_IMMORTAL(ch) || ( ch->pcdata->council
	&&   !str_cmp( ch->pcdata->council->name, "Newbie Council" ) ) )
          ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_NEWBIE) ?
    				 	        " &G+NEWBIE"	     	  :
						" &g-newbie" );
        if ( !IS_NPC( ch ) && ch->pcdata->council )
          ch_printf_color( ch, "%s",   !IS_SET( ch->deaf, CHANNEL_COUNCIL)?
				                " &G+COUNCIL"	     	  :
						" &g-council" );

	/* Immortal channels */
        if ( IS_IMMORTAL( ch ) )
        {
            send_to_char_color( "\n\r &gImmortal Channels&G:\n\r  ", ch );
            send_to_char_color( !IS_SET( ch->deaf, CHANNEL_IMMTALK )    ?
		" &G+IMMTALK"	:	" &g-immtalk", ch );
         /*   send_to_char_color( !IS_SET( ch->deaf, CHANNEL_PRAY )       ?
		" &G+PRAY"	:	" &g-pray", ch ); */ 
            if ( get_trust( ch ) >= sysdata.muse_level )
              send_to_char_color( !IS_SET( ch->deaf, CHANNEL_MUSE )  ?
		" &G+MUSE"	:	" &g-muse", ch );
            send_to_char_color( !IS_SET( ch->deaf, CHANNEL_MONITOR )    ?
		" &G+MONITOR"	:	" &g-monitor", ch );
	    send_to_char_color( !IS_SET( ch->deaf, CHANNEL_AUTH )	?
	       " &G+AUTH"	:	" &g-auth", ch );	
        }
        if ( get_trust( ch ) >= sysdata.log_level )
        {
            send_to_char_color( !IS_SET( ch->deaf, CHANNEL_LOG ) 	?
		" &G+LOG"	:	" &g-log", ch);
            send_to_char_color( !IS_SET( ch->deaf, CHANNEL_BUILD)       ?
		" &G+BUILD"	:	" &g-build", ch );
            send_to_char_color( !IS_SET( ch->deaf, CHANNEL_COMM ) 	?
		" &G+COMM"	:	" &g-comm", ch );
            send_to_char_color( !IS_SET (ch->deaf, CHANNEL_WARN)
                        ? " &G+WARN" : " &g-warn", ch);
            if ( get_trust( ch ) >= sysdata.think_level )
              send_to_char_color( !IS_SET( ch->deaf, CHANNEL_THINK ) 	?
		" &G+THINK"	:	" &g-think", ch );
        }
        send_to_char( "\n\r", ch );   
    }
    else
    {
	bool fClear;
	bool ClearAll;
	int bit;

        bit=0;
        ClearAll = FALSE;

	     if ( arg[0] == '+' ) fClear = TRUE;
	else if ( arg[0] == '-' ) fClear = FALSE;
	else
	{
	    send_to_char( "Channels -channel or +channel?\n\r", ch );
	    return;
	}

	     if ( !str_cmp( arg+1, "auction"  ) ) bit = CHANNEL_AUCTION;
	else if ( !str_cmp( arg+1, "traffic"  ) ) bit = CHANNEL_TRAFFIC;
	else if ( !str_cmp( arg+1, "gossip"   ) ) bit = CHANNEL_GOSSIP;
	else if ( !str_cmp( arg+1, "ftell"    ) ) bit = CHANNEL_FTELL;
	else if ( !str_cmp( arg+1, "council"  ) ) bit = CHANNEL_COUNCIL;
        else if ( !str_cmp( arg+1, "guild"    ) ) bit = CHANNEL_GUILD;  
	else if ( !str_cmp( arg+1, "quest"    ) ) bit = CHANNEL_QUEST;
	else if ( !str_cmp( arg+1, "tells"    ) ) bit = CHANNEL_TELLS;
	else if ( !str_cmp( arg+1, "immtalk"  ) ) bit = CHANNEL_IMMTALK;
	else if ( !str_cmp( arg+1, "log"      ) ) bit = CHANNEL_LOG;
	else if ( !str_cmp( arg+1, "build"    ) ) bit = CHANNEL_BUILD;
	else if ( !str_cmp( arg+1, "traffic"  ) ) bit = CHANNEL_TRAFFIC;
   //	else if ( !str_cmp( arg+1, "pray"     ) ) bit = CHANNEL_PRAY;
	else if ( !str_cmp( arg+1, "avtalk"   ) ) bit = CHANNEL_AVTALK;
	else if ( !str_cmp( arg+1, "monitor"  ) ) bit = CHANNEL_MONITOR;
	else if ( !str_cmp( arg+1, "auth"     ) ) bit = CHANNEL_AUTH;
	else if ( !str_cmp( arg+1, "newbie"   ) ) bit = CHANNEL_NEWBIE;
	else if ( !str_cmp( arg+1, "music"    ) ) bit = CHANNEL_MUSIC;
	else if ( !str_cmp( arg+1, "muse"     ) ) bit = CHANNEL_MUSE;
	else if ( !str_cmp( arg+1, "ask"      ) ) bit = CHANNEL_ASK;
	else if ( !str_cmp( arg+1, "shout"    ) ) bit = CHANNEL_SHOUT;
	else if ( !str_cmp( arg+1, "yell"     ) ) bit = CHANNEL_YELL;
	else if ( !str_cmp( arg+1, "comm"     ) ) bit = CHANNEL_COMM;
        else if ( !str_cmp (arg+1, "warn"     ) ) bit = CHANNEL_WARN;
	else if ( !str_cmp( arg+1, "order"    ) ) bit = CHANNEL_ORDER;
        else if ( !str_cmp( arg+1, "wartalk"  ) ) bit = CHANNEL_WARTALK;
	else if ( !str_cmp( arg+1, "whisper"  ) ) bit = CHANNEL_WHISPER;
	else if ( !str_cmp( arg+1, "racetalk" ) ) bit = CHANNEL_RACETALK;
	else if ( !str_cmp( arg+1, "ooc"	) )	bit = CHANNEL_OOC;
	else if ( !str_cmp( arg+1, "all"      ) ) ClearAll = TRUE;
	else
	{
	    send_to_char( "Set or clear which channel?\n\r", ch );
	    return;
	}

	if (( fClear ) && ( ClearAll ))
	{
	    REMOVE_BIT (ch->deaf, CHANNEL_RACETALK);
            REMOVE_BIT (ch->deaf, CHANNEL_AUCTION);
            REMOVE_BIT (ch->deaf, CHANNEL_GOSSIP);
            REMOVE_BIT (ch->deaf, CHANNEL_QUEST);
            REMOVE_BIT (ch->deaf, CHANNEL_WARTALK);
        //    REMOVE_BIT (ch->deaf, CHANNEL_PRAY);
	    REMOVE_BIT (ch->deaf, CHANNEL_TRAFFIC);
            REMOVE_BIT (ch->deaf, CHANNEL_MUSIC);
            REMOVE_BIT (ch->deaf, CHANNEL_ASK);
            REMOVE_BIT (ch->deaf, CHANNEL_SHOUT);
            REMOVE_BIT (ch->deaf, CHANNEL_YELL);
			REMOVE_BIT (ch->deaf, CHANNEL_OOC);

       /*     if (ch->pcdata->clan)
              REMOVE_BIT (ch->deaf, CHANNEL_FTELL);

	    if (ch->pcdata->council)
	      REMOVE_BIT (ch->deaf, CHANNEL_COUNCIL);

            if (ch->pcdata->guild)
              REMOVE_BIT (ch->deaf, CHANNEL_GUILD);
       */
            if (ch->level >= LEVEL_IMMORTAL)
              REMOVE_BIT (ch->deaf, CHANNEL_AVTALK);
 
	    /*
	    if (ch->level >= sysdata.log_level )
	      REMOVE_BIT (ch->deaf, CHANNEL_COMM);
	    */

        } else if ((!fClear) && (ClearAll))
        {
	    SET_BIT (ch->deaf, CHANNEL_RACETALK);
            SET_BIT (ch->deaf, CHANNEL_AUCTION);
	    SET_BIT (ch->deaf, CHANNEL_TRAFFIC);
            SET_BIT (ch->deaf, CHANNEL_GOSSIP);
            SET_BIT (ch->deaf, CHANNEL_QUEST);
     //       SET_BIT (ch->deaf, CHANNEL_PRAY);
            SET_BIT (ch->deaf, CHANNEL_MUSIC);
            SET_BIT (ch->deaf, CHANNEL_ASK);
            SET_BIT (ch->deaf, CHANNEL_SHOUT);
	    SET_BIT (ch->deaf, CHANNEL_WARTALK);
            SET_BIT (ch->deaf, CHANNEL_YELL);
			SET_BIT (ch->deaf, CHANNEL_OOC);
          
       /*     if (ch->pcdata->clan)
              SET_BIT (ch->deaf, CHANNEL_FTELL);

	    if (ch->pcdata->council)
	      SET_BIT (ch->deaf, CHANNEL_COUNCIL);

            if ( IS_GUILDED(ch) )
              SET_BIT (ch->deaf, CHANNEL_GUILD);
       */
            if (ch->level >= LEVEL_IMMORTAL)
              SET_BIT (ch->deaf, CHANNEL_AVTALK);

	    /*
	    if (ch->level >= sysdata.log_level)
	      SET_BIT (ch->deaf, CHANNEL_COMM);
	    */

         } else if (fClear)
         {
	    REMOVE_BIT (ch->deaf, bit);
         } else
         {
	    SET_BIT    (ch->deaf, bit);
         }

	  send_to_char( "Ok.\n\r", ch );
    }

    return;
}


/*
 * display WIZLIST file						-Thoric
 */
void do_wizlist( CHAR_DATA *ch, char *argument )
{
    set_pager_color( AT_IMMORT, ch );
    show_file( ch, WIZLIST_FILE );
}

/*
 * Contributed by Grodyn.
 * Display completely overhauled, 2/97 -- Blodkai
 */
void do_config( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
 
    if ( IS_NPC(ch) )
        return;
 
    one_argument( argument, arg );
 
    set_char_color( AT_GREEN, ch );
 
    if ( arg[0] == '\0' )
    {
      set_char_color( AT_DGREEN, ch );
      send_to_char( "\n\rConfigurations ", ch );
      set_char_color( AT_GREEN, ch );
      send_to_char( "(use 'config +/- <keyword>' to toggle, see 'help config')\n\r\n\r", ch );
      set_char_color( AT_DGREEN, ch );
      send_to_char( "Display:   ", ch );
      set_char_color( AT_GREY, ch );
      ch_printf( ch, "%-12s   %-12s   %-12s   %-12s\n\r           %-12s   %-12s   %-12s   %-12s\n\r           %-12s   %-12s   %-12s   %-12s\n\r           %-12s",
        IS_SET( ch->pcdata->flags, PCFLAG_PAGERON ) 	? "[+] PAGER"
                                                    	: "[-] pager",
        IS_SET( ch->pcdata->flags, PCFLAG_GAG )     	? "[+] GAG"
                                                    	: "[-] gag",
        xIS_SET(ch->act, PLR_BRIEF )                	? "[+] BRIEF"
                                                    	: "[-] brief",
        xIS_SET(ch->act, PLR_COMBINE )              	? "[+] COMBINE"
                                                    	: "[-] combine",
        xIS_SET(ch->act, PLR_BLANK )                	? "[+] BLANK"
                                                    	: "[-] blank",
        xIS_SET(ch->act, PLR_PROMPT )               	? "[+] PROMPT"
                                                    	: "[-] prompt",
        xIS_SET(ch->act, PLR_ANSI )                 	? "[+] ANSI"
                                                    	: "[-] ansi",
        xIS_SET(ch->act, PLR_RIP )                  	? "[+] RIP"
                                                    	: "[-] rip",
		xIS_SET(ch->act, PLR_COMPASS )					? "[+] COMPASS"
														: "[-] compass",
		xIS_SET(ch->act, PLR_SEEDAM)					? "[+] SEEDAM"
														: "[-] seedam",
		xIS_SET(ch->act, PLR_ABBAFFS)					? "[+] ABBAFFS"
														: "[-] abbaffs",
		xIS_SET(ch->act, PLR_SHORTWHO)                  ? "[+] SHORTWHO"
														: "[-] shortwho",
		xIS_SET(ch->act, PLR_TELNET_GA)					? "[+] TELNETGA"
														: "[-] telnetga");

      set_char_color( AT_DGREEN, ch );
      send_to_char( "\n\r\n\rAuto:      ", ch );
      set_char_color( AT_GREY, ch );
      ch_printf( ch, "%-12s   %-12s   %-12s   %-12s\n\r           %-12s %-12s %-12s",
        xIS_SET(ch->act, PLR_AUTOSAC  )             	? "[+] AUTOSAC"
                                                    	: "[-] autosac",
        xIS_SET(ch->act, PLR_AUTOGOLD )             	? "[+] AUTOGOLD"
                                                    	: "[-] autogold",
        xIS_SET(ch->act, PLR_AUTOLOOT )             	? "[+] AUTOLOOT"
                                                    	: "[-] autoloot",
        xIS_SET(ch->act, PLR_AUTOEXIT )             	? "[+] AUTOEXIT"
                                                    	: "[-] autoexit",
		xIS_SET(ch->act, PLR_AUTOGLANCE )	  			? "[+] AUTOGLANCE"
														: "[-] autoglance",
		xIS_SET(ch->act, PLR_AUTOUPDATE_PROMPT)			? "[+] AUTOUPDATE"
		                                                : "[-] autoupdate",
		xIS_SET(ch->act, PLR_AUTOASSIST )				? "[+] AUTOASSIST"
														: "[-] autoassist" );
 
 
      set_char_color( AT_DGREEN, ch );
      send_to_char( "\n\r\n\rSettings:  ", ch );
      set_char_color( AT_GREY, ch );
      ch_printf_color( ch, "Pager Length (%d)    Wimpy (&W%d&w)",
							ch->pcdata->pagerlen,
						        ch->wimpy );
 
      if ( IS_IMMORTAL( ch ) )
      {
	set_char_color( AT_DGREEN, ch );
        send_to_char( "\n\r\n\rImmortal toggles:  ", ch );
        set_char_color( AT_GREY, ch );
        ch_printf( ch, "Roomvnum [%s]    Automap [%s]",
	  xIS_SET(ch->act, PLR_ROOMVNUM ) 		? "+"
							: " ",
          xIS_SET(ch->act, PLR_AUTOMAP  ) 		? "+"
							: " " );
      }
 
      set_char_color( AT_DGREEN, ch );
      send_to_char( "\n\r\n\rSentences imposed on you (if any):", ch );
      set_char_color( AT_YELLOW, ch );
      ch_printf( ch, "\n\r%s%s%s%s%s%s",
          xIS_SET(ch->act, PLR_SILENCE )  ?
            " For your abuse of channels, you are currently silenced.\n\r" : "",
          xIS_SET(ch->act, PLR_NO_EMOTE ) ?
            " The gods have removed your emotes.\n\r"                      : "", 
          xIS_SET(ch->act, PLR_NO_TELL )  ?
            " You are not permitted to send 'tells' to others.\n\r"        : "", 
          xIS_SET(ch->act, PLR_BULLY )?
            " A lowdown bully.  Pick on someone your own size!\n\r"       : "", 
          xIS_SET(ch->act, PLR_THIEF )    ?
            " A proven thief, you will be hunted by the authorities.\n\r"  : "", 
          xIS_SET(ch->act, PLR_KILLER )   ?
            " For the crime of murder you are sentenced to death...\n\r"   : "" );
    }
    else
    {
	bool fSet;
	int bit = 0;

	     if ( arg[0] == '+' ) fSet = TRUE;
	else if ( arg[0] == '-' ) fSet = FALSE;
	else
	{
	    send_to_char( "Config -option or +option?\n\r", ch );
	    return;
	}

	     if ( !str_prefix( arg+1, "autoexit" ) ) bit = PLR_AUTOEXIT;
	else if ( !str_prefix( arg+1, "abbaffs" ) )	 bit = PLR_ABBAFFS;
	else if ( !str_prefix( arg+1, "autoassist" ) ) bit = PLR_AUTOASSIST;
	else if ( !str_prefix( arg+1, "autoloot" ) ) bit = PLR_AUTOLOOT;
	else if ( !str_prefix( arg+1, "autosac"  ) ) bit = PLR_AUTOSAC;
	else if ( !str_prefix( arg+1, "autogold" ) ) bit = PLR_AUTOGOLD;
	else if ( !str_prefix( arg+1, "autoglance" ) ) bit = PLR_AUTOGLANCE;
	else if ( !str_prefix( arg+1, "autoupdate" ) ) bit = PLR_AUTOUPDATE_PROMPT;
	else if ( !str_prefix( arg+1, "blank"    ) ) bit = PLR_BLANK;
	else if ( !str_prefix( arg+1, "brief"    ) ) bit = PLR_BRIEF;
	else if ( !str_prefix( arg+1, "combine"  ) ) bit = PLR_COMBINE;
	else if ( !str_prefix( arg+1, "prompt"   ) ) bit = PLR_PROMPT;
	else if ( !str_prefix( arg+1, "telnetga" ) ) bit = PLR_TELNET_GA;
	else if ( !str_prefix( arg+1, "ansi"     ) ) bit = PLR_ANSI;
	else if ( !str_prefix( arg+1, "rip"      ) ) bit = PLR_RIP;
	else if ( !str_prefix( arg+1, "compass"  ) ) bit = PLR_COMPASS;
	else if ( !str_prefix( arg+1, "seedam"   ) ) bit = PLR_SEEDAM;
	else if ( !str_prefix( arg+1, "shortwho" ) ) bit = PLR_SHORTWHO;
/*	else if ( !str_prefix( arg+1, "flee"     ) ) bit = PLR_FLEE; */
/*	else if ( !str_prefix( arg+1, "nice"     ) ) bit = PLR_NICE; */
/*	else if ( !str_prefix( arg+1, "drag"     ) ) bit = PLR_SHOVEDRAG; */
	else if ( IS_IMMORTAL( ch )
	     &&   !str_prefix( arg+1, "vnum"     ) ) bit = PLR_ROOMVNUM;
	else if ( IS_IMMORTAL( ch )
	     &&   !str_prefix( arg+1, "map"      ) ) bit = PLR_AUTOMAP;     /* maps */

	if (bit)
        {
  	  if ( (bit == PLR_FLEE || bit == PLR_NICE || bit == PLR_SHOVEDRAG) 
	  &&  IS_SET( ch->pcdata->flags, PCFLAG_DEADLY ) )
          {
	    send_to_char( "Pkill characters can not config that option.\n\r", ch );
	    return;
          }
          
	  if ( fSet )
	    xSET_BIT   (ch->act, bit);
	  else
	    xREMOVE_BIT(ch->act, bit);
	  send_to_char( "Ok.\n\r", ch );
          return;
        }
        else
        {
	       if ( !str_prefix( arg+1, "norecall" ) ) bit = PCFLAG_NORECALL;
	  else if ( !str_prefix( arg+1, "nointro"  ) ) bit = PCFLAG_NOINTRO;
          else if ( !str_prefix( arg+1, "gag"      ) ) bit = PCFLAG_GAG; 
          else if ( !str_prefix( arg+1, "pager"    ) ) bit = PCFLAG_PAGERON;
          else if ( !str_prefix( arg+1, "groupwho" ) ) bit = PCFLAG_GROUPWHO;
	  else if ( !str_prefix( arg+1, "@hgflag_" ) ) bit = PCFLAG_HIGHGAG;
          else
	  {
	    send_to_char( "Config which option?\n\r", ch );
	    return;
    	  }

          if ( fSet )
	    SET_BIT    (ch->pcdata->flags, bit);
	  else
	    REMOVE_BIT (ch->pcdata->flags, bit);

	  send_to_char( "Ok.\n\r", ch );
          return;
        }
    }

    return;
}


void do_credits( CHAR_DATA *ch, char *argument )
{
  do_luahelp( ch, "credits" );
}


extern int top_area;
/*
 * New do_areas, written by Fireblade, last modified - 4/27/97
 *
 *   Syntax: area            ->      lists areas in alphanumeric order
 *           area <a>        ->      lists areas with soft max less than
 *                                                    parameter a
 *           area <a> <b>    ->      lists areas with soft max bewteen
 *                                                    numbers a and b
 *           area old        ->      list areas in order loaded
 *
 */
void do_areas( CHAR_DATA *ch, char *argument )
{ 
    char *header_string1 = "\n\r   &PAuthor    &W|             &GArea"
                                    "                     &W| "
                                    "&YRecommended &W|\n\r";
    char *header_string2 = "&W-------------+-----------------"
                                    "&W---------------------+----"
                                    "&W---------|&W\n\r";
    char *print_string = "&P%-12s &W| &G%-36s &W| &Y%4d &W- &Y%-4d &W\n\r";
 
    AREA_DATA *pArea;
    int lower_bound = 0;
    int upper_bound = MAX_LEVEL + 1;
    /* make sure is to init. > max area level */
    char arg[MAX_STRING_LENGTH];
   
    argument = one_argument(argument,arg);
        
    if(arg[0] != '\0')
    {
      if(!is_number(arg))
      {
        if(!strcmp(arg,"old"))
        {
          set_pager_color( AT_PLAIN, ch );
          send_to_pager_color(header_string1, ch);
          send_to_pager_color(header_string2, ch);
          for (pArea = first_area; pArea;pArea = pArea->next)
          {   
            pager_printf(ch, print_string,
              pArea->author, pArea->name,
              pArea->low_soft_range,
              pArea->hi_soft_range,
              pArea->low_hard_range,
              pArea->hi_hard_range);
          }  
          return;
        }
        else
        {
          send_to_char("Area may only be followed by numbers, or 'old'.\n\r", ch);
          return;
        }
      }
                                 
      upper_bound = atoi(arg);
      lower_bound = upper_bound;
                                                
      argument = one_argument(argument,arg);
                                                
      if(arg[0] != '\0')
      {
        if(!is_number(arg))
        {
          send_to_char("Area may only be followed by numbers.\n\r", ch);
          return;
        }
                                
        upper_bound = atoi(arg);
                 
        argument = one_argument(argument,arg);
        if(arg[0] != '\0')
        {
          send_to_char("Only two level numbers allowed.\n\r",ch);
          return;
        }
      }
    }
                         
    if(lower_bound > upper_bound)
    {
        call_va(L_mud, "swap", "ii>ii", lower_bound, upper_bound, &lower_bound, &upper_bound);
      //~ int swap = lower_bound;
      //~ lower_bound = upper_bound;
      //~ upper_bound = swap;
    }
 
    set_pager_color( AT_PLAIN, ch );
    send_to_pager_color(header_string1, ch);
    send_to_pager_color(header_string2, ch);
                                
    for (pArea = first_area_name; pArea; pArea = pArea->next_sort_name)
    {
      if (pArea->hi_soft_range >= lower_bound
      &&  pArea->low_soft_range <= upper_bound)
      {
        pager_printf(ch, print_string,
          pArea->author, pArea->name,
          pArea->low_soft_range,
          pArea->hi_soft_range,
          pArea->low_hard_range,
          pArea->hi_hard_range);
      }
    }
    return;
}

void do_afk( CHAR_DATA *ch, char *argument )
{
     if ( IS_NPC(ch) )
     return;
     
     if xIS_SET(ch->act, PLR_AFK)
     {
    	xREMOVE_BIT(ch->act, PLR_AFK);
	send_to_char( "You are no longer afk.\n\r", ch );
/*	act(AT_GREY,"$n is no longer afk.", ch, NULL, NULL, TO_ROOM);*/
	act(AT_GREY,"$n is no longer afk.", ch, NULL, NULL, TO_CANSEE);
     }
     else
     {
	xSET_BIT(ch->act, PLR_AFK);
	send_to_char( "You are now afk.\n\r", ch );
/*	act(AT_GREY,"$n is now afk.", ch, NULL, NULL, TO_ROOM);*/
	act(AT_GREY,"$n is now afk.", ch, NULL, NULL, TO_CANSEE);
	return;
     }
         
}

/***************************************************************************
*     Shows mana and blood (if vampire) requirements to cast a spell.      *
*          Created by Desden, el Chaman Tibetano - Jun 1999                *
* Snippets page: http://luisso.net/smaug_snippets.htm *
*                Email: jose@luisso.net                          *
***************************************************************************/
void do_mana( CHAR_DATA *ch, char *argument)
{
   SKILLTYPE *skill=NULL;
   char arg1[MAX_INPUT_LENGTH];
   int sn;
   int col = 0;

   argument=one_argument(argument, arg1);

   if (IS_NPC(ch))
   {
      send_to_char("Mobs cannot use this command.\n\r", ch);
      return;
   }

   if (arg1[0]=='\0')
   {
         send_to_char("Syntax: mana all\n\r        mana <spell>\n\r",ch);
      return;
    }

    if(!strcmp(arg1,"all"))
    {
       set_pager_color(AT_YELLOW,ch); 
 
          send_to_pager("                         MANA REQUIRED TO CAST\n\r", ch);

       send_to_pager("                        -----------------------\n\r", ch);
  
       for ( sn = 0; sn < top_sn ; sn++ )   
       {
 	  skill=get_skilltype(sn);  
          if(ch->pcdata->learned[sn] < 1 || !skill->name || !skill->min_mana )
              continue;

          if( (ch->level >= skill->skill_level[ch->class]) || (ch->level >= skill->skill_level[ch->dualclass]) )
          {
             {
                if(ch->mana >= MANA)
        	   pager_printf_color(ch, "&Y%-16.16s:%4d   ", skill->name, MANA );
                else
	           pager_printf_color(ch, "&R%-16.16s:%4d   ", skill->name, MANA );
             }	    
             if(++col % 3 == 0)
            
             pager_printf(ch,"\n\r");         
          }
       }
       pager_printf(ch,"\n\r");
    }

    else   

    {
       if((sn =skill_lookup( arg1)) > 0)
       { 
          skill=get_skilltype(sn);
     
          if(!skill->min_mana)
          {
             ch_printf(ch, "%s, '%s' doesn't use mana points.\n\r", ch->name, skill->name );
             return;
          }
     
          if(ch->pcdata->learned[sn] < 1)
          {
             if (  ch->level < skill->skill_level[ch->class] || ch->level < skill->skill_level[ch->dualclass] )
             {
                send_to_char( "You have not enough level to cast it.\n\r", ch );
                return;
             }
             else
             {
                send_to_char("You must practice a spell before using it.\n\r",ch);
                return;
             }   
          }

          pager_printf(ch,"You need %d mana points to cast '%s' with success.\n\r", MANA, skill->name);
       }
       else
       ch_printf(ch, "That is not a spell or a skill.\n\r");
    }
    return;
}


void do_slist( CHAR_DATA *ch, char *argument )
{
   int sn, i, lFound;
   char skn[MAX_INPUT_LENGTH];
   char buf[MAX_INPUT_LENGTH];
   char arg1[MAX_INPUT_LENGTH];
   char arg2[MAX_INPUT_LENGTH]; 
   int lowlev, hilev;
   sh_int lasttype = SKILL_SPELL;

   if ( IS_NPC(ch) )
     return;

   argument = one_argument( argument, arg1 );
   argument = one_argument( argument, arg2 );

   lowlev=1;
   hilev=50;

   if (arg1[0]!='\0')
      lowlev=atoi(arg1);

   if ((lowlev<1) || (lowlev>LEVEL_IMMORTAL))
      lowlev=1;

   if (arg2[0]!='\0')
      hilev=atoi(arg2);

   if ((hilev<0) || (hilev>=LEVEL_IMMORTAL))
      hilev=LEVEL_HERO;

   if(lowlev>hilev)
      lowlev=hilev;

   set_pager_color( AT_MAGIC, ch );
   send_to_pager("SPELL & SKILL LIST\n\r",ch);
   send_to_pager("------------------\n\r",ch);

   for (i=lowlev; i <= hilev; i++)
   {
	lFound= 0;
	sprintf(skn,"Spell");   
	for ( sn = 0; sn < top_sn; sn++ )
	{
	    if ( !skill_table[sn]->name )
		break;

	    if ( skill_table[sn]->type != lasttype )
	    {
		lasttype = skill_table[sn]->type;
		strcpy( skn, skill_tname[lasttype] );
	    }

	    if ( ch->pcdata->learned[sn] <= 0
	    &&   SPELL_FLAG(skill_table[sn], SF_SECRETSKILL) )
		continue;
	
	    if( i == find_skill_level(ch, sn) )
	    {
		if( !lFound )
		{
		    lFound=1;
		    pager_printf( ch, "Level %d\n\r", i );
		}
                switch (skill_table[sn]->minimum_position)
                {
                    case POS_DEAD:
                            sprintf(buf, "any");
                            break;
                    case POS_MORTAL:
                            sprintf(buf, "mortally wounded");
                            break;
                    case POS_INCAP:
                            sprintf(buf, "incapacitated");
                            break;
                    case POS_STUNNED:
                            sprintf(buf, "stunned");
                            break;
                    case POS_SLEEPING:
                            sprintf(buf, "sleeping");
                            break;
                    case POS_RESTING:
                            sprintf(buf, "resting");
                            break;
                    case POS_STANDING:
                            sprintf(buf, "standing");
                            break;
                    case POS_FIGHTING:
                            sprintf(buf, "fighting");
                            break;
                    case POS_EVASIVE:
                            sprintf(buf, "fighting (evasive)");   /* Fighting style support -haus */
                            break;
                    case POS_DEFENSIVE:
                            sprintf(buf, "fighting (defensive)");
                            break;
                    case POS_AGGRESSIVE:
                            sprintf(buf, "fighting (aggressive)");
                            break;
                    case POS_BERSERK:
                            sprintf(buf, "fighting (berserk)");
                            break;
                    case POS_MOUNTED:
                            sprintf(buf, "mounted");
                            break;
                    case POS_SITTING:
                            sprintf(buf, "sitting");
                            break;
                }
              
                int maxadept;
		maxadept = 0;
		if ( (skill_table[sn]->skill_adept[ch->class]) >= (skill_table[sn]->skill_adept[ch->dualclass]) )
		    maxadept = skill_table[sn]->skill_adept[ch->class];
		else
		    maxadept = skill_table[sn]->skill_adept[ch->dualclass];

		pager_printf(ch, "%7s: %20.20s \t Current: %-3d Max: %-3d  MinPos: %s \n\r",
                        skn, skill_table[sn]->name, 
                        ch->pcdata->learned[sn],
                        maxadept,
			buf );
	    }
	}
   }
   return;
}

void do_whois( CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *victim;
  char buf[MAX_STRING_LENGTH];
  char buf2[MAX_STRING_LENGTH];

  buf[0] = '\0';

  if(IS_NPC(ch))
    return;

  if(argument[0] == '\0')
  {
    send_to_pager("You must input the name of an online character.\n\r", ch);
    return;
  }

  strcat(buf, "0.");
  strcat(buf, argument);
  if( ( ( victim = get_char_world(ch, buf) ) == NULL ))
  {
    send_to_pager("No such character online.\n\r", ch);
    return;
  }

  if(IS_NPC(victim))
  {
    send_to_pager("That's not a player!\n\r", ch);
    return;
  }

  set_pager_color( AT_GREY, ch );
  if( victim->class == victim->dualclass )
  {
     pager_printf(ch, "\n\r'%s%s.'\n\r %s is a %s level %d %s %s, %d years of age.\n\r",
    	   victim->name,
	   victim->pcdata->title,
           victim->sex == SEX_MALE ? "He" :
           victim->sex == SEX_FEMALE ? "She" : "It",
	   victim->sex == SEX_MALE ? "male" : 
	   victim->sex == SEX_FEMALE ? "female" : "neutral",
	   victim->level, 
	   capitalize(race_table[victim->race]->race_name),
	   class_table[victim->class]->who_name,
	   get_age(victim) );
  }
  else
  {
       pager_printf(ch, "\n\r'%s%s.'\n\r %s is a %s level %d %s %s-%s, %d years of age.\n\r",
        victim->name, 
        victim->pcdata->title,
        victim->sex == SEX_MALE ? "He" :
        victim->sex == SEX_FEMALE ? "She" : "It",
        victim->sex == SEX_MALE ? "male" :
        victim->sex == SEX_FEMALE ? "female" : "neutral",
        victim->level,
        capitalize(race_table[victim->race]->race_name),
        class_table[victim->class]->who_name,
	class_table[victim->dualclass]->who_name,
        get_age(victim) );
  } 	

  pager_printf(ch, " %s is a %sdeadly player",
	victim->sex == SEX_MALE ? "He" :
	victim->sex == SEX_FEMALE ? "She" : "It",
	IS_SET(victim->pcdata->flags, PCFLAG_DEADLY) ? "" : "non-");

  if ( victim->pcdata->clan )
  {
	if ( victim->pcdata->clan->clan_type == CLAN_ORDER )
	   send_to_pager( ", and belongs to the Order ", ch );
	else
	if ( victim->pcdata->clan->clan_type == CLAN_GUILD )
	   send_to_pager( ", and belongs to the ", ch );
	else
	   send_to_pager( ", and belongs to ", ch );
	send_to_pager( victim->pcdata->clan->name, ch );
  }
  send_to_pager( ".\n\r", ch );

  if(victim->pcdata->council)
    pager_printf(ch, " %s holds a seat on:  %s\n\r",
        victim->sex == SEX_MALE ? "He" :
        victim->sex == SEX_FEMALE ? "She" : "It",
	victim->pcdata->council->name );
    
  if(victim->pcdata->deity)
    pager_printf(ch, " %s has found succor in the deity %s.\n\r",
        victim->sex == SEX_MALE ? "He" :
        victim->sex == SEX_FEMALE ? "She" : "It",
	victim->pcdata->deity->name);

  if(victim->pcdata->spouse)
    pager_printf(ch, " %s is married to %s.\n\r",
	victim->sex == SEX_MALE ? "He" :
	victim->sex == SEX_FEMALE ? "She" : "It",
	victim->pcdata->spouse);

  pager_printf_color(ch, " %s has completed %d MobMaster Quests.\n\r",
        victim->sex == SEX_MALE ? "He" :
        victim->sex == SEX_FEMALE ? "She" : "It",
        victim->mobmastercomplete); 

  //~ if(victim->pcdata->homepage && victim->pcdata->homepage[0] != '\0')
    //~ pager_printf(ch, " %s homepage can be found at %s\n\r", 
        //~ victim->sex == SEX_MALE ? "His" :
        //~ victim->sex == SEX_FEMALE ? "Her" : "Its",
	//~ show_tilde( victim->pcdata->homepage ) );

  if(victim->pcdata->bio && victim->pcdata->bio[0] != '\0')
    pager_printf(ch, " %s's personal bio:\n\r%s",
	victim->name,
	victim->pcdata->bio);
  else
    pager_printf(ch, " %s has yet to create a bio.\n\r",
	victim->name );

  if(IS_IMMORTAL(ch))
  {  
    send_to_pager("-------------------\n\r", ch);
    send_to_pager("Info for immortals:\n\r", ch);

    if ( victim->pcdata->authed_by && victim->pcdata->authed_by[0] != '\0' )
	pager_printf(ch, "%s was authorized by %s.\n\r",
		victim->name, victim->pcdata->authed_by );
    pager_printf(ch, "%s has killed %d mobiles, and been killed by a mobile %d times.\n\r",
		victim->name, victim->pcdata->mkills, victim->pcdata->mdeaths );
    if ( victim->pcdata->pkills || victim->pcdata->pdeaths )
	pager_printf(ch, "%s has killed %d players, and been killed by a player %d times.\n\r",
		victim->name, victim->pcdata->pkills, victim->pcdata->pdeaths );
    if ( victim->pcdata->illegal_pk )
	pager_printf(ch, "%s has committed %d illegal player kills.\n\r",
		victim->name, victim->pcdata->illegal_pk );

    pager_printf(ch, "%s is %shelled at the moment.\n\r",
	victim->name, 
	(victim->pcdata->release_date == 0) ? "not " : "");

    if (victim->pcdata->nuisance )
    {
      pager_printf_color( ch, "&RNuisance   &cStage: (&R%d&c/%d)  Power:  &w%d  &cTime:  &w%s.\n\r", victim->pcdata->nuisance->flags,
                  MAX_NUISANCE_STAGE, victim->pcdata->nuisance->power,
		              ctime(&victim->pcdata->nuisance->time));
    }
    if(victim->pcdata->release_date != 0)
      pager_printf(ch, "%s was helled by %s, and will be released on %24.24s.\n\r",
	victim->sex == SEX_MALE ? "He" :
	victim->sex == SEX_FEMALE ? "She" : "It",
        victim->pcdata->helled_by,
	ctime(&victim->pcdata->release_date));

    if(get_trust(victim) < get_trust(ch))
    {
      sprintf(buf2, "list %s", buf);
      do_comment(ch, buf2);
    }

    if(xIS_SET(victim->act, PLR_SILENCE) || xIS_SET(victim->act, PLR_NO_EMOTE) 
    || xIS_SET(victim->act, PLR_NO_TELL) || xIS_SET(victim->act, PLR_THIEF) 
    || xIS_SET(victim->act, PLR_KILLER) )
    {
      sprintf(buf2, "This player has the following flags set:");
      if(xIS_SET(victim->act, PLR_SILENCE)) 
        strcat(buf2, " silence");
      if(xIS_SET(victim->act, PLR_NO_EMOTE)) 
        strcat(buf2, " noemote");
      if(xIS_SET(victim->act, PLR_NO_TELL) )
        strcat(buf2, " notell");
      if(xIS_SET(victim->act, PLR_THIEF) )
        strcat(buf2, " thief");
      if(xIS_SET(victim->act, PLR_KILLER) )
        strcat(buf2, " killer");
      strcat(buf2, ".\n\r");
      send_to_pager(buf2, ch);
    }
  if ( victim->desc && victim->desc->host[0]!='\0' )   /* added by Gorog */
     {
     sprintf (buf2, "%s's IP info: %s ", victim->name, victim->desc->host);
     if (get_trust(ch) >= LEVEL_GOD)
        strcat (buf2, victim->desc->user);
     strcat (buf2, "\n\r");
     send_to_pager(buf2, ch);
     }
  }
}

void do_pager( CHAR_DATA *ch, char *argument )
{
  char arg[MAX_INPUT_LENGTH];
  
  if ( IS_NPC(ch) )
    return;
  set_char_color( AT_NOTE, ch );
  argument = one_argument(argument, arg);
  if ( !*arg )
  {
    if ( IS_SET(ch->pcdata->flags, PCFLAG_PAGERON) )
    {
        send_to_char( "Pager disabled.\n\r", ch );
        do_config(ch, "-pager");
    } else {
        ch_printf( ch, "Pager is now enabled at %d lines.\n\r", ch->pcdata->pagerlen );
        do_config(ch, "+pager");
    }
    return;
  }
  if ( !is_number(arg) )
  {
    send_to_char( "Set page pausing to how many lines?\n\r", ch );
    return;
  }
  ch->pcdata->pagerlen = atoi(arg);
  if ( ch->pcdata->pagerlen < 5 )
    ch->pcdata->pagerlen = 5;
  ch_printf( ch, "Page pausing set to %d lines.\n\r", ch->pcdata->pagerlen );
  return;
}

/*
 * The ignore command allows players to ignore up to MAX_IGN
 * other players. Players may ignore other characters whether
 * they are online or not. This is to prevent people from
 * spamming someone and then logging off quickly to evade
 * being ignored.
 * Syntax:
 *	ignore		-	lists players currently ignored
 *	ignore none	-	sets it so no players are ignored
 *	ignore <player>	-	start ignoring player if not already
 *				ignored otherwise stop ignoring player
 *	ignore reply	-	start ignoring last player to send a
 *				tell to ch, to deal with invis spammers
 * Last Modified: June 26, 1997
 * - Fireblade
 */
void do_ignore(CHAR_DATA *ch, char *argument)
{
	char arg[MAX_INPUT_LENGTH];
	IGNORE_DATA *temp, *next;
	char fname[1024];
	struct stat fst;
	CHAR_DATA *victim;
	
	if(IS_NPC(ch))
		return;
	
	argument = one_argument(argument, arg);
	
	sprintf(fname, "%s%c/%s", PLAYER_DIR,
		tolower(arg[0]), capitalize(arg));
	
	victim = NULL;
	
	/* If no arguements, then list players currently ignored */
	if(arg[0] == '\0')
	{
		set_char_color(AT_DIVIDER, ch);
		ch_printf(ch, "\n\r----------------------------------------\n\r");
		set_char_color(AT_DGREEN, ch);
		ch_printf(ch, "You are currently ignoring:\n\r");
		set_char_color(AT_DIVIDER, ch);
		ch_printf(ch, "----------------------------------------\n\r");
		set_char_color(AT_IGNORE, ch);
		
		if(!ch->pcdata->first_ignored)
		{
			ch_printf(ch, "\t    no one\n\r");
			return;
		}
		
		for(temp = ch->pcdata->first_ignored; temp;
				temp = temp->next)
		{
			ch_printf(ch,"\t  - %s\n\r",temp->name);
		}
		
		return;
	}
	/* Clear players ignored if given arg "none" */
	else if(!strcmp(arg, "none"))
	{
		for(temp = ch->pcdata->first_ignored; temp; temp = next)
		{
			next = temp->next;
			UNLINK(temp, ch->pcdata->first_ignored,
					ch->pcdata->last_ignored,
					next, prev);
			STRFREE(temp->name);
			DISPOSE(temp);
		}
		
		set_char_color(AT_IGNORE, ch);
		ch_printf(ch, "You now ignore no one.\n\r");
		
		return;
	}
	/* Prevent someone from ignoring themself... */
	else if(!strcmp(arg, "self") || nifty_is_name(arg, ch->name))
	{
		set_char_color(AT_IGNORE, ch);
		ch_printf(ch, "Did you type something?\n\r");
		return;
	}
	else
	{
		int i;
		
		/* get the name of the char who last sent tell to ch */		
		if(!strcmp(arg, "reply"))
		{
			if(!ch->reply)
			{
				set_char_color(AT_IGNORE, ch);
				ch_printf(ch, "They're not here.\n\r");
				return;
			}
			else
			{
				strcpy(arg, ch->reply->name);
			}
		}
		
		/* Loop through the linked list of ignored players */
		/* 	keep track of how many are being ignored     */
		for(temp = ch->pcdata->first_ignored, i = 0; temp;
				temp = temp->next, i++)
		{
			/* If the argument matches a name in list remove it */
			if(!strcmp(temp->name, capitalize(arg)))
			{
				UNLINK(temp, ch->pcdata->first_ignored,
					ch->pcdata->last_ignored,
					next, prev);
				set_char_color(AT_IGNORE, ch);
				ch_printf(ch,"You no longer ignore %s.\n\r",
					temp->name);
				STRFREE(temp->name);
				DISPOSE(temp);
				return;
			}
		}
		
		/* if there wasn't a match check to see if the name   */
		/* is valid. This if-statement may seem like overkill */
		/* but it is intended to prevent people from doing the*/
		/* spam and log thing while still allowing ya to      */
		/* ignore new chars without pfiles yet...             */
		if( stat(fname, &fst) == -1 &&
			(!(victim = get_char_world(ch, arg)) ||
			IS_NPC(victim) ||
			strcmp(capitalize(arg),victim->name) != 0))
		{
			set_char_color(AT_IGNORE, ch);
			ch_printf(ch,"No player exists by that"
				" name.\n\r");
			return;
		}
		
		if(victim)
		{
			strcpy(capitalize(arg),victim->name);
		}
		
		/* If its valid and the list size limit has not been */
		/* reached create a node and at it to the list	     */
		if(i < MAX_IGN)
		{
			IGNORE_DATA *new;
			CREATE(new, IGNORE_DATA, 1);
			new->name = STRALLOC(capitalize(arg));
			new->next = NULL;
			new->prev = NULL;
			LINK(new, ch->pcdata->first_ignored,
				ch->pcdata->last_ignored, next, prev);
			set_char_color(AT_IGNORE, ch);
			ch_printf(ch,"You now ignore %s.\n\r", new->name);
			return;
		}
		else
		{
			set_char_color(AT_IGNORE, ch);
			ch_printf(ch,"You may only ignore %d players.\n\r",
				MAX_IGN);
			return;
		}
	}
}

/*
 * This function simply checks to see if ch is ignoring ign_ch.
 * Last Modified: October 10, 1997
 * - Fireblade
 */
bool is_ignoring(CHAR_DATA *ch, CHAR_DATA *ign_ch)
{
	IGNORE_DATA *temp;
	
	if(IS_NPC(ch) || IS_NPC(ign_ch))
		return FALSE;
	
	for(temp = ch->pcdata->first_ignored; temp; temp = temp->next)
	{
		if(nifty_is_name(temp->name, ign_ch->name))
			return TRUE;
	}
	
	return FALSE;
}

/* Version info -- Scryn */

void do_version(CHAR_DATA* ch, char* argument)
{
	if(IS_NPC(ch))
	  return;

	set_char_color(AT_YELLOW, ch);
	ch_printf(ch, "SMAUG %s.%s\n\r", SMAUG_VERSION_MAJOR, SMAUG_VERSION_MINOR);
	ch_printf(ch, "HoG %s.%s.%s\n\r", HOG_VERSION_MAJOR, HOG_VERSION_MINOR, HOG_VERSION_REVISION);
    ch_printf(ch, "See &CHELP VERSION%s.%s.%s&Y for version information.\n\r", HOG_VERSION_MAJOR, HOG_VERSION_MINOR, HOG_VERSION_REVISION);

	if(IS_IMMORTAL(ch))
	  ch_printf(ch, "\n\rCompiled on %s at %s.\n\r", __DATE__, __TIME__);

	return;
}


void do_nohelps(CHAR_DATA *ch, char *argument)
{
    //~ CMDTYPE *command;
    //~ AREA_DATA *tArea;
    //~ char arg[MAX_STRING_LENGTH];
    //~ int hash, col=0, sn=0;

    //~ argument = one_argument( argument, arg);

    //~ if(!IS_IMMORTAL(ch) || IS_NPC(ch) )
    //~ {
	//~ send_to_char("Huh?\n\r", ch);
	//~ return;
    //~ }

    //~ if ( arg[0] == '\0' || !str_cmp(arg, "all") )
    //~ {
	//~ do_nohelps(ch, "commands");
	//~ send_to_char( "\n\r", ch);
	//~ do_nohelps(ch, "skills");
	//~ send_to_char( "\n\r", ch);
	//~ do_nohelps(ch, "areas");
	//~ send_to_char( "\n\r", ch);
	//~ return;
    //~ }

    //~ if(!str_cmp(arg, "commands") )
    //~ {
	//~ send_to_char_color("&C&YCommands for which there are no help files:\n\r\n\r", ch);

	//~ for ( hash = 0; hash < 126; hash++ )
	//~ {
	    //~ for ( command = command_hash[hash]; command; command = command->next )
	    //~ {
		//~ if(!get_help(ch, command->name) )
		//~ {
		    //~ ch_printf_color(ch, "&W%-15s", command->name);
		    //~ if ( ++col % 5 == 0 )
		    //~ {
			//~ send_to_char( "\n\r", ch);
		    //~ }
		//~ }
	     //~ }
	//~ }

	//~ send_to_char("\n\r", ch);
	//~ return;
    //~ }

    //~ if(!str_cmp(arg, "skills") || !str_cmp(arg, "spells") )
    //~ {
	//~ send_to_char_color("&CSkills/Spells for which there are no help files:\n\r\n\r", ch);

	//~ for ( sn = 0; sn < top_sn && skill_table[sn] && skill_table[sn]->name; sn++ )
	//~ {
	    //~ if(!get_help(ch, skill_table[sn]->name))
	    //~ {
		//~ ch_printf_color(ch, "&W%-20s", skill_table[sn]->name);
		//~ if ( ++col % 4 == 0 )
		//~ {
		    //~ send_to_char("\n\r", ch);
		//~ }
	    //~ }
	//~ }

	//~ send_to_char("\n\r", ch);
	//~ return;
    //~ }

    //~ if(!str_cmp(arg, "areas") )
    //~ {
	//~ send_to_char_color("&GAreas for which there are no help files:\n\r\n\r", ch);
	
	//~ for (tArea = first_area; tArea; tArea = tArea->next)
	//~ {
	    //~ if(!get_help(ch, tArea->name) )
	    //~ {
		//~ ch_printf_color(ch, "&W%-35s", tArea->name);
		//~ if ( ++col % 2 == 0 )
		//~ {
		    //~ send_to_char("\n\r", ch);
		//~ }
	    //~ }
	//~ }

	//~ send_to_char( "\n\r", ch);
	//~ return;
    //~ }

    //~ send_to_char("Syntax:  nohelps <all|areas|commands|skills>\n\r", ch);
    return;
}

void do_luahelp( CHAR_DATA *ch, char *argument )
{
    if(IS_NPC(ch))
        return;
    
    call_lua (ch, "help", argument);
    return;
}
