#include "mud.h"

typedef struct	scoremobm_data	SCOREMOBM_DATA;
typedef struct  scorepk_data	SCOREPK_DATA;
typedef struct  scoregold_data	SCOREGOLD_DATA;
typedef struct  scoreqp_data	SCOREQP_DATA;
typedef struct  scoremk_data	SCOREMK_DATA;
typedef struct	scorexp_data	SCOREXP_DATA;
typedef struct	scoresp_data	SCORESP_DATA;
typedef struct	scoremp_data	SCOREMP_DATA;

bool valid_player   args( ( char * name ) );

struct scoremobm_data
{
	char 		*name;
	int 		scoremobm;
	SCOREMOBM_DATA 	*next;
	SCOREMOBM_DATA 	*prev;
};

struct scorepk_data
{ 
        char            *name;
        int             scorepk;
        SCOREPK_DATA      *next;
        SCOREPK_DATA      *prev;
};

struct scoreqp_data
{ 
        char            *name;
        int             scoreqp;
        SCOREQP_DATA      *next;
        SCOREQP_DATA      *prev;
};

struct scoregold_data
{ 
        char            *name;
        int             scoregold;
        SCOREGOLD_DATA      *next;
        SCOREGOLD_DATA      *prev;
};

struct scoremk_data
{
	char		*name;
	int		scoremk;
	SCOREMK_DATA	*next;
	SCOREMK_DATA	*prev;
};

struct scoremp_data
{
	char		*name;
	int		scoremp;
	SCOREMP_DATA	*next;
	SCOREMP_DATA	*prev;
};

struct scoresp_data
{
	char		*name;
	int		scoresp;
	SCORESP_DATA	*next;
	SCORESP_DATA	*prev;
};

struct scorexp_data
{
	char		*name;
	int		scorexp;
	SCOREXP_DATA	*next;
	SCOREXP_DATA	*prev;
};

SCOREMOBM_DATA * first_scoremobm;
SCOREMOBM_DATA * last_scoremobm;
#define MAX_SCOREMOBM 20  /* variable for easy adjustment of how many to display */

SCOREPK_DATA * first_scorepk;
SCOREPK_DATA * last_scorepk;
#define MAX_SCOREPK 20  /* variable for easy adjustment of how many to display */

SCOREQP_DATA * first_scoreqp;
SCOREQP_DATA * last_scoreqp;
#define MAX_SCOREQP 20  /* variable for easy adjustment of how many to display */

SCOREGOLD_DATA * first_scoregold;
SCOREGOLD_DATA * last_scoregold;
#define MAX_SCOREGOLD 20  /* variable for easy adjustment of how many to display */

SCOREMK_DATA * first_scoremk;
SCOREMK_DATA * last_scoremk;
#define MAX_SCOREMK 20 /* variable for easy adjustment of how many to display */

SCORESP_DATA * first_scoresp;
SCORESP_DATA * last_scoresp;
#define MAX_SCORESP 20 /* variable for easy adjustment of how many to display */

SCOREMP_DATA * first_scoremp;
SCOREMP_DATA * last_scoremp;
#define MAX_SCOREMP 20 /* variable for easy adjustment of how many to display */

SCOREXP_DATA * first_scorexp;
SCOREXP_DATA * last_scorexp;
#define MAX_SCOREXP 20 /* variable for easy adjustment of how many to display */


/* local functions */
void	replace_scoremobm      args( ( CHAR_DATA *ch) );
void    replace_scoregold      args( ( CHAR_DATA *ch) );
void    replace_scorepk        args( ( CHAR_DATA *ch) );
void    replace_scoreqp        args( ( CHAR_DATA *ch) );
void	replace_scoremk        args( ( CHAR_DATA *ch) );
void	replace_scoremp			args( ( CHAR_DATA *ch) );
void	replace_scoresp			args( ( CHAR_DATA *ch) );
void	replace_scorexp			args( ( CHAR_DATA *ch) );
//  bool	valid_player	       args( ( char *name) );
void	fix_scoremobm_length   args( ( ) );
void    fix_scorepk_length     args( ( ) );
void    fix_scoreqp_length     args( ( ) );
void    fix_scoregold_length   args( ( ) );
void    fix_scoremk_length args( ( ) );
void	fix_scoremp_length	args( ( ) );
void	fix_scoresp_length	args( ( ) );
void	fix_scorexp_length	args( ( ) );

int	count_scoremobm	       args( ( ) );
int     count_scoregold        args( ( ) );
int     count_scoreqp          args( ( ) );
int     count_scorepk          args( ( ) );
int	count_scoremk     args( ( ) );
int count_scoremp		args( ( ) );
int	count_scoresp		args( ( ) );
int count_scorexp		args( ( ) );

/* local function for save_scores */
void    save_scoremobm   args( ( ) );
void    save_scoregold   args( ( ) );
void    save_scoreqp     args( ( ) ); 
void    save_scorepk     args( ( ) );
void    save_scoremk     args( ( ) );
void	save_scoremp	args( ( ) );
void	save_scoresp	args( ( ) );
void	save_scorexp	args( ( ) );

/* This is the function that actually tallies a persons score and sets it up
to add it to the list, be sure to add it to do_save so that saving will adjust
the players scores */

void calc_scoremobm(CHAR_DATA *ch)
{
   int scoremobm=0;

   if (IS_NPC(ch)) /* Mobiles dont have pcdata */
    return;   

   if ( ch->level > 51 || ch->tmplevel > 51 ) /* Dont want to clutter your table with imms. */
    return;   

   scoremobm += ch->mobmastercomplete; 

 /* Now that we've calculated the score its time to set it */

  ch->pcdata->scoremobm = scoremobm;
  replace_scoremobm(ch);  /* use the data we just collected */
  return;
}

void calc_scorepk(CHAR_DATA *ch)
{ 
   int scorepk=0; 
    
   if (IS_NPC(ch)) /* Mobiles dont have pcdata */
    return; 
                                                          
   if ( ch->level > 51 || ch->tmplevel > 51 ) /* Dont want to clutter your table with imms. */
    return; 
   
   scorepk += ch->pcdata->pkills;    
        
 /* Now that we've calculated the score its time to set it */
   
  ch->pcdata->scorepk = scorepk; 
  replace_scorepk(ch);  /* use the data we just collected */
  return;
} 

