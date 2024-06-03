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
 *			 Low-level communication module			    *
 ****************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include "mud.h"
#ifdef USE_IMC
#include "imc.h"
#include "icec.h"
#endif


/*
 * Socket and TCP/IP stuff.
 */
#ifdef WIN32
  #include <io.h>
  #undef EINTR
  #undef EMFILE
  #define EINTR WSAEINTR
  #define EMFILE WSAEMFILE
  #define EWOULDBLOCK WSAEWOULDBLOCK
  #define MAXHOSTNAMELEN 32

  #define  TELOPT_ECHO        '\x01'
  #define  GA                 '\xF9'
  #define  SB                 '\xFA'
  #define  WILL               '\xFB'
  #define  WONT               '\xFC'
  #define  DO                 '\xFD'
  #define  DONT               '\xFE'
  #define  IAC                '\xFF'
  void bailout(void);
  void shutdown_checkpoint (void);
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netinet/in_systm.h>
  #include <netinet/ip.h>
  #include <arpa/inet.h>
  #include <arpa/telnet.h>
  #include <netdb.h>
  #define closesocket close
#endif

#ifdef sun
int gethostname ( char *name, int namelen );
#endif

const	char	echo_off_str	[] = { IAC, WILL, TELOPT_ECHO, '\0' };
const	char	echo_on_str	[] = { IAC, WONT, TELOPT_ECHO, '\0' };
const	char 	go_ahead_str	[] = { IAC, GA, '\0' };

void	auth_maxdesc	args( ( int *md, fd_set *ins, fd_set *outs,
				fd_set *excs ) );
void	auth_check	args( ( fd_set *ins, fd_set *outs, fd_set *excs ) );
void	set_auth	args( ( DESCRIPTOR_DATA *d ) );
void	kill_auth	args( ( DESCRIPTOR_DATA *d ) );
void	open_mud_lua	args( ( void ) );
void	close_mud_lua	args( ( void ) );

void    save_sysdata args( ( SYSTEM_DATA sys ) );

void shutdown_mud( char *reason );

/*
 * Global variables.
 */
IMMORTAL_HOST * immortal_host_start;    /* Start of Immortal legal domains */
IMMORTAL_HOST * immortal_host_end;    /* End of Immortal legal domains */
DESCRIPTOR_DATA *   first_descriptor;	/* First descriptor		*/
DESCRIPTOR_DATA *   last_descriptor;	/* Last descriptor		*/
DESCRIPTOR_DATA *   d_next;		/* Next descriptor in loop	*/
int		    num_descriptors;
FILE *		    fpReserve;		/* Reserved file handle		*/
bool		    mud_down;		/* Shutdown			*/
bool		    service_shut_down;  /* Shutdown by operator closing down service */
bool		    wizlock;		/* Game is wizlocked		*/
time_t              boot_time;
HOUR_MIN_SEC  	    set_boot_time_struct;
HOUR_MIN_SEC *      set_boot_time;
struct tm *         new_boot_time;
struct tm           new_boot_struct;
char		    str_boot_time[MAX_INPUT_LENGTH];
char		    lastplayercmd[MAX_INPUT_LENGTH*2];
time_t		    current_time;	/* Time of this pulse		*/
int		    control;		/* Controlling descriptor	*/
int		    control2;		/* Controlling descriptor #2	*/
int		    conclient;		/* MUDClient controlling desc	*/
int		    conjava;		/* JavaMUD controlling desc	*/
int		    newdesc;		/* New descriptor		*/
fd_set		    in_set;		/* Set of desc's for reading	*/
fd_set		    out_set;		/* Set of desc's for writing	*/
fd_set		    exc_set;		/* Set of desc's with errors	*/
int 		    maxdesc;
char *		    alarm_section = "(unknown)";

/*
 * OS-dependent local functions.
 */
void	game_loop		args( ( ) );
int	init_socket		args( ( int port ) );
void	new_descriptor		args( ( int new_desc ) );
bool	read_from_descriptor	args( ( DESCRIPTOR_DATA *d ) );
bool	write_to_descriptor	args( ( int desc, char *txt, int length ) );


/*
 * Other local functions (OS-independent).
 */
bool	check_parse_name	args( ( char *name, bool newchar ) );
bool	check_reconnect		args( ( DESCRIPTOR_DATA *d, char *name,
				    bool fConn ) );
bool	check_playing		args( ( DESCRIPTOR_DATA *d, char *name, bool kick ) );
int	main			args( ( int argc, char **argv ) );
void	nanny			args( ( DESCRIPTOR_DATA *d, char *argument ) );
bool	flush_buffer		args( ( DESCRIPTOR_DATA *d, bool fPrompt ) );
void	read_from_buffer	args( ( DESCRIPTOR_DATA *d ) );
void	stop_idling		args( ( CHAR_DATA *ch ) );
void	free_desc		args( ( DESCRIPTOR_DATA *d ) );
void	display_prompt		args( ( DESCRIPTOR_DATA *d ) );
int	make_color_sequence	args( ( const char *col, char *buf,
					DESCRIPTOR_DATA *d ) );
void	set_pager_input		args( ( DESCRIPTOR_DATA *d,
					char *argument ) );
bool	pager_output		args( ( DESCRIPTOR_DATA *d ) );

void	mail_count		args( ( CHAR_DATA *ch ) );

int port;

#ifdef WIN32
  int mainthread( int argc, char **argv )
#else
  int main( int argc, char **argv )
#endif
{
    struct timeval now_time;
    char hostn[128];
    bool fCopyOver = !TRUE;

    /*
     * Memory debugging if needed.
     */
#if defined(MALLOC_DEBUG)
    malloc_debug( 2 );
#endif

    DONT_UPPER			= FALSE;
    num_descriptors		= 0;
    first_descriptor		= NULL;
    last_descriptor		= NULL;
    sysdata.NO_NAME_RESOLVING	= TRUE;
    sysdata.WAIT_FOR_AUTH	= TRUE;

    /*
     * Init time.
     */
    gettimeofday( &now_time, NULL );
    current_time = (time_t) now_time.tv_sec;
/*  gettimeofday( &boot_time, NULL);   okay, so it's kludgy, sue me :) */
    boot_time = time(0);         /*  <-- I think this is what you wanted */
    strcpy( str_boot_time, ctime( &current_time ) );

    /*
     * Init boot time.
     */
    set_boot_time = &set_boot_time_struct;
    set_boot_time->manual = 0;
    
    new_boot_time = update_time(localtime(&current_time));
    /* Copies *new_boot_time to new_boot_struct, and then points
       new_boot_time to new_boot_struct again. -- Alty */
    new_boot_struct = *new_boot_time;
    new_boot_time = &new_boot_struct;
    new_boot_time->tm_mday += 7; // Number of days until automatic reboot
    new_boot_time->tm_sec = 0;  // sec to reboot
    new_boot_time->tm_min = 30;  // min to reboot
    new_boot_time->tm_hour = 12; // Hour to reboot - military time
    if(new_boot_time->tm_hour > 12)
    	new_boot_time->tm_mday += 1;

    /* Update new_boot_time (due to day increment) */
    new_boot_time = update_time(new_boot_time);
    new_boot_struct = *new_boot_time;
    new_boot_time = &new_boot_struct;
    /* Bug fix submitted by Gabe Yoder */
    new_boot_time_t = mktime(new_boot_time);
    reboot_check(mktime(new_boot_time));
    /* Set reboot time string for do_time */
    get_reboot_string();
    
    init_pfile_scan_time(); /* Pfile autocleanup initializer - Samson 5-8-99 */

    /*
     * Reserve two channels for our use.
     */
    if ( ( fpReserve = fopen( NULL_FILE, "r" ) ) == NULL )
    {
	perror( NULL_FILE );
	exit( 1 );
    }
    if ( ( fpLOG = fopen( NULL_FILE, "r" ) ) == NULL )
    {
	perror( NULL_FILE );
	exit( 1 );
    }

   /*
    * Get the port number.
    */
   port = 4000;
   if ( argc > 1 )
   {
	if ( !is_number( argv[1] ) )
	{
	    fprintf( stderr, "Usage: %s [port #]\n", argv[0] );
	    exit( 1 );
	}
	else if ( ( port = atoi( argv[1] ) ) <= 1024 )
	{
	    fprintf( stderr, "Port number must be above 1024.\n" );
	    exit( 1 );
	}

      if (argv[2] && argv[2][0])
      {
         fCopyOver = TRUE;
         control = atoi( argv[3] );
         control2 = atoi( argv[4] );
         conclient = atoi( argv[5] );
         conjava = atoi( argv[6] );
      }
      else
         fCopyOver = FALSE;
   }

    /*
     * Run the game.
     */
#ifdef WIN32
    {
	/* Initialise Windows sockets library */

	unsigned short wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsadata;
	int err;

	/* Need to include library: wsock32.lib for Windows Sockets */
	err = WSAStartup(wVersionRequested, &wsadata);
	if (err)
	{
	    fprintf(stderr, "Error %i on WSAStartup\n", err);
	    exit(1);
	}

	/* standard termination signals */
	signal(SIGINT, (void *) bailout);
	signal(SIGTERM, (void *) bailout);
  }
#endif /* WIN32 */

	log_string( "Initializing Lua" );
	open_mud_lua ();  /* initialize Lua engine */
    log_string("Booting Database");
    boot_db( fCopyOver );
    log_string("Initializing socket"); 
    if (!fCopyOver) /* We have already the port if copyover'ed */
    {
	control  = init_socket( port   );
	control2 = init_socket( port+1 );
	conclient= init_socket( port+10);
	conjava  = init_socket( port+20);
    }

    /* I don't know how well this will work on an unnamed machine as I don't
       have one handy, and the man pages are ever-so-helpful.. -- Alty */
    if (gethostname(hostn, sizeof(hostn)) < 0)
    {
      perror("main: gethostname");
      strcpy(hostn, "unresolved");
    }
    sprintf( log_buf, "%s ready at address %s on port %d.",
		sysdata.mud_name, hostn, port );
/*
    sprintf( log_buf, "Realms of Despair ready at address %s on port %d.",
	hostn, port );
*/
    log_string( log_buf );

    if( fCopyOver )
      {
         log_string( "Initiating hotboot recovery." );
         hotboot_recover();
      }

    game_loop( );
    
#ifdef USE_IMC
    imc_shutdown(); /* shut down IMC */
#endif
    
    closesocket( control  );
    closesocket( control2 );
    closesocket( conclient);
    closesocket( conjava  );

#ifdef WIN32
    if (service_shut_down)
    {
	CHAR_DATA *vch;

	/* Save all characters before booting. */
	for ( vch = first_char; vch; vch = vch->next )
	    if ( !IS_NPC( vch ) )
	    {
		shutdown_checkpoint ();
		save_char_obj( vch );
	    }
	}
    /* Shut down Windows sockets */
    
    WSACleanup();                 /* clean up */
    kill_timer();                 /* stop timer thread */
#endif


    /*
     * That's all, folks.
     */
    log_string( "Normal termination of game." );

    log_string( "Closing Lua." );
    close_mud_lua ();  /* finished with Lua */

    exit( 0 );
    return 0;
}


int init_socket( int port )
{
    char hostname[64];
    struct sockaddr_in	 sa;
    int x = 1;
    int fd;

    gethostname(hostname, sizeof(hostname));
    

    if ( ( fd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
	perror( "Init_socket: socket" );
	exit( 1 );
    }

    if ( setsockopt( fd, SOL_SOCKET, SO_REUSEADDR,
		    (void *) &x, sizeof(x) ) < 0 )
    {
	perror( "Init_socket: SO_REUSEADDR" );
	closesocket( fd );
	exit( 1 );
    }

#if defined(SO_DONTLINGER) && !defined(SYSV)
    {
	struct	linger	ld;

	ld.l_onoff  = 1;
	ld.l_linger = 1000;

	if ( setsockopt( fd, SOL_SOCKET, SO_DONTLINGER,
			(void *) &ld, sizeof(ld) ) < 0 )
	{
	    perror( "Init_socket: SO_DONTLINGER" );
	    closesocket( fd );
	    exit( 1 );
	}
    }
#endif

    memset(&sa, '\0', sizeof(sa));
    sa.sin_family   = AF_INET;
    sa.sin_port	    = htons( port );

    if ( bind( fd, (struct sockaddr *) &sa, sizeof(sa) ) == -1 )
    {
	perror( "Init_socket: bind" );
	closesocket( fd );
	exit( 1 );
    }

    if ( listen( fd, 50 ) < 0 )
    {
	perror( "Init_socket: listen" );
	closesocket( fd );
	exit( 1 );
    }

    return fd;
}

/*
static void SegVio()
{
  CHAR_DATA *ch;
  char buf[MAX_STRING_LENGTH];

  log_string( "SEGMENTATION VIOLATION" );
  log_string( lastplayercmd );
  for ( ch = first_char; ch; ch = ch->next )
  {
    sprintf( buf, "%cPC: %-20s room: %d", IS_NPC(ch) ? 'N' : ' ',
    		ch->name, ch->in_room->vnum );
    log_string( buf );  
  }
  exit(0);
}
*/

static void SigTerm( int signum )
{
   CHAR_DATA *vch;

   echo_to_all( AT_RED, "&RATTENTION!! Message from game server: &YEmergency shutdown called.\a", ECHOTAR_ALL );
   echo_to_all( AT_YELLOW, "Executing emergency shutdown proceedure.", ECHOTAR_ALL );
   log_string( "Message from server: Executing emergency shutdown proceedure." );
   shutdown_mud( "Emergency Shutdown" );

   if( auction->item )
      do_auction( supermob, "stop" );

   log_string( "Saving players...." );
   for( vch = first_char; vch; vch = vch->next )
   {
      if( !IS_NPC( vch ) ) 
      { 
         save_char_obj( vch );
	 snprintf( log_buf, MAX_STRING_LENGTH, "%s saved.", vch->name );
	 log_string( log_buf );
//	 if( vch->desc )
//	    write_to_descriptor( vch->desc, "You have been saved to disk.\n\r", 0 );
      }
   }

   /*  Save morphs so can sort later. --Shaddai */
   if( sysdata.morph_opt )
      save_morphs( );

   fflush( stderr );	/* make sure strerr is flushed */
   close( control );

#ifdef IMC
   imc_shutdown(); /* shut down IMC */
#endif
#ifdef I3
   I3_shutdown( 0 );
#endif 

   log_string( "Emergency shutdown complete." );

   /* Using exit here instead of mud_down because the thing sometimes failed to kill when asked!! */
   exit( 0 );
}


/*
 * LAG alarm!							-Thoric
 */
void caught_alarm()
{
    char buf[MAX_STRING_LENGTH];

    sprintf( buf, "ALARM CLOCK!  In section %s", buf );
    bug( buf );
    strcpy( buf, "Alas, the hideous malevalent entity known only as 'Lag' rises once more!\n\r" );
    echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL );
    if ( newdesc )
    {
	FD_CLR( newdesc, &in_set );
	FD_CLR( newdesc, &out_set );
	FD_CLR( newdesc, &exc_set );
	log_string( "clearing newdesc" );
    }
}

