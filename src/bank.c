/****************************************************************************
 *                   ^     +----- |  / ^     ^ |     | +-\                  *
 *                  / \    |      | /  |\   /| |     | |  \                 *
 *                 /   \   +---   |<   | \ / | |     | |  |                 *
 *                /-----\  |      | \  |  v  | |     | |  /                 *
 *               /       \ |      |  \ |     | +-----+ +-/                  *
 ****************************************************************************
 * AFKMud Copyright 1997-2003 by Roger Libiez (Samson),                     *
 * Levi Beckerson (Whir), Michael Ward (Tarl), Erik Wolfe (Dwip),           *
 * Cameron Carroll (Cam), Cyberfox, Karangi, Rathian, Raine, and Adjani.    *
 * All Rights Reserved.                                                     *
 *                                                                          *
 * Original SMAUG 1.4a written by Thoric (Derek Snider) with Altrag,        *
 * Blodkai, Haus, Narn, Scryn, Swordbearer, Tricops, Gorog, Rennard,        *
 * Grishnakh, Fireblade, and Nivek.                                         *
 *                                                                          *
 * Original MERC 2.1 code by Hatchet, Furey, and Kahn.                      *
 *                                                                          *
 * Original DikuMUD code by: Hans Staerfeldt, Katja Nyboe, Tom Madsen,      *
 * Michael Seifert, and Sebastian Hammer.                                   *
 ****************************************************************************
 *                              Bank module                                 *
 ****************************************************************************/

/***************************************************************************  
 *                          SMAUG Banking Support Code                     *
 ***************************************************************************
 *                                                                         *
 * This code may be used freely, as long as credit is given in the help    *
 * file. Thanks.                                                           *
 *                                                                         *
 *                                        -= Minas Ravenblood =-           *
 *                                 Implementor of The Apocalypse Theatre   *
 *                                      (email: krisco7@hotmail.com)       *
 *                                                                         *
 ***************************************************************************/

/* Modifications to original source by Samson */
/* Modified to use Lua for string allocation -Darwin 2008-02-05 */

#include "mud.h"
int load_new_economy(AREA_DATA *tarea);
void save_new_economy(AREA_DATA *tarea);

/* You can add this or just put it in the do_bank code. I don't really know
   why I made a seperate function for this, but I did. If you do add it,
   don't forget to declare it - Minas */
/* Finds banker mobs in a room. Installed by Samson on unknown date */
/* NOTE: Smaug 1.02a Users - Your compiler probably died on this
   function - if so, remove the x in front of IS_SET and recompile */
CHAR_DATA *find_banker( CHAR_DATA *ch )
{
  CHAR_DATA *banker = NULL;
  
  for ( banker = ch->in_room->first_person; banker; banker = banker->next_in_room )
    if ( IS_NPC( banker ) && xIS_SET( banker->act, ACT_BANKER ) )
      break;

  return banker;
}

/* SMAUG Bank Support
 * Coded by Minas Ravenblood for The Apocalypse Theatre
 * (email: krisco7@hotmail.com)
 */
/* Deposit, withdraw, balance and transfer commands */
void do_deposit( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *banker;
    char *arg1, *buf;
    int amount;
  
    if ( !( banker = find_banker( ch ) ) )
    {
        send_to_char( "You're not in a bank!\n\r", ch );
        return;
    }
  
    if ( IS_NPC( ch ) )
    {
        call_va(L_mud, "sprintf", "ss>s", "Sorry, %s, we don't do business with mobs.", ch->short_descr, &buf);
        do_say( banker, buf );
        return;
    }
  
    if ( argument[0] == '\0' )
    {
        do_say( banker, "If you need help, see HELP BANK." );
        return;
    }

    call_va(L_mud, "one_arg", "s>ss", argument, &arg1, &argument);

    if ( arg1 == '\0' )
    {
        call_va(L_mud, "sprintf", "ss>s", "%s How much gold do you wish to deposit?", ch->name, &buf);
        do_tell( banker, buf );
        return;
    }

    if ( str_cmp( arg1, "all" ) && !is_number( arg1 ) )
    {
        call_va(L_mud, "sprintf", "ss>s", "%s How much gold do you wish to deposit?", ch->name, &buf);
        do_tell( banker, buf );
        return;
    }

    if ( !str_cmp( arg1, "all" ) )
        amount = ch->gold;
    else
        amount = atoi( arg1 );

    if ( amount > ch->gold )
    {
        call_va(L_mud, "sprintf", "ss>s", "%s Sorry, but you don't have that much gold to deposit.", ch->name, &buf);
        do_tell( banker, buf );
        return;
    }

    if ( amount <= 0 )
    {
        call_va(L_mud, "sprintf", "ss>s", "%s Oh, I see.. you're a comedian.", ch->name, &buf);
        do_tell( banker, buf );
        return;
    }

    int amount2;
    amount2 = taxed(amount);

    ch->gold		-= amount;
    ch->pcdata->balance += amount2;
    set_char_color( AT_PLAIN, ch );
    ch_printf( ch, "You deposit %d gold.\n\r", amount2 );
    ch_printf( ch, "You were charged %d gold in bank fees.\n\r", amount-amount2);
    tax(ch, amount);

    act(AT_PLAIN, "$n makes a deposit into $s account.\n\r", ch, NULL, NULL, TO_ROOM );
    save_char_obj( ch );
    return;
}

