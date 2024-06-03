/****************************************************************************
 * This is an automated questmaster snippet. Its based off the concept of   *
 * the questmaster snippet found all over the place. As such the credits are*
 * a completely disgusting tangle.                                          *
 * The nearest semblence of ownership I can determine is this comes from ROM*
 * was created by Vassago for the mud Moongate, then Vir ported it from ROM *
 * to SMAUG, then LrdElder allegedly edited it and released it for smaug 1.4*
 *                                                                          *
 * Regardless of how it got there, the one floating about is pretty crappy  *
 * And has tons of bugs in it, and since I'm sick of hearing questions about*
 * ways to fix it, therefore I've rewritten it in my own way to make it more*
 * compatible, and quite frankly workable.                                  *
 *                                                                          *
 * I myself add no terms or conditions to this code, simply because I don't *
 * care. If you're going to steal it, you will whether I tell you you can or*
 * not, likewise if you wish to do something special like mention me or the *
 * other authors or whatever, somewhere, this is also entirely up to you,   *
 * and not something I can force you to do, etc.                            *
 *                                                                          *
 * Whether or not you follow the license of the previous ways this snippet  *
 * has been affected is also up to you. Because this is entirely rewritten, *
 * I have no idea whether or not you're bound by the licenses of the first  *
 * version that exists since you're not actually using it, but as far as I  *
 * am aware, you are not constrained in any way by those licenses since this*
 * work is not a derivitive of that, nor a copy of it, merely something that*
 * was inspired by it (Aka I looked at it and said "It'd work much better if*
 * if it were like this", and so wrote my own this way learning from the    *
 * quite hideous mistakes in the other).                                    *
 *                                                                          *
 * The installation instructions are within the readme.txt, this also will  *
 * detail what the functions are, and do, as well as some other practical   *
 * usages for them. The license.txt includes the headers/licenses from the  *
 * inspirational work for those who are interested or concerned.            *
 *                                                                          *
 *                                         -Aurora                          *
 *                                          EternalEmpress@Lostprophecy.com *
 ****************************************************************************/


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mud.h"

/* Object vnums for Quest Rewards */

#define QUEST_ITEM0 29800
#define QUEST_ITEM1 29801 
#define QUEST_ITEM2 29802  
#define QUEST_ITEM3 29803  
#define QUEST_ITEM4 29804 
#define QUEST_ITEM5 29805
#define QUEST_ITEM6 29806
#define QUEST_ITEM7 29807
#define QUEST_ITEM8 29808
#define QUEST_ITEM9 29809 
#define QUEST_ITEM10 29810
#define QUEST_ITEM11 29811
#define QUEST_ITEM12 29812
#define QUEST_ITEM13 29813
#define QUEST_ITEM14 29814
#define QUEST_ITEM15 29815
#define QUEST_ITEM16 29816
#define QUEST_ITEM17 29817
#define QUEST_ITEM18 29818
#define QUEST_ITEM19 29819
#define QUEST_ITEM20 29820
#define QUEST_ITEM21 29821
#define QUEST_ITEM22 29822
#define QUEST_ITEM23 29823
#define QUEST_ITEM24 29824
#define QUEST_ITEM25 29825
#define QUEST_ITEM26 29826
#define QUEST_ITEM27 29827
#define QUEST_ITEM28 29828
#define QUEST_ITEM29 29829
#define QUEST_ITEM30 29830
#define QUEST_ITEM31 29831
#define QUEST_ITEM32 29832
#define QUEST_ITEM33 29833
#define QUEST_ITEM34 29834
#define QUEST_ITEM35 29835
#define QUEST_ITEM36 29836
#define QUEST_ITEM37 29837
#define QUEST_ITEM38 29838
#define QUEST_ITEM39 29839
#define QUEST_ITEM40 29840
#define QUEST_ITEM41 29841
#define QUEST_ITEM42 29842
#define QUEST_ITEM43 29843
#define QUEST_ITEM44 29844
#define QUEST_ITEM45 29845
#define QUEST_ITEM46 29846
#define QUEST_ITEM47 29847
#define QUEST_ITEM48 29848
#define QUEST_ITEM49 29849


/* Prices for each Quest Reward, in glory */

#define QUEST_VALUE0 9900
#define QUEST_VALUE1 9900 
#define QUEST_VALUE2 9600 
#define QUEST_VALUE3 10100 
#define QUEST_VALUE4 11475 
#define QUEST_VALUE5 10725 
#define QUEST_VALUE6 10600 
#define QUEST_VALUE7 10350 
#define QUEST_VALUE8 7500 
#define QUEST_VALUE9 5000 
#define QUEST_VALUE10 10000 
#define QUEST_VALUE11 6250 
#define QUEST_VALUE12 5700 
#define QUEST_VALUE13 5300 
#define QUEST_VALUE14 12375 
#define QUEST_VALUE15 6000 
#define QUEST_VALUE16 6800 
#define QUEST_VALUE17 8100 
#define QUEST_VALUE18 9000 
#define QUEST_VALUE19 5550 
#define QUEST_VALUE20 4750 
#define QUEST_VALUE21 8250 
#define QUEST_VALUE22 6750 
#define QUEST_VALUE23 7125 
#define QUEST_VALUE24 12000 
#define QUEST_VALUE25 7400 
#define QUEST_VALUE26 10750 
#define QUEST_VALUE27 7550 
#define QUEST_VALUE28 6250 
#define QUEST_VALUE29 6500 
#define QUEST_VALUE30 5000 
#define QUEST_VALUE31 4625 
#define QUEST_VALUE32 4500 
#define QUEST_VALUE33 9500 
#define QUEST_VALUE34 6250 
#define QUEST_VALUE35 5750 
#define QUEST_VALUE36 4250 
#define QUEST_VALUE37 5500 
#define QUEST_VALUE38 7800 
#define QUEST_VALUE39 8750 
#define QUEST_VALUE40 6050 
#define QUEST_VALUE41 8625 
#define QUEST_VALUE42 4000 
#define QUEST_VALUE43 5525 
#define QUEST_VALUE44 5700
#define QUEST_VALUE45 8000
#define QUEST_VALUE46 5125
#define QUEST_VALUE47 6500
#define QUEST_VALUE48 750
#define QUEST_VALUE49 750

 /* Local functions */

void generate_quest	args(( CHAR_DATA *ch, CHAR_DATA *questman ));
void quest_update	args(( void ));
bool qchance            args(( int num ));
CHAR_DATA *find_quest_mob args(( CHAR_DATA *ch));
OBJ_DATA *find_quest_obj  args(( CHAR_DATA *ch));
void quest_list           args((CHAR_DATA *ch));
void quest_buy            args((CHAR_DATA *questman, CHAR_DATA *ch, sh_int number));

bool qchance( int num )
{

 if ( number_range(1,100) <= num)
      return TRUE;
 else
      return FALSE;
}

/* The main quest function */