void calc_scoreqp(CHAR_DATA *ch)
{ 
   int scoreqp=0; 
    
   if (IS_NPC(ch)) /* Mobiles dont have pcdata */
    return; 
                                                          
   if (ch->level > 51 || ch->tmplevel > 51) /* Dont want to clutter your table with imms. */
    return; 
   
   scoreqp += ch->pcdata->quest_accum;    
        
 /* Now that we've calculated the score its time to set it */
   
  ch->pcdata->scoreqp = scoreqp; 
  replace_scoreqp(ch);  /* use the data we just collected */
  return;
} 

void calc_scoregold(CHAR_DATA *ch)
{ 
   int scoregold=0; 
    
   if (IS_NPC(ch)) /* Mobiles dont have pcdata */
    return; 
                                                          
   if (ch->level > 51 || ch->tmplevel > 51) /* Dont want to clutter your table with imms. */
    return; 
   
   scoregold += ch->gold;
   scoregold += ch->pcdata->balance;    
        
 /* Now that we've calculated the score its time to set it */
   
  ch->pcdata->scoregold = scoregold; 
  replace_scoregold(ch);  /* use the data we just collected */
  return;
} 

void calc_scoremk(CHAR_DATA *ch)
{ 
   int scoremk=0;
 
   if (IS_NPC(ch)) /* Mobiles dont have pcdata */ 
    return; 
 
   if ( ch->level > 51 || ch->tmplevel > 51 ) /* Dont want to clutter your table with imms. */
    return;
  
   scoremk += ch->pcdata->mkills;
   
 /* Now that we've calculated the score its time to set it */ 
   
  ch->pcdata->scoremk = scoremk;
  replace_scoremk(ch);  /* use the data we just collected */
  return; 
}

void calc_scoremp(CHAR_DATA *ch)
{ 
   int scoremp=0;
 
   if (IS_NPC(ch)) /* Mobiles dont have pcdata */ 
    return; 
 
   if ( ch->level > 51 || ch->tmplevel > 51 ) /* Dont want to clutter your table with imms. */
    return;
  
   scoremp += ch->pcdata->magicpoints;
   
 /* Now that we've calculated the score its time to set it */ 
   
  ch->pcdata->scoremp = scoremp;
  replace_scoremp(ch);  /* use the data we just collected */
  return; 
}

void calc_scoresp(CHAR_DATA *ch)
{ 
   int scoresp=0;
 
   if (IS_NPC(ch)) /* Mobiles dont have pcdata */ 
    return; 
 
   if ( ch->level > 51 || ch->tmplevel > 51 ) /* Dont want to clutter your table with imms. */
    return;
  
   scoresp += ch->pcdata->skillpoints;
   
 /* Now that we've calculated the score its time to set it */ 
   
  ch->pcdata->scoresp = scoresp;
  replace_scoresp(ch);  /* use the data we just collected */
  return; 
}

void calc_scorexp(CHAR_DATA *ch)
{ 
   int scorexp=0;
 
   if (IS_NPC(ch)) /* Mobiles dont have pcdata */ 
    return; 
 
   if ( ch->level > 51 || ch->tmplevel > 51 ) /* Dont want to clutter your table with imms. */
    return;
  
   scorexp += ch->exp;
   if(IS_TIER(ch)) scorexp += ch->tierexp;
   
 /* Now that we've calculated the score its time to set it */ 
   
  ch->pcdata->scorexp = scorexp;
  replace_scorexp(ch);  /* use the data we just collected */
  return; 
}

/* The actual insertion of a new score */

void add_scoremobm( CHAR_DATA *ch)
{
 int value = ch->pcdata->scoremobm;
 SCOREMOBM_DATA *scoremobm, *newscoremobm;
 int i;

 if (IS_NPC(ch))
  return;

	for( i=1, scoremobm = first_scoremobm ; i <= MAX_SCOREMOBM ; scoremobm = scoremobm->next, i++ )
	{
		if( !scoremobm)
		/* there are empty slots at end of list, add there */
		{
			CREATE( newscoremobm, SCOREMOBM_DATA, 1 );
			newscoremobm->name = STRALLOC( ch->name );
			newscoremobm->scoremobm = value;
			LINK( newscoremobm, first_scoremobm, last_scoremobm, next, prev );
			break;
		}
/* This section inserts the higher value into the higher slot */
		else if( value > scoremobm->scoremobm )
		{
			CREATE( newscoremobm, SCOREMOBM_DATA, 1 );
			newscoremobm->name = STRALLOC( ch->name );
			newscoremobm->scoremobm = value;
			INSERT( newscoremobm, scoremobm, first_scoremobm, next, prev );
			break;
		}
	}

 fix_scoremobm_length();
 save_scoremobm();
 return;
}

void add_scoregold( CHAR_DATA *ch)
{    
 int value = ch->pcdata->scoregold;   
 SCOREGOLD_DATA *scoregold, *newscoregold;
 int i; 
  
 if (IS_NPC(ch)) 
  return;   
  
        for( i=1, scoregold = first_scoregold ; i <= MAX_SCOREGOLD ; scoregold = scoregold->next, i++ )
        {  
                if( !scoregold)
                /* there are empty slots at end of list, add there */
                { 
                        CREATE( newscoregold, SCOREGOLD_DATA, 1 );
                        newscoregold->name = STRALLOC( ch->name );
                        newscoregold->scoregold = value;
                        LINK( newscoregold, first_scoregold, last_scoregold, next, prev );
                        break; 
                }
/* This section inserts the higher value into the higher slot */
                else if( value > scoregold->scoregold )
                { 
                        CREATE( newscoregold, SCOREGOLD_DATA, 1 );
                        newscoregold->name = STRALLOC( ch->name );
                        newscoregold->scoregold = value;
                        INSERT( newscoregold, scoregold, first_scoregold, next, prev );
                        break;
                }
        }
  
 fix_scoregold_length();
 save_scoregold();
 return;
}

