/*****************************************************
**     _________       __                           **
**     \_   ___ \_____|__| _____  ________  ___     **
**      /    \  \/_  __ \ |/     \/  ___/_ \/   \   **
**      \     \___|  | \/ |  | |  \___ \  / ) |  \  **
**       \______  /__| |__|__|_|  /____ \__/__|  /  **
**         ____\/____ _        \/ ___ \/      \/    **
**         \______   \ |_____  __| _/___            **
**          |    |  _/ |\__  \/ __ | __ \           **
**          |    |   \ |_/ __ \  / | ___/_          **
**          |_____  /__/____  /_  /___  /           **
**               \/Antipode\/  \/    \/             **
******************************************************
******************************************************
**       Copyright 2000-2003 Crimson Blade          **
******************************************************
** Contributors: Noplex, Krowe, Emberlyna, Lanthos  **
******************************************************/

/*
 * File: liquids.c
 * Name: Liquidtable Module (3.02b)
 * Author: John 'Noplex' Bellone (jbellone@comcast.net)
 * Terms:
 * If this file is to be re-disributed; you must send an email
 * to the author. All headers above the #include calls must be
 * kept intact. All license requirements must be met. License
 * can be found in the included license.txt document or on the
 * website.
 * Description:
 * This module is a rewrite of the original module which allowed for
 * a SMAUG mud to have a fully online editable liquidtable; adding liquids;
 * removing them; and editing them online. It allows an near-endless supply
 * of liquids for builder's to work with.
 * A second addition to this module allowed for builder's to create mixtures;
 * when two liquids were mixed together they would produce a different liquid.
 * Yet another adaptation to the above concept allowed for objects to be mixed
 * with liquids to produce a liquid.
 * This newest version offers a cleaner running code; smaller; and faster in
 * all ways around. Hopefully it'll knock out the old one ten fold ;)
 * Also in the upcoming 'testing' phase of this code; new additions will be added
 * including a better alchemey system for creating poitions as immortals; and as
 * mortals.
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "mud.h"

#ifdef KEY
#undef KEY
#endif
#define KEY( literal, field, value )                                    \
                                if ( !str_cmp( word, literal ) )        \
                                {                                       \
                                    field  = value;                     \
                                    fMatch = TRUE;                      \
                                    break;                              \
                                }

#ifndef FCLOSE
 #define FCLOSE(fp) fclose(fp); fp=NULL;
#endif

#ifndef NULLSTR
 #define NULLSTR(str)         (!str || str[0] == '\0')
#endif

char *const liquid_types[LIQTYPE_TOP] =
{
  "Beverage", "Alcohol", "Poison", "Blood"
};

char *const mod_types[MAX_CONDS] =
{
  "Drunk", "Full", "Thirst", "Bloodthirst"
};

/* locals */
int         top_liquid;
int         liq_count;

/* liquid i/o functions */

/* save the liquids to the liquidtable.dat file in
 * the system directory    -Nopey */
void save_liquids(void)
{
  FILE *fp = NULL;
  LIQ_TABLE *liq = NULL;
  char filename[256];
  int i;

  sprintf(filename, "%sliquidtable.dat", SYSTEM_DIR);
  if((fp = fopen(filename, "w")) == NULL)
  {
    bug("save_liquids(): cannot open %s for writing", filename);
    return;
  }

  fprintf(fp, "#VERSION 3\n");
  for(i = 0; i <= top_liquid; i++)
  {
    liq = liquid_table[i];

    fprintf(fp, "#LIQUID\n");
    fprintf(fp, "Name              %s~\n", liq->name);
    fprintf(fp, "Shortdesc         %s~\n", liq->shortdesc);
    fprintf(fp, "Color             %s~\n", liq->color);
    fprintf(fp, "Type              %d\n", liq->type);
    fprintf(fp, "Vnum              %d\n", liq->vnum);
    fprintf(fp, "Mod      %d %d %d %d\n", liq->mod[COND_DRUNK], liq->mod[COND_FULL], liq->mod[COND_THIRST], liq->mod[COND_BLOODTHIRST]);
    fprintf(fp, "End\n");
   }
  fprintf(fp, "#END\n");
  FCLOSE(fp);
  return;
}

/* load the liquids from the liquidtable.dat file in the
 * system directory -Nopey */
void load_liquids(void)
{
  FILE *fp = NULL;
  char filename[256];
  int file_version = 0;

  sprintf(filename, "%sliquidtable.dat", SYSTEM_DIR);
  if((fp = fopen(filename, "r")) == NULL)
  {
    bug("load_liquids(): cannot open %s for reading", filename);
    return;
  }

  top_liquid = -1;
  liq_count  = -1;

  for( ; ; )
  {
    char letter = fread_letter(fp);
    char *word;

    if(letter == '*')
    {
      fread_to_eol(fp);
      continue;
    }

    if(letter != '#')
    {
      bug("load_liquids(): # not found (%c)", letter);
      return;
    }

    word = fread_word(fp);
    if(!str_cmp(word, "VERSION"))
    {
      file_version = fread_number(fp);
      continue;
    }
    else
    if(!str_cmp(word, "LIQUID"))
    {
      LIQ_TABLE *liq = fread_liquid(fp);

      //log_string("debugger: 6"); -Darwin
      if(!liq)
       bug("load_liquids(): returned NULL liquid");
      else
      {
       static char logger[1024];
       sprintf(logger, "debugger: added liquid %s(%d) to table", liq->name, liq->vnum);
       //log_string(logger); -Darwin
       liquid_table[liq->vnum] = liq;
       if(liq->vnum > top_liquid)
        top_liquid = liq->vnum;
       liq_count++;
      }
      continue;
    }
    else
    if(!str_cmp(word, "END"))
     break;
    else
    {
      bug("load_liquids(): no match for %s", word);
      continue;
    }
  }
  FCLOSE(fp);
  return;
}

/* read the liquids from a file descriptor and then
 * distribute them accordingly to the struct   -Nopey */
LIQ_TABLE *fread_liquid(FILE *fp)
{
  LIQ_TABLE *liq = NULL;
  bool fMatch = FALSE;
  int i;

  CREATE(liq, LIQ_TABLE, 1);
  liq->name              = STRALLOC("None");
  liq->color             = STRALLOC("None");
  liq->shortdesc         = STRALLOC("None");
  liq->vnum              = -1;
  liq->type              = -1;
  for(i = 0; i < MAX_CONDS; i++)
   liq->mod[i]           = -1;

  for( ; ; )
  {
    char *word = feof(fp) ? "End" : fread_word(fp);

    switch(UPPER(word[0]))
    {
      case '*':
       fread_to_eol(fp);
      break;

      case 'C':
       KEY("Color", liq->color, fread_string(fp));
      break;

      case 'E':
       if(!str_cmp(word, "End"))
       {
         if(liq->vnum <= -1)
          return NULL;
         return liq;
       }
      break;

      case 'N':
       KEY("Name", liq->name, fread_string(fp));
      break;

      case 'M':
       if(!str_cmp(word, "Mod"))
       {
         liq->mod[COND_DRUNK]        = fread_number(fp);
         liq->mod[COND_FULL]         = fread_number(fp);
         liq->mod[COND_THIRST]       = fread_number(fp);
         liq->mod[COND_BLOODTHIRST]  = fread_number(fp);
       }
      break;

      case 'S':
       KEY("Shortdesc", liq->shortdesc, fread_string(fp));
      break;

      case 'T':
       KEY("Type", liq->type, fread_number(fp));
      break;

      case 'V':
       KEY("Vnum", liq->vnum, fread_number(fp));
      break;
    }

    if(!fMatch)
     bug("fread_liquids(): no match for %s", word);
  }
  /* something went wrong if it gets here */
  return NULL;
}