bool check_bad_desc( int desc )
{
    if ( FD_ISSET( desc, &exc_set ) )
    {
	FD_CLR( desc, &in_set );
	FD_CLR( desc, &out_set );
	log_string( "Bad FD caught and disposed." );
	return TRUE;
    }
    return FALSE;
}

/*
 * Determine whether this player is to be watched  --Gorog
 */
bool chk_watch(sh_int player_level, char *player_name, char *player_site)
{
    WATCH_DATA *pw;
/*
    char buf[MAX_INPUT_LENGTH];
    sprintf( buf, "che_watch entry: plev=%d pname=%s psite=%s",
                  player_level, player_name, player_site);
    log_string(buf);
*/
    if ( !first_watch ) return FALSE;

    for ( pw = first_watch; pw; pw = pw->next )
    {
        if ( pw->target_name )
        {
           if ( !str_cmp(pw->target_name, player_name)
           &&   player_level < pw->imm_level )
                 return TRUE;
        }
        else 
        if ( pw->player_site )
        {
           if ( !str_prefix(pw->player_site, player_site)
           &&   player_level < pw->imm_level )
                 return TRUE;
        }
    }
    return FALSE; 
}


void accept_new( int ctrl )
{
	static struct timeval null_time;
	DESCRIPTOR_DATA *d;
	/* int maxdesc; Moved up for use with id.c as extern */

#if defined(MALLOC_DEBUG)
	if ( malloc_verify( ) != 1 )
	    abort( );
#endif

	/*
	 * Poll all active descriptors.
	 */
	FD_ZERO( &in_set  );
	FD_ZERO( &out_set );
	FD_ZERO( &exc_set );
	FD_SET( ctrl, &in_set );
	maxdesc	= ctrl;
	newdesc = 0;
	for ( d = first_descriptor; d; d = d->next )
	{
	    maxdesc = UMAX( maxdesc, d->descriptor );
	    FD_SET( d->descriptor, &in_set  );
	    FD_SET( d->descriptor, &out_set );
	    FD_SET( d->descriptor, &exc_set );
	    if ( d == last_descriptor )
	      break;
	}
	auth_maxdesc(&maxdesc, &in_set, &out_set, &exc_set);
	
#ifdef USE_IMC
	maxdesc=imc_fill_fdsets(maxdesc, &in_set, &out_set, &exc_set);
#endif

	if ( select( maxdesc+1, &in_set, &out_set, &exc_set, &null_time ) < 0 )
	{
	    perror( "accept_new: select: poll" );
	    exit( 1 );
	}

	if ( FD_ISSET( ctrl, &exc_set ) )
	{
	    bug( "Exception raise on controlling descriptor %d", ctrl );
	    FD_CLR( ctrl, &in_set );
	    FD_CLR( ctrl, &out_set );
	}
	else
	if ( FD_ISSET( ctrl, &in_set ) )
	{
	    newdesc = ctrl;
	    new_descriptor( newdesc );
	}
}

void game_loop( )
{
    struct timeval	  last_time;
    char cmdline[MAX_INPUT_LENGTH];
    DESCRIPTOR_DATA *d;
/*  time_t	last_check = 0;  */

#ifndef WIN32
    signal( SIGPIPE, SIG_IGN );
    signal( SIGALRM, caught_alarm );
#endif

    /* signal( SIGSEGV, SegVio ); */

    signal( SIGTERM, SigTerm ); /* Catch kill signals */

    gettimeofday( &last_time, NULL );
    current_time = (time_t) last_time.tv_sec;

    /* Main loop */
    while ( !mud_down )
    {
	accept_new( control  );
	accept_new( control2 );
	accept_new( conclient);
	accept_new( conjava  );
	
	auth_check(&in_set, &out_set, &exc_set);
	
	/*
	 * Kick out descriptors with raised exceptions
	 * or have been idle, then check for input.
	 */
	for ( d = first_descriptor; d; d = d_next )
	{
	    if ( d == d->next )
	    {
	      bug( "descriptor_loop: loop found & fixed" );
	      d->next = NULL;
	    }
 	    d_next = d->next;   

	    d->idle++;	/* make it so a descriptor can idle out */
	    if ( FD_ISSET( d->descriptor, &exc_set ) )
	    {
		FD_CLR( d->descriptor, &in_set  );
		FD_CLR( d->descriptor, &out_set );
		if ( d->character
		&& ( d->connected == CON_PLAYING
		||   d->connected == CON_EDITING ) )
		    save_char_obj( d->character );
		d->outtop	= 0;
		close_socket( d, TRUE );
		continue;
	    }
	    else 
	    if ( (!d->character && d->idle > 360)		  /* 2 mins */
            ||   ( d->connected != CON_PLAYING && d->idle > 1200) /* 5 mins */
	    ||   (d->character && !IS_IMMORTAL(d->character) && d->idle > 28800)) /* 2 hrs  */
	    {
		write_to_descriptor( d->descriptor,
		 "Idle timeout... disconnecting.\n\r", 0 );
		d->outtop	= 0;
		close_socket( d, TRUE );
		continue;
	    }
	    else
	    {
		d->fcommand	= FALSE;

		if ( FD_ISSET( d->descriptor, &in_set ) )
		{
			d->idle = 0;
			if ( d->character )
			  d->character->timer = 0;
			if ( !read_from_descriptor( d ) )
			{
			    FD_CLR( d->descriptor, &out_set );
			    if ( d->character
			    && ( d->connected == CON_PLAYING
			    ||   d->connected == CON_EDITING ) )
				save_char_obj( d->character );
			    d->outtop	= 0;
			    close_socket( d, FALSE );
			    continue;
			}
		}

		if ( d->character && d->character->wait > 0 )
		{
			--d->character->wait;
			if(
			   ( d->character->wait == 0 ) && 
			   //( !d->character->fighting ) && 
			   ( xIS_SET( d->character->act, PLR_AUTOUPDATE_PROMPT ) )
			  )
				flush_buffer(d, TRUE);
			continue;
		}

		read_from_buffer( d );
		if ( d->incomm[0] != '\0' )
		{
			d->fcommand	= TRUE;
			stop_idling( d->character );

			strcpy( cmdline, d->incomm );
			d->incomm[0] = '\0';
			
			if ( d->character )
			  set_cur_char( d->character );

			if ( d->pagepoint )
			  set_pager_input(d, cmdline);
			else
			  switch( d->connected )
			  {
			   default:
                    if(d->character && IS_IMMORTAL(d->character))
                    {
                        switch(d->connected)
                        {
                            case CON_PRESS_ENTER:
                                strcpy(cmdline, "\n");
                                d->connected = CON_READ_MOTD;
                                break;
                            case CON_READ_MOTD:
                                strcpy(cmdline, "\n");
                                break;
                        }
                    }
                    nanny( d, cmdline );
				break;
			   case CON_PLAYING:
				//~ d->character->cmd_recurse = 0;
				interpret( d->character, cmdline );
				break;
			   case CON_EDITING:
				edit_buffer( d->character, cmdline );
				break;
			  }
		}
	    }
	    if ( d == last_descriptor )
	      break;
	}
	
#ifdef USE_IMC
	/* kick IMC */
	imc_idle_select(&in_set, &out_set, &exc_set, current_time);
#endif

	/*
	 * Autonomous game motion.
	 */
	update_handler( );

	/*
	 * Check REQUESTS pipe
	 */
        //~ check_requests( );

	/*
	 * Output.
	 */
	for ( d = first_descriptor; d; d = d_next )
	{
	    d_next = d->next;   

	    if ( ( d->fcommand || d->outtop > 0 )
	    &&   FD_ISSET(d->descriptor, &out_set) )
	    {
	        if ( d->pagepoint )
	        {
	          if ( !pager_output(d) )
	          {
	            if ( d->character
	            && ( d->connected == CON_PLAYING
	            ||   d->connected == CON_EDITING ) )
	                save_char_obj( d->character );
	            d->outtop = 0;
	            close_socket(d, FALSE);
	          }
	        }
		else if ( !flush_buffer( d, TRUE ) )
		{
		    if ( d->character
		    && ( d->connected == CON_PLAYING
		    ||   d->connected == CON_EDITING ) )
			save_char_obj( d->character );
		    d->outtop	= 0;
		    close_socket( d, FALSE );
		}
	    }
	    if ( d == last_descriptor )
	      break;
	}
	
	/*
	 * Synchronize to a clock.
	 * Sleep( last_time + 1/PULSE_PER_SECOND - now ).
	 * Careful here of signed versus unsigned arithmetic.
	 */
	{
	    struct timeval now_time;
	    long secDelta;
	    long usecDelta;

	    gettimeofday( &now_time, NULL );
	    usecDelta	= ((int) last_time.tv_usec) - ((int) now_time.tv_usec)
			+ 1000000 / PULSE_PER_SECOND;
	    secDelta	= ((int) last_time.tv_sec ) - ((int) now_time.tv_sec );
	    while ( usecDelta < 0 )
	    {
		usecDelta += 1000000;
		secDelta  -= 1;
	    }

	    while ( usecDelta >= 1000000 )
	    {
		usecDelta -= 1000000;
		secDelta  += 1;
	    }

	    if ( secDelta > 0 || ( secDelta == 0 && usecDelta > 0 ) )
	    {
		struct timeval stall_time;

		stall_time.tv_usec = usecDelta;
		stall_time.tv_sec  = secDelta;
#ifdef WIN32
		Sleep( (stall_time.tv_sec * 1000L) + (stall_time.tv_usec / 1000L) );
#else
		if ( select( 0, NULL, NULL, NULL, &stall_time ) < 0 && errno != EINTR )
		{
		    perror( "game_loop: select: stall" );
		    exit( 1 );
		}
#endif
	    }
	}

	gettimeofday( &last_time, NULL );
	current_time = (time_t) last_time.tv_sec;

        /* Check every 5 seconds...  (don't need it right now)
	if ( last_check+5 < current_time )
	{
	  CHECK_LINKS(first_descriptor, last_descriptor, next, prev,
	      DESCRIPTOR_DATA);
	  last_check = current_time;
	}
	*/
    }
    /*  Save morphs so can sort later. --Shaddai */
    if ( sysdata.morph_opt )
	save_morphs( );

    fflush(stderr);	/* make sure strerr is flushed */
    return;
}


void new_descriptor( int new_desc )
{
    char buf[MAX_STRING_LENGTH];
    DESCRIPTOR_DATA *dnew;
    struct sockaddr_in sock;
    struct hostent *from;
    int desc;
    int size;
    char bugbuf[MAX_STRING_LENGTH];
#ifdef WIN32
    unsigned long arg = 1;
#endif

    size = sizeof(sock);
    if ( check_bad_desc( new_desc ) )
    {
      set_alarm( 0 );
      return;
    }
    set_alarm( 20 );
    alarm_section = "new_descriptor::accept";
    if ( ( desc = accept( new_desc, (struct sockaddr *) &sock, (unsigned int *) &size) ) < 0 )
    {
	perror( "New_descriptor: accept" );
	sprintf(bugbuf, "[*****] BUG: New_descriptor: accept");
	log_string_plus( bugbuf, LOG_COMM, sysdata.log_level );
	set_alarm( 0 );
	return;
    }
    if ( check_bad_desc( new_desc ) )
    {
      set_alarm( 0 );
      return;
    }
#if !defined(FNDELAY)
#define FNDELAY O_NDELAY
#endif

    set_alarm( 20 );
    alarm_section = "new_descriptor: after accept";

#ifdef WIN32
    if ( ioctlsocket(desc, FIONBIO, &arg) == -1 )
#else
    if ( fcntl( desc, F_SETFL, FNDELAY ) == -1 )
#endif
    {
	perror( "New_descriptor: fcntl: FNDELAY" );
	set_alarm( 0 );
	return;
    }
    if ( check_bad_desc( new_desc ) )
      return;

    CREATE( dnew, DESCRIPTOR_DATA, 1 );
    dnew->next		= NULL;
    dnew->descriptor	= desc;
    dnew->connected	= CON_GET_NAME;
    dnew->outsize	= 2000;
    dnew->idle		= 0;
    dnew->lines		= 0;
    dnew->scrlen	= 24;
    dnew->port		= ntohs( sock.sin_port );
    dnew->user 		= STRALLOC("(unknown)");
    dnew->newstate	= 0;
    dnew->prevcolor	= 0x07;

    CREATE( dnew->outbuf, char, dnew->outsize );

    strcpy( buf, inet_ntoa( sock.sin_addr ) );
    sprintf( log_buf, "Sock.sinaddr:  %s, port %hd.",
		buf, dnew->port );
    log_string_plus( log_buf, LOG_COMM, sysdata.log_level );
    if ( sysdata.NO_NAME_RESOLVING )
      dnew->host = STRALLOC( buf );
    else
    {
       from = gethostbyaddr( (char *) &sock.sin_addr,
	  	sizeof(sock.sin_addr), AF_INET );
       dnew->host = STRALLOC( (char *)( from ? from->h_name : buf) );
    }

    if ( check_total_bans( dnew ) )
    {
          write_to_descriptor (desc,
                         "Your site has been banned from this Mud.\n\r", 0);
          free_desc (dnew);
          set_alarm (0);
          return;
     }

    /*
     * Init descriptor data.
     */

    if ( !last_descriptor && first_descriptor )
    {
	DESCRIPTOR_DATA *d;

	bug( "New_descriptor: last_desc is NULL, but first_desc is not! ...fixing" );
	for ( d = first_descriptor; d; d = d->next )
	   if ( !d->next )
		last_descriptor = d;
    }

    LINK( dnew, first_descriptor, last_descriptor, next, prev );

    /*
     * Send the greeting.
     */
    {
		extern char * help_greeting;
		extern char * help_greeting2;
		extern char * help_greeting3;
		extern char * help_greeting4;
		char * rand_greeting;
		switch(number_range(1,4))
		{
			case 1:  rand_greeting = help_greeting4;  break;
			case 2:  rand_greeting = help_greeting2; break;
			case 3:  rand_greeting = help_greeting3; break;
			case 4:  rand_greeting = help_greeting4; break;
			default: rand_greeting = help_greeting;  break;
		}
		if ( rand_greeting[0] == '.' )
			write_to_buffer( dnew, rand_greeting+1, 0 );
		else
			write_to_buffer( dnew, rand_greeting  , 0 );
    }

    alarm_section = "new_descriptor: set_auth";
    set_auth(dnew);
    alarm_section = "new_descriptor: after set_auth";

    if ( ++num_descriptors > sysdata.maxplayers )
	sysdata.maxplayers = num_descriptors;
    if ( sysdata.maxplayers > sysdata.alltimemax )
    {
	if ( sysdata.time_of_max )
	  DISPOSE(sysdata.time_of_max);
	sprintf(buf, "%24.24s", ctime(&current_time));
	sysdata.time_of_max = str_dup(buf);
	sysdata.alltimemax = sysdata.maxplayers;
	sprintf( log_buf, "Broke all-time maximum player record: %d", sysdata.alltimemax );
	log_string_plus( log_buf, LOG_COMM, sysdata.log_level );
	to_channel( log_buf, CHANNEL_MONITOR, "Monitor", LEVEL_IMMORTAL );
	save_sysdata( sysdata );
    }
    set_alarm(0);
    return;
}

