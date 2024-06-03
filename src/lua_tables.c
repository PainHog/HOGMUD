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
 *			 Lua Constants Tables     by Nick Gammon            *
 ****************************************************************************/
 
/*

Lua scripting written by Nick Gammon
Date: 8th July 2007

You are welcome to incorporate this code into your MUD codebases.

Post queries at: http://www.gammon.com.au/forum/


*/


#include <stdio.h>
#include <string.h>
#include "mud.h"

#include "lualib.h"
#include "lauxlib.h"

#define AT_TABLE "at"
#define OBJ_ITEM_TYPE_TABLE "itype"
#define ATTACK_TYPE_TABLE "atype"
#define DAMAGE_TYPE_TABLE "dtype"
#define RACE_TYPE_TABLE "race"
#define AFF_BY_TYPE_TABLE "affby"
#define APPLY_TYPE_TABLE "apply"
#define SPELL_DAMAGE_TYPE_TABLE "sdtype"

typedef struct { const char* key; int val; } flags_pair;

static int MakeFlagsTable (lua_State *L, const char *name, const flags_pair *arr)
{
    const flags_pair *p;
    lua_newtable(L);
    for(p=arr; p->key != NULL; p++)
    {
        lua_pushstring(L, p->key);
        lua_pushnumber(L, p->val);
        lua_rawset(L, -3);
    }
    lua_setglobal (L, name);
    return 1;
}

/* ex: apply.none */
static flags_pair apply_types_table[] =
{
	{ "none", 		APPLY_NONE },
	{ "str", 		APPLY_STR },
	{ "dex", 		APPLY_DEX },
	{ "int", 		APPLY_INT },
	{ "wis", 		APPLY_WIS },
	{ "con", 		APPLY_CON },
	{ "sex", 		APPLY_SEX },
	{ "class", 		APPLY_CLASS },
	{ "level", 		APPLY_LEVEL },
	{ "age", 		APPLY_AGE },
	{ "height", 		APPLY_HEIGHT },
	{ "weight", 		APPLY_WEIGHT },
	{ "mana", 		APPLY_MANA },
	{ "hp", 		APPLY_HIT },
	{ "move", 		APPLY_MOVE },
	{ "gold", 		APPLY_GOLD },
	{ "exp", 		APPLY_EXP },
	{ "ac", 		APPLY_AC },
	{ "hr", 		APPLY_HITROLL },
	{ "dr", 		APPLY_DAMROLL },
	{ "svd", 		APPLY_SAVING_DAMAGE },
	{ "svr", 		APPLY_SAVING_ROD },
	{ "svp", 		APPLY_SAVING_PARA },
	{ "svb", 		APPLY_SAVING_BREATH },
	{ "svs", 		APPLY_SAVING_SPELL },
	{ "cha", 		APPLY_CHA },
	{ "affect", 		APPLY_AFFECT },
	{ "resistant", 		APPLY_RESISTANT },
	{ "immune", 		APPLY_IMMUNE },
	{ "susceptible", 	APPLY_SUSCEPTIBLE },
	{ "weaponspell", 	APPLY_WEAPONSPELL },
	{ "lck", 		APPLY_LCK },
	{ "backstab", 		APPLY_BACKSTAB },
	{ "pick", 		APPLY_PICK },
	{ "track", 		APPLY_TRACK },
	{ "steal", 		APPLY_STEAL },
	{ "sneak", 		APPLY_SNEAK },
	{ "hide", 		APPLY_HIDE },
	{ "palm", 		APPLY_PALM },
	{ "detrap", 		APPLY_DETRAP },
	{ "dodge", 		APPLY_DODGE },
	{ "peek", 		APPLY_PEEK },
	{ "scan", 		APPLY_SCAN },
	{ "gouge", 		APPLY_GOUGE },
	{ "search", 		APPLY_SEARCH },
	{ "mount", 		APPLY_MOUNT },
	{ "disarm", 		APPLY_DISARM },
	{ "kick", 		APPLY_KICK },
	{ "parry", 		APPLY_PARRY },
	{ "bash", 		APPLY_BASH },
	{ "stun", 		APPLY_STUN },
	{ "punch", 		APPLY_PUNCH },
	{ "climb", 		APPLY_CLIMB },
	{ "grip", 		APPLY_GRIP },
	{ "scribe", 		APPLY_SCRIBE },
	{ "brew", 		APPLY_BREW },
	{ "wearspell", 		APPLY_WEARSPELL },
	{ "removespell", 	APPLY_REMOVESPELL },
	{ "emotion", 		APPLY_EMOTION },
	{ "mentalstate", 	APPLY_MENTALSTATE },
	{ "stripsn", 		APPLY_STRIPSN },
	{ "remove", 		APPLY_REMOVE },
	{ "dig", 		APPLY_DIG },
	{ "full", 		APPLY_FULL },
	{ "thirst", 		APPLY_THIRST },
	{ "drunk", 		APPLY_DRUNK },
	{ "blood", 		APPLY_BLOOD },
	{ "recurringspell", 	APPLY_RECURRINGSPELL },
	{ "contagious", 	APPLY_CONTAGIOUS },
	{ "ext_affect", 	APPLY_EXT_AFFECT },
	{ "odor", 		APPLY_ODOR },
	{ "roomflag", 		APPLY_ROOMFLAG },
	{ "sectortype", 	APPLY_SECTORTYPE },
	{ "roomlight", 		APPLY_ROOMLIGHT },
	{ "televnum", 		APPLY_TELEVNUM },
	{ "teledelay", 		APPLY_TELEDELAY },
	{ "camo", 		APPLY_CAMO },
	{ "ambush", 		APPLY_AMBUSH },
	{ "spiritshield", 	APPLY_SPIRITSHIELD },
	{ "spelldam", 		APPLY_SPELLDAM },
	{ "jump", 		APPLY_JUMP },
	{ "wait", 		APPLY_WAIT },
	{ "mute", 		APPLY_MUTE },
	{ "max_apply_type", 	MAX_APPLY_TYPE },

	{NULL, 0}
};