/* save the mixtures to the mixture table -Nopey */
void save_mixtures(void)
{
  MIX_TABLE *mix = NULL;
  FILE *fp = NULL;
  char filename[256];

  sprintf(filename, "%smixturetable.dat", SYSTEM_DIR);
  if((fp = fopen(filename, "w")) == NULL)
  {
    bug("save_mixtures(): cannot open %s for writing", filename);
    return;
  }

  fprintf(fp, "%s", "#VERSION 3\n");
  for(mix = first_mixture; mix; mix = mix->next)
  {
    fprintf(fp, "%s", "#MIXTURE\n");
    fprintf(fp, "Name           %s~\n", mix->name);
    fprintf(fp, "Data      %d %d %d\n", mix->data[0], mix->data[1], mix->data[2]);
    fprintf(fp, "Object         %d\n", mix->object);
    fprintf(fp, "End\n");
  }
  fprintf(fp, "%s", "#END\n");
  FCLOSE(fp);
  return;
}

/* load the mixtures from the mixture table         -Nopey */
void load_mixtures(void)
{
  FILE *fp = NULL;
  char filename[256];
  static int file_version = 0;

  sprintf(filename, "%smixturetable.dat", SYSTEM_DIR);
  if((fp = fopen(filename, "r")) == NULL)
  {
    bug("load_mixtures(): cannot open %s for reading", filename);
    return;
  }

  for( ;; )
  {
    char letter = fread_letter(fp);
    char *word;

    if(letter == '*')
    {
      fread_to_eol(fp);
      continue;
    }

    if( letter != '#' )
    {
      bug("load_mixtures(): # not found (%c)", letter);
      return;
    }

    word = fread_word(fp);
    if( !str_cmp(word, "VERSION") )
    {
      file_version = fread_number(fp);
      continue;
    }
    else if( !str_cmp(word, "MIXTURE") )
    {
      MIX_TABLE *mix = NULL;

      mix = fread_mixture(fp);
      if(!mix)
         bug("load_mixtures(): mixture returned NULL");
      else
         LINK(mix, first_mixture, last_mixture, next, prev);
    }
    else if(!str_cmp(word, "END"))
     break;
    else
    {
      bug("load_mixtures(): no match for %s", word);
      break;
    }
  }
  FCLOSE(fp);
  return;
}

/* read the mixtures into the structure -Nopey */
MIX_TABLE *fread_mixture(FILE *fp)
{
  MIX_TABLE *mix = NULL;
  bool fMatch = FALSE;

  CREATE(mix, MIX_TABLE, 1);
  mix->data[0]           = -1;
  mix->data[1]           = -1;
  mix->data[2]           = -1;
  mix->object            = FALSE;

  for( ;; )
  {
    char *word = feof(fp) ? "End" : fread_word(fp);

    switch(UPPER(word[0]))
    {
      case '*':
       fread_to_eol(fp);
      break;

      case 'D':
       if(!str_cmp(word, "Data"))
       {
         mix->data[0]    = fread_number(fp);
         mix->data[1]    = fread_number(fp);
         mix->data[2]    = fread_number(fp);
       }
      break;

      case 'E':
       if(!str_cmp(word, "End"))
       {
         return mix;
       }
      break;

      case 'I':
         KEY("Into", mix->data[2], fread_number(fp));
        break;

      case 'N':
       KEY("Name", mix->name, fread_string(fp));
      break;

      case 'O':
       KEY("Object", mix->object, fread_number(fp));
      break;

       case 'W':
        if(!str_cmp(word, "With"))
        {
          mix->data[0] = fread_number(fp);
          mix->data[1] = fread_number(fp);
        }
       break;
    }

    if(!fMatch)
     bug("fread_mixture(): no match for %s", word);
  }
  /* something went wrong if it gets here */
  return NULL;
}

/* figure out a vnum for the next liquid  -Nopey */
static int figure_liq_vnum(void)
{
  int i;

  /* incase a liquid gets removed; we can fill it's place */
  for(i=0; liquid_table[i] != NULL; i++);

  /* add to the top */
  if(i > top_liquid)
   top_liquid = i;

  return i;
}

/* lookup func for liquids      -Nopey */
LIQ_TABLE *get_liq(char *str)
{
  int i;

  if(is_number(str))
  {
    i = atoi(str);

    return liquid_table[i];
  }
  else
  {
    for(i = 0; i <= top_liquid; i++)
     if(!str_cmp(liquid_table[i]->name, str))
      return liquid_table[i];
  }
  return NULL;
}

LIQ_TABLE *get_liq_vnum(int vnum)
{
  return liquid_table[vnum];
}

/* lookup func for mixtures      -Nopey */
MIX_TABLE *get_mix(char *str)
{
  MIX_TABLE *mix = NULL;

  for(mix = first_mixture; mix; mix = mix->next)
   if(!str_cmp(mix->name, str))
    return mix;

  return NULL;
}