void add_scorepk( CHAR_DATA *ch)
{    
 int value = ch->pcdata->scorepk;   
 SCOREPK_DATA *scorepk, *newscorepk;
 int i; 
  
 if (IS_NPC(ch)) 
  return;   
  
        for( i=1, scorepk = first_scorepk ; i <= MAX_SCOREPK ; scorepk = scorepk->next, i++ )
        {  
                if( !scorepk)
                /* there are empty slots at end of list, add there */
                { 
                        CREATE( newscorepk, SCOREPK_DATA, 1 );
                        newscorepk->name = STRALLOC( ch->name );
                        newscorepk->scorepk = value;
                        LINK( newscorepk, first_scorepk, last_scorepk, next, prev );
                        break; 
                }
/* This section inserts the higher value into the higher slot */
                else if( value > scorepk->scorepk )
                { 
                        CREATE( newscorepk, SCOREPK_DATA, 1 );
                        newscorepk->name = STRALLOC( ch->name );
                        newscorepk->scorepk = value;
                        INSERT( newscorepk, scorepk, first_scorepk, next, prev );
                        break;
                }
        }
  
 fix_scorepk_length();
 save_scorepk();
 return;
}

void add_scoreqp( CHAR_DATA *ch)
{    
 int value = ch->pcdata->scoreqp;   
 SCOREQP_DATA *scoreqp, *newscoreqp;
 int i; 
  
 if (IS_NPC(ch)) 
  return;   
  
        for( i=1, scoreqp = first_scoreqp ; i <= MAX_SCOREQP ; scoreqp = scoreqp->next, i++ )
        {  
                if( !scoreqp)
                /* there are empty slots at end of list, add there */
                { 
                        CREATE( newscoreqp, SCOREQP_DATA, 1 );
                        newscoreqp->name = STRALLOC( ch->name );
                        newscoreqp->scoreqp = value;
                        LINK( newscoreqp, first_scoreqp, last_scoreqp, next, prev );
                        break; 
                }
/* This section inserts the higher value into the higher slot */
                else if( value > scoreqp->scoreqp )
                { 
                        CREATE( newscoreqp, SCOREQP_DATA, 1 );
                        newscoreqp->name = STRALLOC( ch->name );
                        newscoreqp->scoreqp = value;
                        INSERT( newscoreqp, scoreqp, first_scoreqp, next, prev );
                        break;
                }
        }
  
 fix_scoreqp_length();
 save_scoreqp();
 return;
}

void add_scoremk( CHAR_DATA *ch) 
{ 
 int value = ch->pcdata->scoremk;
 SCOREMK_DATA *scoremk, *newscoremk;
 int i; 
                 
 if (IS_NPC(ch)) 
  return; 
                         
        for( i=1, scoremk = first_scoremk ; i <= MAX_SCOREMK ; scoremk = scoremk->next, i++ )
        { 
                if( !scoremk) 
                /* there are empty slots at end of list, add there */
                {
                        CREATE( newscoremk, SCOREMK_DATA, 1 );
                        newscoremk->name = STRALLOC( ch->name );
                        newscoremk->scoremk = value;
                        LINK( newscoremk, first_scoremk, last_scoremk, next, prev );
                        break;
                } 
/* This section inserts the higher value into the higher slot */ 
                else if( value > scoremk->scoremk ) 
                { 
                        CREATE( newscoremk, SCOREMK_DATA, 1 );
                        newscoremk->name = STRALLOC( ch->name );
                        newscoremk->scoremk = value;
                        INSERT( newscoremk, scoremk, first_scoremk, next, prev );
                        break;
                } 
        } 
          
 fix_scoremk_length(); 
 save_scoremk(); 
 return; 
} 

void add_scoremp( CHAR_DATA *ch) 
{ 
 int value = ch->pcdata->scoremp;
 SCOREMP_DATA *scoremp, *newscoremp;
 int i; 
                 
 if (IS_NPC(ch)) 
  return; 
                         
        for( i=1, scoremp = first_scoremp ; i <= MAX_SCOREMP ; scoremp = scoremp->next, i++ )
        { 
                if( !scoremp) 
                /* there are empty slots at end of list, add there */
                {
                        CREATE( newscoremp, SCOREMP_DATA, 1 );
                        newscoremp->name = STRALLOC( ch->name );
                        newscoremp->scoremp = value;
                        LINK( newscoremp, first_scoremp, last_scoremp, next, prev );
                        break;
                } 
/* This section inserts the higher value into the higher slot */ 
                else if( value > scoremp->scoremp ) 
                { 
                        CREATE( newscoremp, SCOREMP_DATA, 1 );
                        newscoremp->name = STRALLOC( ch->name );
                        newscoremp->scoremp = value;
                        INSERT( newscoremp, scoremp, first_scoremp, next, prev );
                        break;
                } 
        } 
          
 fix_scoremp_length(); 
 save_scoremp(); 
 return; 
} 

void add_scoresp( CHAR_DATA *ch) 
{ 
 int value = ch->pcdata->scoresp;
 SCORESP_DATA *scoresp, *newscoresp;
 int i; 
                 
 if (IS_NPC(ch)) 
  return; 
                         
        for( i=1, scoresp = first_scoresp ; i <= MAX_SCORESP ; scoresp = scoresp->next, i++ )
        { 
                if( !scoresp) 
                /* there are empty slots at end of list, add there */
                {
                        CREATE( newscoresp, SCORESP_DATA, 1 );
                        newscoresp->name = STRALLOC( ch->name );
                        newscoresp->scoresp = value;
                        LINK( newscoresp, first_scoresp, last_scoresp, next, prev );
                        break;
                } 
/* This section inserts the higher value into the higher slot */ 
                else if( value > scoresp->scoresp ) 
                { 
                        CREATE( newscoresp, SCORESP_DATA, 1 );
                        newscoresp->name = STRALLOC( ch->name );
                        newscoresp->scoresp = value;
                        INSERT( newscoresp, scoresp, first_scoresp, next, prev );
                        break;
                } 
        } 
          
 fix_scoresp_length(); 
 save_scoresp(); 
 return; 
} 