/* ex: affby.blind */
static flags_pair aff_by_types_table[] =
{
	{ "blind", 		AFF_BLIND },
	{ "invis", 		AFF_INVISIBLE },
	{ "det_evil", 		AFF_DETECT_EVIL },
	{ "det_invis", 		AFF_DETECT_INVIS },
	{ "det_magic", 		AFF_DETECT_MAGIC },
	{ "det_hidden", 	AFF_DETECT_HIDDEN },
	{ "imp_invis", 		AFF_IMP_INVIS },
	{ "sanctuary", 		AFF_SANCTUARY },
	{ "faerie_fire", 	AFF_FAERIE_FIRE },
	{ "infrared", 		AFF_INFRARED },
	{ "curse", 		AFF_CURSE },
	{ "corrupt", 		AFF_CORRUPT },
	{ "poison", 		AFF_POISON },
	{ "protect", 		AFF_PROTECT },
	{ "paralysis", 		AFF_PARALYSIS },
	{ "sneak", 		AFF_SNEAK },
	{ "hide", 		AFF_HIDE },
	{ "sleep", 		AFF_SLEEP },
	{ "charm", 		AFF_CHARM },
	{ "flying", 		AFF_FLYING },
	{ "pass_door", 		AFF_PASS_DOOR },
	{ "floating", 		AFF_FLOATING },
	{ "truesight", 		AFF_TRUESIGHT },
	{ "det_traps", 		AFF_DETECTTRAPS },
	{ "scrying", 		AFF_SCRYING },
	{ "fireshield", 	AFF_FIRESHIELD },
	{ "shockshield", 	AFF_SHOCKSHIELD },
	{ "det_good", 		AFF_DETECT_GOOD },
	{ "iceshield", 		AFF_ICESHIELD },
	{ "possess", 		AFF_POSSESS },
	{ "berserk", 		AFF_BERSERK },
	{ "aqua_breath", 	AFF_AQUA_BREATH },
	{ "recurringspell", 	AFF_RECURRINGSPELL },
	{ "empowered", 		AFF_EMPOWERED },
	{ "tongues", 		AFF_TONGUES },
	{ "balanced", 		AFF_BALANCED },
	{ "auralink", 		AFF_AURALINK },
	{ "unused5", 		AFF_UNUSED5 },
	{ "mighty", 		AFF_MIGHTY },
	{ "camo", 		AFF_CAMO },
	{ "demonsight", 	AFF_DEMONSIGHT },
	{ "bound", 		AFF_BOUND },
	{ "mute", 		AFF_MUTE },
	{ "max_affected_by", 	MAX_AFFECTED_BY },

	{NULL, 0}
};