/* olc function for liquids   -Nopey */
void do_setliquid(CHAR_DATA *ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];

  if(!IS_IMMORTAL(ch) || IS_NPC(ch))
  {
    send_to_char("Huh?\n\r", ch);
    return;
  }

  argument = one_argument(argument, arg);
  if(NULLSTR(arg))
  {
    send_to_char("Syntax: setliquid <vnum> <field> <value>\n\r"
                 "        setliquid list [vnum]\n\r"
                 "        setliquid create <name>\n\r"
                 "        setliquid delete <vnum>\n\r"
		 "	  setliquid save/load\n\r", ch);
    send_to_char(" Fields being one of the following:\n\r"
                 " name color type shortdesc drunk thrist blood full\n\r", ch);
    return;
  }

  if(!str_cmp(arg, "save"))
  {
     save_liquids();
     send_to_char("Ok.\n\r", ch);
     return;
  }

  if(!str_cmp(arg, "load"))
  {
     load_liquids();
     send_to_char("Ok.\n\r", ch);
     return;
  }

  if(!str_cmp(arg, "list"))
  {
    LIQ_TABLE *liq = NULL;
    int i;

    if(!liquid_table[0])
    {
      send_to_char("There is currently no liquids loaded.\n\r", ch);
      send_to_char("WARNING:\n\rHaving no liquids loaded will result in no drinks providing\n\r"
                               "nurishment. This iQncludes water. The default set of liquids\n\r"
                               "should always be backed up.\n\r", ch);
      return;
    }

    if(!NULLSTR(argument) && ((liq = get_liq(argument)) != NULL))
    {
      if(!NULLSTR(liq->name))
       pager_printf_color(ch, "&GLiquid information for:&g %s\n\r", liq->name);
      if(!NULLSTR(liq->shortdesc))
       pager_printf_color(ch, "&GLiquid shortdesc:&g\t %s\n\r", liq->shortdesc);
      if(!NULLSTR(liq->color))
       pager_printf_color(ch, "&GLiquid color:&g\t %s\n\r", liq->color);
      pager_printf_color(ch, "&GLiquid vnum:&g\t %d\n\r", liq->vnum);
      pager_printf_color(ch, "&GLiquid type:&g\t %s\n\r", liquid_types[liq->type]);
      pager_printf_color(ch, "&GLiquid Modifiers\n\r");
       for(i = 0; i < MAX_CONDS; i++)
        if(liquid_table[i])
         pager_printf_color(ch, "&G%s:&g\t %d\n\r", mod_types[i], liq->mod[i]);
      return;
    }
    else if(!NULLSTR(argument) && ((liq = get_liq(argument)) == NULL))
    {
      send_to_char("Invaild liquid-vnum.\n\rUse 'setliquid list' to gain a vaild liquidvnum.\n\r", ch);
      return;
    }

    pager_printf_color(ch, "&G[&gVnum&G] [&gName&G]\n\r");
    for(i = 0; i <= top_liquid; i++)
     pager_printf_color(ch, "  %-7d %s\n\r", liquid_table[i]->vnum, liquid_table[i]->name);

    send_to_char("\n\rUse 'setliquid list [vnum]' to view individual liquids.\n\r", ch);
    send_to_char("Use 'setmixture list' to view the mixturetable.\n\r", ch);
    return;
  }
  else
  if(!str_cmp(arg, "create"))
  {
    LIQ_TABLE *liq = NULL;
    int i;

    if(liq_count >= MAX_LIQUIDS)
    {
      send_to_char("Liquid count is at the hard-coded max. Remove some liquids or raise\n\r"
                   "the hard-coded max number of liquids.\n\r", ch);
      return;
    }

    if(NULLSTR(argument))
    {
      send_to_char("Syntax: setliquid create <name>\n\r", ch);
      return;
    }

    CREATE(liq, LIQ_TABLE, 1);
    liq->name              = STRALLOC(argument);
    liq->color             = STRALLOC("");
    liq->shortdesc         = STRALLOC(argument);
    liq->vnum              = figure_liq_vnum( );
    liq->type              = 0;
    for(i = 0; i < MAX_CONDS; i++)
     liq->mod[i]           = 0;
    liquid_table[liq->vnum] = liq;
    liq_count++;
    send_to_char("Done.\n\r", ch);
    save_liquids( );
    return;
  }
  else if(!str_cmp(arg, "delete"))
  {
    LIQ_TABLE *liq = NULL;
    int i = atoi(argument);

    if(NULLSTR(argument))
    {
      send_to_char("Syntax: setliquid delete <vnum>\n\r", ch);
      return;
    }

    if((liq = get_liq_vnum(i)) == NULL)
    {
      send_to_char("No such vnum. Use 'setliquid list' to gain the vnums.\n\r", ch);
      return;
    }

    if(!NULLSTR(liq->name))
     STRFREE(liq->name);
    if(!NULLSTR(liq->color))
     STRFREE(liq->color);
    if(!NULLSTR(liq->shortdesc))
     STRFREE(liq->shortdesc);
    if(liq->vnum >= top_liquid)
    {
      int j;

       for(j = 0; j != liq->vnum; j++)
        if(j > top_liquid)
         top_liquid = j;
    }
    liquid_table[liq->vnum] = NULL;
    liq_count--;
    DISPOSE(liq);
    send_to_char("Done.\n\r", ch);
    save_liquids( );
    return;
  }
  else
  {
    char arg2[MAX_INPUT_LENGTH];
    LIQ_TABLE *liq = NULL;

    argument = one_argument(argument, arg2);
    if(NULLSTR(arg2))
    {
      send_to_char("Syntax: setliquid <vnum> <field> <value>\n\r", ch);
      send_to_char(" Fields being one of the following:\n\r"
                   " name color shortdesc drunk thrist blood full\n\r", ch);
      return;
    }

    if((liq = get_liq(arg)) == NULL)
    {
      send_to_char("Invaild liquid-name or vnum.\n\r", ch);
      return;
    }

    if(!str_cmp(arg2, "name"))
    {
      if(NULLSTR(argument))
      {
        send_to_char("Syntax: setliquid <vnum> name <name>\n\r", ch);
        return;
      }
      liq->name               = STRALLOC(argument);
    }
    else
    if(!str_cmp(arg2, "color"))
    {
      if(NULLSTR(argument))
      {
        send_to_char("Syntax: setliquid <vnum> color <color>\n\r", ch);
        return;
      }
      liq->color               = STRALLOC(argument);
    }
    else
    if(!str_cmp(arg2, "shortdesc"))
    {
      if(NULLSTR(argument))
      {
        send_to_char("Syntax: setliquid <vnum> shortdesc <shortdesc>\n\r", ch);
        return;
      }
      liq->shortdesc              = STRALLOC(argument);
    }
    else if(!str_cmp(arg2, "type"))
    {
      char arg3[MAX_INPUT_LENGTH];
      int i;
      bool found = FALSE;

      argument = one_argument(argument, arg3);

      /* bah; forgot to add this shit -- */
      for(i = 0; i < LIQTYPE_TOP; i++)
       if(!str_cmp(arg3, liquid_types[i]))
       {
         found = TRUE;
         liq->type       = i;
       }
      if(!found)
      {
        send_to_char("Syntax: setliquid <vnum> type <liquidtype>\n\r", ch);
        return;
      }
    }
    else
    {
     int i;
     bool found = FALSE;
     static char * const arg_names[MAX_CONDS] =
     { "drunk", "full", "thirst", "blood" };

     if(NULLSTR(argument))
     {
       send_to_char("Syntax: setliquid <vnum> <field> <value>\n\r", ch);
       send_to_char(" Fields being one of the following:\n\r"
                    " name color shortdesc drunk thrist blood full\n\r", ch);
       return;
     }

     for(i = 0; i < MAX_CONDS; i++)
      if(!str_cmp(arg2, arg_names[i]))
      {
        found = TRUE;
        liq->mod[i]           = atoi(argument);
      }
     if(!found)
     {
      do_setliquid(ch, "");
      return;
     }
    }
    send_to_char("Done.\n\r", ch);
    save_liquids( );
    return;
  }
}