void add_scorexp( CHAR_DATA *ch) 
{ 
 int value = ch->pcdata->scorexp;
 SCOREXP_DATA *scorexp, *newscorexp;
 int i; 
                 
 if (IS_NPC(ch)) 
  return; 
                         
        for( i=1, scorexp = first_scorexp ; i <= MAX_SCOREXP ; scorexp = scorexp->next, i++ )
        { 
                if( !scorexp) 
                /* there are empty slots at end of list, add there */
                {
                        CREATE( newscorexp, SCOREXP_DATA, 1 );
                        newscorexp->name = STRALLOC( ch->name );
                        newscorexp->scorexp = value;
                        LINK( newscorexp, first_scorexp, last_scorexp, next, prev );
                        break;
                } 
/* This section inserts the higher value into the higher slot */ 
                else if( value > scorexp->scorexp ) 
                { 
                        CREATE( newscorexp, SCOREXP_DATA, 1 );
                        newscorexp->name = STRALLOC( ch->name );
                        newscorexp->scorexp = value;
                        INSERT( newscorexp, scorexp, first_scorexp, next, prev );
                        break;
                } 
        } 
          
 fix_scorexp_length(); 
 save_scorexp(); 
 return; 
} 

/* This is used to determine ensure an existing score is removed before a new one
is added, so that you dont have repeats and so if a persons score drops, its actually
changed instead of staying forever at its highest point */

void replace_scoremobm( CHAR_DATA *ch)
{
 SCOREMOBM_DATA *scoremobm;

 if (IS_NPC(ch))
  return;

        for ( scoremobm = first_scoremobm; scoremobm; scoremobm = scoremobm->next )
         if( !str_cmp( ch->name, scoremobm->name ) )
          break;

   if (!scoremobm || (scoremobm->name != ch->name))
   {
     add_scoremobm(ch);
     return;
   }

   UNLINK( scoremobm, first_scoremobm, last_scoremobm, next, prev );
   STRFREE( scoremobm->name );
   DISPOSE( scoremobm );

   add_scoremobm(ch);
   return;
}

void replace_scoregold( CHAR_DATA *ch) 
{ 
 SCOREGOLD_DATA *scoregold; 
                         
 if (IS_NPC(ch)) 
  return; 
                 
        for ( scoregold = first_scoregold; scoregold; scoregold = scoregold->next )
         if( !str_cmp( ch->name, scoregold->name ) ) 
          break; 
                         
   if (!scoregold || (scoregold->name != ch->name)) 
   { 
     add_scoregold(ch);
     return;             
   }
  
   UNLINK( scoregold, first_scoregold, last_scoregold, next, prev );
   STRFREE( scoregold->name );
   DISPOSE( scoregold );
 
   add_scoregold(ch); 
   return; 
}

void replace_scorepk( CHAR_DATA *ch) 
{ 
 SCOREPK_DATA *scorepk; 
                         
 if (IS_NPC(ch)) 
  return; 
                 
        for ( scorepk = first_scorepk; scorepk; scorepk = scorepk->next )
         if( !str_cmp( ch->name, scorepk->name ) ) 
          break; 
                         
   if (!scorepk || (scorepk->name != ch->name)) 
   { 
     add_scorepk(ch);
     return;             
   }
  
   UNLINK( scorepk, first_scorepk, last_scorepk, next, prev );
   STRFREE( scorepk->name );
   DISPOSE( scorepk );
 
   add_scorepk(ch); 
   return; 
}

void replace_scoreqp( CHAR_DATA *ch) 
{ 
 SCOREQP_DATA *scoreqp; 
                         
 if (IS_NPC(ch)) 
  return; 
                 
        for ( scoreqp = first_scoreqp; scoreqp; scoreqp = scoreqp->next )
         if( !str_cmp( ch->name, scoreqp->name ) ) 
          break; 
                         
   if (!scoreqp || (scoreqp->name != ch->name)) 
   { 
     add_scoreqp(ch);
     return;             
   }
  
   UNLINK( scoreqp, first_scoreqp, last_scoreqp, next, prev );
   STRFREE( scoreqp->name );
   DISPOSE( scoreqp );
 
   add_scoreqp(ch); 
   return; 
}

void replace_scoremk( CHAR_DATA *ch)
{ 
 SCOREMK_DATA *scoremk;
    
 if (IS_NPC(ch)) 
  return;
  
        for ( scoremk = first_scoremk; scoremk; scoremk = scoremk->next )
         if( !str_cmp( ch->name, scoremk->name ) )
          break;
    
   if (!scoremk || (scoremk->name != ch->name)) 
   { 
     add_scoremk(ch);
     return;
   } 
    
   UNLINK( scoremk, first_scoremk, last_scoremk, next, prev );
   STRFREE( scoremk->name );
   DISPOSE( scoremk );
         
   add_scoremk(ch); 
   return; 
}

void replace_scoremp( CHAR_DATA *ch)
{ 
 SCOREMP_DATA *scoremp;
    
 if (IS_NPC(ch)) 
  return;
  
        for ( scoremp = first_scoremp; scoremp; scoremp = scoremp->next )
         if( !str_cmp( ch->name, scoremp->name ) )
          break;
    
   if (!scoremp || (scoremp->name != ch->name)) 
   { 
     add_scoremp(ch);
     return;
   } 
    
   UNLINK( scoremp, first_scoremp, last_scoremp, next, prev );
   STRFREE( scoremp->name );
   DISPOSE( scoremp );
         
   add_scoremp(ch); 
   return; 
}

void replace_scoresp( CHAR_DATA *ch)
{ 
 SCORESP_DATA *scoresp;
    
 if (IS_NPC(ch)) 
  return;
  
        for ( scoresp = first_scoresp; scoresp; scoresp = scoresp->next )
         if( !str_cmp( ch->name, scoresp->name ) )
          break;
    
   if (!scoresp || (scoresp->name != ch->name)) 
   { 
     add_scoresp(ch);
     return;
   } 
    
   UNLINK( scoresp, first_scoresp, last_scoresp, next, prev );
   STRFREE( scoresp->name );
   DISPOSE( scoresp );
         
   add_scoresp(ch); 
   return; 
}

