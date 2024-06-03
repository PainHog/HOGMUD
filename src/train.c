#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "mud.h"

void do_train( CHAR_DATA *ch, char *argument )
{
    char buf[MAX_STRING_LENGTH];
    CHAR_DATA *mob;
    int cost = 0;
    int costqp = 0;
    char *pOutput = "";
    buf[0] = '\0';

    if ( IS_NPC(ch) )
    {
        send_to_char( "Not for NPCs.  Sorry.\n\r", ch );
        return;
    }

    /*
     * Check for trainer.
     */
    for ( mob = ch->in_room->first_person; mob != NULL; mob = mob->next_in_room )
    {
        if ( IS_NPC(mob) && xIS_SET(mob->act, ACT_TRAIN) )
            break;
    }

    if ( !mob  )
    {
        send_to_char( "You can't do that here.\n\r", ch );
        return;
    }

    if ( argument[0] == '\0' || !is_name(argument, "str int wis dex con lck cha hp mana") )
    {
        cost = 10;
        costqp = 2500;
        
        sprintf( buf, "&WYou have &C%d &Wpractice sessions and &c%d &Wquestpoints.&D\n\r", ch->practice, ch->pcdata->quest_curr );
        send_to_char( buf, ch );

        send_to_char( "&WYou can train: &Yhp &w(&C3&w/&c200&w)  &Ymana &w(&C3&w/&c200&w)", ch );

        if ( ch->perm_str < UMAX(18, (18 + race_table[ch->race]->str_plus)) )
            ch_printf( ch, " &Ystr &w(&C%d&w/&c%d&w)", cost, costqp);
        if ( ch->perm_int < UMAX(18, (18 + race_table[ch->race]->int_plus)) )
            ch_printf( ch, " &Yint &w(&C%d&w/&c%d&w)", cost, costqp);
        if ( ch->perm_wis < UMAX(18, (18 + race_table[ch->race]->wis_plus)) )
            ch_printf( ch, " &Ywis &w(&C%d&w/&c%d&w)", cost, costqp);
        if ( ch->perm_dex < UMAX(18, (18 + race_table[ch->race]->dex_plus)) )
            ch_printf( ch, " &Ydex &w(&C%d&w/&c%d&w)", cost, costqp);
        if ( ch->perm_con < UMAX(18, (18 + race_table[ch->race]->con_plus)) )
            ch_printf( ch, " &Ycon &w(&C%d&w/&c%d&w)", cost, costqp);
        if ( ch->perm_lck < UMAX(18, (18 + race_table[ch->race]->lck_plus)) ) 
            ch_printf( ch, " &Ylck &w(&C%d&w/&c%d&w)", cost, costqp);
        if ( ch->perm_cha < UMAX(18, (18 + race_table[ch->race]->cha_plus)) ) 
            ch_printf( ch, " &Ycha &w(&C%d&w/&c%d&w)", cost, costqp);

        send_to_char( "&W.&D\n\r", ch );
  
        return;
    }

    if ( !str_cmp( argument, "str" ) )
    {
        cost    = 10;
        costqp  = 2500;
        pOutput     = "strength";
    }

    else if ( !str_cmp( argument, "int" ) )
    {
        cost    = 10;
        costqp  = 2500;
        pOutput     = "intelligence";
    }

    else if ( !str_cmp( argument, "wis" ) )
    {
        cost    = 10;
        costqp  = 2500;
        pOutput     = "wisdom";
    }

    else if ( !str_cmp( argument, "dex" ) )
    {
        cost    = 10;
        costqp  = 2500;
        pOutput     = "dexterity"; 
    }

    else if ( !str_cmp( argument, "con" ) )
    {
        cost    = 10;
        costqp	= 2500;
        pOutput     = "constitution";
    }

    else if ( !str_cmp( argument, "lck" ) )
    {
        cost    = 10;
        costqp  = 2500;
        pOutput     = "luck";
    }

    else if ( !str_cmp( argument, "cha" ) )
    {   
        cost    = 10;                                          
        costqp  = 2500;
        pOutput     = "charisma";
    }

    else if ( !str_cmp( argument, "hp" ) )
    {
        pOutput = "number of hit points";
        cost = 3;    /* this is pracs per "train hp" */
        costqp = 200;  /* cost in questpoints per "train hp" */
    }

    else if ( !str_cmp( argument, "mana" ) )
    {
        pOutput = "amount of mana";
        cost = 3;
        costqp = 200;
    }

    if(cost && costqp)
    {
        if ( cost > ch->practice )
        {
            send_to_char( "&WYou don't have enough practices.&D\n\r", ch );
            return;
        }

        if ( costqp > ch->pcdata->quest_curr )
        { 
            send_to_char( "&WYou don't have enough quest points.&D\n\r", ch );
            return; 
        }
    }
    
    if ( !str_cmp( argument, "hp" ) )
    {
        ch->practice        -= cost;
        ch->pcdata->quest_curr -= costqp;
        ch->max_hit         += 3;
        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return;
    }

    if ( !str_cmp( argument, "mana" ) )
    {
        ch->practice        -= cost;
        ch->pcdata->quest_curr -= costqp;
        ch->max_mana       += 3;

        act( AT_ACTION, "Your $T increases!", ch, NULL,  pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL,  pOutput, TO_ROOM );
        return;
    }

    if ( !str_cmp( argument, "str" ) )
    {
        if ( ch->perm_str >= UMAX(18, (18 + race_table[ch->race]->str_plus)) )
        {
            act( AT_ACTION, "Your $T is already at maximum.", ch,NULL, pOutput, TO_CHAR );
            return;
        }

        ch->practice        -= cost;
        ch->pcdata->quest_curr -= costqp;
        ch->perm_str       += 1;

        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return;
    }

    if ( !str_cmp( argument, "int" ) )
    {
        if ( ch->perm_int >= UMAX(18, (18 + race_table[ch->race]->int_plus)) )
        {
            act( AT_ACTION, "Your $T is already at maximum.", ch, NULL, pOutput, TO_CHAR );
            return;
        }

        ch->practice        -= cost;
        ch->pcdata->quest_curr -= costqp;
        ch->perm_int       += 1;

        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return;
    }

    if ( !str_cmp( argument, "wis" ) )
    {
        if ( ch->perm_wis >= UMAX(18, (18 + race_table[ch->race]->wis_plus)) )
        {
            act( AT_ACTION, "Your $T is already at maximum.", ch, NULL, pOutput, TO_CHAR );
            return;
        }

        ch->practice        -= cost;
        ch->pcdata->quest_curr -= costqp;
        ch->perm_wis       += 1;

        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return;
    }

    if ( !str_cmp( argument, "dex" ) )
    {
        if ( ch->perm_dex >= UMAX(18, (18 + race_table[ch->race]->dex_plus)) )
        {
            act( AT_ACTION, "Your $T is already at maximum.", ch, NULL, pOutput, TO_CHAR );
            return;
        }

        ch->practice        -= cost;
        ch->pcdata->quest_curr -= costqp;
        ch->perm_dex       += 1;

        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return;
    }

    if ( !str_cmp( argument, "con" ) )
    {
        if ( ch->perm_con >= UMAX(18, (18 + race_table[ch->race]->con_plus)) )
        {
            act( AT_ACTION, "Your $T is already at maximum.", ch, NULL, pOutput, TO_CHAR );
            return;
        }

        ch->practice        -= cost;
        ch->pcdata->quest_curr -= costqp;
        ch->perm_con       += 1;

        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return;
    }

    if ( !str_cmp( argument, "lck" ) )
    { 
        if ( ch->perm_lck >= UMAX(18, (18 + race_table[ch->race]->lck_plus)) )
        {  
            act( AT_ACTION, "Your $T is already at maximum.", ch, NULL, pOutput, TO_CHAR );
            return; 
        }

        ch->practice        -= cost; 
        ch->pcdata->quest_curr -= costqp;
        ch->perm_lck       += 1;            

        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return; 
    }

    if ( !str_cmp( argument, "cha" ) )
    { 
        if ( ch->perm_cha >= UMAX(18, (18 + race_table[ch->race]->cha_plus)) )
        {  
            act( AT_ACTION, "Your $T is already at maximum.", ch, NULL, pOutput, TO_CHAR );
            return; 
        }

        ch->practice        -= cost; 
        ch->pcdata->quest_curr -= costqp;
        ch->perm_cha       += 1;            

        act( AT_ACTION, "Your $T increases!", ch, NULL, pOutput, TO_CHAR );
        act( AT_ACTION, "$n's $T increases!", ch, NULL, pOutput, TO_ROOM );
        return; 
    }
}