void do_withdraw( CHAR_DATA *ch, char *argument )
{
    CHAR_DATA *banker;
    char *arg1, *buf;
    int amount;

    if ( !( banker = find_banker( ch ) ) )
    {
        send_to_char( "You're not in a bank!\n\r", ch );
        return;
    }

    if ( IS_NPC( ch ) )
    {
        call_va(L_mud, "sprintf", "ss>s", "Sorry, %s, we don't do business with mobs.", ch->short_descr, &buf);
        do_say( banker, buf );
        return;
    }

    if ( argument[0] == '\0' )
    {
        do_say( banker, "If you need help, see HELP BANK." );
        return;
    }

    call_va(L_mud, "one_arg", "s>ss", argument, &arg1, &argument);

    if ( arg1 == '\0' )
    {
        call_va(L_mud, "sprintf", "ss>s", "%s How much gold do you wish to withdraw?", ch->name, &buf );
        do_tell( banker, buf );
        return;
    }
    if ( str_cmp( arg1, "all" ) && !is_number( arg1 ) )
    { 
        call_va(L_mud, "sprintf", "ss>s", "%s How much gold do you wish to withdraw?", ch->name, &buf );
        do_tell( banker, buf );
        return;
    }

    if ( !str_cmp( arg1, "all" ) )
        amount = ch->pcdata->balance;
    else
        amount = atoi( arg1 );

    if( amount > ch->pcdata->balance )
    {
        call_va(L_mud, "sprintf", "ss>s", "%s But you do not have that much gold in your account!", ch->name, &buf );
        do_tell( banker, buf );
        return;
    }

    if ( amount <= 0 )
    {
        call_va(L_mud, "sprintf", "ss>s", "%s Oh I see.. you're a comedian.", ch->name, &buf );
        do_tell( banker, buf );
        return;
    }

    ch->pcdata->balance -= amount;
    ch->gold += amount;
    set_char_color( AT_PLAIN, ch );
    ch_printf( ch, "You withdraw %d gold.\n\r", amount );
    act( AT_PLAIN, "$n withdraws some gold from $s account.\n\r", ch, NULL, NULL, TO_ROOM );
    save_char_obj( ch );
    return;
}

void do_balance( CHAR_DATA *ch, char *argument )
{
   CHAR_DATA *banker;
   char *buf;

   if ( !( banker = find_banker( ch ) ) )
   {
      send_to_char( "You're not in a bank!\n\r", ch );
      return;
   }
    
   if ( IS_NPC( ch ) )
   {
      call_va(L_mud, "sprintf", "ss>s", "Sorry, %s, we don't do business with mobs.", ch->short_descr, &buf );
      do_say( banker, buf );
      return;
   }

   ch_printf( ch, "You have %d gold in the bank.\n\r", ch->pcdata->balance  );
   return;
}
/* End of new bank support */
int taxed(int amount)
{
	return (int)(amount - (amount * 0.05));
}

void tax(CHAR_DATA *ch, int amount)
{
    if(ch && ch->in_room)
        boost_economy(ch->in_room->area, amount-taxed(amount));
    return;
}
/* These next 2 functions are for loading and saving area economy
 * stats into the ../economy/ directory set in mud.h as ECONOMY_DIR.
 * These keep gold inflation down so that gold has value to players
 * instead of just being able to get it freely for practically nothing
 * The information is saved in files that have the same name as the
 * area file name. This makes it easy to figure out what area has what
 * for an economy. -Darwin
 */
int load_new_economy(AREA_DATA *tarea)
{
    //~ char *strsave;
	char strsave[MAX_STRING_LENGTH];
    FILE *fp;
	int newecon = 0;

	log_string("Loading new economy");
    //~ call_va(L_mud, "sprintf", "sss>s", "%s%s", ECONOMY_DIR, capitalize(tarea->filename), &strsave);
	sprintf(strsave, "%s%s", ECONOMY_DIR, capitalize(tarea->filename));
    if ( ( fp = fopen( strsave, "r" ) ) != NULL )
	{
		newecon = fread_number(fp);
	}
	else 
	{
		newecon = 250000000;
		log_string("Loading new economy failed.");
	}

	if(fp) fclose(fp);
	if(newecon < 1000) newecon = 1000000; // create some new money for low economies -Darwin

	return (int)newecon+newecon*.05;
}

void save_new_economy(AREA_DATA *tarea)
{
    FILE *fp = NULL;
    //~ char *strsave;
	char strsave[MAX_STRING_LENGTH];

    //~ call_va(L_mud, "sprintf", "sss>s", "%s%s", ECONOMY_DIR, capitalize(tarea->filename), &strsave);
	sprintf(strsave, "%s%s", ECONOMY_DIR, capitalize(tarea->filename));
    if ( ( fp = fopen( strsave, "wb+" ) ) != NULL )
    {
		fprintf(fp, "%d", tarea->low_economy);
	}
	else log_string("Save new economy failed.");

	if(fp) fclose(fp);
}
