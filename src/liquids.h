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
 * File: liquids.h
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

/* max condition value */
#define MAX_COND_VALUE 100

/* hard-coded max liquids */
#define MAX_LIQUIDS    100

typedef enum
{
  LIQTYPE_NORMAL, LIQTYPE_ALCOHOL, LIQTYPE_POISON, LIQTYPE_BLOOD, LIQTYPE_TOP
} liquid_struct_types;

/*
 * Conditions (moved from mud.h)
 */
typedef enum
{
  COND_DRUNK, COND_FULL, COND_THIRST, COND_BLOODTHIRST, MAX_CONDS
} conditions;

typedef struct liquid_table LIQ_TABLE;
struct liquid_table
{
  char *name;
  char *shortdesc;
  char *color;
  int vnum;
  int type;
  int mod[MAX_CONDS];
};

typedef struct mixture_list MIX_TABLE;
struct mixture_list
{
  MIX_TABLE *next;
  MIX_TABLE *prev;
  char *name;
  int  data [3];
  bool object;
};

MIX_TABLE *first_mixture;
MIX_TABLE *last_mixture;

typedef struct potion_table POT_TABLE;
struct potion_table
{
  POT_TABLE *next;
  POT_TABLE *prev;
  char *name;
  EXT_BV  spells;
};

POT_TABLE *first_potion;
POT_TABLE *last_potion;

/* functions */
DECLARE_DO_FUN(do_mix);
DECLARE_DO_FUN(do_setliquid);
DECLARE_DO_FUN(do_setmixture);

/* globals */
LIQ_TABLE *liquid_table[MAX_LIQUIDS];

/* liquids.c */
MIX_TABLE *fread_mixture    args((FILE *fp));
LIQ_TABLE *fread_liquid     args((FILE *fp));
void save_liquids           args((void));
void save_mixtures          args((void));
void load_liquids           args((void));
void load_mixtures          args((void));
LIQ_TABLE *get_liq          args((char *str));
LIQ_TABLE *get_liq_vnum     args((int vnum));
MIX_TABLE *get_mix          args((char *str));
LIQ_TABLE *liqobj_can_mix   args((OBJ_DATA *iObj, OBJ_DATA *oLiq));
LIQ_TABLE *liq_can_mix      args((OBJ_DATA *iObj, OBJ_DATA *tObj));
