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
 *			      Regular update module			    *
 ****************************************************************************/

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mud.h"



/*
 * Local functions.
 */
int	hit_gain	args( ( CHAR_DATA *ch ) );
int	mana_gain	args( ( CHAR_DATA *ch ) );
int	move_gain	args( ( CHAR_DATA *ch ) );
void	mobile_update	args( ( void ) );
void	weather_update	args( ( void ) );
void	time_update	args( ( void ) );	/* FB */
void	char_update	args( ( void ) );
void    mobmaster_update args( ( void ) ); //MOBM
void	char_regen	args( ( void ) );
void	obj_update	args( ( void ) );
void	aggr_update	args( ( void ) );
void	room_act_update	args( ( void ) );
void	obj_act_update	args( ( void ) );
void	char_check	args( ( void ) );
void    drunk_randoms	args( ( CHAR_DATA *ch ) );
void    hallucinations	args( ( CHAR_DATA *ch ) );
void	subtract_times	args( ( struct timeval *etime,
				struct timeval *stime ) );
bool	flush_buffer		args( ( DESCRIPTOR_DATA *d, bool fPrompt ) );


/* weather functions - FB */
void	adjust_vectors		args( ( WEATHER_DATA *weather) );
void	get_weather_echo	args( ( WEATHER_DATA *weather) );
void	get_time_echo		args( ( WEATHER_DATA *weather) );

void    quest_update		args( ( void ) );   /* Questmaster */
/*
 * Global Variables
 */

CHAR_DATA *	gch_prev;
OBJ_DATA *	gobj_prev;

CHAR_DATA *	timechar;

char * corpse_descs[] =
   { 
     "The corpse of %s is in the last stages of decay.", 
     "The corpse of %s is crawling with vermin.",
     "The corpse of %s fills the air with a foul stench.",
     "The corpse of %s is buzzing with flies.",
     "The corpse of %s lies here."
   };

extern int      top_exit;

/*
   This is used to determine a character is the appropriate level to learn
   or use a skill. It assumes that you want the character to be able to use
   a skill at the lowest level his classes would permit.
   Ie: class 1 gives spell Y at 10, class 2 at 5. ch will learn the spell at 5.
   This should be used in place of checks like:
    "if (ch->level >= skill_table[sn]->skill_level[ch->class])"
   It will not tell WHAT level the ch can learn it at, only that they can.
 */
bool DUAL_SKILL(CHAR_DATA *ch, int sn)
{

  if (skill_table[sn]->type == SKILL_RACIAL)
  {
    if(ch->level >= skill_table[sn]->race_level[ch->race]
      && skill_table[sn]->race_level[ch->race])
       return TRUE;
  }
  else
  if (IS_DUAL(ch) && !IS_TIER(ch))
  {
    if(ch->level>= skill_table[sn]->skill_level[ch->dualclass]
      && skill_table[sn]->skill_level[ch->dualclass])
       return TRUE;
  }
  else
  if (IS_TIER(ch))
  {
    if(50>= skill_table[sn]->skill_level[ch->dualclass]
      && skill_table[sn]->skill_level[ch->dualclass])
       return TRUE;
  }
  else
  {
    if(ch->level>= skill_table[sn]->skill_level[ch->class]
      && skill_table[sn]->skill_level[ch->class])
       return TRUE;
  }
	return FALSE;
}
/*
  This it used to determine the maximum a character can learn a skill.
  Example : class 1  can learn skill x to  45% and class 2 can learn it
  85%, so the character can learn the skill to 85% because its the highest.
  This should be used wherever you want to find how high a character can
  learn something, in place of the old checks to:  
  skill_table[sn]->skill_adept[ch->class] 
 */
int dual_adept(CHAR_DATA *ch, int sn)
{
  int max = 0;

  if (skill_table[(sn)]->type == SKILL_RACIAL)
   max = skill_table[(sn)]->race_adept[ch->race];
  else
  if (skill_table[(sn)]->skill_level[ch->class] <=  LEVEL_HERO)
   max = skill_table[(sn)]->skill_adept[ch->class];
  if(!IS_DUAL(ch))
    return max;

  if ((skill_table[(sn)]->skill_adept[ch->dualclass] > max )
  &&  (skill_table[(sn)]->skill_level[ch->dualclass] <=  LEVEL_HERO))
    max = skill_table[(sn)]->skill_adept[ch->dualclass];

  return max;
}
/*
   This function finds the level a skill is learned at, returning the lowest
   level they could possibly achieve it. You would essentially use this whenever
   you would normally do a call to 
   skill_table[sn]->skill_level[ch->class]

*/

int find_skill_level(CHAR_DATA *ch, int sn)
{
  int level = skill_table[sn]->skill_level[ch->class];

  if (skill_table[(sn)]->type == SKILL_RACIAL)
   return skill_table[(sn)]->race_level[ch->race];
  else
   if(!IS_DUAL(ch))
    return level;

  if (skill_table[sn]->skill_level[ch->dualclass] < level)
   level = skill_table[sn]->skill_level[ch->dualclass];
  return level;
}

/*
    These three are simple functions that probably would not be used very much, but it
    is important where it used, as it allows you to make sure your dualclass gets the
    broadest range of hitpoints, and uses mana if supposed to.
    advance_level is the one place to definitely put both of these.
    See the readme on where to use these.
*/

int hp_max(CHAR_DATA *ch)
{
    if(IS_NPC(ch))
        return 20;
  if(!IS_DUAL(ch) )
    return class_table[ch->class]->hp_max;
  else
   if (class_table[ch->dualclass]->hp_max < class_table[ch->class]->hp_max)
    return class_table[ch->dualclass]->hp_max;

 return class_table[ch->class]->hp_max;
}

int hp_min(CHAR_DATA *ch)
{
    if(IS_NPC(ch))
        return 20;
  if(!IS_DUAL(ch) )
    return class_table[ch->class]->hp_min;
  else
   if (class_table[ch->dualclass]->hp_min < class_table[ch->class]->hp_min)
    return class_table[ch->dualclass]->hp_min;

 return class_table[ch->class]->hp_min;
}

/* Used in advance_level */
bool use_mana(CHAR_DATA *ch)
{
    if(IS_NPC(ch))
        return FALSE;
if (class_table[ch->class]->fMana)
    return TRUE;
  if (!IS_DUAL(ch))
    return FALSE;
  if (class_table[ch->dualclass]->fMana)
    return TRUE;
  return FALSE;
}


/*
 * Advancement stuff.
 */
void advance_level( CHAR_DATA *ch )
{
    char buf[MAX_STRING_LENGTH];
    char buf2[MAX_STRING_LENGTH];
    int add_hp;
    int add_mana;
    int add_move;
    int add_prac;
    int luck_prac;
    int luck_chk;

    save_char_obj( ch );
  /*  sprintf( buf, "the %s",
	title_table [ch->class] [ch->level] [ch->sex == SEX_FEMALE ? 1 : 0] );
    set_title( ch, buf );  */

    add_hp	= con_app[get_curr_con(ch)].hitp + number_range(hp_min(ch), hp_max(ch) );
    add_mana	= use_mana(ch) ? number_range( (get_curr_int(ch) / 2), ( (get_curr_int(ch) + get_curr_wis(ch)) / 2 ) ) : 0;
    add_move	= number_range( 10, (get_curr_con(ch)+get_curr_dex(ch)) );
    
    if ( IS_DUAL( ch ) )
    {
	add_prac = wis_app[get_curr_wis(ch)].practice + 2;
    }
    else
    { 
        add_prac = wis_app[get_curr_wis(ch)].practice + 1;
    }
    luck_prac   = 3;

    add_hp	= UMAX(  1, add_hp   );
    add_mana	= UMAX(  0, add_mana );
    add_move	= UMAX( 10, add_move );

    /* bonus for deadlies */
     if(IS_PKILL(ch)){
        add_mana = add_mana;
        add_move = add_move;
        add_hp +=2; 
        sprintf(buf,"Drazuk's Pandect steals your sinews.\n\r");
     
    }

    ch->max_hit 	+= add_hp;
    ch->max_mana	+= add_mana;
    ch->max_move	+= add_move;
    ch->practice	+= add_prac;

    if ( !IS_NPC(ch) )
	xREMOVE_BIT( ch->act, PLR_BOUGHT_PET );

    if ( ch->level == LEVEL_AVATAR && !IS_TIER(ch) )
    {
	DESCRIPTOR_DATA *d;

	sprintf( buf, "%s has just achieved Avatarhood!", ch->name );
	for ( d = first_descriptor; d; d = d->next )
	   if ( d->connected == CON_PLAYING && d->character != ch )
	   {
		set_char_color( AT_IMMORT, d->character );
		send_to_char( buf,	d->character );
		send_to_char( "\n\r",	d->character );
	   }
	set_char_color( AT_WHITE, ch );
	do_help( ch, "M_ADVHERO_" );
    }
    if ( ch->level < LEVEL_IMMORTAL )
    {
        sprintf( buf,
	  "Your gain is: %d/%d hp, %d/%d mana, %d/%d mv %d/%d prac.\n\r",
	  add_hp,	ch->max_hit,
 	  add_mana,	ch->max_mana,
	  add_move,	ch->max_move,
	  add_prac,	ch->practice
	  );
      set_char_color( AT_WHITE, ch );
      send_to_char( buf, ch );

      luck_chk = number_range(1, 100);
      if (luck_chk < ch->mod_lck )
      {
          sprintf( buf, "Lucky you!  You get %d extra practice sessions!\n\r", luck_prac );
          send_to_char( buf, ch );
          ch->practice += luck_prac;
      }
	  

      ch->hit = ch->max_hit;
      ch->mana = ch->max_mana;
      ch->move = ch->max_move;
      if(!IS_NPC(ch))
      {
      ch->pcdata->condition[COND_THIRST] = 95;
      ch->pcdata->condition[COND_FULL] = 95;
      }

      update_pos( ch );	
      send_to_char( "Medea restores you and offers her congratulations!\n\r", ch);
      if(!IS_NPC(ch))
      {
      sprintf(buf, "[INFO] %s has advanced to level %d!", ch->name, ch->level);
      echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL);
      }

      if ( !IS_NPC( ch ) )
      {
	sprintf( buf2, "&G%-13s  ->&w%-2d  &G-&w  %-5d&G   Rvnum: %-5d   %s %s",
	  ch->name,
	  ch->level,
	  get_age( ch ),
	  ch->in_room == NULL ? 0 : ch->in_room->vnum,
	  capitalize(race_table[ch->race]->race_name),
	  class_table[ch->class]->who_name );
	append_to_file( PLEVEL_FILE, buf2 );
      }
    }
	if(!IS_NPC(ch)) call_lua_num (ch, "advance_level", ch->level);
    return;
}   

void tadvance_level( CHAR_DATA *ch )
{
    char buf[MAX_STRING_LENGTH];
    char buf2[MAX_STRING_LENGTH];
//    char buf3[MAX_STRING_LENGTH];
    int add_hp;
    int add_mana;
    int add_move;
    int add_prac;

    add_hp	= number_range( 1, 4 );
    add_mana	= number_range( 1, 4 );
    add_move	= number_range( 1, 4 );
    add_prac    = wis_app[get_curr_wis(ch)].practice + 2;

    add_hp	= UMAX(  1, add_hp   );
    add_mana	= UMAX(  0, add_mana );
    add_move	= UMAX(  1, add_move );
    add_prac	= UMAX(  1, add_prac  );


    ch->max_hit 	+= add_hp;
    ch->max_mana	+= add_mana;
    ch->max_move	+= add_move;
    ch->practice	+= add_prac;

    if ( !IS_NPC(ch) )
	xREMOVE_BIT( ch->act, PLR_BOUGHT_PET );


    if ( ch->level == LEVEL_AVATAR && !IS_TIER(ch) )
    {
	DESCRIPTOR_DATA *d;
	sprintf( buf, "### %s has just achieved Avatarhood!", ch->name );
	for ( d = first_descriptor; d; d = d->next )
	   if ( d->connected == CON_PLAYING && d->character != ch )
	   {
		set_char_color( AT_IMMORT, d->character );
		send_to_char( buf,	d->character );
		send_to_char( "\n\r",	d->character );
	   }
	set_char_color( AT_WHITE, ch );
	do_help( ch, "M_ADVHERO_" );
    }

    if ( ch->level < LEVEL_IMMORTAL )
    {
          pager_printf_color( ch, "&WYour gain is: &R%d&w/&r%d&W hp, &C%d&w/&c%d&W mana, &G%d&w/&g%d&W mv &P%d&w/&p%d&W practice sessions.\n\r",
	  add_hp,	ch->max_hit,
 	  add_mana,	ch->max_mana,
	  add_move,	ch->max_move,
	  add_prac,	ch->practice );
		
      if ( !IS_NPC( ch ) )
      {
	sprintf( buf2, "&G%-13s  ->&w%-2d  &G-&w  %-5d&G   Rvnum: %-5d   %s %s",
	  ch->name,
	  ch->level,
	  get_age( ch ),
	  ch->in_room == NULL ? 0 : ch->in_room->vnum,
	  capitalize(race_table[ch->race]->race_name),
	  class_table[ch->class]->who_name );
	append_to_file( PLEVEL_FILE, buf2 );
      }
	sprintf(buf, "[INFO] %s has advanced to level %d %s!", ch->name, ch->level, class_table[ch->class]->who_name );
	echo_to_all(AT_IMMORT, buf, ECHOTAR_ALL);
	}

		  ch->hit = ch->max_hit;
		  ch->mana = ch->max_mana;
		  ch->move = ch->max_move;

    return;
}