void free_desc( DESCRIPTOR_DATA *d )
{
    kill_auth(d);
    closesocket( d->descriptor );
    STRFREE( d->host );
    DISPOSE( d->outbuf );
    STRFREE( d->user );    /* identd */
    if ( d->pagebuf )
	DISPOSE( d->pagebuf );
    DISPOSE( d );
/*    --num_descriptors;  This is called from more than close_socket -- Alty */
    return;
}

void close_socket( DESCRIPTOR_DATA *dclose, bool force )
{
    CHAR_DATA *ch;
    DESCRIPTOR_DATA *d;
    bool DoNotUnlink = FALSE;

    /* flush outbuf */
    if ( !force && dclose->outtop > 0 )
	flush_buffer( dclose, FALSE );

    /* say bye to whoever's snooping this descriptor */
    if ( dclose->snoop_by )
	write_to_buffer( dclose->snoop_by,
	    "Your victim has left the game.\n\r", 0 );

    /* stop snooping everyone else */
    for ( d = first_descriptor; d; d = d->next )
	if ( d->snoop_by == dclose )
	  d->snoop_by = NULL;

    /* Check for switched people who go link-dead. -- Altrag */
    if ( dclose->original )
    {
	if ( ( ch = dclose->character ) != NULL )
	  do_return(ch, "");
	else
	{
	  bug( "Close_socket: dclose->original without character %s",
		(dclose->original->name ? dclose->original->name : "unknown") );
	  dclose->character = dclose->original;
	  dclose->original = NULL;
	}
    }
    
    ch = dclose->character;

    /* sanity check :( */
    if ( !dclose->prev && dclose != first_descriptor )
    {
	DESCRIPTOR_DATA *dp, *dn;
	bug( "Close_socket: %s desc:%p != first_desc:%p and desc->prev = NULL!",
		ch ? ch->name : d->host, dclose, first_descriptor );
	dp = NULL;
	for ( d = first_descriptor; d; d = dn )
	{
	   dn = d->next;
	   if ( d == dclose )
	   {
		bug( "Close_socket: %s desc:%p found, prev should be:%p, fixing.",
		    ch ? ch->name : d->host, dclose, dp );
		dclose->prev = dp;
		break;
	   }
	   dp = d;
	}
	if ( !dclose->prev )
	{
	    bug( "Close_socket: %s desc:%p could not be found!.",
		    ch ? ch->name : dclose->host, dclose );
	    DoNotUnlink = TRUE;
	}
    }
    if ( !dclose->next && dclose != last_descriptor )
    {
	DESCRIPTOR_DATA *dp, *dn;
	bug( "Close_socket: %s desc:%p != last_desc:%p and desc->next = NULL!",
		ch ? ch->name : d->host, dclose, last_descriptor );
	dn = NULL;
	for ( d = last_descriptor; d; d = dp )
	{
	   dp = d->prev;
	   if ( d == dclose )
	   {
		bug( "Close_socket: %s desc:%p found, next should be:%p, fixing.",
		    ch ? ch->name : d->host, dclose, dn );
		dclose->next = dn;
		break;
	   }
	   dn = d;
	}
	if ( !dclose->next )
	{
	    bug( "Close_socket: %s desc:%p could not be found!.",
		    ch ? ch->name : dclose->host, dclose );
	    DoNotUnlink = TRUE;
	}
    }

    if ( dclose->character )
    {
	sprintf( log_buf, "Closing link to %s.", ch->pcdata->filename );
	log_string_plus( log_buf, LOG_COMM, UMAX( sysdata.log_level, ch->level ) );
/*
	if ( ch->level < LEVEL_DEMI )
	  to_channel( log_buf, CHANNEL_MONITOR, "Monitor", ch->level );
*/
	if ( dclose->connected == CON_PLAYING
	||   dclose->connected == CON_EDITING
	||   dclose->connected == CON_ROLL_STATS
        ||   dclose->connected == CON_DELETE )
	{
	    act( AT_ACTION, "$n has lost $s link.", ch, NULL, NULL, TO_CANSEE );
	    ch->desc = NULL;
		//if(IS_IMMORTAL(ch)) /* Force LinkDead immortals to quit immediatly -Darwin */
		//	do_quit(ch, "");
	}
	else
	{
	    /* clear descriptor pointer to get rid of bug message in log */
	    dclose->character->desc = NULL;
	    free_char( dclose->character );
	}
    }


    if ( !DoNotUnlink )
    {
	/* make sure loop doesn't get messed up */
	if ( d_next == dclose )
	  d_next = d_next->next;
	UNLINK( dclose, first_descriptor, last_descriptor, next, prev );
    }

    if ( dclose->descriptor == maxdesc )
      --maxdesc;

    free_desc( dclose );
    --num_descriptors;
    return;
}


bool read_from_descriptor( DESCRIPTOR_DATA *d )
{
    int iStart, iErr;

    /* Hold horses if pending command already. */
    if ( d->incomm[0] != '\0' )
	return TRUE;

    /* Check for overflow. */
    iStart = strlen(d->inbuf);
    if ( iStart >= sizeof(d->inbuf) - 10 )
    {
	sprintf( log_buf, "%s input overflow!", d->host );
	log_string( log_buf );
	write_to_descriptor( d->descriptor,
	    "\n\r*** PUT A LID ON IT!!! ***\n\rYou cannot enter the same command more than 20 consecutive times!\n\r", 0 );
	return FALSE;
    }
    for ( ; ; )
    {
	int nRead;

	nRead = recv( d->descriptor, d->inbuf + iStart,
	    sizeof(d->inbuf) - 10 - iStart, 0 );
#ifdef WIN32
	iErr = WSAGetLastError ();
#else
	iErr = errno;
#endif
	if ( nRead > 0 )
	{
	    iStart += nRead;
	    if ( d->inbuf[iStart-1] == '\n' || d->inbuf[iStart-1] == '\r' )
		break;
	}
	else if ( nRead == 0 )
	{
	    log_string_plus( "EOF encountered on read.", LOG_COMM, sysdata.log_level );
	    return FALSE;
	}
	else if ( iErr == EWOULDBLOCK )
	    break;
	else
	{
	    perror( "Read_from_descriptor" );
	    return FALSE;
	}
    }

    d->inbuf[iStart] = '\0';
    return TRUE;
}



/*
 * Transfer one line from input buffer to input line.
 */
void read_from_buffer( DESCRIPTOR_DATA *d )
{
    int i, j, k;

    /*
     * Hold horses if pending command already.
     */
    if ( d->incomm[0] != '\0' )
	return;

    /*
     * Look for at least one new line.
     */
    for ( i = 0; d->inbuf[i] != '\n' && d->inbuf[i] != '\r' && i<MAX_INBUF_SIZE;
	  i++ )
    {
	if ( d->inbuf[i] == '\0' )
	    return;
    }

    /*
     * Canonical input processing.
     */
    for ( i = 0, k = 0; d->inbuf[i] != '\n' && d->inbuf[i] != '\r'; i++ )
    {
	if ( k >= 254 )
	{
	    write_to_descriptor( d->descriptor, "Line too long.\n\r", 0 );

	    /* skip the rest of the line */
	    /*
	    for ( ; d->inbuf[i] != '\0' || i>= MAX_INBUF_SIZE ; i++ )
	    {
		if ( d->inbuf[i] == '\n' || d->inbuf[i] == '\r' )
		    break;
	    }
	    */
	    d->inbuf[i]   = '\n';
	    d->inbuf[i+1] = '\0';
	    break;
	}

	if ( d->inbuf[i] == '\b' && k > 0 )
	    --k;
	else if ( isascii(d->inbuf[i]) && isprint(d->inbuf[i]) )
	    d->incomm[k++] = d->inbuf[i];
    }

    /*
     * Finish off the line.
     */
    if ( k == 0 )
	d->incomm[k++] = ' ';
    d->incomm[k] = '\0';

    /*
     * Deal with bozos with #repeat 1000 ...
     */
    if ( k > 1 || d->incomm[0] == '!' )
    {
	if ( d->incomm[0] != '!' && strcmp( d->incomm, d->inlast ) )
	{
	    d->repeat = 0;
	}
	else
	{
	    if ( ++d->repeat >= 40 )
	    {
		sprintf( log_buf, "%s input spamming!", d->host );
		log_string( log_buf );
		write_to_descriptor( d->descriptor,
		    "\n\r*** PUT A LID ON IT!!! ***\n\rYou cannot enter the same command more than 40 consecutive times!\n\r", 0 );
		write_to_descriptor( d->descriptor, "This has been logged.  Repeated occurrences will cause problems for you.\n\r", 0 );
//		strcpy( d->incomm, "quit" );
	    }
	}
    }

    /*
     * Do '!' substitution.
     */
    if ( d->incomm[0] == '!' )
	strcpy( d->incomm, d->inlast );
    else
	strcpy( d->inlast, d->incomm );

    /*
     * Shift the input buffer.
     */
    while ( d->inbuf[i] == '\n' || d->inbuf[i] == '\r' )
	i++;
    for ( j = 0; ( d->inbuf[j] = d->inbuf[i+j] ) != '\0'; j++ )
	;
    return;
}



/*
 * Low level output function.
 */
bool flush_buffer( DESCRIPTOR_DATA *d, bool fPrompt )
{
    char buf[MAX_INPUT_LENGTH];
    extern bool mud_down;

    /*
     * If buffer has more than 4K inside, spit out .5K at a time   -Thoric
     */
    if ( !mud_down && d->outtop > 4096 )
    {
	memcpy( buf, d->outbuf, 512 );
	d->outtop -= 512;
	memmove( d->outbuf, d->outbuf + 512, d->outtop );
	if ( d->snoop_by )
	{
	    char snoopbuf[MAX_INPUT_LENGTH];

	    buf[512] = '\0';
	    if ( d->character && d->character->name )
	    {
		if (d->original && d->original->name)
		    sprintf( snoopbuf, "%s (%s)", d->character->name, d->original->name );
		else          
		    sprintf( snoopbuf, "%s", d->character->name);
		write_to_buffer( d->snoop_by, snoopbuf, 0);
	    }
	    write_to_buffer( d->snoop_by, "% ", 2 );
	    write_to_buffer( d->snoop_by, buf, 0 );
	}
        if ( !write_to_descriptor( d->descriptor, buf, 512 ) )
        {
	    d->outtop = 0;
	    return FALSE;
        }
        return TRUE;
    }
                                                                                        

    /*
     * Bust a prompt.
     */
    if ( fPrompt && !mud_down && d->connected == CON_PLAYING )
    {
	CHAR_DATA *ch;

	ch = d->original ? d->original : d->character;
	if ( xIS_SET(ch->act, PLR_BLANK) )
	    write_to_buffer( d, "\n\r", 2 );

	    
	if ( xIS_SET(ch->act, PLR_PROMPT) )
	    display_prompt(d);
	if ( xIS_SET(ch->act, PLR_TELNET_GA) )
	    write_to_buffer( d, go_ahead_str, 0 );
    }

    /*
     * Short-circuit if nothing to write.
     */
    if ( d->outtop == 0 )
	return TRUE;

    /*
     * Snoop-o-rama.
     */
    if ( d->snoop_by )
    {
        /* without check, 'force mortal quit' while snooped caused crash, -h */
	if ( d->character && d->character->name )
	{
	    /* Show original snooped names. -- Altrag */
	    if ( d->original && d->original->name )
		sprintf( buf, "%s (%s)", d->character->name, d->original->name );
	    else
		sprintf( buf, "%s", d->character->name);
	    write_to_buffer( d->snoop_by, buf, 0);
	}
	write_to_buffer( d->snoop_by, "% ", 2 );
	write_to_buffer( d->snoop_by, d->outbuf, d->outtop );
    }

    /*
     * OS-dependent output.
     */
    if ( !write_to_descriptor( d->descriptor, d->outbuf, d->outtop ) )
    {
	d->outtop = 0;
	return FALSE;
    }
    else
    {
	d->outtop = 0;
	return TRUE;
    }
}



/*
 * Append onto an output buffer.
 */
void write_to_buffer( DESCRIPTOR_DATA *d, const char *txt, int length )
{
    if ( !d )
    {
	bug( "Write_to_buffer: NULL descriptor" );
	return;
    }

    /*
     * Normally a bug... but can happen if loadup is used.
     */
    if ( !d->outbuf )
    	return;

    /*
     * Find length in case caller didn't.
     */
    if ( length <= 0 )
	length = strlen(txt);

/* Uncomment if debugging or something
    if ( length != strlen(txt) )
    {
	bug( "Write_to_buffer: length(%d) != strlen(txt)!", length );
	length = strlen(txt);
    }
*/

    /*
     * Initial \n\r if needed.
     */
    if ( d->outtop == 0 && !d->fcommand )
    {
	d->outbuf[0]	= '\n';
	d->outbuf[1]	= '\r';
	d->outtop	= 2;
    }

    /*
     * Expand the buffer as needed.
     */
    while ( d->outtop + length >= d->outsize )
    {
        if (d->outsize > 32000)
	{
	    /* empty buffer */
	    d->outtop = 0;
	    bug("Buffer overflow. Closing (%s).", d->character ? d->character->name : "???" );
	    close_socket(d, TRUE);
	    return;
 	}
	d->outsize *= 2;
	RECREATE( d->outbuf, char, d->outsize );
    }

    /*
     * Copy.
     */
    strncpy( d->outbuf + d->outtop, txt, length );
    d->outtop += length;
    d->outbuf[d->outtop] = '\0';
    return;
}


/*
 * Lowest level output function.
 * Write a block of text to the file descriptor.
 * If this gives errors on very long blocks (like 'ofind all'),
 *   try lowering the max block size.
 */
bool write_to_descriptor( int desc, char *txt, int length )
{
    int iStart;
    int nWrite;
    int nBlock;

    if ( length <= 0 )
	length = strlen(txt);

    for ( iStart = 0; iStart < length; iStart += nWrite )
    {
	nBlock = UMIN( length - iStart, 4096 );
	if ( ( nWrite = send( desc, txt + iStart, nBlock, 0 ) ) < 0 )
	    { perror( "Write_to_descriptor" ); return FALSE; }
    }

    return TRUE;
}



void show_title( DESCRIPTOR_DATA *d )
{
    CHAR_DATA *ch;

    ch = d->character;

    if ( !IS_SET( ch->pcdata->flags, PCFLAG_NOINTRO ) )
    {
        if (xIS_SET(ch->act, PLR_RIP))
            send_rip_title(ch);
        else
        if (xIS_SET(ch->act, PLR_ANSI))
            send_ansi_title(ch);
        else
            send_ascii_title(ch);
    }
    else
    {
        write_to_buffer( d, "Press enter...\n\r", 0 );
    }
    d->connected = CON_PRESS_ENTER;
}

/*
 * Deal with sockets that haven't logged in yet.
 */