/* ex: race.human */
static flags_pair race_types_table[] = 
{
	{ "human", 	RACE_HUMAN },
	{ "elf", 	RACE_ELF },
	{ "dwarf", 	RACE_DWARF },
	{ "halfling", 	RACE_HALFLING },
	{ "pixie", 	RACE_PIXIE },
	{ "minotaur", 	RACE_MINOTAUR },
	{ "half-ogre", 	RACE_HALF_OGRE },
	{ "half-orc", 	RACE_HALF_ORC },
	{ "half-troll", RACE_HALF_TROLL },
	{ "half-elf", 	RACE_HALF_ELF },
	{ "gith", 	RACE_GITH },
	{ "drow", 	RACE_DROW },
	{ "sea-elf", 	RACE_SEA_ELF },
	{ "lizardman", 	RACE_LIZARDMAN },
	{ "gnome", 	RACE_GNOME },
	{ "ghoul", 	RACE_GHOUL },
	{ "goblin", 	RACE_GOBLIN },
	{ "wolfen", 	RACE_WOLFEN },
	{ "shuri", 	18 },
	{ "gulran", 	19 },
	{ "zephyr", 	20 },
	{ "jinn", 	21 },
	{ "ahpock", 	22 },

	{NULL, 0}
};

/* ex: dtype.slash */
static flags_pair damage_types_table[] =
{
	{ "hit", 	DAM_HIT },
	{ "slice", 	DAM_SLICE },
	{ "stab", 	DAM_STAB },
	{ "slash", 	DAM_SLASH },
	{ "whip", 	DAM_WHIP },
	{ "claw", 	DAM_CLAW },
	{ "blast", 	DAM_BLAST },
	{ "pound", 	DAM_POUND },
	{ "crush", 	DAM_CRUSH },
	{ "hack", 	DAM_HACK },
	{ "bite", 	DAM_BITE },
	{ "pierce", 	DAM_PIERCE },
	{ "pslice", 	DAM_PSLICE },
	{ "bolt", 	DAM_BOLT },
	{ "arrow", 	DAM_ARROW },
	{ "dart", 	DAM_DART },
	{ "stone", 	DAM_STONE },
	{ "pslash", 	DAM_PSLASH },
	{ "aslice", 	DAM_ASLICE },
	{ "aslash", 	DAM_ASLASH },
	{ "ehit", 	DAM_EHIT },
	{ "sbash", 	DAM_SBASH },
	{ "tear", 	DAM_TEAR },
	{ "rip", 	DAM_RIP },
	{ "pstab", 	DAM_PSTAB },
	{ "apierce", 	DAM_APIERCE },

	{NULL, 0}
};