void replace_scorexp( CHAR_DATA *ch)
{ 
 SCOREXP_DATA *scorexp;
    
 if (IS_NPC(ch)) 
  return;
  
        for ( scorexp = first_scorexp; scorexp; scorexp = scorexp->next )
         if( !str_cmp( ch->name, scorexp->name ) )
          break;
    
   if (!scorexp || (scorexp->name != ch->name)) 
   { 
     add_scorexp(ch);
     return;
   } 
    
   UNLINK( scorexp, first_scorexp, last_scorexp, next, prev );
   STRFREE( scorexp->name );
   DISPOSE( scorexp );
         
   add_scorexp(ch); 
   return; 
}
/* This will make sure it stays at only the max you want to display 
by checking to see how many total there are and cutting off the last one until
there are only the amount you want, default is 10 */

void fix_scoregold_length( )
{
  SCOREGOLD_DATA *scoregold;
  sh_int x;

  x = count_scoregold();

	while( x > MAX_SCOREGOLD )
	{
		scoregold = last_scoregold;
		UNLINK( scoregold, first_scoregold, last_scoregold, next, prev );
		STRFREE( scoregold->name );
		DISPOSE( scoregold );
                x = count_scoregold();
	}
}

void fix_scoremobm_length( ) 
{ 
  SCOREMOBM_DATA *scoremobm;
  sh_int x;
           
  x = count_scoremobm();
 
        while( x > MAX_SCOREMOBM)
        { 
                scoremobm = last_scoremobm;
                UNLINK( scoremobm, first_scoremobm, last_scoremobm, next, prev );
                STRFREE( scoremobm->name );
                DISPOSE( scoremobm );
                x = count_scoremobm(); 
        } 
} 

void fix_scorepk_length( ) 
{ 
  SCOREPK_DATA *scorepk;
  sh_int x;
           
  x = count_scorepk();
 
        while( x > MAX_SCOREPK )
        { 
                scorepk = last_scorepk;
                UNLINK( scorepk, first_scorepk, last_scorepk, next, prev );
                STRFREE( scorepk->name );
                DISPOSE( scorepk );
                x = count_scorepk(); 
        } 
} 

void fix_scoreqp_length( ) 
{ 
  SCOREQP_DATA *scoreqp;
  sh_int x;
           
  x = count_scoreqp();
 
        while( x > MAX_SCOREQP )
        { 
                scoreqp = last_scoreqp;
                UNLINK( scoreqp, first_scoreqp, last_scoreqp, next, prev );
                STRFREE( scoreqp->name );
                DISPOSE( scoreqp );
                x = count_scoreqp(); 
        } 
} 

void fix_scoremk_length( )
{ 
  SCOREMK_DATA *scoremk;
  sh_int x;
   
  x = count_scoremk();
         
        while( x > MAX_SCOREMK )
        { 
                scoremk = last_scoremk; 
                UNLINK( scoremk, first_scoremk, last_scoremk, next, prev );
                STRFREE( scoremk->name );
                DISPOSE( scoremk ); 
                x = count_scoremk();
        }
}

void fix_scoremp_length( )
{ 
  SCOREMP_DATA *scoremp;
  sh_int x;
   
  x = count_scoremp();
         
        while( x > MAX_SCOREMP )
        { 
                scoremp = last_scoremp; 
                UNLINK( scoremp, first_scoremp, last_scoremp, next, prev );
                STRFREE( scoremp->name );
                DISPOSE( scoremp ); 
                x = count_scoremp();
        }
}

void fix_scoresp_length( )
{ 
  SCORESP_DATA *scoresp;
  sh_int x;
   
  x = count_scoresp();
         
        while( x > MAX_SCORESP )
        { 
                scoresp = last_scoresp; 
                UNLINK( scoresp, first_scoresp, last_scoresp, next, prev );
                STRFREE( scoresp->name );
                DISPOSE( scoresp ); 
                x = count_scoresp();
        }
}

void fix_scorexp_length( )
{ 
  SCOREXP_DATA *scorexp;
  sh_int x;
   
  x = count_scorexp();
         
        while( x > MAX_SCOREXP )
        { 
                scorexp = last_scorexp; 
                UNLINK( scorexp, first_scorexp, last_scorexp, next, prev );
                STRFREE( scorexp->name );
                DISPOSE( scorexp ); 
                x = count_scorexp();
        }
}
/* very simple function to count how many scores are in memory */

int count_scoregold()
{
  SCOREGOLD_DATA *scoregold;
  sh_int x=0;

        for ( scoregold= first_scoregold; scoregold; scoregold= scoregold->next )
         ++x;
 return x;
         
}

int count_scorepk() 
{ 
  SCOREPK_DATA *scorepk;
  sh_int x=0;
                 
        for ( scorepk= first_scorepk; scorepk; scorepk= scorepk->next )
         ++x;
 return x; 
   
} 

int count_scoreqp() 
{ 
  SCOREQP_DATA *scoreqp;
  sh_int x=0;
                 
        for ( scoreqp= first_scoreqp; scoreqp; scoreqp= scoreqp->next )
         ++x;
 return x; 
   
} 

int count_scoremobm() 
{ 
  SCOREMOBM_DATA *scoremobm;
  sh_int x=0;
                 
        for ( scoremobm= first_scoremobm; scoremobm; scoremobm= scoremobm->next )
         ++x;
 return x; 
   
} 

int count_scoremk()
{ 
  SCOREMK_DATA *scoremk;
  sh_int x=0;
         
        for ( scoremk= first_scoremk; scoremk; scoremk= scoremk->next )
         ++x;
 return x; 
   
}  

int count_scoremp()
{ 
  SCOREMP_DATA *scoremp;
  sh_int x=0;
         
        for ( scoremp= first_scoremp; scoremp; scoremp= scoremp->next )
         ++x;
 return x; 
   
}  

int count_scoresp()
{ 
  SCORESP_DATA *scoresp;
  sh_int x=0;
         
        for ( scoresp= first_scoresp; scoresp; scoresp= scoresp->next )
         ++x;
 return x; 
   
}  

int count_scorexp()
{ 
  SCOREXP_DATA *scorexp;
  sh_int x=0;
         
        for ( scorexp= first_scorexp; scorexp; scorexp= scorexp->next )
         ++x;
 return x; 
   
}  
/* the actual command to see whos where */