void gain_exp( CHAR_DATA *ch, int gain )
{
    char buf[MAX_STRING_LENGTH];

    /*if ( IS_NPC(ch) || ch->level >= LEVEL_AVATAR )
	return;*/
    if(IS_NPC(ch))
    {
        if(!xIS_SET( ch->act, ACT_PET))
            return;
        
        ch->exp += gain;
        if(ch->exp >= exp_level(ch, ch->level+1))
        {
            send_to_char( "&YYour pet has gained a level!\n\r", ch->master);
            ++ch->level;
            advance_level( ch );
        }            
        return;
    }

    /* Deadly exp loss floor is exp floor of level */
    if(IS_PKILL(ch)&& gain<0){
       if( ch->exp + gain < exp_level(ch, ch->level)){
          gain = exp_level(ch, ch->level) - ch->exp;
          sprintf(buf,"Drazuk's Pandect protects your insight.\n\r");
       }
    }
/*
    if( ch->tmplevel && ch->tmplevel > 50)
	gain = 0;
*/

    ch->exp = UMAX( 0, ch->exp + gain );

    if (NOT_AUTHED(ch) && ch->exp >= exp_level(ch, ch->level+1))
    {
	send_to_char("You can not ascend to a higher level until you are authorized.\n\r", ch);
	ch->exp = (exp_level(ch, (ch->level+1)) - 1);
	return;
    }

	if(ch->level >= LEVEL_AVATAR)
		return;

    if(xIS_SET(ch->act, PLR_TIER) && ch->level < LEVEL_AVATAR && ch->exp >= exp_level(ch, ch->level+1) && ch->tmplevel < 50 )
    {
        set_char_color( AT_WHITE + AT_BLINK, ch );
        ch_printf( ch, "You have now obtained experience level %d!\n\r", ++ch->level );
        tadvance_level(ch); 
        return;
    } 

    while ( ch->level < LEVEL_AVATAR && ch->exp >= exp_level(ch, ch->level+1) && ch->tmplevel < 50)
    {
        set_char_color( AT_WHITE + AT_BLINK, ch );
        ch_printf( ch, "You have now obtained experience level %d!\n\r", ++ch->level );
        advance_level( ch );
    }

    return;
}



/*
 * Regeneration stuff.
 */
int hit_gain( CHAR_DATA *ch )
{
    int gain;

    if ( IS_NPC(ch) )
    {
	gain = 1;
    }
    else
    {
	gain = UMIN( 1, ch->level/5 );

	switch ( ch->position )
	{
	case POS_DEAD:	   return -2;
	case POS_MORTAL:   return -2;
	case POS_INCAP:    return -1;
	case POS_STUNNED:  return 1;
	case POS_SLEEPING: gain += 5 + get_curr_con(ch);	break;
	case POS_RESTING:  gain += 5 + (get_curr_con(ch) / 2);	break;
	}
/*
	if ( ch->pcdata->condition[COND_FULL]   == 0 )
	    gain /= 2;

	if ( ch->pcdata->condition[COND_THIRST] == 0 )
	    gain /= 2;
*/
    }

    if ( IS_AFFECTED(ch, AFF_POISON) )
	gain /= 4;

    if (ch->on != NULL)
	gain *= 2;

    if ( gain < 1 )
	gain = 1;

    if ( IS_SET(ch->in_room->room_flags, ROOM_HEALING) )
	gain *= 3;

    return UMIN(gain, ch->max_hit - ch->hit);
}



int mana_gain( CHAR_DATA *ch )
{
    int gain;

    gain = 0;

    if ( IS_NPC(ch) )
    {
	gain = 1;
    }
	else
	{
		if ( !IS_NPC(ch) && ch->level < 51 )
		{
			gain = UMIN( 1, ch->level / 10 );

			if ( ch->position < POS_SLEEPING )
			  return 0;
			switch ( ch->position )
			{
			case POS_SLEEPING: gain += (5 + get_curr_int(ch));	break;
			case POS_RESTING:  gain += (5 + (get_curr_int(ch) / 2));	break;
			}
		}
		else if ( !IS_NPC(ch) && IS_DEMI(ch) )
		{
			CHAR_DATA *vch; 
			CHAR_DATA *vch_next;
                     
			for ( vch = first_char; vch; vch = vch_next )
			{
				vch_next = vch->next;
     
				if ( !IS_NPC(vch) && ch->pcdata->clan && vch->pcdata->clan && (vch->pcdata->clan == ch->pcdata->clan) )
				   gain += 1;
			}
			return UMIN(gain, ch->max_mana - ch->mana);
		}
		else
		{
			gain = UMIN( 1, ch->level / 5 );
		}
	}

/*
	if ( ch->pcdata->condition[COND_FULL]   == 0 )
	    gain /= 2;

	if ( ch->pcdata->condition[COND_THIRST] == 0 )
	    gain /= 2;
*/

	if (!IS_IMMORTAL(ch))
	{
		if ( IS_AFFECTED(ch, AFF_POISON) )
			gain /= 4;
    
		if (ch->on != NULL)
			gain *= 2;
	}

    if ( gain < 1 )
        gain = 1;

    if ( IS_SET(ch->in_room->room_flags, ROOM_MENTAL) )
        gain *= 3;

    return UMIN(gain, ch->max_mana - ch->mana);
}



int move_gain( CHAR_DATA *ch )
{
    int gain;

    if ( IS_NPC(ch) )
    {
	gain = ch->level;
    }
    else
    {
	gain = UMAX( 1, ch->level / 5 );

	switch ( ch->position )
	{
	case POS_DEAD:	   return 0;
	case POS_MORTAL:   return -1;
	case POS_INCAP:    return -1;
	case POS_STUNNED:  return 1;
	case POS_SLEEPING: gain += (5 + get_curr_dex(ch) );	break;
	case POS_RESTING:  gain += (5 + (get_curr_dex(ch) / 2));	break;
	}
/*
	if ( ch->pcdata->condition[COND_FULL]   == 0 )
	    gain /= 2;

	if ( ch->pcdata->condition[COND_THIRST] == 0 )
	    gain /= 2;
*/    
	}

    if ( IS_AFFECTED(ch, AFF_POISON) )
	gain /= 4;

    if (ch->on != NULL)
	gain *= 2;

    if ( gain < 1 )
        gain = 1;

    if ( IS_SET(ch->in_room->room_flags, ROOM_HEALING) )
        gain *= 3;

    return UMIN(gain, ch->max_move - ch->move);
}


void gain_condition( CHAR_DATA *ch, int iCond, int value )
{
    int condition;
    ch_ret retcode = rNONE;

    if  (   value == 0 
        ||  IS_NPC(ch) 
        ||  NOT_AUTHED(ch) 
        )
        return;

    condition				        = ch->pcdata->condition[iCond];
    ch->pcdata->condition[iCond]	= URANGE( 0, condition + value, 100 );

    // only apply hunger and thirst to characters that are level 5 to 49
    // and are not tiered
    if(     ( !IS_TIER(ch)              )
        &&  ( ch->level >= 5            )
        &&  ( ch->level < LEVEL_AVATAR  )
        )
    {
        if( ch->pcdata->condition[iCond] == 0 )
        {
            switch ( iCond )
            {
            case COND_FULL:
                set_char_color( AT_HUNGRY, ch );
                send_to_char( "You are STARVING!\n\r",  ch );
                break;

            case COND_THIRST:
                set_char_color( AT_THIRSTY, ch );
                send_to_char( "You are DYING of THIRST!\n\r", ch );
                break;

            case COND_BLOODTHIRST:
                set_char_color( AT_BLOOD, ch );
                send_to_char( "You are starved to feast on blood!\n\r", ch );
                break;
            case COND_DRUNK:
                if ( condition != 0 ) 
                {
                    set_char_color( AT_SOBER, ch );
                    send_to_char( "You are sober.\n\r", ch );
                }
                retcode = rNONE;
                break;
            default:
                bug( "Gain_condition: invalid condition type %d", iCond );
                retcode = rNONE;
                break;
            }
        }

        if ( retcode != rNONE )
            return;

        if( ch->pcdata->condition[iCond] == 1 )
        {
            switch ( iCond )
            {
            case COND_FULL:
                    set_char_color( AT_HUNGRY, ch );
                    send_to_char( "You are really hungry.\n\r",  ch );
                break;

            case COND_THIRST:
                    set_char_color( AT_THIRSTY, ch );
                    send_to_char( "You are really thirsty.\n\r", ch );
                break;

            case COND_BLOODTHIRST:
                    set_char_color( AT_BLOOD, ch );
                    send_to_char( "You have a growing need to feast on blood!\n\r", ch );
                break;
            case COND_DRUNK:
                if ( condition != 0 ) 
                {
                    set_char_color( AT_SOBER, ch );
                    send_to_char( "You are feeling a little less light headed.\n\r", ch );
                }
                break;
            }
        }

        if( ch->pcdata->condition[iCond] == 2 )
        {
            switch ( iCond )
            {
            case COND_FULL:
                set_char_color( AT_HUNGRY, ch );
                send_to_char( "You are hungry.\n\r",  ch );
                break;

            case COND_THIRST:
                set_char_color( AT_THIRSTY, ch );
                send_to_char( "You are thirsty.\n\r", ch );
                break;

            case COND_BLOODTHIRST:
                set_char_color( AT_BLOOD, ch );
                send_to_char( "You feel an urgent need for blood.\n\r", ch );
                break;
            }
        }

        if( ch->pcdata->condition[iCond] == 3 )
        {
            switch ( iCond )
            {
            case COND_FULL:
                set_char_color( AT_HUNGRY, ch );
                send_to_char( "You are a mite peckish.\n\r",  ch );
                break;

            case COND_THIRST:
                set_char_color( AT_THIRSTY, ch );
                send_to_char( "You could use a sip of something refreshing.\n\r", ch );
                break;

            case COND_BLOODTHIRST:
                set_char_color( AT_BLOOD, ch );
                send_to_char( "You feel an aching in your fangs.\n\r", ch );
                break;
            }
        }
    }
    else
    {
        if(iCond != COND_DRUNK)
            ch->pcdata->condition[iCond] = 95;
        else
            ch->pcdata->condition[iCond] = 0;
    }

    return;
}


/*
 * Put this in a seperate function so it isn't called three times per tick
 * This was added after a suggestion from Cronel	--Shaddai
 */

void check_alignment( CHAR_DATA *ch )
{
     /*
      *  Race alignment restrictions, h
      */
     if(ch->alignment<race_table[ch->race]->minalign)
     {
	set_char_color( AT_BLOOD, ch );
        send_to_char( "Your actions have been incompatible with the ideals of your race.  This troubles you.", ch);
     }

     if(ch->alignment>race_table[ch->race]->maxalign)
     {
	set_char_color( AT_BLOOD, ch );
        send_to_char( "Your actions have been incompatible with the ideals of your race.  This troubles you.", ch);
     }
}

/*
 * Mob autonomous action.
 * This function takes 25% to 35% of ALL Mud cpu time.
 */