void do_aquest(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *questman;
    OBJ_DATA *obj=NULL, *obj_next;
    OBJ_INDEX_DATA *obj0, *obj1, *obj2, *obj3, *obj4, *obj5, *obj6, *obj7, *obj8, *obj9, *obj10, *obj11,
		*obj12, *obj13, *obj14, *obj15, *obj16, *obj17, *obj18, *obj19, *obj20, *obj21,
		*obj22, *obj23, *obj24, *obj25, *obj26, *obj27, *obj28, *obj29, *obj30, *obj31,
		*obj32, *obj33, *obj34, *obj35, *obj36, *obj37, *obj38, *obj39, *obj40, *obj41,
		*obj42, *obj43, *obj44, *obj45, *obj46, *obj47, *obj48, *obj49;
    OBJ_INDEX_DATA *questinfoobj;
    MOB_INDEX_DATA *questinfo;
    char buf [MAX_STRING_LENGTH];
    char arg1 [MAX_INPUT_LENGTH];
    char arg2 [MAX_INPUT_LENGTH];

    int spentpracs;
    int boughtqps;

    if (IS_NPC(ch)) return;

    argument = one_argument(argument, arg1);
    argument = one_argument(argument, arg2);

    if (!strcmp(arg1, "info"))
    {
		if (xIS_SET(ch->act, PLR_QUESTOR))
		{
			if (ch->pcdata->questmob == -1 && ch->pcdata->questgiver != 0)
				ch_printf(ch, "&CYour quest is ALMOST complete!\n\rGet back to the questmaster before your time runs out!&w\n\r");
			else if (ch->pcdata->questobj > 0)
			{
				questinfoobj = get_obj_index(ch->pcdata->questobj);
				if (questinfoobj != NULL)
					ch_printf(ch, "&CYou are on a quest to recover %s from %s in %s.&w\n\r",questinfoobj->short_descr, ch->pcdata->questroom, ch->pcdata->questarea);
				else 
					send_to_char("&CYou aren't currently on a quest.&w\n\r",ch);
				return;
			}
			else if (ch->pcdata->questmob > 0)
			{
				questinfo = get_mob_index(ch->pcdata->questmob);
				if (questinfo != NULL)
						ch_printf(ch, "&CYou are on a quest to slay %s in %s in the area of %s.&w\n\r",questinfo->short_descr, ch->pcdata->questroom, ch->pcdata->questarea);
				else 
					send_to_char("&CYou aren't currently on a quest.&w\n\r",ch);
				return;
			}
		}
		else
			send_to_char("&CYou aren't currently on a quest.&w\n\r",ch);
		return;
    }
    if (!strcmp(arg1, "points"))
    {
		ch_printf(ch, "&CYou have &W%d &Cglory.&w\n\r",ch->pcdata->quest_curr);
		return;
    }
    else if (!strcmp(arg1, "time"))
    {
		if (!xIS_SET(ch->act, PLR_QUESTOR))
		{
			send_to_char("&CYou aren't currently on a quest.&w\n\r",ch);
			if (ch->pcdata->nextquest > 1)
				ch_printf(ch, "&CThere are &Y%d &Cminutes remaining until you can go on another quest.&w\n\r",ch->pcdata->nextquest);
			else if (ch->pcdata->nextquest == 1)
				ch_printf(ch, "&CThere is less than a minute remaining until you can go on another quest.&w\n\r");
		}
		else if (ch->pcdata->countdown > 0)
			ch_printf(ch, "&CTime left for current quest: &W%d&w\n\r",ch->pcdata->countdown);
		return;
    }

/* Check for questmaster in room. */

    for ( questman = ch->in_room->first_person; questman != NULL; questman = questman->next_in_room )
		if (IS_NPC(questman) && xIS_SET(questman->act, ACT_QUESTMASTER))
			break;

    if (!questman)
    {
        send_to_char("&CYou can't do that here.&w\n\r",ch);
        return;
    }

    if ( questman->fighting)
    {
		send_to_char("&CWait until the fighting stops.&w\n\r",ch);
        return;
    }

    ch->pcdata->questgiver = questman->pIndexData->vnum;

    obj0 = get_obj_index(QUEST_ITEM0);
    obj1 = get_obj_index(QUEST_ITEM1);
    obj2 = get_obj_index(QUEST_ITEM2);
    obj3 = get_obj_index(QUEST_ITEM3);
    obj4 = get_obj_index(QUEST_ITEM4);
    obj5 = get_obj_index(QUEST_ITEM5);
    obj6 = get_obj_index(QUEST_ITEM6);
    obj7 = get_obj_index(QUEST_ITEM7);
    obj8 = get_obj_index(QUEST_ITEM8);
    obj9 = get_obj_index(QUEST_ITEM9);
    obj10 = get_obj_index(QUEST_ITEM10);
    obj11 = get_obj_index(QUEST_ITEM11);
    obj12 = get_obj_index(QUEST_ITEM12);
    obj13 = get_obj_index(QUEST_ITEM13);
    obj14 = get_obj_index(QUEST_ITEM14);
    obj15 = get_obj_index(QUEST_ITEM15);
    obj16 = get_obj_index(QUEST_ITEM16);
    obj17 = get_obj_index(QUEST_ITEM17);
    obj18 = get_obj_index(QUEST_ITEM18);
    obj19 = get_obj_index(QUEST_ITEM19);
    obj20 = get_obj_index(QUEST_ITEM20);
    obj21 = get_obj_index(QUEST_ITEM21);
    obj22 = get_obj_index(QUEST_ITEM22);
    obj23 = get_obj_index(QUEST_ITEM23);
    obj24 = get_obj_index(QUEST_ITEM24);
    obj25 = get_obj_index(QUEST_ITEM25);
    obj26 = get_obj_index(QUEST_ITEM26);
    obj27 = get_obj_index(QUEST_ITEM27);
    obj28 = get_obj_index(QUEST_ITEM28);
    obj29 = get_obj_index(QUEST_ITEM29);
    obj30 = get_obj_index(QUEST_ITEM30);
    obj31 = get_obj_index(QUEST_ITEM31);
    obj32 = get_obj_index(QUEST_ITEM32);
    obj33 = get_obj_index(QUEST_ITEM33);
    obj34 = get_obj_index(QUEST_ITEM34);
    obj35 = get_obj_index(QUEST_ITEM35);
    obj36 = get_obj_index(QUEST_ITEM36);
    obj37 = get_obj_index(QUEST_ITEM37);
    obj38 = get_obj_index(QUEST_ITEM38);
    obj39 = get_obj_index(QUEST_ITEM39);
    obj40 = get_obj_index(QUEST_ITEM40);
    obj41 = get_obj_index(QUEST_ITEM41);
    obj42 = get_obj_index(QUEST_ITEM42);   
    obj43 = get_obj_index(QUEST_ITEM43);   
    obj44 = get_obj_index(QUEST_ITEM44);   
    obj45 = get_obj_index(QUEST_ITEM45);   
    obj46 = get_obj_index(QUEST_ITEM46);   
    obj47 = get_obj_index(QUEST_ITEM47);   
    obj48 = get_obj_index(QUEST_ITEM48);   
    obj49 = get_obj_index(QUEST_ITEM49);   


    if ( !obj0 || !obj1 || !obj2 || !obj3 || !obj4 || !obj5 || !obj6 || !obj7 || !obj8 || !obj9 || !obj10 || !obj11 || !obj12 ||
	 !obj13 || !obj14 || !obj15 || !obj16 || !obj17 || !obj18 || !obj19 || !obj20 || !obj21 || !obj22 || !obj23 || !obj24 ||
	 !obj25 || !obj26 || !obj27 || !obj28 || !obj29 || !obj30 || !obj31 || !obj32 || !obj33 || !obj34 || !obj35 || !obj36 ||
	 !obj37 || !obj38 || !obj39 || !obj40 || !obj41 || !obj42 || !obj43 || !obj44 || !obj45 || !obj46 || !obj47 || !obj48 ||
	 !obj49 )
    {
		bug("Error loading quest objects. Char: ", ch->name);
		return;
    }

    if (!strcmp(arg1, "list"))
    {
        act(AT_PLAIN,"$n asks $N for a list of quest items.",ch,NULL,questman,TO_ROOM);
		act(AT_PLAIN,"You ask $N for a list of quest items.",ch,NULL,questman,TO_CHAR);
        quest_list(ch);
		return;
    }
    else if (!strcmp(arg1, "buy"))
    {
		if (arg2[0] == '\0')
		{
			send_to_char("&CTo buy an item, type '&WAQUEST BUY <item #>&C'.&w\n\r",ch);
			return;
		}
        quest_buy(questman, ch, atoi(arg2));
		return;
    }
    else if (!strcmp(arg1, "pracs"))
    {
		if (arg2[0] == '\0')
		{
			send_to_char("&CYou can buy 15 quest points for 1 practice...how many do you wish to spend?&w\n\r",ch);
			return;
		}
		spentpracs = atoi(arg2);
		if (spentpracs > ch->practice)
		{
			send_to_char("&CYou don't have that many practice points to spend!&w\n\r",ch);
			return;
		}
		if (spentpracs < 1)
		{
			send_to_char("&CSorry, you have to actually spend practices.&w\n\r",ch);
			return;
		}
		else
		{
			boughtqps = (spentpracs * 15);
			ch_printf(ch, "&COK, you traded &W%d &Cpractices for &W%d &Cquest points.&w", spentpracs, boughtqps);   
			ch->practice -= spentpracs;
			ch->pcdata->quest_curr += boughtqps;
			ch->pcdata->quest_accum += boughtqps;
			return;
		}
    }
    else if (!strcmp(arg1, "request"))
    {
        act(AT_PLAIN,"$n asks $N for a quest.", ch, NULL, questman, TO_ROOM);
		act(AT_PLAIN,"You ask $N for a quest.",ch, NULL, questman, TO_CHAR);
        if (sysdata.DENY_NEW_PLAYERS == TRUE)
		{
            ch_printf(ch, "&CI'm sorry. Please come back after the reboot. I can't give you a quest until then.&w\n\r");
			return;
		}
        if (xIS_SET(ch->act, PLR_QUESTOR) || xIS_SET(ch->act, PLR_SQUESTOR) || xIS_SET(ch->act, PLR_MQUESTOR))
		{
			ch_printf(ch, "&CBut you're already on a quest!\n\rBetter hurry up and finish it!&w\n\r");
			return;
		}
		if (ch->pcdata->nextquest > 0)
		{
			ch_printf(ch, "&CYou're very brave, %s, but you must wait before you can quest again.&w\n\r",ch->name);
			ch_printf(ch, "&CPlease come back in about &W%d &Cminutes.&w\n\r", ch->pcdata->nextquest);
			return;
		}

		ch_printf(ch, "&CVery well %s...&w\n\r",ch->name);

		generate_quest(ch, questman);

		if (ch->pcdata->questmob > 0 || ch->pcdata->questobj > 0)
		{
			ch->pcdata->countdown = number_range(15,45);
			xSET_BIT(ch->act, PLR_QUESTOR);
			ch_printf(ch, "&CYou have &W%d &Cminutes to complete this quest.&w\n\r",ch->pcdata->countdown);
			ch_printf(ch, "&CMay the gods go with you!&w\n\r");
		}
		return;
    }
    else if (!strcmp(arg1, "refuse"))
    {
        act(AT_PLAIN,"$n informs $N $e has refused $s quest.", ch, NULL, questman, TO_ROOM);
        act(AT_PLAIN,"You inform $N you have refused the quest.",ch, NULL, questman, TO_CHAR);
		if (ch->pcdata->questgiver != questman->pIndexData->vnum)
		{
			ch_printf(ch, "&CI never sent you on a quest! Perhaps you're thinking of someone else.&w\n\r");
			return;
		}
        if (!xIS_SET(ch->act, PLR_QUESTOR))
		{
			ch->pcdata->questgiver = 0;
			ch->pcdata->countdown = 0;
			ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
			ch_printf(ch, "&CYou should at least &WREQUEST &Ca quest before you refuse it!&w\n\r");

	        return;
	    }

        if (xIS_SET(ch->act, PLR_QUESTOR))
		{
			xREMOVE_BIT(ch->act, PLR_QUESTOR);
	        ch->pcdata->questgiver = 0;
	        ch->pcdata->countdown = 0;
	        ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch))
				ch->pcdata->nextquest = 0;
			else
				ch->pcdata->nextquest = 10;
	        ch_printf(ch, "&CAlright fine, I'll put it back in the heap for someone else.&w\n\r");
			ch_printf(ch, "&CYou can come back in about &W%d &Cminutes.&w\n\r", ch->pcdata->nextquest);

	        return;
	    }
    }
    else if (!strcmp(arg1, "complete"))
    {
        act(AT_PLAIN,"$n informs $N $e has completed $s quest.", ch, NULL, questman, TO_ROOM);
        act(AT_PLAIN,"You inform $N you have completed $s quest.",ch, NULL,	questman, TO_CHAR);
		if (ch->pcdata->questgiver != questman->pIndexData->vnum)
		{
			ch_printf(ch, "&CI never sent you on a quest! Perhaps you're thinking of someone else.&w\n\r");
			return;
		}
		if (xIS_SET(ch->act, PLR_QUESTOR))
		{
			if (ch->pcdata->questmob == -1 && ch->pcdata->countdown > 0)
			{
				int reward, pointreward, pracreward, expreward;
				reward = number_range(1000,5000);
				pointreward = number_range(35,110);
				expreward = number_range(250,500);

				ch_printf(ch, "&CCongratulations on completing your quest!&w\n\r");
				ch_printf(ch,"&CAs a reward, I am giving you &W%d glory&C, &Y%d gold&C and &P%d experience points&C!&w\n\r",
				pointreward,reward,expreward);
				if (number_range(1,100) <= 25)
				{
					pracreward = number_range(1,3);
					ch_printf(ch, "&CYou gain &W%d practice%s&C!&w\n\r",pracreward, pracreward > 1 ? "s" : "");
					ch->practice += pracreward;
				}
				if ( ch->pcdata->questmobold != NULL ) 
				   sprintf(buf, "[INFO] %s has completed a quest to slay %s!", ch->name, ch->pcdata->questmobold);
				else 
				   sprintf(buf, "[INFO] %s has completed a quest to slay a creature!", ch->name);
				echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL );  //Yzek 

				xREMOVE_BIT(ch->act, PLR_QUESTOR);
				ch->pcdata->questgiver = 0;
				ch->pcdata->countdown = 0;
				ch->pcdata->questmob = 0;
				ch->pcdata->questmobold = NULL;
				ch->pcdata->questobj = 0;
				if(IS_IMMORTAL(ch)) 
				   ch->pcdata->nextquest = 0; 
				else
				   ch->pcdata->nextquest = 5;
				ch->gold += reward;
				gain_exp( ch, expreward );
				ch->pcdata->quest_curr += pointreward;
				ch->pcdata->quest_accum += pointreward;

				return;
			}
			else if (ch->pcdata->questobj > 0 && ch->pcdata->countdown > 0)
			{
				bool obj_found = FALSE;

				for (obj = ch->first_carrying; obj != NULL; obj=obj_next)
				{
					obj_next = obj->next_content;

					if (obj != NULL && obj->pIndexData->vnum == ch->pcdata->questobj && obj->wear_loc == WEAR_NONE)
					{
						obj_found = TRUE;
						break;
					}
				}
				if (obj_found == TRUE)
				{
					int reward, pointreward, pracreward, expreward;

					reward = number_range(1000,5000);
					pointreward = number_range(35,110);
					expreward = number_range(250,500);

					act(AT_PLAIN,"You hand $p to $N.",ch, obj, questman, TO_CHAR);
					act(AT_PLAIN,"$n hands $p to $N.",ch, obj, questman, TO_ROOM);
					
					ch_printf(ch, "&CCongratulations on completing your quest!&w\n\r");
					ch_printf(ch,"&CAs a reward, I am giving you &W%d glory&C, &Y%d gold&C and &P%d experience points&C!&w\n\r", pointreward,reward,expreward);   
					if (number_range(1,100) <= 25)
					{
						pracreward = number_range(1,3);
						ch_printf(ch, "&CYou gain &W%d practices&C!&w\n\r",pracreward);
						ch->practice += pracreward;
					}

					if ( ch->pcdata->questobj > 0 )
					{ 
					   questinfoobj = get_obj_index(ch->pcdata->questobj);
					   sprintf(buf, "[INFO] %s has completed a quest to find %s!", ch->name, questinfoobj->short_descr);
					} 
					else
					   sprintf(buf, "[INFO] %s has completed a quest to find an item!", ch->name);
	 
					echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL );  //Yzek 

					xREMOVE_BIT(ch->act, PLR_QUESTOR);
					ch->pcdata->questgiver = 0;
					ch->pcdata->countdown = 0;
					ch->pcdata->questmob = 0;
					ch->pcdata->questmobold = NULL;
					ch->pcdata->questobj = 0;
					if(IS_IMMORTAL(ch)) 
					   ch->pcdata->nextquest = 0; 
					else
					   ch->pcdata->nextquest = 5;
					ch->gold += reward;
					gain_exp( ch, expreward );
					ch->pcdata->quest_curr += pointreward;
					ch->pcdata->quest_accum += pointreward;

					extract_obj(obj);
					return;
				}
				else
				{
					ch_printf(ch, "&CYou haven't completed the quest yet, but there is still time!&w\n\r");
					return;
				}
				return;
			}
			else if ((ch->pcdata->questmob > 0 || ch->pcdata->questobj > 0) && ch->pcdata->countdown > 0)
			{
				ch_printf(ch, "&CYou haven't completed the quest yet, but there is still time!&w\n\r");
				return;
			}
		}
		if (ch->pcdata->nextquest > 0)
			ch_printf(ch,"&CBut you didn't complete your quest in time!&w\n\r");
		else 
			ch_printf(ch, "&CYou have to &WREQUEST &Ca quest first, %s.&w\n\r",ch->name);
		return;
    }

    send_to_char("AQUEST commands: POINTS INFO TIME REQUEST REFUSE COMPLETE LIST BUY PRACS.\n\r",ch);
    send_to_char("For more information, type 'HELP AQUEST'.\n\r",ch);
    return;
}