/* ex: atype.bite */
static flags_pair attack_types_table[] =
{
  {"bite", 		ATCK_BITE}, 
  {"claws", 		ATCK_CLAWS}, 
  {"tail", 		ATCK_TAIL}, 
  {"sting", 		ATCK_STING}, 
  {"punch", 		ATCK_PUNCH}, 
  {"kick", 		ATCK_KICK},
  {"trip", 		ATCK_TRIP}, 
  {"bash", 		ATCK_BASH}, 
  {"stun", 		ATCK_STUN}, 
  {"gouge", 		ATCK_GOUGE}, 
  {"backstab", 		ATCK_BACKSTAB},
  {"drain", 		ATCK_DRAIN},  
  {"firebreath", 	ATCK_FIREBREATH}, 
  {"frostbreath", 	ATCK_FROSTBREATH}, 
  {"acidbreath", 	ATCK_ACIDBREATH},
  {"lightningbreath", 	ATCK_LIGHTNBREATH}, 
  {"gasbreath", 	ATCK_GASBREATH}, 
  {"poison", 		ATCK_POISON}, 
  {"unused1", 		ATCK_UNUSED1}, 
  {"unused2", 		ATCK_UNUSED2},
  {"blindness", 	ATCK_BLINDNESS}, 
  {"causeserious", 	ATCK_CAUSESERIOUS}, 
  {"earthquake", 	ATCK_EARTHQUAKE}, 
  {"causecritical", 	ATCK_CAUSECRITICAL},
  {"curse", 		ATCK_CURSE}, 
  {"flamestrike", 	ATCK_FLAMESTRIKE}, 
  {"harm", 		ATCK_HARM}, 
  {"fireball", 		ATCK_FIREBALL}, 
  {"colorspray", 	ATCK_COLORSPRAY},
  {"weaken", 		ATCK_WEAKEN}, 
  {"spiralblast", 	ATCK_SPIRALBLAST}, 
  {"ambush", 		ATCK_AMBUSH}, 
  {"max_attack_type", 	MAX_ATTACK_TYPE},
  
  { NULL, 0 }
};