void mobile_update( void )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *ch;
    EXIT_DATA *pexit;
    int door;
    ch_ret     retcode;

    retcode = rNONE;

    /* Examine all mobs. */
    for ( ch = last_char; ch; ch = gch_prev )
    {
	set_cur_char( ch );
	if ( ch == first_char && ch->prev )
	{
	    bug( "mobile_update: first_char->prev != NULL... fixed", 0 );
	    ch->prev = NULL;
	}
	  
	gch_prev = ch->prev;
	
	if ( gch_prev && gch_prev->next != ch )
	{
	    sprintf( buf, "FATAL: Mobile_update: %s->prev->next doesn't point to ch.",
		ch->name );
	    bug( buf, 0 );	    
	    bug( "Short-cutting here", 0 );
	    gch_prev = NULL;
	    ch->prev = NULL;
	    do_shout( ch, "Drazuk says, 'Prepare for the worst!'" );
	}

	if ( !IS_NPC(ch) )
	{
	    drunk_randoms(ch);
	    hallucinations(ch);
	    continue;
	}

	if(ch->charmed_from && !IS_AFFECTED(ch, AFF_CHARM))
	{
		char_from_room(ch);
		char_to_room(ch, get_room_index(ch->charmed_from));
		ch->charmed_from = 0;
	}


	if ( !ch->in_room
	||   IS_AFFECTED(ch, AFF_CHARM)
	||   IS_AFFECTED(ch, AFF_PARALYSIS) )
	    continue;

        /* If PK Attackers time is up, release the victims name */
	if ( !IS_NPC(ch) && get_timer( ch, TIMER_PKER ) <= 0 && ch->pcdata->pkvictim != NULL )
	{
	    ch->pcdata->pkvictim = NULL;
            continue;
        }   
              
/* Clean up 'animated corpses' that are not charmed' - Scryn */

        if ( (ch->pIndexData->vnum == MOB_VNUM_ANIMATED_CORPSE		&& !IS_AFFECTED(ch, AFF_CHARM)) ||
             (ch->pIndexData->vnum == MOB_VNUM_BEAST				&& !IS_AFFECTED(ch, AFF_CHARM)) ||
			 (ch->pIndexData->vnum == MOB_VNUM_ETHEREAL_GUARDIAN	&& !IS_AFFECTED(ch, AFF_CHARM)) ||
			 (ch->pIndexData->vnum == MOB_VNUM_SUMMONED_SPIRIT		&& !IS_AFFECTED(ch, AFF_CHARM))  )
	{
	  if(ch->in_room->first_person)
	    act(AT_MAGIC, "$n returns to the plane from whence $e came.", ch, NULL, NULL, TO_ROOM);       

          if ( ch->master != NULL && !IS_NPC( ch->master ) )
          {
			  if(ch->pIndexData->vnum == MOB_VNUM_ETHEREAL_GUARDIAN)
				  ch->master->pcdata->charmies -= 5;
		     ch->master->pcdata->charmies--;
          }

   	  if(IS_NPC(ch)) /* Guard against purging switched? */
	    extract_char(ch, TRUE);
	  continue;
	}

        if ( (ch->pIndexData->vnum == 4 && !IS_AFFECTED(ch, AFF_CHARM)) ||
             (ch->pIndexData->vnum == 6 && !IS_AFFECTED(ch, AFF_CHARM)) ||
             (ch->pIndexData->vnum == 7 && !IS_AFFECTED(ch, AFF_CHARM)) ||
             (ch->pIndexData->vnum == 8 && !IS_AFFECTED(ch, AFF_CHARM)) ||
             (ch->pIndexData->vnum == 9 && !IS_AFFECTED(ch, AFF_CHARM)) ||
			 (ch->pIndexData->vnum == 18 && !IS_AFFECTED(ch, AFF_CHARM)) )
        { 
          if(ch->in_room->first_person) 
            act(AT_MAGIC, "$n returns to the plane from whence $e came.", ch, NULL, NULL, TO_ROOM);
             
          if ( ch->master != NULL && !IS_NPC( ch->master ) )
          {
             ch->master->pcdata->charmies = 0;
          } 
         
          if(IS_NPC(ch)) /* Guard against purging switched? */
            extract_char(ch, TRUE);
          continue; 
        }



	if ( !xIS_SET( ch->act, ACT_RUNNING )
	&&   !xIS_SET( ch->act, ACT_SENTINEL )
	&&   !ch->fighting && ch->hunting )
	{
	  WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
	  /* Commented out temporarily to avoid spam - Scryn 
	  sprintf( buf, "%s hunting %s from %s.", ch->name,
	  	ch->hunting->name,
		ch->in_room->name );
	  log_string( buf ); */
	  hunt_victim( ch );
	  continue;
	}  

	/* Examine call for special procedure */
	if ( !xIS_SET( ch->act, ACT_RUNNING )
	&&    ch->spec_fun )
	{
	    if ( (*ch->spec_fun) ( ch ) )
		continue;
	    if ( char_died(ch) )
		continue;
	}

	/* Check for mudprogram script on mob */
	if ( HAS_PROG( ch->pIndexData, SCRIPT_PROG ) )
	{
	    mprog_script_trigger( ch );
	    continue;
	}

	if ( ch != cur_char )
	{
	    bug( "Mobile_update: ch != cur_char after spec_fun", 0 );
	    continue;
	}

	/* That's all for sleeping / busy monster */
	if ( ch->position != POS_STANDING )
	    continue;

	if ( xIS_SET(ch->act, ACT_MOUNTED ) )
	{
	    if ( xIS_SET(ch->act, ACT_AGGRESSIVE) )
		do_emote( ch, "snarls and growls." );
	    continue;
	}

	if ( IS_SET(ch->in_room->room_flags, ROOM_SAFE )
	&&  (xIS_SET(ch->act, ACT_AGGRESSIVE) ) )
	    do_emote( ch, "glares around and snarls." );


	/* MOBprogram random trigger */
	if ( ch->in_room->area->nplayer > 0 )
	{
	    mprog_random_trigger( ch );
	    if ( char_died(ch) )
		continue;
	    if ( ch->position < POS_STANDING )
	        continue;
	}

        /* MOBprogram hour trigger: do something for an hour */
        mprog_hour_trigger(ch);

	if ( char_died(ch) )
	  continue;

	rprog_hour_trigger(ch);
	if ( char_died(ch) )
	  continue;

	if ( ch->position < POS_STANDING )
	  continue;

	/* Scavenge */
	if ( xIS_SET(ch->act, ACT_SCAVENGER)
	&&   ch->in_room->first_content
	&&   number_bits( 2 ) == 0 )
	{
	    OBJ_DATA *obj;
	    OBJ_DATA *obj_best;
	    int max;

	    max         = 1;
	    obj_best    = NULL;
	    for ( obj = ch->in_room->first_content; obj; obj = obj->next_content )
	    {
		if ( CAN_WEAR(obj, ITEM_TAKE) && obj->cost > max 
		&& !IS_OBJ_STAT( obj, ITEM_BURIED ) && obj->item_type != ITEM_CORPSE_PC )
		{
		    obj_best    = obj;
		    max         = obj->cost;
		}
	    }

	    if ( obj_best )
	    {
		obj_from_room( obj_best );
		obj_to_char( obj_best, ch );
		act( AT_ACTION, "$n gets $p.", ch, obj_best, NULL, TO_ROOM );
	    }
	}

	/* Wander */
	if ( !xIS_SET(ch->act, ACT_RUNNING)
	&&   !xIS_SET(ch->act, ACT_SENTINEL)
	&& ( door = number_bits( 5 ) ) <= 9
	&& ( pexit = get_exit(ch->in_room, door) ) != NULL
	&&   pexit->to_room
	&&   !IS_SET(pexit->exit_info, EX_CLOSED)
	&&   !IS_SET(pexit->to_room->room_flags, ROOM_NO_MOB)
	&&   !IS_SET(pexit->to_room->room_flags, ROOM_DEATH)
	&& ( !xIS_SET(ch->act, ACT_STAY_AREA)
	||   pexit->to_room->area == ch->in_room->area ) )
	{
	    retcode = move_char( ch, pexit, 0, FALSE );
						/* If ch changes position due
						to it's or someother mob's
						movement via MOBProgs,
						continue - Kahn */
	    if ( char_died(ch) )
	      continue;
	    if ( retcode != rNONE || xIS_SET(ch->act, ACT_SENTINEL)
	    ||    ch->position < POS_STANDING )
	        continue;
	}

	/* Flee */
	if ( ch->hit < ch->max_hit / 2
	&& ( door = number_bits( 4 ) ) <= 9
	&& ( pexit = get_exit(ch->in_room,door) ) != NULL
	&&   pexit->to_room
	&&   !IS_SET(pexit->exit_info, EX_CLOSED)
	&&   !IS_SET(pexit->to_room->room_flags, ROOM_NO_MOB) )
	{
	    CHAR_DATA *rch;
	    bool found;

	    found = FALSE;
	    for ( rch  = ch->in_room->first_person;
		  rch;
		  rch  = rch->next_in_room )
	    {
		if ( is_fearing(ch, rch) )
		{
		    switch( number_bits(2) )
		    {
			case 0:
			  sprintf( buf, "Get away from me, %s!", IS_NPC(rch) ? rch->short_descr : rch->name );
			  break;
			case 1:
			  sprintf( buf, "Leave me be, %s!", IS_NPC(rch) ? rch->short_descr : rch->name );
			  break;
			case 2:
			  sprintf( buf, "%s is trying to kill me!  Help!", IS_NPC(rch) ? rch->short_descr : rch->name );
			  break;
			case 3:
			  sprintf( buf, "Someone save me from %s!", IS_NPC(rch) ? rch->short_descr : rch->name );
			  break;
		    }
		    do_yell( ch, buf );
		    found = TRUE;
		    break;
		}
	    }
	    if ( found )
		retcode = move_char( ch, pexit, 0, FALSE );
	}
    }

    return;
}



/*
 * Update all chars, including mobs.
 * This function is performance sensitive.
 */