/* Buy enhancemenets with quest points - (c) Gareth */
void do_qpbuy( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
	char arg3[MAX_INPUT_LENGTH];
	char buf[MAX_STRING_LENGTH];
    OBJ_DATA *obj;
    argument = one_argument( argument, arg );
    CHAR_DATA *questman;

/* Check for questmaster in room. */   
     
    for ( questman = ch->in_room->first_person; questman != NULL; questman = questman->next_in_room )
        if (IS_NPC(questman) && xIS_SET(questman->act, ACT_QUESTMASTER))
			break; 
     
    if (!questman) 
    { 
        send_to_char("You can't do that here.\n\r",ch);
        return; 
    } 
     
    if ( questman->fighting) 
    { 
        send_to_char("Wait until the fighting stops.\n\r",ch);
        return; 
    } 
     
    ch->pcdata->questgiver = questman->pIndexData->vnum; 

    if ( IS_NPC(ch) )
        return;

    if ( !IS_AWAKE(ch) )
    {
        send_to_char( "In your dreams, or what?\n\r", ch );
        return;
    }

    if ( arg[0] == '\0' )
    {
        send_to_char( "&WEnhance what?&D\n\r", ch );
		send_to_char( "&WAvailable enhancements: noburn, hum, glow, keyword&D\n\r", ch);
		send_to_char( "&WSee &CHELP QPBUY&W for more information.\n\r", ch);
        return;
    }

    if ( !str_cmp( arg, "noburn" ) )
    { 
        if( ch->pcdata->quest_curr < NOBURN_COST )
        { 
            send_to_char( "You don't have the questpoints.\n\r",ch );
            return;
        } 
        argument = one_argument( argument, arg2 );
         
        if ( arg2[0] == '\0' )
        { 
          send_to_char( "Make what item noburn?\n\r", ch );
          return;
        }
         
        if ( !( obj = get_obj_carry( ch, arg2 ) ) )
        { 
           send_to_char( "That item is not in your inventory.\n\r", ch );
           return;
        } 
        
        if ( obj->item_type != ITEM_CONTAINER )
        {
		   send_to_char( "Setting noburn on an item that isn't a container is useless.\n\r", ch );
		   return;
		}
             
        if ( IS_OBJ_STAT( obj, ITEM_NOBURN ) ) 
        {
            send_to_char( "That item is already marked noburn.\n\r", ch ); 
            return;
        } 
         
        ch->pcdata->quest_curr -= NOBURN_COST;
        separate_obj( obj );  
        xSET_BIT( obj->extra_flags, ITEM_NOBURN );
           
        send_to_char( "Your item is now protected from burning up!\n\r", ch );
        return;
    } 

    if ( !str_cmp( arg, "hum" ) )
    {
        if( ch->pcdata->quest_curr < HUM_COST )
        {
            send_to_char( "You don't have the questpoints.\n\r",ch );
            return;
        }
        argument = one_argument( argument, arg2 );

        if ( arg2[0] == '\0' )
        {
          send_to_char( "Make what item hum?\n\r", ch );
          return;
        }

        if ( !( obj = get_obj_carry( ch, arg2 ) ) )
        {
           send_to_char( "That item is not in your inventory.\n\r", ch );
           return;
        }

		if ( IS_OBJ_STAT( obj, ITEM_HUM ) )
		{
			send_to_char( "That item is already humming.\n\r", ch );
			return;
		}
 
        ch->pcdata->quest_curr -= HUM_COST;
		separate_obj( obj );
        xSET_BIT( obj->extra_flags, ITEM_HUM );

        send_to_char( "Your item begins to hum softly.\n\r", ch );
        return;
    }
 
    if ( !str_cmp( arg, "glow" ) )
    {
        if( ch->pcdata->quest_curr < GLOW_COST )
        {
            send_to_char( "You don't have the questpoints.\n\r",ch );
            return;
        }
        argument = one_argument( argument, arg2 );

        if ( arg2[0] == '\0' )
        {
          send_to_char( "Make what item glow?\n\r", ch );
          return;
        }

        if ( !( obj = get_obj_carry( ch, arg2 ) ) )
        {
           send_to_char( "That item is not in your inventory.\n\r", ch );
           return;
        }

		if ( IS_OBJ_STAT( obj, ITEM_GLOW ) )
		{
			send_to_char( "That item is already glowing.\n\r", ch );
			return;
		}
 
        ch->pcdata->quest_curr -= GLOW_COST;
		separate_obj( obj );
        xSET_BIT( obj->extra_flags, ITEM_GLOW );

        send_to_char( "Your item begins to glow.\n\r", ch );
        return;
    }

    if ( !str_cmp( arg, "keyword" ) )
    {

        if( ch->pcdata->quest_curr < NAME_COST )
        {
            send_to_char( "You don't have the questpoints.\n\r",ch );
            return;
        }
        argument = one_argument( argument, arg2 );
		argument = one_argument( argument, arg3 );

        if ( arg2[0] == '\0' )
        {
          send_to_char( "Add keyword to what item?\n\r", ch );
          return;
        }

        if ( !( obj = get_obj_carry( ch, arg2 ) ) )
        {
           send_to_char( "That item is not in your inventory.\n\r", ch );
           return;
        }

		if ( nifty_is_name( arg3, obj->name ) )
		{
			send_to_char( "That item already has that keyword.\n\r", ch );
			return;
		}
 
        ch->pcdata->quest_curr -= NAME_COST;
		separate_obj( obj );
		sprintf( buf, "%s %s", obj->name, arg3 );
		STRFREE( obj->name );
		obj->name = STRALLOC( buf );

        send_to_char( "Your item has been given another keyword.\n\r", ch );
        return;
    }

    else
    {
		send_to_char( "That cannot be enhanced. Read HELP QPBUY for details.\n\r", ch);  
		return;
    }

}


void generate_quest(CHAR_DATA *ch, CHAR_DATA *questman)
{
    CHAR_DATA *victim=NULL;
    ROOM_INDEX_DATA *room;
    OBJ_DATA *questitem;

    /*  40 % chance it will send the player on a 'recover any item' quest. */
    if (qchance(40))
    {
 
        questitem = find_quest_obj(ch);
        if (questitem && questitem->carried_by)
			victim = questitem->carried_by;

        if (!victim || !questitem)
        {
			ch_printf(ch, "&CI'm sorry, but I don't have any quests for you at this time.&w\n\r");
			ch_printf(ch, "&CTry again later.&w\n\r");
            ch->pcdata->questmob = 0;
            ch->pcdata->questmobold = NULL;
            ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch)) 
               ch->pcdata->nextquest = 0; 
            else
               ch->pcdata->nextquest = 5;
            return;
        }

        room = victim->in_room;
		STRFREE( questitem->creator );
		questitem->creator = STRALLOC( ch->name );
		ch->pcdata->questobj = questitem->pIndexData->vnum;

        switch(number_range(0,5))
        {
		case 0:
			ch_printf(ch, "&CI've been contracted to acquire &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CUsing my resources I've located the present location of this item.&w\n\r");
			break;

		case 1:
			ch_printf(ch, "&CThe Battlesisters of Alden request I find &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CLast I heard, some creature had a hold of it.&w\n\r");
			break;

		case 2:
			ch_printf(ch, "&CI've always wanted to have &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CMy many agents have found one, but can't recover it.&w\n\r");
			break;

		case 3:
			ch_printf(ch, "&CLord Drazuk asked me to pick up &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CLord Drazuk is your friend...surely you don't want to upset him?&w\n\r");
			break;

		case 4:
			ch_printf(ch, "&CHave you ever seen a &W%s&C?&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CI've heard mention of its location, but haven't seen one...&w\n\r");
			break;

		case 5:
			ch_printf(ch, "&CMalaclypse tells a tale about &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CHe said the one who found it would gain great glory!&w\n\r");
			break;
        }

		ch_printf(ch, "&CLook in the general area of &W%s &Cfor &W%s\n\r",room->area->name, questitem->short_descr);
        ch_printf(ch, "&Cbeing carried by &W%s&C, in &W%s&C.&w\n\r",victim->short_descr, room->name);
        ch->pcdata->questroom = room->name;
        ch->pcdata->questarea = room->area->name;
		return;
    }

    /* Quest to kill a mob */
    else
    {
        victim = find_quest_mob(ch);

        if (!victim)
        {
    	    ch_printf(ch, "&CI'm sorry, but I don't have any quests for you at this time.&w\n\r");
			ch_printf(ch, "&CTry again later.&w\n\r");
            ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
            ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch)) 
               ch->pcdata->nextquest = 0; 
            else
               ch->pcdata->nextquest = 5;
            return;
        }

        room = victim->in_room;
        switch(number_range(0,5))
        {
		case 0:
			ch_printf(ch, "&W%s &Chas reneged upon a contract with me.&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CThe penalty for this is death, and you are to deliver the sentence!&w\n\r");
			break;

		case 1:
			ch_printf(ch,"&CI have a contract to carry out an assassination!&w\n\r");
			ch_printf(ch, "&CYou are to eliminate &W%s&C.&w\n\r",victim->short_descr);
			break;

		case 2: 
			ch_printf(ch, "&W%s &Chas dishonored thier family's name!&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CThey want blood, and you are going to give it to them!&w\n\r");
			break;

		case 3: 
			ch_printf(ch, "&W%s &Chas upset the mighty God, Drazuk!&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CHe will grant you glory and coin if you complete your quest!&w\n\r");
			break;

		case 4: 
			ch_printf(ch, "&W%s &Chas upset the Thieves Guild of Alden.&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CThey wish for someone else to handle the matter for them.&w\n\r");
			break;

		case 5: 
			ch_printf(ch, "&W%s &Cjust plain doesn't deserve to live!&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CI advise you to find them and terminate their existence!&w\n\r");
			break;
        }

        if (room->name != NULL)
        {
            ch_printf(ch, "&CSeek &W%s &Cout somewhere in the vicinity of &W%s&C!&w\n\r",victim->short_descr,room->name);
			ch_printf(ch, "&CThat location is in the general area of &W%s&C.&w\n\r",room->area->name);
            ch->pcdata->questroom = room->name;
            ch->pcdata->questarea = room->area->name;
        }
        ch->pcdata->questmob = victim->pIndexData->vnum;
		ch->pcdata->questmobold = victim->pIndexData->short_descr;
    }
    return;
}