void nanny( DESCRIPTOR_DATA *d, char *argument )
{
/*	extern int lang_array[];
	extern char *lang_names[];*/
    char buf[MAX_STRING_LENGTH];
    char arg[MAX_STRING_LENGTH];
    CHAR_DATA *ch;
    char *pwdnew;
    char *p;
    int iClass;
    int iRace;
    bool fOld, chk;

    while ( isspace(*argument) )
	argument++;

    ch = d->character;

    switch ( d->connected )
    {

    default:
	bug( "Nanny: bad d->connected %d.", d->connected );
	close_socket( d, TRUE );
	return;

    case CON_GET_NAME:
	if ( argument[0] == '\0' )
	{
	    close_socket( d, FALSE );
	    return;
	}

	argument[0] = UPPER(argument[0]);

	/* Old players can keep their characters. -- Alty */
	if ( !check_parse_name( argument, (d->newstate != 0) ) )
	{
	    write_to_buffer( d, "Illegal name, try another.\n\rName: ", 0 );
	    return;
	}
                                                
        if ( !str_cmp( argument, "New" ) )
	{
	    if (d->newstate == 0)
	    {
            /* New player */
            /* Don't allow new players if DENY_NEW_PLAYERS is true */
            if (sysdata.DENY_NEW_PLAYERS == TRUE)
            {
                sprintf( buf, "The mud is currently preparing for a reboot.\n\r" );
                write_to_buffer( d, buf, 0 );
                sprintf( buf, "New players are not accepted during this time.\n\r" );
                write_to_buffer( d, buf, 0 );
                sprintf( buf, "Please try again in a few minutes.\n\r" );
                write_to_buffer( d, buf, 0 );
                close_socket( d, FALSE );
            }
            sprintf( buf,   "\n\rChoosing a name is one of the most important parts of this game...\n\r"
                            "Make sure to pick a name appropriate to the character you are going\n\r"
                            "to role play, and be sure that it suits a medieval theme.\n\r"
                            "If the name you select is not acceptable, you will be asked to choose\n\r"
                            "another one. Your character name may contain one space and one apostrophe."
                            "\n\r\n\rPlease choose a name for your character: ");
            write_to_buffer( d, buf, 0 );
            d->newstate++;
            d->connected = CON_GET_NAME;
            return;
	    }
	    else
   	    {
	      write_to_buffer(d, "Illegal name, try another.\n\rName: ", 0);
	      return;
	    }
	}

	if ( check_playing( d, argument, FALSE ) == BERR )
	{
	    write_to_buffer( d, "Name: ", 0 );
	    return;
	}

	fOld = load_char_obj( d, argument, TRUE, FALSE );
	if ( !d->character )
	{
	    sprintf( log_buf, "Bad player file %s@%s.", argument, d->host );
	    log_string( log_buf );
	    write_to_buffer( d, "Your playerfile is corrupt...Please notify darwin.hog@gmail.com.\n\r", 0 );
	    close_socket( d, FALSE );
	    return;
	}
	ch   = d->character;
      if ( check_bans( ch, BAN_SITE ) )
      {
              write_to_buffer (d,
                         "Your site has been banned from this Mud.\n\r", 0);
              close_socket (d, FALSE);
              return;
      }

      if ( fOld ) {
      if ( check_bans( ch, BAN_CLASS ) )
      {
              write_to_buffer (d,
                         "Your class has been banned from this Mud.\n\r", 0);
              close_socket (d, FALSE);
              return;
      }
      if ( check_bans( ch, BAN_RACE ) )
      {
              write_to_buffer (d,
                         "Your race has been banned from this Mud.\n\r", 0);
              close_socket (d, FALSE);
              return;
      }
      }

	if ( xIS_SET(ch->act, PLR_DENY) )
	{
	    sprintf( log_buf, "Denying access to %s@%s.", argument, d->host );
	    log_string_plus( log_buf, LOG_COMM, sysdata.log_level );
	    if (d->newstate != 0)
	    {
              write_to_buffer( d, "That name is already taken.  Please choose another: ", 0 );
	      d->connected = CON_GET_NAME;
	      d->character->desc = NULL;
	      free_char( d->character ); /* Big Memory Leak before --Shaddai */
	      d->character = NULL;
	      return;
	    }
	    write_to_buffer( d, "You are denied access.\n\r", 0 );
	    close_socket( d, FALSE );
	    return;
	}
      /*
       *  Make sure the immortal host is from the correct place.
       *  Shaddai
       */

      if ( IS_IMMORTAL(ch) && sysdata.check_imm_host
           && !check_immortal_domain( ch , d->host) )
        {
        sprintf (log_buf, "%s's char being hacked from %s.", argument, d->host);
        log_string_plus (log_buf, LOG_COMM, sysdata.log_level);
        write_to_buffer (d, "This hacking attempt has been logged.\n\r", 0);
        close_socket (d, FALSE);
        return;
        }


	chk = check_reconnect( d, argument, FALSE );
	if ( chk == BERR )
	  return;

	if ( chk )
	{
	    fOld = TRUE;
	}
	else
	{
	    if ( wizlock && !IS_IMMORTAL(ch) )
	    {
		write_to_buffer( d, "The game is wizlocked.  Only immortals can connect now.\n\r", 0 );
		write_to_buffer( d, "Please try back later.\n\r", 0 );
		close_socket( d, FALSE );
		return;
	    }
	}

	if ( fOld )
	{
	    if (d->newstate != 0)
	    {
	      write_to_buffer( d, "That name is already taken.  Please choose another: ", 0 );
	      d->connected = CON_GET_NAME;
	      d->character->desc = NULL;
	      free_char( d->character ); /* Big Memory Leak before --Shaddai */
	      d->character = NULL;
	      return;
	    }
	    /* Old player */
	    write_to_buffer( d, "Password: ", 0 );
	    write_to_buffer( d, echo_off_str, 0 );
	    d->connected = CON_GET_OLD_PASSWORD;
	    return;
	}
	else
	{
	    /*if ( !check_parse_name( argument ) )
	    {
		write_to_buffer( d, "Illegal name, try another.\n\rName: ", 0 );
		return;
	    }*/

	    if (d->newstate == 0)
	    {
	      /* No such player */
	      write_to_buffer( d, "\n\rNo such player exists.\n\rPlease check your spelling, or type NEW to start a new player.\n\r\n\rName: ", 0 );
	      d->connected = CON_GET_NAME;
	      d->character->desc = NULL;
	      free_char( d->character ); /* Big Memory Leak before --Shaddai */
	      d->character = NULL;
	      return;
	    }

            sprintf( buf, "Did I get that right, %s (Y/N)? ", argument );
            write_to_buffer( d, buf, 0 );
            d->connected = CON_CONFIRM_NEW_NAME;
	    return;
	}
	break;

    case CON_DELETE:
    write_to_buffer( d, "\n\r", 2 );

    if ( strcmp( crypt( argument, ch->pcdata->pwd ), ch->pcdata->pwd ) )
    {
        write_to_buffer( d, "Wrong password entered, deletion cancelled.\n\r", 0 );
        write_to_buffer( d, echo_on_str, 0 );
        d->connected = CON_PLAYING;
        return;
    }
    else
    {
        write_to_buffer( d, "\n\rYou've deleted your character!!!\n\r", 0 );
        snprintf( log_buf, MAX_STRING_LENGTH, "Player: %s has deleted.", capitalize( ch->name ) );
        log_string( log_buf );
        do_destroy( ch, ch->name );
        return;
    }
    break;

    case CON_ROLL_STATS:
	switch (argument[0] )
	{
		case 'y': case 'Y':
			write_to_buffer( d, "\n\rWould you like ANSI, or no color/graphic support, (A/N)? ", 0 );
			d->connected = CON_GET_WANT_RIPANSI;
			break;

			case 'n': case 'N':

			name_stamp_stats(ch);		
			snprintf( buf, MAX_STRING_LENGTH, "\n\rStr: %d  Int: %d  Wis: %d  Dex: %d  Con: %d  Cha: %d  Lck: %d\n\rKeep? (Y/N)",
			ch->perm_str, ch->perm_int, ch->perm_wis, ch->perm_dex, ch->perm_con, ch->perm_cha, ch->perm_lck );
			write_to_buffer( d, buf, 0 );
			return;
			default: write_to_buffer( d, "Yes or No? ", 0 );
			return;
	}
    break;

	
    case CON_GET_OLD_PASSWORD:
	write_to_buffer( d, "\n\r", 2 );

	if ( strcmp( crypt( argument, ch->pcdata->pwd ), ch->pcdata->pwd ) )
	{
	    write_to_buffer( d, "Wrong password.\n\r", 0 );
	    /* clear descriptor pointer to get rid of bug message in log */
	    d->character->desc = NULL;
	    close_socket( d, FALSE );
	    return;
	}

	write_to_buffer( d, echo_on_str, 0 );

	if ( check_playing( d, ch->pcdata->filename, TRUE ) )
	    return;

	chk = check_reconnect( d, ch->pcdata->filename, TRUE );
	if ( chk == BERR )
	{
	    if ( d->character && d->character->desc )
	      d->character->desc = NULL;
	    close_socket( d, FALSE );
	    return;
	}
	if ( chk == TRUE )
	  return;

	sprintf( buf, ch->pcdata->filename );
	d->character->desc = NULL;
	free_char( d->character );
	d->character = NULL;
	fOld = load_char_obj( d, buf, FALSE, FALSE );
	ch = d->character;
        if ( ch->position ==  POS_FIGHTING
          || ch->position ==  POS_EVASIVE
          || ch->position ==  POS_DEFENSIVE
          || ch->position ==  POS_AGGRESSIVE
          || ch->position ==  POS_BERSERK )
		ch->position = POS_STANDING;

	sprintf( log_buf, "%s@%s(%s) has connected.", ch->pcdata->filename, 
		d->host, d->user );
    open_lua (ch);  /* fire up Lua state */
    call_lua (ch, "reconnected", ch->name);
	if ( ch->level < LEVEL_DEMI )
	{
	  /*to_channel( log_buf, CHANNEL_MONITOR, "Monitor", ch->level );*/
	  log_string_plus( log_buf, LOG_COMM, sysdata.log_level );
	}
	else
	  log_string_plus( log_buf, LOG_COMM, ch->level );
	if(!IS_IMMORTAL(ch))
    {
        show_title(d);
        break;
    }
    else
    {
        if ( chk_watch(get_trust(ch), ch->name, d->host) ) /*  --Gorog */
            SET_BIT( ch->pcdata->flags, PCFLAG_WATCH );
        else
            REMOVE_BIT( ch->pcdata->flags, PCFLAG_WATCH );

        if ( ch->position == POS_MOUNTED )
            ch->position = POS_STANDING;

        set_pager_color( AT_PLAIN, ch );
        if ( xIS_SET(ch->act, PLR_RIP) )
            send_rip_screen(ch);
        if ( xIS_SET(ch->act, PLR_ANSI) )
            send_to_pager( "\033[2J", ch );
        else
            send_to_pager( "\014", ch );
        d->connected = CON_READ_MOTD;
        goto imm_skip_stuff;
    }

    case CON_CONFIRM_NEW_NAME:
	switch ( *argument )
	{
	case 'y': case 'Y':
	    sprintf( buf, "\n\rMake sure to use a password that won't be easily guessed by someone else."
	    		  "\n\rPick a good password for %s: %s",
		ch->name, echo_off_str );
	    write_to_buffer( d, buf, 0 );
	    d->connected = CON_GET_NEW_PASSWORD;
	    break;

	case 'n': case 'N':
	    write_to_buffer( d, "Ok, what IS it, then? ", 0 );
	    /* clear descriptor pointer to get rid of bug message in log */
	    d->character->desc = NULL;
	    free_char( d->character );
	    d->character = NULL;
	    d->connected = CON_GET_NAME;
	    break;

	default:
	    write_to_buffer( d, "Please type Yes or No. ", 0 );
	    break;
	}
	break;

    case CON_GET_NEW_PASSWORD:
	write_to_buffer( d, "\n\r", 2 );

	if ( strlen(argument) < 5 )
	{
	    write_to_buffer( d,
		"Password must be at least five characters long.\n\rPassword: ",
		0 );
	    return;
	}

	pwdnew = crypt( argument, ch->name );
	for ( p = pwdnew; *p != '\0'; p++ )
	{
	    if ( *p == '~' )
	    {
		write_to_buffer( d,
		    "New password not acceptable, try again.\n\rPassword: ",
		    0 );
		return;
	    }
	}

	DISPOSE( ch->pcdata->pwd );
	ch->pcdata->pwd	= str_dup( pwdnew );
	write_to_buffer( d, "\n\rPlease retype the password to confirm: ", 0 );
	d->connected = CON_CONFIRM_NEW_PASSWORD;
	break;

    case CON_CONFIRM_NEW_PASSWORD:
	write_to_buffer( d, "\n\r", 2 );

	if ( strcmp( crypt( argument, ch->pcdata->pwd ), ch->pcdata->pwd ) )
	{
	    write_to_buffer( d, "Passwords don't match.\n\rRetype password: ",
		0 );
	    d->connected = CON_GET_NEW_PASSWORD;
	    return;
	}

	write_to_buffer( d, echo_on_str, 0 );
	write_to_buffer( d, "\n\rWhat is your sex (M/F/N)? ", 0 );
	d->connected = CON_GET_NEW_SEX;
	break;

    case CON_GET_NEW_SEX:
	switch ( argument[0] )
	{
	case 'm': case 'M': ch->sex = SEX_MALE;    break;
	case 'f': case 'F': ch->sex = SEX_FEMALE;  break;
	case 'n': case 'N': ch->sex = SEX_NEUTRAL; break;
	default:
	    write_to_buffer( d, "That's not a sex.\n\rWhat IS your sex? ", 0 );
	    return;
	}
    open_lua (ch);  /* fire up Lua state */
    call_lua (ch, "new_player", ch->name);
	    write_to_buffer( d, "\n\rYou may choose from the following races, or type help [race] to learn more:\n\r[", 0 );
	buf[0] = '\0';
	for ( iRace = 0; iRace < MAX_PC_RACE; iRace++ )
	{
	  if ( race_table[iRace]->race_name && race_table[iRace]->race_name[0] != '\0'
	  //&& !IS_SET(race_table[iRace]->class_restriction, 1 << ch->class)
          //&& !IS_SET(race_table[iRace]->class_restriction, 1 << ch->dualclass) 
	  && str_cmp(race_table[iRace]->race_name,"unused") )
	  {
            if ( iRace > 0 )
	    {
		if ( strlen(buf)+strlen(race_table[iRace]->race_name) > 77 )
		{
		   strcat( buf, "\n\r" );
		   write_to_buffer( d, buf, 0 );
		   buf[0] = '\0';
		}
		else
		   strcat( buf, " " );
	    }
	    strcat( buf, race_table[iRace]->race_name );
          }
        }
	strcat( buf, "]\n\r: " );
	write_to_buffer( d, buf, 0 );
	d->connected = CON_GET_NEW_RACE;
	break;

    case CON_GET_NEW_RACE:
	argument = one_argument(argument, arg);
        if (!str_cmp( arg, "help") )
        {
          for ( iRace = 0; iRace < MAX_PC_RACE; iRace++ )
	  {
	    if ( toupper(argument[0]) == toupper(race_table[iRace]->race_name[0])
	    &&  !str_prefix( argument, race_table[iRace]->race_name) )
	    {
	      do_luahelp(ch, argument);
      	      write_to_buffer( d, "Please choose a race: ", 0);
	      return;
	    }
	  }
   	  write_to_buffer( d, "No help on that topic.  Please choose a race: ", 0 );
	  return;
	}
	

	for ( iRace = 0; iRace < MAX_PC_RACE; iRace++ )
	{
	    if ( toupper(arg[0]) == toupper(race_table[iRace]->race_name[0])
	    &&   !str_prefix( arg, race_table[iRace]->race_name ) )
	    {
		ch->race = iRace;
		break;
	    }
	}

    if ( iRace == MAX_PC_RACE
    ||  !race_table[iRace]->race_name || race_table[iRace]->race_name[0] == '\0'
    //||   IS_SET(race_table[iRace]->class_restriction, 1 << ch->class )
    //||   IS_SET(race_table[iRace]->class_restriction, 1 << ch->dualclass )
    ||   !str_cmp(race_table[iRace]->race_name,"unused")
       )
	{
	    write_to_buffer( d,
		"That's not a race.\n\rWhat IS your race? ", 0 );
	    return;
	}
	write_to_buffer( d, "\n\rYou will now pick a class.  You will be given the chance to dualclass"
			    "\n\rwhich gives you more power, but it takes longer to level."
			    "\n\rSingle class characters will have the ability to advance to"
			    "\n\ra more powerful class once they have reached Avatar level in"
			    "\n\rtheir current class."
			    "\n\rThe important thing, is the class you choose first will decide"
			    "\n\rwhich statistics are your Primary and Secondary stats."
			    "\n\rIMPORTANT:  Some classes don't work well as dual-classes."
			    "\n\r The main example is monk-shaman (or shaman-monk)."
			    "\n\r Read the help files to be sure you aren't choosing a class"
			    "\n\r that has opposing restrictions!"
                "\n\rSelect a class, or type help [class] to learn more about that class.\n\r> ", 0 );
	buf[0] = '\0';

	/*
	 * Take this out SHADDAI
	 */
	for ( iClass = 0; iClass < MAX_PC_CLASS; iClass++ )
	{
	    if ( class_table[iClass]->who_name &&
	    	 class_table[iClass]->who_name[0] != '\0' )
	    {
	      if ( !IS_SET(race_table[ch->race]->class_restriction, 1 << iClass ) )
		  { 
		  if ( strlen(buf)+strlen(class_table[iClass]->who_name) > 77 )
		  {
		     strcat( buf, "\n\r" );
		     write_to_buffer( d, buf, 0 );
		     buf[0] = '\0';
		  }
		  else
		     strcat( buf, " " );
	      strcat( buf, class_table[iClass]->who_name );
	      }
	    }
	}
	strcat( buf, "]\n\r: " );
	write_to_buffer( d, buf, 0 );
	d->connected = CON_GET_NEW_CLASS; 
	break;

  case CON_GET_NEW_CLASS:
	argument = one_argument(argument, arg);

        if (!str_cmp(arg, "help"))
        {
        
	for ( iClass = 0; iClass < MAX_PC_CLASS; iClass++ )
	{
	  if ( class_table[iClass]->who_name &&
	       class_table[iClass]->who_name[0] != '\0' )
	  {
            if (toupper(argument[0])==toupper(class_table[iClass]->who_name[0])
	    &&   !str_prefix( argument, class_table[iClass]->who_name ) )
	    {
	      do_luahelp(ch, argument);
	      write_to_buffer( d, "Please choose a class: ", 0 );
              return;
	    }
	  }
        }  
	write_to_buffer( d, "No such help topic.  Please choose a class: ", 0 );
	return;
	}

	for ( iClass = 0; iClass < MAX_PC_CLASS; iClass++ )
	{
	  if ( class_table[iClass]->who_name &&
	       class_table[iClass]->who_name[0] != '\0' )
	  {
	    if ( toupper(arg[0]) == toupper(class_table[iClass]->who_name[0])
	    &&   !str_prefix( arg, class_table[iClass]->who_name ) 
		&& !IS_SET(race_table[ch->race]->class_restriction, 1 << iClass ) )
	    {
		ch->class =  iClass;
		break;
	    }
	  }
	}

	if ( iClass == MAX_PC_CLASS
	||  !class_table[iClass]->who_name 
	|| class_table[iClass]->who_name[0] == '\0'
	|| !str_cmp(class_table[iClass]->who_name,"unused"))
	{
	  write_to_buffer( d, "That's not a class.\n\rWhat IS your class? ",0);
	  return;
	}


        if ( check_bans( ch, BAN_CLASS ) )
        {
         write_to_buffer (d,
             "That class is not currently avaiable.\n\rIt's probably new or a tiered class you can gain later.\n\rWhat IS your class? ",0);
         return;
        }

	sprintf( buf, "Would you like to dual class? This gives your character more power, but\n\r takes longer to level. (Y/N) " );
            write_to_buffer( d, buf, 0 );
            d->connected = CON_CONFIRM_DUAL;
	    return;

    case CON_CONFIRM_DUAL:
	switch ( *argument )
	{
	case 'y': case 'Y':
	    write_to_buffer( d, "\n\rSelect a class, or type help [class] to learn more about that class.\n\r[", 0 );
	buf[0] = '\0';

	/*
	 * Take this out SHADDAI
	 */
	for ( iClass = 0; iClass < MAX_PC_CLASS; iClass++ )
	{
	    if ( class_table[iClass]->who_name &&
	    	 class_table[iClass]->who_name[0] != '\0' )
	    {
	      if ( !IS_SET(race_table[ch->race]->class_restriction, 1 << iClass ) )
	      {
		  if ( strlen(buf)+strlen(class_table[iClass]->who_name) > 77 )
		  {
		     strcat( buf, "\n\r" );
		     write_to_buffer( d, buf, 0 );
		     buf[0] = '\0';
		  }
		  else
		     strcat( buf, " " );
	      strcat( buf, class_table[iClass]->who_name );
	      }
	    }
	}
	strcat( buf, "]\n\r: " );
	write_to_buffer( d, buf, 0 );
	d->connected = CON_GET_DUAL_CLASS;
	break;

	case 'n': case 'N':
            ch->dualclass = ch->class;
/* Rerolling of stats added by Samson 2-8-98.  Code courtesy of Kermit's Mud Page */

	write_to_buffer( d, "You may now roll for your character's stats.\n\rYou may roll as often as you like.\n\r",0);

	name_stamp_stats(ch);

	snprintf( buf, MAX_STRING_LENGTH, "\n\rStr: %d  Int: %d  Wis: %d  Dex: %d  Con: %d  Cha: %d  Lck: %d\n\rKeep? (Y/N)",
	ch->perm_str, ch->perm_int, ch->perm_wis, ch->perm_dex, ch->perm_con, ch->perm_cha, ch->perm_lck );
	write_to_buffer( d, buf, 0 );
	
	d->connected = CON_ROLL_STATS;
        break;

	default:
	    write_to_buffer( d, "Please type Yes or No. ", 0 );
	    break;
	}
	break;

    case CON_GET_DUAL_CLASS:
	argument = one_argument(argument, arg);

        if (!str_cmp(arg, "help"))
        {
        
	for ( iClass = 0; iClass < MAX_PC_CLASS; iClass++ )
	{
	  if ( class_table[iClass]->who_name &&
	       class_table[iClass]->who_name[0] != '\0' )
	  {
            if (toupper(argument[0])==toupper(class_table[iClass]->who_name[0])
	    &&   !str_prefix( argument, class_table[iClass]->who_name ) )
	    {
	      do_help(ch, argument);
	      write_to_buffer( d, "Please choose a class: ", 0 );
              return;
	    }
	  }
        }  
	write_to_buffer( d, "No such help topic.  Please choose a class: ", 0 );
	return;
	}

	for ( iClass = 0; iClass < MAX_PC_CLASS; iClass++ )
	{
	  if ( class_table[iClass]->who_name &&
	       class_table[iClass]->who_name[0] != '\0' )
	  {
	    if ( toupper(arg[0]) == toupper(class_table[iClass]->who_name[0])
	    &&   !str_prefix( arg, class_table[iClass]->who_name )
		&& !IS_SET(race_table[ch->race]->class_restriction, 1 << iClass )  )
	    {
		ch->dualclass =  iClass;
		break;
	    }
	  }
	}

	if ( iClass == MAX_PC_CLASS
	||  !class_table[iClass]->who_name 
	|| class_table[iClass]->who_name[0] == '\0'
	|| !str_cmp(class_table[iClass]->who_name,"unused"))
	{
	  write_to_buffer( d, "That's not a class.\n\rWhat IS your class? ",0);
	  return;
	}


        if ( check_bans( ch, BAN_CLASS ) )
        {
         write_to_buffer (d,
             "That class is not currently avaiable.\n\rWhat IS your class? ",0);
         return;
        }

/* Rerolling of stats added by Samson 2-8-98.  Code courtesy of Kermit's Mud Page */

	write_to_buffer( d, "You may now roll for your character's stats.\n\rYou may roll as often as you like.\n\r",0);

	name_stamp_stats(ch);

	snprintf( buf, MAX_STRING_LENGTH, "\n\rStr: %d  Int: %d  Wis: %d  Dex: %d  Con: %d  Cha: %d  Lck: %d\n\rKeep? (Y/N)",
	ch->perm_str, ch->perm_int, ch->perm_wis, ch->perm_dex, ch->perm_con, ch->perm_cha, ch->perm_lck );
	write_to_buffer( d, buf, 0 );
	
	d->connected = CON_ROLL_STATS; // select class
        break;

    case CON_GET_WANT_RIPANSI:
	switch ( argument[0] )
	{
	case 'r': case 'R':
	    xSET_BIT(ch->act,PLR_RIP);
	    xSET_BIT(ch->act,PLR_ANSI);
	    break;
	case 'a': case 'A': xSET_BIT(ch->act,PLR_ANSI);  break;
	case 'n': case 'N': break;
	default:
	    write_to_buffer( d, "Invalid selection.\n\rRIP, ANSI or NONE? ", 0 );
	    return;
	}
	reset_colors(ch);
	sprintf( log_buf, "%s@%s new %s %s%s%s.", ch->name, d->host,
		race_table[ch->race]->race_name,
		class_table[ch->class]->who_name,
        IS_DUAL(ch)?"-":"",
        IS_DUAL(ch)?class_table[ch->dualclass]->who_name:"");
	log_string_plus( log_buf, LOG_COMM, sysdata.log_level);
	to_channel( log_buf, CHANNEL_MONITOR, "Monitor", LEVEL_IMMORTAL );
	write_to_buffer( d, "Press [ENTER] ", 0 );
	show_title(d);
	ch->level = 0;
	ch->position = POS_STANDING;
	d->connected = CON_PRESS_ENTER;
	set_pager_color( AT_PLAIN, ch );
	return;
	break;

    case CON_PRESS_ENTER:
        if ( chk_watch(get_trust(ch), ch->name, d->host) ) /*  --Gorog */
           SET_BIT( ch->pcdata->flags, PCFLAG_WATCH );
        else
           REMOVE_BIT( ch->pcdata->flags, PCFLAG_WATCH );

	if ( ch->position == POS_MOUNTED )
		ch->position = POS_STANDING;

        set_pager_color( AT_PLAIN, ch );
        if ( xIS_SET(ch->act, PLR_RIP) )
          send_rip_screen(ch);
        if ( xIS_SET(ch->act, PLR_ANSI) )
          send_to_pager( "\033[2J", ch );
        else
          send_to_pager( "\014", ch );
        //~ if ( IS_IMMORTAL(ch) )
          //~ do_help( ch, "imotd" );
        if ( ch->level == 50)
          do_help( ch, "amotd" );
        if ( ch->level < 50 && ch->level > 0 )
          do_help( ch, "motd" );
        if ( ch->level == 0 )
          do_help( ch, "nmotd" );
        send_to_pager( "\n\rPress [ENTER] ", ch );
        d->connected = CON_READ_MOTD;
        break;

imm_skip_stuff:
    case CON_READ_MOTD:
	if(!IS_IMMORTAL(ch))
    {
	  char motdbuf[MAX_STRING_LENGTH];

	  sprintf( motdbuf, "\n\rWelcome to %s...\n\r", sysdata.mud_name);
	  write_to_buffer( d, motdbuf, 0 );
	}
    else
    {
        send_to_char("\n\r\n\r&WWelcome home!\n\r\n\r", ch);
    }
	add_char( ch );
	d->connected	= CON_PLAYING;

	if ( ch->level == 0 )
	{
	    OBJ_DATA *obj;
	    int iLang;

	    ch->pcdata->clan	  = NULL;
	    ch->affected_by	  = race_table[ch->race]->affected;
        ch->armor		 += race_table[ch->race]->ac_plus;
        ch->alignment	 += race_table[ch->race]->alignment;
        ch->attacks              = race_table[ch->race]->attacks;
        ch->defenses             = race_table[ch->race]->defenses;
	    ch->saving_damage  	= race_table[ch->race]->saving_damage;
	    ch->saving_wand  		= race_table[ch->race]->saving_wand;
	    ch->saving_para_petri  	= race_table[ch->race]->saving_para_petri;
	    ch->saving_breath  		= race_table[ch->race]->saving_breath;
	    ch->saving_spell_staff	= race_table[ch->race]->saving_spell_staff;

	    ch->height = number_range(race_table[ch->race]->height *.9, race_table[ch->race]->height *1.1);
	    ch->weight = number_range(race_table[ch->race]->weight *.9, race_table[ch->race]->weight *1.1);

	    if ( (iLang = skill_lookup( "common" )) < 0 )
	    	bug( "Nanny: cannot find common language." );
	    else
	    	ch->pcdata->learned[iLang] = 100;
	    	
	    for ( iLang = 0; lang_array[iLang] != LANG_UNKNOWN; iLang++ )
	    	if ( lang_array[iLang] == race_table[ch->race]->language )
	    		break;
	    if ( lang_array[iLang] == LANG_UNKNOWN )
	    	bug( "Nanny: invalid racial language." );
	    else
	    {
	    	if ( (iLang = skill_lookup( lang_names[iLang] )) < 0 )
	    		bug( "Nanny: cannot find racial language." );
	    	else
	    		ch->pcdata->learned[iLang] = 100;
	    }

            /* ch->resist           += race_table[ch->race]->resist;    drats */
            /* ch->susceptible     += race_table[ch->race]->suscept;    drats */

	    // name_stamp_stats( ch );

	    ch->level	= 1;
	    ch->exp	= 0;
            ch->max_hit    += race_table[ch->race]->hit;
            ch->max_mana   += race_table[ch->race]->mana;
	    ch->hit	= UMAX(1,ch->max_hit);
	    ch->mana	= UMAX(1,ch->max_mana);
	    ch->move	= ch->max_move;
	    sprintf( buf, "the %s",
		title_table [ch->class] [ch->level]
		[ch->sex == SEX_FEMALE ? 1 : 0] );
	    set_title( ch, buf );

            /* Added by Narn.  Start new characters with autoexit and autgold
               already turned on.  Very few people don't use those. */
	    xSET_BIT( ch->act, PLR_AUTOGOLD ); 
	    xSET_BIT( ch->act, PLR_AUTOEXIT ); 
	    xSET_BIT( ch->act, PLR_COMPASS );
	    xSET_BIT( ch->act, PLR_AUTOGLANCE );
	    xSET_BIT( ch->act, PLR_NICE );

            /* Added by Brittany, Nov 24/96.  The object is the adventurer's guide
               to the realms of despair, part of Academy.are. */
           {
            OBJ_INDEX_DATA *obj_ind = get_obj_index( 10333 );
            if ( obj_ind != NULL )
            {
              obj = create_object( obj_ind, 0 );
              obj_to_char( obj, ch );
              equip_char( ch, obj, WEAR_HOLD );
            }
           }
           { 
            OBJ_INDEX_DATA *obj_ind = get_obj_index( 10314 ); 
            if ( obj_ind != NULL )
            { 
              obj = create_object( obj_ind, 0 );
              obj_to_char( obj, ch );
            } 
           }
           {
	    OBJ_INDEX_DATA *obj_ind = get_obj_index( 10311 ); 
            if ( obj_ind != NULL )
            { 
              obj = create_object( obj_ind, 0 );
              obj_to_char( obj, ch );
              equip_char( ch, obj, WEAR_LIGHT );
            } 
           }

            if( (ch->class == CLASS_MONK) || (ch->dualclass == CLASS_MONK) )
            {
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10308 ); 
               if ( obj_ind != NULL ) 
               { 
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               } 
            }
            if( (ch->class == CLASS_SHAMAN) || (ch->dualclass == CLASS_SHAMAN) )
            {   
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10336 );
               if ( obj_ind != NULL )   
               { 
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               } 
            } 

            else if ( ch->class == CLASS_MAGE || ch->class == CLASS_DIABOLIST ||
		      ch->class == CLASS_CONJURER )
	    {
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10312 );
               if ( obj_ind != NULL )
               {
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch );
               } 
            } 
            else if ( ch->class == CLASS_CLERIC || ch->class == CLASS_JESTER )
            { 
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10315 );
               if ( obj_ind != NULL ) 
               {
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               }
            } 
            else if ( ch->class == CLASS_THIEF )
            { 
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10312 );
               if ( obj_ind != NULL ) 
               {
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               }
            }
            else if ( ch->class == CLASS_WARRIOR )
            { 
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10313 );
               if ( obj_ind != NULL ) 
               {
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               }
            } 
            else if ( ch->class == CLASS_THUG )
            { 
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10329 );
               if ( obj_ind != NULL ) 
               {
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               }
            } 
            else if ( ch->class == CLASS_DRUID )
            { 
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10313 );
               if ( obj_ind != NULL ) 
               {
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               }
            }
            else if ( ch->class == CLASS_RANGER )
            { 
               OBJ_INDEX_DATA *obj_ind = get_obj_index( 10313 );
               if ( obj_ind != NULL ) 
               { 
                 obj = create_object( obj_ind, 0 );
                 obj_to_char( obj, ch ); 
               } 
            } 
      
	    if (!sysdata.WAIT_FOR_AUTH)
	      char_to_room( ch, get_room_index( ROOM_VNUM_SCHOOL ) );
	    else
	    {
	      char_to_room( ch, get_room_index( ROOM_AUTH_START ) );
	      ch->pcdata->auth_state = 0;
	      SET_BIT(ch->pcdata->flags, PCFLAG_UNAUTHED);
	    }
	    /* Display_prompt interprets blank as default */
	    //~ ch->pcdata->prompt = STRALLOC("");
	}
	else
	if ( !IS_IMMORTAL(ch) && ch->pcdata->release_date > 0 && 
		ch->pcdata->release_date > current_time )
	{
	    if ( ch->in_room->vnum == 6
	    ||   ch->in_room->vnum == 8
	    ||   ch->in_room->vnum == 1206 )
		char_to_room( ch, ch->in_room );
	    else
	      char_to_room( ch, get_room_index(8) );
	}
	else
	if ( ch->in_room && ( IS_IMMORTAL( ch ) 
             || !IS_SET( ch->in_room->room_flags, ROOM_PROTOTYPE ) ) )
	{
	    char_to_room( ch, ch->in_room );
	}
	else
	if ( IS_IMMORTAL(ch) )
	{
	    char_to_room( ch, get_room_index( ROOM_VNUM_CHAT ) );
	}
	else
	{
	    char_to_room( ch, get_room_index( ROOM_VNUM_TEMPLE ) );
	}


    if ( get_timer( ch, TIMER_SHOVEDRAG ) > 0 )
        remove_timer( ch, TIMER_SHOVEDRAG );

    if ( get_timer( ch, TIMER_PKILLED ) > 0 )
	remove_timer( ch, TIMER_PKILLED );

    act( AT_ACTION, "$n has entered the game.", ch, NULL, NULL, TO_CANSEE );
    if (!IS_IMMORTAL(ch))
    {
	sprintf(buf, "[INFO] %s has entered the game.", ch->name );
	echo_to_all( AT_IMMORT, buf, ECHOTAR_ALL);
    }

    if ( ch->pcdata->pet )
    {
           act( AT_ACTION, "$n returns to $s master from the Void.",
                      ch->pcdata->pet, NULL, ch, TO_NOTVICT );
           act( AT_ACTION, "$N returns home with you.",
                        ch, NULL, ch->pcdata->pet, TO_CHAR );
    }
	fix_char(ch);
    do_look( ch, "auto" );
    mail_count(ch);

    if ( !ch->was_in_room && ch->in_room == get_room_index( ROOM_VNUM_TEMPLE ))
      	ch->was_in_room = get_room_index( ROOM_VNUM_TEMPLE );
    else if ( ch->was_in_room == get_room_index( ROOM_VNUM_TEMPLE ))
        ch->was_in_room = get_room_index( ROOM_VNUM_TEMPLE );
    else if ( !ch->was_in_room )
    	ch->was_in_room = ch->in_room;
	call_lua (ch, "entered_game", ch->name);

    break;

    }

    return;
}