void char_update( void )
{   
    CHAR_DATA *ch;
    CHAR_DATA *ch_save;
    sh_int save_count = 0;

    ch_save	= NULL;
    for ( ch = last_char; ch; ch = gch_prev )
    {
	if ( ch == first_char && ch->prev )
	{
	    bug( "char_update: first_char->prev != NULL... fixed", 0 );
	    ch->prev = NULL;
	}
	gch_prev = ch->prev;
	set_cur_char( ch );
	if ( gch_prev && gch_prev->next != ch )
	{
	    bug( "char_update: ch->prev->next != ch", 0 );
	    return;
	}

	if(!IS_NPC(ch)) call_lua (ch, "char_update", NULL);

    /*
	 *  Do a room_prog rand check right off the bat
	 *   if ch disappears (rprog might wax npc's), continue
	 */
	if(!IS_NPC(ch))
	    rprog_random_trigger( ch );

	if( char_died(ch) )
	    continue;

	if(IS_NPC(ch))
	    mprog_time_trigger(ch);   

	if( char_died(ch) )
	    continue;

	rprog_time_trigger(ch);

	if( char_died(ch) )
	    continue;

        if ( (!IS_PET(ch) && IS_AFFECTED(ch, AFF_CHARM) && ch->master && (ch->in_room->vnum != ch->master->in_room->vnum))
            || (IS_PET(ch) && ch->master && (ch->in_room->vnum != ch->master->in_room->vnum) && ch->position > POS_SITTING ) )
        { 
            ROOM_INDEX_DATA *room;
            room = get_room_index(ch->master->in_room->vnum);
            char_from_room( ch );
            char_to_room( ch, room );
            act( AT_MAGIC, "$n arrives, looking for its master!", ch, NULL, NULL, TO_ROOM);
            if (xIS_SET( ch->act, ACT_MOUNTED ) )
            { 
                xREMOVE_BIT( ch->act, ACT_MOUNTED );
            }
            continue;
        } 

	/*
	 * See if player should be auto-saved.
	 */
	if ( !IS_NPC(ch)
	&& ( !ch->desc || ch->desc->connected == CON_PLAYING )
	&&    ch->level >= 2
	&&    current_time - ch->save_time > (sysdata.save_frequency*60) )
	    ch_save	= ch;
	else
	    ch_save	= NULL;

	if ( ch->position >= POS_STUNNED )
	{
	    if ( ch->hit  < ch->max_hit )
	       ch->hit  += hit_gain(ch);
            if( ch->hit > ch->max_hit )
               ch->hit = ch->max_hit;
                  
	    if ( ch->mana < ch->max_mana )
		ch->mana += mana_gain(ch);
            if( ch->mana > ch->max_mana )
                ch->mana = ch->max_mana;

	    if ( ch->move < ch->max_move )
		ch->move += move_gain(ch);
            if( ch->move > ch->max_move )
                ch->move = ch->max_move;
	}

	if ( ch->position == POS_STUNNED )
	    update_pos( ch );

      /*   Morph timer expires */

      	if ( ch->morph ) {
           if ( ch->morph->timer > 0 )
	   {
            	    ch->morph->timer--;
           	    if ( ch->morph->timer == 0 )
            	   	 do_unmorph_char( ch );
	   }
  	}

        /* To make people with a nuisance's flags life difficult 
         * --Shaddai
         */

        if ( !IS_NPC(ch) && ch->pcdata->nuisance )
        {
	    long int temp;
    
	    if ( ch->pcdata->nuisance->flags < MAX_NUISANCE_STAGE )
	    {
	     temp = ch->pcdata->nuisance->max_time-ch->pcdata->nuisance->time;
 	     temp *= ch->pcdata->nuisance->flags;
	     temp /= MAX_NUISANCE_STAGE;
	     temp += ch->pcdata->nuisance->time;
	     if ( temp < current_time )
		    ch->pcdata->nuisance->flags++;
	    }
        }

	if ( !IS_NPC(ch) && (ch->level < LEVEL_IMMORTAL ) )
	{
	    OBJ_DATA *obj;

	    if ( ( obj = get_eq_char( ch, WEAR_LIGHT ) ) != NULL
	    &&   (obj->item_type == ITEM_LIGHT || obj->item_type == ITEM_ARTLIGHT)
	    &&   obj->value[2] > 0 )
	    {
		if ( --obj->value[2] == 0 && ch->in_room )
		{
		    ch->in_room->light -= obj->count;
		    if (ch->in_room->light < 0 )
				ch->in_room->light=0;
		    act( AT_ACTION, "$p goes out.", ch, obj, NULL, TO_ROOM );
		    act( AT_ACTION, "$p goes out.", ch, obj, NULL, TO_CHAR );
		    if ( obj->serial == cur_obj )
		      global_objcode = rOBJ_EXPIRED;
		    extract_obj( obj );
		}
	    }


	    if ( ++ch->timer >= 12 ) 
	    {
		if ( !IS_IDLE( ch ) && !IS_IMMORTAL(ch) )
		{
		/*
		    ch->was_in_room = ch->in_room;
		    */
		    if ( ch->fighting )
			stop_fighting( ch, TRUE );
		    act( AT_ACTION, "$n disappears into the void.",
			ch, NULL, NULL, TO_ROOM );
		    send_to_char( "You disappear into the void.\n\r", ch );
		    if ( IS_SET( sysdata.save_flags, SV_IDLE ) )
			save_char_obj( ch );
		    SET_BIT(ch->pcdata->flags, PCFLAG_IDLE);
		    char_from_room( ch );
		    char_to_room( ch, get_room_index( ROOM_VNUM_LIMBO ) );
		}
	    }

		/* Send dreaming messages to sleeping PCs -Darwin */
		if ( !IS_NPC(ch) && ( ch->position == POS_SLEEPING ))
		{
            char *dream;
            call_va(L_mud, "random_dream", ">s", &dream);
            send_to_char( dream, ch );
		}

	    if ( ch->pcdata->condition[COND_DRUNK] > 8 )
            worsen_mental_state( ch, ch->pcdata->condition[COND_DRUNK]/8 );

	    if ( ch->pcdata->condition[COND_FULL] > 1 )
	    {
		switch( ch->position )
		{
		    case POS_SLEEPING:  better_mental_state( ch, 20 );	break;
		    case POS_RESTING:   better_mental_state( ch, 15);	break;
		    case POS_SITTING:
		    case POS_MOUNTED:   better_mental_state( ch, 10 );	break;
		    case POS_STANDING:  better_mental_state( ch, 5 );	break;
		    case POS_FIGHTING:
            case POS_EVASIVE:
            case POS_DEFENSIVE:
            case POS_AGGRESSIVE:
            case POS_BERSERK:
			if ( number_bits(2) == 0 )
			    better_mental_state( ch, 1 );
			break;
		}
	    }
	    if ( ch->pcdata->condition[COND_THIRST] > 1 )
	    {
		switch( ch->position )
		{
		    case POS_SLEEPING:  better_mental_state( ch, 20 );	break;
		    case POS_RESTING:   better_mental_state( ch, 15 );	break;
		    case POS_SITTING:
		    case POS_MOUNTED:   better_mental_state( ch, 10 );	break;
		    case POS_STANDING:  better_mental_state( ch, 5 );	break;
		    case POS_FIGHTING:
            case POS_EVASIVE:
            case POS_DEFENSIVE:
            case POS_AGGRESSIVE:
            case POS_BERSERK:
			if ( number_bits(2) == 0 )
			    better_mental_state( ch, 1 );
			break;
		}
	    }
	    /*
	     * Function added on suggestion from Cronel
	     */
	    check_alignment( ch );
	    if ( ch->pcdata->condition[COND_DRUNK] > 0 )
        {
            int dval = -1;
            
            switch( ch->position )
            {
            case POS_SLEEPING:  dval = -10;	break;
            case POS_RESTING:   dval = -5;	break;
            case POS_SITTING:
            case POS_MOUNTED:   dval = -2;	break;
            case POS_STANDING:  dval = -1;	break;
            case POS_FIGHTING:
            case POS_EVASIVE:
            case POS_DEFENSIVE:
            case POS_AGGRESSIVE:
            case POS_BERSERK:
                if ( number_bits(2) == 0 )
                    dval = 0;
                break;
            }
            gain_condition( ch, COND_DRUNK,  dval );
        }
        gain_condition( ch, COND_FULL,  -1 + race_table[ch->race]->hunger_mod );

	    //~ if ( CAN_PKILL( ch ) && ch->pcdata->condition[COND_THIRST] - 3 > 10 )
	      //~ gain_condition( ch, COND_THIRST, -3 );

	    if ( !IS_NPC( ch ) && ch->pcdata->nuisance )
	    {
		int value;
		
		value = ((0 - ch->pcdata->nuisance->flags)*ch->pcdata->nuisance->power);
		gain_condition ( ch, COND_THIRST, value );
		gain_condition ( ch, COND_FULL, --value );
	    }

	    if ( ch->in_room )
	      switch( ch->in_room->sector_type )
	      {
		default:
		    gain_condition( ch, COND_THIRST, -1 + race_table[ch->race]->thirst_mod);  break;
		case SECT_DESERT:
		    gain_condition( ch, COND_THIRST, -4 + race_table[ch->race]->thirst_mod);  break;
		case SECT_UNDERWATER:
		case SECT_OCEANFLOOR:
		    if ( number_bits(1) == 0 )
			gain_condition( ch, COND_THIRST, -1 + race_table[ch->race]->thirst_mod);  break;
	      }

	}
      if ( !IS_NPC(ch) && !IS_IMMORTAL(ch) && ch->pcdata->release_date > 0 &&
           ch->pcdata->release_date <= current_time )
      {
         ROOM_INDEX_DATA *location;
         if ( ch->pcdata->clan )
          location = get_room_index( ch->pcdata->clan->recall );
         else
          location = get_room_index(ROOM_VNUM_TEMPLE);
         if ( !location )
          location = ch->in_room;
         MOBtrigger = FALSE;
         char_from_room(ch);
         char_to_room( ch, location );
         send_to_char( "The gods have released you from hell as your sentance is up!\n\r", ch );
         do_look(ch, "auto");
         STRFREE( ch->pcdata->helled_by );
	 ch->pcdata->helled_by = NULL;
         ch->pcdata->release_date = 0;
         save_char_obj( ch );
      }

	if ( !char_died(ch) )
	{
	    /*
	     * Careful with the damages here,
	     *   MUST NOT refer to ch after damage taken, without checking
	     *   return code and/or char_died as it may be lethal damage.
	     */
	    if ( IS_AFFECTED(ch, AFF_POISON) )
	    {
		act( AT_POISON, "$n shivers and suffers.", ch, NULL, NULL, TO_ROOM );
		act( AT_POISON, "You shiver and suffer.", ch, NULL, NULL, TO_CHAR );
		ch->mental_state = URANGE( 20, ch->mental_state
				 + (IS_NPC(ch) ? 2 : IS_PKILL(ch) ? 3 : 4), 100 );
		damage( ch, ch, 6, gsn_poison );
	    }
	    else
	    if ( ch->position == POS_INCAP )
		damage( ch, ch, 1, TYPE_UNDEFINED );
	    else
	    if ( ch->position == POS_MORTAL )
		damage( ch, ch, 4, TYPE_UNDEFINED );
	    if ( char_died(ch) )
		continue;

	    /*
	     * Recurring spell affect
	     */
 	    if ( IS_AFFECTED(ch, AFF_RECURRINGSPELL) )
	    {
		AFFECT_DATA *paf, *paf_next;
		SKILLTYPE *skill;
		bool found = FALSE, died = FALSE;

		for ( paf = ch->first_affect; paf; paf = paf_next )
		{
		    paf_next = paf->next;
		    if ( paf->location == APPLY_RECURRINGSPELL )
		    {
			found = TRUE;
			if ( IS_VALID_SN(paf->modifier)
			&&  (skill=skill_table[paf->modifier]) != NULL
			&&   skill->type == SKILL_SPELL )
			{
			    if ( (*skill->spell_fun)(paf->modifier, ch->level, ch, ch) == rCHAR_DIED
			    ||   char_died(ch) )
			    {
				died = TRUE;
				break;
			    }
			}
		    }
		}
		if ( died )
		    continue;
		if ( !found )
		    xREMOVE_BIT(ch->affected_by, AFF_RECURRINGSPELL);
	    }

	    if ( ch->mental_state >= 30 )
		switch( (ch->mental_state+5) / 10 )
		{
		    case  3:
		    	send_to_char( "You feel feverish.\n\r", ch );
			act( AT_ACTION, "$n looks kind of out of it.", ch, NULL, NULL, TO_ROOM );
		    	break;
		    case  4:
		    	send_to_char( "You do not feel well at all.\n\r", ch );
			act( AT_ACTION, "$n doesn't look too good.", ch, NULL, NULL, TO_ROOM );
		    	break;
		    case  5:
		    	send_to_char( "You need help!\n\r", ch );
			act( AT_ACTION, "$n looks like $e could use your help.", ch, NULL, NULL, TO_ROOM );
		    	break;
		    case  6:
		    	send_to_char( "Seekest thou a cleric.\n\r", ch );
			act( AT_ACTION, "Someone should fetch a healer for $n.", ch, NULL, NULL, TO_ROOM );
		    	break;
		    case  7:
		    	send_to_char( "You feel reality slipping away...\n\r", ch );
			act( AT_ACTION, "$n doesn't appear to be aware of what's going on.", ch, NULL, NULL, TO_ROOM );
		    	break;
		    case  8:
		    	send_to_char( "You begin to understand... everything.\n\r", ch );
			act( AT_ACTION, "$n starts ranting like a madman!", ch, NULL, NULL, TO_ROOM );
		    	break;
		    case  9:
		    	send_to_char( "You are ONE with the universe.\n\r", ch );
			act( AT_ACTION, "$n is ranting on about 'the answer', 'ONE' and other mumbo-jumbo...", ch, NULL, NULL, TO_ROOM );
		    	break;
		    case 10:
		    	send_to_char( "You feel the end is near.\n\r", ch );
			act( AT_ACTION, "$n is muttering and ranting in tongues...", ch, NULL, NULL, TO_ROOM );
		    	break;
		}
	    if ( ch->mental_state <= -30 )
		switch( (abs(ch->mental_state)+5) / 10 )
		{
		    case  10:
			if ( ch->position > POS_SLEEPING )
			{
			   if ( (ch->position == POS_STANDING
			   ||    ch->position < POS_FIGHTING)
			   &&    number_percent()+10 < abs(ch->mental_state) )
				do_sleep( ch, "" );
			   else
				send_to_char( "You're barely conscious.\n\r", ch );
			}
			break;
		    case   9:
			if ( ch->position > POS_SLEEPING )
			{
			   if ( (ch->position == POS_STANDING
			   ||    ch->position < POS_FIGHTING)
			   &&   (number_percent()+20) < abs(ch->mental_state) )
				do_sleep( ch, "" );
			   else
				send_to_char( "You can barely keep your eyes open.\n\r", ch );
			}
			break;
		    case   8:
			if ( ch->position > POS_SLEEPING )
			{
			   if ( ch->position < POS_SITTING
			   &&  (number_percent()+30) < abs(ch->mental_state) )
				do_sleep( ch, "" );
			   else
				send_to_char( "You're extremely drowsy.\n\r", ch );
			}
			break;
		    case   7:
			if ( ch->position > POS_RESTING )
			   send_to_char( "You feel very unmotivated.\n\r", ch );
			break;
		    case   6:
			if ( ch->position > POS_RESTING )
			   send_to_char( "You feel sedated.\n\r", ch );
			break;
		    case   5:
			if ( ch->position > POS_RESTING )
			   send_to_char( "You feel sleepy.\n\r", ch );
			break;
		    case   4:
			if ( ch->position > POS_RESTING )
			   send_to_char( "You feel tired.\n\r", ch );
			break;
		    case   3:
			if ( ch->position > POS_RESTING )
			   send_to_char( "You could use a rest.\n\r", ch );
			break;
		}
	    if ( ch->timer > 24 )
		do_quit( ch, "auto" );
	    else
	    if ( ch == ch_save && IS_SET( sysdata.save_flags, SV_AUTO )
	    &&   ++save_count < 10 )	/* save max of 10 per tick */
		save_char_obj( ch );
	}
    }

    return;
}

void char_regen( void )
{   
    CHAR_DATA *ch;

    for ( ch = last_char; ch; ch = gch_prev )
    {
	if ( ch == first_char && ch->prev )
	{
	    bug( "char_regen: first_char->prev != NULL... fixed", 0 );
	    ch->prev = NULL;
	}
	gch_prev = ch->prev;
	set_cur_char( ch );
	if ( gch_prev && gch_prev->next != ch )
	{
	    bug( "char_regen: ch->prev->next != ch", 0 );
	    return;
	}
	if ( ch->position >= POS_STUNNED )
	{
	    if ( ch->hit  < ch->max_hit )
		ch->hit  += hit_gain(ch);

	    if ( ch->mana < ch->max_mana )
		ch->mana += mana_gain(ch);

	    if ( ch->move < ch->max_move )
		ch->move += move_gain(ch);
	}

	if ( ch->position == POS_STUNNED )
	    update_pos( ch );
   
        if ( ch->mental_state != 0 )
	    ch->mental_state = 0;
  /*
        if ( IS_IMMORTAL(ch) )
        {
	    ch->pcdata->condition[COND_FULL] = 100;
            ch->pcdata->condition[COND_THIRST] = 100;
        }
*/
	if( xIS_SET( ch->act, PLR_AUTOUPDATE_PROMPT ) )
				flush_buffer(ch->desc, TRUE);
    }
    return;
}


/*
 * Update all objs.
 * This function is performance sensitive.
 */