void generate_mquest(CHAR_DATA *ch, CHAR_DATA *questman)
{
    CHAR_DATA *victim=NULL;
    ROOM_INDEX_DATA *room;
    OBJ_DATA *questitem;

    /*  40 % chance it will send the player on a 'recover any item' quest. */
    if (qchance(40))
    {
        questitem = find_quest_obj(ch);
        if (questitem && questitem->carried_by)
           victim = questitem->carried_by;

        if (!victim || !questitem)
        {
			ch_printf(ch, "&CI'm sorry, but I don't have any magic quests for you at this time.&w\n\r");
			ch_printf(ch, "&CTry again later.&w\n\r");
			ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch)) 
			   ch->pcdata->nextquest = 0; 
			else
			   ch->pcdata->nextquest = 5;
            return;
        }

        room = victim->in_room;
		STRFREE( questitem->creator );
		questitem->creator = STRALLOC( ch->name );
		ch->pcdata->questobj = questitem->pIndexData->vnum;

        switch(number_range(0,6))
        {
		case 0:
			ch_printf(ch, "&CI need &W%s&C as a component of a spell I have been working on.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CUsing my resources I've located the current location of this item.&w\n\r");
			break;

		case 1:
			ch_printf(ch, "&CThe guild leaders request you to find &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CLast I heard, some creature had a hold of it.&w\n\r");
			break;

		case 2:
			ch_printf(ch, "&CI've always wanted to have &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CMy many agents have found one, but can't recover it.&w\n\r");
			break;

		case 3:
			ch_printf(ch, "&CDarwin requested that I pick up &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CDarwin is your friend... surely you wouldn't want to upset him?&w\n\r");
			break;

		case 4:
			ch_printf(ch, "&CHave you ever seen a &W%s&C?&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CI've heard mention of its location, but haven't seen one...&w\n\r");
			break;

		case 5:
			ch_printf(ch, "&CMalaclypse tells a tale about &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CI will reward you if you are able to bring this item to me!&w\n\r");
			break;
		case 6:
			ch_printf(ch, "&CI sent &W%s&C on a mission months ago to return &W%s&C to me.\n\r", victim->short_descr, questitem->short_descr);
			ch_printf(ch, "&CThe bum has yet to return. I will reward you, instead, if you bring me &W%s&C.\n\r", questitem->short_descr);
			break;
        }

		ch_printf(ch, "&CLook in the general area of &W%s &Cfor &W%s\n\r",room->area->name, questitem->short_descr);
        ch_printf(ch, "&Cbeing carried by &W%s&C, in &W%s&C.&w\n\r",victim->short_descr, room->name);
        ch->pcdata->questroom = room->name;
        ch->pcdata->questarea = room->area->name;
		return;
    }
    else /* Quest to kill a mob */
    {
        victim = find_quest_mob(ch);

        if (!victim)
        {
    	    ch_printf(ch, "&CI'm sorry, but I don't have any magic quests for you at this time.&w\n\r");
			ch_printf(ch, "&CTry again later.&w\n\r");
            ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
            ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch)) 
			   ch->pcdata->nextquest = 0; 
			else
			   ch->pcdata->nextquest = 5;
			return;
        }

        room = victim->in_room;
        switch(number_range(0,5))
        {
	    case 0:
			ch_printf(ch, "&W%s &Chas stolen goods from the guild.&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CThe penalty for this crime is death, and you are to deliver the sentence!&w\n\r");
			break;

	    case 1:
			ch_printf(ch,"&CRumor has it that &W%s&C has been spreading lies about the guild!&w\n\r", victim->short_descr);
			ch_printf(ch, "&CYou are to eliminate &W%s&C.&w\n\r",victim->short_descr);
			break;

		case 2: 
			ch_printf(ch, "&W%s &Chas dishonored the guild's good name!&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CThe guild wants blood, and you are going to give it to us!&w\n\r");
			break;

		case 3: 
			ch_printf(ch, "&W%s &Chas upset the mighty Goddess, Medea!&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CDestroy the infidel and be rewarded!&w\n\r");
			break;

		case 4: 
			ch_printf(ch, "&W%s &Chas been lurking around the guild, clearly up to no good.&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CI need you to eliminate &W%s&C before any of our secrets are discovered.&w\n\r", victim->short_descr);
			break;

		case 5: 
			ch_printf(ch, "&CThe guild has deemed &W%s&C unworthy to live!&w\n\r", victim->short_descr);
			ch_printf(ch, "&CI advise you to find them and terminate their existence!&w\n\r");
			break;
        }

        if (room->name != NULL)
        {
            ch_printf(ch, "&CSeek &W%s &Cout somewhere in the vicinity of &W%s&C!&w\n\r",victim->short_descr,room->name);
			ch_printf(ch, "&CThat location is in the general area of &W%s&C.&w\n\r",room->area->name);
            ch->pcdata->questroom = room->name;
            ch->pcdata->questarea = room->area->name;
        }
        ch->pcdata->questmob = victim->pIndexData->vnum;
		ch->pcdata->questmobold = victim->pIndexData->short_descr;
    }
    return;
}

void generate_squest(CHAR_DATA *ch, CHAR_DATA *questman)
{
    CHAR_DATA *victim=NULL;
    ROOM_INDEX_DATA *room;
    OBJ_DATA *questitem;

    /*  40 % chance it will send the player on a 'recover any item' quest. */
    if (qchance(40))
    {
        questitem = find_quest_obj(ch);
        if (questitem && questitem->carried_by)
           victim = questitem->carried_by;

        if (!victim || !questitem)
        {
			ch_printf(ch, "&CI'm sorry, but I don't have any skill quests for you at this time.&w\n\r");
			ch_printf(ch, "&CTry again later.&w\n\r");
			ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch)) 
			   ch->pcdata->nextquest = 0; 
			else
			   ch->pcdata->nextquest = 5;
            return;
        }

        room = victim->in_room;
		STRFREE( questitem->creator );
		questitem->creator = STRALLOC( ch->name );
		ch->pcdata->questobj = questitem->pIndexData->vnum;

        switch(number_range(0,5))
        {
		case 0:
			ch_printf(ch, "&COur guild needs &W%s&C for training purposes.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CUsing my resources I've located the current location of this item.&w\n\r");
			break;

		case 1:
			ch_printf(ch, "&CThe guild leaders request you to find &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CLast I heard, some creature had a hold of it.&w\n\r");
			break;

		case 2:
			ch_printf(ch, "&CI've always wanted to have &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CMy many agents have found one, but can't recover it.&w\n\r");
			break;

		case 3:
			ch_printf(ch, "&CMedea requested that I pick up &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CMedea is your friend... surely you wouldn't want to upset her?&w\n\r");
			break;

		case 4:
			ch_printf(ch, "&CHave you ever seen a &W%s&C?&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CI've heard rumors of its location, but haven't seen one...&w\n\r");
			break;

		case 5:
			ch_printf(ch, "&CMalaclypse tells a tale about &W%s&C.&w\n\r",questitem->short_descr);
			ch_printf(ch, "&CI will reward you if you are able to bring this item to me!&w\n\r");
			break;
        }

		ch_printf(ch, "&CLook in the general area of &W%s &Cfor &W%s\n\r",room->area->name, questitem->short_descr);
        ch_printf(ch, "&Cbeing carried by &W%s&C, in &W%s&C.&w\n\r",victim->short_descr, room->name);
        ch->pcdata->questroom = room->name;
        ch->pcdata->questarea = room->area->name;
		return;
    }
    else /* Quest to kill a mob */
    {
        victim = find_quest_mob(ch);

        if (!victim)
        {
    	    ch_printf(ch, "&CI'm sorry, but I don't have any skill quests for you at this time.&w\n\r");
			ch_printf(ch, "&CTry again later.&w\n\r");
            ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
            ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch)) 
			   ch->pcdata->nextquest = 0; 
			else
			   ch->pcdata->nextquest = 5;
			return;
        }

        room = victim->in_room;
        switch(number_range(0,5))
        {
	    case 0:
			ch_printf(ch, "&W%s &Chas stolen goods from the guild.&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CThe penalty for this crime is death, and you are to deliver the sentence!&w\n\r");
			break;

	    case 1:
			ch_printf(ch,"&CRumor has it that &W%s&C has been spreading lies about the guild!&w\n\r", victim->short_descr);
			ch_printf(ch, "&CYou are to eliminate &W%s&C.&w\n\r",victim->short_descr);
			break;

		case 2: 
			ch_printf(ch, "&W%s &Chas dishonored the guild's good name!&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CThe guild wants blood, and you are going to give it to us!&w\n\r");
			break;

		case 3: 
			ch_printf(ch, "&W%s &Chas upset the mighty Goddess, Medea!&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CDestroy the infidel and be rewarded!&w\n\r");
			break;

		case 4: 
			ch_printf(ch, "&W%s &Chas been lurking around the guild, clearly up to no good.&w\n\r",capitalize(victim->short_descr));
			ch_printf(ch, "&CI need you to eliminate &W%s&C before any of our secrets are discovered.&w\n\r", victim->short_descr);
			break;

		case 5: 
			ch_printf(ch, "&W%s&C's existance disgusts the guild!&w\n\r", capitalize(victim->short_descr));
			ch_printf(ch, "&CI advise you to find them and terminate their miserable existence!&w\n\r");
			break;
        }

        if (room->name != NULL)
        {
            ch_printf(ch, "&CSeek &W%s &Cout somewhere in the vicinity of &W%s&C!&w\n\r",victim->short_descr,room->name);
			ch_printf(ch, "&CThat location is in the general area of &W%s&C.&w\n\r",room->area->name);
            ch->pcdata->questroom = room->name;
            ch->pcdata->questarea = room->area->name;
        }
        ch->pcdata->questmob = victim->pIndexData->vnum;
		ch->pcdata->questmobold = victim->pIndexData->short_descr;
    }
    return;
}

/* Called from update_handler() by pulse_area */

void quest_update(void)
{
    CHAR_DATA *ch;
	DESCRIPTOR_DATA *d, *d_next;

	// change this to just loop through descriptors since
	// they should be the only characters able to quest
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
			bug( "quest_update: NPC found in descriptor loop" );
			continue;
		}

		if (ch->pcdata->nextquest > 0)
		{
			ch->pcdata->nextquest--;

			if (ch->pcdata->nextquest == 0)
			{
				send_to_char("&WYou may now quest again.&D\n\r",ch);
				return;
			}
		}
		if (ch->pcdata->nextmquest > 0)
		{
			ch->pcdata->nextmquest--;

			if (ch->pcdata->nextmquest == 0)
			{
				send_to_char("&WYou may now magic quest again.&D\n\r",ch);
				return;
			}
		}
		if (ch->pcdata->nextsquest > 0)
		{
			ch->pcdata->nextsquest--;

			if (ch->pcdata->nextsquest == 0)
			{
				send_to_char("&WYou may now skill quest again.&D\n\r",ch);
				return;
			}
		}

		if (xIS_SET(ch->act,PLR_QUESTOR))
		{
			if (--ch->pcdata->countdown <= 0)
			{
				if(IS_IMMORTAL(ch)) 
				   ch->pcdata->nextquest = 0; 
				else
				   ch->pcdata->nextquest = 10;
				ch_printf(ch, "You have run out of time for your quest!\n\rYou may quest again in %d minutes.\n\r",ch->pcdata->nextquest);
				xREMOVE_BIT(ch->act, PLR_QUESTOR);
				STRFREE(ch->pcdata->questroom);
				STRFREE(ch->pcdata->questarea);
				ch->pcdata->questgiver = 0;
				ch->pcdata->countdown = 0;
				ch->pcdata->questmob = 0;
				ch->pcdata->questmobold = NULL;
			}
		}
		if (xIS_SET(ch->act,PLR_SQUESTOR))
		{
			if (--ch->pcdata->countdownsq <= 0)
			{
				if(IS_IMMORTAL(ch)) 
				   ch->pcdata->nextsquest = 0; 
				else
				   ch->pcdata->nextsquest = 10;
				ch_printf(ch, "You have run out of time for your quest!\n\rYou may quest again in %d minutes.\n\r",ch->pcdata->nextquest);
				xREMOVE_BIT(ch->act, PLR_SQUESTOR);
				STRFREE(ch->pcdata->questroom);
				STRFREE(ch->pcdata->questarea);
				ch->pcdata->questgiver = 0;
				ch->pcdata->countdownsq = 0;
				ch->pcdata->questmob = 0;
				ch->pcdata->questmobold = NULL;
			}
		}
		if (xIS_SET(ch->act,PLR_MQUESTOR))
		{
			if (--ch->pcdata->countdownmq <= 0)
			{
				if(IS_IMMORTAL(ch)) 
				   ch->pcdata->nextmquest = 0; 
				else
				   ch->pcdata->nextmquest = 10;
				ch_printf(ch, "You have run out of time for your quest!\n\rYou may quest again in %d minutes.\n\r",ch->pcdata->nextquest);
				xREMOVE_BIT(ch->act, PLR_MQUESTOR);
				STRFREE(ch->pcdata->questroom);
				STRFREE(ch->pcdata->questarea);
				ch->pcdata->questgiver = 0;
				ch->pcdata->countdownmq = 0;
				ch->pcdata->questmob = 0;
				ch->pcdata->questmobold = NULL;
			}
		}
	    if ((ch->pcdata->countdown > 0 && ch->pcdata->countdown < 10)
			|| (ch->pcdata->countdownmq > 0 && ch->pcdata->countdownmq < 10)
			|| (ch->pcdata->countdownsq > 0 && ch->pcdata->countdownsq < 10))
	    {
	        send_to_char("Better hurry, you have less than 10 minutes to complete your quest!\n\r",ch);
	        return;
	    }
    }
    return;
}

