/*
 *  Anti-tanking code
 *  Author: Cronel (supfly@geocities.com) based on idea by Krage
 *  of FrozenMUD (empire.digiunix.net 4000)
 *
 *  Permission to use and distribute this code is granted provided
 *  this header is retained and unaltered, and the distribution
 *  package contains all the original files unmodified.
 *  If you modify this code and use/distribute modified versions
 *  you must give credit to the original author(s).
 */

#include <stdio.h>
#include "mud.h"

/* This is called from violence_update, for mobs fighting PCs only;
 * ch is the mob, victim is the player. Returns TRUE if "victim"
 * has changed, FALSE otherwise.
 * The code simply checks if there's someone else fighting this
 * mob in the room, and if this person is under ten levels from the
 * one the mob is currently fighting, then powerlevel-tanking has
 * been detected. Switch and kill the lowbie! Ha Ha Ha!
 */
bool check_anti_tanking( CHAR_DATA *ch, CHAR_DATA *victim )
{

	CHAR_DATA *lowbie;
	CHAR_DATA *tanker;
    char *buf;

	for( lowbie = ch->in_room->first_person ; lowbie ; lowbie = lowbie->next_in_room )
	{
		if( lowbie == ch
		|| lowbie == victim 
		|| IS_NPC(lowbie) )
			continue;
		if( who_fighting(lowbie) == ch 
		&& CH_LEVEL(lowbie) < CH_LEVEL(victim) - 10 /* && !IS_TIER(lowbie) */)
		{
			act( AT_CARNAGE, "$n sees that $N has joined the fight, and decides $E is a much better prey!",
				ch, NULL, lowbie, TO_ROOM );
			do_yell( ch, "Younger meat, ha ha!" );
			tanker = who_fighting( ch );
			stop_fighting( ch, FALSE );
			set_fighting( ch, lowbie );
			ch->damroll += 100;
            call_va(L_mud, "sprintf", "sssi>s", "check_anti_tanking: Tanking detected. %s is tanking for %s, with mob %d",
                tanker->name, lowbie->name, ch->pIndexData->vnum, &buf);
			log_string( buf );
			return TRUE;
		}

	}
	return FALSE;
}