/* olc funciton for mixtures  -Nopey */
void do_setmixture(CHAR_DATA *ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];

  if(!IS_IMMORTAL(ch) || IS_NPC(ch))
  {
    send_to_char("Huh?\n\r", ch);
    return;
  }

  argument = one_argument(argument, arg);
  if(NULLSTR(arg))
  {
    send_to_char("Syntax: setmixture create <name>\n\r"
                 "        setmixture delete <name>\n\r"
                 "        setmixture list [name]\n\r"
                 "        setmixture <name> <field> <value>\n\r"
	         "	  setmixture save/load\n\r", ch);
    send_to_char(" Fields being one of the following:\n\r"
                 " name vnum1 vnum2 into object\n\r", ch);
    return;
  }

  if(!str_cmp(arg, "load"))
  {
    load_mixtures();
    send_to_char( "Ok.\n\r", ch );
    return;
  }

  if(!str_cmp(arg, "save"))
  {
    save_mixtures();
    send_to_char( "Ok.\n\r", ch );
    return;
  }


  if(!str_cmp(arg, "list"))
  {
    MIX_TABLE *mix = NULL;

    if(!NULLSTR(argument) && ((mix = get_mix(argument)) != NULL))
    {
     if(!mix->object)
      pager_printf_color(ch,
      "&G%s&g mixes with two liquids; &G%d&g and &G%d&g\n\r", mix->name, mix->data[0], mix->data[1]);
     else
      pager_printf_color(ch,
      "&G%s&g mixes with one object; &G%d&g; and one liquid, &G%d&g\n\r", mix->name, mix->data[0], mix->data[1]);

     pager_printf_color(ch, "&G%s&g mixes into liquid &G%d&g\n\r", mix->name, mix->data[2]);
     return;
    }
    else if(!NULLSTR(argument) && ((mix = get_mix(argument)) == NULL))
    {
      send_to_char("Invaild mixture-name.\n\rUse 'setmixture list' to gain a vaild name.\n\r", ch);
      return;
    }

    if(!first_mixture)
    {
      send_to_char("There is currently no mixtures loaded.\n\r", ch);
      return;
    }

    /* BUGFIX - thanks to Samson */
    send_to_pager_color("&G[&gType&G] &G[&gName&G]\n\r", ch);
    for(mix = first_mixture; mix; mix = mix->next)
     pager_printf_color(ch, "  %-8s %s\n\r", mix->object ? "Object" : "Liquids", mix->name);

    pager_printf_color(ch, "\n\rUse 'setmixture list [name]' to view individual mixtures.\n\r");
    pager_printf_color(ch, "Use 'setliquid list' to view the liquidtable.\n\r");
    return;
  }
  else
  if(!str_cmp(arg, "create"))
  {
    MIX_TABLE *mix = NULL;

    if(NULLSTR(argument))
    {
      send_to_char("Syntax: setmixture create <name>\n\r", ch);
      return;
    }

    CREATE(mix, MIX_TABLE, 1);
    mix->name              = STRALLOC(argument);
    mix->data[0]           = -1;
    mix->data[1]           = -1;
    mix->data[2]           = -1;
    mix->object            = FALSE;
    LINK(mix, first_mixture, last_mixture, next, prev);
    send_to_char("Done.\n\r", ch);
    save_mixtures( );
    return;
  }
  else if(!str_cmp(arg, "delete"))
  {
    MIX_TABLE *mix = NULL;

    if(NULLSTR(argument))
    {
      send_to_char("Syntax: setmixture delete <name>\n\r", ch);
      return;
    }

    if((mix = get_mix(argument)) == NULL)
    {
      send_to_char("That's not a mixture name.\n\r", ch);
      return;
    }

    UNLINK(mix, first_mixture, last_mixture, next, prev);
    if(!NULLSTR(mix->name))
     STRFREE(mix->name);
    DISPOSE(mix);
    send_to_char("Done.\n\r", ch);
    save_mixtures( );
    return;
  }
  else
  {
    char arg2[MAX_INPUT_LENGTH];
    MIX_TABLE *mix = NULL;

    if(NULLSTR(arg) || ((mix = get_mix(arg)) == NULL))
    {
      send_to_char("Syntax: setmixture <mixname> <field> <value>\n\r", ch);
      send_to_char(" Fields being one of the following:\n\r"
                   " name vnum1 vnum2 into object\n\r", ch);
      return;
    }

    argument = one_argument(argument, arg2);

    if(!str_cmp(arg2, "name"))
    {
      if(NULLSTR(argument))
      {
        send_to_char("Syntax: setmixture <mixname> name <name>\n\r", ch);
        return;
      }
      mix->name               = STRALLOC(argument);
    }
    else if(!str_cmp(arg2, "vnum1"))
    {
      int i = atoi(argument);

      if(NULLSTR(argument))
      {
        send_to_char("Syntax: setmixture <mixname> vnum1 <liqvnum>\n\r", ch);
        return;
      }
      mix->data[0]            = i;
    }
    else if(!str_cmp(arg2, "vnum2"))
    {
      int i = atoi(argument);

      if(NULLSTR(argument))
      {
        send_to_char("Syntax: setmixture <mixname> vnum2 <liqvnum>\n\r", ch);
        return;
      }
      mix->data[1]            = i;
    }
    else if(!str_cmp(arg2, "object"))
    {
      mix->object = !mix->object;
      if(mix->object)
       send_to_char("Mixture -vnum2- is now an object-vnum.\n\r", ch);
      else
       send_to_char("Both mixture vnums are now liquids.\n\r", ch);
    }
    else if(!str_cmp(arg2, "into"))
    {
      int i = atoi(argument);

      if(NULLSTR(argument))
      {
        send_to_char("Syntax: setmixture <mixname> into <liqvnum>\n\r", ch);
        return;
      }
      mix->data[2]            = i;
    }
    send_to_char("Done.\n\r", ch);
    save_mixtures( );
    return;
  }
}

/* the actual -mix- funciton  -Nopey */
void do_mix(CHAR_DATA *ch, char *argument)
{
  char arg[MAX_INPUT_LENGTH];
  OBJ_DATA *iObj, *tObj = NULL;

  argument = one_argument(argument, arg);
  /* null arguments */
  if(NULLSTR(arg) || NULLSTR(argument))
  {
    send_to_char("What would you like to mix together?\n\r", ch);
    return;
  }

  /* check for objects in the inventory */
  if(((iObj = get_obj_carry(ch, arg)) == NULL) || ((tObj = get_obj_carry(ch, argument)) == NULL))
  {
    send_to_char("You aren't carrying that.\n\r", ch);
    return;
  }

  /* check itemtypes */
  if((iObj->item_type != ITEM_DRINK_CON && iObj->item_type != ITEM_DRINK_MIX)
   || (tObj->item_type != ITEM_DRINK_CON && tObj->item_type != ITEM_DRINK_MIX))
   {
     send_to_char("You can't mix that!\n\r", ch);
     return;
   }

  /* check to see if it's empty or not */
  if(iObj->value[1] <= 0 || tObj->value[1] <= 0)
  {
    send_to_char("It's empty.\n\r", ch);
    return;
  }

  /* two liquids */
  if(iObj->item_type == ITEM_DRINK_CON && tObj->item_type == ITEM_DRINK_CON)
  {
    /* check to see if the two liquids can be mixed together
     * and return the final liquid -Nopey */
    if(!liq_can_mix(iObj, tObj))
    {
      send_to_char("Those two don't mix well together.\n\r", ch);
      return;
    }
  }
  else if(iObj->item_type == ITEM_DRINK_MIX && tObj->item_type == ITEM_DRINK_CON)
  {
    if(!liqobj_can_mix(tObj, iObj))
    {
      send_to_char("Those two don't mix well together.\n\r", ch);
      return;
    }
  }
  else if(iObj->item_type == ITEM_DRINK_CON && tObj->item_type == ITEM_DRINK_MIX)
  {
    if(!liqobj_can_mix(iObj, tObj))
    {
      send_to_char("Those two don't mix well together.\n\r", ch);
      return;
    }
  }
  else
  {
    send_to_char("Those two don't mix well together.\n\r", ch);
    return;
  }
  send_to_char_color("&cYou mix them together.&g\n\r", ch);
  return;
}

/* mix a liquid with a liquid; return the final product    -Nopey */
LIQ_TABLE *liq_can_mix(OBJ_DATA *iObj, OBJ_DATA *tObj)
{
  MIX_TABLE *mix = NULL;
  bool mix_found = FALSE;

  for(mix = first_mixture; mix; mix = mix->next)
   if(mix->data[0] == iObj->value[2] || mix->data[1] == iObj->value[2])
   {
     mix_found = TRUE;
     break;
   }

  if(!mix_found)
   return NULL;

  if(mix->data[2] > -1)
  {
    LIQ_TABLE *liq = NULL;

    if((liq = get_liq_vnum(mix->data[2])) == NULL)
     return NULL;
    else
    {
      iObj->value[1]        += tObj->value[1];
      iObj->value[2]        = liq->vnum;
      tObj->value[1]        = 0;
      tObj->value[2]        = -1;
      return liq;
    }
  }
  return NULL;
}

