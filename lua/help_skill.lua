all_helps.skill = {}
all_helps.skill = {
  entries = {
  {
    keywords = {"skill", "skills", "skill list", "skill helps"},
    htype = "catagory",
    level = -1,
    text = function ()
     send("&WHelp files catagorized as 'skill'&D")
     send_nocr("&Y")
     hyphens()
     txt = "&W" .. get_catagory_list ("skill") .. "&Y"
     send(txt)
     hyphens()
     send([[
&WType 'practice' to get a list of skills currently available to you and
to see to what extent you have them practiced.  Type 'slist' to view a
list of all skills available at each level to your class.
]])
   end, -- text function
  },
  {  
    keywords = {"AGGRESSIVE", "AGGRESSIVE STYLE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: style aggressive

This style of combat allows a fighter to strike more effectively, but
leaves many holes in his defenses as well. Fighters who know this tactic
can strike enemies for more damage, but their enemies' weapons will slip
through their defenses for slightly more damage as well.

See Also: style, evasive, defensive, standard, aggressive, berserk
]],
  },
  {  
    keywords = {"AID"},
    level = 0,
    htype = "skill",
    text = [[
Syntax: aid <character>

This skill allows you to bring a stunned person back into consciousness.
]],
  },
  {  
    keywords = {"AMBUSH"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: ambush <victim>

A thug likes to fight on his or her own terms, which are usually quite dirty.
One of the tactics at their disposal is the handy ambush. If an appropriate
level of stealth is achieved, thugs can use a two-handed bludgeoning weapon to
strike their opponent over the head, damaging them, and possibly even stunning
the victim for a short time, allowing the thug to do even more damage. As the
thug grows in experience, the amount of damage done increases.
]],
  },
  {  
    keywords = {"BACKSTAB", "BS"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  backstab <victim>
Syntax:  bs       <victim>

A backstab is a method of attack, used primarily by thieves but able
to be utilized by others in some circumstances, and which inflicts a
tremendous degree of damage on unsuspecting victims if successful.

An appropriate weapon type is required to backstab, and if your victim
is wounded or suspicious it may not be possible to surprise them.  The
most important factor in anyone's ability to backstab is to catch the
victim when they are unaware of your presence.
]],
  },
  {  
    keywords = {"BASH"},
    level = 0,
    htype = "skill",
    text = [[
Syntax:  bash

Bash can only be used once a fight has started.  It will inflict damage and
temporarily daze both yourself and your opponent for approximately two rounds
during which you cannot heal, flee or perform other extraneous combat actions
(i.e. you will be able to dodge/parry/attack but nothing else).  These same
consequences are inflicted on your opponent if it is a player character,
otherwise the skill only inflicts damage.

Note that bash has a drastically reduced chance of hitting if the basher is
not one of the primary combatants (i.e. is not tanking).
]],
  },
  {  
    keywords = {"BERSERK", "BERSERK STYLE"},
    level = 1,
    htype = "skill",
    text = [[
Two different things here...
Syntax:  berserk

Going berserk sends your warrior into a frenzied state, increasing its
attacks per round to a maximum of six and making you a lot stronger.  While
you are berserking you cannot flee.

Syntax: style berserk

This style throws all caution to the wind.  You will hit for quite a bit of
damage, but your opponent will be able to take advantage of the many openings
you leave.  You also cannot flee when in a berserk style.

See Also: style, evasive, defensive, standard, aggressive, berserk
]],
  },
  {  
    keywords = {"BITE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  bite

The act of sinking your teeth into an enemy.
]],
  },
  {  
    keywords = {"BLITZ"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  blitz

Blitz is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"BLOODLET"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  bloodlet

A vampire which is itself sated on blood may open his own veins to drain
a small amount of the vitae for the consumption of a more needy comrade
through the use of bloodlet.  The pool spilled last only a very brief
time, however, as already-consumed blood loses its value quickly once
exposed again to air.
]],
  },
  {  
    keywords = {"BROACH"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  broach <direction>

This skill causes the user to attempt to bypass a locked or barred
door or other obstruction.
]],
  },
  {  
    keywords = {"BUMRUSH"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: bumrush victim

A mighty rushing attack, this skill allows the user to throw themselves and
their weapons towards their victim, causing great damage.  In addition, it is
possible to even stun the victim, allowing the user to cause great damage
directly after the attack also.
]],
  },
  {  
    keywords = {"CHARGE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: charge <spell>

Charge allows a mana user to magically charge a suitably prepared
wand with a spell. The wand must be held. Once the command to charge
a wand is given, several things happen at once. First a maximum amount
of charges that can be placed upon the wand is determined, based
primarily on the caster's level. Next, the amount of mana required
for each charge is determined, based on the spell that the wand is
being charged with. The total current mana that the caster has is
divided by the cost per charge and, provided it doesn't exceed the
maximum charge figure, that figure is the amount of charges that the
wand will get if the charge is successful. The total number of charges
is multiplied by the cost per charge and that total is deducted from
the caster's mana. Basically, the less mana it takes to cast the
particular spell, the more charges a wand of that spell will get,
modified by the amount of mana the caster has at the time, when
charging.

NOTE: If the charge itself fails, the wand is destroyed.
      There are some spells that cannot be charged into a wand at all.
      A successful charge will always leave the caster almost completely
      drained of mana.


SEE: SCRIBE, BREW
]],
  },
  {  
    keywords = {"CHEAPSHOT"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  cheapshot victim

An extremely dishonorable thing to do in combat, the cheapshot doesn't do
hardly any damage at all, but it can potentially stun the victim of the attack
for a short time, making up for its lack of damage by allowing the user to hit
twice as hard as normal.
]],
  },
  {  
    keywords = {"CIRCLE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  circle <mob>

A skill unique to thieves and thugs, and which can only be used while in combat.
It inflicts damage comparable to backstab, and requires the thief to
be wielding a piercing weapon.  To successfully circle you must be the
first to attack in the battle, or be grouped with whoever was.
]],
  },
  {  
    keywords = {"CLAW"},
    level = 1,
    htype = "skill",
    text = [[
Some creatures use their natural weapons in combat.  Claws can dig deep
furrows in your flesh, causing massive damage to you.
]],
  },
  {  
    keywords = {"CLIMB"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  climb  <direction>

This skill enables you to climb into and out of rooms that require it.  It may
also be used automatically in some situations.  Falling may cause damage, so
be careful!
]],
  },
  {  
    keywords = {"CRANE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: crane

The crane style is based around the mystical and magical bird, the crane.
Strong attacks and an iron defense are coupled with the ability to resist
spells and dragon breath.  You can only have one style set at a time.
]],
  },
  {  
    keywords = {"CUFF"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  cuff

Cuff is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"DEFENSIVE", "DEFENSIVE STYLE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: style defensive

This style emphasizes the deflecting of blows from an enemy. It is similar
to the evasive style, except that it focuses on holding ground instead of
dodging. An effective fighter will take less damage from an enemy, but not
as much as one using evasive tactics. A fighter will also do less damage to
enemies, but slightly greater than those who simply evade.

See Also: style, evasive, defensive, standard, aggressive, berserk
]],
  },
  {  
    keywords = {"DETRAP"},
    level = 0,
    htype = "skill",
    text = [[
Syntax: detrap <object>

This skill allows one to disarm a trapped object.
Use it with care.
]],
  },
  {  
    keywords = {"DIG", "DIGGING", "BURY", "BURYING"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  dig
Syntax:  dig  <direction>
Syntax:  bury <item>

You can dig and bury items through the use of the dig skill and bury command.
Buried items are not visible to players, even through the use of spells such
as locate object.  To dig an item up, type dig with no arguments.  Having a
shovel raises your chance of success.  If you dig in a direction, you will
attempt to dig open an exit.

To bury an item (or corpse), drop the item on the ground and bury <item>.
Depending on the size and weight of the object, you might need a shovel.

* Note:  Players can bury/dig up each other's corpses. *

Items buried will not last beyond crash or reboot.  Do not attempt to use
this skill for storage of items you wish to keep.
]],
  },
  {  
    keywords = {"DISARM"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  disarm

Disarm is an auxiliary fighting command to attempt to disarm your opponent.
Several things affect your ability to disarm or resist a disarm attempt
successfully, including your weapon and your stats compared to the weapon
and stats of your opponent.

You can only attempt to disarm your primary opponent, meaning you will be
unable to try to disarm a second or third attacker until you have disposed
of the first.
]],
  },
  {  
    keywords = {"DODGE"},
    level = 0,
    htype = "skill",
    text = [[
Syntax:  operates automatically

Dodge is a skill which assists in the evasion of incoming attacks.  If
you are successful, your opponent's attack misses and you take will
take no damage. Dodge is an automatic skill and requires no weapon.
]],
  },
  {  
    keywords = {"DOMINATE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  dominate <victim>

Dominate allows the character to bend his victim's will to his own.

Dominate is functionally similar to charm, and the rules and matters
of etiquette regarding its use are the same.

See CHARM
]],
  },
  {  
    keywords = {"DOORBASH"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: doorbash <direction>

This skill can be used to effectively bash open doors. NOTE: Not all doors
are affected by this skill.
]],
  },
  {  
    keywords = {"DUAL WIELD"},
    level = 1,
    htype = "skill",
    text = [[
Characters with this skill are able to wield two weapons at once.  To
do so, the character must remove any 'held' item and any shield, then
simply wield two weapons.  Characters with strength under 25 may be
unable to dual wield two very heavy weapons.

Once two weapons are wielded, the affects of the skill are automatic.
]],
  },
  {  
    keywords = {"EAGLE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: eagle

This combat style is based upon the mighty eagle.  Able to move about with
ease, as if flying, the eagle master can hit strong and fast.  In addition to
the amazing blocking ability this style gives, it also gives an aura of
sanctuary.  You can only have one style set at a time.
]],
  },
  {  
    keywords = {"ELBOW"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  elbow

Elbow is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"ENGAGE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: engage victim

This command allows you to switch targets in combat.  Useful when attacked by
a group of mobs and you want to concentrate on attacking a certain mob in the
group.

This code was written by John Patrick (j.s.patrick@ieee.org) and used with
permission.
]],
  },
  {  
    keywords = {"ENHANCED DAMAGE"},
    level = 0,
    htype = "skill",
    text = [[
This skill increases the damage you inflict when attacking.  Use of the
skill is automatic once you have practiced it.  The chance of your damage
being increased, per hit, is based on your skill level.  The amount of damage
added is based on your level...more damage is done by a higher level warrior.
]],
  },
  {  
    keywords = {"ENHANCED HIT"},
    level = 1,
    htype = "skill",
    text = [[
This skill increases chance of hitting when attacking.  Use of the
skill is automatic once you have practiced it.  The increase in chance of
hitting, per hit, is based on your skill level.  The amount of the hitroll
increase added is based on your level...a higher level Ranger has a better
chance to hit.
]],
  },
  {  
    keywords = {"EVASIVE","EVASIVE STYLE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: style evasive

This style of fighting focuses on the art of dodging and parrying blows.
Less damage will be taken by a fighter using this style, but the damage
a fighter does in battle is also reduced due to the concentration needed
for evading an enemy.

See also: style, defensive, standard, aggressive, berserk
]],
  },
  {  
    keywords = {"FOCUS"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: focus

A monk can focus intensely on every little thing about and around its body,
enhancing strength, dexterity, and constitution.  This power grows as the monk
grows in level.
Mana: 50]],
  },
  {  
    keywords = {"GOUGE"},
    level = 1,
    htype = "skill",
    text = [[
syntax:  gouge

This attack can only be used in combat, and will strike at the eyes of
your opponent, causing damage and temporary blindness.

Note that gouge has a reduced chance of hitting if the gouger is not
one of the primary combatants (i.e. is not tanking).

See also BLIND, BLINDED
]],
  },
  {  
    keywords = {"GRASP", "GRASP SUSPIRIA"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  grasp

The suspiric grasp is a very lethal attack, allowing one to
drain the life of its opponent in larger quantities than nearly any
other skill or spell in the Realms.  The more intelligent is the
user, the more effectively it will perform this loathsome act.  Be
aware that the magical nature of this attack causes it to be affected
by the victim's saves.
]],
  },
  {  
    keywords = {"GRIP"},
    level = 1,
    htype = "skill",
    text = [[
This skill is automatic, once practiced.  The skill causes you to grip
your weapon tightly as someone tries to disarm you, making it far more
difficult to successfully disarm you.  This skill will only increase as
you are engaged in fights where someone is attempting to disarm you.
]],
  },
  {  
    keywords = {"HEADBUTT"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  headbutt

Headbutt is a skill which can only be used once a fight has started,
and can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"HIDE", "SNEAK", "CAMOUFLAGE", "VISIBLE"},
    level = 1,
    htype = "skill",
    text = [[
Syntax:  hide
Syntax:  sneak
Syntax:  camouflage
Syntax:  visible

If you successfully hide, creatures cannot see you unless they are affected
by 'detect hidden'.  The same is true with camouflage, except only creatures
with the "demonsight" ability can see you, making it a much more useful skill.

If you successfully sneak, you can move from place to place without being
noticed by other player characters.  If you flee, you will stop sneaking
and will have to 'sneak' again.

In order to either hide or sneak successfully, you will have to practice
the appropriate skill.

Visible (vis) cancels your hiding and sneaking, as well as any invisibility,
effectively making you visible again to all.
]],
  },
  {  
    keywords = {"HITALL"},
    level = 1,
    htype = "skill",
    text = [[
Syntax: hitall

Hitall is a fighter skill that will start a fight by hitting all the
opponents in the room.  For characters it means all the players in the room.

Be aware that area attacks are aggressive to all mobs in the room,
including pets, mounts and charmed creatures.
]],
  },
  {
    keywords = {"skirmish line"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: skirmish

The warrior calls out to their group, ordering them into a wide formation that
increases their effect in combat by the number of members involved in the
formation.
]],
  },
  {
    keywords = {"form ranks"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: form

The warrior both increases the groups defense and the warriors own offense by
ordering the group into a tight formation.
]],
  },
  {
    keywords = {"final stand"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: final

The warrior can choose to meet death defiant and so can gain a boost to their
hp and combat abilities for a short time. However, when the warrior can no
longer sustain their defiance, they might die from their wounds.
]],
  },
  {
    keywords = {"pincer movement"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: pincer

The champion attempts to flank his target, providing a short bonus to damage
and chances of hitting. However, this bonus increases in power for every
member of the champions group assisting in the movement.
]],
  },
  {
    keywords = {"cleanse aura"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: cleanse

The monk enters a deep trance, realigning their centers of energy inside their
body, cleansing themselves of many negative effects.
]],
  },
  {
    keywords = {"tendon strike"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: tendon

The rogue strikes the soft tendons of his victim, keeping them immobile for a
short time.
]],
  },
  {
    keywords = {"salt wounds", "salt wounds"},    
    level = 1,    
    htype = "skill",
    text = [[
]],
  },
  {
    keywords = {"crush"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: crush

Use the size and weight of your own weapon to crush your opponent. This skill
can only be used in combat and requires a two-handed blunt weapon.
]],
  },
  {
    keywords = {"shadow venom"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: shadow <weapon>

A highly skilled thief can learn ways of increasing the potency of the poison
applied to a weapon, making it deadlier and the weapon's sting even greater.
This skill requires some black poisoning powder and a water container.
]],
  },
  {
    keywords = {"snipe"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: snipe <target>

Using the element of surprise one can fire a bolt at their target and inflict
a great amount of damage. This skill requires the use of a missle type weapon
and to be in some kind of stealth mode.
]],
  },
  {
    keywords = {"enhanced dual wield"},    
    level = 1,    
    htype = "skill",
    text = [[
This skill is automatic once learned.

Enhanced dual wield allows a champion to wield a two-handed weapon as if it
were a one-handed weapon. This means a champion can dual wield two two-handed
weapons, or wield a two-handed weapon and wear a shield, or wield a two-handed
weapon and wear a held item or, like dual wield, wield two one-handed weapons.
]],
  },
  {
    keywords = {"enjoying the game"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: enjoy

The rogue appreciates the fun of battle and gains a bonus to her fighting
abilities in direct relation to how much health she has. The more hurt the
rogue is, the less effective her jovial nature becomes.
]],
  },
  {
    keywords = {"tactical retreat"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: tactical

The champion knows when to leave gracefully and exits combat. However, the
champion also gains a small bonus to their ability to fight as well as a
slight boost to their health.
]],
  },
  {
    keywords = {"vanish"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: vanish

The rogue throws a flash bomb, immediately removing herself from combat.
]],
  },
  {
    keywords = {"high jump", "high_jump"},    
    level = 1,    
    htype = "skill",
    text = [[
]],
  },
  {
    keywords = {"left handed"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: left

The rogue reveals that he has been fighting with his less dominant hand and
switches to his strong hand. He gains a huge bonus to his combat abilities for
a very short time.
]],
  },
  {
    keywords = {"skin"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: skin corpse

With proper teaching a player can strip the hide away from any mob corpse. The
hide can be used for various other skills in the creation of items.
]],
  },
  {
    keywords = {"smelt"},    
    level = 1,    
    htype = "skill",
    text = [[
]],
  },
  {
    keywords = {"southpaw"},    
    level = 1,    
    htype = "skill",
    text = [[
]],
  },
  {
    keywords = {"die laughing"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: die

The rogue will not face death a dour woman, instead when a rogue is critically
injured her insane laughing boosts her offensive capabilities while lowering
her opponents.
]],
  },
  {
    keywords = {"disengage"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: disengage

The crafty individual can circle around their opponent, allowing them to exit
combat with no penalties.
]],
  },
  {
    keywords = {"flash bang"},    
    level = 1,    
    htype = "skill",
    text = [[
]],
  },
  {
    keywords = {"apologize"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: apologize

The rogue makes a "heartfelt" apology. This lowers the animosity of the two
sides, lowering both the rogue and his targets dr/hr. Although the target
loses much more animosity.
]],
  },
  {
    keywords = {"blitzkrieg"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: blitzkrieg

The warrior throws caution to the wind and attacks with reckless abandon. This
increases the warriors offensive capabilities but also weakes his defenses.
]],
  },
  {
    keywords = {"pressure point"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: pressure <victim>

Having extensive knowledge of weak points on others bodies, you are able to
strike out at these points, inflicting damage and causing the victim to become
physically susceptible.
]],
  },
  {
    keywords = {"crashing wave"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: crashing <victim>

By drawing upon your magical abilites and your body's own energies, you can
focus these into a single damaging attack.
]],
  },
  {
    keywords = {"shock strike"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: shock <victim>

By focusing on the powers of lightning, you can channel that energy into a
powerful bare-handed blow.
]],
  },
  {
    keywords = {"ice palm"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: ice <victim>

By focusing on the freezing powers of water, you can channel that energy into
a powerful bare-handed blow.
]],
  },
  {
    keywords = {"gnaw"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: gnaw <victim>

Lash out at your victim and take a chunk out of their flesh.
]],
  },
  {
    keywords = {"street brawler"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: street

Life on the streets can make you pretty buff and resistant to damage and
paralysis.
]],
  },
  {
    keywords = {"fire fist"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: fire <victim>

By focusing on the element of fire, you can channel that energy into a
powerful bare-handed blow.
]],
  },
  {
    keywords = {"fishhook"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: fishhook <victim>

Inflict pain on your victim and cause them to lose magical focus by
fishhooking them.
]],
  },
  {
    keywords = {"garrote"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: garrote <victim>

This skill can only be used to initiate combat.
Get the jump on your victim and render their magical abilities almost useless.
]],
  },
  {
    keywords = {"catnap"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: catnap

Take a short, but invigorating, nap to recover a portion of mana and moves.
]],
  },
  {
    keywords = {"invigorate"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: invigorate

Sometimes you need to be invigorated to make those long journies...
]],
  },
  {
    keywords = {"nirvana"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: nirvana

Enter into a state of extreme concentration while recovering dwindled magical
abilities.
]],
  },
  {
    keywords = {"telegraph"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: telegraph

By focusing on the subtle movements of your opponents, you can temporarily
increasing your ability to dodge and parry attacks as well as negate some of
the damage.
]],
  },
  {
    keywords = {"south paw", "southpaw"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: southpaw

Switch to fighting with your weaker hand and open up your opponent to greater
damage. Be warned, this tactic lessens your ability to parry and dodge.
]],
  },
  {
    keywords = {"low guard"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: low

This skill is a guard stance.
Switch to a low guard stance for increased protection. Activating another
guard stance will deactivate low guard.
]],
  },
  {
    keywords = {"liquid sword"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: liquid <victim>

Twirl your own weapon around that of your opponent, causing damage and
crippling your opponent's ability to dodge or parry for a short time.
]],
  },
  {
    keywords = {"shell defense"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: shell

This skill is a guard stance.
Switch to a conservative guard style without sacrifice to power and gain a
bonus to your ability to absorb damage and avoid paraylsis. Activating another
guard stance will deactivate shell defense.
]],
  },
  {
    keywords = {"clinch"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: clinch <victim>

Wrap up your victim, pulling their head down and delivering a massive knee to
the temple. The attack also dazes the victim, making them very vulnerable to
paralysis attacks for a time.
]],
  },
  {
    keywords = {"defiance"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: defiance

Focus your ability for physical punishment and increases your defenses
drastically in all aspects for a short time.
]],
  },
  {
    keywords = {"bladedancer"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: bladedancer

Display your weapon skill with a dazzling dance and increase your defenses in
a shield of theatrics.
]],
  },
  {
    keywords = {"left hand"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: left

Reveal to your opponent that you have been fighting with your less dominant
hand and switch to your strong hand and gain a bonus to your combat abilities
for a short time.
]],
  },
  {
    keywords = {"capoeira"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: capoeira

This is a rare and physically draining fighting skill. The user dances around
their surrounding opponents, confusing them and weaking their ability to
target, while also dealing a varied amount of damage.  However, the user must
sacrifice his own magic to fuel the energy required to do such complicated
movements in a blink of an eye in order to not leave the user exhausted
afterwords.
]],
  },
  {
    keywords = {"high guard", "high_guard"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: high_guard

This skill is a guard stance.
Assume a high guard stance and increase your ability to hit and deal damage,
but be warned, this stance may leave you slightly vulnerable. Activating
another guard stance will deactivate high guard.
]],
  },
  {
    keywords = {"wrist slash"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: wrist <victim>

This attack targets the victim's wrists and causes the victim to be unable to
effectively wield their weapon for a short while.
]],
  },
  {
    keywords = {"gather"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: gather

Gather allows a player to go into forested areas and gather up some wood,
useful for creating fires. The wood also has other uses in crafting items.
]],
  },
  {
    keywords = {"ignite"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: ignite <combustable>

This skills allows a player to set a combustable on fire. Fires are used for
a variety of other skills. Different combustables will start the fire at
different temperatures.
]],
  },
  {
    keywords = {"tan"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: tan <skin>

Drying a skin will make it into a hide that can then be used to craft certain
types of equipment or other items.
]],
  },
  {
    keywords = {"mine"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: mine

This skill allows a player to venture into mountainous or underground areas
and dig up various metals and gems. These items will need to be processed in
order to use them in any way.
]],
  },
  {
    keywords = {"concentrate"},    
    level = 1,    
    htype = "skill",
    text = [[
LEGENDARY SKILL:

Learning how to concentrate during battle is one of the most difficult tasks
to accomplish, but when you're taught by the master's and mistresses that have
sound advice, the ability to concentrate is very possible. Taught only to
those who seek this skill, the amount of hit and damage you do is increased.

This skill costs mana. See also: Legendary
]],
  },
  {
    keywords = {"windwalk"},    
    level = 1,    
    htype = "skill",
    text = [[
LEGENDARY SKILL:

Dancing on the winds of change is never easy, but if you've mastered WINDWALK,
it's...a breeze. Using the currents of air all around you, parry, dodge, and
the ability to avoid being hit are increased. Just a puff of time goes by
before you must beckon the winds once more, but the affects are worth the time
invested in this skill.

This skill costs mana. See also: Legendary
]],
  },
  {
    keywords = {"bladesong"},    
    level = 1,    
    htype = "skill",
    text = [[
LEGENDARY SKILL:

The power of a weapon that belongs to a person is increased simply by the
knowledge of the weapon itself. Legend has it, that if a certain skill is
learned, hitting your opponent is as easy as slicing butter with a hot knife.
The unity with one's blade is temporary and expensive to work but finding the
BLADESONG is a feeling only a selct few can master.

The cost of this skill costs hitpoints and moves. See also: Legendary
]],
  },
  {
    keywords = {"bloodsong"},    
    level = 1,    
    htype = "skill",
    text = [[
LEGENDARY SKILL:

The heat of battle. The rage of your ancestors flowing through your veins. The
sounds of battle all around you but the only thing you can hear is the  sound
of your heart beating in your ears.  Your eyes lose focus as your muscles take
over with the memory of every trained skill you've ever honed to perfection.
You can only feel the flush of wrath as it overcomes you  with its BLOODSONG.

This skill costs hitpoints and moves.  See also: Legendary
]],
  },
  {
    keywords = {"starcloak"},    
    level = 1,    
    htype = "skill",
    text = [[
LEGENDARY SKILL:

Learning to become one with the heavens benefits the user of this skill by
protecting them in a cloak of stars that reflect negativity from the wearer.
Resistance is futile? Not a chance when this skill is applied.

This skill uses mana and moves. See also: Legendary
]],
  },
  {
    keywords = {"willpower"},    
    level = 1,    
    htype = "skill",
    text = [[
LEGENDARY SKILL:

Better than a Baywatch lifeguard, this saves you all around for only the cost
of mana. See also: Legendary
]],
  },
  {
    keywords = {"riposte"},    
    level = 1,    
    htype = "skill",
    text = [[
]],
  },
  {
    keywords = {"treage"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: treage

The champion uses their knowledge of field medicine to quickly heal themselves
outside of combat.
]],
  },
  {
    keywords = {"serpent kiss"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: serpent

The champion using 2 weapons delivers several quick strikes to key pressure
points in their target, doing damage and making their opponent temporarily
vunerable to further damage and stun.
]],
  },
  {
    keywords = {"shield slam"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: shield

The champion with a shield equips delivers a massive strike with their shield,
doing damage and having a chance of sending the target to the ground.
]],
  },
  {
    keywords = {"tailor"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: tailor <hide> <type> <location>

With a fully tanned hide, adventurers can tailor them into various pieces of
armor or other objects.

Type      	|   Locations
------------------------------------------------------------------------------
armor           head, face, body, arms, hands, about, back, waist, legs,
                feet, ankle
container       hold
drinkcon        hold
]],
  },
  {
    keywords = {"forge"},    
    level = 1,    
    htype = "skill",
    text = [[
Syntax: forge <slab> <type> <location>

With slab of material, adventurers can forge them into various pieces of
armor, treasures and weapons.

Type      	|   Locations
------------------------------------------------------------------------------
armor           head, face, body, arms, hands, about, waist, back, legs, feet
                shield, ankle
treasure        ears, neck, wrist, finger, ankle
weapon          axe, sword, dagger, mace, claw
]],
  },
  }
}