/**************************************************************************
*									  *
* Codigo para la implementación de juegos de azar en SMAUG (version 1.4)  *
*  Desden, el Chaman Tibetano( José Luis Sogorb)  - Octubre de 1998       *
*                  Email: jose@luisso.net                                 *
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>           /* Random functions */
#include <string.h>
#include <ctype.h>
#include "mud.h"
			       /* You can set here max and min bet */
#define MAX_BET 10000      /* Max bet */                        
#define MIN_BET 100       /* Min bet */                     
#define REWARD  2*gold_bet      /* Reward for the winner */

int gold_bet;    

void do_bet( CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *gambler;
  CHAR_DATA *compet;
  char buf[MAX_STRING_LENGTH];
  char arg[MAX_INPUT_LENGTH];
  
  argument=one_argument(argument,arg);
  gold_bet = atoi(arg);

 
/* Checks there is a spec_gambler in your room */                    
  for (gambler = ch->in_room->first_person; gambler != NULL; gambler = gambler->next_in_room)
  {
   if (!IS_NPC(gambler))continue;
   if(gambler->spec_fun == spec_lookup( "spec_gambler")) break;
  }

  if (gambler == NULL || gambler->spec_fun != spec_lookup("spec_gambler"))
  {
   send_to_char ("You can't do that here!\n\r",ch);
   return;
  }

  if ( arg[0] == '\0')             /* You must bet something */
  {
   send_to_char("You must bet something.\n\r",ch);
   return;
  } 

  if (gold_bet <MIN_BET || gold_bet > MAX_BET)
  {
   sprintf(buf,"You must bet between %d gold and %d gold.\n\r",MIN_BET, MAX_BET);
   send_to_char(buf,ch);
   return;
  }

  /* Checks mob is not fighting */
  if (gambler->position == POS_FIGHTING)
  {
   send_to_char ("You can't place bets with a fighting gambler!\n\r",ch);
   return;
  }

  /* Cheks there is not another player doing a bet */
  for (compet = ch->in_room->first_person; compet != NULL; compet = compet->next_in_room)
  {
    if( xIS_SET(compet->act, PLR_GAMBLER))
     {  
      act(AT_PLAIN,"You must wait $N finishes a pending bet.",ch,NULL,gambler,TO_CHAR);
      return;
     }
   }

 /* Checks player has enough money */
  if (ch->gold < gold_bet)
  {
   sprintf(buf,"You must have %d gold coins, at least, to do bets.\n\r",gold_bet );
   send_to_char(buf,ch);
   return;
  }
   else
  {
   xSET_BIT(ch->act, PLR_GAMBLER); /* Set gambler bit in player */
   ch->gold -= gold_bet;         /* He takes away bet amount from your gold*/

   sprintf(buf,"%s puts a small piece of amber into a cup and begin to interchange them.", gambler->short_descr);
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_CHAR); 
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_ROOM);
   sprintf(buf, "The cups move so quickly that you can't follow them very well.");
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_CHAR); 
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_ROOM);
   sprintf(buf, "When finished, the cups are in their original positions, but where is the amber now??");
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_CHAR); 
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_ROOM);
   sprintf(buf,"%s, UNCOVER which cup, red, blue or green?",ch->name);
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_CHAR);
   act(AT_PLAIN,buf,ch,NULL,NULL,TO_ROOM);
   return;
 }
}

void do_uncover(CHAR_DATA *ch, char *argument)
{
  CHAR_DATA *gambler;
  int result;
  char arg[MAX_INPUT_LENGTH];
  char buf[MAX_STRING_LENGTH]; 
  
  argument=one_argument(argument,arg);
  result = number_range(1,3);           /* Chooses a random cup */           
  
/* Checks there is a spec_gambler in your room */                       
  for (gambler = ch->in_room->first_person; gambler != NULL; gambler = gambler->next_in_room)
  {
   if (!IS_NPC(gambler))continue;
   if(gambler->spec_fun == spec_lookup( "spec_gambler")) break;
  }

  if (gambler == NULL || gambler->spec_fun != spec_lookup("spec_gambler"))
  {
   send_to_char ("You can't do that here!\n\r",ch);
   return;
  }

/* Checks bet has been done */                 
  if (!xIS_SET(ch->act, PLR_GAMBLER))
  {
   send_to_char("You must bet first if you want to play.\n\r",ch);
   return;
  }

 /* Checks mob is not fighting*/              
  if (gambler->position == POS_FIGHTING)
  {
   send_to_char ("You must wait until they stop fighting.\n\r",ch);
   return;
  }

  if(!strcmp(arg,"red") || !strcmp(arg,"green") || !strcmp(arg,"blue"))
  {
     sprintf(buf,"%s bets %d gold coins and thinks the amber is in the %s cup.\n\r", ch->name, gold_bet, arg);
     act(AT_PLAIN, buf, ch, NULL, NULL, TO_CHAR);
     act(AT_PLAIN, buf, ch, NULL, NULL, TO_ROOM);

 /* Compare choosen cup with random choice */                 
     if((!strcmp(arg,"red") && result==1) || (!strcmp(arg,"green") && result==2) || (!strcmp(arg,"blue") && result==3))
     {
      sprintf(buf,"%s uncovers the indicated cup and shouts, '%s is right!'",gambler->short_descr, ch->name);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_CHAR);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_ROOM);
      sprintf(buf,"'They have just won %d gold coins.  Anyone else want to try it?'\n\r", REWARD);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_CHAR);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_ROOM); 

      ch->gold += REWARD;      /* Pay winner bet */                   
     }
     else              
     {
      sprintf(buf,"With a smile %s uncovers the indicated cup and says 'Oh, what bad luck!'",gambler->short_descr);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_CHAR);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_ROOM);
      sprintf(buf, "'I'm sorry %s, it wasn't in there. Anyone else want to try it?",ch->name);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_CHAR);
      act(AT_YELLOW,buf,ch,NULL,NULL,TO_ROOM);
     }

     xREMOVE_BIT(ch->act, PLR_GAMBLER);   /* Removes gambler bit in player */                 
  }
  else          
  { 
   act(AT_PLAIN,"$n, you must uncover one of the cups.",ch,NULL,gambler,TO_CHAR);
   return;
  }
}