/* used to mix an object with a liquid to form
 * another liquid; returns the result  -Nopey */
LIQ_TABLE *liqobj_can_mix(OBJ_DATA *iObj, OBJ_DATA *oLiq)
{
  MIX_TABLE *mix = NULL;
  bool mix_found = FALSE;

  for(mix = first_mixture; mix; mix = mix->next)
   if(mix->object && (mix->data[0] == iObj->value[2] || mix->data[1] == iObj->value[2]))
    if(mix->data[0] == oLiq->value[2] || mix->data[1] == oLiq->value[2])
    {
      mix_found = TRUE;
      break;
    }

  if(!mix_found)
   return NULL;

  if(mix->data[2] > -1)
  {
    LIQ_TABLE *liq = NULL;

    if((liq = get_liq_vnum(mix->data[2])) == NULL)
     return NULL;
    else
    {
      oLiq->value[1]        += iObj->value[1];
      oLiq->value[2]        = liq->vnum;
      obj_from_char(iObj);
      extract_obj(iObj);
      return liq;
    }
  }
  return NULL;
}

/* modified do_drink function -Nopey */
void do_drink( CHAR_DATA *ch, char *argument )
{
   char arg[MAX_INPUT_LENGTH];
   OBJ_DATA *obj;
   AFFECT_DATA af;
   int amount;


   argument = one_argument( argument, arg );
   
   /* munch optional words */
   if ( !str_cmp( arg, "from" ) && argument[0] != '\0' )
        argument = one_argument( argument, arg );

   if ( arg[0] == '\0' )
   {
        for ( obj = ch->in_room->first_content; obj; obj = obj->next_content )
           if( obj->item_type == ITEM_FOUNTAIN )
                break;

        if ( !obj )
        {
           send_to_char( "Drink what?\n\r", ch );
           return;
        }
   }

   else
   {
        if ( ( obj = get_obj_here( ch, arg ) ) == NULL )
        {
           send_to_char( "You can't find it.\n\r", ch );
           return;
        }
   }

   if ( obj->count > 1 && obj->item_type != ITEM_FOUNTAIN )
        separate_obj( obj );

   if ( !IS_NPC(ch) && ch->pcdata->condition[COND_DRUNK] > MAX_COND_VALUE - 8 )
   {
        send_to_char( "You fail to reach your mouth.  *Hic*\n\r", ch );
        return;
   }

   switch ( obj->item_type )
   {
        default:
           if ( obj->carried_by == ch )
           {
              act( AT_ACTION, "$n lifts $p up to $s mouth and tries to drink from it...", ch, obj, NULL, TO_ROOM );
              act( AT_ACTION, "You bring $p up to your mouth and try to drink from it...", ch, obj, NULL, TO_CHAR );
           }
           else
           {
              act( AT_ACTION, "$n gets down and tries to drink from $p... (Is $e feeling ok?)", ch, obj, NULL, TO_ROOM );
              act( AT_ACTION, "You get down on the ground and try to drink from $p...", ch, obj, NULL, TO_CHAR );
           }
           break;

    case ITEM_BLOOD:
        send_to_char( "It is not in your nature to do such things.\n\r", ch );
        break;

      case ITEM_POTION:
           if ( obj->carried_by == ch )
              do_quaff( ch, obj->name );
           else
              send_to_char( "You're not carrying that.\n\r", ch );
           break;

      case ITEM_FOUNTAIN:
      {
        LIQ_TABLE *liq = NULL;

        if(obj->value[1] <= 0)
         obj->value[1] = MAX_COND_VALUE;

         if((liq = get_liq_vnum(obj->value[2])) == NULL)
         {
           bug( "Do_drink: bad liquid number %d.", obj->value[2] );
           liq = get_liq_vnum( 0 );
         }

         if(!IS_NPC(ch) && obj->value[2] != 0)
         {
             gain_condition(ch, COND_THIRST, liq->mod[COND_THIRST]);
             gain_condition(ch, COND_FULL, liq->mod[COND_FULL]);
             gain_condition(ch, COND_DRUNK, liq->mod[COND_DRUNK]);
         }
         else if(!IS_NPC(ch) && obj->value[2] == 0)
           ch->pcdata->condition[COND_THIRST] = 100;

         if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
         {
            act( AT_ACTION, "$n drinks from the fountain.", ch, NULL, NULL, TO_ROOM );
            send_to_char( "You take a long thirst quenching drink.\n\r", ch );
         }
         break;
      }

      case ITEM_DRINK_CON:
      {
        LIQ_TABLE *liq = NULL;

           if( obj->value[1] == 0 ) // Changed from <= to allow endless drink containers -Darwin
           {
              send_to_char( "It is already empty.\n\r", ch );
              return;
           }

           /* allow water to be drank; but nothing else on a full stomach     -Nopey */
           /* added is_npc check; thanks to Olcerin */
		   /* removed full stomach check -Darwin */
//            if(!IS_IMMORTAL(ch) && !IS_NPC(ch) && (ch->pcdata->condition[COND_THIRST] == MAX_COND_VALUE || ch->pcdata->condition[COND_FULL] == MAX_COND_VALUE))
            if(!IS_IMMORTAL(ch) && !IS_NPC(ch) && (ch->pcdata->condition[COND_THIRST] > MAX_COND_VALUE ))
            {
              send_to_char( "You cannot drink anymore!\n\r", ch );
              return;
            }

           if ( ( liq = get_liq_vnum(obj->value[2]) ) == NULL )
           {
              bug( "Do_drink: bad liquid number %d.", obj->value[2] );
              liq = get_liq_vnum( 0 );
           }

           if ( !oprog_use_trigger( ch, obj, NULL, NULL, NULL ) )
           {
              act( AT_ACTION, "$n drinks $T from $p.", ch, obj, liq->shortdesc, TO_ROOM );
              act( AT_ACTION, "You drink $T from $p.", ch, obj, liq->shortdesc, TO_CHAR );
           }

           amount = 1; /* UMIN(amount, obj->value[1]); */

           /* gain conditions accordingly              -Nopey */
           gain_condition( ch, COND_DRUNK,  liq->mod[COND_DRUNK] );
           //gain_condition( ch, COND_FULL,   liq->mod[COND_FULL] ); // removed by Darwin
           gain_condition( ch, COND_THIRST, liq->mod[COND_THIRST] );
         
		 // IS_IMMORTAL check added by -Darwin
         if( liq->type == LIQTYPE_POISON && !IS_IMMORTAL(ch) )
         {
              act( AT_POISON, "$n sputters and gags.", ch, NULL, NULL, TO_ROOM );
              act( AT_POISON, "You sputter and gag.", ch, NULL, NULL, TO_CHAR );
              ch->mental_state = URANGE( 20, ch->mental_state + 5, 100 );
              af.type      = gsn_poison;
              af.duration  = obj->value[3];
              af.location  = APPLY_NONE;
              af.modifier  = 0;
              af.bitvector = meb(AFF_POISON);
              affect_join( ch, &af );
         }

         if( !IS_NPC(ch) && !IS_IMMORTAL(ch) )
         {
              if( ch->pcdata->condition[COND_DRUNK] > ( MAX_COND_VALUE / 2 ) && ch->pcdata->condition[COND_DRUNK] < ( MAX_COND_VALUE * .4 ) )
                   send_to_char( "You feel quite sloshed.\n\r", ch );
              else if( ch->pcdata->condition[COND_DRUNK] >= ( MAX_COND_VALUE * .4 ) && ch->pcdata->condition[COND_DRUNK] < ( MAX_COND_VALUE * .6 ) )
                   send_to_char( "You start to feel a little drunk.\n\r", ch );
              else if( ch->pcdata->condition[COND_DRUNK] >= ( MAX_COND_VALUE * .6 ) && ch->pcdata->condition[COND_DRUNK] < ( MAX_COND_VALUE * .9 ) )
                   send_to_char( "Your vision starts to get blurry.\n\r", ch );
              else if( ch->pcdata->condition[COND_DRUNK] >= ( MAX_COND_VALUE * .9 ) && ch->pcdata->condition[COND_DRUNK] < MAX_COND_VALUE )
                   send_to_char( "You feel very drunk.\n\r", ch );
              else if( ch->pcdata->condition[COND_DRUNK] == MAX_COND_VALUE )
                   send_to_char( "You feel like you're going to pass out.\n\r", ch );

              if( ch->pcdata->condition[COND_THIRST] > ( MAX_COND_VALUE / 2 ) && ch->pcdata->condition[COND_THIRST] < ( MAX_COND_VALUE * .4 ) )
                   send_to_char( "Your are no longer thirsty.\n\r", ch );
              else if( ch->pcdata->condition[COND_THIRST] >= ( MAX_COND_VALUE * .4 ) && ch->pcdata->condition[COND_THIRST] < ( MAX_COND_VALUE * .6 ) )
                   send_to_char( "You start to feel a little bloated.\n\r", ch );
              else if( ch->pcdata->condition[COND_THIRST] >= ( MAX_COND_VALUE * .6 ) && ch->pcdata->condition[COND_THIRST] < ( MAX_COND_VALUE * .9 ) )
                   send_to_char( "You start to feel pretty bloated.\n\r", ch );
              else if( ch->pcdata->condition[COND_THIRST] >= ( MAX_COND_VALUE * .9 ) && ch->pcdata->condition[COND_THIRST] < MAX_COND_VALUE )
                   send_to_char( "Your stomach is almost filled to it's brim!\n\r", ch );
              else if( ch->pcdata->condition[COND_THIRST] == MAX_COND_VALUE)
                   send_to_char( "Your stomach is full, you can't manage to get anymore down.\n\r", ch );
         }
         if(!IS_IMMORTAL(ch))
 	 {
           if(obj->value[1] > 0) obj->value[1] -= amount; // don't change if container is "endless" -Darwin
	 }
           if ( obj->value[1] == 0 ) /* Come now, what good is a drink container that vanishes?? */
           {
              obj->value[1] = 0; /* Prevents negative values - Samson */
              ch_printf(ch, "You drink the last drop from %s.\n\r", obj->short_descr );
              if ( cur_obj == obj->serial )
                 global_objcode = rOBJ_DRUNK;
              /* extract_obj( obj );      Modified 4-21-98 - Samson */
           }
           break;
      }
   }

   if ( who_fighting( ch ) && IS_PKILL( ch ) )
      WAIT_STATE( ch, PULSE_PER_SECOND/3 );
   else
      WAIT_STATE( ch, PULSE_PER_SECOND );
   return;
}