/* we can use at.orange (for example) as an argument to mud.set_char_color */
static flags_pair at_colours_table[] =
{
   { "black",        AT_BLACK        },  { "rmname",   AT_RMNAME   },
   { "blood",        AT_BLOOD        },  { "rmdesc",   AT_RMDESC   },
   { "dgreen",       AT_DGREEN       },  { "object",   AT_OBJECT   },
   { "orange",       AT_ORANGE       },  { "person",   AT_PERSON   },
   { "dblue",        AT_DBLUE        },  { "list",     AT_LIST     },
   { "purple",       AT_PURPLE       },  { "bye",      AT_BYE      },
   { "cyan",         AT_CYAN         },  { "gold",     AT_GOLD     },
   { "grey",         AT_GREY         },  { "gtell",    AT_GTELL    },
   { "dgrey",        AT_DGREY        },  { "note",     AT_NOTE     },
   { "red",          AT_RED          },  { "hungry",   AT_HUNGRY   },
   { "green",        AT_GREEN        },  { "thirsty",  AT_THIRSTY  },
   { "yellow",       AT_YELLOW       },  { "fire",     AT_FIRE     },
   { "blue",         AT_BLUE         },  { "sober",    AT_SOBER    },
   { "pink",         AT_PINK         },  { "wearoff",  AT_WEAROFF  },
   { "lblue",        AT_LBLUE        },  { "exits",    AT_EXITS    },
   { "white",        AT_WHITE        },  { "score",    AT_SCORE    },
   { "blink",        AT_BLINK        },  { "reset",    AT_RESET    },
   { "black_blink",  AT_BLACK	     },  { "log",      AT_LOG      },
   { "blood_blink",  AT_BLOOD	     },  { "diemsg",   AT_DIEMSG   },
   { "dgreen_blink", AT_DGREEN	     },  { "wartalk",  AT_WARTALK  },
   { "orange_blink", AT_ORANGE	     },  { "arena",    AT_ARENA    },
   { "dblue_blink",  AT_DBLUE	     },  { "muse",     AT_MUSE     },
   { "purple_blink", AT_PURPLE	     },  { "think",    AT_THINK    },
   { "cyan_blink",   AT_CYAN	     },  { "aflags",   AT_AFLAGS   },
   { "grey_blink",   AT_GREY	     },  { "who",      AT_WHO      },
   { "dgrey_blink",  AT_DGREY	     },  { "racetalk", AT_RACETALK },
   { "red_blink",    AT_RED	         },  { "ignore",   AT_IGNORE   },
   { "green_blink",  AT_GREEN	     },  { "whisper",  AT_WHISPER  },
   { "yellow_blink", AT_YELLOW	     },  { "divider",  AT_DIVIDER  },
   { "blue_blink",   AT_BLUE	     },  { "morph",    AT_MORPH    },
   { "pink_blink",   AT_PINK	     },  { "shout",    AT_SHOUT    },
   { "lblue_blink",  AT_LBLUE	     },  { "rflags",   AT_RFLAGS   },
   { "white_blink",  AT_WHITE_BLINK  },  { "stype",    AT_STYPE    },
   { "plain",        AT_PLAIN        },  { "aname",    AT_ANAME    },
   { "action",       AT_ACTION       },  { "auction",  AT_AUCTION  },
   { "say",          AT_SAY          },  { "score2",   AT_SCORE2   },
   { "gossip",       AT_GOSSIP       },  { "score3",   AT_SCORE3   },
   { "yell",         AT_YELL         },  { "score4",   AT_SCORE4   },
   { "tell",         AT_TELL         },  { "who2",     AT_WHO2     },
   { "hit",          AT_HIT          },  { "who3",     AT_WHO3     },
   { "hitme",        AT_HITME        },  { "who4",     AT_WHO4     },
   { "immort",       AT_IMMORT       },  { "intermud", AT_INTERMUD },
   { "hurt",         AT_HURT         },  { "help",     AT_HELP     },
   { "falling",      AT_FALLING      },  { "who5",     AT_WHO5     },
   { "danger",       AT_DANGER       },  { "score5",   AT_SCORE5   },
   { "magic",        AT_MAGIC        },  { "who6",     AT_WHO6     },
   { "consider",     AT_CONSIDER     },  { "who7",     AT_WHO7     },
   { "report",       AT_REPORT       },  { "prac",     AT_PRAC     },
   { "poison",       AT_POISON       },  { "prac2",    AT_PRAC2    },
   { "social",       AT_SOCIAL       },  { "prac3",    AT_PRAC3    },
   { "dying",        AT_DYING        },  { "prac4",    AT_PRAC4    },
   { "dead",         AT_DEAD         },  { "mxpprompt",AT_MXPPROMPT},
   { "skill",        AT_SKILL        },  { "guildtalk",AT_GUILDTALK},
   { "carnage",      AT_CARNAGE      }, /* { "board",    AT_BOARD    },*/
   { "damage",       AT_DAMAGE       }, /* { "board2",   AT_BOARD2   },*/
   { "flee",         AT_FLEE         }, /* { "board3",   AT_BOARD3   },*/
  
   { NULL, 0 }
};

