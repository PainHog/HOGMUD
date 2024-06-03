  {  
    keywords = {"INFRAVISION INFRARED"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c infravision
Syntax:  c infravision <character>

This spell enables the character to detect the heat signatures of other
players and creatures in the room with them.  This spell will also allow
you to find items in corpses, containers, etc. but will not allow you to
view the actual contents.

You must have a light source to actually see items, room descriptions,
the contents of corpses or containers, room exits and the like inside
a darkened area.

Infravision is not the same as "night vision".
]],
  },
  {  
    keywords = {"INNER WARMTH"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'inner warmth'

This spell makes you more resistant to all forms of coldness.

]],
  },
  {  
    keywords = {"INSTALLAREA"},
    level = 59,
    type = "wizhelp",
    text = [[
Syntax: installarea <area filename> <full area name/title>

Installs a prototype area into the mud as a non-prototype area.
The filename can be fixed with aset, (don't forget to foldarea the new name.)

Currently the builder should quit and have his/her vnums cleared manually.
(This should be fixed soon).
]],
  },
  {  
    keywords = {"INSULT"},
    level = 1,
    type = "skill",
    text = [[
Syntax: insult "victim"

Jesters have travelled the realm, and in that time, learned quite a few
insults from the various cultures in the land.  They know the perfect one for
each target.  In combat, they can insult their victim to the point where they
lose all reason and open themselves up to more damaging hits from the witty
adventurer.
]],
  },
  {  
    keywords = {"INT", "INTELLIGENCE"},
    level = 1,
    type = "info",
    text = [[
Intelligence (INT in your 'score') represents your character's mental
capacity.  Among other things, it affects:

 - heavily influences the amount of mana a character gains at level

 - affects the amount of mana regenerated or recovered at each tick
   if a character is resting or sleeping

 - the rate at which a character learns a new skill or spell

 - the percentage rate at which a character practices a new language

Intelligence is an important factor in learning between combatants.  If
a character fights a creature several times, the more intelligent of the
two opponents will gain an advantage over time...
]],
  },
  {  
    keywords = {"INVADE"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: invade areaname.are #ofmobs mobvnum #glory

This command loads up a certain number of mobs into an area.  It tries to
avoid safe rooms, but otherwise mobs just appear (:  Fun command to get bored
players to help clean up an invasion of mobs from the towns.
Specify glory to be awarded for killing the invading mobs.
]],
  },
  {  
    keywords = {"INVIS", "MASS INVIS", "IMPROVED INVIS"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast invis <character>
Syntax: cast 'mass invis'
Syntax: cast 'improved invis' (character)

The INVIS spell makes the target character invisible.  Invisible characters
will become visible when they attack.

The MASS INVIS spell makes all characters in the caster's group invisible,
including the caster.

The IMPROVED INVIS spell works on one character, but that character stays
invisible until the spell wears off, even in combat.]],
  },
  {  
    keywords = {"INVIS OBJECT"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: cast 'invis object' object

An interesting little spell, mages have learned how to turn objects
invisible.  Unlike other invisibility spells, this never runs out, so
a mage can be in a situation where they turn their objects invisible, then
lose their detections spells, and not be able to find their objects.  At
first this may seem like a useless spell, but in fact there are many things
you can do with it.  Opponents find it difficult to dodge a weapon they
cannot see, and it's quite hard for someone to locate invisible items that
cannot see.
]],
  },
  {  
    keywords = {"INVOKE DRAGON"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'invoke dragon'

A shaman can channel the spirit of the awesome dragon, giving him a boost to
his damroll and hitroll.  The dragon spirit also helps the shaman avoid
damage, paralysis, breath attacks and other spells.  Invoking an animal spirit
removes any previous animal spirit the shaman may of channeled.
]],
  },
  {  
    keywords = {"INVOKE STAG"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'invoke stag'

A shaman can channel the spirit of a mighty stag, giving him a boost to his
dexterity, hitroll and even help absorb some incoming damage.  Invoking an
animal spirit removes any previous animal spirit the shaman may of channeled.
]],
  },
  {  
    keywords = {"INVOKE WOLF"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'invoke wolf'

A shaman can channel the spirit of a fearsome wolf, giving him a boost to his
dexterity, strength, damroll and hitroll.  Invoking an animal spirit removes
any previous animal spirit the shaman may of channeled.
]],
  },
  {  
    keywords = {"IPCOMPARE"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: ipcompare <name>
        ipcompare <site>
        ipcompare <name or site> <room|area|world> <#>

This takes * as a wild card.
Ipcompare will compare online users to search for multiplayers. A positive
match using ipcompare does not always mean it is a multiplayer..but shows
that there are more than one user from a site on simultaneously.
Ipcompare <field> <#> will limit the output to x number of lines based on #.
* may be used as a wild card, for example ipcompare 207.18.3.* will return
matches from any that begin with the ip prior to the asterisk.
Ipcompare <field> <room|area|world> will limit the search based on that
criteria.  The room|area|world limitation will be judged on the room that
the immortal issued the command in.  So if you are in a different area
than the victim, it will show only players matching the site in the area
you are in.
]],
  },
  {  
    keywords = {"ITEMVALUES"},
    level = 53,
    type = "wizhelp",
    text = [[
In these values, 'sn' is a spell number;  a negative value means 'no spell'.
Item Type |V0         |V1          |V2         |V3         |V4       |V5
----------|-----------|------------|-----------|-----------|---------|-------
armor     |current AC |original AC |           |           |         |
container |capacity   |flags       |key vnum   |condition  |         |
drinkcon  |capacity   |quantity    |liquid #   |poison?    |         |
food      |food value |(condition) |           |poison?    |         |
herb      |           |charges     |herb #     |           |         |
key       |(lock #)   |            |           |           |         |
keyring   |capacity   |            |           |           |         |
lever     |leverflags |vnum/sn     |vnum       |vnum/value |         |
light     |           |            |hours left |           |         |
money     |# of coins |coin type   |           |           |         |
pill      |spell level|sn 1        |sn 2       |sn 3       |food val |
pipe      |capacity   |# of draws  |herb (sn)  |flags **   |         |
potion    |spell level|sn 1        |sn 2       |sn 3       |         |
projectile|           |            |           |           |         |
salve     |spell level|charges     |max charges|delay      |sn       |sn
scroll    |spell level|sn 1        |sn 2       |sn3        |         |
staff     |spell level|max charges |charges    |sn         |         |
switch    |leverflags |vnum/sn     |vnum       |vnum/value |         |
trap      |charges    |type        |level      |flags      |         |
treasure  |(type)     |(condition) |           |           |         |
wand      |level      |max charges |charges    |sn         |         |
weapon    |condition  |num dice    |size dice  |weapontype |         |
missiles  |condition  |            |dam bonus  |weapontype |range    |
quiver    |capacity   |flags       |key vnum   |condition  |         |
funiture  |           |            |(type)     |           |         |
npc corpse|           |            |rot timer  |weight     |         |
pc corpse |           |pk (1 or 0) |           |           |pc level |

** pipe flags : see help pipeflag
** npc and pc corpse is for reference only. These items should not be oinvoked
and the values should not be altered unless you know what you are doing.
]],
    see_also = {"OBJECTTYPES", "WEAPONTYPES", "SLOOKUP", "LIQUIDTYPES", "LEVERFLAGS", "OSET",
                "ARMORCLASS", "WEAPONCONDITION", "MISSILES"},
  },
  {  
    keywords = {"JAB"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  jab

Jab is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"JESTER", "JESTERS"},
    level = 0,
    type = "class",
    text = [[
A strange class, the jester.  Master of many odd tricks, he can move about
with great quickness and is very strong, due to the acrobatic nature of his
stunts.  Not the normal "HaHa" jester you find in the halls of Kings, these
jesters are the "battlefield reporters" of the Realm.  They love to roam the
continents, gathering knowledge, for who knows when you'll need more
knowledge!  A mixture of skills from all over the board, plus a few handy
other tricks keep a jester useful all the time.

Charisma is a jesters prime attribute, with dexterity the secondary.  Luck is
their tertiary statistic.

The races of Human, Elf, Halfling, Pixie, Half-elf, Sea-elf, Gnome, Ghoul and
Goblin are allowed to be jesters.
]],
  },
  {  
    keywords = {"JUDO"},
    level = 1,
    type = "skill",
    text = [[
Syntax: judo

Another combat style from the East, this builds upon the attacks and defense
of karate, and also helps resist magical attacks too.
]],
  },
  {  
    keywords = {"JUGGLE"},
    level = 1,
    type = "skill",
    text = [[
Syntax: juggle

An interesting skill, juggle allows the user to quickly toss their weapon
about, confusing their attacker as to where to actually strike.  This gives
the user a higher chance to dodge and parry while in combat.
]],
  },
  {  
    keywords = {"JUNK"},
    level = 1,
    type = "command",
    text = [[
Syntax: junk (fullobjectname)

Sometimes you have an item in your inventory that you don't want, don't want
to donate, and is not acceptable for sacrificing to the gods.  You can "junk
(item)" to get it out of your inventory. This does not, however, work for
cursed items.
]],
  },
  {  
    keywords = {"KARATE"},
    level = 1,
    type = "skill",
    text = [[
Syntax: karate

The first combat style learned by all monks, this impressive command of combat
will not only increase the attacking power and accuracy of the user, but also
helps defend from foes.
]],
  },
  {  
    keywords = {"KHISTORY"},
    level = 58,
    type = "wizhelp",
    text = [[
Syntax: khistory <player>

This command will display a list of mobs recently killed by the
character in question.
This is an imm only command.
]],
  },
  {  
    keywords = {"KICK"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  kick

Kick is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"KILL", "MURDER", "MURDE"},
    level = 1,
    type = "command",
    text = [[
KILL MURDER
Syntax:  kill     <character>
Syntax:  murder   <character>   -- must be level 5 or higher to murder

KILL starts a fight, and, hopefully, kills something.

MURDER is used to initiate attacks on other player characters (WARNING:
see 'laws pkill' for restrictions on attacking other players).  You must
be level 5 or higher to be able to use the murder command.

You must fully spell out "Murder"

CAREFUL:  PKing someone over 10 levels below your level will get you flagged
as a KILLER.
]],
  },
  {  
    keywords = {"KILLER", "BULLY"},
    level = 1,
    type = "info",
    text = [[
During the course of play, characters may pick up a Killer flag.  This is
almost always the result of an illegal PK.  Once again, an Illegal PK is
attacking and/or killing any character more than 10 levels underneath
you...you can attack anyone above you.  "Nice" characters are the
exception...attacking a "nice" player, or being "nice" and attacking anyone
will also count as an illegal PK.

Killer flags will stop most shopkeepers from dealing with you, and some will
attempt to report your location to others.  Guards and the Masked Hunters will
attack you on site, and possibly even track you down.  Players of any level
can attack you without fear of being flagged themselves.

The ONLY way to lose a Killer flag is to be pardoned by an immortal.  That's
it.  We understand there are fun situations where a high level character may
attack a low level, and we will pardon those players as soon as possible.
However, we reserve the right to leave that flag on you as long as I want.

Bullys are those who steal from a non-deadly player and get caught...same deal
as Killer flags, ask for removal...and pray.
]],
  },
  {  
    keywords = {"KILLSTEAL", "KILLSTEALING"},
    level = 1,
    type = "rule",
    text = [[
Don't do it.
Kill stealing occurs when a player attacks a mob that is already being
fought. This is both annoying and illegal. If someone should do this to
you please inform them of the rules. If they continue, seek an immortal
but do not take the law into your own hands.
]],
  },
  {  
    keywords = {"KINDRED STRENGTH"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast 'kindred strength' <character>

This spell increases the strength of the target character.
]],
  },
  {  
    keywords = {"KNEE"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  knee

Knee is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"KNEECAP"},
    level = 1,
    type = "skill",
    text = [[
Syntax: kneecap

A most devastating attack, used by those who definitely do not fight fairly.
In addition to doing a bit of very painful damage, this attack causes the
victim to lose a bit of their combat power.  In addition, the awful pain also
makes it impossible for the victim to move quickly, ensuring they cannot flee
from battle for a short time.
]],
  },
  {  
    keywords = {"KNOCK"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast 'knock'  <direction>

This spell enables one to unlock doors.
]],
  },
  {  
    keywords = {"KNOW ALIGNMENT"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'know alignment' <character>

This spell reveals the alignment of the target character.
]],
  },
  {  
    keywords = {"KOBOLD CAVERNS"},
    level = 1,
    type = "info",
    text = [[
One night, one of the dwarven roadbuilders mentioned to the innkeeper at the
Tickler in Drazukville that a tribe of kobolds had taken up residence in an
old mine just east of the city.  The tale mentioned that there was a steep
climb to reach the mineshaft.  Kobolds are strange creatures; look like small
dogs, don't seem very smart, but sometimes are able to craft wondrous magical
objects.
]],
  },
  {  
    keywords = {"LAND"},
    level = 1,
    type = "command",
    text = [[
Syntax: land

Cancels all fly and floating affects immediately.  Affects given by equipment
will go away, but reappear in a short time.  You will have to remove that
equipment if it is necessary to stay on the ground.
]],
  },
  {  
    keywords = {"LANGUAGES", "LANG"},
    level = 1,
    type = "command",
    text = [[
Syntax: languages
Syntax: language learn <language name>

Languages alone shows which languages you know, and "language learn
<name>" will add to your percentage of language knowledge.  To learn a
language, a scholar who is knowledgeable in that tongue must be present.

If someone is speaking in a language, and you know it, you will
understand what they are saying.  However, to change the language in which
you are speaking, you must change that manually.  (See help on SPEAK).
]],
    see_also = {"LANGUAGE", "SPEAK"},
  },
  {  
    keywords = {"LAST"},
    level = 1,
    type = "command",
    text = [[
Syntax: Last (charname)

Check and see when the last time a player was online.
]],
  },
  {  
    keywords = {"LAW CHANNELS"},
    level = -1,
    type = "rule",
    text = [[
&GSpam (repeating the same message repeatedly or otherwise purposely causing
the screen to scroll), harassment (including sexual) and abusive behavior are
not permitted on any channel (this includes in 'say' or 'tell').  Do not
continue to 'tell' to someone after they have asked you to stop.

Profanity is not permitted on any public channel, which is a channel seen by
those other than yourself and the person to whom you are speaking.  If you
use profanity in a private conversation and the other party asks you to stop,
please respect their wishes.  The difference between '****, I'm having a bad
day' and 'what is your ****** problem' should be obvious to everyone.  Deities
can decide whether or not its OK to use profanity on Ftell.

If any level of Immortal asks you to desist on a subject, or to move the
subject to an appropriate channel, do so immediately.  Continuing on a
subject or channel after you are requested to stop may result in your
character losing its access to channels through silencing.  An Immortal's
decision on subject matter and/or channel use should be obeyed.

&WWarning:  &GArguing with or flaming immortals on channels _will_ get you
silenced or worse, and this may extend to your other characters as well if
you push the matter. House of Ghouls provides ample avenue for complaint
without resorting to public baiting and name-calling.
]],
  },
  {  
    keywords = {"LAW CHARM"},
    level = -1,
    type = "rule",
    text = [[
&GDo not bring aggressive mobs into or near Drazukville, as when their charm
wears off (either naturally or by attack) their aggressive nature will
return.  Also do not bring aggressive mobs into areas which are lower in
level than the area from which the mob originally came.  You can use the
'areas' command to check an area's level.  See 'help charm' for more.
]],
  },
  {  
    keywords = {"LAW CHEATING"},
    level = -1,
    type = "rule",
    text = [[
&GCheating is a very serious offense and subjects _all_ characters involved
to a slay, purge (loss of all equipment), freeze, balzhur (destruction of
all equipment and public demotion to level 2), deny or even a site ban.

What is considered cheating?
 - exploiting (intentionally using) a bug to gain equipment or gold
 - intentionally causing the system to crash
 - intentionally duplicating equipment or gold
 - knowingly accepting illegal equipment (see above) from others
 - attempting to duplicate equipment or gold -- * even if not successful *
 - using or making profit from equipment that was accidentally duplicated
 - using gold that was accidentally duplicated
 - finding clever ways to "work around" the rules as they are intended will be
   considered cheating also, after a review of the circumstances.

Cheating hurts the game, and every player in the game.  Protect yourself
and report any bugs you find, and inform the Immortals if you have strong
cause to believe someone is engaged in any of the above.

If you find you have accidentally duplicated an item, turn the item over
_immediately_ to an Immortal or drop and sacrifice the item.
]],
  },
  {  
    keywords = {"LAW HARASSMENT"},
    level = -1,
    type = "rule",
    text = [[
&GHarassment is giving a person unwanted attention, whether you perceive it
as negative or positive attention.  If a person is made to be uncomfortable
by your attention or comments, you are harassing that person.  If a person
asks you to desist in talking to them or performing socials on them, and
you do not stop, you are harassing that person.  If you act in an intimate
manner to a character, without their permission, you are harassing that
person.

No form of harassment is tolerated at House of Ghouls.  We especially frown
upon unwanted comments or actions with a sexual nature or explicit content.
If you do not have an intimate relationship with the person, whether in real
life or within House of Ghouls, you should refrain from using suggestive
actions and/or comments.

If you are caught harassing another player in any way, you can be silenced,
helled, frozen, denied, and/or site banned.  Harassing another player is a
serious violation of the rules and will not be permitted.  If you choose
to harass an immortal, you will simply be deleted.
]],
  },
  {  
    keywords = {"LAW KILLSTEAL"},
    level = -1,
    type = "rule",
    text = [[
Don't do it...

Kill stealing occurs when a player attacks a mob that is already being
fought.  This is both highly annoying and illegal.  If someone should do
this to you please inform them of the rules (ask them to read 'laws
killsteal').  If they continue, seek an immortal but do not take the law
into your own hands.
]],
  },
  {  
    keywords = {"LAW", "LAWS"},
    level = -1,
    type = "rule",
    text = [[
&GHouse of Ghouls is governed by a set of laws, most of which are simple
common sense and courtesy, and all of which must be followed to ensure
everyone the opportunity to enjoy the game.  As with any mud, a player's
presence here is a privilege, not a right, and is something we reserve the
right to deny at any time at our discretion.

The Immortals of the House of Ghouls are responsible for enforcing these laws,
and their decisions on these matters should be abided. If you feel an Immortal
has treated you unfairly, you may petition directly to a level 60 (God)
or higher or you may petition via a note at Kallista.

WARNING:  Impersonating an Immortal by any means is BAD.  If you are caught,
you will be punished harshly.

The decisions of a God or higher are final.  To see which Immortals are
online and visible, type "who 52" at any time.

To read the laws, type "laws <topic>" for any of the following:
&W
       |  CHANNELS      |  PKILL     |  SPAM    |  HARASSMENT     |
       |  MULTIPLAYING  |  SHARING   |  STAKE   |  CHARM          |
       |  OBJECTS       |  CHEATING  |  MURDER  |  KILLSTEAL      |

&GFor further explanation, see section 2 of the Adventurer's Guide...
]],
  },
  {  
    keywords = {"LAW MULTIPLAYING"},
    level = -1,
    type = "rule",
    text = [[
&GMulti-playing is not permitted at House of Ghouls. Don't do it. We
understand that you can spoof your IP and all that. If you want to go
through that much trouble to multiplay, you have issues.

We also understand that some of you have computers sitting behind a router of
some type that reports back a common IP address for those of you sharing a
connection between multiple computers...let an Immortal know that, if that is
the situation.  We will be pretty reasonable about these things.

We also ask for character separation.  Each character should be a different
"person".  You can say whatever you want on private channels, but on public
channels, each character you own should attempt to stay "separate".  Trading
equipment between characters or using one character to help out another one of
your characters is a bad thing.  Being caught may result in the loss of
equipment, or worse.

&WNOTE:&G  Link-dead characters are not considered to be "online", however, if
you abuse this loophole by switching back and forth to trade equipment or
whatever, it is considered multiplaying, and action will be taken.&D
]],
  },
  {  
    keywords = {"LAW MURDER"},
    level = -1,
    type = "rule",
    text = [[
&GPlayer killing is decided the instant you cast any hostile spell or make
any aggressive action against a non-deadly player.  Actually killing the
target means little.

Being involved in an illegal pkill is a serious violation of law, and can
result in a stay in hell, slay, loss of all equipment, freeze and/or deny
or site ban.
]],
  },
  {  
    keywords = {"LAW OBJECTS"},
    level = -1,
    type = "rule",
    text = [[
&GIf you notice an item on the ground and there is a player in the room with
it, do _not_ pick it up without first getting permission from the person(s)
in the room.  Taking such items may be considered stealing if you do not
first obtain permission from those present.

Do not simply take an item to identify it without asking permission.  If
you are asked to drop an item you picked up, do so immediately.

Do not take items laying next to a corpse, even if no one is present,
without asking the owner of the corpse if the item(s) belong to them.

Do not take items from a mob corpse unless you made the kill yourself or
you have specific permission from the character who made the kill.  This
includes removing gold from a corpse.

* &WWarning:&G  It is never wise to leave items or containers unattended and
  expect them to be there when you return.  If there is an item on the
  ground and there is neither a corpse nor a player in the room, the
  object is considered abandoned and free for the taking.&D
]],
  },
  {  
    keywords = {"LAW PKILL"},
    level = -1,
    type = "rule",
    text = [[
.&G After level 5 and before level 25, a player has the chance to sign the
Book of Blood, 1 east and 1 south of Kallista, to become a Deadly player.
Anyone NOT switching by then will not be able to switch later.  You must
decide between those levels if you are to take part in Player Killing.

Here's the PK Rules:
- ANYONE CAN BE PKED!  Yes, this means that a lvl50 character can kill a lvl10
character.  However...

- PKing anyone more than 10 levels beneath your level is deemed an Illegal PK.
Illegal PK's will get you a KILLER flag, which makes life quite rough.
Guards and Hunters will track you down and most shopkeepers will ignore you.
Plus, any other character can kill you with no penalty.  Check help on KILLER
for more info about this.  It is the attackers responsibility to check if
their victim is PKable...this is done by doing a "whois" command on that
victim, or just checking the who list to see if they have a "PK" flag.

- Anyone can loot anyone else's corpse.  Keeping restrung items is frowned
upon, however, those items should usually be marked to ensure they are not
included on a corpse after death...special situations will be moderated by an
Immortal, and their decision on who gets what is final.  The one exception to
this rule is the corpse of a non-deadly player.  While it is indeed possible
to loot one, it is a bad thing to do so.  Anyone reported to have looted a
non-deadly players corpse will get flagged as a KILLER, probably for a long
time.  Also, if you are marked non-PK, and you loot the corpse of a character
who is flagged PK, you will be happily set as a PK-player if caught or
reported, in order to make things fair.

- Anyone can assist a PKer with spells, such as healing or whatnot, without
being penalized.  Plus, anyone who is in a group in which the leader attacks a
character that puts the group member in an illegal PK situation should not
auto-assist the group leader in that combat.

&WWarning&G:  Going AFK or link-dead in a non-safe area leaves you open to
attack; you are open to attack every second online, link-live or not.
]],
  },
  {  
    keywords = {"LAW SHARING"},
    level = -1,
    type = "rule",
    text = [[
&GCharacter sharing is not permitted at House of Ghouls. At no time should any
player reveal their character's password to another player. If it is
determined that a character is being shared, that character may be deleted. It
is YOUR responsibility to keep your passwords safe.&D
]],
  },
  {  
    keywords = {"LAW SPAM"},
    level = -1,
    type = "rule",
    text = [[
No, we are not talking about a luncheon meat here.  Spam is the repeated use
of a phrase, command, or channel that causes screen scroll for others.  Not
only is spam considered rude, but excessive screen scroll can interfere with
the game play of anyone seeing it (not to mention combat situations).  The
game will also tell you to PUT A LID ON IT and force-quit you after the 20th
repeat of a single command

It is also considered spam to use the same phrase over several different
channels.  The use of all-caps can also be considered spam.  Only use
capitals to add emphasis to key words in a sentence.

Moving a large number of items into and out of a container in a crowded,
non-store room is considered spam.  Using multiple characters to chat the
same message at the same time is considered spam.  Making charmed mobs
or pets to cause screen scroll through movement or orders is considered
spam. ANYTHING that causes excessive or irritating screen scroll can be
considered spam.
]],
  },
  {  
    keywords = {"LAW STAKE"},
    level = -1,
    type = "rule",
    text = [[
&GThe first player to attack a mob has the rights to the kill.  Others should
not get involved without being requested to do so.  Those receiving aid are
under no obligation to reward their benefactors.  Monopolization of a mob and
its repops will not be tolerated.

Any disputes brought to the attention of an immortal for resolution will be
handled according the the immortal's discretion.  All such decisions are
final.
]],
  },
  {  
    keywords = {"LCK", "LUCK"},
    level = 1,
    type = "info",
    text = [[
Luck (LCK in your 'score') represents the tendency of a character to succeed
or prosper through chance or good fortune.  As in life, the exact extent of
this factor remains and will always remain shrouded in uncertainty...

Also as in life, however, it can be said with surety that its influence on a
character is pervasive.  Though it affects some aspects of life here in a
very direct manner, it can affect nearly every aspect to at least a degree.

]],
  },
  {  
    keywords = {"LEAP"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  leap

Leap is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"LETHARGY"},
    level = 1,
    type = "wizhelp",
    text = [[
Syntax:  c lethargy <victim>

Lethargy causes the victim to be less dexterous.
]],
  },
  {  
    keywords = {"LEVERFLAGS", "SWITCHFLAGS", "BUTTONFLAGS", "PULLCHAINFLAGS", "DIALFLAGS"},
    level = 52,
    type = "wizhelp",
    text = [[
FLAG NAME     |  BITVECTOR  |  DESCRIPTION
----------------------------------------------------------------------
UP            |          1  |  Trigger is UP
UNLOCK        |          2  |  Trigger unlocks something
LOCK          |          4  |  Trigger locks something
D_NORTH       |          8  |  Affects the north exit
D_SOUTH       |         16  |  Affects the south exit
D_EAST        |         32  |  Affects the east exit
D_WEST        |         64  |  Affects the west exit
D_UP          |        128  |  Affects the exit up
D_DOWN        |        256  |  Affects the exit down
DOOR          |        512  |  Affects a door
CONTAINER    *|       1024  |  Affects a container
OPEN          |       2048  |  Opens something
CLOSE         |       4096  |  Closes something
PASSAGE       |       8192  |  Creates a passage
OLOAD        *|      16384  |  Loads up an object
MLOAD        *|      32768  |  Loads up a mobile
TELEPORT      |      65536  |  Teleports the puller
TELEPORTALL  *|     131072  |  Teleports everyone in the room
TELEPORTPLUS *|     262144  |  Teleports everything in the room
DEATH        *|     524288  |  Causes instant death
CAST         *|    1048567  |  Casts a spell (sn in value1)
FAKEBLADE    *|    2097152  |  Lever is a wax covered sword blade (OUCH)
RAND4         |    4194304  |  Randomizes the exits N, S, E, W
RAND6         |    8388608  |  Randomizes the exits N, S, E, W, U, D
TRAPDOOR     *|   16777216  |  Opens a trap door, everthing falls down
                 
              * = not yet implemented.
]],
    see_also = {"OSET", "ITEMVALUES"},
  },
  {  
    keywords = {"LIGHT"},
    level = 1,
    type = "command",
    text = [[
Syntax:  light <pipe>

This lights the herb in your pipe.  Once lit, the herb will continue to
burn until it burns itself out, is smoked out, or you tamp your pipe.
]],
  },
  {  
    keywords = {"LIGHTNING BOLT"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'lightning bolt' (charname)

This spell hurls a devastating strike of lightning towards your enemy, zapping
them with the power of electricity.]],
  },
  {  
    keywords = {"LIMBO"},
    level = 1,
    type = "info",
    text = [[
The limitless void known as Limbo is a strange plane fabricated by
the Gods to hold mortals who have been rendered unconscious or have
been mortally wounded. It is a well known fact that only Gods may travel
here of their own volition.
]],
  },
  {  
    keywords = {"LIQUIDTYPES"},
    level = 52,
    type = "wizhelp",
    text = [[
Value | Liquid Type
------------------------------
  0   | water
  1   | beer
  2   | wine
  3   | ale
  4   | dark ale
  5   | whiskey
  6   | lemonade
  7   | firebreather
  8   | local specialty
  9   | slime mold juice
 10   | milk
 11   | tea
 12   | coffee
 13   | salt water
 14   | cola
]],
    see_also = {"OSET", "ITEMVALUES"},
  },
  {  
    keywords = {"LITTERBUG"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: litterbug <player>

Places/removes the litterbug flag, allowing/prohibiting a player from
dropping any objects.
]],
  },
  {  
    keywords = {"LIZARDMAN", "LIZARDMEN", "LIZARD-MAN", "LIZARD-MEN", "LIZARD MAN", "LIZARD MEN"},
    level = 1,
    type = "race",
    text = [[
Lizardmen are semi-aquatic, breathing air but often dwelling totally
underwater.  They are often noted to use underwater caves as their
lair, and are typically found in swamps, marshes, and similar places.
Members of this race band together in rough tribal form; they are
omnivores, and are likely to prefer human flesh to other foods.

This race, of course, has the innate ability to breath under water.
They get hungry and thirsty faster than other races.  Their scaly skin
helps shed the blows of slashing weapons.  They can swing their spiked
tail in combat.

Lizardmen get 110% of the normal experience award.

Lizardmen can be a Mage, Cleric, Thief, Warrior, Druid, Ranger, Diabolist
or Shaman.
]],
  },
  {  
    keywords = {"LOADUP"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax:  loadup <player>

LOADUP allows one to load up a player's character (playing or not), to do
whatever needs be done to the character.  (Modifying a flag, changing a
password... etc).  Use FORCE to make the character do your bidding.

If we make any changes to the char, we comment the char and place a note in
their inventory explaining who loaded them up and what changes were made.
The character is transed to room 99 and forced to quit there (unless they
are going to be left in hell).  If we don't make any changes to the char, we
trans them back from where they came and force quit them there.  Loadup is
used primarily when a player quits to avoid dealing with immortals or if
they quit before you finish writing a comment.  But it is also used to
investigate chars for duping and other allegations made against them.

So... there is actually a wide range of reasons to use loadup and you are
encouraged to use your discretion in this area.

If you load up a character to slay or purge them, you must post in 1205.
]],
    see_also = {"FORCE"},
  },
  {  
    keywords = {"LOCATE OBJECT"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'locate object' <name>

This spell reveals the location of all objects with the given name.

]],
  },
  {  
    keywords = {"LOCKER"},
    level = 1,
    type = "command",
    text = [[
Syntax: LOCKER OPENOLD
Syntax: LOCKER CLOSE

If you buy a house (see the Deed agent in Drazukville), you have the option of
installing a locker.  A locker is a storage area where you can put any items
except for containers, up to a 500 weight limit.  No other player or Immortal
can get to your locker...it's the safest place in the Realms to stash special
things!
]],
    see_also = {"PERSONAL LOCKERS"},
  },
  {  
    keywords = {"LOG", "SNOOP"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: log   <character>
Syntax: log   all
Syntax: snoop <character>

LOG <character> causes all of a character's commands to be logged into
the server's log file.  Like FREEZE, it is a permanent character toggle.

Certain commands (PASSWORD) are protected against LOG.  Conversely, certain
commands (especially immortal commands) are always logged.

LOG ALL logs all character commands.  It is a server-wide toggle; it does not
persist across reboots.

SNOOP shows you a copy of all the input and output going to a character.
The character must have an open channel.  You may snoop more than one
character at a time.
The input from the player will be displayed with a header of the players
name and a percentage sign (i.e. Mudder%)
SNOOP yourself to cancel all outstanding snoops.
-- Do not snoop people being intimate. <i.e. Mudsex, voyeurism, etc...>
-- Do not repeat information learned in snoop casually, especially to mortals
-- Only snoop a person talking to a higher level Immortal with the higher
   Immortals "Express Permission".
-- If a higher level Immortal begins communication with someone you are
     snooping, inform that higher Immortal immediately of the snoop.
-- Any incidental references learned in snoop should be disregarded
    ** For example, you hear someone is having a mud affair, it is not
    ** important to the reason you are snooping.  Do not judge or pass
    ** on information learned in this manner.
-- "Spot check" snooping of lower level Immortals is part of being a higher
   level immortal.  All Immortals may be snooped at any time, for any reason.
-- Do not snoop for the purpose of gaining information for personal reasons.
-- Being an Immortal is a privilege and a job.  Snoop is a tool to assist
   you do your job properly.  Snoop is neither a toy nor a right.

]],
  },
  {  
    keywords = {"LOYAL", "LOYALTY"},
    level = 1,
    type = "info",
    text = [[
The item flag 'loyal' reflects a weapon's loyal status to its deadly owner.
Such a weapon will return to a player's inventory when disarmed by another
deadly character.
]],
  },
  {  
    keywords = {"LUNGE"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  lunge

Lunge is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.]],
  },
  {  
    keywords = {"MAGIC MISSILE"},
    level = 1,
    type = "spell",
    text = [[
The first spell learned by new mages, magic missile is useful for their entire
career.  As the caster advances in skill level, more missiles are created for
each casting, resulting in more damage done.  This spell can be cast a little
quicker than others.
]],
  },
  {  
    keywords = {"MAGICTABLE", "EQUIPTABLE"},
    level = 0,
    type = "info",
    text = [[
Here's a handy table to see which classes can use which items...
A "*" means the class can use the object type.
A "-" means the class cannot use the object type.
A "#" (such as "10") means the class can use it if the level of the item is
lower than the number given.  For example, most classes can only use scrolls
if the scroll is lower than level 10 in power.

            2-Hand | Wands | Staves | Scrolls |
Mage      |    -   |   *   |    *   |    *    |
Cleric    |    *   |   -   |    *   |    *    |
Thief     |    -   |   *   |    -   |    10   |
Warrior   |    *   |   -   |    -   |    10   |
Thug      |    *   |   -   |    -   |    10   |
Druid     |    -   |   -   |    *   |    10   |
Ranger    |    *   |   -   |    -   |    10   |
Monk      |    -   |   -   |    -   |    10   |
Diabolist |    -   |   *   |    *   |    *    |
Conjurer  |    -   |   *   |    -   |    *    |
Jester    |    *   |   *   |    -   |    10   |
Shaman    |    *   |   -   |    -   |    *    |
Champion  |    *   |   -   |    -   |    10   |
Bishop    |    *   |   *   |    *   |    *    |
Rogue     |    *   |   *   |    -   |    10   |
Archmagi  |    -   |   *   |    *   |    *    |
]],
  },
  {  
    keywords = {"MAGICUSER", "MAGE", "MAGES"},
    level = 0,
    type = "class",
    text = [[
A mage is one of the weakest classes when it comes to body, but the mage
is a being of pure magic.  Their minds revolve around crafting spells that
damage others in combat and spells that protect them from the elements
and spells wielded against them.  Poor in physical combat, a mage that
is allowed to fire off a few spells will do some serious damage indeed.

Intelligence is a mages prime attribute, with wisdom the secondary.  Dexterity
is their tertiary skill.

The races of Human, Elf, Pixie, Half-elf, Half-troll, Gith, Sea-elf, Drow,
Gnome, Ghoul, Goblin, Wolfen, Minotaur and Lizardman are allowed to be mages.
]],
  },
  {  
    keywords = {"MAGNETIC THRUST"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'magnetic thrust' (victim)

'Magnetic Thrust,' much like 'Sonic Resonance,' allows the casting
Druid to control the nature of space and time in the immediate locale
of his victim.  In this sorcery, the Druid forms a wedge of magnetic
energy within the body of the victim.  As the spell progresses, the
victims organs are violently rent and internal tissues are torn.  The
resulting pain and damage are formidable, indeed.
]],
  },
  {  
    keywords = {"MAILING"},
    level = 0,
    type = "info",
    text = [[
There is no official mailing list.
 -> send a message to  :  xdarwinevolved@aim.com
if you need to contact him.
]],
  },
  {  
    keywords = {"MAJOR INVOCATION"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'major invocation'

The spell MAJOR INVOCATION lays upon the members of the casters group
a strong, but short-lived Sanctuary of The High Gods.
]],
  },
  {  
    keywords = {"MAKE"},
    level = 50,
    type = "command",
    text = [[
Syntax:  make <object>

For use by following leaders only to make one of the three following objects.
]],
    see_also = {"SETFOL"},
  },
  {  
    keywords = {"MAKEBOARD"},
    level = 61,
    type = "wizhelp",
    text = [[
Creates a new noteboard.
]],
  },
  {  
    keywords = {"MAKECOUNCIL"},
    level = 65,
    type = "wizhelp",
    text = [[
MAKECOUNCIL

     SYNTAX: makecouncil <council name>

DESCRIPTION: The MAKECOUNCIL command creates a new council
             that may then be customized with the SETCOUNCIL
             command.
]],
    see_also = {"SETCOUNCIL", "SHOWCOUNCIL"},
  },
  {  
    keywords = {"MAKEDEITY"},
    level = 65,
    type = "wizhelp",
    text = [[
&W     SYNTAX: makedeity <deity name>

DESCRIPTION: The MAKEDEITY command creates a new deity
             that may then be customized with the SETDEITY
             command.
]],
    see_also = {"SETDEITY", "SHOWDEITY", "DEITIES"},
  },
  {  
    keywords = {"MAKEFOL"},
    level = 61,
    type = "wizhelp",
    text = [[
MAKEFOL
&W-----------------------------------------------------------

     SYNTAX: makefol <following name>

DESCRIPTION: The MAKEFOL command is used to create a
             new following which may then
             be customized with the SETFOL command.
]],
  },
  {  
    keywords = {"MAKELOCKER"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: makelocer <player>

Used to setup a player with a locker.  Use this for people who buy houses.
]],
  },
  {  
    keywords = {"MAKEREPAIR"},
    level = 57,
    type = "wizhelp",
    text = [[
Syntax:  makerepair <mobvnum>

Automatically gives the mobile the ability to repair damaged equipment.
Use 'repairset' to set the parameters by which the shop will function.
]],
    see_also = {"REPAIRSET", "REPAIRSTAT", "REPAIRSHOPS"},
  },
  {  
    keywords = {"MAKESHOP"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: makeshop <mobile vnum>

Creates a new shop and assigns it to a mobile.

The levels of the items in the shop are picked randomly based on item type:

--------------------------------------------
|Item Type | Level Range                   |
--------------------------------------------
| default  | 0                             |
| pill     | 0 to 10                       |
| potion   | 0 to 10                       |
| scroll   | value[0] of the scroll object |
| wand     | 10 to 20                      |
| staff    | 15 to 25                      |
| armor    | 5 to 15                       |
| weapon   | 5 to 15                       |
--------------------------------------------
]],
    see_also = {"SHOPSTAT", "SHOPSET", "SHOPS"},
  },
  {  
    keywords = {"MAKESLAY"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: makeslay <type>

This command creates a new slaytype and sets it up with default options.
Once created, it can then be edited using the online slay editor.
]],
    see_also = {"DESTROYSLAY", "SETSLAY", "SHOWSLAY", "SLAY"},
  },
  {  
    keywords = {"MAKEWIZLIST"},
    level = 61,
    type = "wizhelp",
    text = [[
Refreshes the wizlist.  Not too useful unless a new god is created.]],
  },
  {  
    keywords = {"MANA"},
    level = 1,
    type = "command",
    text = [[
Mana is the living inner power used by spellcasters to cast their magic.
Non-spellcasters may use mana for some of their skills, representing the
energy they put into the skill.

Syntax: mana (spell)
        mana all
This command shows a list of how much mana a spell or skill will cost a
character at their current level.
]],
  },
  {  
    keywords = {"MAP", "DVILLEMAP"},
    level = 1,
    type = "info",
    text = [[
.
.                                Ga=te
.                        Trumpy St.|  Trumpy St.
.                       - - - - - - - - - - - -
.                      |        Sh-|-Co        |
.                      |           |<-Homer St.|
.                      |  Sturm St.| Tr         |
.       Sohcahtoa St.->|        Ut-|  V        |<-Argot St.
.                      |    - - - - - - - -    |
.                      |  S|  | Wg_|_Rg Mo-|A  |
.                      |  h|  Ta O_|_r Thg_|i  |
.                      |  y|       | Race @|r  |
.       Pendragon St.  |   | Q W   |/  A MT|w  | Pendragon St.
.            Gate ->  _|_ _ _|_|_ _T_ _|_|_ _ _|_ <- Gate
.                      |1-l| | | U/|   | | |a  |
.                      |2-o| B R M_|_C m FT|l  |
.                      |  k|    Tg_|_Dg    |k  |
.                      |   |       |       |   |
.                      |    - - - - - - - -    |
.       Sohcahtoa St.->|           |Scroll St. |<-Argot St.
.                      |        Di-|           |
.                      |       Jes-|-Art       |
.                      |           |           |
.                       - - - - - - - - - - - -
.                        Marley St.|  Marley St.
.                                Ga=te

Try HELP MAPLEGEND for map info.
]],
  },
  {  
    keywords = {"MAPLEGEND"},
    level = 1,
    type = "info",
    text = [[
Legend :
Wg - Warrior's Guild
Rg - Ranger's Guild
C  - Cleric's Guild
M  - Mage's Guild
Tg - Thieve's Guild
Dg - Druid's Guild
Thg- Thug's Guild
Di - Diabolists Guild
O  - Outdoor Outfitters
R  - Rogue/Sneaky Shop
W  - Weaponsmith
A  - Armorsmith
MT - Male Tailor
FT - Female Tailor
m  - Magic Shop
B  - Bank
@  - Portal
U  - University
r  - Real Estate Office
T  - Temple
Ta - Tavern
Mo - Monks Guild
1  - Repair Shop
2  - Recharge Shop
Art- Artificers Shop
Jes - Jesters Guild
Ut - Undertaker
Sh - Shaman's Guild
Co - Conjurer's Guild
Tr - Transportal Chamber (V means on the south side of the street)
]],
  },
  {  
    keywords = {"MAPOUT"},
    level = 65,
    type = "wizhelp",
    text = [[
Crazy mapping thing...check later.]],
  },
  {  
    keywords = {"MASTER"},
    level = 1,
    type = "skill",
    text = [[
Syntax: master

The style of a master monk, anyone using this style has mastered the arts of
offense and defense to an amazing level.  Awesome attacks, solid defense, the
ability to resist both magic and nonmagic, shrug off spells, and fly are all
parts of the master style.
]],
  },
  {  
    keywords = {"MCREATE", "OCREATE"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: mcreate <vnum> <keywords>
Syntax: ocreate <vnum> <keywords>

Create and new mobile / object.
A prototype monster or object will be created with the selected vnum, and
set up with the plainest of default values.  A material image of the magical
prototype will appear before you, for you to futher modify with MSET or OSET.

See MSET or OSET.
]],
  },
  {  
    keywords = {"MDELETE"},
    level = 65,
    type = "wizhelp",
    text = [[
Delete a mob.]],
  },
  {  
    keywords = {"MEDITATE", "MEDITATION"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  meditate

A character in possession of this skill may use it to briefly focus its
energies toward restoring a small burst of mana.

]],
  },
  {  
    keywords = {"MEMORY"},
    level = 57,
    type = "wizhelp",
    text = [[
Syntax: memory

MEMORY reports the current counts of objects, mobiles, affects, rooms,
areas, etc, etc.
]],
  },
  {  
    keywords = {"MEND"},
    level = 1,
    type = "skill",
    text = [[
Syntax: mend victim

Since they are used so much in combat, golems tend to get banged up
quite a bit.  Conjurers can repair their golems using the mend skill.
As conjurers gain more experience, their mend works better and better.
Mend can only be used on golems, and can't heal a character.
]],
  },
  {  
    keywords = {"MENTALSTATE", "MENTALSTATES", "MENTAL STATE", "MENTAL STATES"},
    level = -1,
    type = "info",
    text = [[
.
&gYour mental state is your current frame of mind, and how clearly and
realistically you view your surroundings.  Mental states can be affected
by prolonged combat, hunger, thirst, or poison.  If you are affected by
one of the above for a period of time, your mental state will begin to
deteriorate, and you will not view your surroundings as they truly are.
You may begin to hallucinate, or become too lethargic to function, and
your general abilities will be affected.  In extreme cases you may
collapse from exhaustion or enter a delirious coma.

To restore your mental state, you may need to rest (resting and sleeping
will speed your recovery), eat, cure whatever poison afflicts you, etc.
Note that if you are malnourished your state will &wont&g improve, even with
sleep, until you have fed and/or quenched your thirst.

Your mental state is by the text line in 'score' which describes your state
of mind (You feel great, etc.)  The 'group' display contains a less accurate
reading of your and your group-mates' mentalstates as well.
]],
    see_also = {"GROUP DISPLAY"},
  },
  {  
    keywords = {"MENU"},
    level = 53,
    type = "wizhelp",
    text = [[
When in one of the menu systems (RMENU, OMENU, MMENU), to switch from one
page to another, type '- <letter>'.  (For example, '- a' will bring you to
the first page in the current menu system).

'- h' will bring up a help file in any menu system.

'+ <name>' in OMENU or MMENU will change the object or mobile being edited
if it exists in your inventory/room respectively.
]],
    see_also = {"RMENU", "OMENU", "MMENU"},
  },
  {  
    keywords = {"MERC", "FUREY", "KHAN", "HATCHET"},
    level = -1,
    type = "info",
    text = [[
SMAUG was originally based on the Merc 2.1 code which was created by Furey,
Hatchet, and Kahn.
This original code base is available as Merc_21.tar.gz via FTP from:
ftp.tcp.com, ftp.math.okstate.edu and ftp.game.org.
E-mail to 'merc-request@kpc.com' to join the merc mailing list.

Merc would like to thank ...
  ... Diku Mud for their code base.
  ... The Free Software Foundation and DJ Delorie for kick-ass tools.
  ... Copper Mud and Alfa Mud for releasing their code and worlds.
  ... Aod of Generic for ... well, everything.  You're a hoopy frood, Aod.
  ... Alander for many ideas and contributions.
  ... John Brothers of Silly for permission to use Silly code and worlds.
  ... Zrin for administering the mailing list.
  ... Abaddon for proofreading our comm.c.
  ... Hind, Quin, Vic, Diavolo, Oleg, Trienne, and others for porting help.
  ... Diavolo, Grodyn, Morgenes, and others for code and bug fixes.
  ... Raff, Doctor, VampLestat, Nirrad, Tyrst, PinkF, Chris, Glop for worlds.
  ... the players and imps of Mud Dome, Final Mud, Mud Lite, Vego Mud, Rivers
      of Mud, Ruhr Mud, and Mystic Realms for bug reports, ideas, new code,
      and hours of enjoyment.
                                Share and enjoy.
]],
  },
  {  
    keywords = {"MFIND", "OFIND"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: mfind <name>
Syntax: ofind <name>

MFIND finds all mobile types with a particular name.

OFIND finds all object types with a particular name.
]],
  },
  {  
    keywords = {"MIDAS TOUCH", "MIDAS"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'midas touch' (object)

Turns an object in your inventory into gold.  This only works if the object
already has some sort of value.

]],
  },
  {  
    keywords = {"MINDFOG"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast mindfog (victim)

Created by the thief-mages of the Eastern shores, this spell not only makes
its victim lose intelligence, it also reduces their ability to resist most
other spells.
]],
  },
  {  
    keywords = {"MINOR INVOCATION"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast 'minor invocation'

This spell casts a bless spell among every character in the group.

]],
  },
  {  
    keywords = {"MINOTAUR", "MINOTAURS"},
    level = 0,
    type = "race",
    text = [[
Living in the islands far to the south of the Realm, Minotaurs are large,
bull-like humanoids.  Very strong and quick, they are also quite intelligent,
and can work magic spells as well as many other races.

They have the ability to see heat in the dark, and their thick skin can resist
the attacks of many different weapon types.  However, they have some type of
strange allergies to nonmagical weapons, which counters some of that
resistance.

Minotaurs get 90% of the normal experience bonus.

Minotaurs can only a Mage, Thief, Warrior, Thug, Druid, Ranger, Diabolist,
or Shaman.
]],
  },
  {  
    keywords = {"MINPOS"},
    level = 1,
    type = "info",
    text = [[
Minimum Positions affect both spells and skills. For example, if the minimum
position for a spell was 8, it would work while sitting, fighting or any
position higher than that. The same spell would not work in the resting
position as it's ranked at 6.
0 POS_DEAD
1 POS_MORTAL
2 POS_INCAP
3 POS_STUNNED
4 POS_SLEEPING
5 POS_BERSERK
6 POS_RESTING
7 POS_AGGRESSIVE
8 POS_SITTING
9 POS_FIGHTING
10 POS_DEFENSIVE
11 POS_EVASIVE
12 POS_STANDING
13 POS_MOUNTED
14 POS_SHOVE
15 POS_DRAG
]],
    see_also = {"STYLE"},
  },
  {  
    keywords = {"MINVOKE", "OINVOKE"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax:  minvoke <vnum>
         minvoke <keyword of mob>
Syntax:  oinvoke <vnum>
         oinvoke <keyword of obj>
         oinvoke <vnum/keyword of obj> <quantity>

MINVOKE invokes an instance of the mobile specified.

OINVOKE invokes an copy of the object specified.  It accepts an optional
parameter for the quantity of the object to be invoked.
]],
  },
  {  
    keywords = {"MISSILE WEAPONS"},
    level = 1,
    type = "skill",
    text = [[
This skill allows the user to utilize bows, crossbows, blowguns, and other
ranged weapons in combat more effectively.
]],
  },
  {  
    keywords = {"MISTFORM"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  mistform

The user may assume a form of lucent mist, capable of traveling
through many barriers otherwise unpassable.


]],
  },
  {  
    keywords = {"MISTWALK"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  mistwalk <victim>

The user may become a fine mist, capable of traveling with great speed
and precision through the smallest of cracks and crevices to to reach its
intended victim.

Due to the nature of this skill, it only works in darkest night (between
the hours of 9 o'clock in the night and 5 o'clock in the morning).

]],
  },
  {  
    keywords = {"MITHRIL BOLT"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'mithril bolt' victim

Sometimes a conjurer needs a little help in combat.  This spell allows them to
shoot a mithril bolt at their enemies, hitting them for a decent amount of
damage!  Mithril bolt requires one charge from a mithril cylinder to work.
]],
  },
  {  
    keywords = {"MIX"},
    level = 1,
    type = "command",
    text = [[
Syntax: mix <liquid1> <liquid2>

If you have two liquids that can mix into something else, then use the MIX
command to create that new mixture!  The mixture will end up in the container
of <liquid1>.  Warning!  Sometimes mixing two safe liquids can create
poisonous liquids!
]],
  },
  {  
    keywords = {"MLIST"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: mlist
      :	mlist <first mob>
      :	mlist <first mob> <last mob>

This command will list all of the prototype mobs in your area, when used
with no arguments.  When used with a single argument it will list all
mobs including and after the argument, and when used with two arguments,
it will list all mobs including and between the two.
]],
  },
  {  
    keywords = {"MMENU"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: mmenu <mob name> [menu page] (defaults to 'a' if none given)

Mmenu will bring you into a menu system of editing mobiles.  To use mmenu,
the mobile that you are editing should be in the same room as you.  To
choose an option in the menu, type the number of the section followed by the
desired letter, and any variables that may follow.

See MENU for generic menu commands.
]],
  },
  {  
    keywords = {"MOBM", "MOBMASTER", "MOBMASTERY"},
    level = 1,
    type = "command",
    text = [[
Syntax: mobmaster start
        mobmaster check
        mobmaster quit
        mobmaster start expert

A mob mastery is a quest of knowledge and might. When you start a mob mastery,
a randomly selected mob will be chosen. You must seek out and kill this mob.
You will be rewarded with glory points upon the slaying of your target mob. If
you fail to find and kill your selected mob, or you quit your quest, you will
have to wait out a time penalty before you can attempt another mob mastery
quest. The difficulty increases as you complete more mob masteries.

Once you have obtained 400 mob masteries, you can then choose to attempt an
expert mob mastery. The difficulty is greatly increased in this mode, however,
the reward is greater than normal mob masteries.
]],
  },
  {  
    keywords = {"MOBPROG", "MOBPROGRAMS", "OBJPROG", "ROOMPROG", "MUDPROG"},
    level = 51,
    type = "wizhelp",
    text = [[
.
         The MOBprograms have been contributed by N'Atas-ha.

         Haus hacked together room && obj programs 'cause
          he got sick of failing to add lever bitvectors,
               and cause he thought Carnage was a
                  Trancendentally Cool Mud.
]],
  },
  {  
    keywords = {"MOBTRIGGERS", "MUDTRIGGERS", "MPTRIGGERS"},
    level = 51,
    type = "wizhelp",
    text = [[
Trigger Optnl Triggering Variable Explanation
------- ----- ------------------- -----------
Act      {p}  <keyword / phrase>  [emotes, socials, actions, bamfs]
Speech   {p}  <keyword / phrase>  [says or tells from same room as mob]
Rand          <percentage>        [randomly triggered based on percentile]
Fight         <percentage>        [random, within a fight, based on percentile]
Hitprcnt      <percentage>        [percent is % of mob's max H.P.]
Greet         <percentage>        [entry that mob can see, by mob/player]
Allgreet      <percentage>        [entry by a mob/player, regardless if seen]
Entry         <percentage>        [when the mob itself enters a room]
Bribe         <amount of gold>    [when a player gives the mob money]
Death         <percentage>        [when the mob dies]
Script {hour}                     [loops a line at a time. Hour triggers start]
Time          <hour>              [script prog, runs once on hour specified]
Hour          <hour>              [loops as Script for an hour from start hour]

*NOTE* {hour}/<hour> is in military time. ie, 15 hours is 3p.m. mud time.
*NOTE* The mpcommand MPDONOTHING currently only works in Script progs,
       NOT in Time or Hour progs.
]],
    see_also = {"MPSTAT", "MPEDIT", "TRIGGER", "MPCOMMANDS", "IFCHECKS", "VARIABLES"},
  },
  {  
    keywords = {"MONK", "MONKS"},
    level = 0,
    type = "class",
    text = [[
The monks of the realms are powerful figures.  Studying the arts of pure
offense and pure defense, monks become masters of various combat styles, each
one more deadly than the last.  Eventually, monks become true masters of
combat, and can dance circles around their enemies.  Strong with powers of
meditation, they can also focus their own will into power that flows
throughout their bodies.  Monks take quite a long time to learn new skills.
Monks can only use talonous or pugilism weapons, even if they learn other
weapons skills.

Monks need to pull on their spiritual energy to use their skills, yet don't
gain any when they level.  This requires them to search out magic items that
they can draw upon in order to maximize their strengths.

Dexterity is a monks prime attribute, with constitution the secondary.
Strength is their tertiary statistic.

The races of Human, Elf, Half-elf, Gith, Sea-elf, Drow and Ghoul are allowed
to be monks.
]],
  },
  {  
    keywords = {"MORALE"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast morale

This spell grants moderate healing to everyone in the group.  While it can't
be cast during a battle, it is useful to ensure the entire group is healed up
and ready to go before entering combat.
]],
  },
  {  
    keywords = {"MORPH", "UNMORPH"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax:  morph <vnum> <target>
Syntax:  unmorph

Morph is an immortal command used to morph into various
things, while unmorph reverts the effect.

See also:  polymorph, morphcreate, morphdestroy, morphstat
]],
  },
  {  
    keywords = {"MORPHCREATE", "MORPHDESTROY"},
    level = 51,
    type = "wizhelp",
    text = [[
These commands are used for the creation or deletion of
polymorph data.

See also:  polymorph, morph, morphstat
]],
  },
  {  
    keywords = {"MORPHSTAT"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax:  morphstat <vnum|name> [help|desc]

Stats a morphed target by name or vnum.

See also:  polymorph, morphcreate, morphdestroy, morph
]],
  },
  {  
    keywords = {"MORTALITY"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: mortality Lvl (broadcast)

This command allows a God to assume a mortal form.  The broadcast flag is
optional for those Gods over level 60.  Gods less than 60 or those using the
broadcast flag announce their transition to the whole realm upon doing so.
Use the same command with your Immortal level to return to the heavens.
]],
  },
  {  
    keywords = {"MORTALIZE"},
    level = 65,
    type = "wizhelp",
    text = [[
Drop someone back down to mortal range.  Wipes out Immortal data.]],
  },
  {  
    keywords = {"MOUNT", "DISMOUNT"},
    level = 0,
    type = "skill",
    text = [[
Syntax: mount <mob>
Syntax: dismount

Mount is a skill, which allows you to mount certain mobs.  Being mounted
on a mob cuts down on movement points that are used whenever you move.

New water sectors allow a person mounted to traverse them without damage
from drowning.  If you are in an area where your movement points begin
to drop suddenly and/or you begin to lose hps <hitpoints> quickly, you
should try to mount immediately.
]],
  },
  {  
    keywords = {"MOVE", "MOVEMENT"},
    level = 1,
    type = "info",
    text = [[
This discusses the process of moving your character from one place in the
Realms to another.  The common movements are north, east, south, west, up
down, northeast, southeast, southwest, and northwest.  You may also move
in these directions by the use of n, e, s, w, u, d, ne, se, sw, and nw.
If you need to pass through a door, at times they require being unlocked
and opened. To unlock a door, you type UNLOCK <direction or door name>.
To open a door, you type OPEN <direction or door name>.

At times, you may run out of movement points or require healing.  To allow
for faster recovery, you may SIT, REST, or SLEEP.  When are finished with
your recovery, and wish to continue adventuring, type WAKE or STAND.

For more detailed information on movement and doors, read sections 7 and
8 of your Adventurer's Guide book.
]],
  },
  {  
    keywords = {"MPADVANCE"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPADVANCE <name> <level>

Advances the level of a player (not functional in prototype programs).
]],
  },
  {  
    keywords = {"MPAPPLY", "MPAPPLYB"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax:  mpapply <victim>
Syntax:  mpapplyb <victim>

These commands are used in the pre-auth area to signal a new character's
authorization status.  When a character first enters the game, it will
be targeted by an 'mpapply <victim>' which will inform the immortals that
the character is waiting for authorization.  Once the character is
authorized, a mob will attempt to 'mapplyb <victim>' the character, and
the character will be sent into the actual game.

]],
  },
  {  
    keywords = {"MPASOUND"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPASOUND <phrase>

Displays a phrase to all surrounding rooms.
]],
  },
  {  
    keywords = {"MPAT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPAT <vnum> <command>

Lets the mobile perform a command at another location.
]],
  },
  {  
    keywords = {"MPBODYBAG", "MPNUISANCE", "MPUNNUISANCE", "MPMSET", "MPOSET", "MPLOG", "MPUNMORPH", "MPMORPH", "MPASUPRESS"},
    level = 55,
    type = "wizhelp",
    text = [[
Mob Prog stuff.]],
  },
  {  
    keywords = {"MPCOMMANDS", "RPCOMMANDS", "OPCOMMANDS"},
    level = 53,
    type = "wizhelp",
    text = [[
The following commands can be used for Room, Mob and Object progs.  The
commands listed at the bottom are for mob progs only.  Each command also
has its own help file.  Type HELP <COMMAND>.

MPCOMMAND       PARAMETERS            MPCOMMAND      PARAMETERS
--------------  --------------------  -------------  --------------------
MPASOUND        <phrase>              MPJUNK         <name/var>
MPECHOAROUND    <name/var> <phrase>   MPECHOAT       <name/var> <phrase>
MPECHO          <phrase>              MPMLOAD        <mob vnum>
MPOLOAD         <object vnum>         MPPURGE        <object/mobile name>
MPADVANCE       <player name> <level> MPTRANSFER     <name/all>
MPFORCE         <name/all> <actions>  MPSLAY         <victim>
MPDREAM         <name> <phrase>       MPDAMAGE       <name> <#hps>
MPCLOSEPASSAGE  <room> <direction>    MPOPENPASSAGE  <origin> <dest> <dir>
MPPRACTICE      <victim> (skill|spell) (max_percent)
MPFAVOR         <victim> <favor>

Mobs only:
MPKILL           <name>                 MPGOTO <vnum>
MPAT             <vnum> <command>
]],
    see_also = {"MPSTAT", "RPSTAT", "OPSTAT", "MPEDIT", "RPEDIT", "OPEDIT", "TRIGGER", "MPTRIGGERS",
                "RPTRIGGERS", "OPTRIGGERS", "IFCHECKS", "VARIABLES"},
  },
  {  
    keywords = {"MPDAMAGE"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax:  mpdamage <victim> <amount>

This command inflicts a specified amount of damage on the victim.
This damage will be affected by sanctuary, but is not affected by
protect, saving throws or resists.

A mob should _never_ mpdamage itself.
]],
  },
  {  
    keywords = {"MPDELAY"},
    level = 65,
    type = "wizhelp",
    text = [[
Mob program supposed to delay for a bit of time :/]],
  },
  {  
    keywords = {"MPDEPOSIT", "MPWITHDRAW"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax:  mpdeposit <amount>
Syntax:  mpwithdraw <amount>

This command orders the mobile to deposit or withdraw a specified number
of gold coins from an area.  These can be used in conjunction with mpat
to tell the mob which area to withdraw/deposit money in.

Example:  mpat 21000 mpwithdraw 5000000

This would cause the mob to withdraw 5 million coins from the new Darkhaven
area, as that is the area vnum 21000 is in.

If no mpat is used, the mob will withdraw or deposit the gold from the
area in which it is located at the time.
]],
  },
  {  
    keywords = {"MPDREAM"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPDREAM <name> <phrase>
Sends a message to a sleeping character.
]],
  },
  {  
    keywords = {"MPECHO", "MPE"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPECHO <phrase>

Displays a phrase to the entire room.
]],
  },
  {  
    keywords = {"MPECHOAROUND", "MER"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPECHOAROUND <name> <phrase>

Displays a phrase to all in the room except victim.
The abbreviation "mer" may be used for mpechoaround.
]],
  },
  {  
    keywords = {"MPECHOAT", "MEA"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPECHOAT <name> <phrase>

Displays a phrase to only the victim.
The abbreviation "mea" may be used for mpechoat.
]],
  },
  {  
    keywords = {"MPECHOZONE", "MEZ"},
    level = 51,
    type = "wizhelp",
    text = [[
&W     SYNTAX: mpechozone <color> <string>

DESCRIPTION: The MPECHOZONE mpcommand works much like
             the ECHO and RECHO commands do except the
             specified string is only displayed within
             the area.
]],
    see_also = {"COLOR", "MPCOMMANDS"},
  },
  {  
    keywords = {"MPEDIT"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax:  mpedit <mobile> <command> [number]  [program] [arguments]
Syntax:  mpedit <mobile> add       <program> <arguments>
Syntax:  mpedit <mobile> insert    <number>  <program> <arguments>
Syntax:  mpedit <mobile> edit      <number>  [program] [arguments]
Syntax:  mpedit <mobile> delete    <number>
Syntax:  mpedit <mobile> list

Add, insert and edit will put you into the line editor to edit your
program.  The arguments consist of a trigger, plus any arguments
associated with that trigger.
]],
    see_also = {"MPSTAT", "TRIGGER", "MPTRIGGERS", "MPCOMMANDS", "IFCHECKS", "IFCHECKS2", "VARIABLES"},
  },
  {  
    keywords = {"MPFAVOR"},
    level = 51,
    type = "wizhelp",
    text = [[
&W     SYNTAX: mpfavor <target> -#
             mpfavor <target> +#
             mpfavor <target> #

DESCRIPTION: The MPFAVOR mpcommand is used to take, give,
             or set a PCs favor by/to the specified amount.

   EXAMPLES:

mpfavor 0.$n -10 -> decrease $n's favor by 10
mpfavor 0.$n +10 -> increase $n's favor by 10
mpfavor 0.$n 10  -> set $n's favor to 10

       NOTE: The current high/low settings for favor
             can not be exceeded: 2500 and -2500
]],
    see_also = {"IFCHECK FAVOR"},
  },
  {  
    keywords = {"MPFILLIN"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: mpfillin <exit>

New mpfillin, this simply sets a closed door bit, so can be used for
several things, quietly closing a door, closing an exit that was dug, etc...
]],
  },
  {  
    keywords = {"MPFIND"},
    level = 65,
    type = "wizhelp",
    text = [[
.  Display a maximum of n lines.

mpfind n mud text
   Search all the mobs in the mud for
   mob progs that contain an occurrence of text.
   Display a maximum of n lines.

Example:
mpfind 20 901 969 if isnpc
  Search all mob progs in Olympus (vnums 901 thru 969)
  and display all mob vnums that contain text "if isnpc".
  Display a maximum of 20 lines.
Example:
mpfind 100 mud mpslay
  Search all mob pros in the entire mud
  and display all mob vnums containing text "mpslay".
  Display a maximum of 100 lines.
]],
  },
  {  
    keywords = {"MPFORCE"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPFORCE <name/all>

Forces a player/mob to do a command (non-functional on immortals, all will
only force all in room).
]],
  },
  {  
    keywords = {"MPGOTO"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPGOTO <vnum>

Goes to any room which is not private.
]],
  },
  {  
    keywords = {"MPINVIS"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax:  mpinvis
Syntax:  mpinvis <level>

This command controls a mob's ability to use a modified form of wizinvis.

Use 'mpinvis' alone to toggle the invisibility.

Use 'mpinvis <level>' to set the level at which the mob will be invis.

Mortals under the mobinvis level of the mob will be unable to see the mob
when it goes mobinvis; they cannot see it with any spell, it will be
completely invisible to them.

Be warned, however, that its programs will still function as normal, the
mortal will simply see a 'someone' if it performs an action or an echo
that they see, just as if a wizinvis immortal performed the action.

Also be warned that at the present time, area attacks _will_ hit a mobinvis
creature even if it is invisible.
]],
  },
  {  
    keywords = {"MPJUNK"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPJUNK <name>

Destroys an object in inventory/being worn - can be used with all.object .
]],
  },
  {  
    keywords = {"MPKILL"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPKILL <name>

Kills a player without using murder.
]],
  },
  {  
    keywords = {"MPMLOAD", "MPOLOAD"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPMLOAD <vnum>
        MPOLOAD <vnum> <level> <timer>

Loads a mob or object. In the case of objects, the level must be set, or
supermob will end up setting the level. Timer is optional, and is the decay
timer for objects.
]],
  },
  {  
    keywords = {"MPNOTHING"},
    level = 65,
    type = "wizhelp",
    text = [[
Does Nothing
]],
  },
  {  
    keywords = {"MPOPENPASSAGE", "MPCLOSEPASSAGE"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPOPENPASSAGE <origin> <destination> <direction>

Opens a passage to a room (does not affect pre-existing doors)

Syntax: MPCLOSEPASSAGE <room> <direction>

Closes a passage to a room (does not affect pre-existing doors that were
not created with mpopenpassage)
]],
  },
  {  
    keywords = {"MPPARDON"},
    level = 51,
    type = "info",
    text = [[
&W     SYNTAX: mppardon <target> <flag>

DESCRIPTION: The MPPARDON mpcommand works just as the
             immortal PARDON command does.
]],
    see_also = {"PARDON", "FLAGS", "IFCHECK ISATTACKER", "IFCHECK ISKILLER", "IFCHECK ISTHEIF"},
  },
  {  
    keywords = {"MPPEACE"},
    level = 51,
    type = "wizhelp",
    text = [[
&W     SYNTAX:     MPPEACE <name>

DESCRIPTION:     Any target name within the room can be forced
                 to cease all fighting.

*-------------------------------------------------------------------*
See Also:  MPCOMMANDS OPCOMMANDS RPCOMMANDS OPTRIGGERS MPTRIGGERS
]],
  },
  {  
    keywords = {"MPPKSET"},
    level = 51,
    type = "wizhelp",
    text = [[
&W     SYNTAX: mppkset <target> yes/no

DESCRIPTION: The MPPKSET mpcommand will set the
             PC to deadly or peaceful based on what is
             specified regardless of their present state.
             No = peaceful Yes = deadly
]],
  },
  {  
    keywords = {"MPPRACTICE"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax:  mppractice <victim> <skill/spell/language> <amount>

This command will set the victim's percentage of proficiency in the
specified skill/spell/language to the specified amount.

It cannot train a character in a skill/spell/language the character does
not have as a part of its class and that it does not already have as a
result of its level.  In other words, it cannot train a warrior in
fireball, or a level 1 thief in gouge.
]],
  },
  {  
    keywords = {"MPPURGE"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: MPPURGE <object/mobile>

Purges the room, or a specified object/mobile.
-----------------------------------------------------------

     SYNTAX: mppurge
             mppurge <item name>
             mppurge <mob name>

DESCRIPTION: The MPPURGE mpcommand works much like the
             immortal command PURGE, but for one exception:
             there must be something to purge. If there is
             nothing to be purged, the command will log a bug.
]],
  },
  {  
    keywords = {"MPRESTORE"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax:  mprestore <victim> <amount>

This command restores a specified number of hitpoints to the victim.
]],
  },
  {  
    keywords = {"MPSCATTER"},
    level = 51,
    type = "wizhelp",
    text = [[
&W     SYNTAX:     MPSCATTER <target name> <low vnum> <hi vnum>

DESCRIPTION:     This command will send the victim to any one of
                 the rooms specified at random.

Example: mpscatter lascivias 1 50
         Will transfer Lascivias to a room between 1 and 50.
         The numbers you specify are inclusive in the formula.
]],
    see_also = {"MPCOMMANDS", "OPCOMMANDS", "RPCOMMANDS", "OPTRIGGERS", "MPTRIGGERS"},
  },
  {  
    keywords = {"MPSLAY"},
    level = 51,
    type = "wizhelp",
    text = [[
&W     SYNTAX: mpslay <target>

DESCRIPTION: The mpcommand MPSLAY works exactly as the
             immortal slay command does, causing the
             PC/NPC target instant death. NOTE: This is
             a mob program command only.
]],
    see_also = {"MPCOMMANDS"},
  },
  {  
    keywords = {"MPSTAT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax:  mpstat <mob/mobvnum>

Mpstat will display all of the mobprograms that have been written for the
specified mob.  If an instance of that mob exists in the game, it can be
accessed with its vnum.
]],
    see_also = {"MPEDIT", "TRIGGER", "MPTRIGGERS", "MPCOMMANDS", "IFCHECKS", "IFCHECKS2", "VARIABLES"},
  },
  {  
    keywords = {"MPTD"},
    level = 58,
    type = "wizhelp",
    text = [[
]],
  },
  {  
    keywords = {"MPTRANSFER"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: MPTRANSFER <name/all>

Transfers one or all in the room to a specified location.
]],
  },
  {  
    keywords = {"MRANGE"},
    level = 65,
    type = "wizhelp",
    text = [[
?
]],
  },
  {  
    keywords = {"MSET"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: mset <character> <field> <value>
        mset character on

MSET sets the properties of mobiles. If a mobile has the PROTOTYPE flag,
modifying an instance of this mobile will also modify the index mobile, which
all other instances of the mobile are based on.

MSET ON will lock you onto a particular mob/character. Once locked on, all
mset commands will imply 'mset <character>'. Hitting enter while in MSET ON
will give you an mstat of the mob/character you are working on. To get out
of MSET ON, simply type the word DONE. Example:

        mset gracca on
        long A large hulking figure stands here.
        sex 1
        done
]],
    see_also = {"ACTFLAGS", "SPECFUNCS", "SAVINGTHROWS", "RIS", "NPC_RACES", "ATTACKS",
                "DEFENSES", "MCREATE", "MMENU", "MSTAT"},
  },
  {  
    keywords = {"MSETPKILL"},
    level = 54,
    type = "wizhelp",
    text = [[
mset <target> pkill

Before msetting a player to pkill, ensure the following conditions are met:

Player has read HELP DEADLY and LAWS PKILL
Player understands he/she/it may not return to the peaceful side
Player is config -nice
Player is in an area appropriate for pkill.
]],
  },
  {  
    keywords = {"MSTAT", "OSTAT", "RSTAT"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax:  mstat <character/mob or mobvnum>
Syntax:  ostat <object/object vnum>
Syntax:  rstat
Syntax:  rstat <location>

MSTAT shows you statistics on a character or mobile.  If a copy of the mobile
is present in the game, you can access it using its vnum.

OSTAT shows you statistics on an object.  If a copy of the object is present
in the game, you can acces it using its vnum.

RSTAT shows you statistics on a location.  The location may be specified as
a roomvnum, as the name of a mobile, or as the name of an object.  Rstat
with no argument returns the statistics on your present room.
]],
    see_also = {"MSET", "OSET", "REDIT"},
  },
  {  
    keywords = {"MUDMAIL", "MAIL"},
    level = 0,
    type = "command",
    text = [[
Syntax: mail list
Syntax: mail read    <number>
Syntax: mail read    all
Syntax: mail write
Syntax: mail subject <string>
Syntax: mail to      <to-list>
Syntax: mail take    <number>
Syntax: mail show
Syntax: mail post
Syntax: mail remove  <number>

The mail command is very similar to the note command.  To write mail, as
in notes, you must have a blank note held in your hands, and a quill or
pen in your inventory.  Mail can only be addressed to real players, or
'all'.  There is a charge for reading and taking mail.

To post mail to more than one party, use 'note to <name> <name> <name>', etc.
Note that any of the named parties can remove the mail before the other
parties get a chance to read it.
]],
    see_also = {"HELP BOARDS", "HELP NOTE"},
  },
  {  
    keywords = {"MUSE"},
    level = 55,
    type = "wizhelp",
    text = [[
A "muse" channel to muse on for level 55 and up...
]],
  },
  {  
    keywords = {"MWHERE"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: mwhere <name>

MWHERE shows you the locations of all mobiles with a particular name.
]],
  },
  {  
    keywords = {"NATURES COMPANION"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast 'natures companion'

Rangers have the ability to call forth a companion to help them in their
travels.  They must be in a natural setting...there are not too many wild
beasts in the cities, unless you count some of the drinkers at the ol Tickler!
The power of the beast grows as the ranger grows in power.  While at first
only a small hawk will heed the call, as the rangers skill advances, a wolf, a
panther, and then a mighty bear will come to their assistance.
]],
  },
  {  
    keywords = {"NECROMANTIC TOUCH"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c 'necromantic touch' <victim>

This spell drains hitpoints from the victim and returns some to the caster.
]],
  },
  {  
    keywords = {"NEW", "NEWBIE", "START", "BEGIN"},
    level = 1,
    type = "info",
    text = [[
If you are new to the Realms, here are a few help files that will help you
get acquainted with our world.

GUIDE -       Will help you learn to use your Adventurers Guide Book.
RULES -       Will lead you through the laws of the land.
SPAM -        Will explain what spam is, and why you should not do it.
CONFIG -      Will teach you about our configuration menu.
SCORE -       Will tell you about your character's personal score sheet.
MOVEMENT -    Will teach you various commands for moving about the Realms.
OBJECTS -     Will teach you various commands to use your equipment.
CONTAINER -   Will teach you about using containers to hold belongings.
CHANNELS -    Will teach you about communication with other players.
GROUP -       Will help you with grouping with other adventurers.
COMBAT -      Will teach you how to choose, start and stop a fight.
DEATH -       Will tell you about the death experience in the Realms.
PRACTICE -    Will teach you about training spells, skills, and weapons.
INFORMATION - Will cover ways to find certain types of information.

To use these files, type HELP topic.  Type 'help' for general commands.
]],
  },
  {  
    keywords = {"NEWBIECHAT"},
    level = 1,
    type = "command",
    text = [[
Newbiechat is a channel created for and use by only low-level new
players.  It is designed to lessen the confusion of their transition
into the Realms, and can be used to gain answers to any questions
or problems the player may have.
]],
  },
  {  
    keywords = {"NEWBIESET"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: newbieset <character>

NEWBIESET puts the default (i.e. Drazukville University) equipment into the
character's inventory.  Recipient must be level 5 or lower.
]],
  },
  {  
    keywords = {"NEWPASSWORD"},
    level = 65,
    type = "wizhelp",
    text = [[
Sets a new password on a character.  Use with caution!
]],
  },
  {  
    keywords = {"NEWSCORE"},
    level = 1,
    type = "command",
    text = [[
Does the same thing as "score" now (:]],
  },
  {  
    keywords = {"NEWZONES"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: newzones [low] [high]
Lists the vnum range for rooms/mobs/objects in prototype areas that have been
loaded.
]],
  },
  {  
    keywords = {"NEW_DEATH"},
    level = -1,
    type = "info",
    text = [[
...Everything begins to fade to black.  You feel yourself leaving your body.
Rising up into the air, you feel more free than you have ever felt before...

However, before your deity comes to collect your soul, you feel a strange
pulling sensation as strange and colorful mists swirl around you...

&CA low voice fills your head with words of advice...
"When your character dies, you are reincarnated at the altar in the Temple of
Drazuk in Drazukville; should you one day become a member of a
clan, guild or order you will be returned to your own altar."

"Your corpse, however, is left behind where you were killed, together with
 all of your equipment, so that you can attempt to return to the scene and
 loot your corpse.  Your gold stays with you.  Corpses decay after time,
 and when this happens the objects inside will decay with it."

"Once you have chosen a deity and gained sufficient favor, you may be able
 to supplicate to your deity for your corpse.  Type '&Whelp death&C' for more
 information.  This message will appear only on your first two deaths..."
]],
  },
  {  
    keywords = {"NMOTD"},
    level = -1,
    type = "info",
    text = [[
Greetings New Adventurer!

You are about to embark upon a grand adventure in the realms of HoG!  Here's a
few pointers to help you get started with things...

1. Typing "command" will give you a list of all the commands available in the
game.  There should be a corresponding Help file for each command, which you
can read by type "help (commandname)".

2. Other players can help answer many questions about things specific to House
of Ghouls.  Feel free to ask questions!  Most players are quite friendly and
are glad to help out.

3. Be prepared for setbacks.  At some point you will probably die.  Death
here results in your corpse being left behind at the point you died with all
your equipment on it (except in special cases).  Once you reach a certain
level, you will also lose some experience points, but you can never lose a
level this way.

4. Have fun!  HoG is a game, and we hope you have a good time exploring the
various areas.  If you have any suggestions to make things more enjoyable, let
an Immortal know (type "who", they show up underneath the list of Mortals).
]],
  },
  {  
    keywords = {"NOHELPS"},
    level = 51,
    type = "wizhelp",
    text = [[
A handy tool for finding things that don't have affiliated help files.
]],
  },
  {  
    keywords = {"NORESOLVE"},
    level = 65,
    type = "wizhelp",
    text = [[
Turn off or on name resolving.  Its disabled by default.
]],
  },
  {  
    keywords = {"NORTH", "SOUTH", "EAST", "WEST", "UP", "DOWN", "N", "S", "E", "W", "U", "D"},
    level = 1,
    type = "command",
    text = [[
Syntax: north or n
Syntax: south or s
Syntax: east or e
Syntax: west or w
Syntax: up or u
Syntax: down or d

Use these commands to walk in a particular direction.
]],
  },
  {  
    keywords = {"NORTHEAST", "NORTHWEST", "SOUTHEAST", "SOUTHWEST", "NE", "NW", "SE", "SW"},
    level = 1,
    type = "command",
    text = [[
Syntax: northeast or ne
Syntax: northwest or nw
Syntax: southeast or se
Syntax: southwest or sw

Use these commands to walk in a particular direction.
]],
  },
  {  
    keywords = {"NOSTRUM"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c nostrum

A restorative spell of the Druid which heals the caster of wounds.
The spell cannot be cast on others.

]],
  },
  {  
    keywords = {"NOSUPPLICATE", "NOSUPP"},
    level = 55,
    type = "wizhelp",
    text = [[
Nosupplicate as a room flag is only for use in hell, jails and some immortal
rooms. It should never be used in an area without fair warning given to mortals
and after extensive consideration and approval by the Area council.
]],
  },
  {  
    keywords = {"NOTE", "NOTES"},
    level = 1,
    type = "command",
    text = [[
USAGE - 'note (command) [number or text]'
   (command) can be any of the following:
    List, Read, Write, Subject, To, Show, Post, Remove, Take, Date.
   [number or text] can be left blank, be a number, or be words
    depending on what (command) you use.  Usage is explained below.

LIST - Lists the notes you can read. List [number] lists all the notes
 including, and after [number]. You must be at a note board to List.
 example: 'note list'    shows all notes on the board.
          'note list 10' shows notes 10 and later on the board.

READ - Displays the contents of [number]. You must be at a note board to
 Read, and you must specify a [number].
 example: 'note read 5' displays note #5.

WRITE - Puts you in an editor where you can write a note. You must be
 holding a note, and have a quill in your inventory to Write.
 example: 'note write' puts you in the editor. See Help EDITOR.
]],
    see_also = {"Note2"},
  },
  {  
    keywords = {"NOTE2"},
    level = 1,
    type = "info",
    text = [[
SUBJECT - Sets the subject line of a new note to [text]. You must be
 holding a note, and have a quill in your inventory to set the Subject.
 example: 'note subject Hello World!' sets Hello World! as the subject.

TO - Sets the recipient(s) to [text]. ALL means all players. IMMORTAL
 means all immortals. You must be holding a note, and have a quill.
 example: 'note to Harakiem' sets Harakiem as the note's recipient.

SHOW - displays a note you are holding.
 example: 'note show' displays the note you're holding.

POST - takes a note you're holding and posts it to the board you are at,
 so others may read it.
 example: 'note post' puts it on the board.

REMOVE - erases note [number] from a note board. You must be at a note
 board and be the note's author or an immortal to use Remove.
 example: 'note remove 12' removes note #12, if you're its author.

TAKE - similar to 'Remove' but places the note in your inventory, rather
 than completely erasing it.
 example: 'note take 10' moves note 10 to your inventory from the board.

DATE - similar to 'list' but replaces who the message is to with the
 date that the note was written.
]],
    see_also = {"note"},
  },
  {  
    keywords = {"NOTELL", "NOEMOTE", "NOTITLE", "SILENCE", "UNSILENCE"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: notitle <character>
Syntax: noemote <character>
Syntax: notell  <character>
Syntax: silence <character>
Syntax: unsilence <character>

NOTITLE, NOEMOTE, NOTELL, and SILENCE are used to muffle other characters, by
preventing them from setting their title, emoting, telling, and using
channels, respectively.  Characters who are notelled will also not receive
those forms of communication.

Use UNSILENCE to remove a player's silence.  Simple use notell, noemote or
notitle on the character again to remove each of those restrictions.
]],
  },
  {  
    keywords = {"NPCCLASSES"},
    level = 53,
    type = "wizhelp",
    text = [[
CLASS #      CLASS              CLASS #      CLASS
-------      -----              -------      -----
  0          MAGE                 7          Blank
  1          CLERIC               20         BAKER
  2          THIEF                21         BUTCHER
  3          WARRIOR              22         BLACKSMITH
  4          THUG                 23         MAYOR
  5          DRUID                24         KING
  6          RANGER               25         QUEEN
]],
    see_also = {"ACTFLAGS", "SPECFUNCS", "BODYPARTS", "SAVINGTHROWS", "RIS", "NPCRACES",
                "ATTACKS", "LANGUAGES", "DEFENSES", "MSTAT", "MCREATE", "MMENU"},
  },
  {  
    keywords = {"NPCRACES", "NPC_RACES"},
    level = 53,
    type = "wizhelp",
    text = [[
A mobile may be any of the following races:

human         elf         dwarf        halfling     pixie        vampire
half-ogre     half-orc    half-troll   half-elf     gith         ant
ape           baboon      bat          bear         bee          beetle
boar          bugbear     cat          dog          dragon       ferret
fly           gargoyle    gelatin      ghoul        gnoll        gnome
goblin        golem       gorgon       harpy        hobgoblin    kobold
lizardman     locust      lycanthrope  minotaur     mold         mule
neanderthal   ooze        orc          rat          rustmonster  shadow
shapeshifter  shrew       shrieker     skeleton     slime        snake
spider        stirge      thoul        troglodyte   undead       wight
wolf          worm        zombie       bovine       canine       feline
porcine       mammal      rodent       avis         reptile      amphibian
fish          crustacean  insect       spirit       magical      horse
animal        humanoid    monster      god
]],
    see_also = {"ACTFLAGS", "SPECFUNCS", "BODYPARTS", "SAVINGTHROWS", "RIS", "NPCCLASSES",
                "ATTACKS", "LANGUAGES", "DEFENSES", "MSTAT", "MCREATE", "MMENU"},
  },
  {  
    keywords = {"NUISANCE STAGES"},
    level = 54,
    type = "wizhelp",
    text = [[
Stages of nuisances are the affects that the victim picks up while in
that stage.  As time progresses and the victim progresses through the
stages, they pick up new problems and the old ones gradually strengthen.
So for example if they are in stage 3 and progress to stage 4.  They
will feel more affects from stage 1,2 and 3 and pick up the affects from
stage 4. Power level is how hard they get hit with the affect. So if in stage
1 the affect was 2% of the time at power level 1 it may be 4% of the time
in power level 2.  And in stage 2 the affect in stage 1 may be 4% of the
time at power level 1 and 8% of the time at power level 2.
So with that being said here are the current stages and their affects:
Stage 1:  The Thirst Stage
          This makes them become thirsty quicker.  The formula used is the
following: <current stage>*<power level> for how much more is added to your
following: <current stage>*<power level> for how much more is subtracted from
your thirst each time.  With 100 being not thirsty and 0 being dehydrated.
Stage 2:  The Hunger Stage
          The hunger stage works exactly as above except, the formula
subtracts 1 from the current stage becoming: (<current stage>-1)*<power level>
Stage 3:  The Mentalstate Stage
          In this stage each time your mentalstate worsens nuisance exaggerates
the amount you worsen by. The formula used to compute how much more it
adds or subtracts is: .4*(<current stage>-2)*<power level>.
Stage 4:  The Potion Stage
          In this stage you can not stomach as many potions as you normally
could without the nuisance flag.  Normally if your thirst or hunger is above
48 you can't quaff anymore.  Nuisance makes this a much lower number.
The formula used is: (48-(3*<current stage>)+<power level>)
So at power level 10, stage 10 you could only quaff 8 potions on an empty
stomach.
Stage 5:  The Wait Stage
          In this stage commands start taking longer to complete.  A
normal spell for example takes around 8-15 rounds of wait time.  With this
stage more wait time is added with the following formula:
(<current stage> -4 ) + <power level>    So at Stage 6 at power level 5,
each command would have an additional 7 wait added to it.
Stage 6:  The Offensive Magic Stage
           In this stage you have a chance of targeting yourself with
offensive spells instead of whatever target is specified.  The formula
for the percentage or the time you do it is the following:
(<current stage>-5)*8 + <power_level>*6  So at first stage 6 with a power
level of 5 you would have a 38% chance to target yourself with offensive
spells.
Stage 7:  The Defensive Magic Stage
          In this stage, if you are fighting someone you have a chance to
target them with any defensive spells you cast.  The formula used is the
following:  (<current stage>-6)*8 + <power_level>*6
Continued in help 'NUISANCE STAGES2'
]],
  },
  {  
    keywords = {"NUISANCE STAGES2"},
    level = 54,
    type = "wizhelp",
    text = [[
Stage 8:  The Speech Stage
          In this stage you have a chance to scramble your speech and
scramble other peoples speech (IE what you hear from them).  This works
on a percentage with the following formula:
(<current stage>-7)*10*<power level>  So at stage 9 with power level 2
speech is scrambled 40% of the time.
Stage 9:  The Movement Stage
            In this stage you start moving in random directions like a drunk
does.  This is worked out in a percentage as well. Which works of the
following formula:  (<current stage>-8)*10*<power level>  So in stage 10
with a power level of 4 you would randomly choose an exit 80% of the time.
Stage 10:  The command Stage
           In this stage your commands start failing (Like mentalstate).
This is done on a percentage of the following:
(<current stage>-9)*10*<power level>  So at stage 10, power level 10 the
character becomes utterly useless, as commands will fail 100% of the time.
Soon there will be more options, when they come in the help files you should
see are:  'NUISANCE", "NUISANCE STAGES", "NUISANCE OPTIONS'
]],
  },
  {  
    keywords = {"NUISANCE", "UNNUISANCE"},
    level = 51,
    type = "wizhelp",
    text = [[
&WSyntax:
      &cunnuisance  <victim>
      &cnuisance    <victim> [options]
&GUnnuisance will remove the nuisance flag from a player.
Nuisance will add a nuisance flag to the player specified by victim.
&wThis only works on pc's.  The optional parameters are as follows:
  &cmaxtime <#> <minutes/days/hours>&w
         &wThe maxstage of nuisance. Default is 8 days.
  &ctime <#>&w:  The time in days that the nuisance flag will stay on the
         player, once the time is expired the flag will automatically be
         removed. If this option is not used it will default to a permanent
         penalty.
  &cpower <#>&w:  A number from 1 to 10, 10 being the worst for the player.

&WNote the words before the options are not optional and must be used.

&RExamples:  &cnuisance mortal maxtime 5 days time 7 power 5
&GThis would nuisance mortal for 7 days with the maximum stage being
reached in 5 days, at a power level of 5.  Also note you can leave options
out:  &cnuisance mortal maxtime 5 days power 5 &Gfor example would set the
maximum time to reach the final stage at a power level 5 and use the default
value for the time.  Also options can be rearranged n like:
&cnuisance mortal power 5 maxtime 5 days time 7 &Gwould be the same as the
first example.
&GTo see info on nuisance level, power and set time of a player, use &WMSTAT.
&WFor information on stages see help 'NUISANCE STAGES'
&G
We are not to give mortals any info about nuisance.
If they notice something is wrong and ask for an explanation just
&Wtrans <name> nuisance &G
MORTS ARE NOT TO BE TOLD WHAT THE FLAG IS OR GIVEN OTHER INFO RE: IT.
]],
  },
  {  
    keywords = {"OBJECTFLAGS"},
    level = 51,
    type = "wizhelp",
    text = [[
Flags that objects can have:

Flag        Affect                Flag        Affect
&r====        ======                ====        ======
&Gglow        &cn/a                   &Ghum         &cn/a
&Gdark        &cn/a                   &Gloyal       &cloyalty ('help loyal')
&Gevil        &cglow on det. evil     &Ginvis       &cinvisible
&Gmagic       &cprevents enchant      &Gnodrop      &ccannot drop
&Gbless       &c+20% resist dam.      &Gantigood    &czap if align +350
            &cdbl. duration poison
            &cweapon
&Gantievil    &czap if align -350     &Gantineutral &czap if align -350 to +350
&Gnoremove    &ccannot remove         &Ginventory   &cpurge upon char. death
&Gantimage    &czap if mage           &Gantithief   &czap if thief
&Gantiwarrior &czap if warrior        &Ganticleric  &czap if cleric
&Gantivampire &czap if vampire        &Gantidruid   &czap if druid
&Gorganic     &c+20% suscept. dam.    &Gmetal       &c+20% resist damage
&Gdonation    &cprevents get all      &Gclanobject  &cn/a
&Gclancorpse  &cn/a                   &Gprototype   &cn/a
&Gnolocate    &cnot visible on locate

&YAdditional flags:
&Gcovering      &cItems inside this are 'covered', use 'look under <object>' to
              see 'inside'.  The object does not have to be a container to
              be a covering object.  Use 'reset put' to indicate objects to
              be covered by this object.&w
]],
  },
  {  
    keywords = {"OBJECTS"},
    level = 1,
    type = "info",
    text = [[
To see the objects you currently possess, type INVENTORY and EQUIPMENT>
INVENTORY is the items you are carrying, but are not currently wearing.
EQUIPMENT shows you the equipment you are currently wearing.

You may WEAR, WIELD, or HOLD equipment to use it.  To stop using a piece
of equipment, you REMOVE it.  Before you may wield a new weapon, you must
first REMOVE the old weapon.

You can gain information on your objects by using LOOK or EXAMINE.  EXAMINE
tells you the condition of your item, as a more detailed form of LOOK.

To find out more information on objects, read sections 9, 10 and 17 of your
Adventurer's Guide book.

Also check MAGICTABLE or EQUIPTABLE to see which item restrictions your class
might be dealing with.
]],
  },
  {  
    keywords = {"OBJECTTYPES"},
    level = 51,
    type = "wizhelp",
    text = [[
Object types listed in bit order:

  None        Light     Scroll     Wand        Staff       Weapon
  Fireweapon  Missile   Treasure   Armor       Potion      Worn
  Furniture   Trash     Oldtrap    Container   Note        Drink_con
  Key         Food      Money      Pen         Boat        Corpse_npc
  Corpse_pc   Fountain  Pill       Blood       Bloodstain  Scraps
  Pipe        Herb_con  Herb       Incense     Fire        Book
  Switch      Lever     Pullchain  Button      Dial        Rune
  Runepouch   Match     Trap       Map         Portal      Paper
  Tinder      Lockpick  Spike      Disease     Oil         Fuel
  Short_bow   Long_bow  Crossbow   Projectile  Quiver      Shovel
  Salve

Not all are implemented.
]],
    see_also = {"OSET", "ITEMVALUES", "ARMORCLASS"},
  },
  {  
    keywords = {"OBJTRIGGERS OPTRIGGERS"},
    level = 51,
    type = "wizhelp",
    text = [[
Trigger Optnl Triggering Variable Explanation
------- ----- ------------------- -----------
Wear          <percentage>        [when a player wears the object]
Remove        <percentage>        [when a player removes the object]
Speech   {p}  <keyword / phrase>  [says or tells from same room as mob]
Rand          <percentage>        [randomly triggered based on percentile]
Sac           <percentage>        [when a player sacrifices the object]
Zap           <percentage>        [when the player is zapped due to alignment]
Get           <percentage>        [when a player gets the object]
Drop          <percentage>        [when a player drops the object]
Damage        <percentage>        [when the object is damaged]
Repair        <percentage>        [when the object is repaired]
Greet         <percentage>        [when a mob/player enters the room]
Exa           <percentage>        [when the object is Examined or Looked upon]
Look          ** THIS TRIGGER IS NOT CURRENTLY IN USE **
Push          <percentage>        [when a player pushes an object]
Pull          <percentage>        [when a player pulls an object]
Use           <percentage>        [see 'help useprog' for details]
]],
    see_also = {"OPSTAT", "OPEDIT", "TRIGGER", "OPCOMMANDS", "IFCHECKS", "VARIABLES"},
  },
  {  
    keywords = {"OBJTYPENUMS"},
    level = 52,
    type = "wizhelp",
    text = [[
&G                   NUMBER                 TYPE of OBJECT
&c
                     1                       Light
                     2                       Scroll
                     3                       Wand
                     4                       Staff
                     5                       Weapon
                     9                       Armor
                    10                       Potion
                    15                       Container
                    16                       Note
                    18                       Key
                    19                       Food
                    23                       Mcorpse
                    24                       Pcorpse
                    26                       Pill
                    34                       Book
]],
    see_also = {"MPEDIT", "OPEDIT", "RPEDIT", "IFCHECKS", "IFCHECKS2", "IFCHECKS3", "ITEMVALUES", "OBJECTTYPES", "VARIABLES"},
  },
  {  
    keywords = {"OCCULUTUS VISUM"},
    level = 1,
    type = "command",
    text = [[
Syntax:  occulutus visum
    or:  occu (or other unique abbreviation)

Triggers a character's special ability to sense all manner of the unseen.

See DETECT INVIS, DETECT HIDDEN
]],
  },
  {  
    keywords = {"ODELETE"},
    level = 65,
    type = "wizhelp",
    text = [[
Deletes an object.]],
  },
  {  
    keywords = {"OGRUB"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: ogrub <num of lines> <sort order> [keywords] [operands]

ogrub 20 level<8 avg>12
Display weapons below level 8 that do more than 12 average damage.

ogrub 20 +wear type=armor hp>100 dr>20
Display armor with more than 100 added hp and 20 added dam roll. Sort
by wear location.

ogrub 20 +type nm ng vnum>=900 vnum<=951 level>45 hp>0
Display all eq from Olympus that is above level 45 and affects hp.
Sort by object type in ascending order. Display only that eq held
by players - ignore any on mobs or on the ground.

ogrub 20 +name name<>gloves
Display all eq with the substring "gloves" in the name field. Sort
by object name. Note that often objects are named with two or three
keywords like "gauntlets steel gloves". The substring operator <>
is used to search fields for substrings.

ogrub 20 +cname np ng type=light int>0
Display lights on mobs that raise intelligence. Sort by character name.
Ignore any lights on players or on the ground.

ogrub 20 -dr np ng luck>0 level>=10 level<=20
Display eq that raises luck and is between levels 10 thru 20. Sort by
object damroll in descending order. Only display eq on mobs.

ogrub 20 +level or hr>25 dr>25 hp>100 mp>100 ac<-100
Display eq that raises hit roll more than 25 or dam roll more than 25
or hit points more than 100 or mana points more than 100 or lowers
armor class by more than 100 (remember the lower the AC the better)
Sort by object level in ascending order.

ogrub 20 or d2 sav0>1 sav1>1 sav2>1 sav3>1 sav4>1
Display equipment that have affects resulting in any saving throws that are
greater than one. Note that positive saving throws are bad for characters
and negative ones are good. The more negative the better. The d2 keyword
requests an alternate form of display which shows the saving throws.

ogrub 20 nm cname=joe type=weapon    Display Joe the player's weapons
ogrub 20 np cname=joe type=armor     Display Joe the mob's armor
]],
    see_also = {"OGRUB DATA"},
  },
  {  
    keywords = {"OGRUB DATA"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: ogrub <num of lines> <sort order> [keywords] [operands]

Here is some reference data you will need in order to use OGRUB.

FIELDS                      TYPES      WEAR     MODIFIERS
cname - chr name          1 light      1 take     or - select any
count - obj count         2 scroll     2 finger  +field - sort up
vnum  - obj vnum          3 wand       3 neck    -field - sort down
type  - obj type          4 staff      4 body     np - no players
name  - obj name          5 weapon     5 head     nm - no mobs
level - obj level         9 armor      6 legs     ng - not on the ground
wear  - obj wear locn    10 potion     7 feet     d2 - display saving throws
avg   - obj avg dam      15 container  8 hands
hr    - obj hit roll     16 note       9 arms     OPERATORS
dr    - obj dam roll     18 key       10 shield    = equals
hp    - obj hit pts      19 food      11 about    != not equal
mp    - obj mana pts     23 mcorpse   12 waist    >  greater than
ac    - obj armor class  24 pcorpse   13 wrist    >= greater than or equal
str   - obj str affect   26 pill      14 wield    <  less than
dex   - obj dex affect   24 book      15 hold     <= less than or equal
con   - obj con affect                16 dual     <> substring
wis   - obj wis affect                17 ears
int   - obj int affect                18 eyes
luck  - obj luck affect               19 missile
sav0  - save_poison
sav1  - save_rod
sav2  - save_para
sav3  - save_breath
sav4  - save_spell

Don't be scared by the fact that things like "pill" are referenced by
a number like 26. If you want info about pills, you can request the
info either by the name "pill" or the number "26".  ***SMILE***
]],
    see_also = {"OGRUB"},
  },
  {  
    keywords = {"OGRUB2"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: &Wogrub <num of lines> <sort order> [keywords] [operands]
&w
Here is some reference data you will need in order to use OGRUB.
&GFIELDS
&gcname - chr name   wear - obj wear locn  ac  - obj a.c.
count - obj count  avg  - obj avg dam    str - obj str
vnum  - obj vnum   hr   - obj hit roll   dex - obj dex
type  - obj type   dr   - obj dam roll   con - obj con
name  - obj name   hp   - obj hit pts    wis - obj wis
level - obj level  mp   - obj mana pts   int - obj int
luck  - obj luck
&GTYPES
&g1 light        2 scroll  3 wand  4 staff  5 weapon    9 armor    10 potion
15 container  16 note   18 key  19 food  23 mcorpse  24 pcorpse  26 pill
24 book
&GWEAR
&g 1 take   2 finger   3 neck     4 body    5 head    6 legs    7 feet   8 hand
 9 arms  10 shield  11 about   12 waist  13 wrist  14 wield  15 hold  16 dual
17 ears  18 eyes    19 missile
&GMODIFIERS
&gor - select any.  +field - sort up.  -field - sort down.
np - no players.  nm     - no mobs.  ng     - not on the ground.
&GOPERATORS
&g = equals                   != not equal     > greater than
>= greater than or equal     < less than    <= less than or equal
<> substring
&wDon't be scared by the fact that things like "pill" are referenced by
a number like 26. If you want info about pills, you can request the
info either by the name "pill" or the number "26".  ***SMILE***
]],
  },
  {  
    keywords = {"OLDSCORE"},
    level = 0,
    type = "command",
    text = [[
Syntax: oldscore

Oldscore shows the score information in a different way than 'score'.
]],
  },
  {  
    keywords = {"OLIST"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: olist
      :	olist <first object>
      :	olist <first object> <last object>

This command will list all of the prototype objects in your area, when used
with no arguments.  When used with a single argument it will list all
objects including and after the argument, and when used with two arguments,
it will list all objects including and between the two.
]],
  },
  {  
    keywords = {"OMENU"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: omenu <object name> [menu page] (defaults to 'a' if none given)

Omenu will bring you into a menu system of editing objects.  To use omenu,
you must be holding the object that you are editing in your inventory.  To
choose an option in the menu, type the number of the section followed by the
desired letter, and any variables that may follow.

See MENU for generic menu commands.
]],
  },
  {  
    keywords = {"OPEDIT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax:  opedit <object> <command> [number]  [program] [arguments]
Syntax:  opedit <object> add       <program> <arguments>
Syntax:  opedit <object> insert    <number>  <program> <arguments>
Syntax:  opedit <object> edit      <number>  [program] [arguments]
Syntax:  opedit <object> delete    <number>
Syntax:  opedit <object> list

Add, insert and edit will put you into the line editor to edit your program.
The arguments consist of a trigger, plus any arguments associated with that
trigger.  Object programs are like mobprograms, with trigger differences.

To edit an Objprogram, you must be holding the object in your inventory.
]],
    see_also = {"OPSTAT", "TRIGGER", "OPTRIGGERS", "OPCOMMANDS", "IFCHECKS", "IFCHECKS2", "VARIABLES"},
  },
  {  
    keywords = {"OPEN", "CLOSE", "LOCK", "UNLOCK", "PICK", "BOLT", "UNBOLT", "PICK LOCK"},
    level = 1,
    type = "command",
    text = [[
Syntax: open   <object|direction>
Syntax: close  <object|direction>
Syntax: lock   <object|direction>
Syntax: unlock <object|direction>
Syntax: pick   <object|direction>

OPEN and CLOSE open and close an object or a door.
LOCK and UNLOCK lock and unlock a closed object or door.  You must have
the requisite key to LOCK or UNLOCK.
PICK can open a lock without having the key.  In order to PICK successfully,
you must practice the appropriate skill.
]],
  },
  {  
    keywords = {"OPSTAT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: opstat <object/object vnum>

Opstat will display all of the objprograms that have been written for the
specified object.  If a copy of the object exists in the game, it can be
accessed by its vnum.
]],
    see_also = {"OPEDIT", "TRIGGER", "OPTRIGGERS", "OPCOMMANDS", "IFCHECKS", "IFCHECKS2", "VARIABLES"},
  },
  {  
    keywords = {"ORANGE"},
    level = 62,
    type = "wizhelp",
    text = [[
This function is under construction.
]],
  },
  {  
    keywords = {"ORDER"},
    level = 0,
    type = "command",
    text = [[
Syntax: order <character> command
Syntax: order all command

ORDER orders one or all of your charmed followers (including pets) to
perform any command.  The command may have arguments.  You are responsible
for the actions of your followers, and others who attack your followers
will incur the same penalty as if they attacked you directly.

Most charmed creatures lose their aggressive nature (while charmed).
]],
  },
  {  
    keywords = {"ORDERS"},
    level = 65,
    type = "wizhelp",
    text = [[
Shows created Orders.
]],
  },
  {  
    keywords = {"ORDERTALK"},
    level = 65,
    type = "wizhelp",
    text = [[
Special channels for Orders to discuss things.]],
  },
  {  
    keywords = {"OSET"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax:  oset <object>    <field> <value>
         oset object on

If the copy of the object you are currently modifying has the PROTOTYPE flag,
your modifications will also modify the index of that object, which all other
instances of the object are based on.  In the future, every copy of that obj
will reflect your modifications.

Also be aware that modifications to the object affect list (everything that
is listed after 'object values') will affect _every_ copy of that object in
the game, including old copies (even if they are not online).  Thus if you
change a prototype-flagged copy of a sword to +4 damroll, every copy of that
vnum ever made will reflect that change.  If you add a 'magic' flag to that
sword, however, only copies made after the change will be affected.

If the copy of the object you are modifying does NOT have the PROTOTYPE flag,
your modifications will affect only that copy.

OSET ON will lock you onto a particular object.  Once locked on, all commands
commands will imply 'oset <object>'.  Hitting enter while in OSET ON gives
you an ostat of the object you are working on.  To get out of OSET ON, simply
type the word DONE. Example:

        oset staff on
        long A long gnarled staff of burnished oak lies here.
        type staff
        done
]],
    see_also = {"AFFECTTYPES", "WEARFLAGS", "OBJECTFLAGS", "OBJECTTYPES", "ARMORCLASS",
                "ITEMVALUES", "WEAPONTYPES", "VARIABLES", "OMENU", "LAYERS", "LAYERS2"},
  },
  {  
    keywords = {"OVERRUN"},
    level = 1,
    type = "skill",
    text = [[
Syntax: overrun victim

This skill lets you charge into battle and inflict a greater damage on your
victim. You can only charge if you're mounted and wielding a weapon, and only
if the victim isn't fighting. Whether your charge successfully inflicts damage
is determined by your proficiency in this skill.
]],
  },
  {  
    keywords = {"OWHERE"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax 'Owhere <object/keyword>

This command will allow you to search for a certain item by using its
keyword. This will list the name of the object, its' location, the name
of the player(s) carrying it and the number of the objects currently online.
are currently on-line.

]],
  },
  {  
    keywords = {"PAGELENGTH"},
    level = 0,
    type = "command",
    text = [[
Syntax: pagelength <number of lines>

This command sets your screen to only display a certain amount of lines.
After setting pagelength, type clear to reinitialize your screen.
]],
  },
  {  
    keywords = {"PAGER"},
    level = 0,
    type = "command",
    text = [[
Syntax:  Pager <# of lines per screen>
Syntax:  Config +pager       (turns page pausing on)
Syntax:  Config -pager       (turns page pausing off)
Syntax:  Pager               (toggles pager on/off)

Pager is a configurable item that will pause screen scrollage at the user
specified pager length.  To set it, first set a desired page length using:

Pager <# of lines>

Initially, page length is set to 24 lines.  Once page length is set, use
the Config command to turn it on and off, or simply type 'pager'.

Commands available within the pager are:

(C)ontinue, (R)efresh, (B)ack, (Q)uit.

With 'continue' being the default item.  When the screen pauses, hit the
enter key to continue, or type another choice and hit the enter key.
]],
    see_also = {"CONFIG"},
  },
  {  
    keywords = {"PARALYZE"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast paralyze victim

A dark spell indeed, paralyze causes the very muscles of the body to stiffen,
making it very difficult indeed for the victim to resist stunning blows to the
body.
]],
  },
  {  
    keywords = {"PARDON"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: pardon <character> killer
Syntax: pardon <character> thief
Syntax: pardon <character> attacker

PARDON pardons a player for their crimes.
]],
  },
  {  
    keywords = {"PARRY"},
    level = 0,
    type = "skill",
    text = [[
Syntax:  operates automatically

Parry is a skill which assists in warding off incoming attacks.  If you
successfully parry attack, you take no damage from it.  Parry is an
autonomic skill, but you must be wielding a weapon to use it.
]],
  },
  {  
    keywords = {"PART", "BODYPARTS", "XFLAGS"},
    level = 53,
    type = "wizhelp",
    text = [[
Misc body parts:
HEAD     ARMS    LEGS   HEART        BRAINS      GUTS        HANDS   FEET
FINGERS  EAR     EYE    LONG_TONGUE  EYESTALKS   TENTACLES   FINS    WINGS
TAIL     SCALES  HOOVES FORELEGS     HAUNCHES

Used for attacking:
CLAWS    HORNS   TUSKS  TAILATTACK   SHARPSCALES
]],
  },
  {  
    keywords = {"PASS DOOR"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'pass door'

This spell enables the caster to pass through closed doors.
]],
  },
  {  
    keywords = {"PASSWORD"},
    level = 0,
    type = "command",
    text = [[
Syntax:  password  <new password>   <new password>

PASSWORD changes your character's password.  You repeat the new password only.
If you do not get it correctly it will not work.  This should end the typo
locking you out of your character.
The PASSWORD command is protected against being snooped or logged; it is
impossible for any immortal to in any way see, find or retrieve it.  It
is the responsibility of the player to ensure that the password of the
character is kept secure.

Passwords can not contain certain characters, or spaces.  We also advise
that you use an alphanumeric password (one containing both numbers and
letters) as they are harder to guess.  We also recommend that you choose
a password that is greater than 6 characters in length.  A good rule of
thumb is if it is in the dictionary, it is probably not a good password.

NOTE:  if you decide to trade a character, you do so at your own risk.
Immortals are not responsible for ensuring fair trades.  You may seek an
immortal to oversee a trade, but it is not their  responsibility.

&YThe password policy is:  password equals ownership.&w
]],
  },
  {  
    keywords = {"PCOLORS", "PROMPT COLORS", "COLOR", "COLORS", "PCOLOR"},
    level = 0,
    type = "info",
    text = [[
The following are the tags used for adding color in your text.

Foreground text tag: &&
Tokens for foreground text are:

&&x - Black           &&r - &rDark Red&w  &&g - &gDark Green&w
&&O - &OOrange (brown)&w  &&b - &bDark Blue&w &&p - &pPurple&w
&&c - &cCyan&w            &&w - &wGrey&w      &&z - &zDark Grey&w
&&R - &RRed&w             &&G - &GGreen&w     &&Y - &YYellow&w
&&B - &BBlue&w            &&P - &PPink&w      &&C - &CLight Blue&w
&&W - &WWhite&w
&&v or &&V - &vReverse the colors.&w
&&u or &&U - &uUnderline the text.&w
&&i or &&I - &iItalicize the text.&w
&&s or &&S - &sStrikeover text.&w
&&D - Resets to custom color for whatever is being displayed.
&&d - Resets to terminal default color.

Blinking foreground text tag: }}
Tokens for blinking text are:

}}x - Black           }}r - }rDark Red&w  }}g - }gDark Green&w
}}O - }OOrange (brown)&w  }}b - }bDark Blue&w }}p - }pPurple&w
}}c - }cCyan&w            }}w - }wGrey&w      }}z - }zDark Grey&w
}}R - }RRed&w             }}G - }GGreen&w     }}Y - }YYellow&w
}}B - }BBlue&w            }}P - }PPink&w      }}C - }CLight Blue&w
}}W - }WWhite&w