void do_qstat( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    OBJ_INDEX_DATA *questinfoobj;
    MOB_INDEX_DATA *questinfo;
    MOB_INDEX_DATA *mobminfo;

    one_argument( argument, arg );
    if ( arg[0] == '\0' )
    {
		send_to_char( "Qstat whom?\n\r", ch );
		return;
    }

    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    {
		send_to_char( "They aren't here.\n\r", ch );
		return;
    }

    if ( IS_NPC(victim) )
    {
		send_to_char( "Mobiles cannot quest.\n\r", ch );
		return;
    }

    if (xIS_SET(victim->act, PLR_MOBM) || xIS_SET(victim->act, PLR_MOBM_EXPERT))
    { 
		mobminfo = get_mob_index(victim->mobmaster);
		if (mobminfo == NULL )
			ch_printf(ch, "%s has something broken with MobM's\n\r", victim->name );
		else if (mobminfo != NULL)
			ch_printf(ch, "%s is on a%s mobmaster quest.\n\rTarget: %s   VNum: %d\n\r", victim->name, xIS_SET(victim->act, PLR_MOBM_EXPERT)? "n expert": "", mobminfo->short_descr, mobminfo->vnum );
    } 
    if (!xIS_SET(victim->act, PLR_QUESTOR) && !xIS_SET(victim->act, PLR_SQUESTOR) && !xIS_SET(victim->act, PLR_MQUESTOR) )
    {
		ch_printf(ch, "%s is not on a quest and may quest again in %d.\n\r",victim->name, victim->pcdata->nextquest );
		return;
    }
    ch_printf(ch, "%s has %d minutes left for their quest.\n\r",victim->name, victim->pcdata->countdown );
    
    questinfoobj = get_obj_index(victim->pcdata->questobj);
    if (questinfoobj != NULL)
		ch_printf(ch, "%s is on a quest to find %s.\n\rObject Vnum: %d\n\rFound in %s in %s.\n\r",victim->name, questinfoobj->short_descr, questinfoobj->vnum, victim->pcdata->questroom, victim->pcdata->questarea );

    questinfo = get_mob_index(victim->pcdata->questmob);
    if (questinfo != NULL)
		ch_printf(ch, "%s is on a quest to slay %s.\n\rMobile Vnum: %d\n\rFound in %s in %s.\n\r", victim->name, questinfo->short_descr, questinfo->vnum, victim->pcdata->questroom, victim->pcdata->questarea );
	return;
}

void do_fixmobm( CHAR_DATA *ch, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    MOB_INDEX_DATA *mobminfo;

    one_argument( argument, arg ); 
    if ( arg[0] == '\0' ) 
    {  
        send_to_char( "Qstat whom?\n\r", ch );
        return;
    }
	
    if ( ( victim = get_char_world( ch, arg ) ) == NULL )
    { 
        send_to_char( "They aren't here.\n\r", ch );
        return;
    }

    if (xIS_SET(victim->act, PLR_MOBM) || xIS_SET(victim->act, PLR_MOBM_EXPERT))
    { 
		mobminfo = get_mob_index(victim->mobmaster); 
		if (mobminfo == NULL ) 
		{
			ch_printf(ch, "%s has something broken with MobM's\n\r", victim->name );    
			if(xIS_SET(victim->act, PLR_MOBM))
				xREMOVE_BIT( victim->act, PLR_MOBM );
			else if(xIS_SET(victim->act, PLR_MOBM_EXPERT))
				xREMOVE_BIT(victim->act, PLR_MOBM_EXPERT);
			victim->mobmticks = 0;
			victim->nextmobm = 0;
			send_to_char( "Fixed!\n\r", ch );
			return;
		} 
		else if (mobminfo != NULL)
		{ 
			ch_printf(ch, "%s is on a mobmaster quest.\n\rTarget: %s   VNum: %d\n\r", victim->name, mobminfo->short_descr, mobminfo->vnum );
			return;
		} 
    }    
}
    

/* setquest <victim> <mob|obj> <vnum> <location name> */

void do_setquest( CHAR_DATA *ch, char *argument )
{
  char arg[MAX_INPUT_LENGTH];
  char arg2[MAX_INPUT_LENGTH];
  char arg3[MAX_INPUT_LENGTH];
  CHAR_DATA *victim;
  int vnum;
  bool object=TRUE;

  set_char_color( AT_IMMORT, ch );

  if ( IS_NPC(ch) )
  {
    send_to_char( "Cannot setquest as an NPC.\n\r", ch );
    return;
  }
  if ( get_trust( ch ) < LEVEL_IMMORTAL ) 
  {
    send_to_char( "Huh?\n\r", ch );
    return;
  }

  argument = one_argument( argument, arg );
  argument = one_argument( argument, arg2 );
  argument = one_argument( argument, arg3 );
  vnum = atoi( arg3 );
  if ( arg[0] == '\0' || arg2[0] == '\0' || vnum <= 0)
  {
    send_to_char( "Syntax: setquest <character> <mob|obj> <vnum> <quest location>\n\r", ch );
    send_to_char( "Vnum must be an existing mobile vnum.\n\r", ch );
    return;
  }
  if ( ( victim = get_char_world( ch, arg ) ) == NULL )
  {
    send_to_char( "There is no such player currently playing.\n\r", ch );
    return;
  }
  if ( IS_NPC( victim ) )
  {
    send_to_char( "Quests cannot be given to or taken from a mob.\n\r", ch );
    return;
  }

  set_char_color( AT_IMMORT, victim );
  if ( nifty_is_name_prefix( arg2, "mob" ) )
    object = FALSE;
  else if ( nifty_is_name_prefix( arg2, "obj" ) )
    object = TRUE;
  else
  {
    do_setquest( ch, "" );
    return;
  }


  if ( object )
  {
   if (obj_by_vnum(vnum) == NULL)
   {
    send_to_char( "There is no such object.\n\r", ch );
    return;
   }
   if (obj_by_vnum(vnum)->carried_by)
   {
    victim->pcdata->questarea = STRALLOC(obj_by_vnum(vnum)->carried_by->in_room->area->name);
    victim->pcdata->questroom = STRALLOC(obj_by_vnum(vnum)->carried_by->in_room->name);
   }
   if (obj_by_vnum(vnum)->in_room)
   {
    victim->pcdata->questarea = STRALLOC(obj_by_vnum(vnum)->in_room->area->name);
    victim->pcdata->questroom = STRALLOC(obj_by_vnum(vnum)->in_room->name);
   }

   victim->pcdata->questmob = 0;
   victim->pcdata->questmobold = NULL;
   victim->pcdata->questobj = vnum;
   ch_printf( ch, "You've assigned %s a quest to find %s in %s in the area of %s\n\r", victim->name, obj_by_vnum(vnum)->short_descr, victim->pcdata->questroom, victim->pcdata->questarea );
   ch_printf( victim, "You've been assigned a quest to find %s in %s in the area of %s\n\r", obj_by_vnum(vnum)->short_descr, victim->pcdata->questroom, victim->pcdata->questarea );
  }
  else
  {
   if (get_mob(vnum) == NULL)
   {
    send_to_char( "There is no such mobile.\n\r", ch );
    return;
   }
   victim->pcdata->questarea = STRALLOC(get_mob(vnum)->in_room->area->name);
   victim->pcdata->questroom = STRALLOC(get_mob(vnum)->in_room->name);
   victim->pcdata->questobj = 0;
   victim->pcdata->questmob = vnum;
   ch_printf( ch, "You've assigned %s a quest to slay %s, in %s in the area of %s\n\r", victim->name, get_mob(vnum)->short_descr, victim->pcdata->questroom, victim->pcdata->questarea );
   ch_printf( victim, "You've been assigned a quest to slay %s in %s in the area of %s\n\r", get_mob(vnum)->short_descr, victim->pcdata->questroom, victim->pcdata->questarea );
  }
  xSET_BIT(victim->act, PLR_QUESTOR);
  victim->pcdata->nextquest = 0;
  victim->pcdata->countdown = 25;

  return;
}

CHAR_DATA *find_quest_mob( CHAR_DATA *ch)
{
  CHAR_DATA *victim=NULL;
  int counter, mob_vnum, level_diff, charlevel;
  charlevel = 0;

     for (counter = 0; counter < 2000; counter ++)
     {
	mob_vnum = number_range(100, 22000); /* Raise 32000 to your highest mobile vnum */

	if ( (victim = get_mob(mob_vnum) ) != NULL )
	{
            if(!IS_IMMORTAL(ch) && IS_TIER(ch))
		charlevel = 50 + (ch->level / 10);
	    else
	 	charlevel = ch->level;

	    level_diff = victim->level - charlevel;

            if ((level_diff >= -10  && level_diff <= questmaster->level_range)  
                && !IS_SET(victim->in_room->room_flags, ROOM_SAFE)
                && in_hard_range(ch, victim->in_room->area)
                && !xIS_SET( victim->act, ACT_NOQUEST) 
                && !xIS_SET( victim->act, ACT_PET) 
    		&& !xIS_SET( victim->act, ACT_IMMORTAL))
             return victim;
	    else 
             continue;
	}
    }
  return victim;
}

OBJ_DATA *find_quest_obj( CHAR_DATA *ch)
{
  CHAR_DATA *victim=NULL;
  int counter, obj_vnum, level_diff, charlevel;
  OBJ_DATA *obj=NULL;
  charlevel = 0;

     for (counter = 0; counter < 2000; counter ++)
     {
        OBJ_DATA *obj;

   	obj_vnum = number_range(100, 22000); /* Raise 32000 to your highest obj vnum */

   	if ( (obj = obj_by_vnum(obj_vnum) ) != NULL )
   	{

            if (IS_OBJ_STAT(obj, ITEM_PROTOTYPE)
            || IS_OBJ_STAT(obj, ITEM_INVENTORY)
            || ( obj->item_type == ITEM_CONTAINER )
            || (obj->timer > 0)
            || !obj->carried_by
            || IS_OBJ_STAT(obj, ITEM_NOQUEST)
            || (obj->carried_by && !IS_NPC(obj->carried_by))
            || IS_OBJ_STAT(obj, ITEM_DEATHROT))
              continue;

            if ( (victim = obj->carried_by ) == NULL )
              continue;
            if (!victim || !IS_NPC(victim))
              continue;

            if(!IS_IMMORTAL(ch) && IS_TIER(ch)) 
                charlevel = 50 + (ch->level / 10); 
            else 
                charlevel = ch->level; 

	    level_diff = victim->level - charlevel;

            if (((level_diff < questmaster->level_range && level_diff >= -10))  
                && !IS_SET(victim->in_room->room_flags, ROOM_SAFE)
                && in_hard_range(ch, victim->in_room->area)
                && !xIS_SET( victim->act, ACT_NOQUEST) 
                && !xIS_SET( victim->act, ACT_PET) 
                && !xIS_SET( victim->act, ACT_IMMORTAL))
             return obj;
	    else 
             continue;

   	}
     }
  return obj;
}