/* object types */
static flags_pair object_types_table[] =
{

	{ "none",		    ITEM_NONE },		    { "light",	        ITEM_LIGHT },
	{ "scroll",		    ITEM_SCROLL },		    { "wand",	        ITEM_WAND },
	{ "staff",		    ITEM_STAFF },		    { "weapon",	        ITEM_WEAPON },
	{ "_fireweapon",	ITEM_FIREWEAPON },	    { "_missile",	    ITEM_MISSILE },
	{ "treasure",		ITEM_TREASURE },	    { "armor",	        ITEM_ARMOR },
	{ "potion",		    ITEM_POTION },		    { "worn",	        ITEM_WORN },
	{ "furniture",		ITEM_FURNITURE },	    { "trash",	        ITEM_TRASH },
	{ "_oldtrap",		ITEM_OLDTRAP },		    { "container",	    ITEM_CONTAINER },
	{ "_note",		    ITEM_NOTE },		    { "drinkcon",	    ITEM_DRINK_CON },
	{ "key",		    ITEM_KEY },		        { "food",	        ITEM_FOOD },
	{ "money",		    ITEM_MONEY },		    { "pen",	        ITEM_PEN },
	{ "boat",		    ITEM_BOAT },		    { "corpse",	        ITEM_CORPSE_NPC },
	{ "corpse_pc",		ITEM_CORPSE_PC },	    { "fountain",	    ITEM_FOUNTAIN },
	{ "pill",		    ITEM_PILL },		    { "blood",	        ITEM_BLOOD },
	{ "bloodstain",		ITEM_BLOODSTAIN },	    { "scraps",	        ITEM_SCRAPS },
	{ "pipe",		    ITEM_PIPE },		    { "herbcon",	    ITEM_HERB_CON },
	{ "herb",		    ITEM_HERB },		    { "incense",	    ITEM_INCENSE },
	{ "fire",		    ITEM_FIRE },		    { "book",	        ITEM_BOOK },
	{ "switch",		    ITEM_SWITCH },		    { "lever",	        ITEM_LEVER },
	{ "pullchain",		ITEM_PULLCHAIN },	    { "button",	        ITEM_BUTTON },
	{ "dial",		    ITEM_DIAL },		    { "rune",	        ITEM_RUNE },
	{ "runepouch",		ITEM_RUNEPOUCH },	    { "match",	        ITEM_MATCH },
	{ "trap",		    ITEM_TRAP },		    { "map",	        ITEM_MAP },
	{ "portal",		    ITEM_PORTAL },		    { "paper",	        ITEM_PAPER },
	{ "tinder",		    ITEM_TINDER },		    { "lockpick",	    ITEM_LOCKPICK },
	{ "spike",		    ITEM_SPIKE },		    { "disease",	    ITEM_DISEASE },
	{ "oil",		    ITEM_OIL },		        { "fuel",	        ITEM_FUEL },
	{ "piece",		    ITEM_PIECE },		    { "_empty2",	    ITEM_EMPTY2 },
	{ "missileweapon",	ITEM_MISSILE_WEAPON },	{ "projectile", ITEM_PROJECTILE },
	{ "quiver",		    ITEM_QUIVER },		    { "shovel",	        ITEM_SHOVEL },
	{ "salve",		    ITEM_SALVE },		    { "cook",	        ITEM_COOK },
	{ "keyring",		ITEM_KEYRING },		    { "comp",	        ITEM_COMP },
	{ "artweapon",		ITEM_ARTWEAPON },	    { "artarmor",	    ITEM_ARTARMOR },
	{ "arttreasure",	ITEM_ARTTREASURE },	    { "artworn",	    ITEM_ARTWORN },
	{ "artlight",		ITEM_ARTLIGHT },	    { "mix",	        ITEM_DRINK_MIX },
	{ "chance",		    ITEM_CHANCE },

	{ NULL, 0 }
};

static flags_pair spell_damage_types_table[] =
{
    { "none"        ,   SD_NONE         }, 
    { "fire"        ,   SD_FIRE         }, 
    { "cold"        ,   SD_COLD         }, 
    { "electricity" ,   SD_ELECTRICITY  }, 
    { "energy"      ,   SD_ENERGY       }, 
    { "acid"        ,   SD_ACID         },
    { "poison"      ,   SD_POISON       },
    { "drain"       ,   SD_DRAIN        },
    
    { NULL          , 0                 }
};

void add_lua_tables (lua_State *L)
{
    /* AT colours */
    MakeFlagsTable (L, AT_TABLE, at_colours_table);

    /* Object item types */
    MakeFlagsTable (L, OBJ_ITEM_TYPE_TABLE, object_types_table);

    /* attack types */
    MakeFlagsTable (L, ATTACK_TYPE_TABLE, attack_types_table);

    /* damage types */
    MakeFlagsTable(L, DAMAGE_TYPE_TABLE, damage_types_table);

    /* race types */
    MakeFlagsTable(L, RACE_TYPE_TABLE, race_types_table);

    /* aff-by types */
    MakeFlagsTable(L, AFF_BY_TYPE_TABLE, aff_by_types_table);

    /* apply types */
    MakeFlagsTable(L, APPLY_TYPE_TABLE, apply_types_table);

    /* spell damage types */
    MakeFlagsTable(L, SPELL_DAMAGE_TYPE_TABLE, spell_damage_types_table);

}