void obj_update( void )
{   
    OBJ_DATA *obj;
    sh_int AT_TEMP;

    for ( obj = last_object; obj; obj = gobj_prev )
    {
	CHAR_DATA *rch;
	char *message;

	if ( obj == first_object && obj->prev )
	{
	    bug( "obj_update: first_object->prev != NULL... fixed", 0 );
	    obj->prev = NULL;
	}
	gobj_prev = obj->prev;
	if ( gobj_prev && gobj_prev->next != obj )
	{
	    bug( "obj_update: obj->prev->next != obj", 0 );
	    return;
	}
	set_cur_obj( obj );
	if ( obj->carried_by )
	  oprog_random_trigger( obj ); 
	else
	if( obj->in_room && obj->in_room->area->nplayer > 0 )
	  oprog_random_trigger( obj ); 

        if( obj_extracted(obj) )
	  continue;

	if ( obj->item_type == ITEM_PIPE )
	{
	    if ( IS_SET( obj->value[3], PIPE_LIT ) )
	    {
		if ( --obj->value[1] <= 0 )
		{
		  obj->value[1] = 0;
		  REMOVE_BIT( obj->value[3], PIPE_LIT );
		}
		else
		if ( IS_SET( obj->value[3], PIPE_HOT ) )
		  REMOVE_BIT( obj->value[3], PIPE_HOT );
		else
		{
		  if ( IS_SET( obj->value[3], PIPE_GOINGOUT ) )
		  {
		    REMOVE_BIT( obj->value[3], PIPE_LIT );
		    REMOVE_BIT( obj->value[3], PIPE_GOINGOUT );
		  }
		  else
		    SET_BIT( obj->value[3], PIPE_GOINGOUT );
		}
		if ( !IS_SET( obj->value[3], PIPE_LIT ) )
		  SET_BIT( obj->value[3], PIPE_FULLOFASH );
	    }
	    else
	      REMOVE_BIT( obj->value[3], PIPE_HOT );
	}


/* Corpse decay (npc corpses decay at 8 times the rate of pc corpses) - Narn */

        if ( obj->item_type == ITEM_CORPSE_PC || obj->item_type == ITEM_CORPSE_NPC )
        {
          sh_int timerfrac = UMAX(1, obj->timer - 1);
          if ( obj->item_type == ITEM_CORPSE_PC )
	    timerfrac = (int)(obj->timer / 8 + 1);

	  if ( obj->timer > 0 && obj->value[2] > timerfrac )
	  {
            char buf[MAX_STRING_LENGTH];
            char name[MAX_STRING_LENGTH];
            char *bufptr;
            bufptr = one_argument( obj->short_descr, name ); 
            bufptr = one_argument( bufptr, name ); 
            bufptr = one_argument( bufptr, name ); 

	    separate_obj(obj);
            obj->value[2] = timerfrac; 
            sprintf( buf, corpse_descs[ UMIN( timerfrac - 1, 4 ) ], 
                          bufptr ); 

            STRFREE( obj->description );
            obj->description = STRALLOC( buf ); 
          }  
        }
       
	/* don't let inventory decay */
	if ( IS_OBJ_STAT(obj, ITEM_INVENTORY) )
	{
		/* special case for conjurer eq -Darwin */
		/* this will only happen if the eq was acquired through pk */
		if(IS_OBJ_STAT(obj, ITEM_CONJURER))
		{
			if( obj->timer > 0 )
			{
				if( --obj->timer == 0 )
				{
					if(obj->carried_by && !IS_NPC(obj->carried_by))
					{
						STRFREE( obj->owner );
						obj->owner = STRALLOC( obj->carried_by->name ); 

						xREMOVE_BIT(obj->extra_flags, ITEM_CONJURER);
						if(IS_OBJ_STAT(obj, ITEM_DEATHROT))
							xREMOVE_BIT(obj->extra_flags, ITEM_DEATHROT);
						obj->timer = -1;
					}
					else
					{
						if(obj->in_obj)
							obj_from_obj(obj);
						else if(obj->in_room)
							obj_from_room(obj);
						else if(obj->carried_by)
							obj_from_char(obj);

						extract_obj(obj);
						continue;
					}
				}
			}
		}
		continue;
	}

	/* groundrot items only decay on the ground */
	if ( IS_OBJ_STAT(obj, ITEM_GROUNDROT) && !obj->in_room )
	  continue;

	if ( ( obj->timer <= 0 || --obj->timer > 0 ) )
	  continue;
	
	/* if we get this far, object's timer has expired. */
 
         AT_TEMP = AT_PLAIN;
	 switch ( obj->item_type )
	 {
	 default:
	   message = "Drazuk collects $p for his personal collection.";
           AT_TEMP = AT_PLAIN;
	   break;
	 case ITEM_CONTAINER:
	   message = "$p falls apart, tattered from age.";
	   AT_TEMP = AT_OBJECT;
	   break; 
	 case ITEM_PORTAL:
	   message = "$p unravels and winks from existence.";
           remove_portal(obj);
	   obj->item_type = ITEM_TRASH;		/* so extract_obj	 */
           AT_TEMP = AT_MAGIC;			/* doesn't remove_portal */
	   break;
	 case ITEM_FOUNTAIN:
	   message = "$p dries up.";
           AT_TEMP = AT_BLUE;
	   break;
	 case ITEM_CORPSE_NPC:
	   message = "$p decays into dust and blows away.";
           AT_TEMP = AT_OBJECT;
	   break;
	 case ITEM_CORPSE_PC:
	   message = "$p is sucked into a swirling vortex of colors...";
           AT_TEMP = AT_MAGIC;
	   break;
	 case ITEM_COOK:
	 case ITEM_FOOD:
	   message = "$p is devoured by a swarm of maggots.";
           AT_TEMP = AT_HUNGRY;
	   break;
         case ITEM_BLOOD:
           message = "$p slowly seeps into the ground.";
           AT_TEMP = AT_BLOOD;
           break;
         case ITEM_BLOODSTAIN:
           message = "$p dries up into flakes and blows away.";
           AT_TEMP = AT_BLOOD;
	   break;
         case ITEM_SCRAPS:
           message = "$p crumble and decay into nothing.";
           AT_TEMP = AT_OBJECT;
	   break;
	 case ITEM_FIRE:
	   /* This is removed because it is done in obj_from_room
	    * Thanks to gfinello@mail.karmanet.it for pointing this out.
	    * --Shaddai
	   if (obj->in_room)
	   {
	     --obj->in_room->light;
	     if ( obj->in_room->light < 0 )
			obj->in_room->light = 0;
	   }
	   */
	   message = "$p burns out.";
	   AT_TEMP = AT_FIRE;
	 }

	if ( obj->carried_by )
	{
	    act( AT_TEMP, message, obj->carried_by, obj, NULL, TO_CHAR );
	}
	else if ( obj->in_room
	&&      ( rch = obj->in_room->first_person ) != NULL
	&&	!IS_OBJ_STAT( obj, ITEM_BURIED ) )
	{
	    act( AT_TEMP, message, rch, obj, NULL, TO_ROOM );
            act( AT_TEMP, message, rch, obj, NULL, TO_CHAR );
	}
	if ( obj->serial == cur_obj )
	  global_objcode = rOBJ_EXPIRED;

        if ( obj->item_type == ITEM_CORPSE_PC || obj->item_type == ITEM_CORPSE_NPC )
        {
           if (obj->carried_by)
           {
              empty_obj(obj, NULL, obj->carried_by->in_room);
           }
//	   else if (obj->in_obj) 
//	   {
//            empty_obj(obj, NULL, obj->in_obj->carried_by->in_room);
//         }
           else if (obj->in_room)
 	   {
              empty_obj(obj, NULL, obj->in_room);
	   }
        }


	extract_obj( obj );
    }
    return;
}


/*
 * Function to check important stuff happening to a player
 * This function should take about 5% of mud cpu time
 */
void char_check( void )
{
    CHAR_DATA *ch, *ch_next;
    OBJ_DATA *obj;
    EXIT_DATA *pexit;
    static int cnt = 0;
    int door, retcode;

    /* This little counter can be used to handle periodic events */
    cnt = (cnt+1) % SECONDS_PER_TICK;

    for ( ch = first_char; ch; ch = ch_next )
    {
	set_cur_char(ch);
	ch_next = ch->next;
	will_fall(ch, 0);

	if ( char_died( ch ) )
	  continue;

	if ( IS_NPC( ch ) )
	{
	    if ( (cnt & 1) )
		continue;

	    /* running mobs	-Thoric */
	    if ( xIS_SET(ch->act, ACT_RUNNING) )
	    {
		if ( !xIS_SET(ch->act, ACT_SENTINEL)
		&&   !ch->fighting && ch->hunting )
		{
		    WAIT_STATE( ch, 2 * PULSE_VIOLENCE );
		    hunt_victim( ch );
		    continue;
		}

		if ( ch->spec_fun )
		{
		    if ( (*ch->spec_fun) ( ch ) )
			continue;
		    if ( char_died(ch) )
			continue;
		}

		if ( !xIS_SET(ch->act, ACT_SENTINEL)
		&& ( door = number_bits( 4 ) ) <= 9
		&& ( pexit = get_exit(ch->in_room, door) ) != NULL
		&&   pexit->to_room
		&&   !IS_SET(pexit->exit_info, EX_CLOSED)
		&&   !IS_SET(pexit->to_room->room_flags, ROOM_NO_MOB)
		&&   !IS_SET(pexit->to_room->room_flags, ROOM_DEATH)
		&& ( !xIS_SET(ch->act, ACT_STAY_AREA)
		||   pexit->to_room->area == ch->in_room->area ) )
		{
		    retcode = move_char( ch, pexit, 0, FALSE );
		    if ( char_died(ch) )
			continue;
		    if ( retcode != rNONE || xIS_SET(ch->act, ACT_SENTINEL)
		    ||    ch->position < POS_STANDING )
			continue;
		}
	    }
	    continue;
	}
	else
	{
	    if ( ch->mount
	    &&   ch->in_room != ch->mount->in_room )
	    {
		xREMOVE_BIT( ch->mount->act, ACT_MOUNTED );
		ch->mount = NULL;
		ch->position = POS_STANDING;
		send_to_char( "No longer upon your mount, you fall to the ground...\n\rOUCH!\n\r", ch );
	    }

	    if ( ( ch->in_room && ch->in_room->sector_type == SECT_UNDERWATER )
	    || ( ch->in_room && ch->in_room->sector_type == SECT_OCEANFLOOR ) )
	    {
		if ( !IS_AFFECTED( ch, AFF_AQUA_BREATH ) )
		{
		    if ( ch->level < LEVEL_IMMORTAL )
		    {
			int dam;

        		/* Changed level of damage at Brittany's request. -- Narn */	
			//   dam = number_range( ch->max_hit / 100, ch->max_hit / 50 );
			dam = 25;
			if ( number_bits(2) == 0 )
			  send_to_char( "You cough and choke as you try to breathe water!\n\r", ch );
			damage( ch, ch, dam, TYPE_UNDEFINED );
		    }
		}
	    }
	
	    if ( char_died( ch ) )
		continue; 

	    if ( ch->in_room
	    && (( ch->in_room->sector_type == SECT_WATER_NOSWIM )
	    ||  ( ch->in_room->sector_type == SECT_WATER_SWIM ) ) )
	    {
		if ( !IS_AFFECTED( ch, AFF_FLYING )
		&& !IS_AFFECTED( ch, AFF_FLOATING ) 
		&& !IS_AFFECTED( ch, AFF_AQUA_BREATH )
		&& !ch->mount )
		{
		    for ( obj = ch->first_carrying; obj; obj = obj->next_content )
		      if ( obj->item_type == ITEM_BOAT ) break;

		    if ( !obj )
		    {
			if ( ch->level < LEVEL_IMMORTAL )
			{
			    int mov;
			    int dam;

				send_to_char( "You gasp for air but inhale water instead.\n\r", ch);

			    if ( ch->move > 0 )
			    {
				mov = number_range( ch->max_move / 20, ch->max_move / 5 );
				mov = UMAX( 1, mov );

				if ( ch->move - mov < 0 )
				    ch->move = 0;
				else
				    ch->move -= mov;
			    }
			    else
			    {
				dam = 25;

				if ( number_bits(3) == 0 )
				   send_to_char( "Struggling with exhaustion, you choke on a mouthful of water.\n\r", ch );
				send_to_char( "Water fills your lungs!\n\r", ch);
				damage( ch, ch, dam, TYPE_UNDEFINED );
			    }
			}
		    }
		}
	    }

	    /* beat up on link dead players */
	    if ( !ch->desc )
	    {
		CHAR_DATA *wch, *wch_next;

		for ( wch = ch->in_room->first_person; wch; wch = wch_next )
		{
		    wch_next	= wch->next_in_room;

		    if (!IS_NPC(wch)
		    ||   wch->fighting
		    ||   IS_AFFECTED(wch, AFF_CHARM)
		    ||   !IS_AWAKE(wch)
		    || (xIS_SET(wch->act, ACT_WIMPY) && IS_AWAKE(ch) )
		    ||   !can_see( wch, ch ) )
			continue;

		    if ( is_hating( wch, ch ) )
		    {
			found_prey( wch, ch );
			continue;
		    }

		    if ( (!xIS_SET(wch->act, ACT_AGGRESSIVE))
		    ||    xIS_SET(wch->act, ACT_MOUNTED)
		    ||    IS_SET(wch->in_room->room_flags, ROOM_SAFE ) )
			continue;
		    global_retcode = multi_hit( wch, ch, TYPE_UNDEFINED );
		}
	    }
	}
    }
}


int is_aggressive( CHAR_DATA *ch )
{
	if( xIS_SET(ch->act, ACT_AGGRESSIVE))
		return 1;
	else if(	xIS_SET(ch->act, ACT_AGGRESSIVE_LOW))
		return 2;
	else if(	xIS_SET(ch->act, ACT_AGGRESSIVE_MID))
		return 3;
	else if(	xIS_SET(ch->act, ACT_AGGRESSIVE_HIGH))
		return 4;
	else
		return 0;
}

/*
 * Aggress.
 *
 * for each descriptor
 *     for each mob in room
 *         aggress on some random PC
 *
 * This function should take 5% to 10% of ALL mud cpu time.
 * Unfortunately, checking on each PC move is too tricky,
 *   because we don't the mob to just attack the first PC
 *   who leads the party into the room.
 *
 */