void quest_list(CHAR_DATA *ch)
{
  sh_int i, count=0;

  ch_printf( ch, "&Y[&W%2s&Y] [&W%-35s&Y] [&W%6s&Y] \n\r", "#", "Item", "Cost" );
  for(i = 0; i <= MAX_QDATA; i++)
  {
   if (questmaster->award_vnum[i] && questmaster->award_value[i])
   {
     ++count;
     ch_printf( ch, "&Y[&W%2d&Y] [&g%-35s&Y] [&W%6s&Y] \n\r", count, get_obj_index(questmaster->award_vnum[i])->short_descr,
		 num_punct(questmaster->award_value[i]) );
   }
  }
  ch_printf( ch, "&Y[&W%2d&Y] [100000 Gold                        ] [&W   500&Y]\n\r", count+1 );
  ch_printf( ch, "&Y[&W%2d&Y] [10 Practices                       ] [&W   500&Y]\n\r", count+2 );
  return;
}

void quest_buy(CHAR_DATA *questman, CHAR_DATA *ch, sh_int number)
{
  sh_int i, count=0;
  OBJ_DATA *obj;

  for(i = 0; i <= MAX_QDATA; i++)
  {
   if (questmaster->award_vnum[i] > 0 && questmaster->award_value[i] > 0)
   {
     ++count;
     if (count == number)
      break;
   }
  }
  if (number > count+2 || number < 1)
  {
    do_say(questman, "I don't know what you're trying to buy. Check the list again.");
    return;
  }

  if (number == (count+1)) /* Gold */
  {
   if (ch->pcdata->quest_curr >= questmaster->gold_cost)
   {
    ch->pcdata->quest_curr -= questmaster->gold_cost;
    ch->gold += taxed(questmaster->gold_amt);
	tax(ch, questmaster->gold_amt);
    act(AT_MAGIC,"$N gives a sack of gold pieces to $n.", ch, NULL, questman, TO_ROOM );
    act(AT_MAGIC,"$N hands you your gold.", ch, NULL, questman, TO_CHAR );
    return;
   }
   else
   {
    do_say(questman, "You're not glorious enough to purchase that.");
    return;
   }
  }
  else if (number == (count+2)) /* Practices */
  {
   if (ch->pcdata->quest_curr >= questmaster->practice_cost)
   {
    ch->pcdata->quest_curr -= questmaster->practice_cost;
    ch->practice += questmaster->practice_amt;
    act(AT_MAGIC,"$N expands $n's mind to recieve greater knowledge.", ch, NULL, questman, TO_ROOM );
    act(AT_MAGIC,"$N opens your mind to greater possibilities of learning.", ch, NULL, questman, TO_CHAR );
    return;
   }
   else
   {
    do_say(questman, "You're not glorious enough to purchase that.");
    return;
   }
  }
  else if (ch->pcdata->quest_curr >= questmaster->award_value[i] && (questmaster->award_value[i] != 0))
  {
   ch->pcdata->quest_curr -= questmaster->award_value[i];
   obj = create_object(get_obj_index(questmaster->award_vnum[i]), ch->level);
   obj->owner = ch->name;
   act(AT_PLAIN,"$N gives $p to $n.", ch, obj, questman, TO_ROOM );
   act(AT_PLAIN,"$N gives you $p.",   ch, obj, questman, TO_CHAR );
   obj_to_char(obj, ch);
  }
  else
  {
   do_say(questman, "You're not glorious enough to purchase that.");
   return;
  }
  return;
}


void fwrite_questmaster()
{
    FILE *fp;
    char filename[256];
    int counter;

    sprintf( filename, "%s", QUEST_FILE );
    
    fclose( fpReserve );
    if ( ( fp = fopen( filename, "w" ) ) == NULL )
    {
    	bug( "fwrite_questmaster: fopen", 0 );
    	perror( filename );
    }
    fprintf( fp, "Lrange %d\n", questmaster->level_range);
    fprintf( fp, "Pamt %d\n",	questmaster->practice_amt);
    fprintf( fp, "Pcost %d\n",	questmaster->practice_cost);
    fprintf( fp, "Gamt %d\n",	questmaster->gold_amt	);
    fprintf( fp, "Gcost %d\n",	questmaster->gold_cost	);
    for(counter = 0; counter <= MAX_QDATA; counter++)
     if (questmaster->award_value[counter] && questmaster->award_vnum[counter])
	fprintf( fp, "Object %d %d\n", questmaster->award_vnum[counter], questmaster->award_value[counter] );
     else
        continue;
    fprintf( fp, "End\n"						);
    fclose( fp );
    fpReserve = fopen( NULL_FILE, "r" );
    return;
}

#if defined(KEY)
#undef KEY
#endif

#define KEY( literal, field, value )		\
if ( !str_cmp( word, literal ) )			\
{											\
	  field = value;						\
	  fMatch = TRUE;						\
	  break;								\
}


void fread_questmaster()
{
    char filename[256];
    FILE *fp;
    char buf[MAX_STRING_LENGTH];
    char *word;
    bool fMatch;
    int vnum=-1, value=-1, counter;

    sprintf( filename, "%s", QUEST_FILE );

    if ( ( fp = fopen( filename, "r" ) ) == NULL )
    {
    	bug( "fread_questmaster: fopen", 0 );
    	perror( filename );
    }
    for ( ; ; )
    {
	word   = feof( fp ) ? "End" : fread_word( fp );
	fMatch = FALSE;

	switch ( UPPER(word[0]) )
	{
	case '*':
	    fMatch = TRUE;
	    fread_to_eol( fp );
	    break;
	case 'E':
	    if ( !str_cmp( word, "End" ) )
            {
                fclose( fp );
                for(counter = vnum; counter != MAX_QDATA; counter++)
                {
		 questmaster->award_vnum[++vnum] = 0;
		 questmaster->award_value[++value] = 0;
                }
		return;
            }
	    break;
	case 'G':
	    KEY( "Gamt",	questmaster->gold_amt,	fread_number( fp ) );
	    KEY( "Gcost",	questmaster->gold_cost,	fread_number( fp ) );
	    break;
	case 'L':
	    KEY( "Lrange",	questmaster->level_range, fread_number( fp ) );
	    break;
	case 'P':
	    KEY( "Pamt",	questmaster->practice_amt,	fread_number( fp ) );
	    KEY( "Pcost",	questmaster->practice_cost,	fread_number( fp ) );
	    break;
	case 'O':
	    if ( !str_cmp( word, "Object" ) )
            {
                if (vnum >= MAX_QDATA)
                 break;
		questmaster->award_vnum[++vnum]	= fread_number( fp );
		questmaster->award_value[++value] = fread_number( fp );
		fMatch = TRUE;
                break;
            }
	    break;
	}
	if ( !fMatch )
	{
	    sprintf( buf, "fread_questmaster: no match: %s", word );
	    bug( buf, 0 );
	}
    }
}

void do_queststat( CHAR_DATA *ch, char *argument)
{
  char arg1[MAX_INPUT_LENGTH];
  char arg2[MAX_INPUT_LENGTH];
  char arg3[MAX_INPUT_LENGTH];
  char arg4[MAX_INPUT_LENGTH];

  argument = one_argument( argument, arg1 );
  argument = one_argument( argument, arg2 );
  argument = one_argument( argument, arg3 );
  argument = one_argument( argument, arg4 );

  if (arg1[0] == '\0')
  {
    sh_int i, count=0;

    for(i = 0; i != MAX_QDATA; i++)
    {
       ch_printf( ch, "&p[&w%2d&p] [&g%-35s&p] [&w%6s&p] [&w%6d&p] \n\r", count, questmaster->award_vnum[i] ? get_obj_index(questmaster->award_vnum[i])->short_descr : "Empty", num_punct(questmaster->award_value[i]), questmaster->award_vnum[i] );
       ++count;
    }
    ch_printf( ch, "&p[&w**&p] [&Y100000 Gold&p                        ] [&w   500&p] \n\r");
    ch_printf( ch, "&p[&w**&p] [&Y10 Practices&p                       ] [&w   500&p] \n\r");
    ch_printf( ch, "&p[&w**&p] [%-37s&p] [&w%6d&p]\n\r", "&YLevel Range", questmaster->level_range  );
    return;
  }
  if (!str_cmp(arg1, "Object"))
  {
   int seek=atoi(arg2), vnum=atoi(arg3), value=atoi(arg4);
   sh_int i, count=0;

   if (vnum < 0|| seek < 0|| value < 0)
   {
    send_to_char( "Syntax: queststat object # vnum value\n\r", ch );
    return;
   }
   
   for(i = 0; i != MAX_QDATA; i++)
   {
     if (count == seek)
      break;
     ++count;
   }

   if (seek != count)
   {
    send_to_char( "# Not found.\n\r", ch );
    send_to_char( "Syntax: queststat object # vnum value\n\r", ch );
    return;
   }
   else
   {
    questmaster->award_vnum[i] = vnum;
    questmaster->award_value[i] = value;
   }
   fwrite_questmaster();
   send_to_char( "Done.\n\r", ch );
   return;
  }
  if (!str_cmp(arg1, "Gold"))
  {
   int amount=atoi(arg2), value=atoi(arg3);

   if (!amount || !value)
   {
    send_to_char( "Syntax: queststat gold amount value\n\r", ch );
    return;
   }
   questmaster->gold_amt = amount;
   questmaster->gold_cost = value;
   fwrite_questmaster();
   send_to_char( "Done.\n\r", ch );
   return;
  }
  if (!str_cmp(arg1, "Practices"))
  {
   int amount=atoi(arg2), value=atoi(arg3);

   if (!amount || !value)
   {
    send_to_char( "Syntax: queststat practices amount value\n\r", ch );
    return;
   }
   questmaster->practice_amt = amount;
   questmaster->practice_cost = value;
   fwrite_questmaster();
   send_to_char( "Done.\n\r", ch );
   return;
  }
  if (!str_cmp(arg1, "Range"))
  {
   int value=atoi(arg2);

   if (!value)
   {
    send_to_char( "Syntax: queststat range value\n\r", ch );
    return;
   }
   questmaster->level_range = value;
   fwrite_questmaster();
   send_to_char( "Done.\n\r", ch );
   return;
  }
  do_queststat(ch, "");
  return;
}