When putting color in something, please try to remember to close your
colors with a &&D tag so that anyone viewing it won't have to deal with
color bleeding all over the place. The same holds for italic or underlined
text as well.

The &&d tag should only be used when absolutely necessary.

Background color tag: ^^
Tokens for background color are:

^^x - Black         ^^r - Red           ^^g - Green
^^O - Orange        ^^b - Blue          ^^p - Purple
^^c - Cyan          ^^w - Grey

If setting both foreground and background colors. The foreground must
be used before the background color. Also, the last color setting in your
prompt will wash over into the text you type. So, if you want a set
of colors for your typed text, include that at the end of your prompt set.

Example (assuming current h.p.'s of 43 and mana of 23):

Prompt &&Y^^b<%h/&&x^^r%m>&&w^^x = <43/23>
        {A}     {B}       {C}

A) Yellow with blue background.
B) Black with dark red background.
C) Light Grey with black background.
]],
    see_also = {"PROMPT", "ANSI"},
  },
  {  
    keywords = {"PCRENAME"},
    level = 55,
    type = "wizhelp",
    text = [[
syntax pcrename <oldname> <newname>

This command permanently changes a players name and should be used
sparingly. It does a check to ensure there is no other player by that
name already in the files. Double quotes are required for names that
contain an apostrophe, a space or both.

Examples:
pcrename "player a" "player'a"
pcrename playera playerb
]],
  },
  {  
    keywords = {"PEACE"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: peace

PEACE causes all characters in a room to stop fighting.
]],
  },
  {  
    keywords = {"PEEK"},
    level = 0,
    type = "skill",
    text = [[
This skill shows you a character's inventory when you look at a character.
Use of the skill is automatic when you 'look' at a character after you
have practiced the skill.
]],
  },
  {  
    keywords = {"PELT"},
    level = 1,
    type = "skill",
    text = [[
Syntax: pelt

Some creatures use their natural weapons in combat.  Some may toss spines or
other items grown from their own body at you!  Other may throw rocks and other
heavy debris at you!
]],
  },
  {  
    keywords = {"PET", "PETS"},
    level = 0,
    type = "info",
    text = [[
You can buy pets in the pet shop.  You may buy one more pet each time you
advance in level.  Your pet-buying opportunities do not accumulate; use
them or lose them.  This policy prevents wholesale abuse of pets.

You are responsible for the actions of your pets.
]],
    see_also = {"PETSAVE"},
  },
  {  
    keywords = {"PETSAVE"},
    level = 1,
    type = "info",
    text = [[
Petsaving is automatic in the Realms. When you purchase a pet, it is
loyal to you until its' death. Your pet will automatically save when
you save and quit when you quit. If you die, your pet may still live
and vice-versa.
Pets remain loyal until they die or until you purchase a new pet. If
you lose link your pet may be killed without you around to protect it.
In no instances will pets be reimbursed. Do not even ask.
  *** You may only purchase one pet per level ***
]],
  },
  {  
    keywords = {"PFILES"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: pfiles

Performs a manual check for out of date player files.  This runs everyday
also, so isn't really a necessary to do a lot.
]],
  },
  {  
    keywords = {"PIPEFLAG"},
    level = 51,
    type = "wizhelp",
    text = [[
The following flags may be used with the item type pipe in the v3 item
value:
PIPE_TAMPED          Pipe has been tamped (not really used yet)
PIPE_LIT             Pipe is lit (required for smoking)
PIPE_HOT             Pipe is hot
PIPE_DIRTY           Pipe is dirty (not really used yet)
PIPE_FILTHY          Pipe is REALLY dirty (not used at all yet)
PIPE_GOINGOUT        Pipe is about to go out
PIPE_BURNT           Not used yet.
PIPE_FULLOFASH       Pipe is full of ashes, and needs to be emptied.
]],
  },
  {  
    keywords = {"PIT", "ETCH", "PITTING", "ETCHING"},
    level = 1,
    type = "info",
    text = [[
Pitting and etching occurs when acid hits your armor, due to spells or
breath. It permanently reduces the armor class of the item and reduces
the value of the armor.
]],
  },
  {  
    keywords = {"PIXIE PIXIES"},
    level = 0,
    type = "race",
    text = [[
Pixies are small Elfin creatures with gossamer wings.  They are very much
more intelligent than most other races, but their strength and constitution
suffers from their small size.  Because of this, the Pixie often choose the
calling of magic and excels especially in the arts of the Mage; the mind of
the Pixie knows no equal.  Pixies possess the obvious ability of flight.
Due to their fragility, blunt weapons seem to do extra damage to them.

Pixies are slight of stature, standing less than 2 feet in height.  Both
their skin and hair color varies from among all the colors of the rainbow.

Due to their high intelligence, Pixies learn at 115% of the normal experience
rate.

Pixies can be a Mage, Cleric, Thief, Druid, Diabolist and Jester.
]],
  },
  {  
    keywords = {"PK", "PLAYERKILL", "PLAYERKILLING", "PKILL"},
    level = 1,
    type = "info",
    text = [[
See "LAW PKILL" for more information about playerkilling.
]],
  },
  {  
    keywords = {"PLANT PASS"},
    level = 0,
    type = "spell",
    text = [[
Syntax:  cast 'plant pass' <victim>

This spell allows the caster to merge with nearby foliage, and flow through
it to emerge near the victim, who must also be in a forested area.

Obviously this spell requires a good deal of natural foliage in both the
caster's and the victim's location.
]],
  },
  {  
    keywords = {"POISON"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast poison <victim>

This spell reduces the strength of the victim by two, as well as reducing the
victim's regeneration rate.
]],
  },
  {  
    keywords = {"POISON WEAPON"},
    level = 0,
    type = "skill",
    text = [[
Syntax:  'poison weapon' <weapon>
Abbrev:  poison <weapon>

A skill unique to thieves which enables them to coat their weapon with a
deadly poison.  In battle, this poison will cause ill effects on its
recipient.  Be warned however, it has been told that poison has a strong
lessening effect on the lifetime of the weapon poisoned.

To poison a weapon you must have the weapon itself, the poisoning powder
and a full waterskin in your inventory.  Your intelligence and wisdom
must both also be relatively high, else you will be unable to complete
the poisoning process until they are raised to a sufficient level.

Due to the personal nature of working with these deadly poisons, only those
who have this skill can wield such a weapon.  Note that there are several
different types of poisoned weapons in the Realm...some poisoned weapons are
usable by anyone...
]],
  },
  {  
    keywords = {"POLYMORPH"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c polymorph

A spell enabling the caster to morph into the desired
creature.  Varies by class and/or race according to the
machinations of the gods.

See also:  revert
]],
  },
  {  
    keywords = {"POSSESS"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast possess (victim)

Mighty spellcasters can possess the bodies of other, less-capable, creatures
in the Realm.  This is most commonly seen when major demons and devils try to
take over the bodies of mortals to perform nefarious deeds.

]],
  },
  {  
    keywords = {"PRACTICE"},
    level = 1,
    type = "command",
    text = [[
Syntax: PRACTICE
Syntax: PRACTICE <skill|spell|weapon>

PRACTICE without an argument tells you your current ability level in all
the skills and spells available to you.  You can check this anywhere.

PRACTICE with an argument practice that skill or spell.  Your learning
percentage starts off at 0% (unlearned), and can be practiced to a certain
point.  That point depends on the class, basic statistics, and race.
After this initial practice, the skill/spell must be used to develop it
to the level of 'adept' (Adept is not always necessarily 100%)  You must
be at a guild master to practice.

The higher your wisdom, the more practice sessions you will have each time you
gain a level.  Unused sessions are saved until you do use them.  You can also
earn more practices by taking Quests...but only if you are lucky (;

All characters may practice skills, spells, and weapons in the Academy.

For more information on spell, skills, weapons, and practicing, read section
15 of your Adventurer's Guide book.
]],
  },
  {  
    keywords = {"PRANCE"},
    level = 1,
    type = "skill",
    text = [[
Syntax: prance

One of the more useful skills a Jester learns is the ability to dance about,
using forms they have learned from the various cultures they have visited.  A
Jester has such moves, that they are quite hard to hit in combat, as they jump
back and forth, causing their victims seemingly devastating strikes to land
with less energy and damage.
]],
  },
  {  
    keywords = {"PRAY"},
    level = 1,
    type = "command",
    text = [[
Pray is a special channel, which lets you talk directly to the demigod or
demigoddess of your Following.  This is heard only by that Immortal.
]],
  },
  {  
    keywords = {"PROJECT"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: project -- same as project list
        project save
        project list [available]
        project code  --- Lists approved projects with no coders
        project mine -- Lists all projects that you own or are the coder
        project more --- Lists projects as well as coder/log info
        project add <name>
        project <number> coder  --- Assigns you as the coder of a project
        project <number> delete
        project <number> take
        project <number> log write
        project <number> log subject <subject>
        project <number> log post
        project <number> log list
        project <number> log <number> read
        project <number> log <number> delete
        project <number> description --- Buffer to describe the project
        project <number> show -- shows description of the project

You can remove yourself as a coder or owner by repeating the command.
Change status/post on other's projects, 60+, Code council, Vc heads.
List logs/read logs from others projects, 54+
Add/ delete logs  <Level 60+, Code council and VC heads)
]],
  },
  {  
    keywords = {"PROMPT", "FPROMPT"},
    level = 1,
    type = "command",
    text = [[
Syntax:   prompt  <string>
Syntax:   fprompt <string>

Sets your prompt to a given string.  The game automatically sets your prompt
when your character is created, but you can use PROMPT to change your prompt
to more to your liking.  If you type 'default' as the string, your prompt
will be set back to the game default.

The fprompt sets your fighting prompt.  This is the prompt that is displayed
to you while you are fighting.  It follows the same format as the normal
prompt does.

Your prompt can be any string of characters that you wish. You can also embed
special characters and tokens into the string that you set. These special
characters are linked with specific groups of tokens. These tokens will add
specific sets of information to your prompt.

The first special character is:  %
Tokens for % are:
  %h  - current hitpoints                %m  - current mana (0 for vamp)
  %H  - maximum hitpoints                %M  - maximum mana (0 for vamp)
  %g  - gold held                        %x  - current experience
  %v  - current movement                 %V  - maximum movement
  %a  - your alignment                   %X  - experience needed to next level
  %A  - invisible/hide/sneak indicator   %S  - your current combat style
  %c  - your opponent's health           %n  - your opponent's name
  %C  - your health                      %T  - descriptive time of day
  %w  - displays your wait status        %L  - adds a line break
  %t  - displays a timestamp

The other special characters are:
 &&  - Foreground color                  ^^  - Background color

Examples (assuming current hit points of 43, mana of 23, and movement of 120):
Prompt %h%m%v       =   4323120
Prompt <%h|%m|%v>>> =   <43|23|120>>>
Prompt %h %m %v     =   43 23 120

Please see HELP PCOLORS for a list of the color tokens. If you are immortal,
see HELP IMMPROMPT for a list of immortal-only prompt tokens.
]],
  },
  {  
    keywords = {"PROTECTION", "SANCTUARY", "CORRUPTION", "BALANCE"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast protection
Syntax: cast corruption
Syntax: cast sanctuary  <character>

The PROTECTION spell reduces the damage taken from any attack by an evil
creature by one quarter.  If a neutral or evil character is under the
influence of Protection, they will take more damage.

The CORRUPTION spell reduces the damage taken from any attack by an good
creature by one quarter.  If a neutral or good character is under the
influence of Corruption, they will take more damage.

The BALANCE spell reduces damage taken from a good or evil character by a
sixth.  If a good or evil character is under the influence of Balance, they
will take more damage.

The SANCTUARY spell reduces the damage taken by the character from any attack
by one half.

These spells may be used simultaneously for cumulative effect.
]],
  },
  {  
    keywords = {"PUGILISM", "LONG BLADES", "SHORT BLADES", "FLEXIBLE ARMS", "TALONOUS ARMS", "BLUDGEONS", "SHIELDWORK", "AXES", "POLEARMS", "EXOTIC ARMS", "MISSILE WEAPONS"},
    level = 1,
    type = "skill",
    text = [[
These skills represent your proficiency with various type of weapons.
Each class has different maximum proficiencies with different types
of arms, i.e. the best choice for mages are 'short blades, while a
cleric's best choice is with 'bludgeons'

Proficiency of less than 50% with a given weapon type means that damage
inflicted is less than "average", while proficiency greater than 50%
increases your damage per hit.

These skills are automatic:  you need not type anything to invoke them.

"Pugilism" affects your proficiency with otherwise unclassified weapons or
fighting barehanded.

"Shieldwork" helps with blocking and using the shield as an offensive weapon
during combat.
]],
  },
  {  
    keywords = {"PULL", "PUSH", "LEVERS", "PULLCHAINS", "SWITCHES", "BUTTONS"},
    level = 0,
    type = "command",
    text = [[
Syntax: pull <trigger>
Syntax: push <trigger>

Levers, switches, pullchains and buttons can do all sorts of interesting
things... open or unlock doors, change exits around, teleport you to another
location, cast a spell, summon a monster... you name it!
]],
  },
  {  
    keywords = {"PULLTYPES"},
    level = 51,
    type = "wizhelp",
    text = [[
&YSyntax&W: redit pushtype <direction> <type>
&YSyntax&W: redit push <direction> <force>

Where type is equal to Current, Wave, Whirlpool, Geyser, Wind,
Storm, and Vortex, to name a few . These equal the 'pushforce'
Other types include Vacuum, Slip, Coldwind, Sinkhole, Landslide,
Quicksand, Earthquake, Undefined, Lava, Hotair and Breeze (objects only).

The frequency of the push is controlled by the value set in
redit push <force>, and may be anything from -100 to 100. Positive
and negative values represent pulling and pushing, respectively.
The more positive (or negative) the number is, the sooner the force
will push or pull you.
]],
  },
  {  
    keywords = {"PUMMEL"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  pummel

Pummel is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"PUNCH"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  punch
Punch is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"PUNT"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  punt

Punt is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"PURGE"},
    level = 57,
    type = "wizhelp",
    text = [[
Syntax: purge
Syntax: purge <character>

PURGE is used to clean up the world.  PURGE with no arguments removes all the
NPC's and objects in the current room.  PURGE with an argument purges one
character from anywhere in the world.

PURGE will not get rid of PC's.
]],
  },
  {  
    keywords = {"QPBUY"},
    level = 1,
    type = "command",
    text = [[
Syntax: qpbuy hum <item>
        qpbuy glow <item>
        qpbuy noburn <container>
        qpbuy keyword <item> <keyword>

This can add a flag or statistic to an item by buying them from Joey the
Questmaster.  Hum and Glow are cosmetic only, and cost 50QPs.  Noburn can only
be added to containers, and costs 5000QPs. Keyword will add a new keyword to
the item and costs 100QPs.
]],
  },
  {  
    keywords = {"QPSET"},
    level = 51,
    type = "wizhelp",
    text = [[
This command is used for giving/taking Glory from players.  The syntax
is as follows:

      qpset <player>  <give|take>  <amount>

Where one of give or take is used, and the amount is always a positive
integer.

Please see HELP GLORYIMM before affecting a player's Glory.
]],
    see_also = {"GLORYIMM2", "GLORY", "GLORY RATES"},
  },
  {  
    keywords = {"QPSTAT"},
    level = 51,
    type = "info",
    text = [[
syntax ( qpstat target)

This command will show information regarding the amount of glory a
player has. The first number is their current glory, the second is
the amount of glory held over lifetime.
]],
    see_also = {"GLORY", "GLORYRATES", "QPSET"},
  },
  {  
    keywords = {"QSTAT"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: qstat (charname)

Check and see if a character is on a quest, and if so, the information about
the quest.  If the character is on a quest but no info is given, then they
have completed their quest and need to head back to Joey to complete it.

Use this to check characters before hotbooting.
]],
  },
  {  
    keywords = {"QUANTUM SPIKE"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'quantum spike' (victim)

The 'Quantum Spike' is one of the Sorcerers's most awesome attacks.  With
this spell, the casting Mage is able to form, within the body of his
victim, a sphere of Quantum probability optimized in such a way as to
cause the most bizarre contortion of bodily order imaginable.  Organs
and tissues are rendered into unrecognizable blobs interconnected in
fiendish, unknowable geometries.

Obviously, such an attack has astonishing effects on any physical
creature, as well as any entity which has an extension into the
physical world.

]],
  },
  {  
    keywords = {"QUEST"},
    level = 0,
    type = "command",
    text = [[
Syntax: QUEST <message>

The quest channel is one which is typically used when a quest is being
run, to notify players who are involved as to new updates.

Quests are held at the whim of Immortals. If you are using the Quest channel
to ask if there is a quest, you are probably too late to enter. Simply keep
the channel on and wait for an Immortal's announcement, should there be one.

If you are trying to work something out with Joey the Questmaster, the command
you're probably looking for is "AQUEST".
]],
  },
  {  
    keywords = {"QUESTS", "QUESTING"},
    level = 1,
    type = "info",
    text = [[
.
  Quests are run at random times for different groups of players within the
realms.  They may involve anything from a scavenger hunt, to solving riddles,
to killing mobs that threaten the Realms.  Quests are an excellent way to
meet other players, and enhance roleplaying throughout the realm.
  Different quests will result in different awards.  Awards are up to the
discretion of the immortal running the quest.

Some things to remember while questing:

 &W-&GWe are volunteers, and choose to run quests. If you have criticisms of
    the quest, or the person running the quest, please be constructive and
    vent your concerns in an appropriate forum.

 &W-&GDo not ask when the next quest will be, or if there is a quest. Just pay
    attention to channels and what is going on around you.  If something out
    of the ordinary is going on, there's a good chance it might be a quest.

 &W-&GUnless explicitly stated, Multi-playing is &YNOT&G allowed during quests.
    IF you are caught multi-playing, you will forfeit any reward, and most
    likely have a temporary ban from questing placed on the characters involved
]],
    see_also = {"QUEST", "GLORY", "GLORY", "RATES", "GLORY", "TRADE"},
  },
  {  
    keywords = {"QUESTSTAT"},
    level = 65,
    type = "wizhelp",
    text = [[
Load up quest items, and set the price and level range.
]],
  },
  {  
    keywords = {"QUICKENING"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast quickening

A spell created by the Mages of the Thieves Guild, this incantation allows the
victim to move quicker and dodge attacks with ease.  Many a thief has
performed great criminal feats while under the influence of this spell.]],
  },
  {  
    keywords = {"QUIT", "QUI", "RENT", "OFFER"},
    level = 1,
    type = "command",
    text = [[
Syntax: QUIT

QUIT leaves the game.  You must be in the 3x3 area that makes up the Temple of
Drazuk in Drazukville.  When you re-enter the game you will be back in the
same room, unless that room has a prog that moves you upon re-entry.

QUIT automatically does a SAVE, so you can safely leave the game with just
one command.  Nevertheless, it's a good idea to SAVE before QUIT.  If you
get into the habit of using QUIT without SAVE, and then you play some other
mud that doesn't save before quitting, you're going to regret it.

Non-Deadly characters should instead "RENT".  Otherwise, keeping Limited items
on their person is not guaranteed.  A good idea is to "OFFER" at Kallista
first, which will give you an idea of how much rent will cost.

Rent is listed at a daily value, and then calculated and removed from your
character when you log back in next time.  Example:  If you "RENT" and are
told your rent is 15000 gold per day, then log back in without being gone a
full day, your rent is adjusted for that time span.  Logging out and coming
back a few seconds later may only cost a few coins.
]],
  },
  {  
    keywords = {"RACE", "RACES"},
    level = 0,
    type = "catagory",
    text = [[
There are currently 16 known races existing within these Realms.
Type "help [race]" for specific information on the specified race:

Human ...... the generic race, with no inherent strengths or weaknesses.
Dwarf ...... short, hardy and hairy; often cantankerous in personality.
Elf ........ tall, thin and swift like the wind; close to nature and earth.
Halfling ... short, quick and furry; mischievous and head-strong.
Pixie ...... a winged race, small of stature and with keen minds.
Half-Elf ... a mix of Human and Elf, possess the advantages of both.
Half-Ogre .. tall, powerful and deadly in combat; the prototypical warrior.
Half-Orc ... large, squat and smelly; make exceptionally deadly warriors.
Half-Troll.. a constitution just short of god-like; a truly deadly race.
Gith........ gaunt and long of limb, these astral beings naturally detect
invis
Sea-elf..... born of the sea, natural ability to breath under water.
Drow........ cousins of the elf, with a drawing to magic and casting spells.
Lizardman... given to tribal living, stronger in mind than in body.
Gnome....... demi-human creatures, well suited for magic and religion.
Ghoul....... magical elder race, powerful, with a need to explore.
Goblin...... cavern-dwellers; small, but strong, fast and crafty.
Wolfen...... mystical wolf-like creatures.
Minotaur.... heafty bipedal cattle-like creatures.
Shuri....... swift and agile felines
Gulran...... a massive race of powerful giants
Zephyr...... a race of avians, agile with the gift of flight
Jinn........ completely devoted to magics, very intelligent and wise
Ahpock...... devoid of magical abilities, they are the epitome of soldiers
]],
  },
  {  
    keywords = {"RACETALK"},
    level = 2,
    type = "command",
    text = [[
Syntax:  racetalk <message>

The racetalk channel will send your message to all the members of
your race currently online.  This channel can be used to roleplay
in accordance with the characteristics of your race, to plan runs
or grouping with a more focused body of players, or for general
chatter.  Please note that racetalk is partially designed to
promote roleplaying, so attempting to limit yourself to the
characteristics of your race may enhance your enjoyment of the mud,
and may provide a unique experience for those who have never
roleplayed previously.
]],
  },
  {  
    keywords = {"RANDOM ITEMS", "RANDOMS"},
    level = 1,
    type = "info",
    text = [[
Here at HoG you may not find as many "stock" items on the mobs as you would on
other MUDs.  We make up for that by having a system in place that creates
random items on the creatures as they repop.  These items cover the whole
range of equipment slots.  The name and affects are completely random, and
always changing.  Two random rings with the same name can be completely
different.  A lvl65 mob can have junk...a Mudschool mob can have a priceless
treasure.

In addition, you may find artifacts, which are extremely rare random items.
Artifacts will never have affects that are bad for your character, although
the number of affects on each one varies.
]],
  },
  {  
    keywords = {"RANGER"},
    level = 0,
    type = "class",
    text = [[
A ranger is the outdoorsman and adventuresome free spirit of the times.  A
self-sufficient person, the ranger is adaptable and can survive in almost
any locale.  Skilled with weapons and able to utilize some of the finest
armor available, a ranger is physically skilled enough to take on most any
foe.  However, for especially hardy opponents, a ranger also can cast many
useful spells to both hinder his opponent and aid himself.  From minor
curative magics to blinding his enemy, the ranger is the most adept class
at surviving on its own.  A ranger typically travels light, but he does
have the mighty strength of a warrior to carry equipment needed in his
travels.  Like the druid (the class other than warrior that he most
closely resembles), his need for help from outside sources is low.

Dexterity is the rangers prime attribute, and Strength is his second.
Intelligence is his tertiary statistic.

The races of Human, Dwarf, Elf, Halfling, Half-elf, Sea-elf, Gnome, Ghoul,
Wolfen, Minotaur and Lizardman are allowed to be rangers.
]],
  },
  {  
    keywords = {"RANK"},
    level = 1,
    type = "command",
    text = [[
Syntax: rank (string of text)

Replaces your level title, such as Implementor, Demigod, Avatar, etc.  Only
usable by those over level 50.  Only usable on yourself, please don't make it
so long it breaks the who list.
]],
  },
  {  
    keywords = {"RAP"},
    level = 51,
    type = "wizhelp",
    text = [[
This command allows you to rap on a closed passageway and anyone on the
other side will "hear" it.  The message sent is an act_message, and
act_progs can be trigger by it.
]],
  },
  {  
    keywords = {"RASSIGN", "MASSIGN", "OASSIGN"},
    level = 58,
    type = "wizhelp",
    text = [[
Syntax: rassign
        oassign
        massign

> Steps for creating a new area from scratch;
> 1. checkvnum rooms   low_vnum hi_vnum
>    checkvnum objects low_vnum hi_vnum
>    checkvnum mobs    low_vnum hi_vnum
>     (make sure the vnums don't overlap another area)
> 2. rassign (person) low_vnum hi_vnum
>    massign (person) low_vnum hi_vnum
>    oassign (person) low_vnum hi_vnum
> 3. mset (person) aloaded yes
> 4. goto low_vnum
>    goto hi_vnum
> 5. savea
> 6. save
>
> This should create a new area listed as '{PROTO} (Person)'s area in
> progress', with the file name '(person).are' and it should load up after
> rebooting the MUD with 'loadarea' or 'loadarea (person).are' if it's not
> your area.
NEVER do this to someone who has an area assigned to them. This would
change the range for the area they have assigned and wipe out the area.
]],
  },
  {  
    keywords = {"RAT"},
    level = 58,
    type = "wizhelp",
    text = [[
Syntax: rat vnum1 vnum2 command [parameters]

Rat, or 'range at' is the at command with the added parameters of two
room vnums.  Assuming the vnums are valid, your 'at' command will be
executed in every room in the range you give.

Example: rat 100 110 redit flags 0
This will clear the room flags in all rooms from 100 to 110 inclusive.
]],
  },
  {  
    keywords = {"RAZORBAIT"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast razorbait (victim)

This spell makes the victim more susceptible to stabbing attacks.
]],
  },
  {  
    keywords = {"RDELETE"},
    level = 65,
    type = "wizhelp",
    text = [[
Deletes a room.
]],
  },
  {  
    keywords = {"REBOOT", "SHUTDOWN", "WIZLOCK", "REBOO", "SHUTDOW"},
    level = 64,
    type = "wizhelp",
    text = [[
Syntax: reboot <nosave>
Syntax: shutdown <nosave>
Syntax: wizlock

REBOOT shuts down the server.  When the normal 'startup' script is used
to control the server, a delay of sixty seconds will ensue (to allow
old connections to die), followed by a reboot.

SHUTDOWN shuts down the server and prevents the normal 'startup' script
from restarting it.

WIZLOCK is a toggle command.  When the server is WIZLOCKed, players
below level 51 may not log in.  Players who lose their links, however,
may reconnect.

If nosave is specified for reboot or shutdown, it will not automatically
save all of the players.

You have to do more than "Reboo" or "Shutdow"
]],
  },
  {  
    keywords = {"RECALL"},
    level = 1,
    type = "info",
    text = [[
With a scroll or potion of 'word of recall' you can instantly return from
most areas to your attuned recall spot.  Usually this is the hub of the realm,
The Temple of Drazuk, but followers of the various religions of the world
recall to their god's temples.

Scrolls of recall are available in Drazukville's section of magic shoppes.
]],
    see_also = {"word of recall"},
  },
  {  
    keywords = {"RECHARGE"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'recharge' <wand/staff>

This spell is used to recharge wands and staves after use.  The mage
or cleric performing the recharge should always insure the item is
not fully charged, as overcharging is considered dangerous.  Also,
there is always a small chance of destroying the staff, or in even
rarer instances multiplying the charges available.
]],
  },
  {  
    keywords = {"REDIT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: REDIT FIELD [parameter list]
        REDIT ON

FIELD  | PARAMETERS             -- DESCRIPTION / NOTES
---------------------------------------------------------------------
name   | <room name>            -- sets the room name / short description
exit   | <direction> [vnum] [exit-type] [key] [keywords]
bexit  | same as above, but does the exit in both directions
desc   | none                   -- you will be placed into the buffer editor
exdesc | <direction> [text]     -- sets/clears an exit's description
ed     | <keyword(s)>           -- adds/edits an extra description to the room
rmed   | <keyword(s)>           -- removes an extra description from the room
sector | <value>                -- sets the sector type
flags  | <flag> [flag]          -- toggles room flags
exflags| <direction> [flags]    -- displays/toggles exit flags
exname | <direction> [keywords] -- sets an exit's keywords
exkey  | <direction> <key vnum> -- sets an exit's key vnum/value

Note: Put a '+' before the direction to force ADDing of that exit
      and use a '#' to specify the exit by sequential order.

REDIT ON will lock you into a mode in which 'redit' is implied in each command
sequence, and hitting enter will give you an instant rstat of whichever room
you are in at the time. To get out of REDIT ON, simply type the word DONE.
Example:

        redit on
        name A dark and foreboding hallway
        flags dark indoors
        done
]],
    see_also = { "EXITTYPES", "EXFLAGS", "EXITMAKING", "SECTORTYPES", "ROOMFLAGS"},
  },
  {  
    keywords = {"REDRAW"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: redraw

This will redraw the whole screen, and update the menu that is being worked
on if any.
]],
    see_also = {"REFRESH"},
  },
  {  
    keywords = {"REFRESH"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: refresh

This will refresh the information in the menu that is being worked on without
redrawing the screen.
]],
    see_also = {"REDRAW"},
  },
  {  
    keywords = {"REFRESH", "refresh spell"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast refresh <character>

This spell refreshes the movement points of a character who is out of movement
points. The amount it restores is based upon the casting character's maximum
movement points.
]],
  },
  {  
    keywords = {"REFUND"},
    level = 1,
    type = "command",
    text = [[
Syntax:  refund "itemname"

Sometimes you find that a Quest Item that was useful at one point is not
longer what you need to have.  If it is an official Quest Item, gained from
the Questmaster, then you can goto that Questmaster and use the "refund"
command to return that item.  You will receive 20% of the Quest Points you
spent for that item.

WARNING:  This is the only way to return a Quest Item you have purchased, even
if that purchase was a mistake (like you typed the wrong number or something
when buying a Quest Item).  Please be aware of this.
]],
  },
  {  
    keywords = {"REIMB", "REIMBURSEMENT"},
    level = 1,
    type = "info",
    text = [[
Experience can _not_ be reimbursed under any circumstances whatsoever.

The following are causes we will NOT reimburse for:
-- Loss of corpse due to corpse decay.  See "help corpse" for details.
-- Loss of corpse due to lag.
-- Loss of corpse due to problems with your system or the net.
-- Individual items lost due not saving your character regularly.
-- Individual items lost due to carrying items above your level.
-- Individual items lost because they were zapped or dropped on the ground.
-- Containers lost because they were left on ground or destroyed by a mob.
-- Weapon loss due to disarm before crash, reboot, or from a mob taking it.
-- Items lost due to hitting a death trap
-- Items lost due to scrapping by mobs or other players
-- Items lost due transferring equipment from one character to another.
-- Items lost due to not saving after looting your corpse and a crash occurs.

Corpses are now saved across crashes and reboots, eliminating the need
for most reimbursements due to corpse loss.  The ONLY cause for reimbursement
is when a corpse reappears in the game empty after a crash or reboot.
]],
  },
  {  
    keywords = {"REKEY"},
    level = 1,
    type = "info",
    text = [[
Rekey changes the keyword of an item.
It differs from rename in that it is not the name that is seen, but the
name the object is identified as and can be looked at or picked up as.
For example, if a sword of legend was rekeyed to blade , get sword would
no longer work with this item. (get blade would pick up the item)

   When an item is rekeyed, one of the words from the short description
     &GMUST&W be used in the rekey.

Rekey is included in the rename fee. See help glory for more information.
]],
  },
  {  
    keywords = {"REMAINS"},
    level = 65,
    type = "wizhelp",
    text = [[
Deity command.]],
  },
  {  
    keywords = {"REMOVE CURSE"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'remove curse' <character>

This spell removes a curse from a character. If you have a cursed object you
will need the spell BLESS OBJECT.
]],
  },
  {  
    keywords = {"REMOVE TRAP"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'remove trap' <object>

This spell will magically disarm a trap on an object.
]],
  },
  {  
    keywords = {"RENAME"},
    level = 1,
    type = "info",
    text = [[
A rename may be done by a level 54 or higher immortal..

Renames are to be medieval in style for mortals and must not contain
the name of an immortal without their expressed consent.  Items can be renamed
to whatever you want, pending Immortal approval.

Before contacting an immortal to redeem glory or scrolls for a rename,
please have in mind what you would like done.  You will need to consider
the following:

Short description - what is seen when the item is worn by a person.
Long description - what is seen when the item is lying on the ground.
Rekey - the renaming of the item (usually something from the short desc)
]],
  },
  {  
    keywords = {"RENT"},
    level = 1,
    type = "info",
    text = [[
Syntax: RENT ... characters never have to rent!

There is no RENT here.  Just SAVE and QUIT whenever you want to leave
the game.
]],
  },
  {  
    keywords = {"REPAIR"},
    level = 1,
    type = "command",
    text = [[
Syntax:   repair <object>
          repair all

Repair allows you to repair equipment and swords at metal blacksmiths,
and recharge staves and wands at magical 'blacksmiths.'  Repair all
attempts to repair every item in your inventory.

There is a 10% surcharge for using "repair all". This surcharge is for
the convenience of having all the equipment in your inventory repaired
at once.
]],
  },
  {  
    keywords = {"REPAIRSET"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax:  repairset <mobile vnum> <field> <value>

This command allows you to set the following fields for repair shops:

-----------------------------------------------
| Fields | Meaning                            |
-----------------------------------------------
| fix#   | Types of items the keeper will fix |
|        |  - armor, weapon, wand, staff      |
| profit | Profit on fixing items             |
| type   | Repair shop type                   |
|        |   type 1 = standard                |
|        |   type 2 = recharge                |
| open   | Hour shop opens                    |
| close  | Hour shop closes                   |
| keeper | Vnum of repair shop keeper         |
-----------------------------------------------
]],
    see_also = {"MAKEREPAIR", "REPAIRSTAT", "REPAIRSHOPS"},
  },
  {  
    keywords = {"REPAIRSHOPS"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: repairshops

Displays statistics on all the repair shops.
]],
    see_also = { "MAKEREPAIR", "REPAIRSET", "REPAIRSTAT"},
  },
  {  
    keywords = {"REPAIRSTAT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: repairstat <mobile vnum>

Shows statistics on a mobile's repair shop.
]],
    see_also = { "MAKEREPAIR", "REPAIRSET", "REPAIRSHOPS" },
  },
  {  
    keywords = {"REPEAT"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: repeat <letter>

This command will repeat tell messages which you
have already received. If no parameters are given
it will simply produce the last tell you received.
If a single letter is given, then the last tell
sent to you by a character with a name starting
with that letter will be displayed. This is an imm
only command.
]],
  },
  {  
    keywords = {"REPOP"},
    level = 1,
    type = "info",
    text = [[
Area resetting happens roughly every 3 minutes if there are no characters in
in the area; less often (20-60 minutes) if any characters are present.  Also
note that objects lying on the ground will not be regenerated if anyone
is in the area when it resets.

Area resets are indicated by 'squeaking noises' or other messages just prior
to the reset.
]],
  },
  {  
    keywords = {"REPORT", "TIME", "WEATHER", "DATE"},
    level = 1,
    type = "command",
    text = [[
Syntax: report
Syntax: time
Syntax: weather

REPORT shows your current statistics to you and also announces them to other
players in the room.

TIME shows the game time, as well as the time the mud was last started,
and the current local time for the host computer.  DATE does the same thing.

WEATHER shows the current game weather.  You must be in an outside room
to see the weather.
]],
  },
  {  
    keywords = {"RESERVE"},
    level = 51,
    type = "wizhelp",
    text = [[
The "Reserve" command enables us to specify certain names that are
reserved and cannot be used by players.

We can specify names that we want to reserve because they belong to
former imms (like Narn and Dominus). We can specify names that are
often tried and are a bit of a pain (like Killer or Satan or Seth).

We can specify parts of names by preceding the string with an "*">
e.g.  reserve *goof
This will prevent any name with the substring "goof" ... like ...
"goofface", "biggoof" or "biggoofface".
All deity names should be reserved.

reserve                        list current reserved names
reserve joe                    add joe to the list if he's not on it
reserve joe                    remove joe to the list if he is on it
reserve *goof                  add the substring "goof" to the list
]],
  },
  {  
    keywords = {"RESERVED"},
    level = 1,
    type = "info",
    text = [[
This is a placeholder for spell slots.  Don't worry about it.
]],
  },
  {  
    keywords = {"RESET"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: reset list   [start] [end]
Syntax: reset delete [number]
Syntax: reset add    <command> <parameters>
Syntax: reset insert <number> <command> <parameters>
Syntax: reset edit   <number> <command> <parameters>
Syntax: reset area   (will "reset" your area based on the defined resets)

WARNING:
  The order that resets are in is VERY important.  You cannot equip
  a mobile with an object before putting the mobile into a room first.
  Likewise, you cannot put an object into a container until the container is
  put into a room first.

This command is used to display, edit, delete, add and insert resets for
your area.
]],
    see_also = {"INSTAZONE", "RESETCMDS"},
  },
  {  
    keywords = {"RESETCMDS", "RESETCOMMANDS"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: reset edit   <number> <commands>
Syntax: reset insert <number> <commands>
Syntax: reset add    <commands>

Commands:
MOB   <mobile vnum> <room vnum> [limit]  loads a mobile into a room
OBJ   <object vnum> <room vnum> [limit]  loads an object into a room
GIVE  <object vnum> [limit]              gives object to last loaded mobile
EQUIP <object vnum> <position> [limit]   equips object on last loaded mobile
PUT   <object vnum> <object vnum>        puts and object into another object
DOOR  <room vnum> <door dir> <state>     resets a door to a certain state
RAND  <room vnum> <last door dir>        randomizes a range of exits
TRAP  <vnum> <type> <charges> <flags>    sets a trap
HIDE  <object vnum>                      hides an object

For EQUIP position, see WEARLOCS.
For DOOR door dir, see DOORDIRS.
For TRAP setting see TRAPSETTING.
]],
    see_also = {"resets"},
  },
  {  
    keywords = {"RESILIENCE"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c resilience <target>

Resilience renders the victim resistant to draining attacks.
]],
  },
  {  
    keywords = {"RESIST", "IMMUNE", "SUSCPET", "RESISTANCE", "IMMUNITY", "SUSCEPTIBLE"},
    level = 1,
    type = "info",
    text = [[
During the game it is possible to pick up resistances , immunities and
susceptibilities to various types of damage.  Immune means that type of damage
would do no damage to you whatsoever.

You can use the "Affected By" command to see what affects you are currently
under.

The R/I/S affects are also listed by a number under your score (if the # is
small enough to fit...they get pretty big (;  ).  The numbers correspond with
the affects as follows:

1 - fire          2 - cold           4 - electricity
8 - energy        16 - blunt         32 - pierce
64 - slash        128 - acid         256 - poison
512 - drain

As stated before there are more R/I/S affects, those are only the ones who's
numbers show up as +'s in your score.  "Affected By" is much more accurate and
detailed.
]],
  },
  {  
    keywords = {"REST", "SLEEP", "STAND", "WAKE"},
    level = 0,
    type = "command",
    text = [[
Syntax:  rest
Syntax:  sleep
Syntax:  stand
Syntax:  wake

These commands change your position.

When you REST or SLEEP, you regenerate hit points, mana points, and movement
points at a much faster rate.  However, you are more vulnerable to attack,
and if you SLEEP you won't hear many things happen. Be careful not to sleep
out in the open as you may be attacked by aggressive mobs that wander around
or other players if you are deadly. Sleeping or resting in or on a piece of 
furnature has an added benefit of faster regeneration.

Use STAND or WAKE to come back to a standing position.  You can also WAKE
other sleeping characters.
]],
    see_also = {"sleep spell"},
  },
  {  
    keywords = {"RESTORATION"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast restoration

This spell casts a mighty healing spell upon every member in a cleric's group,
and requires the combined power of two casters, both holding holy symbols.  It
is enough to restore most characters to at least 50% of their hitpoints.

]],
  },
  {  
    keywords = {"RESTORE"},
    level = 1,
    type = "command",
    text = [[
Syntax: restore <character>
        restore all

RESTORE restores full hit points, mana points, and movement points to the
target character.  RESTORE ALL does this for all mortals except player
killers and any who happen to be in the arena.

A note on RESTORE ALL: This is a gift from the gods, and it is never
planned in advance or done on request.  The best way to ensure that a
restore all will NOT be done is to ask for one.
]],
  },
  {  
    keywords = {"RESTORE MANA"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'restore mana' (target)

An interesting spell, this allows a magic-user to rebuild its store of mana.
By calling upon the power of the Realm itself, and spending some of their own
mana, magic power can be restored to another person.

]],
  },
  {  
    keywords = {"RESTORETIME"},
    level = 53,
    type = "wizhelp",
    text = [[
Restoretime shows you how much time has passed since you last did a
restore all. All Immortals between the levels of 53 and 56 can do one
restore all per 18 hours of Real Time. Those of level 57+ can restore
all at any given time, upon their discretion.
]],
  },
  {  
    keywords = {"RESTRICT"},
    level = 57,
    type = "wizhelp",
    text = [[
restrict <command>      -Displays the current level of the command.

Please remember to set the command back to its original level when you
are done with it. Some commands may not be restricted.
]],
  },
  {  
    keywords = {"RETELL"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: retell <message>

The command will send a message to the last character you replied to
or sent a tell to.
]],
  },
  {  
    keywords = {"RETIRE"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: retire <victim>

This command will set or remove the 'retired' flag on the immortal
you use it on.
]],
    see_also = {"RETIRED"},
  },
  {  
    keywords = {"RETIRED"},
    level = 1,
    type = "info",
    text = [[
Retired immortals are imms who are no longer very active at HoG.
They keep their level but are limited in their commands and authority
(equivalent to a level 51 immortal).  Retired imms are not involved in
the day to day running of the realms.

Retirement is only given to immortals who have reached level 53 or
higher and whose immship is in good standing.
]],
    see_also = {"GUESTS"},
  },
  {  
    keywords = {"RETRAN"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: retran <player>

This command will return that player or mob to the room from which
you last transferred it from.
]],
    see_also = {"transfer"},
  },
  {  
    keywords = {"REVERT"},
    level = 1,
    type = "command",
    text = [[
Syntax:  Revert

Revert is the command used to return to your original body from
the polymorphed state.
]],
    see_also = { "polymorph" },
  },
  {  
    keywords = {"RGRUB"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax:

RGRUB st n lo hi  -  list all room vnums between "lo" and "hi" that match
                     sectortype "n"

e.g.

RGRUB st 1 900 969  -  list all sectortype 1 rooms in Olympus
RGRUB st 3          -  list all sectortype 3 rooms in the whole mud

Please use this command with caution. If you're not careful ... you can
get 1,000 lines of output.
]],
  },
  {  
    keywords = {"RIGHTS"},
    level = 1,
    type = "info",
    text = [[
You have the right to remain silent or to hit the off button at any time.
]],
  },
  {  
    keywords = {"RINVOKE"},
    level = 55,
    type = "wizhelp",
    text = [[
Used with EQUIPMENT, MAGIC, or ARTIFACT, this command creates a random item.
]],
  },
  {  
    keywords = {"RIP"},
    level = 0,
    type = "info",
    text = [[
Syntax: rip <on/off>

The rip command will either enable or disable rip graphics.  Rip graphics
will only work provided you are using a rip compatible terminal program.
]],
  },
  {  
    keywords = {"RIS", "RESISTANT", "IMMUNE", "SUSCEPTIBLE"},
    level = 53,
    type = "wizhelp",
    text = [[
Players and mobiles may have resistance, susceptibility or immunity to
certain types of attack:

FIRE      COLD      ELECTRICITY  ENERGY     BLUNT     PIERCE     SLASH
ACID      POISON    DRAIN        SLEEP      CHARM     HOLD       NONMAGIC
PLUS1     PLUS2     PLUS3        PLUS4      PLUS5     PLUS6      MAGIC
PARALYSIS
]],
  },
  {  
    keywords = {"RLIST"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: rlist
      :	rlist <first room>
      :	rlist <first room> <last room>

This command will list all of the prototype rooms in your area, when used
with no arguments.  When used with a single argument it will list all
rooms including and after the argument, and when used with two arguments,
it will list all rooms including and between the two.
]],
  },
  {  
    keywords = {"RMENU"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: rmenu [menu letter] (defaults to 'a' if none given)

Rmenu will bring you into a menu system of editing rooms.  To use rmenu, you
must be in the room that you are editing.  To choose an option in the menu,
type the number of the section followed by the desired letter, and any
variables that may follow.

See MENU for generic menu commands.
]],
  },
  {  
    keywords = {"ROGUE"},
    level = 0,
    type = "class",
    text = [[
Tiered Class for Thieves, Thugs and Jesters.

Rogues are the master thieves, swordsman, and trouble makers of the realm.
Quick of wit, tongue, and sword, the rogue is both dangerous yet entertaining.
The rogue is the master of the unexecpted, often capable of throwing off even
the most observant of opponents. Because of their reliance on speed, rogues
can not use metal armor.

Their primary stat is Dexterity and Luck is their secondary with Strength as
their tertiary statistic.
]],
  },
  {  
    keywords = {"ROOMFLAGS"},
    level = 52,
    type = "wizhelp",
    text = [[
FLAG NAME     |  BITVECTOR  |  DESCRIPTION
----------------------------------------------------------------------
DARK          |          1  |  Room is always dark
DEATH         |          2  |  Room causes instant death
NOMOB         |          4  |  Mobs cannot wander into this room
INDOORS       |          8  |  Room is indoors - MUST also use sectortype 0
LAWFUL        |         16  |  Room is oriented to those of lawful alignment
NEUTRAL       |         32  |  Room is oriented to those of neutral alignment
CHAOTIC       |         64  |  Room is oriented to those of chaotic alignment
NOMAGIC       |        128  |  Magic cannot be used in this room
TUNNEL        |        256  |  Room is a tunnel - x number of players allowed
                               (use 'redit tunnel #' to  set the number)
PRIVATE       |        512  |  Room is private (restricted to 2 people)
SAFE          |       1024  |  Room is safe... no violence allowed
SOLITARY      |       2048  |  Room is solitary (restricted to 1 person)
PETSHOP       |       4096  |  Petshop (next vnum must be the storeroom)
NORECALL      |       8192  |  Players cannot recall out of this room
DONATION      |      16384  |  Donation room... cannot get all
NODROPALL     |      32768  |  Cannot drop all in this room
SILENCE       |      65536  |  Not a sound can be made or heard in this room
LOGSPEECH     |     131072  |  All speech in this room is logged
NODROP        |     262144  |  Nothing can be dropped in this room
CLANSTOREROOM |     524288  |  Clan storage room
NOSUMMON      |    1048576  |  Player cannot be summoned out of this room
NOASTRAL      |    2097152  |  People cannot astral to this room
TELEPORT      |    4194304  |  People in this room will be teleported out
TELESHOWDESC  |    8388608  |  Players will see the room desc of the dest room
NOFLOOR       |   16777216  |  Room has no floor: exit down + no fly = fall
PROTOTYPE     | 1073741824  |  Room is a prototype, (under construction)
NOMISSILE
]],
  },
  {  
    keywords = {"ROOMTRIGGERS", "RPTRIGGERS"},
    level = 51,
    type = "wizhelp",
    text = [[
Trigger Optnl Triggering Variable Explanation
------- ----- ------------------- -----------
Act      {p}  <keyword / phrase>  [emotes, socials, actions, bamfs]
Speech   {p}  <keyword / phrase>  [says or tells from within the room]
Rand          <percentage>        [randomly triggered based on percentile]
Sleep         <percentage>        [when a player sleep within the room]
Rest          <percentage>        [when a player rests within the room]
Entry         <percentage>        [when a mob/player enters the room]
Fight         <percentage>        [when a player is fighting in the room]
Death         <percentage>        [when a player dies in the room]
Leave         <percentage>        [when a player leaves the room]
Time          <hour>              [script prog, runs once on hour specified]
Hour          <hour>              [loops as Script for an hour from start hour]

*NOTE* {hour}/<hour> is in military time. ie, 15 hours is 3p.m. mud time.
*NOTE* The mpcommand MPDONOTHING currently only works in Script progs,
       NOT in Time or Hour progs.
]],
    see_also = { "RPSTAT", "RPEDIT", "TRIGGER", "RPCOMMANDS", "IFCHECKS", "VARIABLES" },
  },
  {  
    keywords = {"ROSMUD", "REALM OF SHADOWS", "ROS"},
    level = 1,
    type = "info",
    text = [[
Realm of Shadows was the MUD that got me back into mudding (:  Its great ideas
and help from Syriac and the other Immortal RoS Staff helped HoG get moving in
the beginning.  Unfortunately now gone, some of its ideas live on in HoG.

The special magical flags, Following's having money for Temple enhancements,
and other code changes, plus a few of the areas that made up the Realm...I
give thanks to all the authors of these things and the players that were my
companions at RoS.

--Drazuk
]],
  },
  {  
    keywords = {"ROSTER"},
    level = 1,
    type = "command",
    text = [[
Syntax: roster 'following name'

This command shows a roster of who belongs to a certain Following.  It is
updated whenever a member logs on, is inducted, or is outcast.  Members of a
Following that haven't logged on since this command was implemented will not
show up in the rosters.

This command can also be used by an Immortal to remove a name from the roster,
but the preferred way is to use outcast, which should do the same thing.
]],
  },
  {  
    keywords = {"ROUNDHOUSE"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  roundhouse

Roundhouse is a skill which can only be used once a fight has started,
and can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"RPEDIT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax:  rpedit <command> [number]  [program] [arguments]
Syntax:  rpedit add       <program> <arguments>
Syntax:  rpedit insert    <number>  <program> <arguments>
Syntax:  rpedit edit      <number>  [program] [arguments]
Syntax:  rpedit delete    <number>
Syntax:  rpedit list

Add, insert and edit will put you into the line editor to edit your
program.  The arguments consist of a trigger, plus any arguments
associated with that trigger.

To edit a roomprogram you must be in the room.
]],
    see_also = { "RPSTAT", "TRIGGER", "RPTRIGGERS", "RPCOMMANDS", "IFCHECKS", "IFCHECKS2", "VARIABLES" },
  },
  {  
    keywords = {"RPFIND"},
    level = 65,
    type = "wizhelp",
    text = [[
.  for room progs that contain an occurrence of text.
   Display a maximum of n lines.

rpfind n mud text
   Search all the rooms in the mud for
   room progs that contain an occurrence of text.
   Display a maximum of n lines.

Example:
rpfind 20 901 969 if isnpc
   Search all room progs in Olympus (vnums 901 thru 969)
   and display all vnums that contain the text "if isnpc".
   Display a maximum of 20 lines.

Example:
rpfind 100 mud mpslay
   Search all room progs in the entire mud
   and display all vnums that contain the text "mpslay".
   Display a maximum of 100 lines.
]],
  },
  {  
    keywords = {"RPSTAT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax:  rpstat

Rpstat will display all of the roomprograms that have been written for a
room.  You must be standing in the room that you are rpstatting (though
you can also use 'rpstat' in conjunction with the 'at' command to rpstat
a room remotely).
]],
    see_also = { "RPEDIT", "TRIGGER", "RPTRIGGERS", "RPCOMMANDS", "IFCHECKS", "IFCHECKS2", "VARIABLES"},
  },
  {  
    keywords = {"RSET", "RRESET"},
    level = 65,
    type = "wizhelp",
    text = [[
Room commands.]],
  },
  {  
    keywords = {"RUN"},
    level = 1,
    type = "command",
    text = [[
Syntax : run (direction) (#)

RUN is used to run as many rooms in certain direction at once, until
stopped by a door or the end of the road (hall, tunnel, whatever).
You can optionally add a number argument at the end if you only want
to move a a few rooms.  There is a slight pause while you catch your
breath at the end of a long run, so be careful when trying to outrun
an angry foe!
]],
  },
  {  
    keywords = {"RWHO"},
    level = 1,
    type = "command",
    text = [[
Syntax: rwho

This does a quick check of characters and mobs in the room with you, and sends
back their names.  This is nice to use when there is a mob in the room and you
aren't sure what the keyword is to interact with them.
]],
  },
  {  
    keywords = {"SACRAL DIVINITY"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c 'sacral divinity'

The prayer of an adventurer for personal sanctuary to its deity, made
over the clasped symbol of that person.  It is said that never will
the prayer be heard should it be uttered by the unworthy.
]],
  },
  {  
    keywords = {"SACRIFICE"},
    level = 1,
    type = "command",
    text = [[
Syntax:  sacrifice <object>
         sacrifice all

Sacrifice offers an object to the gods, or to your deity.
The gods may reward you for the sacrifice, and the nature of the reward
depends upon the type of object. 

The 'sacrifice all' command will sacrifice everyting in the room all at
once and will give you a combined reward all at once.
]],
  },
  {  
    keywords = {"SAGACITY"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast sagacity (target)

This spell increases your wisdom for its duration.
]],
  },
  {  
    keywords = {"APPLY", "SALVE", "OINTMENT"},
    level = 0,
    type = "command",
    text = [[
In your travels you may come across various ointments and salves.
Use 'apply <itemname>' to rub some of the salve onto your skin.

]],
  },
  {  
    keywords = {"SAVE"},
    level = 1,
    type = "command",
    text = [[
Syntax:  Save

SAVE saves your character and its inventory; you must be at least second
level to save.  The system automatically saves approximately one character
every minute. You should not rely on auto-save to keep your character 
updated -- save frequently.

Type SAVE immediately after recovering your corpse, gaining experience or
a level in battle, getting new items, making purchases or repairs, etc.

Some objects (such as keys) may not be saved. Every character is auto-saved
at reboot.
]],
  },
  {  
    keywords = {"POSITIONS"},
    level = 1,
    type = "info",
    text = [[
At current time, there are 14 "positions" in the game. Positions
are in a special order.  If position b is below position a on the
list, that indicates that while in position b, you have more
physical or mental energy to spend on a task, be it a command,
a spell, or a skill.

For example, while standing, you have a greater ability to do things
than while sitting.  While fighting evasively, you have more options
than while fighting aggressively.

The ordered list is as follows, left to right, top to bottom:
Dead          Mortally Wounded        Incapacitated
Stunned       Sleeping                Fighting (Berserk)
Resting       Fighting (Aggressive)   Sitting
Fighting (Std)Fighting (Defensive)    Fighting (Evasive)
Standing      Mounted
]],
    see_also = { "STYLES" },
  },
  {  
    keywords = {"SAVEAREA", "LOADAREA"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: savearea
        loadarea

Savearea and loadarea will save or load your prototype area.
]],
  },
  {  
    keywords = {"SAVINGTHROWS"},
    level = 53,
    type = "wizhelp",
    text = [[
Saving throws:
  sav1 - Saving vs. damage
  sav2 - Saving vs. wands
  sav3 - Saving vs. paralysis or petrification
  sav4 - Saving vs. breath
  sav5 - Saving vs. spells or staves
]],
    see_also = {"mset"},
  },
  {  
    keywords = {"SCAN"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  scan <direction>

This skill enables you to scan for one or more rooms in the direction
specified, dependent on the percent to which the skill is practiced,
and the type of area you are in.
]],
  },
  {  
    keywords = {"SCATTER"},
    level = 65,
    type = "wizhelp",
    text = [[
Toss a character about the MUD.
]],
  },
  {  
    keywords = {"SCORCHING SURGE"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c 'scorching surge' <victim>

A powerful wave of heat created by an mage and directed at its victim.
The spell inflicts fire damage on the target, the higher the level of the
mage the greater the damage.

]],
  },
  {  
    keywords = {"SCORE"},
    level = 1,
    type = "command",
    text = [[
Syntax: score

SCORE is a sheet filled with your characters statistics.  When you type
score, only you can see what is listed there.  Should you want to let
others see your characters health, you can type REPORT.

To get a breakdown of what each slot in your score means, read section 4
in your Adventurer's Guide book.
]],
    see_also = {"SCOREQP", "SCOREPK", "SCOREGOLD", "SCOREMOBM", "SCOREMK", "SCORESP", "SCOREMP", "SCOREXP"},
  },
  {  
    keywords = {"SCOREQP", "SCOREPK", "SCOREGOLD", "SCOREMOBM", "SCOREMK", "SCORESP", "SCOREMP", "SCOREXP", "TOP20"},
    level = 1,
    type = "command",
    text = [[
Syntax:  scoreqp    <--- Top 20 Questors
         scorepk    <--- Top 20 Player Killers
         scoremk    <--- Top 20 Mob Killers
         scoregold  <--- Top 20 Richest Players
         scoremobm  <--- Top 20 Mob Masters
         scoresp    <--- Top 20 Skill Questors
         scoremp    <--- Top 20 Magic Questors
         scorexp    <--- Top 20 Most Experienced

These commands let you see the Top 20 players for several categories.  See if
you can get your name on the lists!
]],
  },
  {  
    keywords = {"SCRIBE", "BREW"},
    level = 0,
    type = "skill",
    text = [[
&YSyntax&W: brew <spell name>
&YSyntax&W: scribe <spell name>

A mage or cleric of sufficient level holding a 'blank scroll or
'empty flask' may transform them into spelled scrolls or potions via
the scribe and brew commands.

It takes significantly more mana to bind a spell to a potion or scroll
than to simply cast it.

Note that a fire is required to brew potions.
]],
  },
  {  
    keywords = {"SCRUTINIZE"},
    level = 1,
    type = "skill",
    text = [[
syntax:  scrutinize

Some more advanced thieves in the realm have grasped the basic concepts
underling the "auralink" of the Mages, and by concentrating (quite hard), they
can bring themselves to see the power levels of magical items.  Note that they
also need to detect a magical aura in the first place for this to work
correctly.
]],
  },
  {  
    keywords = {"SCRY"},
    level = 0,
    type = "spell",
    text = [[
Syntax:  cast scry

This spell will allow the character to scry (look) in to nearby rooms.
After casting the spell, the character needs only to "look" in the
desired direction.

Thieves have an innate ability to scry.
]],
  },
  {  
    keywords = {"SEAELF", "SEA-ELF", "SEA-ELVES", "SEAELVES", "SEA ELF"},
    level = -1,
    type = "race",
    text = [[
Also called Aquatic Elves, they are akin to mermen as land elves are
akin to men.  Found almost exclusively among heavy weed beds in quiet,
sheltered, salty waters, they are great friends of the dolphins.  The
race historically prefers to fashion caverns in lagoon bottoms and
reefs in which to live and work, but the reality of the today's Realms
has forced them into the general populace.

The race is humanoid in appearance, with gill slits on the throat and
greenish-silver skin and green or blue-green hair.  Sea elves have an
inate ability to notice magical auras as well as breath under water.
They are resistant to the colds of the deep, but fire harms them.

Sea-elves receive 93% of the normal experience award.

Sea-elves can be a Mage, Cleric, Thief, Warrior, Druid, Ranger, Monk,
Conjurer or Jester.
]],
  },
  {  
    keywords = {"SEARCH"},
    level = 0,
    type = "skill",
    text = [[
Syntax: search
Syntax: search <container>

Sometimes not all there is to find is in clear view.  Some things may be
concealed or hidden, and will require some searching to find.]],
  },
  {  
    keywords = {"SECOND ATTACK", "THIRD ATTACK", "FOURTH ATTACK", "FIFTH ATTACK"},
    level = 1,
    type = "skill",
    text = [[
These are powerful skills which allow a character to attack more than
once per combat round.  Use of these skills is automatic once you have
practiced them.

While you can practice the attacks out of turn (third attack before you
have mastered second attack, for example), it is extremely inefficient
to do so.]],
  },
  {  
    keywords = {"SECTORTYPES"},
    level = 52,
    type = "wizhelp",
    text = [[
INSIDE              0
CITY                1
FIELD               2
FOREST              3
HILLS               4
MOUNTAIN            5
WATER_SWIM          6
WATER_NOSWIM        7
UNDERWATER          8
AIR                 9
DESERT             10
UNKNOWN            11
OCEANFLOOR         12
UNDERGROUND        13
]],
  },
  {  
    keywords = {"SEDIT"},
    level = 51,
    type = "wizhelp",
    text = [[
View, create, edit or delete socials online.
Syntax:  sedit <social>
Syntax:  sedit <social> [field]
Syntax:  sedit <social> create
Syntax:  sedit <social> delete
Syntax:  sedit <save>

Use sedit <social> to view the current settings of an existing social.
Use sedit <social> [field] to set one of the fields:
  CNoArg: response to character if no argument given
  ONoArg: response to room if no argument given
  CFound: Response to character if target is someone else
  OFound: Response to room if target is someone else
  VFound: Response to target if target is someone else
  CAuto : Response to character if target is self
  OAuto : Response to room if target is self

Variables you can use are:
  $n - Name of the user of the social.
  $N - Name of the target of the social.
  $m - him/her/it for the user the social.
  $M - him/her/it for the target of the social.
  $s - his/her/its for the user of the social.
  $S - his/her/its for the target of the social.
  $e - he/she/it for the user of the social.
  $E - he/she/it for the target of the social.

Use sedit <social> create to create a new social, then edit with sedit field.
Use sedit <social> delete to delete an existing social.
Use sedit save to save the new social or changes to existing socials.
]],
  },
  {  
    keywords = {"SETBOOT"},
    level = 57,
    type = "wizhelp",
    text = [[
Syntax: setboot time <hour> <minute>
 	setboot manual <0|1>

The setboot command is useful for planning a reboot, (to save you from
the trouble of all those echos :) ) and for the daily boot.  The manual
bit is used by the mud to determine whether the boot time was set by
hand.  When the mud starts up, the boot time is set to 0600hrs (6am)
and the manual bit to 0.  If 'setboot time' is used, the mud sets the
manual bit to 1.  When it comes time to do the reboot, the mud checks
how long it has been running.  If it has been running less than 18
hours and the reboot time has not been set manually, the reboot does
not take place (nor do the automatic warning echoes).

Echoes: when a scheduled reboot is coming up, the mud will send out
echoes to that effect.  The echoes start 30 minutes before the reboot
and are repeated at t minus 15, 10, 5, 4, 3, 2 and 1 minute(s).
]],
  },
  {  
    keywords = {"SETCOUNCIL"},
    level = 65,
    type = "wizhelp",
    text = [[
For creating a Council.
]],
  },
  {  
    keywords = {"SETDEITY"},
    level = 65,
    type = "wizhelp",
    text = [[
Sets up deities.
]],
  },
  {  
    keywords = {"SETFOL"},
    level = 55,
    type = "wizhelp",
    text = [[
Usage: setfol <following> <field> <deity|leader|number1|number2> <player>
Field being one of:
 deity leader number1 number2
 members board recall storage guard1 guard2
 align (not functional) memlimit obj1 obj2 obj3 obj4 obj5
 name filename motto desc
 favor strikes type class
 pkill1-7 pdeath1-7
ex: to set a new person in the number 1 spot of guild of warriors..
setfol 'guild of warriors' number1 <name>
]],
  },
  {  
    keywords = {"SETMIXTURE", "SETLIQUID"},
    level = 55,
    type = "wizhelp",
    text = [[
Both used to create liquids and mixtures online.  Use the commands for more
info.
]],
  },
  {  
    keywords = {"SETQUEST"},
    level = 54,
    type = "wizhelp",
    text = [[
Used to set a quest on a character. for a MOB or and OBJect.  Just type
SETQUEST to see the options.  Nice to use for Following quests if you want.
]],
  },
  {  
    keywords = {"SETRACE"},
    level = 51,
    type = "info",
    text = [[
&wSyntax: Setrace <racename> <field>

Setrace &g<name> &wwill name your newly created race
Setrace <name> &gsave&w will save the creation and changes.

Setrace <name> &g<language> &wdetermines the races native language.
Field &gclasses&w  will set the allowed classes. IE.. setrace elf classes
cleric paladin would allow those classes for the race. This is a toggle feature
that will disallow the same classes if repeated.

Field(s) &gstrplus dexplus wisplus intplus conplus chaplus lckplus &w apply
the set modifier to the race.(setrace elf str 2 gives elves +2 bonus to str).
Setrace <race> &ghit &wor &gmana  &wwill determine the amnt of hps or mana
gained by leveling. Example: Setrace drow hit 5 would yield a 5pnt hp gain with
each level.

Setrace &galign &wdetermines the alignment default for the race.
(Setrace mage align 500 sets the mage default alignment to 500)

Setrace <racename> &g minalign&w/&gmaxalign &w sets min and maxs  from
 -1000  to 1000 to determine if a penalty will be applied.  If the max align is
500 - character would suffer a mental state penalty for straying above 500.
]],
    see_also = {"showrace", "setrace2"},
  },
  {  
    keywords = {"SETRACE2"},
    level = 51,
    type = "wizhelp",
    text = [[
.&W
.&w
&wSetrace racename &gaffected /attack/resist/suscept/defense&w are similar
to msetting mobs. Setrace elf affected resist poison would make the race
resistant to poison attacks

Setrace <racename> &gheight/weight &w<value> do not have  affects..yet.

Setrace with a field of  &ghungermod/thirstmod &w will determine the rate of
thirst or hunger  is affected by upon each round.

Setrace  <racename> &gexpmultiplier &w determines the rate of experience
acquired from leveling, adepting or successfully using skills and spells .
Example: If a race with an experience modifier of 80 , the race would gain 80 %
of the exp.that a human would by having completed the same task.

Setrace <racename> &gacplus &w <variable> sets the armor class for the race
without any equipment or spells. See also &ghelp AC &w

Setrace <race> <save>
&gsaving_poison,death,saving_wand,saving_,para_petri,saving_breath,
saving_spell_staff &wwill modify the races saving throw capabilities.
]],
    see_also = {"showrace", "setrace1" },
  },
  {  
    keywords = {"SETSLAY"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: setslay <type> <field> <value>

This command allows you to set the options on a slay type.

<Type> is the command argument for the SLAY command, and identifies which
slay you will be editing.

Field can be one of the following:

Owner - The person who owns this option. Setting owner to 'any' means any
        immortal with access to SLAY can use it.
Color - Numerical value for the color of the messages sent.
        For now, use color 12 until a better method for setting colors
        can be found.
Cmessage - You will be put into the line editor to enter the message the
           user of the SLAY command will see.
Vmessage - You will be put into the line editor to enter the message the
           victim will see when slain.
Rmessage - You will be put into the line editor to enter the message the
           rest of the people in the room will see when someone is slain.

The slay editor uses the same variables as the social editor and the
mudprograms. See SEDIT.
]],
    see_also = { "SHOWSLAY", "MAKESLAY", "DESTROYSLAY", "SLAY" },
  },
  {  
    keywords = {"SETWEATHER", "SHOWWEATHER"},
    level = 61,
    type = "wizhelp",
    text = [[
See and control the weather down to the zone.
]],
  },
  {  
    keywords = {"SHADOWFORM"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast shadowform

Entering Shadowform makes you almost untouchable by non-magical attacks,
at no cost to your attributes.
]],
  },
  {  
    keywords = {"SHAMAN", "SHAMANS"},
    level = 0,
    type = "class",
    text = [[
Shamans are the witch-doctors and voodoo priests of the more tribal races.
While they lack the refined magic of the cleric or conjurer, they can invoke
the natural spirits of the world.  Gifted with the ability to speak to
spirits, they can invoke powerful raw energies that can aid them in almost any
way.  From boosting their natural abilities to protecting them from danger, a
shaman is also an important member of the a tribe, offering rare and powerful
beneficial spells and potions.  Shamans can also wreak havoc upon their
enemies by channeling the natural energies of the world into a mighty spell.


Their primary stat is wisdom, their secondary is is dex, and their tertiary is
con.

The races of Human, Half-elf, Half-ogre, Half-orc, Half-troll, Ghoul, Goblin,
Wolfen, Minotaur and Lizardman are allowed to be shamans.
]],
  },
  {  
    keywords = {"SHARPEN"},
    level = 1,
    type = "skill",
    text = [[
Syntax: sharpen (object)

Characters with this skill and a sharpening stone (purchasable at your local
weapon shop) can put a superior edge on a bladed weapon.  This can only be
done once to a weapon.  A sharpening stone gets used up a little bit each time
it is used.  The sharpness depends on the level of the character.

]],
  },
  {  
    keywords = {"SHELTER THE WEAK"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'shelter the weak'
        cast shelter

By using a holy symbol to commune with their god, clerics are able to grant
health and mana back to a target, even in the heat of combat.  While they can
also cast this spell on themselves, the mana cost of the spell outweighs the
mana they would regain.
]],
  },
  {  
    keywords = {"SHIELD", "STONE SKIN"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast shield
Syntax: cast 'stone skin'

These spells protect the caster by decreasing (improving) the caster's armor
class.  SHIELD provides 30 points of armor.  STONE SKIN provides 60 points of
armor.
]],
  },
  {  
    keywords = {"SHOCKING GRASP"},
    level = 1,
    type = "spell",
    text = [[
This spell allows the caster to deliver a powerful electric shock to a single
enemy.
]],
  },
  {  
    keywords = {"SHOPS"},
    level = 53,
    type = "info",
    text = [[
Syntax: shops

Displays statistics on all the shops.
]],
    see_also = { "MAKESHOP", "SHOPSET", "SHOPSTAT"},
  },
  {  
    keywords = {"SHOPSET"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: shopset <mobile vnum> <field> <value>

-----------------------------------------------
| Fields | Meaning                            |
-----------------------------------------------
| buy#   | Types of items the keeper will buy |
| buy    | Profit on buying items             |
| sell   | Profit on selling items            |
| open   | Hour shop opens                    |
| close  | Hour shop closes                   |
| keeper | Vnum of shop keeper                |
-----------------------------------------------

Lets you set certain stats on a shop.
]],
    see_also = { "MAKESHOP", "SHOPSTAT", "SHOPS", "SHOPVALUES" }
  },
  {  
    keywords = {"SHOPSTAT"},
    level = 53,
    type = "wizhelp",
    text = [[
Syntax: shopstat <mobile vnum>

Shows statistics on a mobile's shop.
]],
    see_also = { "MAKESHOP", "SHOPSET", "SHOPS" },
  },
  {  
    keywords = {"SHOPVALUES"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: shopset <mobile vnum> buy# <value>

1  - light               21 - pen                41 - rune
2  - scroll              22 - boat               42 - runepouch
3  - wand                23 - corpse             43 - match
4  - staff               24 - corpse_pc          44 - trap
5  - weapon              25 - fountain           45 - map
6  - _fireweapon         26 - pill               46 - portal
7  - _missile            27 - blood              47 - paper
8  - treasure            28 - bloodstain         48 - tinder
9  - armor               29 - scraps             49 - lockpick
10 - potion              30 - pipe               50 - spike
11 - _worn               31 - herbcon            51 - disease
12 - furniture           32 - herb               52 - oil
13 - trash               33 - incense            53 - fuel
14 - _oldtrap            34 - fire               54 - shortbow
15 - container           35 - book               55 - longbow
16 - _note               36 - switch             56 - crossbow
17 - drinkcon            37 - lever              57 - projectile
18 - key                 38 - pullchain          58 - quiver
19 - food                39 - button             59 - shovel
20 - money               40 - dial               60 - salve
]],
  },
  {  
    keywords = {"SHOULDER"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  shoulder

Shoulder is a skill which can only be used once a fight has started,
and can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"SHOVE"},
    level = 1,
    type = "command",
    text = [[
Syntax:  shove <character> <direction>

Characters can shove other characters in the direction
specified if the victim is standing up.

Characters who have been in a safe room for longer than 30 seconds
will be unable to be shoved or dragged out of that room until they
either leave of their own choice or they shove/drag another player.

]],
  },
  {  
    keywords = {"SHOWBOARDS"},
    level = 52,
    type = "wizhelp",
    text = [[
Get a listing of the different boards created, including vnum, level stats for
read/write/etc., and posts.
]],
  },
  {  
    keywords = {"SHOWCLASS", "SETCLASS"},
    level = 56,
    type = "wizhelp",
    text = [[
Used to check and create new character classes.]],
  },
  {  
    keywords = {"SHOWCOUNCIL"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: showcouncil '<name> council'

Shows the statistics on the council.
]],
  },
  {  
    keywords = {"SHOWDEITY"},
    level = 65,
    type = "wizhelp",
    text = [[
Show which deities are setup.  Not the same as Following deities!
]],
  },
  {  
    keywords = {"SHOWFOL"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: showfol <following>

Displays statistics on a following.
]],
  },
  {  
    keywords = {"SHOWGUILD"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: showguild 'guild of <guild name>'

Displays the statistics on a guild.
]],
  },
  {  
    keywords = {"SHOWLAYERS"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: showlayers <number of lines>

Example: showlayers 100   (lists a maximum of 100 lines)

This command is used by builders to show all equipment in the game
that is layerable.

It is used by builders to help decide what eq should be made layerable
and what kind of stats to give the eq.

We don't want players to be able to wear 10 pieces of eq on the same
wear location and get huge stats as a result.
]],
  },
  {  
    keywords = {"SHOWORDER"},
    level = 65,
    type = "wizhelp",
    text = [[
Used to see which Orders exist.
]],
  },
  {  
    keywords = {"SHOWRACE"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: Showrace <name of race>

This will give vital statistics on pc races. IE.. showrace lizardmen
would net the following:

Disallowed Classes:Mage Cleric Thief Vampire Druid Augurer
Paladin Nephandi
Allowed Classes:Warrior Ranger
Str Plus: 002   Dex Plus: -003  Wis Plus: -006  Int Plus: -006
Con Plus: 002   Cha Plus: -002  Lck Plus: -004
Hit Pts:  002   Mana: 000       Align:0 AC: 0
Min Align:  -1000       Max Align: 500  XP Mult:91%
Height:  78 in. Weight: 215 lbs.         HungerMod: 0    ThirstMod: 0
Affected by:aqua_breath
Resistant to:slash
Susceptible to:
Saves: (P/D) 0 (W) 0 (P/P) 0 (B) 0 (S/S) 0
Innate Attacks:tail
Innate Defenses:

See also help &WSETRACE
&w
]],
  },
  {  
    keywords = {"SHOWSLAY"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: showslay <type>

This command shows the current settings for the selected slaytype.

The slaytype is the command argument for the SLAY command.
The owner is the person who can use the option, owner 'any' means any
immortal with access to slay can use it.
The color is the numerical value for the color of the messages.
Cmessage is what the user sees when they slay someone.
Vmessage is what the victim sees when slain.
Rmessage is what everyone else in the rooms sees.

The slay editor uses the same variables as the social editor and the
mudprograms. See VARIABLES.

An example listing:

Slaytype: demon
Owner:    Any
Color:    12
Cmessage:
You gesture, and a slavering demon appears.
With a horrible grin, the foul creature turns on
$N, who screams in panic before being eaten alive!

Vmessage:
$n gestures, and a slavering demon appears.
The foul creature turns on you with a horrible grin.
You scream in panic before being eaten alive!

Rmessage:
$n gestures, and a slavering demon appears.
With a horrible grin, the foul creature turns on
$N, who screams in panic before being eaten alive!
]],
    see_also = { "MAKESLAY", "DESTROYSLAY", "SETSLAY", "SLAY" },
  },
  {  
    keywords = {"SHRIEK"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  shriek

An undead wail which may be used to wither the life of all who hear
its anguished sound.
]],
  },
  {  
    keywords = {"SILVER ARROW"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'silver arrow' victim

One of the weaker attack spells available to a conjurer, this spell allows
them to summon up a silver arrow, and send it streaking towards their foes for
a bit of damage!  Silver arrow requires one charge from a silver orb.
]],
  },
  {  
    keywords = {"SIT"},
    level = 0,
    type = "info",
    text = [[
Syntax: sit

Sit makes your character sit down.
]],
  },
  {  
    keywords = {"SLAY", "SLA"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: slay <victim> [option]

SLAY kills a character in cold blood, no saving throw.

To see the current list of options, type slay with no argument.

Slay bypasses auto actions such as autoloot and autosac.  Slay should not
be used to test death_programs on mobs, as it is not the same as an actual
death to the mobile and may not return accurate results.

Slay types can now be edited online for easier configuration of
personalized options.
]],
    see_also = { "MAKESLAY", "DESTROYSLAY", "SETSLAY", "SHOWSLAY" },
  },
  {  
    keywords = {"SLEARN"},
    level = 1,
    type = "command",
    text = [[
Syntax: slearn skill/spell
Example:  slearn fireball    <-- shows which classes can learn fireball

"SLEARN" is a nifty command that shows which classes can learn a certain spell
or skill, what level they learn it at, and how high they can practice it.
]],
  },
  {  
    keywords = {"SLEEP SPELL"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast sleep <victim>

This spell can put the victim to sleep, making them oblivious to what is going
on around them for a short time.  Attacking a sleeping character will cause
them to wake up right away, but that first swing has a chance to hit them for
extra damage.
]],
  },
  {  
    keywords = {"SLICE"},
    level = 1,
    type = "skill",
    text = [[
Syntax: slice corpse

Using a sharp weapon, this skill allows a user to cut pieces of meat from the
corpse of their foes.  This is a handy skill when traveling alone throughout
the realms.
]],
  },
  {  
    keywords = {"SLINK"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast slink

This spell makes you more dexterous for its duration.  Useful for getting into
and out of tight places.
]],
  },
  {  
    keywords = {"SLIST"},
    level = 1,
    type = "command",
    text = [[
Syntax:  slist
Syntax:  slist <low level> <high level>

SLIST without an argument gives you a complete list of the spells and skills
available to your class, also indicating the maximum level to which you can
practice each.

SLIST <low level> <high level> gives a list of spells and skills available
to your class from the low level to the high level specified.

Example:  slist 2 2

    SPELL && SKILL LIST
    ------------------
    Level 2
      skill :                mount   Current:  75 Max: 85

]],
  },
  {  
    keywords = {"SLOOKUP"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: slookup <skill-or-spell>
Syntax: slookup all

SLOOKUP shows you the internal 'sn' and external 'slot' for the given skill
or spell.  The 'sn' is used for OSET and OSTAT.  The 'slot' is used for area
files.  Neither 'sn' nor 'slot' is used for player files; these operate with
the actual skill and spell names.

SLOOKUP ALL shows this information for all skills and spells.
]],
  },
  {  
    keywords = {"SMAUG", "THORIC"},
    level = -1,
    type = "info",
    text = [[
.                               [WWW.SMAUG.ORG]
         /     _      _            _      _    _____
        /      |\    /|     /\     |      |   /     \     ***************
       /       | \  / |    /  \    |      |  |            *   \\._.//   *
      /        |  \/  |   /    \   |      |  |            *   (0...0)   *
     /_______  |      |  |______|  |      |  |            *    ).:.(    *
            /  |      |  |      |  |      |  |            *    {o o}    *
           /   |      |  |      |  |      |  |     __     *   / ", " \   *
          /    |      |  |      |  |      |  |       |    *-'^.VxvxV.^'-*
         /     |      |  |      |   \____/    \_____/     ***************
        /
            [S]imulated [M]edieval multi-[U]ser [A]dventure [G]ame

SMAUG 1.4 is a Merc2.1 derivative written by Thoric (Derek Snider) with help
from Altrag, Blodkai, Haus, Narn, Scryn, Swordbearer, Tricops, Gorog, Rennard,
Grishnakh, Fireblade and Nivek.
]],
  },
  {  
    keywords = {"SMAUGSPELLS"},
    level = 56,
    type = "wizhelp",
    text = [[
SMAUG has a specially coded spell type "spell_smaug", which is a generic
spell handler that uses the extra spell fields to determine what the spell
is going to achieve.

damtype   the class of damage done (see DAMTYPES)
acttype   the action of the spell (see ACTTYPES)
classtype the class of spell (see CLASSTYPES)
powertype the power ranking of the spell (see POWERTYPES)
flag      special extra flags this spell has (see SPELLFLAGS)
hit       Message displayed when spell is successful
miss      Message displayed when spell misses or fails
die       Message sent if spell causes death
imm       Message sent if victim is immune
(Messages must specify char, vict or room, ie: hitchar, hitvict, hitroom)
dice      a dice formula used for rolling things like damage (see DICEFORMULAS)
saves     saving throw victim gets (see SPELLSAVES)
bitvector see AFFECTED_BY, the bitvector applied by the spell, if any
affects   see AFFECTTYPES, the effect the spell has, if any
value     an extra field reserved for things like the vnum used in spells
          that create objects, or summon monsters to the caster's aid.

]],
  },
  {  
    keywords = {"SMOKE"},
    level = 1,
    type = "command",
    text = [[
You may 'smoke' a pipe after first filling it with a smokable herb or
tobacco.
]],
  },
  {  
    keywords = {"SOBER"},
    level = 51,
    type = "wizhelp",
    text = [[
syntax 'Sober <player>'
This command can be used to Sober a player or your self when they/you
are in a drunken state.

]],
  },
  {  
    keywords = {"SOCIAL"},
    level = 51,
    type = "wizhelp",
    text = [[
The following information is needed to create a social:
Use sedit <social> [field] to set one of the fields:
  CNoArg: response to character if no argument given
  ONoArg: response to room if no argument given
  CFound: Response to character if target is someone else
  OFound: Response to room if target is someone else
  VFound: Response to target if target is someone else
  CAuto : Response to character if target is self
  OAuto : Response to room if target is self
Variables you can use are:
  $n - Name of the user of the social.
  $N - Name of the target of the social.
  $m - him/her/it for the user the social.
  $M - him/her/it for the target of the social.
  $s - his/her/its for the user of the social.
  $S - his/her/its for the targt of the social.
  $e - he/she/it for the user of the social.
  $E - he/she/it for the target of the social.

]],
  },
  {  
    keywords = {"SOLAR FLIGHT"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c 'solar flight' <victim>

This spell allows the caster to merge from an outdoor area to their victim
in an outdoor area.

The spell has a few restrictions:  you will only succeed in casting it
during daytime hours, between 5 A.M. and 8 P.M. and you will only succeed
in casting if both you and your victim are in an outdoor area -- you need
to also have a holy symbol to channel the power this spell requires!
]],
  },
  {  
    keywords = {"SOLOMONIC INVOCATION"},
    level = 55,
    type = "spell",
    text = [[
Syntax:  c 'solomonic invocation'

This creates an item, was the paladins holy symbol spell...might put something
else here instead (:
]],
  },
  {  
    keywords = {"SONIC RESONANCE"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'sonic resonance' (victim)

The magick of 'Sonic Resonance' allows the casting druid to realign
the component particles of his foe in such a way that they are
susceptible to a certain mystical tone.  By the completion of the
spell, this tone is conjured, causing the particles to vibrate
violently causing intense pain and tissue damage.
]],
  },
  {  
    keywords = {"SPAM"},
    level = 1,
    type = "info",
    text = [[
No, we are not talking about a luncheon meat here.  Spam is the repeated use
of a phrase, command, or channel that causes screen scroll for others.  Not
only is spam considered rude, but excessive screen scroll can interfere with
the game play of anyone seeing it (not to mention combat situations).  The
game will also tell you to PUT A LID ON IT and force-quit you after the 20th
repeat of a single command

It is also considered spam to use the same phrase over several different
channels.  The use of all-caps can also be considered spam.  Only use
capitals to add emphasis to key words in a sentence.

Moving a large number of items into and out of a container in a crowded,
non-store room is considered spam.  Using multiple characters to chat the
same message at the same time is considered spam.  Making charmed mobs
or pets to cause screen scroll through movement or orders is considered
spam. ANYTHING that causes excessive or irritating screen scroll can be
considered spam.
]],
  },
  {  
    keywords = {"SPEAK", "LANGUAGE"},
    level = 1,
    type = "command",
    text = [[
Syntax:  speak
Syntax:  speak <language>
Syntax:  speak all (immortals only)

The speak command changes the current language in which you are speaking.
To speak your native tongue, type 'speak' alone.  To speak a specific
language (such as common, for example), type "speak common".

Immortals have the unique ability to speak so that everyone can understand,
by typing "speak all".

See also Languages
]],
  },
  {  
    keywords = {"SPECFUNCS"},
    level = 53,
    type = "wizhelp",
    text = [[
These special functions are available to assign to mobiles.
Use them sparingly:

To add spec:  mset <mob> spec <function> (ex. mset guard spec spec_guard)
To remove:    mset <mob> spec none

spec_breath_any          Mobiles breathes one of the four breaths randomly.
spec_breath_acid         Mobile has breath of acid.
spec_breath_fire         Mobile has breath of fire.
spec_breath_frost        Mobile has breath of frost
spec_breath_gas          Mobile has gas breath.
spec_breath_lightning    Mobile has lightning breath.
spec_cast_adept          Mobile casts helpful spells.
spec_cast_cleric         Mobile casts healing spells.
spec_cast_mage           Mobile casts offensive spells during battle.
spec_cast_undead         Mobile casts offensive spells during battle.
spec_guard               Mobile attacks KILLERS and THIEVES.
spec_executioner         Same as above except summons guards to help.
spec_fido                Mobile eats corpses.
spec_janitor             Mobile picks up trash.
spec_mayor               Reserved for the mayor... don't use.
spec_poison              Mobile poisons during battle.
spec_thief               Mobile steals gold from players.
]],
  },
  {  
    keywords = {"SPECTRAL FUROR", "HAND OF CHAOS"},
    level = 1,
    type = "spell",
    text = [[
After the Dark Mage Thanatos accidentally discovered the spell
'Disruption' in a failed attempt to create a teleportation magic,
he spent many years studying how to increase the pain that can
be inflicted by incorrectly moving a victim across the threshold
of dimensions.

 'Spectral Furor' is a formula which, by upsetting the very nature
of the space the victim inhabits causes neural as well as brute
physical damage.

With 'Hand of Chaos,' Thanatos perfected this line of magic, and he
returned to his researches on the art of astral travel.
]],
  },
  {  
    keywords = {"SPELLCOMPONENTS"},
    level = 56,
    type = "wizhelp",
    text = [[
T###         check for item of type ###
V#####       check for item of vnum #####
Kword        check for item with keyword 'word'
G####        check if player has at least #### amount of gold
H####        check if player has at least #### amount of hitpoints
M####        check if player has at least #### amount of moves
W##          check if player is wearing item in ## position (see WEARPOS)

Special operators:
/ fail if percent is not greater than ### (use with H or M only)
\ fail if percent is not less than ### (use with H or M only)
- consume ### percent (use with H or M only)

+ don't consume this component
@ decrease component's value[0], and extract if it reaches 0
# decrease component's value[1], and extract if it reaches 0
$ decrease component's value[2], and extract if it reaches 0
% decrease component's value[3], and extract if it reaches 0
^^ decrease component's value[4], and extract if it reaches 0
&& decrease component's value[5], and extract if it reaches 0
and ! will make the spell fail if the caster is carrying that component.

Example: V1100 V+1101
The spell will only succeed if the caster is carrying objects of vnums
1100 and 1101.  The object of vnum 1100 will get consumed by the spell,
and the object of vnum 1101 will not.

With the decremental operators (@#$%^^&&), the object must have at least
a value of 1 in the respective location for the spell to succeed.

]],
  },
  {  
    keywords = {"SPELLFLAGS"},
    level = 56,
    type = "wizhelp",
    text = [[
water           water based (create water, ice spells)
earth           interacts with nature (earthquake)
air             involve the air or winds
astral          involve the astral plane (astral walk)
area            an "area spell"... affects everyone in the room
distant         affects something far away
reverse         has a reverse affect
save_half_dam   victim can save for half damage
save_negates    victim can save for no effect
accumulative    can be cast repeatedly to have an increased effect
recastable      can be cast again to refresh the spell
nobrew          cannot be brewed into a potion
noscribe        cannot be scribed onto a scroll
group           affects everyone in the caster's group (same room only)
object          specifically affects an object (for target 'ignore')
character       specifically affect a character (for target 'ignore')
pksensitive     affects target as if they were double your level
nonverbal       allows spell to be cast even if caster is mute
noclass         this spell is not assigned to class in particular
]],
  },
  {  
    keywords = {"SPELLSAVES"},
    level = 56,
    type = "wizhelp",
    text = [[
Here are the saving throws you can set for use in SMAUG spells:
none            victim doesn't get a saving throw
poison_death    save vs. poison or death
wands           save vs. wands
para_petri      save vs. paralysis or petrification
breath          save vs. (dragon) breath
spell_staff     save vs. spells or staves

]],
  },
  {  
    keywords = {"SPINKICK"},
    level = 1,
    type = "skill",
    text = [[
Syntax: Spinkick (victim)

To lift one's foot, spin to gain momentum, and kick your opponent.
]],
  },
  {  
    keywords = {"SPIRAL BLAST"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c 'spiral blast'
Abbrev:  c spiral

A powerful, spinning blast of colored gas, this mighty spell attacks
every enemy target in the area.  The spell is hostile to all creatures in
the room, and will cause them to engage the caster in combat.]],
  },
  {  
    keywords = {"SPIRIT ARMOR"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'spirit armor'

Shaman can call upon the spirits of battle, and they will swarm around him,
helping to block incoming blows in combat.  The battle spirits are fickle
however, and won't stay around for a very long time, so the shaman should
always have a backup plan in place.
]],
  },
  {  
    keywords = {"SPIRIT SHIELD"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'spirit shield'

A shaman can call upon the spirits to form a damage absorbing shield around
them, protecting them from any damage received in combat.  When the spirits
have absorbed a certain amount of damage, they will disappear and leave the
shaman to fend for themselves.  The number of spirits called depends on the
level of the shaman.
]],
  },
  {  
    keywords = {"SPIRIT TRADE"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'spirit trade'

Shaman sometimes find themselves in a bad situation and in the need of health
right away.  They can call upon the spirits for a boost in health, but at the
cost of their magical energy and movement.  Shaman should be careful for they
may trade enough that they have health, but no movement left to fight
effectively!
]],
  },
  {  
    keywords = {"SPIRIT WRACK"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'spirit wrack' victim

The shamans main attack spell, this wracks the very spirit of their enemy
causing much pain.  As the shaman grows in power, so does this spell.  An
avatar shaman can kill his foes with just a few spirit wracks!
]],
  },
  {  
    keywords = {"SPIRITUAL WRATH"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'spiritual wrath'

Spiritual Wrath sends a blast of blinding light at all targets in the
room, sweeping their souls with Chaos and death.  The caster needs to be
holding a heart of a previous foe for this spell to work.  The damage is
dependant on the power of the casters mind.

]],
  },
  {  
    keywords = {"SPLIT"},
    level = 0,
    type = "command",
    text = [[
Syntax: SPLIT <amount>

SPLIT splits some gold between you and all the members of your
group who are in the same room as you.  It's customary to SPLIT
the gold after a kill.
]],
  },
  {  
    keywords = {"SPOUSETALK"},
    level = 1,
    type = "command",
    text = [[
Syntax: spousetalk (msg)

Sends a message to your spouse.  Only you and them can hear this channel,
although snooping Gods can also pick up chat.  On that note, Immortals,
"snoop" isn't to be used for casual eavesdropping, please (:
]],
  },
  {  
    keywords = {"SPURN"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  spurn

Spurn is a skill which can only be used on your primary target. If it
successfully lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"SSET"},
    level = 60,
    type = "wizhelp",
    text = [[
Syntax: sset <victim> <skill> <value>
or:     sset <victim> all     <value>
or:     sset <sn>     <field> <value>

name          the name of the skill or spell
code          for spells, the code executed when the spell is cast
target        for spells, the target of the spell (see TARGETTYPES)
minpos        the minimum position required to use this skill/spell
slot          for spells, the slot number used in area files
mana          for spells, the amount of mana consumed by the spell
beats         how long this skill takes to be used (in 1/4 seconds)
flag          for setting flags for this skill (see SPELLFLAGS)
dammsg        a word to describe the damage done by this skill or spell
wearoff       for spells, the message given when the spell wears off
type          the type of skill (Spell, Skill, Weapon, Tongue)
difficulty    how difficult the spell/skill is to learn and/or use
damtype       for spells, the class of damage it does
components    the components required for this spell (see SPELLCOMPONENTS)
teachers      will restrict the teaching of this skill to these mob vnums
participants  the minimum number of required participants (for spells)

For the special fields used by SMAUG spells (spell_smaug) see SMAUGSPELLS
]],
    see_also = {"SSET2"},
  },
  {  
    keywords = {"STALK"},
    level = 1,
    type = "skill",
    text = [[
syntax: stalk (victim)

A skilled tracker can stalk their victim, sometimes following a trail straight
to their target!  This skill depends on both stalk and track skills to work
effectively.
]],
  },
  {  
    keywords = {"STANDARD", "STANDARD STYLE"},
    level = 1,
    type = "command",
    text = [[
Syntax: style standard

This style is both a balance of offense and defense, giving neither a
fighter nor his enemy an advantage in battle.
]],
    see_also = { "style", "evasive", "defensive", "standard", "aggressive", "berserk"},
  },
  {  
    keywords = {"STAT"},
    level = 1,
    type = "command",
    text = [[
Syntax:  stat

Displays to the character its basic stats and attributes in
brief form.
]],
    see_also = { "statreport", "score", "oldscore", "worth" },
  },
  {  
    keywords = {"STATREPORT"},
    level = 1,
    type = "command",
    text = [[
Syntax:  statreport

Displays a brief summary of a character's basic stats and
attributes to everyone present.
]],
    see_also = { "stat", "score", "oldscore", "worth" },
  },
  {  
    keywords = {"STEAL"},
    level = 0,
    type = "skill",
    text = [[
Syntax: STEAL coins <character>
Syntax: STEAL <object> <character>

STEAL attempts to steal coins, or an object, from a mob or another player.

There could be penalties for using STEAL on other players.
]],
  },
  {  
    keywords = {"STING"},
    level = 1,
    type = "skill",
    text = [[
Some creatures use their natural weapons in combat.  Some creatures have sharp
spines or tails, and can sting you with them!
]],
  },
  {  
    keywords = {"STR", "STRENGTH"},
    level = 1,
    type = "info",
    text = [[
Strength (STR in your 'score') represents your character's physical power.

The most common concern with strength deals with how much your character
can carry.  For each additional point of strength  you gain an additional
amount of maximum carryable weight.  Any character with 20 strength can
carry 500kgs; Warriors and Rangers can have a maximum of 25 strength, and
can therefore carry up to 999kgs when their strength is at its maximum.

Strength also affects (among other things):

 - damage roll and hitroll; for each additional point of strength, each
   of these will increase

 - chances of success for bash, stun, bashdoor, shove and drag, and the
   ability to dual-wield heavier weapons
]],
  },
  {  
    keywords = {"STREW"},
    level = 65,
    type = "wizhelp",
    text = [[
Supposed to scatter items, sends them all to one room right now :/
]],
  },
  {  
    keywords = {"STRIKE"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  strike

Strike is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"STRIP"},
    level = 61,
    type = "wizhelp",
    text = [[
Syntax 'strip <victim>

Silently transfers their entire inventory and clothing to yours.
]],
  },
  {  
    keywords = {"STUN"},
    level = 0,
    type = "skill",
    text = [[
Syntax: stun <mob>

Stun is a skill which can only be used once a fight has started.  It will
stun your opponent if successful.
]],
  },
  {  
    keywords = {"STYLE", "STYLES", "STANCE", "STANCES"},
    level = 1,
    type = "skill",
    text = [[
Usage: style <style name>

Styles, when effectively used, can change the tide of battle. The more
experienced one is in a particular style, the better the chances that it
will work for the fighter's advantage. There are five different known
styles. Styles can be changed within combat to better ones advantage
and knowledge of each of the different forms of combat.

See help files on AGGRESSIVE, BERSERK, DEFENSIVE, EVASIVE, STANDARD.


]],
  },
  {  
    keywords = {"SULFUROUS SPRAY"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'sulfurous spray' (victim)

With the incantation 'Sulfurous Spray,' the casting mage culls from
the air the elements necessary to form a strong acid which rains
down upon his opponent or opponents.  This strength and velocity
of the spray is such that it can work its way into various forms
of armor and clothing, and it is also able to harm opponents one
might think resistant to such attacks, due to its magical nature.
]],
  },
  {  
    keywords = {"SUMMARY"},
    level = 0,
    type = "info",
    text = [[
.           &B
|----------------------------------|----------------------------------|
|&C              MOVEMENT&B            |&C               GROUP              &B|
|&Cnorth east south west northeast up&B|&C follow group gtell ; split       &B|
|&Cnorthwest southeast southwest down&B|----------------------------------|
|&Csomewhere open close lock unlock  &B|&C           INFORMATION            &B|
|&Cleave enter climb fly float look  &B|&Cdeath CR reimb rules damage areas &B|
|&Cwhere scan scry sleep wake stand  &B|&Ccommands experience score title   &B|
|&Crest sit&B |------------------------|&Cweather channels description story&B|
|---------|&C CONFIG OPTIONS         &B|&Cwho report tick password typo note&B|
|&Cautoloot autogold autoexit autosac&B|&Cwizlist MOTD news bug weapons mail&B|
|&Cnice flee norecall ansi blank rip &B|&Ctime slist report languages spells&B|
|&Cnointro prompt telnetga shovedrag &B|&Cskills idea&B |---------------------|
|&Ccombine&B  |------------------------|------------|&C COMBAT              &B|
|---------|&C    OBJECTS             &B|&Ckill flee wimpy rescue aid murder &B|
|&Cget put drop give sacrifice recite&B|&Ccast&B |----------------------------|
|&Csay tell chat question answer yell&B|-----|&C     COMMUNICATION          &B|
|&Cwield wear remove inventory list  &B|&Csocial quest clan ordertalk newbie&B|
|&Cappraise buy sell compare examine &B|&Cavatar counciltalk guildtalk shout&B|
|&Chold quaff zap brandish equipment &B|&Csay tell chat question answer yell&B|
|&Cempty fill eat drink pick value   &B|&Cauction&B  |------------------------|
|----------------------------------|----------|
To use the help menu, just type "help <topic>".
To see help on individual areas, you can now type "help <full area name>".
If you are new to the Realms, type HELP NEW to see a special help series.
]],
    see_also = { "!", "SAVE", "QUIT", "PAGELENGTH", "PRACTICE"},
  },
  {  
    keywords = {"SUMMON GOLEM"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'summon golem'

Conjurers can create giant golems to help them in combat.  While initially
somewhat weak, the conjurer has a number of spells that will create powerful
equipment they can order the golem to wear.  Conjurers should be sure to group
their golems to receive the full benefit.  Golems require one charge from some
pine sap, some iron shavings, some diamond dust, some gold flakes, and some
ruby powder.
]],
  },
  {  
    keywords = {"SUMMON", "SUMMONING"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast summon <target>

Summon will bring your target to you. There are some exception for summon not
to work. It cannot summon targets from no-astral or safe rooms and some flags
upon the target may prevent them from being summoned.

Be considerate with summon. Do not summon aggressive mobs into areas where
newbies frequently roam. If you are deadly, do not summon a non-deadly player
unless it is requested. If you are non-deadly, the same applies, do not summon
a deadly character unless it is requested of you.
]],
  },
  {  
    keywords = {"SUPPLICATE"},
    level = 65,
    type = "wizhelp",
    text = [[
For deity use.]],
  },
  {  
    keywords = {"SWAT"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  swat
Swat is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"SWIPE"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  swipe

Swipe is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"SWITCH", "RETURN"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: switch <character>
Syntax: return

SWITCH switches you into the body of another character (who must not
already have a descriptor, e.g. you can't switch into a PC).

RETURN returns you to your original body.
]],
  },
  {  
    keywords = {"SWORDBAIT"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast swordbait (victim)

This spell makes the victim more susceptible to slashing attacks.]],
  },
  {  
    keywords = {"TAIL"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  tail

Tail is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"TAINT"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast taint

Certain casters enjoy the use of acid-type spells more than others.  Those
casters have perfected a spell that causes the victim to become more
susceptible to those spells, and also to the blunt weapons they are trained in
using.
]],
  },
  {  
    keywords = {"TAMP"},
    level = 1,
    type = "command",
    text = [[
Syntax:  tamp <pipe>

This empties your pipe so that you may fill it with fresh herbs.

]],
  },
  {  
    keywords = {"TARGETTYPES"},
    level = 55,
    type = "wizhelp",
    text = [[
Target                Function
--------------------------------------------------------------------
ignore                Spell affect relies on the casting argument
offensive             Spell will initiate combat
defensive             Can be cast on anyone safely
self                  Spell only affects the caster
objinv                Cast onto an object in the caster's inventory

]],
  },
  {  
    keywords = {"TELEPORT"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast teleport

This spell takes you from your current location to a random location somewhere
in the world.  As the energies involved are difficult to control, there is no
sure way of determining your destination.  Therefore, caution and planning
should be in the forefront when considering whether to use this spell.
This spell may not work in all locations...so be careful!

Teleport is a non-verbal spell.
]],
  },
  {  
    keywords = {"TELESCAPE"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c telescape

A powerful but costly (in mana) spell, telescape will allow the caster
to remove themselves from bad situations, even from areas that don't
normally allow astral travel.  The drawback, besides the mana cost, is
the caster may also land in areas that usually block astral travel...
which can sometimes land the caster into an even worse situation!
]],
  },
  {  
    keywords = {"TEMPLECOSTS", "FOLLOWINGCOSTS"},
    level = 1,
    type = "info",
    text = [[
Worshippers of the various Gods and Goddess of the Realms have the ability to
donate money to the Following, using the "fdeposit" command.  What is this
money good for?  Well for starters, how about this?

Stable              5000000
--Mount, Normal     100000
--Mount, Magical    250000

Warroom	            5000000
--Warboard          100000
--Table/Chairs	    150000
--Guard	            200000

Healer Room         6500000
--Bed	            100000
--Healer            10000 x Lvl

Practice Room       4000000
--Guildmaster	    150000
--Table/Chairs	    100000

Scholar Room	    4000000
--Guildmaster	    25000 x Langs
--Table/Chairs	    100000

Throne Room         7500000
--Throne            250000
--Chairs            200000
--Decorations	    150000

Resting Room	    5000000
--Bed	            200000
--Chairs            150000

Lounge	            5000000
--Bed	            200000
--Table/Chairs	    250000
--Bartender         100000 x Objects

Temple	            6500000
--Altar	            500000
--Bed	            200000

Arena	            5000000
--Combat Dummy	    200000
--Stands            250000

Misc Items:
Fountain            50000
Portal (Somewhere)  2000000
Locked Doors/Keys   50000
Special Rooms	    5000000+

Beds are any type of object that allows sleeping or resting upon.  Chairs
allow a character to sit.  Other items may grant other benefits.  Talk to
Darwin about upgrading and purchasing.
]],
  },
  {  
    keywords = {"TEMPLEENHANCE"},
    level = 1,
    type = "info",
    text = [[
A list of enhancement for Temples will be here soon.

Suggestions on what to offer are welcomed.
]],
    see_also = {"TEMPLECOSTS"},
  },
  {  
    keywords = {"TEND"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  tend <target>
         tend
The well-traveled adventurer will normally learn the techniques necessary
to mend the wounds of himself or others.  This is the greatest mending
ability in the characters's repertoire, though due to its nature it can
not be used while in combat.]],
  },
  {  
    keywords = {"THE SOUTHERN ROAD", "SOUTHERN ROAD"},
    level = 1,
    type = "info",
    text = [[
Heading south out of Drazukville is a well-built road that travels all the way
to the ocean.  Passing through the grassy plains and warm sand dunes, bandits
creep about, hoping to waylay other travelers.  Many merchants travel the
Southern Road, from the south ports to Drazukville.
]],
  },
  {  
    keywords = {"THIEF", "THIEVES"},
    level = 0,
    type = "class",
    text = [[
The thief is a dark character which makes use of many skills often deemed
improper by the rest of society. Known to haunt the darkest roads and
alleys. The skills of the thief reflect his way of life, be it sneaking,
peeking into others' inventories, picking locks, or attacking from behind
with deadly backstabs. With amazing dexterity they have the ability to
circle around an enemy, but for living such a dark life, thieves have
always had a bad reputation so don't be surprised if you are always under
suspicion. Thieves start off fairly weak, but as they gain skills such as
backstab and circle they soon become dangerous foes.  A thief is always
useful when there is  a lock that needs pryed, or an item that one wishes
to acquire without detection.

Dexterity is of course the thieves prime attribute, and luck is their
second.  Intelligence is the thieves tertiary statistic.

The races of Human, Dwarf, Elf, Halfing, Pixie, Half-elf, Half-ogre, Half-orc,
Half-troll, Gith, Sea-elf, Drow, Gnome, Ghoul, Goblin, Wolfen, Minotaur, and
Lizardman are allowed to be thieves.
]],
  },
  {  
    keywords = {"THINK"},
    level = 56,
    type = "command",
    text = [[
Syntax: think <message>

Think is an immortal channel.
]],
  },
  {  
    keywords = {"THROUGH THE IRONKORES", "IRONKORES"},
    level = 1,
    type = "info",
    text = [[
Dwarves from the Ironkore mountains east of Drazukville forged their way down
from their kingdom to carve a pass into the mighty rock.  They're hope was to
get merchants and adventurers to come to their city, realizing that
interaction was needed to survive.  Reports of giants and other
mountain-dwelling creatures have been overheard on many a long drinking night
at the inn.
]],
  },
  {  
    keywords = {"THUG", "THUGS"},
    level = 0,
    type = "class",
    text = [[
Not quite the sneakiness of a thief and not quite the strength in
combat of a warrior, the thug is that adventurer who learned from the
school of hard knocks instead of the Guilds.  His thieving skills
are not quite as honed as a true Guilded thief, but they are there
when he needs them. Thugs are limited to two-handed weapons, prefering the weight and heft of the larger swords, axes and polearms.

With some formidable combat skills, including the ability to circle
behind their opponent in the chaos of combat, inflicting massive damage,
they can hold their own in a brawl.  Due to their unique raising on
the streets, thugs don't learn from teachers or guildmasters as well
as the more "educated" classes.  Thats OK with the thug...he'll just
mug those book-learned fools one night in an alley.

Strength is the thugs prime attribute, and dexterity is the
second.  Charisma is the thugs tertiary statistic.

The races of Human, Dwarf, Elf, Half-elf, Half-ogre, Half-orc, Half-troll,
Gith, Drow, Ghoul, Goblin, Minotaur and Wolfen are allowed to be thugs.
]],
  },
  {  
    keywords = {"TICK"},
    level = 0,
    type = "info",
    text = [[
Many of the actions in the Realms are based upon interval timers, including
combat, most autonomous monster actions, hp/mana/move regeneration, spell
duration, weather, and area resetting.

Of these timers, the hp/mana/move regeneration timer is popularly called the
'tick'.  Ticks in these Realms average 60 seconds of real time, but the
actual amount varies randomly from 45 seconds to 75 seconds.

Area resetting happens roughly every 3 minutes if there are no characters in
in the area; less often (15 minutes) if any characters are present; Also,
some lower level areas have shorter reset periods, while some higher level
areas have longer reset periods.

Note that objects lying on the ground will not be regenerated if anyone is
in the area when it resets.

Area resets are indicated by 'squeaking noises' or other messages just prior
to the reset itself.

]],
  },
  {  
    keywords = {"TIER", "TIERED", "TIERED CLASSES"},
    level = 0,
    type = "info",
    text = [[
Tiered classes are a way for single class characters to prove themselves the
masters of their adventuring world.  Upon reaching level 50, a single-class
character can use the "advancetier" command to reset their level back down to
level 2, and become a more advanced version of their class.

Warriors, Monks and Rangers switch to Champion.
Clerics and Diabolists switch to Bishop.
Thieves, Thugs and Jesters switch to Rogue.
Mages, Druids and Conjurers switch to Archmagi.

Once tiered, the character has a tremendous amount of work to do to actually
advance in their level, but they will have access to all the skills the lower
classes have.  So a Champion will get the same skills as a Warrior, a Ranger,
and a Monk...obviously a powerful thing (:

Dual-Classing will gain you different sets of skills...you can have a
fighter-type class and a priest-type class, for instance.  This can be
powerful in its own right, so is not to be overlooked.
]],
  },
  {  
    keywords = {"TIGER"},
    level = 1,
    type = "skill",
    text = [[
Syntax: tiger

A combat style representing the powerful tiger, the tiger master has vicious
attacks and a strong defense.  In addition, the user has the added ability to
resist damage from both magical and nonmagical attacks.
]],
  },
  {  
    keywords = {"TIMECMD"},
    level = 65,
    type = "wizhelp",
    text = [[
Syntax: timecmd <command>

This will execute the command and will output how long the command took to
process. This may be helpful in locating laggy commands.
]],
  },
  {  
    keywords = {"TIMER"},
    level = 51,
    type = "wizhelp",
    text = [[
31 to 40                "is lying here."
23 to 30                "is buzzing with flies."
15 to 22                "fills the air with a foul stench."
07 to 14                "is crawling with vermin."
01 to 06                "is in the last stages of decay."

Since a corpse now lasts from 40 to 60 minutes, we are requested to wait
until the corpse has reached below a timer of 23 or has hit the
"fills the air with a foul stench." stage in decay.

You can see what stage of decay a corpse is in by either typing:
ostat <player name>       (i.e. ostat Brittany)    OR
at 'corpse <name>' look   (i.e. at 'corpse Brittany' look)
]],
    see_also = {"corpse", "imm cr", "bodybag" },
  },
  {  
    keywords = {"TITLE"},
    level = 0,
    type = "command",
    text = [[
Syntax:  title <string>

This command allows you to set your title the text of your choice.  The
game supplies a title when your character is created and each time you
advance a level.

*  Must be level five or higher to use title
** Titles are subject to the same guidelines for use of language as channels

]],
  },
  {  
    keywords = {"TONGUES"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'tongues' victim

Sometimes in an adventurer's journey, they run across someone who speaks a
language they don't understand.  Many magical creatures have their own
languages, that no teacher exists for.  This spell allows the recipient to
understand any language, no matter who speaks it.
]],
  },
  {  
    keywords = {"TOPICS"},
    level = 1,
    type = "info",
    text = [[
Additional topics you may want to look over:
*TICK
*WIZLIST
*EXPERIENCE
*EQDAMAGE
*CLANS
*CHANGES
*DAMAGE
*NEWS
*STORY

To view a topic type: HELP <topic>
]],
  },
  {  
    keywords = {"TORRENT"},
    level = 1,
    type = "spell",
    text = [[
The Druids of the Realm have perfected the art of summoning lightning from the
heavens.  This spell allows them to call multiple lightning strikes down upon
the heads of their victims.  This is primarily used for shockshields.
]],
  },
  {  
    keywords = {"TRACK"},
    level = 0,
    type = "skill",
    text = [[
Syntax: track <mob>

Track will assist you in tracking down a mob that is within the area,
giving you its general direction.  It is vital to have a good track skill if
you plan to stalk.
]],
  },
  {  
    keywords = {"TRAFFIC"},
    level = 1,
    type = "command",
    text = [[
Syntax:  traffic <message>

Traffic is akin to the old auction channel, meaning it is a
simple channel on which to offer to buy or sell whatever it is
you wish to buy or sell.

Please do not spam other channels with offers to buy or sell
goods.  Use the traffic channel.

Avatar traffic is seen only by avatars, and non-avatars see
only non-avatar traffic.  Immortals on the channel see and
are seen by all.


Traffic is for the exchange of equipment, not for discussion.
]],
    see_also = { "AUCTION" },
  },
  {  
    keywords = {"TRAIN"},
    level = 0,
    type = "command",
    text = [[
Certain mobs will help you raise your attributes if you spend a lot of
glory and practices.  You can only raise your attributes to 18 maximum, so
if you are already above 18, then you cannot train them further.

Just find one of the trainer mobs wandering the realm and "TRAIN" when you
are standing at them.
]],
  },
  {  
    keywords = {"TRANCE"},
    level = 1,
    type = "skill",
    text = [[
Syntax: trance

A character in possession of this skill may use it to briefly focus its
energies toward restoring a small burst of mana.
]],
  },
  {  
    keywords = {"TRANSFER"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: transfer <character>
Syntax: transfer all
Syntax: transfer <character> <location>
Syntax: transfer all         <location>

TRANSFER transfers the target character, or ALL player characters,
to your current location (default) or to a specified location.
]],
  },
  {  
    keywords = {"TRANSPORT"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast 'transport' <object> <victim>

'Transport' sends an object in the caster's inventory to the victim.  Useful
for sending recall potions and identifies to someone out in the field.
]],
  },
  {  
    keywords = {"TRAPFLAGS"},
    level = 53,
    type = "wizhelp",
    text = [[
Flags to describe a trap and what triggers it:

ROOM    - Trap is in a room
OBJ     - Trap is on an object
ENTER   - Trap is triggered by entering the room
LEAVE   - Trap is triggered by leaving the room
OPEN    - Trap is triggered by opening
CLOSE   - Trap is triggered by closing
GET     - Trap is triggered by getting the object
PUT     - Trap is triggered by putting the object
EXAMINE - Trap is triggered by examining the object
PICK    - Trap is triggered by picking the object
UNLOCK  - Trap is triggered by unlocking the object
NORTH   - Trap is triggered by moving north
SOUTH   - Trap is triggered by moving south
EAST    - Trap is triggered by moving east
WEST    - Trap is triggered by moving west
UP      - Trap is triggered by moving up
DOWN    - Trap is triggered by moving down

See RESET, TRAPSETTING and TRAPTYPES.
]],
  },
  {  
    keywords = {"TRAPSETTING"},
    level = 52,
    type = "wizhelp",
    text = [[
Setting a trap is a little tricky.

Parameters: <vnum> <type> <charges> <flags>
VNUM    - The vnum of either the room or object to be trapped.
TYPE    - The type of trap.  (See TRAPTYPES)
CHARGES - The number of charges this trap should contain.
FLAGS   - Flags specifying the characteristics of the trap.
          (ie: room trap or object trap, what triggers the trap, etc.)

See RESETS, TRAPTYPES and TRAPFLAGS.
]],
  },
  {  
    keywords = {"TRAPTYPES"},
    level = 52,
    type = "wizhelp",
    text = [[
Types of traps:

 --------------------------------------------------------------------
 | Number | Description             | Number | Description          |
 --------------------------------------------------------------------
 |    1   | Poison gas              |    8   | Flame                |
 |    2   | Poison dart             |    9   | Explosion            |
 |    3   | Poison needle           |   10   | Acid Spray           |
 |    4   | Poison dagger           |   11   | Electric Shock       |
 |    5   | Poison arrow            |   12   | Blade                |
 |    6   | Blindness gas           |   13   | Sex change spell     |
 |    7   | Sleeping gas            |        |                      |
 --------------------------------------------------------------------

See RESET, TRAPSETTING and TRAPFLAGS.
]],
  },
  {  
    keywords = {"TRIGGER"},
    level = 53,
    type = "wizhelp",
    text = [[
A trigger is an action, phrase, or game event that causes a program
held within a room, mob or object, to begin playing out its commands.

Triggers can be anything from a player or mob entering a room, to a
player stating a particular phrase within a room, or to a mob or an
object.

For detailed information on triggers, see:

RPTRIGGERS, MPTRIGGERS, OPTRIGGERS
]],
  },
  {  
    keywords = {"TROLLISH VIGOR"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'trollish vigor' (target)

This spell increases your stamina during its duration, but makes you a little less pretty.
]],
  },
  {  
    keywords = {"TRUESIGHT", "TRUE SIGHT"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  cast truesight
Syntax:  c true

True sight is a combination of infravision (enabling you to see in the dark),
detect invisible, detect magic, and detect hidden.  This spell also allows you
to see through blinding attacks.]],
  },
  {  
    keywords = {"TRUST"},
    level = 60,
    type = "wizhelp",
    text = [[
Syntax: trust <character> <level>

TRUST sets a character's trust to the specified level.  This is similar to
advancing the character for accessing immortal commands, but has no effect
on combat strength, et cetera.  You can give more trust to mortal (or
immortal) characters to give them access to more power without messing up
the character.  You can also restrict a player's trust to less than their
natural level.

A trust of 0 means to use the character's natural level again.
]],
  },
  {  
    keywords = {"TSR", "D&D", "AD&D"},
    level = -1,
    type = "info",
    text = [[
.               Dungeons && Dragons (tm) and TSR Hobbies Inc.

  Here we'd like to duplicate the original credits from the Basic Rules,
Dungeons && Dragons (tm), (c) 1974, 1977, 1978, 1981, 1983 TSR Hobbies Inc.

Acknowledgements:
The following individuals have made this work possible through its years of
evolution: Dave Arneson, Brian Blume, Dave Cook, Anne C. Gray, Ernie Gygax,
E. Gary Gygax, Allen Hammack, Kevin Hendryx, John Eric Holmes, Harrold
Johnston, Tim Kask, Jeff Key, Rob Kuntz, Alan Lucien, Steve Marsh, Tom
Moldvay, Mike Mornard, Jon Pickens, Brian Pitzer, Michael Price, Patrick L.
Price, Paul Reiche, Evan Robinson, Gordon Schick, Lawrence Schick, Don Snow,
Edward G. Sollers, Garry Spiegle, Stephen D. Sullivan, Ralph Wagner, Jim
Ward, Jean Wells, Bill Wilkerson, Donald Paterson, and Frank Mentzer.

      DIKUMud's concepts were directly based on TSR's D&&D concepts.
]],
  },
  {  
    keywords = {"TUMBLE"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  operates independently

Tumble is a high-level thief skill for the evasion of incoming attacks.
The skill functions automatically, and its effectiveness is greater for
more dexterous thieves.
]],
  },
  {  
    keywords = {"UNFOLDAREA"},
    level = 59,
    type = "wizhelp",
    text = [[
Syntax:  unfoldarea <area filename>

This command will load up an area file.

NOTE:  It could be quite dangerous to unfold an area that is already
       loaded, or one that has not been tested.

]],
  },
  {  
    keywords = {"UNIVERSITY OF DRAZUKVILLE", "UNIVERSITY"},
    level = 1,
    type = "info",
    text = [[
The University of Drazukville is a great place to learn about how the world
around you operates.  You will learn about your class and the skills you have
available to you, and how to operate those skills.  After graduating, you will
be prepared to face the Realm with confidence!
]],
  },
  {  
    keywords = {"UNKNOWN"},
    level = 1,
    type = "info",
    text = [[
What do you want to know?]],
  },
  {  
    keywords = {"UNRAVEL DEFENSE"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'unravel defense' <victim>

This spell renders the victim susceptible to both magic and nonmagic attacks.
]],
  },
  {  
    keywords = {"UPLIFT"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c uplift <target>

Uplift is a cleric spell that can heal from afar, meant to be used in
aiding players with negative hitpoints.
Uplift is not to be used as your common mode of healing.  Repeatedly asking
for uplifts on public channels is spammy and annoying for other players.
Keep in mind that the clerics that are uplifting you are doing so out of
kindness.  Do _not_ abuse it or consider it a right.]],
  },
  {  
    keywords = {"UPPERCUT"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  uppercut

Uppercut is a skill which can only be used once a fight has started,
and can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.]],
  },
  {  
    keywords = {"USEPROG"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: opedit <object> <command> [number] [use_prog] [percentage]

The use_prog is an objtrigger that can be used in object programs.  The
use_prog will be executed when the item is used.  To define what will
trigger the use_prog, here is a list:

* Wands - when you zap
* Staves - when you brandish
* Food/pills - when you eat
* Blood/fountains/drink containers - when you drink
* Lights/armour/weapons - when you wear/wield/hold
* Potions - when you quaff
* Pipes - when you smoke

When the use_prog is executed you will not see the standard 'use message'
(ie You quaff a violet potion). What you will will be any mpechoes placed
in the program.  Also, any mobprog commands can be used in use_prog (see
MPCOMMANDS).

**NOTE** The use_progs on lights, armour, and weapons are executed BEFORE
the player wears/holds/wields any item. Therefore, a mpforce to remove the
item will not work in the use_prog.  You will have to use a wear trigger
to accomplish this.
]],
  },
  {  
    keywords = {"USERS"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: users <host ip>
Syntax: users <playername>

USERS reports all of the visible users connected to the server, including users
in the process of logging in.
If used with an argument, it will show all users from that host ip.
Shortforms of host will work -- e.x. 205, or 205.113, etc.
Shortened names will also work.  e.x., users fre would show
Fredrick and Fred if they were on at the time.
The first number, (desc), is the descriptor number that this user is on.
The second number is the user's connected state.  (See CONSTATES)
The third number is the number of seconds the user has been idle.
The fourth number is the remote TCP port on the user's host machine.
Next is the user's character name, then the user's host address.
(Usually the IP number as name resolving is normally disabled.)

The FORCECLOSE command can be used to force a connect to close by its
descriptor number.
]],
  },
  {  
    keywords = {"VALIANCE"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast valiance (target)

This spell increases your perseverance when you are on the verge of
losing consciousness.
]],
  },
  {  
    keywords = {"VARIABLE", "VARIABLES"},
    level = 53,
    type = "wizhelp",
    text = [[
This is the list of variables to be used in actiondescs for objects and in
mob/room/object programs.

VARIABLE         MOBILE  ACTOR  VICTIM  RANDOM  OBJECT  2ND_OBJECT
---------------  ------  -----  ------  ------  ------  ----------
Name               $i     $n      $t      $r      $o        $p
shrt_desc/title    $I     $N      $T      $R      $O        $P
he/she/it          $j     $e      $E      $J      --        --
him/her/it         $k     $m      $M      $K      --        --
his/her/its        $l     $s      $S      $L      --        --

See also: MPSTAT, RPSTAT, OPSTAT, MPEDIT, RPEDIT, OPEDIT, TRIGGER, MPTRIGGERS,
          RPTRIGGERS, OPTRIGGERS, MPCOMMANDS, RPCOMMANDS, OPCOMMANDS, IFCHECKS.
]],
  },
  {  
    keywords = {"VAULT"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  vault

Vault is a skill which can only be used once a fight has started, and
can only be used against your primary opponent.  If it successfully
lands, it inflicts damage on your opponent.
]],
  },
  {  
    keywords = {"VENTRILOQUATE"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast ventriloquate <speaker> <message>

This spell throws your voice, making it appear that some other object or
character in the room is saying your message.  Victims who make their saving
throw will know that someone is using ventriloquism, but not who.  Victims who
fail their saving throw will think that the object or character really did say
your message.

]],
  },
  {  
    keywords = {"VICTORIES"},
    level = 1,
    type = "command",
    text = [[
Shows a list of who's killed who lately.  Pure PK stats at their finest (;
]],
  },
  {  
    keywords = {"VIEWSKILLS"},
    level = 54,
    type = "wizhelp",
    text = [[
Syntax: viewskills (charname)

A handy way to check a characters skills.  Better than snooping them and
having them type "prac" (;
]],
  },
  {  
    keywords = {"VNUMS"},
    level = 55,
    type = "wizhelp",
    text = [[
Syntax: vnums [low] [high]

Lists the vnum range for rooms/mobs/objects in all prototype areas.
]],
  },
  {  
    keywords = {"VOMICA PRAVUS"},
    level = 1,
    type = "skill",
    text = [[
Syntax:  vomica <victim>

A truly depraved affliction which may be inflicted by a character upon
its victim, this curse will weaken an opponent's hitroll and damage
roll, deprive them of precious luck and curse them for a brief time.
The damroll and hitroll affects of this curse increase with the level
of the character.
]],
  },
  {  
    keywords = {"VOODOO DOLL"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'voodoo doll'

A very strange spell indeed, experienced shamans can use their magical energy
to create a voodoo doll.  The voodoo doll contains a spirit of some other
being, which the shaman is able to shed some of the damage received in combat
to.  After a small amount of time, the doll will crumble to dust.
]],
  },
  {  
    keywords = {"VOTING", "VOTE", "VOTES"},
    level = 1,
    type = "command",
    text = [[
Syntax: note vote <number> open/close/yes/no/abstain

Once a note has been posted on a bulletin board, the author may open
voting with 'note vote <number> open'.  All those who can read the
board may then vote on the issue in the note with 'note vote <number>
yes/no/abstain'. The author may close the voting; the syntax for that
should be clear enough.

Note list will show whether a note is not a voting note, open to voting
or closed to voting.  The character that separates the author and the
recipient in 'note list' will be a colon, a capital V or a capital C
accordingly.
]],
  },
  {  
    keywords = {"VSEARCH"},
    level = 58,
    type = "wizhelp",
    text = [[
Syntax: Vsearch <vnum>

This command will list all instances of an object with that vnum that
are currently in the game.
]],
  },
  {  
    keywords = {"WAR CRY"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast 'war cry'

By letting forth a mighty war cry, an entire group can enjoy a surge of
adrenalin and be ensured of mighty swings in combat.  However, this skill is
useless if combat is already joined, for the group members are far too busy
fighting to pay attention to the awesome yell.
]],
  },
  {  
    keywords = {"WAR", "WARTALK"},
    level = 1,
    type = "command",
    text = [[
Syntax:  war <message>

Wartalk is a channel created as a haven for those players who like to openly
discuss their exploits in combat - and brag against their opponents.  It is
most often used for those who declare war on other deadlies and is desirable
for those who like to invite others to battles in player versus player
whether it be in the arena or around the Realms.

Wartalk can be seen by all players in the game, and has the same
rules as other channels.  No harassment, profanity, spamming, or
inappropriate subject matter.
]],
  },
  {  
    keywords = {"WARN"},
    level = 58,
    type = "wizhelp",
    text = [[
Syntax: warn class <field>
Syntax: warn race  <field>
Syntax: warn site  <field>
Field is either #(ban_number) or the site/class/race.
Example:  warn class #1
]],
  },
  {  
    keywords = {"WARP MIND"},
    level = 1,
    type = "spell",
    text = [[
Syntax:  c 'warp mind' victim

Summoning forth the corrupting nature of the chaos warp, a diabolist can
infect the victims mind with visions of that which most terrifies them.
Instantly draining a portion of the victims magical capacity, it also leaves
them very vulnerable to other spell attacks.
]],
  },
  {  
    keywords = {"WARRIOR", "WARRIORS"},
    level = 0,
    type = "class",
    text = [[
Warriors are the epitome of fighters, able to use all weaponry and armour
in the exercise of their most lethal of combat skills.  A warrior must be
strong in body to survive his dangerous lifestyle, and though he has no
magic and limited skills he is nevertheless a formidable force with which
to be reckoned.  Warriors learn no magic, and have no use for mana.

Their prime statistic is strength, and constitution is secondary.  Dexterity
is the tertiary statistic.

The races of Human, Dwarf, Elf, Halfling, Half-elf, Half-ogre, Half-orc,
Half-troll, Gith, Sea-elf, Drow, Ghoul, Goblin, Wolfen, Minotaur and Lizardman
are allowed to be warriors.
]],
  },
  {  
    keywords = {"WATCH"},
    level = 51,
    type = "wizhelp",
    text = [[
. &w
&W Syntax: &G watch                  &W Shows you a help screen
&W Syntax: &G watch size             &W Shows the size of your watch file
&W Syntax: &G watch clear            &W Deletes your watch file
&W Syntax: &G watch show             &W Shows all your active watches
&W Syntax: &G watch player <name>    &W Starts watching a player
&W Syntax: &G watch site <site>      &W Starts watching all players from site
&W Syntax: &G watch delete <number>  &W Stops a watch
&W Syntax: &G watch print 1          &W Shows file starting at line 1
&W Syntax: &G watch print 500        &W Shows file starting at line 500
&W Syntax: &G watch print 500 100    &W Shows 100 lines starting at line 500

Watch will work 24 hours a day from the time you put a watch on a player until
you take it off. You can also watch all players from a specific site.

We need you to be real careful about the size of your watch file. If you
are watching a number of players or sites, please do not just forget about
your watches and allow your watch file to grow to outrageous sizes. You
should never have more than 5,000 or 10,000 lines in your watch file.
If you are doing some watching, be sure you check your watch file daily
and either print it, display it, copy it to your hard drive or do whatever
you need to do with it but then ... please ... please ... be sure you
clear it so that it don't grow huge and eat up all our hard drive space.
If you clear your watch file daily ... there should be no problem. If you
aren't watching anyone ... you don't have to worry about this. But if you
start a watch, it is your responsibility to know how big your watch file
is and to stop the watch when you no longer need it. The command
&G"watch size" &W tells you how many lines are in your watch file.
The command &G"watch clear"&W clears (deletes) your watch file.
For the time being the maximum number of lines you can display at one time
is 1000. So ... even if you have 5,000 lines in your watch file ... you can
only display 1,000 at a time.

]],
  },
  {  
    keywords = {"WEAKEN"},
    level = 1,
    type = "spell",
    text = [[
Syntax: cast weaken <victim>

This spell reduces the strength of the victim by 5 points.]],
  },
  {  
    keywords = {"WEAPONCONDITION", "WEAPONCONDITIONS"},
    level = 53,
    type = "wizhelp",
    text = [[
Value0  Condition
------  ---------
  12    in superb condition.
  11    in excellent condition.
  10    in very good condition.
   9    in good shape.
   8    showing a bit of wear.
   7    a little run down.
   6    in need of repair.
   5    in great need of repair.
   4    in dire need of repair.
   3    very badly worn.
   2    practically worthless.
   1    almost broken.
   0    broken.

See also OSET, OBJECTTYPES, WEAPONTYPES, ITEMVALUES and OMENU.
]],
  },
  {  
    keywords = {"WEAPONS"},
    level = 1,
    type = "info",
    text = [[
Weapons are the primary source of fighting power for most classes,
especially at lower levels where other skills and spells remain
unlearned. To use a weapon, simply 'wield <weapon name>'. You will
hit more frequently with a weapon which is suited to your class, so
choose your weapon wisely. For instance, mages use short blades at 95%
efficiency. A mage wielding a long blade would hit his/her target less
frequently, dependant upon the hitroll of the weapon in hand. Also, be
sure to practice and adept your favored weapontype for best results.
]],
  },
  {  
    keywords = {"WEAPONSMITH ETCH", "WEAPONSMITH LIGHT", "WEAPONSMITH WEIGHT", "WEAPONSMITH GUARD", "WEAPONSMITH ENHANCE", "WEAPONSMITH CURVE", "WEAPONSMITH SPELLWARD", "WEAPONSMITH LOYAL", "WEAPONSMITH SWORDBANE", "WEAPONSMITH THIRST", "WEAPONSMITH SERPENT", "WEAPONSMITH ETHERBLADE", "WEAPONSMITH ETHERGUARD", "WEAPONSMITH DRAGONSLAYER", "WEAPONSMITH OGRESLAYER", "WEAPONSMITH SWORDBREAKER", "WEAPONSMITH SERPENTKISS", "WEAPONSMITH DEVOUR"},
    level = 1,
    type = "spell",
    text = [[
Syntax: c 'weaponsmith (type)' weapon

A conjurer can imbue many different magical effects on weapons.  These effects
can be placed on both magical and nonmagical weapons, but only one can be
placed on an item at a time.  In addition, only conjurers may wear the item
once it has been smithed, and if they die, the weapon will disappear from
existence.  Smithing requires components, and the entire component is used
when the spell is cast.

Etch - some pine sap, some iron shavings
Light - some iron shavings, some diamond dust
Weight - some diamond dust, some gold flakes
Guard - some gold flakes, some ruby powder
Enhance - some ruby powder, a steel cube
Curve - a steel cube, a silver orb
Spellward - a silver orb, some oak leaves
Loyal - some oak leaves, some rose essence
Swordbane - some rose essence, some fish scales
Thirst - some fish scales, some emerald shards
Serpent - some emerald shards, a mithril cylinder
Etherblade - a mithril cylinder, a dragon tooth
Etherguard - a dragon tooth, a demon horn
Dragonslayer - a demon horn, an angel feather
Ogreslayer - a dragon tooth, a demon horn, an angel feather
Swordbreaker - a mithril cylinder, a dragon tooth, a demon horn, an angel
               feather
Serpentkiss - some emerald shards, a mithril cylinder, a dragon tooth, a demon
              horn, an angel feather
Devour - some fish scales, some emerald shards, a mithril cylinder, a dragon
         tooth, a demon horn, an angel feather
]],
  },
  {  
    keywords = {"WEAPONTYPES"},
    level = 53,
    type = "wizhelp",
    text = [[
For items of type "weapon", the value3 field specifies the weapon type:

Value3 | Type     | Weapons     | Skill
-------------------------------------------------------------
   0   | hit      | general     |pugilism
   1   | slice    | knife/sword |long blades
   2   | stab     | dagger      |short blades
   3   | slash    | sword       |long blades
   4   | whip     | whip        |flexible arms
   5   | claw     | claw        |talonous arms
   6   | blast    | magical     |pugilism
   7   | pound    | club/hammer |bludgeons
   8   | crush    | club/hammer |bludgeons
   9   | grep     |             |
  10   | bite     |             |pugilism
  11   | pierce   | dagger      |short blades
  12   | suction  |             |pugilism
  13   | bolt     | crossbow    |missile weapons
  14   | arrow    | bow         |missile weapons
  15   | dart     | pipe        |missile weapons
  16   | stone    | sling       |missile weapons
  17   | pea      | peashooter  |missile weapons

See OSET, MISSILES, WEAPONCONDITION and ITEMVALUES.
]],
  },
  {  
    keywords = {"WEARFLAGS"},
    level = 53,
    type = "wizhelp",
    text = [[
These flags should be self explanatory:

 take   finger   neck    body    head   legs
 feet   hands    arms    shield  about  waist
 wrist  wield    hold    ears    eyes

See OSET, RESETCMDS, and ARMORCLASS.
]],
  },
  {  
    keywords = {"WEARLOCS", "WEARPOS"},
    level = 53,
    type = "wizhelp",
    text = [[
Here are the various locations where items may be equipped:

  0 - light     9 - wrist1     18 - ankle1       27 - aura
  1 - head     10 - wrist2     19 - ankle2
  2 - eyes     11 - hands      20 - feet
  3 - ears     12 - finger1    21 - wield
  4 - face     13 - finger2    22 - dual_wield
  5 - neck1    14 - about      23 - shield
  6 - neck2    15 - back       24 - hold
  7 - body     16 - waist      25 - wwp1
  8 - arms     17 - legs       26 - wwp

See RESETS and RESETCMDS.
]],
  },
  {  
    keywords = {"WEBSITE"},
    level = 1,
    type = "info",
    text = [[
&WHoG has a website at: &Chttp://www.houseofghoulsmud.com&W
You should check it out, it gains more information everyday!

See also "HOMEPAGE".
]],
  },
  {  
    keywords = {"WHERE", "WHOZONE"},
    level = 0,
    type = "info",
    text = [[
Syntax: where
Syntax: where <character>

WHERE without an argument tells you the location of visible players in the same
area as you are.

WHERE with an argument tells you the location of one character with that name
within your area, including monsters.

WHOZONE is just another name for WHERE and works the same way.
]],
  },
  {  
    keywords = {"WHISPER"},
    level = 1,
    type = "command",
    text = [[
whisper <name> msg

To whisper to another, you must be in the same room as the recipient
of the whisper.
]],
  },
  {  
    keywords = {"Old WHO"},
    level = 1,
    type = "command",
    text = [[
WHO shows the characters currently in the Realms.  Invisible characters will
not appear on this list if you cannot detect invisible.  Immortals who are
wizinvis higher than your own level also will not appear.

Syntax:  who                 who <class>    who <class> race>
         who <level range>   who deadly     who <class> <race> <level range>

With arguments, WHO can show players of certain classes, races, or levels:
For example:

 who 10                  lists all characters level 10 or above
 who 15 20               lists all characters between level 15 and 20
 who cleric              lists all clerics playing
 who cleric elf          lists all cleric elfs playing
 who imm                 lists all Immortals playing
 who cleric 1 5          lists all clerics between levels 1 and 5

NEW ADDITIONS:
 who <following>         lists all online members of the specified Following
 who <deity name>        lists all online worshippers of the specified deity
 who group               lists all online grouped players
 who group 10 20         will list all players level 1 thru 10 who are grouped
                         or who desire to group. (see also help CONFIG)
 who leader              will list all leaders of clans, orders, guilds and
                         councils.  This can be used in conjunction with a
                         specific order if it is listed after the name.
]],
  },
  {  
    keywords = {"Old WHO LEADER"},
    level = 1,
    type = "command",
    text = [[
Typing 'who leader' will list the current leaders of various organizations
that are online.
]],
  },
  {  
    keywords = {"WHOIS"},
    level = 0,
    type = "command",
    text = [[
Syntax: whois <player>

The WHOIS command will tell you a bit of information about a player
that is online.
]],
  },
  {  
    keywords = {"WIMPY"},
    level = 0,
    type = "command",
    text = [[
Syntax:  wimpy
Syntax:  wimpy <value>
Syntax:  wimpy max

This command sets your wimpy value.  When your character takes damage that
reduces your hit points below your wimpy value, you will automatically
attempt to flee.

'Wimpy' by itself sets your wimpy to about 20% your maximum hitpoints.

'Wimpy <value>' allows you to set your wimpy at a level you determine,
but it cannot exceed about 75% of your maximum hitpoints.

'Wimpy max' sets your wimpy at its maximum level for you.

Some monsters are wimpy.
]],
    see_also = {"flee"},
  },
  {  
    keywords = {"WINTER MIST"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'winter mist' (victim)

This spell makes the victim more susceptible to all forms of coldness.


]],
  },
  {  
    keywords = {"WIS", "WISDOM"},
    level = 1,
    type = "info",
    text = [[
Wisdom (WIS in your 'score') represents your character's wisdom and ability
to incorporate learning.  Among other things, it affects:

 - the number of practices a character gains each time it levels

 - the mana a character gains each time it levels, though intelligence
   affects this much more heavily

 - the percentage a character learns of a new language at each practice,
   though intelligence affects this slightly more

 - the ability to remove a trap or poison a weapon

Wisdom is the prime attribute of druids and clerics.

]],
  },
  {  
    keywords = {"WITHDRAW", "BALANCE", "DEPOSIT"},
    level = 1,
    type = "command",
    text = [[
When at one of the banks of the Realm, you can use various commands to
interact with the bankers.  The great thing about banks is money you deposit
is readily available from any bank in the Realm.


Deposit - Used to deposit gold with the banker.  Syntax is "deposit #", where
# is the number of coins you want to deposit.

Withdraw - Used to withdraw gold from the banker.  Syntax is "withdraw #",
where # is the number of coins you want to withdraw.

Balance - Used to check and see how much money you have in the bank.
]],
  },
  {  
    keywords = {"WIZHELP"},
    level = 51,
    type = "wizhelp",
    text = [[
Syntax: wizhelp

WIZHELP provides a list of all the immortal commands.
]],
  },
  {  
    keywords = {"WIZINVIS"},
    level = 51,
    type = "wizhelp",
    text = [[
All immortals have the responsibility to be available to others whenever
possible, be they mortal or immortal.  When the use of wizinvis is called
for, the following are parameters for its use:

 - Immortals level 51 through 54 should be visible at all times, save
   for when snooping, running a quest or some similar circumstance.

 - Immortals level 55 and up may invis to any level at their discretion.

Guidelines for use of wizinvis by 55 and higher:
It is considered mandatory to be visible to all other immortals whenever
reasonably able to do so.  Using wizinvis beyond 51 to facilitate work on
a project, allow concentration on something, avoid excessive tells or the
like is fine, but it should only be used while necessary.

Guidelines for use of wizinvis beyond 51 in immortal channels:
Sightings of Someones in immortal channels should be kept to a minimum.
If you are free enough to be able to use an immortal channel, you should
be visible to the lowest immortal in that channel; no higher than 54 in
Muse, no higher than 51 in immtalk, etc.  Being a Someone to anyone on
an immortal channel should only occur if you're too tied up to go
visible but need to make a comment.

The same applies to all situations using channels, tells or actions.
Avoid being a Someone to mortals and immortals alike unless you have
a good reason to do otherwise.
]],
  },
  {  
    keywords = {"WIZLIST"},
    level = 0,
    type = "command",
    text = [[
Syntax: wizlist

Displays a list of the powerful beings who govern this SMAUG MUD!
]],
  },
  {  
    keywords = {"WIZMARK"},
    level = 52,
    type = "wizhelp",
    text = [[
Syntax: wizmark item

Use this command to mark your equipment as an Immortal.  It will flag it as a
Quest item (ensuring its return upon your death) and also flag it with your
name as the owner.  This ensures noone else can use the item if something
weird happens.  MAKE SURE TO DO THIS TO ALL EQUIPMENT YOU WEAR IF YOU ALSO USE
THE MORTALITY COMMAND!!!!
]],
  },
  {  
    keywords = {"WOLFEN"},
    level = 0,
    type = "race",
    text = [[
Wolfen are a strange race, seldom seen in the Realm.  It is said they come
from a land far across the great sea, but noone has ever returned with
proof...

Stronger, faster, and ever smarter than most other races, the wolfen is feared
by others.  Their luck seems to leave them at the worst times.  Being in tune
with magic and nature, they can see heat in dark rooms, and can understand all
languages.

Wolfen grow to be quite large, and due to their nature and build, are
resistant to cold and poison.  Due to the magical nature of a wolfen, they are
susceptible to fire and energy.

An elder race, they hate the Ghouls with a passion and blame them for all of
their troubles.  They only receive 85% of the normal experience point award.

Wolfen can be a Mage, Thief, Warrior, Thug, Druid, Ranger, Diabolist or
Shaman.
]],
  },
  {  
    keywords = {"WORD OF RECALL"},
    level = 0,
    type = "spell",
    text = [[
Syntax: cast 'word of recall'

This spell will recall the caster to his or her home sanctuary.

]],
  },
  {  
    keywords = {"WORTH"},
    level = -1,
    type = "command",
    text = [[
Syntax: worth

WORTH shows a simple, easy-to-read table of important and widely used
statistics. This command is for the character itself and cannot be used
on others. The Statistics that follow have been included in the table:
Level, Favor, Alignment, Experience, Glory, Weight, Style, and Gold.
]],
  },
  {  
    keywords = {"WRATH DOMINUS"},
    level = 1,
    type = "spell",
    text = [[
Only rumors of this spell remain.  Perhaps someday it's secrets will be
recovered, but for now, noone knows how it works or was utilized.
]],
  },
  {  
    keywords = {"ZONES"},
    level = 52,
    type = "command",
    text = [[
Syntax: zones [low] [high]

Lists the name of the file, and room/mob/object vnum range for each
non-prototype zone in the mud.
]],
  },