bool is_reserved_name( char *name )
{
  RESERVE_DATA *res;
  
  for (res = first_reserved; res; res = res->next)
    if ((*res->name == '*' && !str_infix(res->name+1, name)) ||
        !str_cmp(res->name, name))
      return TRUE;
  return FALSE;
}


/*
 * Parse a name for acceptability.
 */
bool check_parse_name( char *name, bool newchar )
{
 /*
  * Names checking should really only be done on new characters, otherwise
  * we could end up with people who can't access their characters.  Would
  * have also provided for that new area havoc mentioned below, while still
  * disallowing current area mobnames.  I personally think that if we can
  * have more than one mob with the same keyword, then may as well have
  * players too though, so I don't mind that removal.  -- Alty
  */
  
	if ( is_reserved_name(name) && newchar )
		return FALSE;

    /* Length restrictions. */
    if ( strlen(name) <  3 )
		return FALSE;

    if ( strlen(name) > 25 ) // lengthened to 25 - was 12 -Darwin
		return FALSE;

	char *pc;
	int space_found = 0;
	int apostrophe_found = 0;
	
	// Name cannot begin with a space or apostrophe
	if(name[0] == 32 || name[0] == 39)
		return FALSE;

	// Name can only contain one space and one apostrophe.
	// check for them in here.
	for ( pc = name; *pc != '\0'; pc++)
	{
		if( !isalpha(*pc) )
		{
			if( *pc != ' ' && *pc != '\'')
				return FALSE;
		}
		if( *pc == ' ') space_found++;
		if( *pc == '\'') apostrophe_found++;
	}
	if(space_found > 1 || apostrophe_found > 1)
		return FALSE;

    return TRUE;
}