void do_squest(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *questman;
    OBJ_DATA *obj=NULL, *obj_next;
    OBJ_INDEX_DATA *questinfoobj;
    MOB_INDEX_DATA *questinfo;
    char buf [MAX_STRING_LENGTH];
    char arg1 [MAX_INPUT_LENGTH];

    if (IS_NPC(ch)) return;

	//~ if(!IS_FIGHTER(ch))
	//~ {
		//~ send_to_char("&WYour classes disallow you from attempting a skill quest.&D\n\r", ch);
		//~ return;
	//~ }

    argument = one_argument(argument, arg1);

    if (!strcmp(arg1, "info"))
    {
        if (xIS_SET(ch->act, PLR_SQUESTOR))
		{
			if (ch->pcdata->questmob == -1 && ch->pcdata->questgiver != 0)
				ch_printf(ch, "&CYour skill quest is ALMOST complete!\n\rGet back to your guild master before your time runs out!&w\n\r");
			else if (ch->pcdata->questobj > 0)
			{
				questinfoobj = get_obj_index(ch->pcdata->questobj);
				if (questinfoobj != NULL)
					ch_printf(ch, "&CYou are on a skill quest to recover %s from %s in %s.&w\n\r",questinfoobj->short_descr, ch->pcdata->questroom, ch->pcdata->questarea);
				else 
					send_to_char("&CYou aren't currently on a skill quest.&w\n\r",ch);
				return;
			}
			else if (ch->pcdata->questmob > 0)
			{
				questinfo = get_mob_index(ch->pcdata->questmob);
				if (questinfo != NULL)
					ch_printf(ch, "&CYou are on a skill quest to slay %s in %s in the area of %s.&w\n\r",questinfo->short_descr, ch->pcdata->questroom, ch->pcdata->questarea);
				else 
					send_to_char("&CYou aren't currently on a skill quest.&w\n\r",ch);
				return;
			}
		}
		else
			send_to_char("&CYou aren't currently on a skill quest.&w\n\r",ch);
		return;
    }
    if (!strcmp(arg1, "points"))
    {
		ch_printf(ch, "&CYou have &W%d &Cskill points.&w\n\r",ch->pcdata->skillpoints);
		return;
    }
    else if (!strcmp(arg1, "time"))
    {
        if (!xIS_SET(ch->act, PLR_SQUESTOR))
		{
			send_to_char("&CYou aren't currently on a skill quest.&w\n\r",ch);
			if (ch->pcdata->nextsquest > 1)
				ch_printf(ch, "&CThere are &Y%d &Cminutes remaining until you can go on another quest.&w\n\r",ch->pcdata->nextsquest);
			else if (ch->pcdata->nextsquest == 1)
				ch_printf(ch, "&CThere is less than a minute remaining until you can go on another quest.&w\n\r");
		}
        else if (ch->pcdata->countdownsq > 0)
			ch_printf(ch, "&CTime left for current skill quest: &W%d&w\n\r",ch->pcdata->countdownsq);
		return;
    }

/* Check for guild master in room. */

    for ( questman = ch->in_room->first_person; questman != NULL; questman = questman->next_in_room )
		if (IS_NPC(questman) && xIS_SET(questman->act, ACT_PRACTICE))
			break;

    if (!questman)
    {
        send_to_char("&CYou can't do that here.&w\n\r",ch);
        return;
    }

    if ( questman->fighting)
    {
		send_to_char("&CWait until the fighting stops.&w\n\r",ch);
        return;
    }

    ch->pcdata->questgiver = questman->pIndexData->vnum;

    if (!strcmp(arg1, "request"))
    {
        act(AT_PLAIN,"$n asks $N for a skill quest.", ch, NULL, questman, TO_ROOM);
		act(AT_PLAIN,"You ask $N for a skill quest.",ch, NULL, questman, TO_CHAR);
        if (sysdata.DENY_NEW_PLAYERS == TRUE)
		{
            ch_printf(ch, "&CI'm sorry. Please come back after the reboot. I can't give you a quest until then.&w\n\r");
			return;
		}
        if (xIS_SET(ch->act, PLR_SQUESTOR) || xIS_SET(ch->act, PLR_QUESTOR) || xIS_SET(ch->act, PLR_MQUESTOR))
		{
            ch_printf(ch, "&CBut you're already on a quest!\n\rBetter hurry up and finish it!&w\n\r");
			return;
		}
		if (ch->pcdata->nextsquest > 0)
		{
			ch_printf(ch, "&CYou're very brave, %s, but you must wait before you can quest again.&w\n\r",ch->name);
			ch_printf(ch, "&CPlease come back in about &W%d &Cminutes.&w\n\r", ch->pcdata->nextsquest);
			return;
		}

		ch_printf(ch, "&CVery well %s...&w\n\r",ch->name);

		generate_squest(ch, questman);

        if (ch->pcdata->questmob > 0 || ch->pcdata->questobj > 0)
		{
            ch->pcdata->countdownsq = number_range(15,45);
            xSET_BIT(ch->act, PLR_SQUESTOR);
			ch_printf(ch, "&CYou have &W%d &Cminutes to complete this quest.&w\n\r",ch->pcdata->countdownsq);
			ch_printf(ch, "&CMay the gods go with you!&w\n\r");
		}
		return;
    }
    else if (!strcmp(arg1, "refuse"))
    {
        act(AT_PLAIN,"$n informs $N $e has refused $s quest.", ch, NULL, questman, TO_ROOM);
        act(AT_PLAIN,"You inform $N you have refused the quest.",ch, NULL, questman, TO_CHAR);
		if (ch->pcdata->questgiver != questman->pIndexData->vnum)
		{
			ch_printf(ch, "&CI never sent you on a quest! Perhaps you're thinking of someone else.&w\n\r");
			return;
		}
        if (!xIS_SET(ch->act, PLR_SQUESTOR))
		{
	        ch->pcdata->questgiver = 0;
	        ch->pcdata->countdownsq = 0;
	        ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
	        ch_printf(ch, "&CYou should at least &WREQUEST &Ca quest before you refuse it!&w\n\r");

	        return;
	    }

        if (xIS_SET(ch->act, PLR_SQUESTOR))
		{
			xREMOVE_BIT(ch->act, PLR_SQUESTOR);
	        ch->pcdata->questgiver = 0;
	        ch->pcdata->countdownsq = 0;
	        ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch))
			   ch->pcdata->nextsquest = 0;
			else
				   ch->pcdata->nextsquest = 5;
	        ch_printf(ch, "&CAlright fine, I'll put it back in the heap for someone else.&w\n\r");
            ch_printf(ch, "&CYou can come back in about &W%d &Cminutes.&w\n\r", ch->pcdata->nextsquest);

	        return;
	    }
    }
    else if (!strcmp(arg1, "complete"))
    {
        act(AT_PLAIN,"$n informs $N $e has completed $s quest.", ch, NULL, questman, TO_ROOM);
        act(AT_PLAIN,"You inform $N you have completed $s quest.",ch, NULL,	questman, TO_CHAR);
		if (ch->pcdata->questgiver != questman->pIndexData->vnum)
		{
			ch_printf(ch, "&CI never sent you on a quest! Perhaps you're thinking of someone else.&w\n\r");
			return;
		}
        if (xIS_SET(ch->act, PLR_SQUESTOR))
		{
			if (ch->pcdata->questmob == -1 && ch->pcdata->countdownsq > 0)
			{
				int reward, pointreward, pracreward, expreward;
                reward = number_range(1000,5000);
                pointreward = number_range(5,10);
				expreward = number_range(250,500);

				ch_printf(ch, "&CCongratulations on completing your skill quest!&w\n\r");
				ch_printf(ch,"&CAs a reward, I am giving you &W%d skill points&C, &Y%d gold&C and &P%d experience points&C!&w\n\r",
				pointreward,reward,expreward);
                if (number_range(1,100) <= 25)
				{
                    pracreward = number_range(1,3);
					ch_printf(ch, "&CYou gain &W%d practice%s&C!&w\n\r",pracreward, pracreward > 1 ? "s" : "");
					ch->practice += pracreward;
				}
                if ( ch->pcdata->questmobold != NULL ) 
                   sprintf(buf, "[INFO] %s has completed a skill quest to slay %s!", ch->name, ch->pcdata->questmobold);
                else 
                   sprintf(buf, "[INFO] %s has completed a skill quest to slay a creature!", ch->name);
                echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL );  //Yzek 

                xREMOVE_BIT(ch->act, PLR_SQUESTOR);
				ch->pcdata->questgiver = 0;
				ch->pcdata->countdownsq = 0;
				ch->pcdata->questmob = 0;
				ch->pcdata->questmobold = NULL;
				ch->pcdata->questobj = 0;
				if(IS_IMMORTAL(ch)) 
                   ch->pcdata->nextsquest = 0; 
                else
                   ch->pcdata->nextsquest = 5;
				ch->gold += reward;
				gain_exp( ch, expreward );
				ch->pcdata->skillpoints += pointreward;

				return;
			}
			else if (ch->pcdata->questobj > 0 && ch->pcdata->countdownsq > 0)
			{
				bool obj_found = FALSE;

                for (obj = ch->first_carrying; obj != NULL; obj=obj_next)
				{
                    obj_next = obj->next_content;
					if (obj != NULL && obj->pIndexData->vnum == ch->pcdata->questobj && obj->wear_loc == WEAR_NONE)
					{
						obj_found = TRUE;
						break;
					}
				}
				if (obj_found == TRUE)
				{
					int reward, pointreward, pracreward, expreward;

					reward = number_range(1000,5000);
					pointreward = number_range(5,10);
					expreward = number_range(250,500);

					act(AT_PLAIN,"You hand $p to $N.",ch, obj, questman, TO_CHAR);
					act(AT_PLAIN,"$n hands $p to $N.",ch, obj, questman, TO_ROOM);
					
					ch_printf(ch, "&CCongratulations on completing your skill quest!&w\n\r");
					ch_printf(ch,"&CAs a reward, I am giving you &W%d skill points&C, &Y%d gold&C and &P%d experience points&C!&w\n\r",
							   pointreward,reward,expreward);   
					if (number_range(1,100) <= 25)
					{
						pracreward = number_range(1,3);
						ch_printf(ch, "&CYou gain &W%d practice%s&C!&w\n\r",pracreward, pracreward > 1 ? "s" : "");
						ch->practice += pracreward;
					}

					if ( ch->pcdata->questobj > 0 )
					{ 
						questinfoobj = get_obj_index(ch->pcdata->questobj);
						sprintf(buf, "[INFO] %s has completed a skill quest to find %s!", ch->name, questinfoobj->short_descr);
					} 
					else
					   sprintf(buf, "[INFO] %s has completed a skill quest to find an item!", ch->name);
	 
					echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL );  //Yzek 

					xREMOVE_BIT(ch->act, PLR_SQUESTOR);
					ch->pcdata->questgiver = 0;
					ch->pcdata->countdownsq = 0;
					ch->pcdata->questmob = 0;
					ch->pcdata->questmobold = NULL;
					ch->pcdata->questobj = 0;
					if(IS_IMMORTAL(ch)) 
					   ch->pcdata->nextsquest = 0; 
					else
					   ch->pcdata->nextsquest = 5;
					ch->gold += reward;
					gain_exp( ch, expreward );
					ch->pcdata->skillpoints += pointreward;

					extract_obj(obj);
					return;
				}
				else
				{
					ch_printf(ch, "&CYou haven't completed the skill quest yet, but there is still time!&w\n\r");
					return;
				}
				return;
			}
			else if ((ch->pcdata->questmob > 0 || ch->pcdata->questobj > 0) && ch->pcdata->countdownsq > 0)
			{
				ch_printf(ch, "&CYou haven't completed the skill quest yet, but there is still time!&w\n\r");
				return;
			}
		}
		if (ch->pcdata->nextsquest > 0)
			ch_printf(ch,"&CBut you didn't complete your skill quest in time!&w\n\r");
		else 
			ch_printf(ch, "&CYou have to &WREQUEST &Ca skill quest first, %s.&w\n\r",ch->name);
		return;
    }

    send_to_char("SQUEST commands: POINTS INFO TIME REQUEST REFUSE COMPLETE.\n\r",ch);
    send_to_char("For more information, type 'HELP SQUEST'.\n\r",ch);
    return;
}