/* standard liquid functions           -Nopey */
void do_fill( CHAR_DATA *ch, char *argument )
{
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];
    OBJ_DATA *obj;
    OBJ_DATA *source;
    sh_int    dest_item, src_item1, src_item2, src_item3;
    int       diff = 0;
    bool      all = FALSE;

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );

    /* munch optional words */
    if ( (!str_cmp( arg2, "from" ) || !str_cmp( arg2, "with" ))
    &&    argument[0] != '\0' )
        argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' )
    {
        send_to_char( "Fill what?\n\r", ch );
        return;
    }

    if ( ms_find_obj(ch) )
        return;

    if ( ( obj = get_obj_carry( ch, arg1 ) ) == NULL )
    {
        send_to_char( "You do not have that item.\n\r", ch );
        return;
    }
    else
        dest_item = obj->item_type;

    src_item1 = src_item2 = src_item3 = -1;
    switch( dest_item )
    {
        default:
          act( AT_ACTION, "$n tries to fill $p... (Don't ask me how)", ch, obj, NULL, TO_ROOM );
          send_to_char( "You cannot fill that.\n\r", ch );
          return;
        /* place all fillable item types here */
        case ITEM_DRINK_CON:
          src_item1 = ITEM_FOUNTAIN;    src_item2 = ITEM_BLOOD;         break;
        case ITEM_HERB_CON:
          src_item1 = ITEM_HERB;        src_item2 = ITEM_HERB_CON;      break;
        case ITEM_PIPE:
          src_item1 = ITEM_HERB;        src_item2 = ITEM_HERB_CON;      break;
        case ITEM_CONTAINER:
          src_item1 = ITEM_CONTAINER;   src_item2 = ITEM_CORPSE_NPC;
          src_item3 = ITEM_CORPSE_PC;   break;
    }

    if ( dest_item == ITEM_CONTAINER )
    {
        if ( IS_SET(obj->value[1], CONT_CLOSED) )
        {
            act( AT_PLAIN, "The $d is closed.", ch, NULL, obj->name, TO_CHAR );
            return;
        }
        if ( get_real_obj_weight( obj ) / obj->count
        >=   obj->value[0] )
        {
           send_to_char( "It's already full as it can be.\n\r", ch );
           return;
        }
    }
    else
    {
        diff = MAX_COND_VALUE;
        if ( diff < 1 || obj->value[1] >= obj->value[0] )
        {
           send_to_char( "It's already full as it can be.\n\r", ch );
           return;
        }
    }

    if ( dest_item == ITEM_PIPE
    &&   IS_SET( obj->value[3], PIPE_FULLOFASH ) )
    {
        send_to_char( "It's full of ashes, and needs to be emptied first.\n\r", ch );
        return;
    }

    if ( arg2[0] != '\0' )
    {
      if ( dest_item == ITEM_CONTAINER
      && (!str_cmp( arg2, "all" ) || !str_prefix( "all.", arg2 )) )
      {
        all = TRUE;
        source = NULL;
      }
      else
      /* This used to let you fill a pipe from an object on the ground.  Seems
         to me you should be holding whatever you want to fill a pipe with.
         It's nitpicking, but I needed to change it to get a mobprog to work
         right.  Check out Lord Fitzgibbon if you're curious.  -Narn */
      if ( dest_item == ITEM_PIPE )
      {
        if ( ( source = get_obj_carry( ch, arg2 ) ) == NULL )
        {
           send_to_char( "You don't have that item.\n\r", ch );
           return;
        }
        if ( source->item_type != src_item1 && source->item_type != src_item2
        &&   source->item_type != src_item3 )
        {
           act( AT_PLAIN, "You cannot fill $p with $P!", ch, obj, source, TO_CHAR );
           return;
        }
      }
      else
      {
        if ( ( source =  get_obj_here( ch, arg2 ) ) == NULL )
        {
           send_to_char( "You cannot find that item.\n\r", ch );
           return;
        }
      }
    }
    else
        source = NULL;

    if ( !source && dest_item == ITEM_PIPE )
    {
        send_to_char( "Fill it with what?\n\r", ch );
        return;
    }

    if ( !source )
    {
        bool      found = FALSE;
        OBJ_DATA *src_next;

        found = FALSE;
        separate_obj( obj );
        for ( source = ch->in_room->first_content;
              source;
              source = src_next )
        {
            src_next = source->next_content;
            if (dest_item == ITEM_CONTAINER)
            {
                if ( !CAN_WEAR(source, ITEM_TAKE)
                ||    IS_OBJ_STAT( source, ITEM_BURIED )
                ||   (IS_OBJ_STAT( source, ITEM_PROTOTYPE) && !can_take_proto(ch))
                ||    ch->carry_weight + get_obj_weight(source) > can_carry_w(ch)
                ||   (get_real_obj_weight(source) + get_real_obj_weight(obj)/obj->count)
                    > obj->value[0] )
                  continue;
                if ( all && arg2[3] == '.'
                &&  !nifty_is_name( &arg2[4], source->name ) )
                   continue;
                obj_from_room(source);
                if ( source->item_type == ITEM_MONEY )
                {
                   ch->gold += taxed(source->value[0]);
				   tax(ch, source->value[0]);
                   extract_obj( source );
                }
                else
                   obj_to_obj(source, obj);
                found = TRUE;
            }
            else
            if (source->item_type == src_item1
            ||  source->item_type == src_item2
            ||  source->item_type == src_item3)
            {
                found = TRUE;
                break;
            }
        }
        if ( !found )
        {
            switch( src_item1 )
            {
                default:
                  send_to_char( "There is nothing appropriate here!\n\r", ch );
                  return;
                case ITEM_FOUNTAIN:
                  send_to_char( "There is no fountain or pool here!\n\r", ch );
                  return;
                case ITEM_BLOOD:
                  send_to_char( "There is no blood pool here!\n\r", ch );
                  return;
                case ITEM_HERB_CON:
                  send_to_char( "There are no herbs here!\n\r", ch );
                  return;
                case ITEM_HERB:
                  send_to_char( "You cannot find any smoking herbs.\n\r", ch );
                  return;
            }
        }
        if (dest_item == ITEM_CONTAINER)
        {
          act( AT_ACTION, "You fill $p.", ch, obj, NULL, TO_CHAR );
          act( AT_ACTION, "$n fills $p.", ch, obj, NULL, TO_ROOM );
          return;
        }
    }

    if (dest_item == ITEM_CONTAINER)
    {
        OBJ_DATA *otmp, *otmp_next;
        char name[MAX_INPUT_LENGTH];
        CHAR_DATA *gch;
        char *pd;
        bool found = FALSE;

        if ( source == obj )
        {
            send_to_char( "You can't fill something with itself!\n\r", ch );
            return;
        }

        switch( source->item_type )
        {
            default:    /* put something in container */
                if ( !source->in_room   /* disallow inventory items */
                ||   !CAN_WEAR(source, ITEM_TAKE)
                ||   (IS_OBJ_STAT( source, ITEM_PROTOTYPE) && !can_take_proto(ch))
                ||    ch->carry_weight + get_obj_weight(source) > can_carry_w(ch)
                ||   (get_real_obj_weight(source) + get_real_obj_weight(obj)/obj->count)
                    > obj->value[0] )
                {
                    send_to_char( "You can't do that.\n\r", ch );
                    return;
                }
                separate_obj( obj );
                act( AT_ACTION, "You take $P and put it inside $p.", ch, obj, source, TO_CHAR );
                act( AT_ACTION, "$n takes $P and puts it inside $p.", ch, obj, source, TO_ROOM );
                obj_from_room(source);
                obj_to_obj(source, obj);
                break;
            case ITEM_MONEY:
                send_to_char( "You can't do that... yet.\n\r", ch );
                break;
            case ITEM_CORPSE_PC:
                if ( IS_NPC(ch) )
                {
                    send_to_char( "You can't do that.\n\r", ch );
                    return;
                }
                if ( IS_OBJ_STAT( source, ITEM_CLANCORPSE )
                &&  !IS_IMMORTAL( ch ) )
                {
                    send_to_char( "Your hands fumble.  Maybe you better loot a different way.\n\r", ch );
                    return;
                }
                if ( !IS_OBJ_STAT( source, ITEM_CLANCORPSE )
                ||   !IS_SET( ch->pcdata->flags, PCFLAG_DEADLY ) )
                {
                    pd = source->short_descr;
                    pd = one_argument( pd, name );
                    pd = one_argument( pd, name );
                    pd = one_argument( pd, name );
                    pd = one_argument( pd, name );

                    if ( str_cmp( name, ch->name ) && !IS_IMMORTAL(ch) )
                    {
                        bool fGroup;

                        fGroup = FALSE;
                        for ( gch = first_char; gch; gch = gch->next )
                        {
                            if ( !IS_NPC(gch)
                            &&   is_same_group( ch, gch )
                            &&   !str_cmp( name, gch->name ) )
                            {
                                fGroup = TRUE;
                                break;
                            }
                        }
                        if ( !fGroup )
                        {
                            send_to_char( "That's someone else's corpse.\n\r", ch );
                            return;
                        }
                    }
                }
            case ITEM_CONTAINER:
                if ( source->item_type == ITEM_CONTAINER  /* don't remove */
                &&   IS_SET(source->value[1], CONT_CLOSED) )
                {
                    act( AT_PLAIN, "The $d is closed.", ch, NULL, source->name, TO_CHAR );
                    return;
                }
            case ITEM_CORPSE_NPC:
                if ( (otmp=source->first_content) == NULL )
                {
                    send_to_char( "It's empty.\n\r", ch );
                    return;
                }
                separate_obj( obj );
                for ( ; otmp; otmp = otmp_next )
                {
                    otmp_next = otmp->next_content;

                    if ( !CAN_WEAR(otmp, ITEM_TAKE)
                    ||   (IS_OBJ_STAT( otmp, ITEM_PROTOTYPE) && !can_take_proto(ch))
                    ||    ch->carry_number + otmp->count > can_carry_n(ch)
                    ||    ch->carry_weight + get_obj_weight(otmp) > can_carry_w(ch)
                    ||   (get_real_obj_weight(source) + get_real_obj_weight(obj)/obj->count)
                        > obj->value[0] )
                        continue;
                    obj_from_obj(otmp);
                    obj_to_obj(otmp, obj);
                    found = TRUE;
                }
                if ( found )
                {
                   act( AT_ACTION, "You fill $p from $P.", ch, obj, source, TO_CHAR );
                   act( AT_ACTION, "$n fills $p from $P.", ch, obj, source, TO_ROOM );
                }
                else
                   send_to_char( "There is nothing appropriate in there.\n\r", ch );
                break;
        }
        return;
    }

    if ( source->value[1] < 1 )
    {
        send_to_char( "There's none left!\n\r", ch );
        return;
    }
    if ( source->count > 1 && source->item_type != ITEM_FOUNTAIN )
      separate_obj( source );
    separate_obj( obj );

    switch( source->item_type )
    {
        default:
          bug( "do_fill: got bad item type: %d", source->item_type );
          send_to_char( "Something went wrong...\n\r", ch );
          return;
        case ITEM_FOUNTAIN:
          if ( obj->value[1] != 0 && obj->value[2] != 0 )
          {
             send_to_char( "There is already another liquid in it.\n\r", ch );
             return;
          }
          obj->value[2] = 0;
          obj->value[1] = obj->value[0];
          act( AT_ACTION, "You fill $p from $P.", ch, obj, source, TO_CHAR );
          act( AT_ACTION, "$n fills $p from $P.", ch, obj, source, TO_ROOM );
          return;
        case ITEM_BLOOD:
          if ( obj->value[1] != 0 && obj->value[2] != 13 )
          {
             send_to_char( "There is already another liquid in it.\n\r", ch );
             return;
          }
          obj->value[2] = 13;
          if ( source->value[1] < diff )
            diff = source->value[1];
          obj->value[1] += diff;
          act( AT_ACTION, "You fill $p from $P.", ch, obj, source, TO_CHAR );
          act( AT_ACTION, "$n fills $p from $P.", ch, obj, source, TO_ROOM );
          if ( (source->value[1] -= diff) < 1 )
          {
             extract_obj( source );
             make_bloodstain( ch );
          }
          return;
        case ITEM_HERB:
          if ( obj->value[1] != 0 && obj->value[2] != source->value[2] )
          {
             send_to_char( "There is already another type of herb in it.\n\r", ch );
             return;
          }
          obj->value[2] = source->value[2];
          if ( source->value[1] < diff )
            diff = source->value[1];
          obj->value[1] += diff;
          act( AT_ACTION, "You fill $p with $P.", ch, obj, source, TO_CHAR );
          act( AT_ACTION, "$n fills $p with $P.", ch, obj, source, TO_ROOM );
          if ( (source->value[1] -= diff) < 1 )
             extract_obj( source );
          return;
        case ITEM_HERB_CON:
          if ( obj->value[1] != 0 && obj->value[2] != source->value[2] )
          {
             send_to_char( "There is already another type of herb in it.\n\r", ch );
             return;
          }
          obj->value[2] = source->value[2];
          if ( source->value[1] < diff )
            diff = source->value[1];
          obj->value[1] += diff;
          source->value[1] -= diff;
          act( AT_ACTION, "You fill $p from $P.", ch, obj, source, TO_CHAR );
          act( AT_ACTION, "$n fills $p from $P.", ch, obj, source, TO_ROOM );
          return;
        case ITEM_DRINK_CON:
          if ( obj->value[1] != 0 && obj->value[2] != source->value[2] )
          {
             send_to_char( "There is already another liquid in it.\n\r", ch );
             return;
          }
          obj->value[2] = source->value[2];
          if ( source->value[1] < diff )
            diff = source->value[1];
          obj->value[1] += diff;
          source->value[1] -= diff;
          act( AT_ACTION, "You fill $p from $P.", ch, obj, source, TO_CHAR );
          act( AT_ACTION, "$n fills $p from $P.", ch, obj, source, TO_ROOM );
          return;
    }
}