void do_scoremobm( CHAR_DATA *ch, char *argument )
{
    SCOREMOBM_DATA *scoremobm;
    sh_int counter=1;

    ch_printf( ch, "    The Top %d Mob Masters.\n\r", MAX_SCOREMOBM);
    ch_printf( ch, "      Name        Score\n\r");
    ch_printf( ch, "-------------------------------\n\r");
        for ( scoremobm= first_scoremobm; scoremobm; scoremobm= scoremobm->next )
        {
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scoremobm->name, scoremobm->scoremobm);
          ++counter;
        }
    ch_printf( ch, "-------------------------------\n\r");
    return;
}

void do_scoregold( CHAR_DATA *ch, char *argument )
{                
    SCOREGOLD_DATA *scoregold;  
    sh_int counter=1;
   
    ch_printf( ch, "The Top %d Richest Players.\n\r", MAX_SCOREGOLD); 
    ch_printf( ch, "      Name        Gold\n\r");
    ch_printf( ch, "-------------------------------\n\r");
        for ( scoregold= first_scoregold; scoregold; scoregold= scoregold->next )
        {
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scoregold->name, scoregold->scoregold);
          ++counter; 
        }
    ch_printf( ch, "-------------------------------\n\r");
    return;  
} 

void do_scoreqp( CHAR_DATA *ch, char *argument )
{                
    SCOREQP_DATA *scoreqp;  
    sh_int counter=1;
   
    ch_printf( ch, "     The Top %d Questors.\n\r", MAX_SCOREQP); 
    ch_printf( ch, "      Name        Score\n\r");
    ch_printf( ch, "-------------------------------\n\r");
        for ( scoreqp= first_scoreqp; scoreqp; scoreqp= scoreqp->next )
        {
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scoreqp->name, scoreqp->scoreqp);
          ++counter; 
        }
    ch_printf( ch, "-------------------------------\n\r");
    return;  
} 

void do_scorepk( CHAR_DATA *ch, char *argument )
{                
    SCOREPK_DATA *scorepk;  
    sh_int counter=1;
   
    ch_printf( ch, "     The Top %d Player Killers.\n\r", MAX_SCOREPK); 
    ch_printf( ch, "      Name        Kills\n\r");
    ch_printf( ch, "-------------------------------\n\r");
        for ( scorepk= first_scorepk; scorepk; scorepk= scorepk->next )
        {
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scorepk->name, scorepk->scorepk);
          ++counter; 
        }
    ch_printf( ch, "-------------------------------\n\r");
    return;  
} 

void do_scoremk( CHAR_DATA *ch, char *argument )
{ 
    SCOREMK_DATA *scoremk;
    sh_int counter=1;
     
    ch_printf( ch, "     The Top %d Mob Killers.\n\r", MAX_SCOREMK);
    ch_printf( ch, "      Name        Kills\n\r"); 
    ch_printf( ch, "-------------------------------\n\r"); 
        for ( scoremk= first_scoremk; scoremk; scoremk= scoremk->next )
        { 
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scoremk->name, scoremk->scoremk);
          ++counter;
        } 
    ch_printf( ch, "-------------------------------\n\r");
    return;
}

void do_scoremp( CHAR_DATA *ch, char *argument )
{ 
    SCOREMP_DATA *scoremp;
    sh_int counter=1;
     
    ch_printf( ch, "     The Top %d Magic Questors.\n\r", MAX_SCOREMP);
    ch_printf( ch, "      Name        Score\n\r"); 
    ch_printf( ch, "-------------------------------\n\r"); 
        for ( scoremp= first_scoremp; scoremp; scoremp= scoremp->next )
        { 
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scoremp->name, scoremp->scoremp);
          ++counter;
        } 
    ch_printf( ch, "-------------------------------\n\r");
	save_scoremp();
    return;
}

void do_scoresp( CHAR_DATA *ch, char *argument )
{ 
    SCORESP_DATA *scoresp;
    sh_int counter=1;
     
    ch_printf( ch, "     The Top %d Skill Questors.\n\r", MAX_SCORESP);
    ch_printf( ch, "      Name        Score\n\r"); 
    ch_printf( ch, "-------------------------------\n\r"); 
        for ( scoresp= first_scoresp; scoresp; scoresp= scoresp->next )
        { 
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scoresp->name, scoresp->scoresp);
          ++counter;
        } 
    ch_printf( ch, "-------------------------------\n\r");
	save_scoresp();
    return;
}

void do_scorexp( CHAR_DATA *ch, char *argument )
{ 
    SCOREXP_DATA *scorexp;
    sh_int counter=1;
     
    ch_printf( ch, "     The Top %d Most Experienced.\n\r", MAX_SCOREXP);
    ch_printf( ch, "      Name        Score\n\r"); 
    ch_printf( ch, "-------------------------------\n\r"); 
        for ( scorexp= first_scorexp; scorexp; scorexp= scorexp->next )
        { 
          ch_printf( ch, "[%2d] %-12s %-32d\n\r", counter, scorexp->name, scorexp->scorexp);
          ++counter;
        } 
    ch_printf( ch, "-------------------------------\n\r");
	save_scorexp();
    return;
}

/*
 *  Additions to make persist over reboots.
 * in db.c look for: void	load_corpses	args( ( void ) );   and add:
 * void    load_scores     args( ( void ) );
 *
 * Then find: init_area_weather();
 * and add load_scores();  after it.
 * This will setup the routines to load you scores.dat when the mud opens.
 *
 * To make this section work you will need to place a call to save_scores()
 * just after fix_score_length in add_score, ie:
 * fix_score_length();
 * save_scores();
 *
 */

void load_scoremobm( )
{
   FILE *fp;
   SCOREMOBM_DATA *scoremobm;
   

   if( ( fp = fopen( SCOREMOBM_FILE, "r" ) ) == NULL )
   {
      bug( "Cannot open scoremobm.dat for reading", 0 );
      return;
   }
   
   for( ; ; )
   {
      char *word;
      
      word = fread_word( fp );
      
      if( !str_cmp( word, "Scoremobm" ) )
      {
         CREATE( scoremobm, SCOREMOBM_DATA, 1 );
         scoremobm->scoremobm = fread_number( fp );
         scoremobm->name = fread_string( fp );
         LINK( scoremobm, first_scoremobm, last_scoremobm, next, prev );
         continue;
      }
         
      if( !str_cmp( word, "End" ) )
      {
         fclose( fp );
         return;
      }
  }
   
}