void do_mquest(CHAR_DATA *ch, char *argument)
{
    CHAR_DATA *questman;
    OBJ_DATA *obj=NULL, *obj_next;
    OBJ_INDEX_DATA *questinfoobj;
    MOB_INDEX_DATA *questinfo;
    char buf [MAX_STRING_LENGTH];
    char arg1 [MAX_INPUT_LENGTH];

    if (IS_NPC(ch)) return;

	//~ if(!IS_CASTER(ch))
	//~ {
		//~ send_to_char("&WYour classes disallow you from attempting a magic quest.&D\n\r", ch);
		//~ return;
	//~ }

    argument = one_argument(argument, arg1);

    if (!strcmp(arg1, "info"))
    {
        if (xIS_SET(ch->act, PLR_MQUESTOR))
		{
			if (ch->pcdata->questmob == -1 && ch->pcdata->questgiver != 0)
			{
				ch_printf(ch, "&CYour magic quest is ALMOST complete!\n\rGet back to your guild master before your time runs out!&w\n\r");
			}
			else if (ch->pcdata->questobj > 0)
			{
				questinfoobj = get_obj_index(ch->pcdata->questobj);
				if (questinfoobj != NULL)
					ch_printf(ch, "&CYou are on a magic quest to recover %s from %s in %s.&w\n\r",questinfoobj->short_descr, ch->pcdata->questroom, ch->pcdata->questarea);
				else 
					send_to_char("&CYou aren't currently on a magic quest.&w\n\r",ch);
				return;
			}
			else if (ch->pcdata->questmob > 0)
			{
				questinfo = get_mob_index(ch->pcdata->questmob);
				if (questinfo != NULL)
					ch_printf(ch, "&CYou are on a magic quest to slay %s in %s in the area of %s.&w\n\r",questinfo->short_descr, ch->pcdata->questroom, ch->pcdata->questarea);
				else 
					send_to_char("&CYou aren't currently on a magic quest.&w\n\r",ch);
				return;
			}
		}
		else
			send_to_char("&CYou aren't currently on a magic quest.&w\n\r",ch);
		return;
    }
    if (!strcmp(arg1, "points"))
    {
		ch_printf(ch, "&CYou have &W%d &Cmagic points.&w\n\r",ch->pcdata->magicpoints);
		return;
    }
    else if (!strcmp(arg1, "time"))
    {
        if (!xIS_SET(ch->act, PLR_MQUESTOR))
		{
			send_to_char("&CYou aren't currently on a magic quest.&w\n\r",ch);
			if (ch->pcdata->nextmquest > 1)
				ch_printf(ch, "&CThere are &Y%d &Cminutes remaining until you can go on another quest.&w\n\r",ch->pcdata->nextmquest);
			else if (ch->pcdata->nextmquest == 1)
				ch_printf(ch, "&CThere is less than a minute remaining until you can go on another quest.&w\n\r");
		}
        else if (ch->pcdata->countdownmq > 0)
			ch_printf(ch, "&CTime left for current magic quest: &W%d&w\n\r",ch->pcdata->countdownmq);
		return;
    }

/* Check for guild master in room. */

    for ( questman = ch->in_room->first_person; questman != NULL; questman = questman->next_in_room )
		if (IS_NPC(questman) && xIS_SET(questman->act, ACT_PRACTICE))
			 break;

    if (!questman)
    {
        send_to_char("&CYou can't do that here.&w\n\r",ch);
        return;
    }

    if ( questman->fighting)
    {
		send_to_char("&CWait until the fighting stops.&w\n\r",ch);
        return;
    }

    ch->pcdata->questgiver = questman->pIndexData->vnum;

    if (!strcmp(arg1, "request"))
    {
        act(AT_PLAIN,"$n asks $N for a magic quest.", ch, NULL, questman, TO_ROOM);
		act(AT_PLAIN,"You ask $N for a skill quest.",ch, NULL, questman, TO_CHAR);
        if (sysdata.DENY_NEW_PLAYERS == TRUE)
		{
            ch_printf(ch, "&CI'm sorry. Please come back after the reboot. I can't give you a quest until then.&w\n\r");
			return;
		}
        if (xIS_SET(ch->act, PLR_QUESTOR) || xIS_SET(ch->act, PLR_SQUESTOR) || xIS_SET(ch->act, PLR_MQUESTOR))
		{
            ch_printf(ch, "&CBut you're already on a quest!\n\rBetter hurry up and finish it!&w\n\r");
			return;
		}
		if (ch->pcdata->nextmquest > 0)
		{
			ch_printf(ch, "&CYou're very brave, %s, but you must wait before you can quest again.&w\n\r",ch->name);
			ch_printf(ch, "&CPlease come back in about &W%d &Cminutes.&w\n\r", ch->pcdata->nextmquest);
			return;
		}

		ch_printf(ch, "&CVery well %s...&w\n\r",ch->name);

		generate_mquest(ch, questman);

        if (ch->pcdata->questmob > 0 || ch->pcdata->questobj > 0)
		{
            ch->pcdata->countdownmq = number_range(15,45);
            xSET_BIT(ch->act, PLR_MQUESTOR);
			ch_printf(ch, "&CYou have &W%d &Cminutes to complete this magic quest.&D\n\r",ch->pcdata->countdownmq);
			ch_printf(ch, "&CMay the gods go with you!&D\n\r");
		}
		return;
    }
    else if (!strcmp(arg1, "refuse"))
    {
        act(AT_PLAIN,"$n informs $N $e has refused $s quest.", ch, NULL, questman, TO_ROOM);
        act(AT_PLAIN,"You inform $N you have refused the quest.",ch, NULL, questman, TO_CHAR);
		if (ch->pcdata->questgiver != questman->pIndexData->vnum)
		{
			ch_printf(ch, "&CI never sent you on a magic quest! Perhaps you're thinking of someone else.&w\n\r");
			return;
		}
        if (!xIS_SET(ch->act, PLR_MQUESTOR))
		{
	        ch->pcdata->questgiver = 0;
	        ch->pcdata->countdownmq = 0;
	        ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
	        ch_printf(ch, "&CYou should at least &WREQUEST &Ca quest before you refuse it!&w\n\r");
	        return;
	    }

        if (xIS_SET(ch->act, PLR_MQUESTOR))
		{
			xREMOVE_BIT(ch->act, PLR_MQUESTOR);
	        ch->pcdata->questgiver = 0;
	        ch->pcdata->countdownmq = 0;
	        ch->pcdata->questmob = 0;
			ch->pcdata->questmobold = NULL;
			ch->pcdata->questobj = 0;
			if(IS_IMMORTAL(ch))
			{
			   ch->pcdata->nextmquest = 0;
			}
			else
			{
				   ch->pcdata->nextmquest = 5;
			}
	        ch_printf(ch, "&CAlright fine, I'll put it back in the heap for someone else.&w\n\r");
            ch_printf(ch, "&CYou can come back in about &W%d &Cminutes.&w\n\r", ch->pcdata->nextmquest);
	        return;
	    }
    }
    else if (!strcmp(arg1, "complete"))
    {
        act(AT_PLAIN,"$n informs $N $e has completed $s quest.", ch, NULL, questman, TO_ROOM);
        act(AT_PLAIN,"You inform $N you have completed $s quest.",ch, NULL,	questman, TO_CHAR);
		if (ch->pcdata->questgiver != questman->pIndexData->vnum)
		{
			ch_printf(ch, "&CI never sent you on a magic quest! Perhaps you're thinking of someone else.&w\n\r");
			return;
		}
        if (xIS_SET(ch->act, PLR_MQUESTOR))
		{
			if (ch->pcdata->questmob == -1 && ch->pcdata->countdownmq > 0)
			{
				int reward, pointreward, pracreward, expreward;
				reward = number_range(1000,5000);
				pointreward = number_range(5,10);
				expreward = number_range(250,500);

				ch_printf(ch, "&CCongratulations on completing your magic quest!&w\n\r");
				ch_printf(ch,"&CAs a reward, I am giving you &W%d magic points&C, &Y%d gold&C and &P%d experience points&C!&w\n\r",
					   pointreward,reward,expreward);
				if (number_range(1,100) <= 25)
				{
					pracreward = number_range(1,3);
					ch_printf(ch, "&CYou gain &W%d practice%s&C!&w\n\r",pracreward, pracreward > 1 ? "s" : "");
					ch->practice += pracreward;
				}
				if ( ch->pcdata->questmobold != NULL ) 
				{ 
				   sprintf(buf, "[INFO] %s has completed a magic quest to slay %s!", ch->name, ch->pcdata->questmobold);
				} 
				else 
				{ 
				   sprintf(buf, "[INFO] %s has completed a magic quest to slay a creature!", ch->name);
				} 
				echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL );  //Yzek 

				xREMOVE_BIT(ch->act, PLR_MQUESTOR);
				ch->pcdata->questgiver = 0;
				ch->pcdata->countdownmq = 0;
				ch->pcdata->questmob = 0;
				ch->pcdata->questmobold = NULL;
				ch->pcdata->questobj = 0;
				if(IS_IMMORTAL(ch)) 
				   ch->pcdata->nextmquest = 0; 
				else
				   ch->pcdata->nextmquest = 5;
				ch->gold += reward;
				gain_exp( ch, expreward );
				ch->pcdata->magicpoints += pointreward;

				return;
			}
			else if (ch->pcdata->questobj > 0 && ch->pcdata->countdownmq > 0)
			{
				bool obj_found = FALSE;

				for (obj = ch->first_carrying; obj != NULL; obj=obj_next)
				{
					obj_next = obj->next_content;

					if (obj != NULL && obj->pIndexData->vnum == ch->pcdata->questobj && obj->wear_loc == WEAR_NONE)
					{
						obj_found = TRUE;
						break;
					}
				}
				if (obj_found == TRUE)
				{
					int reward, pointreward, pracreward, expreward;

					reward = number_range(1000,5000);
					pointreward = number_range(5,10);
					expreward = number_range(250,500);

					act(AT_PLAIN,"You hand $p to $N.",ch, obj, questman, TO_CHAR);
					act(AT_PLAIN,"$n hands $p to $N.",ch, obj, questman, TO_ROOM);
					
					ch_printf(ch, "&CCongratulations on completing your magic quest!&w\n\r");
					ch_printf(ch,"&CAs a reward, I am giving you &W%d magic points&C, &Y%d gold&C and &P%d experience points&C!&w\n\r",
							   pointreward,reward,expreward);   
					if (number_range(1,100) <= 25)
					{
						pracreward = number_range(1,3);
						ch_printf(ch, "&CYou gain &W%d practice%s&C!&w\n\r",pracreward, pracreward > 1 ? "s" : "");
						ch->practice += pracreward;
					}

					if ( ch->pcdata->questobj > 0 )
					{ 
					   questinfoobj = get_obj_index(ch->pcdata->questobj);
						sprintf(buf, "[INFO] %s has completed a magic quest to find %s!", ch->name, questinfoobj->short_descr);
					} 
					else
					{ 
					   sprintf(buf, "[INFO] %s has completed a magic quest to find an item!", ch->name);
					} 
		 
					echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL );  //Yzek 

					xREMOVE_BIT(ch->act, PLR_MQUESTOR);
					ch->pcdata->questgiver = 0;
					ch->pcdata->countdownmq = 0;
					ch->pcdata->questmob = 0;
					ch->pcdata->questmobold = NULL;
					ch->pcdata->questobj = 0;
					if(IS_IMMORTAL(ch)) 
					   ch->pcdata->nextmquest = 0; 
					else
					   ch->pcdata->nextmquest = 5;
					ch->gold += reward;
					gain_exp( ch, expreward );
					ch->pcdata->magicpoints += pointreward;

					extract_obj(obj);
					return;
				}
				else
				{
					ch_printf(ch, "&CYou haven't completed the magic quest yet, but there is still time!&w\n\r");
					return;
				}
				return;
			}
			else if ((ch->pcdata->questmob > 0 || ch->pcdata->questobj > 0) && ch->pcdata->countdownmq > 0)
			{
				ch_printf(ch, "&CYou haven't completed the magic quest yet, but there is still time!&w\n\r");
				return;
			}
		}
		if (ch->pcdata->nextmquest > 0)
			ch_printf(ch,"&CBut you didn't complete your magic quest in time!&w\n\r");
		else 
			ch_printf(ch, "&CYou have to &WREQUEST &Ca magic quest first, %s.&w\n\r",ch->name);
		return;
    }

    send_to_char("MQUEST commands: POINTS INFO TIME REQUEST REFUSE COMPLETE.\n\r",ch);
    send_to_char("For more information, type 'HELP MQUEST'.\n\r",ch);
    return;
}
