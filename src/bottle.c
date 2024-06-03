/*
 *  Bottle spell, unbottle command
 *  Author: Rantic (supfly@geocities.com)
 *  of FrozenMUD (empire.digiunix.net 4000)
 *
 *  Permission to use and distribute this code is granted provided
 *  this header is retained and unaltered, and the distribution
 *  package contains all the original files unmodified.
 *  If you modify this code and use/distribute modified versions
 *  you must give credit to the original author(s).
 * 
 *  Bottle a mob! Not really playable, but interesting
 */

#include <stdio.h>
#include "mud.h"

/* from magic.c */
char *target_name;
void failed_casting( SKILLTYPE *skill, CHAR_DATA *ch, CHAR_DATA *victim, OBJ_DATA *obj );


ch_ret spell_bottle( int sn, int level, CHAR_DATA *ch, void *vo )
{
	CHAR_DATA *victim;
	SKILLTYPE *skill = get_skilltype(sn);
	char buf[MAX_STRING_LENGTH];
	OBJ_DATA *bottle;
	int percent;

	if (target_name[0] == '\0')
	{
		send_to_char( "Bottle whom?\n\r", ch );
		return rNONE;
	}
	
	else if ( ( victim = get_char_room( ch, target_name ) ) != NULL )
	{
	
		if ( victim == ch )
		{
			send_to_char( "Why would you want to bottle yourself?\n\r", ch );
			return rNONE;
		}
	
		
		if (!IS_NPC( victim ))
		{
			set_char_color( AT_BLUE, ch );
			send_to_char( "You can't bottle other players!\n\r", ch );
			return rNONE;
		}
		
		if ( victim->level >= level + 5 )
		{
			failed_casting( skill, ch, victim, NULL );
			return rSPELL_FAILED;
		}
		
		if ( IS_SET( ch->in_room->room_flags, ROOM_SAFE ) )
		{
			set_char_color( AT_MAGIC, ch );
			send_to_char( "Magical forces prevent your bottling.\n\r", ch );
			return rNONE;
		}

		if ( xIS_SET( victim->act, ACT_AGGRESSIVE ) )
		{
			act( AT_MAGIC, "$N is too aggressive to bottle fast enough!", ch, NULL, victim, TO_CHAR );
			multi_hit( ch, victim, TYPE_UNDEFINED );
			return rSPELL_FAILED;
		}
	
		if ( victim->fighting )
		{
			send_to_char( "You can't bottle someone who is in combat.\n\r", ch );
			return rNONE;
		}
	
		percent = number_percent( ) - (get_curr_lck(ch) - 14) + (get_curr_lck(victim) -13);
		if ( percent < ch->pcdata->learned[sn] )
		{ 
			bottle = create_object( get_obj_index( OBJ_VNUM_BOTTLE ), 0 );
			bottle->value[0] = victim->pIndexData->vnum;
			bottle->value[1] = victim->pIndexData->level;
			bottle->value[2] = victim->pIndexData->hitsizedice;
			bottle->value[3] = victim->pIndexData->hitplus;
			bottle->value[4] = victim->max_hit;
			bottle->value[5] = ch->in_room->vnum;
			bottle->owner = ch->name;
			
			sprintf(buf, "translucent bottle %s", victim->name );
			STRFREE(bottle->name);
			bottle->name = STRALLOC(buf);
			
			sprintf(buf, "a bottle filled with '%s'", victim->pIndexData->short_descr );
			STRFREE(bottle->short_descr);
			bottle->short_descr = STRALLOC(buf);
			
			sprintf(buf, "A bottle filled with '%s' bounces around on the ground.", victim->pIndexData->short_descr );
			STRFREE(bottle->description);
			bottle->description = STRALLOC(buf);
			
			act( AT_MAGIC, "$N's body wildly spins, getting smaller and smaller.", ch, NULL, victim, TO_CHAR );
			act( AT_MAGIC, "You quickly bottle $N, before $E runs off!", ch, NULL, victim, TO_CHAR );
			act( AT_MAGIC, "$N's body wildly spins, getting smaller and smaller.", ch, NULL, victim, TO_ROOM );
			act( AT_MAGIC, "$n quickly bottles $N, before $E runs off!", ch, NULL, victim, TO_ROOM );
			bottle = obj_to_char( bottle, ch );
			extract_char( victim, TRUE );
		}
		else
		{
			act( AT_MAGIC, "You try to bottle $N, but $E attacks you before you can!", ch, NULL, victim, TO_CHAR );
			act( AT_MAGIC, "$n tries to bottle $N, but $N attacks $m before $e can!", ch, NULL, victim, TO_ROOM );
			multi_hit( victim, ch, TYPE_UNDEFINED );
			learn_from_failure( ch, sn ); 
			return rNONE;
		}
	} 
	return rNONE;
}