void aggr_update( void )
{
    DESCRIPTOR_DATA *d, *dnext;
    CHAR_DATA *wch;
    CHAR_DATA *ch;
    CHAR_DATA *ch_next;
    CHAR_DATA *vch;
    CHAR_DATA *vch_next;
    CHAR_DATA *victim;
    struct act_prog_data *apdtmp;

#ifdef UNDEFD
  /*
   *  GRUNT!  To do
   *
   */
        if ( IS_NPC( wch ) && wch->mpactnum > 0
	    && wch->in_room->area->nplayer > 0 )
        {
            MPROG_ACT_LIST * tmp_act, *tmp2_act;
	    for ( tmp_act = wch->mpact; tmp_act;
		 tmp_act = tmp_act->next )
	    {
                 oprog_wordlist_check( tmp_act->buf,wch, tmp_act->ch,
				      tmp_act->obj, tmp_act->vo, ACT_PROG );
                 DISPOSE( tmp_act->buf );
            }
	    for ( tmp_act = wch->mpact; tmp_act; tmp_act = tmp2_act )
	    {
                 tmp2_act = tmp_act->next;
                 DISPOSE( tmp_act );
            }
            wch->mpactnum = 0;
            wch->mpact    = NULL;
        }
#endif

    /* check mobprog act queue */
    while ( (apdtmp = mob_act_list) != NULL )
    {
	wch = mob_act_list->vo;
	if ( !char_died(wch) && wch->mpactnum > 0 )
	{
	    MPROG_ACT_LIST * tmp_act;

	    while ( (tmp_act = wch->mpact) != NULL )
	    {
		if ( tmp_act->obj && obj_extracted(tmp_act->obj) )
		  tmp_act->obj = NULL;
		if ( tmp_act->ch && !char_died(tmp_act->ch) )
		  mprog_wordlist_check( tmp_act->buf, wch, tmp_act->ch,
					tmp_act->obj, tmp_act->vo, ACT_PROG );
		wch->mpact = tmp_act->next;
		DISPOSE(tmp_act->buf);
		DISPOSE(tmp_act);
	    }
	    wch->mpactnum = 0;
	    wch->mpact    = NULL;
        }
	mob_act_list = apdtmp->next;
	DISPOSE( apdtmp );
    }


    /*
     * Just check descriptors here for victims to aggressive mobs
     * We can check for linkdead victims in char_check	-Thoric
     */
    for ( d = first_descriptor; d; d = dnext )
    {
	dnext = d->next;
	if ( d->connected != CON_PLAYING || (wch=d->character) == NULL )
	   continue;

	if ( char_died(wch)
	||   IS_NPC(wch)
	||   wch->level >= LEVEL_IMMORTAL
	||  !wch->in_room )
	    continue;

	for ( ch = wch->in_room->first_person; ch; ch = ch_next )
	{
	    int count;

	    ch_next	= ch->next_in_room;

	    if ( !IS_NPC(ch)
	    ||   ch->fighting
	    ||   IS_AFFECTED(ch, AFF_CHARM)
	    ||   !IS_AWAKE(ch)
	    ||   (xIS_SET(ch->act, ACT_WIMPY) && IS_AWAKE(wch) )
	    ||   !can_see( ch, wch ) )
		continue;

	    if ( is_hating(ch, wch) )
	    {
		found_prey(ch, wch);
		continue;
	    }

	    if ( /*(!xIS_SET(ch->act, ACT_AGGRESSIVE))*/ 
			   !is_aggressive(ch)
	    ||     xIS_SET(ch->act, ACT_MOUNTED)
	    ||     IS_SET(ch->in_room->room_flags, ROOM_SAFE ) )
		continue;

	    /*
	     * Ok we have a 'wch' player character and a 'ch' npc aggressor.
	     * Now make the aggressor fight a RANDOM pc victim in the room,
	     *   giving each 'vch' an equal chance of selection.
	     *
	     */
	    count	= 0;
	    victim	= NULL;
	    for ( vch = wch->in_room->first_person; vch; vch = vch_next )
	    {
		vch_next = vch->next_in_room;

		if ( (!IS_NPC(vch) )
		&&   vch->level < LEVEL_IMMORTAL
		&&   (!xIS_SET(ch->act, ACT_WIMPY) || !IS_AWAKE(vch) )
		&&   can_see( ch, vch ) )
		{
			switch(is_aggressive(ch))
			{
			case 1: // Aggressive
			    if ( number_range( 0, count ) == 0 )
					victim = vch;
				break;
			case 2: // Aggressive-low
				if (( number_range( 0, count ) == 0 ) && ( CH_LEVEL(vch) < 16 ))
					victim = vch;
				break;
			case 3: // Aggressive-mid
				if (( number_range( 0, count ) == 0 ) && ( CH_LEVEL(vch) > 15 ))
					victim = vch;
				break;
			case 4: // Aggressive-high
				if (( number_range( 0, count ) == 0 ) && ( CH_LEVEL(vch) > 29 ))
					victim = vch;
				break;
			}
		    count++;
		}
	    }

	    if ( !victim )
	    {
		bug( "Aggr_update: null victim.", count );
		continue;
	    }

	    /* backstabbing mobs (Thoric) */
	    if ( IS_NPC(ch) && xIS_SET(ch->attacks, ATCK_BACKSTAB ) )
	    {
		OBJ_DATA *obj;

		if ( !ch->mount
    		&& (obj = get_eq_char( ch, WEAR_WIELD )) != NULL
    		&& (obj->value[3] == 11 || obj->value[3] == 2)
		&& !victim->fighting
		&& victim->hit >= victim->max_hit )
		{
		    //   check_attacker( ch, victim );
		    WAIT_STATE( ch, skill_table[gsn_backstab]->beats );
		    if ( !IS_AWAKE(victim)
		    ||   number_percent( )+5 < ch->level )
		    {
			global_retcode = multi_hit( ch, victim, gsn_backstab );
			continue;
		    }
		    else
		    {
			global_retcode = damage( ch, victim, 0, gsn_backstab );
			continue;
		    }
		}
	    }
	    global_retcode = multi_hit( ch, victim, TYPE_UNDEFINED );
	}
    }

    return;
}

/* From interp.c */
bool check_social  args( ( CHAR_DATA *ch, char *command, char *argument ) );

/*
 * drunk randoms	- Tricops
 * (Made part of mobile_update	-Thoric)
 */
void drunk_randoms( CHAR_DATA *ch )
{
    CHAR_DATA *rvch = NULL;
    CHAR_DATA *vch;
    sh_int drunk;
    sh_int position;

    if ( IS_NPC( ch ) || ch->pcdata->condition[COND_DRUNK] <= 0 )
	return;

    if ( number_percent() < 30 )
	return;

    drunk = ch->pcdata->condition[COND_DRUNK];
    position = ch->position;
    ch->position = POS_STANDING;

    if ( number_percent() < (2*drunk / 20) )
	check_social( ch, "burp", "" );
    else
    if ( number_percent() < (2*drunk / 20) )
	check_social( ch, "hiccup", "" );
    else
    if ( number_percent() < (2*drunk / 20) )
	check_social( ch, "drool", "" );
    else
    if ( number_percent() < (2*drunk / 20) )
	check_social( ch, "fart", "" );
    else
    if ( drunk > (10+(get_curr_con(ch)/5))
    &&   number_percent() < ( 2 * drunk / 18 ) )
    {
	for ( vch = ch->in_room->first_person; vch; vch = vch->next_in_room )
	    if ( number_percent() < 10 )
		rvch = vch;
	check_social( ch, "puke", (rvch ? rvch->name : "") );
    }

    ch->position = position;
    return;
}

/*
 * Random hallucinations for those suffering from an overly high mentalstate
 * (Hats off to Albert Hoffman's "problem child")	-Thoric
 */
void hallucinations( CHAR_DATA *ch )
{
    if ( ch->mental_state >= 30 && number_bits(5 - (ch->mental_state >= 50) - (ch->mental_state >= 75)) == 0 )
    {
	char *t;

	switch( number_range( 1, UMIN(21, (ch->mental_state+5) / 5)) )
	{
	    default:
	    case  1: t = "You feel very restless... you can't sit still.\n\r";		break;
	    case  2: t = "You're tingling all over.\n\r";				break;
	    case  3: t = "Your skin is crawling.\n\r";					break;
	    case  4: t = "You suddenly feel that something is terribly wrong.\n\r";	break;
	    case  5: t = "Those damn little fairies keep laughing at you!\n\r";		break;
	    case  6: t = "You can hear your mother crying...\n\r";			break;
	    case  7: t = "Have you been here before, or not?  You're not sure...\n\r";	break;
	    case  8: t = "Painful childhood memories flash through your mind.\n\r";	break;
	    case  9: t = "You hear someone call your name in the distance...\n\r";	break;
	    case 10: t = "Your head is pulsating... you can't think straight.\n\r";	break;
	    case 11: t = "The ground... seems to be squirming...\n\r";			break;
	    case 12: t = "You're not quite sure what is real anymore.\n\r";		break;
	    case 13: t = "It's all a dream... or is it?\n\r";				break;
	    case 14: t = "You hear your grandchildren praying for you to watch over them.\n\r";	break;
	    case 15: t = "They're coming to get you... coming to take you away...\n\r";	break;
	    case 16: t = "You begin to feel all powerful!\n\r";				break;
	    case 17: t = "You're light as air... the heavens are yours for the taking.\n\r";	break;
	    case 18: t = "Your whole life flashes by... and your future...\n\r";	break;
	    case 19: t = "You are everywhere and everything... you know all and are all!\n\r";	break;
	    case 20: t = "You feel immortal!\n\r";					break;
	    case 21: t = "Ahh... the power of a Supreme Entity... what to do...\n\r";	break;
	}
	send_to_char( t, ch );
    }
    return;
}

void tele_update( void )
{
    TELEPORT_DATA *tele, *tele_next;

    if ( !first_teleport )
      return;
    
    for ( tele = first_teleport; tele; tele = tele_next )
    {
	tele_next = tele->next;
	if ( --tele->timer <= 0 )
	{
	    if ( tele->room->first_person )
	    {
		if ( IS_SET( tele->room->room_flags, ROOM_TELESHOWDESC ) )
		  teleport( tele->room->first_person, tele->room->tele_vnum,
			TELE_SHOWDESC | TELE_TRANSALL );
		else
		  teleport( tele->room->first_person, tele->room->tele_vnum,
			TELE_TRANSALL );
	    }
	    UNLINK( tele, first_teleport, last_teleport, next, prev );
	    DISPOSE( tele );
	}
    }
}

#if FALSE
/* 
 * Write all outstanding authorization requests to Log channel - Gorog
 */ 
void auth_update( void ) 
{ 
  CHAR_DATA *victim; 
  DESCRIPTOR_DATA *d; 
  char log_buf [MAX_INPUT_LENGTH];
  bool first_time = TRUE;         /* so titles are only done once */

  for ( d = first_descriptor; d; d = d->next ) 
      {
      victim = d->character;
      if ( victim && IS_WAITING_FOR_AUTH(victim) )
         {
         if ( first_time )
            {
            first_time = FALSE;
            strcpy (log_buf, "Pending authorizations:" ); 
            /*log_string( log_buf ); */
            to_channel( log_buf, CHANNEL_AUTH, "Auth", 1);
            }
         sprintf( log_buf, " %s@%s new %s %s", victim->name,
            victim->desc->host, race_table[victim->race]->race_name, 
            class_table[victim->class]->who_name ); 
/*         log_string( log_buf ); */
         to_channel( log_buf, CHANNEL_AUTH, "Auth", 1);
         }
      }
} 
#endif

void auth_update( void ) 
{ 
    CHAR_DATA *victim; 
    DESCRIPTOR_DATA *d; 
    char buf [MAX_INPUT_LENGTH], log_buf [MAX_INPUT_LENGTH];
    bool found_hit = FALSE;         /* was at least one found? */

    strcpy (log_buf, "Pending authorizations:\n\r" );
    for ( d = first_descriptor; d; d = d->next ) 
    {
	if ( (victim = d->character) && IS_WAITING_FOR_AUTH(victim) )
	{
	    found_hit = TRUE;
	    sprintf( buf, " %s@%s new %s %s\n\r", victim->name,
		victim->desc->host, race_table[victim->race]->race_name, 
		class_table[victim->class]->who_name );
	    strcat (log_buf, buf);
	}
    }
    if (found_hit)
    {
/*	log_string( log_buf ); */
	to_channel( log_buf, CHANNEL_AUTH, "Auth", 1);
    }
} 

/*
 * Handle all kinds of updates.
 * Called once per pulse from game loop.
 * Random times to defeat tick-timing clients and players.
 */
void update_handler( void )
{
    static  int     pulse_area;
    static  int     pulse_mobile;
    static  int	    pulse_regen;
    static  int     pulse_violence;
    static  int     pulse_point;
    static  int	    pulse_second;
    struct timeval stime;
    struct timeval etime;

    if ( timechar )
    {
      set_char_color(AT_PLAIN, timechar);
      send_to_char( "Starting update timer.\n\r", timechar );
      gettimeofday(&stime, NULL);
    }
    
    if ( --pulse_area     <= 0 )
    {
	pulse_area	= PULSE_AREA; //number_range( PULSE_AREA / 2, 3 * PULSE_AREA / 2 );
	area_update	( );
	quest_update	( );
        mobmaster_update ( );
    }

    if ( --pulse_mobile   <= 0 )
    {
	pulse_mobile	= PULSE_MOBILE;
	mobile_update  ( );
    }

    if ( --pulse_regen   <= 0 )
    {
	pulse_regen	= PULSE_REGEN;
	char_regen ( );
    }

    if ( --pulse_violence <= 0 )
    {
	pulse_violence	= PULSE_VIOLENCE;
	violence_update	( );
    }

    if ( --pulse_point    <= 0 )
    {
	pulse_point     = PULSE_TICK; //number_range( PULSE_TICK * 0.75, PULSE_TICK * 1.25 );

        auth_update     ( );			/* Gorog */
        time_update	( );
	weather_update	( );
	char_update	( );
	obj_update	( );
	clear_vrooms	( );			/* remove virtual rooms */
    }

    if ( --pulse_second   <= 0 )
    {
	pulse_second	= PULSE_PER_SECOND;
	char_check( );
 	reboot_check(0);
        check_pfiles(0);
	acro_check();
    }

    if ( --auction->pulse <= 0 )
    {                                                  
	auction->pulse = PULSE_AUCTION;                     
	auction_update( );
    }

    tele_update( );
    aggr_update( );
    obj_act_update ( );
    room_act_update( );
    clean_obj_queue();		/* dispose of extracted objects */
    clean_char_queue();		/* dispose of dead mobs/quitting chars */
    if ( timechar )
    {
      gettimeofday(&etime, NULL);
      set_char_color(AT_PLAIN, timechar);
      send_to_char( "Update timing complete.\n\r", timechar );
      subtract_times(&etime, &stime);
      ch_printf( timechar, "Timing took %d.%06d seconds.\n\r",
          etime.tv_sec, etime.tv_usec );
      timechar = NULL;
    }
    tail_chain( );
    return;
}