void load_scorepk( )
{ 
   FILE *fp; 
   SCOREPK_DATA *scorepk; 
   
  
   if( ( fp = fopen( SCOREPK_FILE, "r" ) ) == NULL )
   { 
      bug( "Cannot open scorepk.dat for reading", 0 );
      return;
   }
    
   for( ; ; ) 
   { 
      char *word; 
 
      word = fread_word( fp );
 
      if( !str_cmp( word, "Scorepk" ) )
      { 
         CREATE( scorepk, SCOREPK_DATA, 1 );
         scorepk->scorepk = fread_number( fp );
         scorepk->name = fread_string( fp );
         LINK( scorepk, first_scorepk, last_scorepk, next, prev );
         continue; 
      }
    
      if( !str_cmp( word, "End" ) )
      {
         fclose( fp );
         return; 
      }
  } 
       
}

void load_scoremk( ) 
{         
   FILE *fp; 
   SCOREMK_DATA *scoremk;
          
          
   if( ( fp = fopen( SCOREMK_FILE, "r" ) ) == NULL )
   { 
      bug( "Cannot open scoremk.dat for reading", 0 );
      return;
   }
       
   for( ; ; )
   { 
      char *word;
        
      word = fread_word( fp );
    
      if( !str_cmp( word, "Scoremk" ) )
      {
         CREATE( scoremk, SCOREMK_DATA, 1 );
         scoremk->scoremk = fread_number( fp );
         scoremk->name = fread_string( fp );
         LINK( scoremk, first_scoremk, last_scoremk, next, prev );
         continue;
      }
    
      if( !str_cmp( word, "End" ) )
      { 
         fclose( fp );
         return; 
      } 
  } 
     
} 

void load_scoremp( ) 
{         
   FILE *fp; 
   SCOREMP_DATA *scoremp;
          
          
   if( ( fp = fopen( SCOREMP_FILE, "r" ) ) == NULL )
   { 
      bug( "Cannot open scoremp.dat for reading", 0 );
      return;
   }
       
   for( ; ; )
   { 
      char *word;
        
      word = fread_word( fp );
    
      if( !str_cmp( word, "Scoremp" ) )
      {
         CREATE( scoremp, SCOREMP_DATA, 1 );
         scoremp->scoremp = fread_number( fp );
         scoremp->name = fread_string( fp );
         LINK( scoremp, first_scoremp, last_scoremp, next, prev );
         continue;
      }
    
      if( !str_cmp( word, "End" ) )
      { 
         fclose( fp );
         return; 
      } 
  } 
     
} 

void load_scoresp( ) 
{         
   FILE *fp; 
   SCORESP_DATA *scoresp;
          
          
   if( ( fp = fopen( SCORESP_FILE, "r" ) ) == NULL )
   { 
      bug( "Cannot open scoresp.dat for reading", 0 );
      return;
   }
       
   for( ; ; )
   { 
      char *word;
        
      word = fread_word( fp );
    
      if( !str_cmp( word, "Scoresp" ) )
      {
         CREATE( scoresp, SCORESP_DATA, 1 );
         scoresp->scoresp = fread_number( fp );
         scoresp->name = fread_string( fp );
         LINK( scoresp, first_scoresp, last_scoresp, next, prev );
         continue;
      }
    
      if( !str_cmp( word, "End" ) )
      { 
         fclose( fp );
         return; 
      } 
  } 
     
} 

void load_scorexp( ) 
{         
   FILE *fp; 
   SCOREXP_DATA *scorexp;
          
          
   if( ( fp = fopen( SCOREXP_FILE, "r" ) ) == NULL )
   { 
      bug( "Cannot open scorexp.dat for reading", 0 );
      return;
   }
       
   for( ; ; )
   { 
      char *word;
        
      word = fread_word( fp );
    
      if( !str_cmp( word, "Scorexp" ) )
      {
         CREATE( scorexp, SCOREXP_DATA, 1 );
         scorexp->scorexp = fread_number( fp );
         scorexp->name = fread_string( fp );
         LINK( scorexp, first_scorexp, last_scorexp, next, prev );
         continue;
      }
    
      if( !str_cmp( word, "End" ) )
      { 
         fclose( fp );
         return; 
      } 
  } 
     
} 

void load_scoreqp( )
{ 
   FILE *fp; 
   SCOREQP_DATA *scoreqp; 
   
  
   if( ( fp = fopen( SCOREQP_FILE, "r" ) ) == NULL )
   { 
      bug( "Cannot open scoreqp.dat for reading", 0 );
      return;
   }
    
   for( ; ; ) 
   { 
      char *word; 
 
      word = fread_word( fp );
 
      if( !str_cmp( word, "Scoreqp" ) )
      { 
         CREATE( scoreqp, SCOREQP_DATA, 1 );
         scoreqp->scoreqp = fread_number( fp );
         scoreqp->name = fread_string( fp );
         LINK( scoreqp, first_scoreqp, last_scoreqp, next, prev );
         continue; 
      }
    
      if( !str_cmp( word, "End" ) )
      {
         fclose( fp );
         return; 
      }
  } 
       
}

void load_scoregold( )
{ 
   FILE *fp; 
   SCOREGOLD_DATA *scoregold; 
   
  
   if( ( fp = fopen( SCOREGOLD_FILE, "r" ) ) == NULL )
   { 
      bug( "Cannot open scoregold.dat for reading", 0 );
      return;
   }
    
   for( ; ; ) 
   { 
      char *word; 
 
      word = fread_word( fp );
 
      if( !str_cmp( word, "Scoregold" ) )
      { 
         CREATE( scoregold, SCOREGOLD_DATA, 1 );
         scoregold->scoregold = fread_number( fp );
         scoregold->name = fread_string( fp );
         LINK( scoregold, first_scoregold, last_scoregold, next, prev );
         continue; 
      }
    
      if( !str_cmp( word, "End" ) )
      {
         fclose( fp );
         return; 
      }
  } 
       
}