void do_unbottle( CHAR_DATA *ch, char *argument )
{
	OBJ_DATA *obj;
	CHAR_DATA *mob;
	MOB_INDEX_DATA *pMobData;
	char arg [ MAX_INPUT_LENGTH ];
	char buf[MAX_STRING_LENGTH];
	int ovalue;
	AFFECT_DATA af;

	
/*	if ( !IS_NPC(ch) && ch->level < skill_table[gsn_bottle]->skill_level[ch->class] )
	{
		send_to_char( "You don't know how to unbottle.", ch );
		return;
	}
*/
	
	one_argument( argument, arg );
	
	if ( arg[0] == '\0' )
	{
		send_to_char( "What do you wish to unbottle?\n\r", ch );
		return;
	}
	
	obj = get_obj_carry( ch, arg );
	
	if ( !obj )
	{
		send_to_char( "You dont have that item.\n\r", ch);
		return;
	}

	if(str_cmp(obj->owner, ch->name))
	{
		send_to_char("&WYou can't unbottle someone else's bottle!\n\r", ch );
		return;
	}
	
        if ( !can_charm( ch, 1 ) )
        {
           act( AT_MAGIC, "You are unable to control any more creatures!", ch, NULL, NULL, TO_CHAR ); 
           return;
        }

	if ( ( obj->pIndexData->vnum == OBJ_VNUM_BOTTLE ) && ( obj->value[0] != 0 ) )
		{
			ovalue = (sh_int) obj->value[0];
			pMobData = get_mob_index( (sh_int) (obj->value[0]) );
			/* sprintf( buf, "This says the mob's vnum will be %d", pMobData->vnum );
				send_to_char( buf, ch );
				return; -Degbugging */
			if ( !pMobData->vnum )
			{
				sprintf( buf, "Missing Bottle - Vnum:[%d]", pMobData->vnum );
				bug( buf, 0 );
				return;
			}
			if ( IS_NPC(ch) || !IS_NPC(ch) )
                            //    number_percent( ) < ch->pcdata->learned[gsn_bottle] )
			{
			mob = create_mobile( get_mob_index( pMobData->vnum ) );
			char_to_room( mob, ch->in_room );
			mob->hit = mob->max_hit = obj->value[4];
			mob->pIndexData->level = obj->value[1];
			mob->pIndexData->hitsizedice = obj->value[2];
			mob->pIndexData->hitplus = obj->value[3];
			
			add_follower( mob, ch );
			mob->leader = ch;
                         af.type      = gsn_charm_person;
                         af.duration  = (number_fuzzy( (ch->level + 1) / 4 ) + 1) * DUR_CONV * 2;
                         af.location  = 0;
                         af.modifier  = 0;
                         af.bitvector = meb(AFF_CHARM);
                        affect_to_char( ch, mob, &af );
                        if ( !IS_NPC(ch) ) 
                            ch->pcdata->charmies++;

			mob->charmed_from = obj->value[5];
			
			sprintf( buf, "You pop open %s, and %s quickly runs out.", obj->short_descr, mob->short_descr );
			act( AT_SKILL, buf, ch, NULL, NULL, TO_CHAR );
			sprintf( buf, "$n pops open %s, and %s quickly runs out.", obj->short_descr, mob->short_descr );
			act( AT_SKILL, buf, ch, NULL, NULL, TO_ROOM );
			sprintf( buf, "With a rush of magical air, %s's body spins wildly, regaining its original shape.", mob->short_descr );
			act( AT_SKILL, buf, ch, NULL, NULL, TO_CHAR );
			act( AT_SKILL, buf, ch, NULL, NULL, TO_ROOM );
			extract_obj( obj );
			learn_from_success( ch, gsn_bottle );
			}
			else
			{
				send_to_char( "You squeeze the bottle too hard, and it breaks in your hands!\n\r", ch );
				extract_obj( obj );
				learn_from_failure( ch, gsn_bottle );
				return;
			}
	}
	else
		send_to_char( "That isn't a bottled mob.\n\r", ch );	
	return;
}