void remove_portal( OBJ_DATA *portal )
{
    ROOM_INDEX_DATA *fromRoom, *toRoom;
    EXIT_DATA *pexit;
    bool found;

    if ( !portal )
    {
	bug( "remove_portal: portal is NULL", 0 );
	return;
    }

    fromRoom = portal->in_room;
    found = FALSE;
    if ( !fromRoom )
    {
	bug( "remove_portal: portal->in_room is NULL", 0 );
	return;
    }

    for ( pexit = fromRoom->first_exit; pexit; pexit = pexit->next )
	if ( IS_SET( pexit->exit_info, EX_PORTAL ) )
	{
	    found = TRUE;
	    break;
	}

    if ( !found )
    {
	bug( "remove_portal: portal not found in room %d!", fromRoom->vnum );
	return;
    }

    if ( pexit->vdir != DIR_PORTAL )
	bug( "remove_portal: exit in dir %d != DIR_PORTAL", pexit->vdir );

    if ( ( toRoom = pexit->to_room ) == NULL )
      bug( "remove_portal: toRoom is NULL", 0 );
 
    extract_exit( fromRoom, pexit );

    return;
}

void reboot_check( time_t reset )
{
  static char *tmsg[] =
  { "You feel the ground shake as the end comes near!",
    "Lightning crackles in the sky above!",
    "Crashes of thunder sound across the land!",
    "The sky has suddenly turned midnight black.",
    "You notice the life forms around you slowly dwindling away.",
    "The seas across the realm have turned frigid.",
    "The aura of magic that surrounds the realms seems slightly unstable.",
    "You sense a change in the magical forces surrounding you."
  };
  static const int times[] = { 60, 120, 180, 240, 300, 600, 900, 1800 };
  static const int timesize = 8;
      //~ UMIN(sizeof(times)/sizeof(*times), sizeof(tmsg)/sizeof(*tmsg));
  char buf[MAX_STRING_LENGTH];
  static int trun;
  static bool init = FALSE;
  
  if ( !init || reset >= current_time )
  {
    for ( trun = timesize-1; trun >= 0; trun-- )
      if ( reset >= current_time+times[trun] )
        break;
    init = TRUE;
    return;
  }
  
  if ( (current_time % 1800) == 0 )
  {
    sprintf(buf, "%.24s: %d players", ctime(&current_time), num_descriptors);
    append_to_file(USAGE_FILE, buf);
    sprintf(buf, "%.24s:  %dptn  %dpll  %dsc %dbr  %d global loot",
	ctime(&current_time),
	sysdata.upotion_val,
	sysdata.upill_val,
	sysdata.scribed_used,
	sysdata.brewed_used,
	sysdata.global_looted );
    append_to_file( ECONOMY_FILE, buf );
  }
  
  if ( new_boot_time_t - boot_time < 60*60*18 &&
      !set_boot_time->manual )
    return;
  
  if ( new_boot_time_t <= current_time )
  {
    CHAR_DATA *vch;
    extern bool mud_down;
    
    if ( auction->item )
    {
      sprintf(buf, "Sale of %s has been stopped by mud.",
          auction->item->short_descr);
      talk_auction(buf);
      obj_to_char(auction->item, auction->seller);
      auction->item = NULL;
      if ( auction->buyer && auction->buyer != auction->seller )
      {
        auction->buyer->gold += auction->bet;
        send_to_char("Your money has been returned.\n\r", auction->buyer);
      }
    }
    echo_to_all(AT_YELLOW, "You are forced from these realms by a strong "
        "magical presence\n\ras life here is reconstructed.", ECHOTAR_ALL);
    log_string( "Automatic Reboot" ); 
    for ( vch = first_char; vch; vch = vch->next )
      if ( !IS_NPC(vch) )
        save_char_obj(vch);
    mud_down = TRUE;
    return;
  }
  
  if ( trun != -1 && new_boot_time_t - current_time <= times[trun] )
  {
    echo_to_all(AT_YELLOW, tmsg[trun], ECHOTAR_ALL);
    if ( trun <= 5 )
      sysdata.DENY_NEW_PLAYERS = TRUE;
    --trun;
    return;
  }
  return;
}
  
int taxed(int amount);
void tax(CHAR_DATA *ch, int amount);

/* the auction update*/

void auction_update (void)
{
    int ttax, pay;
    char buf[MAX_STRING_LENGTH];

    if(!auction->item)
    {
    	if(AUCTION_MEM > 0 && auction->history[0] &&
    			++auction->hist_timer == 6*AUCTION_MEM)
    	{
    		int i;
    		
    		for(i = AUCTION_MEM - 1; i >= 0; i--)
    		{
    			if(auction->history[i])
    			{
    				auction->history[i] = NULL;
    				auction->hist_timer = 0;
    				break;
    			}
    		}
    	}
    	return;
    }

    switch (++auction->going) /* increase the going state */
    {
	case 1 : /* going once */
	case 2 : /* going twice */
	    if (auction->bet > auction->starting)
		sprintf (buf, "%s: going %s for %s.", auction->item->short_descr,
			((auction->going == 1) ? "once" : "twice"), num_punct( auction->bet ) );
	    else
		sprintf (buf, "%s: going %s (bid not received yet).",  auction->item->short_descr,
			((auction->going == 1) ? "once" : "twice"));

	    talk_auction (buf);
	    break;

	case 3 : /* SOLD! */
	    if (!auction->buyer && auction->bet)
	    {
		bug( "Auction code reached SOLD, with NULL buyer, but %d gold bid", auction->bet );
		auction->bet = 0;
	    }
	    if (auction->bet > 0 && auction->buyer != auction->seller)
	    {
		sprintf (buf, "%s sold to %s for %s.",
			auction->item->short_descr,
			IS_NPC(auction->buyer) ? auction->buyer->short_descr : auction->buyer->name,
			num_punct(auction->bet) );
		talk_auction(buf);

		act(AT_ACTION, "The auctioneer materializes before you, and hands you $p.",
			auction->buyer, auction->item, NULL, TO_CHAR);
		act(AT_ACTION, "The auctioneer materializes before $n, and hands $m $p.",
			auction->buyer, auction->item, NULL, TO_ROOM);

		if ( (auction->buyer->carry_weight 
		+     get_obj_weight( auction->item ))
		>     can_carry_w( auction->buyer ) )
		{
		    act( AT_PLAIN, "$p is too heavy for you to carry with your current inventory.", auction->buyer, auction->item, NULL, TO_CHAR );
    		    act( AT_PLAIN, "$n is carrying too much to also carry $p, and $e drops it.", auction->buyer, auction->item, NULL, TO_ROOM );
		    obj_to_room( auction->item, auction->buyer->in_room );
		}
		else
		    obj_to_char( auction->item, auction->buyer );
		if(auction->item->owner)
		{
			ttax = (int)auction->bet *.5;
            STRFREE( auction->item->owner );
            auction->item->owner = STRALLOC( auction->buyer->name ); 
		}
		else
			ttax = (int)auction->bet *.05;
//	        pay = (int)auction->bet * 0.9;
//		tax = (int)auction->bet * 0.1;
//		boost_economy( auction->seller->in_room->area, tax );
		pay = auction->bet - ttax; //taxed(auction->bet);
//		ttax = auction->bet-taxed(auction->bet);
		tax(auction->seller, auction->bet);
                auction->seller->gold += pay; /* give him the money, tax 10 % */
		ch_printf( auction->seller, "The auctioneer pays you %s gold, charging an auction fee of ",
			num_punct(pay));
		ch_printf( auction->seller, "%s.\n\r", num_punct(ttax));
                auction->item = NULL; /* reset item */
		if ( IS_SET( sysdata.save_flags, SV_AUCTION ) )
		{
		    save_char_obj( auction->buyer );
		    save_char_obj( auction->seller );
		}
            }
            else /* not sold */
            {
                sprintf (buf, "No bids received for %s - removed from auction.\n\r",auction->item->short_descr);
                talk_auction(buf);
                act (AT_ACTION, "The auctioneer appears before you to return $p to you.",
                      auction->seller,auction->item,NULL,TO_CHAR);
                act (AT_ACTION, "The auctioneer appears before $n to return $p to $m.",
                      auction->seller,auction->item,NULL,TO_ROOM);
		if ( (auction->seller->carry_weight
		+     get_obj_weight( auction->item ))
		>     can_carry_w( auction->seller ) )
		{
		    act( AT_PLAIN, "You drop $p as it is just too much to carry"
			" with everything else you're carrying.", auction->seller,
			auction->item, NULL, TO_CHAR );
		    act( AT_PLAIN, "$n drops $p as it is too much extra weight"
			" for $m with everything else.", auction->seller,
			auction->item, NULL, TO_ROOM );
		    obj_to_room( auction->item, auction->seller->in_room );
		}
		else
		{
		    obj_to_char (auction->item,auction->seller);
		}
		if(auction->item->owner)
			ttax = (int)auction->item->cost *.5;
		else
			ttax = (int)auction->item->cost *.05;
//		ttax = (int)auction->item->cost * 0.05;
		boost_economy( auction->seller->in_room->area, ttax );
		sprintf(buf, "The auctioneer charges you an auction fee of %s.\n\r", num_punct(ttax) );
		send_to_char(buf, auction->seller);
		if ((auction->seller->gold - ttax) < 0)
		  auction->seller->gold = 0;
		else
		{
		  auction->seller->gold -= ttax;
		  boost_economy(auction->seller->in_room->area, ttax);
		}
		if ( IS_SET( sysdata.save_flags, SV_AUCTION ) )
		    save_char_obj( auction->seller );
	    } /* else */
	    auction->item = NULL; /* clear auction */
    } /* switch */
} /* func */

void subtract_times(struct timeval *etime, struct timeval *stime)
{
  etime->tv_sec -= stime->tv_sec;
  etime->tv_usec -= stime->tv_usec;
  while ( etime->tv_usec < 0 )
  {
    etime->tv_usec += 1000000;
    etime->tv_sec--;
  }
  return;
}

/*
 * Function to update weather vectors according to climate
 * settings, random effects, and neighboring areas.
 * Last modified: July 18, 1997
 * - Fireblade
 */
void adjust_vectors(WEATHER_DATA *weather)
{
	NEIGHBOR_DATA *neigh;
	double dT, dP, dW;

	if(!weather)
	{
		bug("adjust_vectors: NULL weather data.", 0);
		return;
	}

	dT = 0;
	dP = 0;
	dW = 0;

	/* Add in random effects */
	dT += number_range(-rand_factor, rand_factor);
	dP += number_range(-rand_factor, rand_factor);
	dW += number_range(-rand_factor, rand_factor);
	
	/* Add in climate effects*/
	dT += climate_factor *
		(((weather->climate_temp - 2)*weath_unit) -
		(weather->temp))/weath_unit;
	dP += climate_factor *
		(((weather->climate_precip - 2)*weath_unit) -
		(weather->precip))/weath_unit;
	dW += climate_factor *
		(((weather->climate_wind - 2)*weath_unit) -
		(weather->wind))/weath_unit;
	
		
	/* Add in effects from neighboring areas */
	for(neigh = weather->first_neighbor; neigh;
			neigh = neigh->next)
	{
		/* see if we have the area cache'd already */
		if(!neigh->address)
		{
			/* try and find address for area */
			neigh->address = get_area(neigh->name);
			
			/* if couldn't find area ditch the neigh */
			if(!neigh->address)
			{
				NEIGHBOR_DATA *temp;
				bug("adjust_weather: "
					"invalid area name.", 0);
				temp = neigh->prev;
				UNLINK(neigh,
				       weather->first_neighbor,
				       weather->last_neighbor,
				       next,
				       prev);
				STRFREE(neigh->name);
				DISPOSE(neigh);
				neigh = temp;
				continue;
			}
		}
		
		dT +=(neigh->address->weather->temp -
		      weather->temp) / neigh_factor;
		dP +=(neigh->address->weather->precip -
		      weather->precip) / neigh_factor;
		dW +=(neigh->address->weather->wind -
		      weather->wind) / neigh_factor;
	}
	
	/* now apply the effects to the vectors */
	weather->temp_vector += (int)dT;
	weather->precip_vector += (int)dP;
	weather->wind_vector += (int)dW;

	/* Make sure they are within the right range */
	weather->temp_vector = URANGE(-max_vector,
		weather->temp_vector, max_vector);
	weather->precip_vector = URANGE(-max_vector,
		weather->precip_vector, max_vector);
	weather->wind_vector = URANGE(-max_vector,
		weather->wind_vector, max_vector);
	
	return;
}