void do_empty( CHAR_DATA *ch, char *argument )
{
    OBJ_DATA *obj;
    char arg1[MAX_INPUT_LENGTH];
    char arg2[MAX_INPUT_LENGTH];

    argument = one_argument( argument, arg1 );
    argument = one_argument( argument, arg2 );
    if ( !str_cmp( arg2, "into" ) && argument[0] != '\0' )
        argument = one_argument( argument, arg2 );

    if ( arg1[0] == '\0' )
    {
        send_to_char( "Empty what?\n\r", ch );
        return;
    }
    if ( ms_find_obj(ch) )
        return;

    if ( (obj = get_obj_carry( ch, arg1 )) == NULL )
    {
        send_to_char( "You aren't carrying that.\n\r", ch );
        return;
    }
    if ( obj->count > 1 )
      separate_obj(obj);

    switch( obj->item_type )
    {
        default:
          act( AT_ACTION, "You shake $p in an attempt to empty it...", ch, obj, NULL, TO_CHAR );
          act( AT_ACTION, "$n begins to shake $p in an attempt to empty it...", ch, obj, NULL, TO_ROOM );
          return;
        case ITEM_PIPE:
          act( AT_ACTION, "You gently tap $p and empty it out.", ch, obj, NULL, TO_CHAR );
          act( AT_ACTION, "$n gently taps $p and empties it out.", ch, obj, NULL, TO_ROOM );
          REMOVE_BIT( obj->value[3], PIPE_FULLOFASH );
          REMOVE_BIT( obj->value[3], PIPE_LIT );
          obj->value[1] = 0;
          return;
        case ITEM_DRINK_CON:
          if ( obj->value[1] < 1 )
          {
                send_to_char( "It's already empty.\n\r", ch );
                return;
          }
          act( AT_ACTION, "You empty $p.", ch, obj, NULL, TO_CHAR );
          act( AT_ACTION, "$n empties $p.", ch, obj, NULL, TO_ROOM );
          obj->value[1] = 0;
          return;
        case ITEM_CONTAINER:
        case ITEM_QUIVER:
          if ( IS_SET(obj->value[1], CONT_CLOSED) )
          {
                act( AT_PLAIN, "The $d is closed.", ch, NULL, obj->name, TO_CHAR );
                return;
          }
        case ITEM_KEYRING:
          if ( !obj->first_content )
          {
                send_to_char( "It's already empty.\n\r", ch );
                return;
          }
          if ( arg2[0] == '\0' )
          {
                if ( IS_SET( ch->in_room->room_flags, ROOM_NODROP ) )
                {
                       set_char_color( AT_MAGIC, ch );
                       send_to_char( "A magical force stops you!\n\r", ch );
                       set_char_color( AT_TELL, ch );
                       send_to_char( "Someone tells you, 'No littering here!'\n\r", ch );
                       return;
                }
                if ( IS_SET( ch->in_room->room_flags, ROOM_NODROPALL )
                ||   IS_SET( ch->in_room->room_flags, ROOM_CLANSTOREROOM ) )
                {
                   send_to_char( "You can't seem to do that here...\n\r", ch );
                   return;
                }
                if ( empty_obj( obj, NULL, ch->in_room ) )
                {
                    act( AT_ACTION, "You empty $p.", ch, obj, NULL, TO_CHAR );
                    act( AT_ACTION, "$n empties $p.", ch, obj, NULL, TO_ROOM );
                    if ( IS_SET( sysdata.save_flags, SV_EMPTY ) )
                        save_char_obj( ch );
                }
                else
                    send_to_char( "Hmmm... didn't work.\n\r", ch );
          }
          else
          {
                OBJ_DATA *dest = get_obj_here( ch, arg2 );

                if ( !dest )
                {
                    send_to_char( "You can't find it.\n\r", ch );
                    return;
                }
                if ( dest == obj )
                {
                    send_to_char( "You can't empty something into itself!\n\r", ch );
                    return;
                }
                if ( dest->item_type != ITEM_CONTAINER && dest->item_type != ITEM_KEYRING
                &&   dest->item_type != ITEM_QUIVER )
                {
                    send_to_char( "That's not a container!\n\r", ch );
                    return;
                }
                if ( IS_SET(dest->value[1], CONT_CLOSED) )
                {
                    act( AT_PLAIN, "The $d is closed.", ch, NULL, dest->name, TO_CHAR );
                    return;
                }
                if ( IS_SET( ch->in_room->room_flags, ROOM_CLANSTOREROOM ) && IS_OBJ_STAT(dest, ITEM_DONATION))
                {
                   send_to_char( "You can't seem to do that here...\n\r", ch );
                   return;
                }
                separate_obj( dest );
                if ( empty_obj( obj, dest, NULL ) )
                {
                    act( AT_ACTION, "You empty $p into $P.", ch, obj, dest, TO_CHAR );
                    act( AT_ACTION, "$n empties $p into $P.", ch, obj, dest, TO_ROOM );
                    if ( !dest->carried_by
                    &&    IS_SET( sysdata.save_flags, SV_EMPTY ) )
                        save_char_obj( ch );
                }
                else
                    act( AT_ACTION, "$P is too full.", ch, obj, dest, TO_CHAR );
          }
          return;
    }
}