void save_scoremobm( )
{
   SCOREMOBM_DATA *scoremobm;
   FILE		*fp;
   
   if ( ( fp = fopen( SCOREMOBM_FILE, "w" ) ) == NULL )
   {
      bug( "Cannot open scoremobm.dat for writing", 0 );
      perror( SCOREMOBM_FILE );
      return;
   }

   for( scoremobm = first_scoremobm; scoremobm; scoremobm = scoremobm->next )
   {
    //~ if (!valid_player(scoremobm->name))
     //~ continue;
    //~ else
     fprintf( fp, "Scoremobm %d %s~\n", scoremobm->scoremobm, scoremobm->name );
   }

   fprintf( fp, "End\n\n" );
   fclose( fp );
}

void save_scoregold( ) 
{ 
   SCOREGOLD_DATA *scoregold;
   FILE         *fp; 
    
   if ( ( fp = fopen( SCOREGOLD_FILE, "w" ) ) == NULL )
   { 
      bug( "Cannot open scoregold.dat for writing", 0 );
      perror( SCOREGOLD_FILE ); 
      return; 
   } 
    
   for( scoregold = first_scoregold; scoregold; scoregold = scoregold->next )
   {
    //~ if (!valid_player(scoregold->name))
     //~ continue;
    //~ else
     fprintf( fp, "Scoregold %d %s~\n", scoregold->scoregold, scoregold->name );
   }
       
   fprintf( fp, "End\n\n" );
   fclose( fp );
}

void save_scorepk( ) 
{ 
   SCOREPK_DATA *scorepk;
   FILE         *fp; 
    
   if ( ( fp = fopen( SCOREPK_FILE, "w" ) ) == NULL )
   { 
      bug( "Cannot open scorepk.dat for writing", 0 );
      perror( SCOREPK_FILE ); 
      return; 
   } 
    
   for( scorepk = first_scorepk; scorepk; scorepk = scorepk->next )
   {
    //~ if (!valid_player(scorepk->name))
     //~ continue;
    //~ else
     fprintf( fp, "Scorepk %d %s~\n", scorepk->scorepk, scorepk->name );
   }
       
   fprintf( fp, "End\n\n" );
   fclose( fp );
} 

void save_scoreqp( ) 
{ 
   SCOREQP_DATA *scoreqp;
   FILE         *fp; 
    
   if ( ( fp = fopen( SCOREQP_FILE, "w" ) ) == NULL )
   { 
      bug( "Cannot open scoreqp.dat for writing", 0 );
      perror( SCOREQP_FILE ); 
      return; 
   } 
    
   for( scoreqp = first_scoreqp; scoreqp; scoreqp = scoreqp->next )
   {
    //~ if (!valid_player(scoreqp->name))
     //~ continue;
    //~ else
     fprintf( fp, "Scoreqp %d %s~\n", scoreqp->scoreqp, scoreqp->name );
   }
          
   fprintf( fp, "End\n\n" );
   fclose( fp );
} 

void save_scoremp( ) 
{ 
   SCOREMP_DATA *scoremp;
   FILE         *fp; 
    
   if ( ( fp = fopen( SCOREMP_FILE, "w" ) ) == NULL )
   { 
      bug( "Cannot open scoremp.dat for writing", 0 );
      perror( SCOREMP_FILE ); 
      return; 
   } 
    
   for( scoremp = first_scoremp; scoremp; scoremp = scoremp->next )
   {
    //~ if (!valid_player(scoremp->name))
     //~ continue;
    //~ else
     fprintf( fp, "Scoremp %d %s~\n", scoremp->scoremp, scoremp->name );
   }
          
   fprintf( fp, "End\n\n" );
   fclose( fp );
} 

void save_scoresp( ) 
{ 
   SCORESP_DATA *scoresp;
   FILE         *fp; 
    
   if ( ( fp = fopen( SCORESP_FILE, "w" ) ) == NULL )
   { 
      bug( "Cannot open scoresp.dat for writing", 0 );
      perror( SCORESP_FILE ); 
      return; 
   } 
    
   for( scoresp = first_scoresp; scoresp; scoresp = scoresp->next )
   {
    //~ if (!valid_player(scoresp->name))
     //~ continue;
    //~ else
     fprintf( fp, "Scoresp %d %s~\n", scoresp->scoresp, scoresp->name );
   }
          
   fprintf( fp, "End\n\n" );
   fclose( fp );
} 

void save_scorexp( ) 
{ 
   SCOREXP_DATA *scorexp;
   FILE         *fp; 
    
   if ( ( fp = fopen( SCOREXP_FILE, "w" ) ) == NULL )
   { 
      bug( "Cannot open scorexp.dat for writing", 0 );
      perror( SCOREXP_FILE ); 
      return; 
   } 
    
   for( scorexp = first_scorexp; scorexp; scorexp = scorexp->next )
   {
    //~ if (!valid_player(scorexp->name))
     //~ continue;
    //~ else
     fprintf( fp, "Scorexp %d %s~\n", scorexp->scorexp, scorexp->name );
   }
          
   fprintf( fp, "End\n\n" );
   fclose( fp );
} 

void save_scoremk( ) 
{ 
   SCOREMK_DATA *scoremk;
   FILE         *fp;
    
   if ( ( fp = fopen( SCOREMK_FILE, "w" ) ) == NULL )
   { 
      bug( "Cannot open scoremk.dat for writing", 0 );
      perror( SCOREMK_FILE );
      return; 
   } 
    
   for( scoremk = first_scoremk; scoremk; scoremk = scoremk->next )
   { 
    //~ if (!valid_player(scoremk->name))
     //~ continue;
    //~ else 
     fprintf( fp, "Scoremk %d %s~\n", scoremk->scoremk, scoremk->name );
   } 
    
   fprintf( fp, "End\n\n" );
   fclose( fp ); 
} 

/*
bool valid_player( char *name)
{
   char strsave[MAX_INPUT_LENGTH];
   FILE *fp = NULL;

   sprintf( strsave, "%s%s", GOD_DIR, capitalize( name) );
   if ( ( fp = fopen( strsave, "r" ) ) != NULL )
   {    
    fclose(fp);
    return TRUE; 
   }
   sprintf( strsave, "%s%c/%s",PLAYER_DIR,tolower(name[0]), capitalize( name ) );
   if( (fp = fopen( strsave, "r" ) ) != NULL )
   {
       fclose(fp);
       return FALSE;
   }

   return TRUE;
}
*/