/*
 * function updates weather for each area
 * Last Modified: July 31, 1997
 * Fireblade
 */
void weather_update()
{
	AREA_DATA *pArea;
	DESCRIPTOR_DATA *d;
	int limit;
	
	limit = 3 * weath_unit;
	
	for(pArea = first_area; pArea;
		pArea = (pArea == last_area) ? first_build : pArea->next)
	{
		/* Apply vectors to fields */
		pArea->weather->temp +=
			pArea->weather->temp_vector;
		pArea->weather->precip +=
			pArea->weather->precip_vector;
		pArea->weather->wind +=
			pArea->weather->wind_vector;
		
		/* Make sure they are within the proper range */
		pArea->weather->temp = URANGE(-limit,
			pArea->weather->temp, limit);
		pArea->weather->precip = URANGE(-limit,
			pArea->weather->precip, limit);
		pArea->weather->wind = URANGE(-limit,
			pArea->weather->wind, limit);
		
		/* get an appropriate echo for the area */
		get_weather_echo(pArea->weather);
	}

	for(pArea = first_area; pArea;
		pArea = (pArea == last_area) ? first_build : pArea->next)
	{
		adjust_vectors(pArea->weather);
	}
	
	/* display the echo strings to the appropriate players */
	for(d = first_descriptor; d; d = d->next)
	{
		WEATHER_DATA *weath;
		
		if(d->connected == CON_PLAYING &&
			IS_OUTSIDE(d->character) &&
			!NO_WEATHER_SECT(d->character->in_room->sector_type) &&
			IS_AWAKE(d->character))
		{
			weath = d->character->in_room->area->weather;
			if(!weath->echo)
				continue;
			set_char_color(weath->echo_color, d->character);
			ch_printf(d->character, weath->echo);
		}
	}
	
	return;
}

/*
 * get weather echo messages according to area weather...
 * stores echo message in weath_data.... must be called before
 * the vectors are adjusted
 * Last Modified: August 10, 1997
 * Fireblade
 */
void get_weather_echo(WEATHER_DATA *weath)
{
	int n;
	int temp, precip, wind;
	int dT, dP, dW;
	int tindex, pindex, windex;
	
	/* set echo to be nothing */
	weath->echo = NULL;
	weath->echo_color = AT_GREY;
	
	/* get the random number */
	n = number_bits(2);
	
	/* variables for convenience */
	temp = weath->temp;
	precip = weath->precip;
	wind = weath->wind;

	dT = weath->temp_vector;
	dP = weath->precip_vector;
	dW = weath->wind_vector;
	
	tindex = (temp + 3*weath_unit - 1)/weath_unit;
	pindex = (precip + 3*weath_unit - 1)/weath_unit;
	windex = (wind + 3*weath_unit - 1)/weath_unit;
	
	/* get the echo string... mainly based on precip */
	switch(pindex)
	{
		case 0:
			if(precip - dP > -2*weath_unit)
			{
				char *echo_strings[4] =
				{
					"The clouds disappear.\n\r",
					"The clouds disappear.\n\r",
					"The sky begins to break through "
						"the clouds.\n\r",
					"The clouds are slowly "
						"evaporating.\n\r"
				};
				
				weath->echo = echo_strings[n];
				weath->echo_color = AT_WHITE;
			}
			break;

		case 1:
			if(precip - dP <= -2*weath_unit)
			{
				char *echo_strings[4] =
				{
					"The sky is getting cloudy.\n\r",
					"The sky is getting cloudy.\n\r",
					"Light clouds cast a haze over "
						"the sky.\n\r",
					"Billows of clouds spread through "
						"the sky.\n\r"
				};
				weath->echo = echo_strings[n];
				weath->echo_color = AT_GREY;
			}
			break;
			
		case 2:
			if(precip - dP > 0)
			{
				if(tindex > 1)
				{
					char *echo_strings[4] =
					{
						"The rain stops.\n\r",
						"The rain stops.\n\r",
						"The rainstorm tapers "
							"off.\n\r",
						"The rain's intensity "
							"breaks.\n\r"
					};
					weath->echo = echo_strings[n];
					weath->echo_color = AT_CYAN;
				}
				else
				{
					char *echo_strings[4] =
					{
						"The snow stops.\n\r",
						"The snow stops.\n\r",
						"The snow showers taper "
							"off.\n\r",
						"The snow flakes disappear "
							"from the sky.\n\r"
					};
					weath->echo = echo_strings[n];
					weath->echo_color = AT_WHITE;
				}
			}
			break;
			
		case 3:
			if(precip - dP <= 0)
			{
				if(tindex > 1)
				{
					char *echo_strings[4] =
					{
						"It starts to rain.\n\r",
						"It starts to rain.\n\r",
						"A droplet of rain falls "
							"upon you.\n\r",
						"The rain begins to "
							"patter.\n\r"
					};
					weath->echo = echo_strings[n];
					weath->echo_color = AT_CYAN;
				}
				else
				{
					char *echo_strings[4] =
					{
						"It starts to snow.\n\r",
						"It starts to snow.\n\r",
						"Crystal flakes begin to "
							"fall from the "
							"sky.\n\r",
						"Snow flakes drift down "
							"from the clouds.\n\r"
					};
					weath->echo = echo_strings[n];
					weath->echo_color = AT_WHITE;
				}
			}
			else if(tindex < 2 && temp - dT > -weath_unit)
			{
				char *echo_strings[4] =
				{
					"The temperature drops and the rain "
						"becomes a light snow.\n\r",
					"The temperature drops and the rain "
						"becomes a light snow.\n\r",
					"Flurries form as the rain freezes.\n\r",
					"Large snow flakes begin to fall "
						"with the rain.\n\r"
				};
				weath->echo = echo_strings[n];
				weath->echo_color = AT_WHITE;
			}
			else if(tindex > 1 && temp - dT <= -weath_unit)
			{
				char *echo_strings[4] =
				{
					"The snow flurries are gradually "
						"replaced by pockets of rain.\n\r",
					"The snow flurries are gradually "
						"replaced by pockets of rain.\n\r",
					"The falling snow turns to a cold drizzle.\n\r",
					"The snow turns to rain as the air warms.\n\r"
				};
				weath->echo = echo_strings[n];
				weath->echo_color = AT_CYAN;
			} 
			break;
		
		case 4:
			if(precip - dP > 2*weath_unit)
			{
				if(tindex > 1)
				{
					char *echo_strings[4] =
					{
						"The lightning has stopped.\n\r",
						"The lightning has stopped.\n\r",
						"The sky settles, and the "
							"thunder surrenders.\n\r",
						"The lightning bursts fade as "
							"the storm weakens.\n\r"
					};
					weath->echo = echo_strings[n];
					weath->echo_color = AT_GREY;
				}
			}
			else if(tindex < 2 && temp - dT > -weath_unit)
			{
				char *echo_strings[4] =
				{
					"The cold rain turns to snow.\n\r",
					"The cold rain turns to snow.\n\r",
					"Snow flakes begin to fall "
						"amidst the rain.\n\r",
					"The driving rain begins to freeze.\n\r"
				};
				weath->echo = echo_strings[n];
				weath->echo_color = AT_WHITE;
			}
			else if(tindex > 1 && temp - dT <= -weath_unit)
			{
				char *echo_strings[4] =
				{
					"The snow becomes a freezing rain.\n\r",
					"The snow becomes a freezing rain.\n\r",
					"A cold rain beats down on you "
						"as the snow begins to melt.\n\r",
					"The snow is slowly replaced by a heavy "
						"rain.\n\r"
				};
				weath->echo = echo_strings[n];
				weath->echo_color = AT_CYAN;
			}
			break;
			
		case 5:
			if(precip - dP <= 2*weath_unit)
			{
				if(tindex > 1)
				{
					char *echo_strings[4] =
					{
						"Lightning flashes in the "
							"sky.\n\r",
						"Lightning flashes in the "
							"sky.\n\r",
						"A flash of lightning splits "
							"the sky.\n\r",
						"The sky flashes, and the "
							"ground trembles with "
							"thunder.\n\r"
					};
					weath->echo = echo_strings[n];
					weath->echo_color = AT_YELLOW;
				}
			}
			else if(tindex > 1 && temp - dT <= -weath_unit)
			{
				char *echo_strings[4] =
				{
					"The sky rumbles with thunder as "
						"the snow changes to rain.\n\r",
					"The sky rumbles with thunder as "
						"the snow changes to rain.\n\r",
					"The falling turns to freezing rain "
						"amidst flashes of "
						"lightning.\n\r",
					"The falling snow begins to melt as "
						"thunder crashes overhead.\n\r"
				};
				weath->echo = echo_strings[n];
				weath->echo_color = AT_WHITE;
			}
			else if(tindex < 2 && temp - dT > -weath_unit)
			{
				char *echo_strings[4] =
				{
					"The lightning stops as the rainstorm "
						"becomes a blinding "
						"blizzard.\n\r",
					"The lightning stops as the rainstorm "
						"becomes a blinding "
						"blizzard.\n\r",
					"The thunder dies off as the "
						"pounding rain turns to "
						"heavy snow.\n\r",
					"The cold rain turns to snow and "
						"the lightning stops.\n\r"
				};
				weath->echo = echo_strings[n];
				weath->echo_color = AT_CYAN;
			}
			break;
			
		default:
			bug("echo_weather: invalid precip index");
			weath->precip = 0;
			break;
	}

	return;
}

/*
 * get echo messages according to time changes...
 * some echoes depend upon the weather so an echo must be
 * found for each area
 * Last Modified: August 10, 1997
 * Fireblade
 */
void get_time_echo(WEATHER_DATA *weath)
{
	int n;
	int pindex;
	
	n = number_bits(2);
	pindex = (weath->precip + 3*weath_unit - 1)/weath_unit;
	weath->echo = NULL;
	weath->echo_color = AT_GREY;
	
	switch(time_info.hour)
	{
		case 5:
		{
			char *echo_strings[4] =
			{
				"The day has begun.\n\r",
				"The day has begun.\n\r",
				"The sky slowly begins to glow.\n\r",
				"The sun slowly embarks upon a new day.\n\r"
			};
			time_info.sunlight = SUN_RISE;
			weath->echo = echo_strings[n];
			weath->echo_color = AT_YELLOW;
			break;
		}
		case 6:
		{
			char *echo_strings[4] =
			{
				"The sun rises in the east.\n\r",
				"The sun rises in the east.\n\r",
				"The hazy sun rises over the horizon.\n\r",
				"Day breaks as the sun lifts into the sky.\n\r"
			};
			time_info.sunlight = SUN_LIGHT;
			weath->echo = echo_strings[n];
			weath->echo_color = AT_ORANGE;
			break;
		}
		case 12:
		{
			if(pindex > 0)
			{
				weath->echo = "It's noon.\n\r";
			}
			else
			{
				char *echo_strings[2] =
				{
					"The intensity of the sun "
						"heralds the noon hour.\n\r",
					"The sun's bright rays beat down "
						"upon your shoulders.\n\r"
				};
				weath->echo = echo_strings[n%2];
			}
			time_info.sunlight = SUN_LIGHT;
			weath->echo_color = AT_WHITE;
			break;
		}
		case 19:
		{
			char *echo_strings[4] =
			{
				"The sun slowly disappears in the west.\n\r",
				"The reddish sun sets past the horizon.\n\r",
				"The sky turns a reddish orange as the sun "
					"ends its journey.\n\r",
				"The sun's radiance dims as it sinks in the "
					"sky.\n\r"
			};
			time_info.sunlight = SUN_SET;
			weath->echo = echo_strings[n];
			weath->echo_color = AT_RED;
			break;
		}
		case 20:
		{
			if(pindex > 0)
			{
				char *echo_strings[2] =
				{
					"The night begins.\n\r",
					"Twilight descends around you.\n\r"
				};
				weath->echo = echo_strings[n%2];
			}
			else
			{
				char *echo_strings[2] =
				{
					"The moon's gentle glow diffuses "
						"through the night sky.\n\r",
					"The night sky gleams with "
						"glittering starlight.\n\r"
				};
				weath->echo = echo_strings[n%2];
			}
			time_info.sunlight = SUN_DARK;
			weath->echo_color = AT_DBLUE;
			break;
		}
	}
	
	return;
}

/*
 * update the time
 */
void time_update()
{
	AREA_DATA *pArea;
	DESCRIPTOR_DATA *d;
	WEATHER_DATA *weath;
	
	switch(++time_info.hour)
	{
		case 5:
		case 6:
		case 12:
		case 19:
		case 20:
			for(pArea = first_area; pArea;
				pArea = (pArea == last_area) ? first_build : pArea->next)
			{
				get_time_echo(pArea->weather);
			}
			
			for(d = first_descriptor; d; d = d->next)
			{
				if(d->connected == CON_PLAYING &&
					IS_OUTSIDE(d->character) &&
					IS_AWAKE(d->character))
				{
					weath = d->character->in_room->area->weather;
					if(!weath->echo)
						continue;
					set_char_color(weath->echo_color,
						d->character);
					ch_printf(d->character, weath->echo);
				}
			}
			break;
		case 24:
			time_info.hour = 0;
			time_info.day++;
			break;
	}
	
	if(time_info.day >= 30)
	{
		time_info.day = 0;
		time_info.month++;
	}
	
	if(time_info.month >= 17)
	{
		time_info.month = 0;
		time_info.year++;
	}
	
	return;
}