/*
 * Look for link-dead player to reconnect.
 */
bool check_reconnect( DESCRIPTOR_DATA *d, char *name, bool fConn )
{
    CHAR_DATA *ch;

    for ( ch = first_char; ch; ch = ch->next )
    {
	if ( !IS_NPC(ch)
	&& ( !fConn || !ch->desc )
	&&    ch->pcdata->filename
	&&   !str_cmp( name, ch->pcdata->filename ) )
	{
	    if ( fConn && ch->switched )
	    {
	      write_to_buffer( d, "Already playing.\n\rName: ", 0 );
	      d->connected = CON_GET_NAME;
	      if ( d->character )
	      {
		 /* clear descriptor pointer to get rid of bug message in log */
		 d->character->desc = NULL;
		 free_char( d->character );
		 d->character = NULL;
	      }
	      return BERR;
	    }
	    if ( fConn == FALSE )
	    {
		DISPOSE( d->character->pcdata->pwd );
		d->character->pcdata->pwd = str_dup( ch->pcdata->pwd );
	    }
	    else
	    {
		/* clear descriptor pointer to get rid of bug message in log */
		d->character->desc = NULL;
		free_char( d->character );
		d->character = ch;
		ch->desc	 = d;
		ch->timer	 = 0;
		send_to_char( "Reconnecting.\n\r", ch );
		do_look( ch, "auto" );
		act( AT_ACTION, "$n has reconnected.", ch, NULL, NULL, TO_CANSEE );
		sprintf( log_buf, "%s@%s(%s) reconnected.", 
				ch->pcdata->filename, d->host, d->user );
		log_string_plus( log_buf, LOG_COMM, UMAX( sysdata.log_level, ch->level ) );
/*
		if ( ch->level < LEVEL_SAVIOR )
		  to_channel( log_buf, CHANNEL_MONITOR, "Monitor", ch->level );
*/
		d->connected = CON_PLAYING;
	    }
	    return TRUE;
	}
    }

    return FALSE;
}



/*
 * Check if already playing.
 */
bool check_playing( DESCRIPTOR_DATA *d, char *name, bool kick )
{
    CHAR_DATA *ch;

    DESCRIPTOR_DATA *dold;
    int	cstate;

    for ( dold = first_descriptor; dold; dold = dold->next )
    {
	if ( dold != d
	&& (  dold->character || dold->original )
	&&   !str_cmp( name, dold->original
		 ? dold->original->pcdata->filename : 
		 dold->character->pcdata->filename ) )
	{
	    cstate = dold->connected;
	    ch = dold->original ? dold->original : dold->character;
	    if ( !ch->name
	    || ( cstate != CON_PLAYING && cstate != CON_EDITING && cstate != CON_ROLL_STATS && cstate != CON_DELETE ))
	    {
		write_to_buffer( d, "Already connected - try again.\n\r", 0 );
		sprintf( log_buf, "%s already connected.", 
				ch->pcdata->filename );
		log_string_plus( log_buf, LOG_COMM, sysdata.log_level );
		return BERR;
	    }
	    if ( !kick )
	      return TRUE;
	    write_to_buffer( d, "Already playing... Kicking off old connection.\n\r", 0 );
	    write_to_buffer( dold, "Kicking off old connection... bye!\n\r", 0 );
	    close_socket( dold, FALSE );
	    /* clear descriptor pointer to get rid of bug message in log */
	    d->character->desc = NULL;
	    free_char( d->character );
	    d->character = ch;
	    ch->desc	 = d;
	    ch->timer	 = 0;
	    if ( ch->switched )
	      do_return( ch->switched, "" );
	    ch->switched = NULL;
	    send_to_char( "Reconnecting.\n\r", ch );
	    do_look( ch, "auto" );
	    act( AT_ACTION, "$n has reconnected, kicking off old link.",
	         ch, NULL, NULL, TO_CANSEE );
	    sprintf( log_buf, "%s@%s reconnected, kicking off old link.",
	             ch->pcdata->filename, d->host );
	    log_string_plus( log_buf, LOG_COMM, UMAX( sysdata.log_level, ch->level ) );
/*
	    if ( ch->level < LEVEL_SAVIOR )
	      to_channel( log_buf, CHANNEL_MONITOR, "Monitor", ch->level );
*/
	    d->connected = cstate;
	    return TRUE;
	}
    }

    return FALSE;
}



void stop_idling( CHAR_DATA *ch )
{
    ROOM_INDEX_DATA *was_in_room;

    /*
    if ( !ch
    ||   !ch->desc
    ||    ch->desc->connected != CON_PLAYING
    ||   !ch->was_in_room
    ||    ch->in_room != get_room_index( ROOM_VNUM_LIMBO ) )
	return;
	*/

    if ( !ch
    ||   !ch->desc 
    ||   ch->desc->connected != CON_PLAYING
    ||   !IS_IDLE(ch) )
    	return;

    /*
    if ( IS_IMMORTAL(ch) )
    	return;
    */

    ch->timer = 0;
    was_in_room = ch->was_in_room;
    char_from_room( ch );
    char_to_room( ch, was_in_room );
    ch->was_in_room = ch->in_room;
    /*
    ch->was_in_room	= NULL;
    */
    REMOVE_BIT(ch->pcdata->flags, PCFLAG_IDLE );
    act( AT_ACTION, "$n has returned from the void.", ch, NULL, NULL, TO_ROOM );
    return;
}



/*
 * Function to strip off the "a" or "an" or "the" or "some" from an object's
 * short description for the purpose of using it in a sentence sent to
 * the owner of the object.  (Ie: an object with the short description
 * "a long dark blade" would return "long dark blade" for use in a sentence
 * like "Your long dark blade".  The object name isn't always appropriate
 * since it contains keywords that may not look proper.		-Thoric
 */
char *myobj( OBJ_DATA *obj )
{
    if ( !str_prefix("a ", obj->short_descr) )
	return obj->short_descr + 2;
    if ( !str_prefix("an ", obj->short_descr) )
	return obj->short_descr + 3;
    if ( !str_prefix("the ", obj->short_descr) )
	return obj->short_descr + 4;
    if ( !str_prefix("some ", obj->short_descr) )
	return obj->short_descr + 5;
    return obj->short_descr;
}


char *obj_short( OBJ_DATA *obj )
{
    static char buf[MAX_STRING_LENGTH];

    if ( obj->count > 1 )
    {
	sprintf( buf, "%s (%d)", obj->short_descr, obj->count );
	return buf;
    }
    return obj->short_descr;
}

#define MORPHNAME(ch)   ((ch->morph&&ch->morph->morph)? \
                         ch->morph->morph->short_desc: \
                         IS_NPC(ch) ? ch->short_descr : ch->name)
#define NAME(ch)        (IS_NPC(ch) ? ch->short_descr : ch->name)

char *act_string(const char *format, CHAR_DATA *to, CHAR_DATA *ch,
		 const void *arg1, const void *arg2, int flags)
{
  static char * const he_she  [] = { "it",  "he",  "she" };
  static char * const him_her [] = { "it",  "him", "her" };
  static char * const his_her [] = { "its", "his", "her" };
  static char buf[MAX_STRING_LENGTH];
  char fname[MAX_INPUT_LENGTH];
  char temp[MAX_STRING_LENGTH];
  char *point = buf;
  const char *str = format;
  const char *i;
  CHAR_DATA *vch = (CHAR_DATA *) arg2;
  OBJ_DATA *obj1 = (OBJ_DATA  *) arg1;
  OBJ_DATA *obj2 = (OBJ_DATA  *) arg2;

  if ( str[0] == '$' )
  	DONT_UPPER = FALSE;

  while ( *str != '\0' )
  {
    if ( *str != '$' )
    {
      *point++ = *str++;
      continue;
    }
    ++str;
    if ( !arg2 && *str >= 'A' && *str <= 'Z' )
    {
      bug( "Act: missing arg2 for code %c:", *str );
      bug( format );
      i = " <@@@> ";
    }
    else
    {
      switch ( *str )
      {
      default:  bug( "Act: bad code %c.", *str );
		i = " <@@@> ";						break;
      case 't': i = (char *) arg1;					break;
      case 'T': i = (char *) arg2;					break;
      case 'n':
              if ( ch->morph == NULL )
                  i = (to ? PERS ( ch, to ): NAME ( ch ) );
              else if ( !IS_SET( flags, STRING_IMM ) )
                  i = (to ? MORPHPERS (ch, to) : MORPHNAME (ch));
              else
              {
                sprintf(temp, "(MORPH) %s", (to ? PERS(ch,to):NAME(ch))); 
                i = temp;
              }
              break;
      case 'N':
              if ( vch->morph == NULL )
                   i = (to ? PERS ( vch, to ) : NAME( vch ) );
              else if ( !IS_SET( flags, STRING_IMM ) )
                   i = (to ? MORPHPERS (vch, to) : MORPHNAME (vch));
              else
              {
                sprintf(temp, "(MORPH) %s", (to ? PERS(vch,to):NAME(vch)));
                i = temp;
              }
              break;

      case 'e': if (ch->sex > 2 || ch->sex < 0)
		{
		  bug("act_string: player %s has sex set at %d!", ch->name,
		      ch->sex);
		  i = "it";
		}
		else
		  i = he_she [URANGE(0,  ch->sex, 2)];
		break;
      case 'E': if (vch->sex > 2 || vch->sex < 0)
		{
		  bug("act_string: player %s has sex set at %d!", vch->name,
		      vch->sex);
		  i = "it";
		}
		else
		  i = he_she [URANGE(0, vch->sex, 2)];
		break;
      case 'm': if (ch->sex > 2 || ch->sex < 0)
		{
		  bug("act_string: player %s has sex set at %d!", ch->name,
		      ch->sex);
		  i = "it";
		}
		else
		  i = him_her[URANGE(0,  ch->sex, 2)];
		break;
      case 'M': if (vch->sex > 2 || vch->sex < 0)
		{
		  bug("act_string: player %s has sex set at %d!", vch->name,
		      vch->sex);
		  i = "it";
		}
		else
		  i = him_her[URANGE(0, vch->sex, 2)];
		break;
      case 's': if (ch->sex > 2 || ch->sex < 0)
		{
		  bug("act_string: player %s has sex set at %d!", ch->name,
		      ch->sex);
		  i = "its";
		}
		else
		  i = his_her[URANGE(0,  ch->sex, 2)];
		break;
      case 'S': if (vch->sex > 2 || vch->sex < 0)
		{
		  bug("act_string: player %s has sex set at %d!", vch->name,
		      vch->sex);
		  i = "its";
		}
		else
		  i = his_her[URANGE(0, vch->sex, 2)];
		break;
      case 'q': i = (to == ch) ? "" : "s";				break;
      case 'Q': i = (to == ch) ? "your" :
		    his_her[URANGE(0,  ch->sex, 2)];			break;
      case 'p': i = (!to || can_see_obj(to, obj1)
		  ? obj_short(obj1) : "something");			break;
      case 'P': i = (!to || can_see_obj(to, obj2)
		  ? obj_short(obj2) : "something");			break;
      case 'd':
        if ( !arg2 || ((char *) arg2)[0] == '\0' )
          i = "door";
        else
        {
          one_argument((char *) arg2, fname);
          i = fname;
        }
        break;
      }
    }
    ++str;
    while ( (*point = *i) != '\0' )
      ++point, ++i;
  }
  strcpy(point, "\n\r");
  if ( !DONT_UPPER )
     buf[0] = UPPER(buf[0]);
  return buf;
}
#undef NAME
  
void act( sh_int AType, const char *format, CHAR_DATA *ch, const void *arg1, const void *arg2, int type )
{
    char *txt;
    CHAR_DATA *to;
    CHAR_DATA *vch = (CHAR_DATA *)arg2;

    /*
     * Discard null and zero-length messages.
     */
    if ( !format || format[0] == '\0' )
	return;

    if ( !ch )
    {
	bug( "Act: null ch. (%s)", format );
	return;
    }

    if ( !ch->in_room )
      to = NULL;
    else if ( type == TO_CHAR )
      to = ch;
    else
      to = ch->in_room->first_person;

    /*
     * ACT_SECRETIVE handling
     */
    if ( IS_NPC(ch) && xIS_SET(ch->act, ACT_SECRETIVE) && type != TO_CHAR )
	return;

    if ( type == TO_VICT )
    {
	if ( !vch )
	{
	    bug( "Act: null vch with TO_VICT." );
	    bug( "%s (%s)", ch->name, format );
	    return;
	}
	if ( !vch->in_room )
	{
	    bug( "Act: vch in NULL room!" );
	    bug( "%s -> %s (%s)", ch->name, vch->name, format );
	    return;
	}
	to = vch;
/*	to = vch->in_room->first_person;*/
    }

    if ( MOBtrigger && type != TO_CHAR && type != TO_VICT && to )
    {
      OBJ_DATA *to_obj;
      
      txt = act_string(format, NULL, ch, arg1, arg2, STRING_IMM);
      if ( HAS_PROG(to->in_room, ACT_PROG) )
        rprog_act_trigger(txt, to->in_room, ch, (OBJ_DATA *)arg1, (void *)arg2);
      for ( to_obj = to->in_room->first_content; to_obj;
            to_obj = to_obj->next_content )
        if ( HAS_PROG(to_obj->pIndexData, ACT_PROG) )
          oprog_act_trigger(txt, to_obj, ch, (OBJ_DATA *)arg1, (void *)arg2);
    }

    /* Anyone feel like telling me the point of looping through the whole
       room when we're only sending to one char anyways..? -- Alty */
    for ( ; to; to = (type == TO_CHAR || type == TO_VICT)
                     ? NULL : to->next_in_room )
    {
	if ((!to->desc 
	&& (  IS_NPC(to) && !HAS_PROG(to->pIndexData, ACT_PROG) ))
	||   !IS_AWAKE(to) )
	    continue;

	if ( type == TO_CHAR && to != ch )
	    continue;
	if ( type == TO_VICT && ( to != vch || to == ch ) )
	    continue;
	if ( type == TO_ROOM && to == ch )
	    continue;
	if ( type == TO_NOTVICT && (to == ch || to == vch) )
	    continue;
    if ( type == TO_CANSEE && ( to == ch || !can_see(to, ch) ) )
        continue;

        if ( IS_IMMORTAL(to) )
            txt = act_string (format, to, ch, arg1, arg2, STRING_IMM);
        else
       	    txt = act_string (format, to, ch, arg1, arg2, STRING_NONE);

/*
	if (to->desc)
	{
	  if ( AType == AT_COLORIZE )
	  {
	     if ( txt[0] == '&' )
	     	send_to_char_color( txt, to );
	     else
	     {
	        set_char_color(AT_MAGIC, to );
		send_to_char_color( txt, to );
	     }
	  }
	  else {
	     set_char_color(AType, to);
	     send_to_char_color( txt, to );
	  }
	}
*/
        if (to->desc)
	{
        set_char_color(AType, to);
        send_to_char( txt, to );
	}

	if (MOBtrigger)
        {
          /* Note: use original string, not string with ANSI. -- Alty */
	  mprog_act_trigger( txt, to, ch, (OBJ_DATA *)arg1, (void *)arg2 );
        }
    }
    MOBtrigger = TRUE;
    return;
}

void do_name( CHAR_DATA *ch, char *argument )
{
  char fname[1024];
  struct stat fst;
  CHAR_DATA *tmp;

  if ( !NOT_AUTHED(ch) || ch->pcdata->auth_state != 2)
  {
    send_to_char("Huh?\n\r", ch);
    return;
  }

  argument[0] = UPPER(argument[0]);

  if (!check_parse_name(argument, TRUE))
  {
    send_to_char("Illegal name, try another.\n\r", ch);
    return;
  }

  if (!str_cmp(ch->name, argument))
  {
    send_to_char("That's already your name!\n\r", ch);
    return;
  }

  for ( tmp = first_char; tmp; tmp = tmp->next )
  {
    if (!str_cmp(argument, tmp->name))
    break;
  }

  if ( tmp )
  {
    send_to_char("That name is already taken.  Please choose another.\n\r", ch);
    return;
  }

  sprintf( fname, "%s%c/%s", PLAYER_DIR, tolower(argument[0]),
                        capitalize( argument ) );
  if ( stat( fname, &fst ) != -1 )
  {
    send_to_char("That name is already taken.  Please choose another.\n\r", ch);
    return;
  }

  STRFREE( ch->name );
  ch->name = STRALLOC( argument );
  STRFREE( ch->pcdata->filename );
  ch->pcdata->filename = STRALLOC( argument ); 
  send_to_char("Your name has been changed.  Please apply again.\n\r", ch);
  ch->pcdata->auth_state = 0;
  return;
}
  
char *default_fprompt( CHAR_DATA *ch )
{
  static char buf[60];

  strcpy(buf, "&w<&R%h&W/&r%H&Whp ");
    strcat(buf, "&P%m&W/&p%M&Wma");
  strcat(buf, " &C%v&W/&c%V&Wmv&W  Style: &R%S&w> ");
  if ( IS_NPC(ch) || IS_IMMORTAL(ch) )
    strcat(buf, "%i%R");
  strcat(buf, "%L");
  return buf;
}

char *default_prompt( CHAR_DATA *ch )
{
  static char buf[60];

  strcpy(buf, "&w<&R%h&Whp ");
    strcat(buf, "&P%m&Wma ");
  strcat(buf, "&C%v&Wmv  &Y%g&Wgp &G%X&Wtnl&w> ");
  if ( IS_NPC(ch) || IS_IMMORTAL(ch) )
    strcat(buf, "%i%R");
  strcat(buf, "%L");
  return buf;
}

int getcolor(char clr)
{
  static const char colors[16] = "xrgObpcwzRGYBPCW";
  int r;
  
  for ( r = 0; r < 16; r++ )
    if ( clr == colors[r] )
      return r;
  return -1;
}

void display_prompt( DESCRIPTOR_DATA *d )
{
  CHAR_DATA *ch = d->character;
  CHAR_DATA *och = (d->original ? d->original : d->character);
  CHAR_DATA *victim;
	EXIT_DATA *pexit;
	bool found = FALSE;
  bool ansi = (!IS_NPC(och) && xIS_SET(och->act, PLR_ANSI));
  const char *prompt;
  const char *helpstart = "<Type HELP START>";
  char buf[MAX_STRING_LENGTH];
  char *pbuf = buf;
  int stat, percent;
  //~ char timebuf[MAX_STRING_LENGTH];

  if ( !ch )
  {
    bug( "display_prompt: NULL ch" );
    return;
  }

  if ( !IS_NPC(ch) && !IS_SET(ch->pcdata->flags, PCFLAG_HELPSTART ) )
	prompt = helpstart;
  else if ( !IS_NPC(ch) && ch->substate != SUB_NONE && ch->pcdata->subprompt
  &&   ch->pcdata->subprompt[0] != '\0' )
    prompt = ch->pcdata->subprompt;
  else if (IS_NPC (ch) || (!ch->fighting && (!ch->pcdata->prompt
                || !*ch->pcdata->prompt) ) )
    prompt = default_prompt (ch);
  else if ( ch->fighting )
  {
        if ( !ch->pcdata->fprompt || !*ch->pcdata->fprompt )
                prompt = default_fprompt ( ch );
        else
                prompt = ch->pcdata->fprompt;
  }
  else
    prompt = ch->pcdata->prompt;

  if ( ansi )
  {
    strcpy( pbuf, ANSI_RESET );
    d->prevcolor = 0x08;
    pbuf += 4;
  }

/*
  if ( ansi )
  {
    strcpy(pbuf, "\033[m");
    d->prevcolor = 0x07;
    pbuf += 3;
  }
*/

  /* Clear out old color stuff */
/*  make_color_sequence(NULL, NULL, NULL);*/

  for ( ; *prompt; prompt++ )
  {
/*
     // '&' = foreground color/intensity bit
     // '^' = background color/blink bit
     // '%' = prompt commands
     // Note: foreground changes will revert background to 0 (black)
 
    if ( *prompt != '&' && *prompt != '^' && *prompt != '%' )
    {
      *(pbuf++) = *prompt;
      continue;
    }
*/
    /*
     * '%' = prompt commands
     * Note: foreground changes will revert background to 0 (black)
     */
    if( *prompt != '%' )
    {
      *(pbuf++) = *prompt;
      continue;
    }

    ++prompt;
    if ( !*prompt )
      break;
    if ( *prompt == *(prompt-1) )
    {
      *(pbuf++) = *prompt;
      continue;
    }
    switch(*(prompt-1))
    {
    default:
      bug( "Display_prompt: bad command char '%c'.", *(prompt-1) );
      break;
/*
    case '&':
    case '^':
      stat = make_color_sequence(&prompt[-1], pbuf, d);
      if ( stat < 0 )
        --prompt;
      else if ( stat > 0 )
        pbuf += stat;
      break;
*/
    case '%':
      *pbuf = '\0';
      stat = 0x80000000;
      switch(*prompt)
      {
      case '%':
	*pbuf++ = '%';
	*pbuf = '\0';
	break;
      case 'a':
	if ( IS_GOOD(ch) )
	  strcpy(pbuf, "good");
	else if ( IS_EVIL(ch) )
	  strcpy(pbuf, "evil");
	else
	  strcpy(pbuf, "neutral");
	break;
      case 'A':
	sprintf( pbuf, "%s%s%s%s%s", IS_AFFECTED( ch, AFF_INVISIBLE ) ? "I" : "",
				 IS_AFFECTED( ch, AFF_IMP_INVIS ) ? "I" : "",
				 IS_AFFECTED( ch, AFF_HIDE )      ? "H" : "",
				 IS_AFFECTED( ch, AFF_CAMO )	  ? "C" : "",
				 IS_AFFECTED( ch, AFF_SNEAK )     ? "S" : "" );
        break;
	  case 'b': // room name
		  strcpy(pbuf, ch->in_room->name);
		  break;
	  case 'B': // room exits
			for ( pexit = ch->in_room->first_exit; pexit; pexit = pexit->next )
			{
				if ( pexit->to_room
				&&  !IS_SET(pexit->exit_info, EX_CLOSED)
				&& (!IS_SET(pexit->exit_info, EX_WINDOW)
				||   IS_SET(pexit->exit_info, EX_ISDOOR))
				&&  !IS_SET(pexit->exit_info, EX_HIDDEN) )
				{
					found = TRUE;
					strcat( pbuf, dir_name[pexit->vdir] );
					if(pexit->next)
						strcat(pbuf, " ");
				}
			}
			if ( !found )
				strcat( pbuf, "none" );
		  break;
        case 'C':  /* Tank */
	  //if ( !IS_IMMORTAL( ch ) ) break;
          if ( !ch->fighting || ( victim = ch->fighting->who ) == NULL )
             strcpy( pbuf, "none" );
          else if(!victim->fighting||(victim = victim->fighting->who)==NULL)
             strcpy( pbuf, "none" );
          else {
              if ( victim->max_hit > 0 )
                    percent = (100 * victim->hit) / victim->max_hit;
              else
                    percent = -1;
                   if (percent >= 100)
                       strcpy (pbuf, "perfect health");
                   else if (percent >= 90)
                       strcpy (pbuf, "slightly scratched");
                   else if (percent >= 80)
                       strcpy (pbuf, "few bruises");
                    else if (percent >= 70)
                       strcpy (pbuf, "some cuts");
                    else if (percent >= 60)
                       strcpy (pbuf, "several wounds");
                    else if (percent >= 50)
                       strcpy (pbuf, "nasty wounds");
                    else if (percent >= 40)
                       strcpy (pbuf, "bleeding freely");
                    else if (percent >= 30)
                       strcpy (pbuf, "covered in blood");
                    else if (percent >= 20)
                       strcpy (pbuf, "leaking guts");
                    else if (percent >= 10)
                       strcpy (pbuf, "almost dead");
                    else
                       strcpy (pbuf, "DYING");
             }
          break;
        case 'c':
	  //if ( !IS_IMMORTAL( ch ) ) break;
          if ( !ch->fighting || ( victim = ch->fighting->who ) == NULL )
             strcpy( pbuf, "none" );
          else {
              if ( victim->max_hit > 0 )
                    percent = (100 * victim->hit) / victim->max_hit;
              else
                    percent = -1;
                if (percent >= 100)
                       strcpy (pbuf, "perfect health");
                    else if (percent >= 90)
                       strcpy (pbuf, "slightly scratched");
                    else if (percent >= 80)
                       strcpy (pbuf, "few bruises");
                    else if (percent >= 70)
                       strcpy (pbuf, "some cuts");
                    else if (percent >= 60)
                       strcpy (pbuf, "several wounds");
                    else if (percent >= 50)
                       strcpy (pbuf, "nasty wounds");
                    else if (percent >= 40)
                       strcpy (pbuf, "bleeding freely");
                    else if (percent >= 30)
                       strcpy (pbuf, "covered in blood");
                    else if (percent >= 20)
                       strcpy (pbuf, "leaking guts");
                    else if (percent >= 10)
                       strcpy (pbuf, "almost dead");
                    else
                       strcpy (pbuf, "DYING");
           }
          break;
      case 'h':
	stat = ch->hit;
	break;
      case 'H':
	stat = ch->max_hit;
	break;
      case 'm':
	  stat = ch->mana;
	break;
      case 'M':
	  stat = ch->max_mana;
	break;
        case 'N': /* Tank */
	  //if ( !IS_IMMORTAL(ch) ) break;
          if ( !ch->fighting || ( victim = ch->fighting->who ) == NULL )
            strcpy( pbuf, "none" );
          else if(!victim->fighting||(victim=victim->fighting->who)==NULL)
            strcpy( pbuf, "none" );
          else {
            if ( ch == victim )
                    strcpy ( pbuf, "You" );
            else if ( IS_NPC(victim) )
                    strcpy ( pbuf, victim->short_descr );
            else
                    strcpy ( pbuf, victim->name );
                pbuf[0] = UPPER( pbuf[0] );
          }
          break;
        case 'n':
	  //if ( !IS_IMMORTAL(ch) ) break;
          if (!ch->fighting || (victim = ch->fighting->who) == NULL )
            strcpy( pbuf, "none" );
          else {
            if ( ch == victim )
                    strcpy ( pbuf, "You" );
            else if ( IS_NPC(victim) )
                    strcpy ( pbuf, victim->short_descr );
            else
                    strcpy ( pbuf, victim->name );
            pbuf[0] = UPPER( pbuf[0] );
          }
          break;
      case 'T':
        if      ( time_info.hour <  5 ) strcpy( pbuf, "night" );
        else if ( time_info.hour <  6 ) strcpy( pbuf, "dawn" );
        else if ( time_info.hour < 19 ) strcpy( pbuf, "day" );
        else if ( time_info.hour < 21 ) strcpy( pbuf, "dusk" );
        else                            strcpy( pbuf, "night" );
        break;
      case 't':
		  stat = time_info.hour;
		  //~ sprintf( timebuf, "%24.24s", (char *)ctime(&current_time));
		  //~ strcpy( pbuf, timebuf);
		  break;
      case 'u':
		  if ( !IS_IMMORTAL(ch) ) break;
	stat = num_descriptors;
	break;
      case 'U':
		  if ( !IS_IMMORTAL(ch) ) break;
	stat = sysdata.maxplayers;
	break;
      case 'v':
	stat = ch->move;
	break;
      case 'V':
	stat = ch->max_move;
	break;
      case 'g':
	stat = ch->gold;
	break;
	  case 'G':
		stat = ch->pcdata->balance;
		break;
      case 'r':
	if ( IS_IMMORTAL(och) )
	  stat = ch->in_room->vnum;
	break;
      case 'F':
	if ( IS_IMMORTAL( och ) )
	  sprintf( pbuf, "%s", flag_string( ch->in_room->room_flags, r_flags) );
	break;
      case 'R':
	if ( xIS_SET(och->act, PLR_ROOMVNUM) )
	  sprintf(pbuf, "<#%d> ", ch->in_room->vnum);
	break;
      case 'x':
	stat = ch->exp;
	break;
      case 'X':
	stat = exp_level(ch, ch->level+1) - ch->exp;
	break;
      case 'o':         /* display name of object on auction */
        if ( auction->item )
           strcpy( pbuf, auction->item->name );
        break;
      case 'S':
        if      ( ch->style == STYLE_BERSERK )    strcpy( pbuf, "B" );
        else if ( ch->style == STYLE_AGGRESSIVE ) strcpy( pbuf, "A" );
        else if ( ch->style == STYLE_DEFENSIVE )  strcpy( pbuf, "D" );
        else if ( ch->style == STYLE_EVASIVE )    strcpy( pbuf, "E" );
        else                                      strcpy( pbuf, "S" );
	break;
	  case 'p':
		switch (ch->position)
		{
			case POS_DEAD:
				sprintf(pbuf, "slowly decomposing"); 	break;
			case POS_MORTAL:
				sprintf(pbuf, "mortally wounded");		break;
			case POS_INCAP:
				sprintf(pbuf, "incapacitated");			break;
			case POS_STUNNED:
				sprintf(pbuf, "stunned");				break;
			case POS_SLEEPING:
				sprintf(pbuf, "sleeping");				break;
			case POS_RESTING:
				sprintf(pbuf, "resting");				break;
			case POS_STANDING:
				sprintf(pbuf, "standing");				break;
			case POS_FIGHTING:
				sprintf(pbuf, "fighting");				break;
			case POS_EVASIVE:
				sprintf(pbuf, "fighting (evasive)");   	break;
			case POS_DEFENSIVE:
				sprintf(pbuf, "fighting (defensive)");	break;
			case POS_AGGRESSIVE:
				sprintf(pbuf, "fighting (aggressive)");	break;
			case POS_BERSERK:
				sprintf(pbuf, "fighting (berserk)");	break;
			case POS_MOUNTED:
				sprintf(pbuf, "mounted");				break;
			case POS_SITTING:
				sprintf(pbuf, "sitting");				break;
		}
		break;
      case 'i':
	if ( (!IS_NPC(ch) && xIS_SET(ch->act, PLR_WIZINVIS)) ||
	      (IS_NPC(ch) && xIS_SET(ch->act, ACT_MOBINVIS)) )
	  sprintf(pbuf, "(Invis %d) ", (IS_NPC(ch) ? ch->mobinvis : ch->pcdata->wizinvis));
	else
	if ( IS_AFFECTED(ch, AFF_INVISIBLE) || IS_AFFECTED(ch, AFF_IMP_INVIS) )
	  sprintf(pbuf, "(Invis) " );
	break;
      case 'I':
	stat = (IS_NPC(ch) ? (xIS_SET(ch->act, ACT_MOBINVIS) ? ch->mobinvis : 0)
	     : (xIS_SET(ch->act, PLR_WIZINVIS) ? ch->pcdata->wizinvis : 0));
	break;
	  case 'w': /* waiting = red x, no wait = green o -Darwin */
		  if(ch->wait)
			  strcpy( pbuf, "&Rx");
		  else
			  strcpy( pbuf, "&Go");
	break;
	  case 'L':
		  strcpy( pbuf, "\n\r");
		  break;
      }
      if ( stat != 0x80000000 )
	sprintf(pbuf, "%d", stat);
      pbuf += strlen(pbuf);
      break;
    }
  }
/*
  *pbuf = '\0';
  write_to_buffer(d, buf, (pbuf-buf));
  return;
*/
  *pbuf = '\0';
  send_to_char( buf, ch );
  return;
}

/*
int make_color_sequence(const char *col, char *buf, DESCRIPTOR_DATA *d)
{
  int ln;
  const char *ctype = col;
  unsigned char cl;
  CHAR_DATA *och;
  bool ansi;
  
  och = (d->original ? d->original : d->character);
  ansi = (!IS_NPC(och) && xIS_SET(och->act, PLR_ANSI));
  col++;
  if ( !*col )
    ln = -1;
  else if ( *ctype != '&' && *ctype != '^' )
  {
    bug("Make_color_sequence: command '%c' not '&' or '^'.", *ctype);
    ln = -1;
  }
  else if ( *col == *ctype )
  {
    buf[0] = *col;
    buf[1] = '\0';
    ln = 1;
  }
  else if ( !ansi )
    ln = 0;
  else
  {
    cl = d->prevcolor;
    switch(*ctype)
    {
    default:
      bug( "Make_color_sequence: bad command char '%c'.", *ctype );
      ln = -1;
      break;
    case '&':
      if ( *col == '-' )
      {
        buf[0] = '~';
        buf[1] = '\0';
        ln = 1;
        break;
      }
    case '^':
      {
        int newcol;
        
        if ( (newcol = getcolor(*col)) < 0 )
        {
          ln = 0;
          break;
        }
        else if ( *ctype == '&' )
          cl = (cl & 0xF0) | newcol;
        else
          cl = (cl & 0x0F) | (newcol << 4);
      }
      if ( cl == d->prevcolor )
      {
        ln = 0;
        break;
      }
      strcpy(buf, "\033[");
      if ( (cl & 0x88) != (d->prevcolor & 0x88) )
      {
        strcat(buf, "m\033[");
        if ( (cl & 0x08) )
          strcat(buf, "1;");
        if ( (cl & 0x80) )
          strcat(buf, "5;");
        d->prevcolor = 0x07 | (cl & 0x88);
        ln = strlen(buf);
      }
      else
        ln = 2;
      if ( (cl & 0x07) != (d->prevcolor & 0x07) )
      {
        sprintf(buf+ln, "3%d;", cl & 0x07);
        ln += 3;
      }
      if ( (cl & 0x70) != (d->prevcolor & 0x70) )
      {
        sprintf(buf+ln, "4%d;", (cl & 0x70) >> 4);
        ln += 3;
      }
      if ( buf[ln-1] == ';' )
        buf[ln-1] = 'm';
      else
      {
        buf[ln++] = 'm';
        buf[ln] = '\0';
      }
      d->prevcolor = cl;
    }
  }
  if ( ln <= 0 )
    *buf = '\0';
  return ln;
}
*/

void set_pager_input( DESCRIPTOR_DATA *d, char *argument )
{
  while ( isspace(*argument) )
    argument++;
  d->pagecmd = *argument;
  return;
}

bool pager_output( DESCRIPTOR_DATA *d )
{
  register char *last;
  CHAR_DATA *ch;
  int pclines;
  register int lines;
  bool ret;

  if ( !d || !d->pagepoint || d->pagecmd == -1 )
    return TRUE;
  ch = d->original ? d->original : d->character;
  pclines = UMAX(ch->pcdata->pagerlen, 5) - 1;
  switch(LOWER(d->pagecmd))
  {
  default:
    lines = 0;
    break;
  case 'b':
    lines = -1-(pclines*2);
    break;
  case 'r':
    lines = -1-pclines;
    break;
  case 'n':
    lines = 0;
    pclines = 0x7FFFFFFF;	/* As many lines as possible */
    break;
  case 'q':
    d->pagetop = 0;
    d->pagepoint = NULL;
    flush_buffer(d, TRUE);
    DISPOSE(d->pagebuf);
    d->pagesize = MAX_STRING_LENGTH;
    return TRUE;
  }
  while ( lines < 0 && d->pagepoint >= d->pagebuf )
    if ( *(--d->pagepoint) == '\n' )
      ++lines;
  if ( *d->pagepoint == '\n' && *(++d->pagepoint) == '\r' )
      ++d->pagepoint;
  if ( d->pagepoint < d->pagebuf )
    d->pagepoint = d->pagebuf;
  for ( lines = 0, last = d->pagepoint; lines < pclines; ++last )
    if ( !*last )
      break;
    else if ( *last == '\n' )
      ++lines;
  if ( *last == '\r' )
    ++last;
  if ( last != d->pagepoint )
  {
    if ( !write_to_descriptor(d->descriptor, d->pagepoint,
          (last-d->pagepoint)) )
      return FALSE;
    d->pagepoint = last;
  }
  while ( isspace(*last) )
    ++last;
  if ( !*last )
  {
    d->pagetop = 0;
    d->pagepoint = NULL;
    flush_buffer(d, TRUE);
    DISPOSE(d->pagebuf);
    d->pagesize = MAX_STRING_LENGTH;
    return TRUE;
  }
  d->pagecmd = -1;
/*
  if ( xIS_SET( ch->act, PLR_ANSI ) )
      if ( write_to_descriptor(d->descriptor, "\033[1;36m", 7) == FALSE )
	return FALSE;
*/
  if( xIS_SET( ch->act, PLR_ANSI ) )
      if( write_to_descriptor( d->descriptor, ANSI_LBLUE, 0 ) == FALSE )
	   return FALSE;
  if ( (ret=write_to_descriptor(d->descriptor,
	"(C)ontinue, (N)on-stop, (R)efresh, (B)ack, (Q)uit: [C] ", 0)) == FALSE )
	return FALSE;
  if ( xIS_SET( ch->act, PLR_ANSI ) )
  {
      char buf[32];
/*
      if ( d->pagecolor == 7 )
	strcpy( buf, "\033[m" );
      else
	sprintf(buf, "\033[0;%d;%s%dm", (d->pagecolor & 8) == 8,
		(d->pagecolor > 15 ? "5;" : ""), (d->pagecolor & 7)+30);
*/
      snprintf( buf, 32, "%s", color_str( d->pagecolor, ch ) );
      ret = write_to_descriptor( d->descriptor, buf, 0 );
  }
  return ret;
}


#ifdef WIN32

void bailout(void)
{
    echo_to_all( AT_IMMORT, "MUD shutting down by system operator NOW!!", ECHOTAR_ALL );
    shutdown_mud( "MUD shutdown by system operator" );
    log_string ("MUD shutdown by system operator");
    Sleep (5000);		/* give "echo_to_all" time to display */
    mud_down = TRUE;		/* This will cause game_loop to exit */
    service_shut_down = TRUE;	/* This will cause characters to be saved */
    fflush(stderr);
    return;
}

#endif
