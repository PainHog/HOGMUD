all_helps.wizhelp = {}
all_helps.wizhelp = {
  entries = {
  
  {  
    keywords = {"AASSIGN"},
    level = 65,
    htype = "wizhelp",
    text = [[
Syntax: aassign <filename>.are  Example:  aassign edo.are

AASSIGN temporarily assigns all rooms, objects, and mobiles in the area
range to your pfile.  This allows you to use rlist, olist, mlist, and
reset list.  This also means that typing savearea, reset area, or
instazone will affect this area.

To save changes permanently, type "aassign none" and foldarea.

&rWarning&w!! Do not have an area aassigned to yourself when getting personal
vnums assigned to you.  The personal vnums will overwrite the area file.

In order to assign a proto area to yourself, you must either have that
area bestowed to you by a Greater God or higher.

In order to assign a nonproto area to yourself, you must either have
that area bestowed to you by an Exalted+. Even if you have the area bestowed
only Lesser+ can aassign themselves nonproto areas.
]],
  },
  {  
    keywords = {"ACTFLAGS", "MOBFLAGS"},
    level = 55,
    htype = "wizhelp",
    text = [[
&GMOBFLAG       &W|&GDESCRIPTION&W
&Y--------------&W|&Y-------------------------------------------------------&W
sentinel        Mobile always stays at its post.
scavenger       Mobile picks up items of value.
aggressive      Mobile attacks players.
stayarea        Mobile does not leave its home area.
wimpy           Mobile flees when low in hits.
practice        Players can "practice" at this mobile.
immortal        Mobile is immortal (not implemented).
deadly          Mobile has a deadly poison (not implemented).
meta_aggr       Mobile is VERY aggressive (not implemented).
nowander        Mobile doesn't wander unless attacked.
mountable       Mobile can be mounted.
prototype       Mobile is under construction.
running         Mobile is running (moves twice as fast)
noassist        Mobile won't assist other mobs in a fight.
pacifist        Mobile cannot be attacked.
scholar         Mobile can teach languages.
secretive       Mobile will not echo acts. MOBs actions are invisible.
mobinvis        Mobile is invisible to both pc's and non pc's.
noattack        Mobile won't use any physical attacks.
autonomous      Mobile won't switch tanks if hit by someone with higher style.
pet             Mobile can be used in creating a petshop.
healer          Mobile can sell healing spells to pc's.
banker          Mobile can accept withdrawals, deposits, and balance.
questmaster     Mobile can give quests to pc's
aggressive_low  Mobile will attack players level 15 and below.
aggressive_mid  Mobile will attack players level 16 and above
aggressive_high Mobile will attack players level 30 and above.
&Y--------------&W|&Y-------------------------------------------------------&W
]],
  },
  {  
    keywords = {"ADVANCE"},
    level = 60,
    htype = "wizhelp",
    text = [[
Syntax: advance <character> <level>

ADVANCE sets a character's level to the specified value.  It is the
only way to create new immortal characters within the game.  ADVANCE
may also be used to demote characters.
]],
  },
  {  
    keywords = {"ADVANCEDEXITS"},
    level = 65,
    htype = "wizhelp",
    text = [[
SMAUG supports having more than one exit in the same direction, as well as
the special direction 'somewhere', represented by a '?'.

If you already have an exit leading north, and would like another one, use
a plus sign '+' in front of the direction:
  redit exit +n 3001          - Adds another exit north to room 3001

To modify an extra exit like this, or to remove it, you'll have to refer to
it by number:
  redit exit #2 3002          - Change the second exit to go to room 3002
  (to know what number an exit is, do an "rstat")

For someone to be able to use the second north exit, you have to set one of
the extra flags (see EXFLAGS) like CAN_CLIMB.  It's also usually a good idea
to set the HIDDEN flag for any special exit so that it looks nicer to those
with autoexits on.

The AUTO flag makes it possible to go in a direction by simply typing the
keyword for that exit:
  redit exit ? 3001           - Create a 'somewhere' exit to 3001
  redit exflags ? auto hidden - Set the proper flags
  redit exname ? swim         - Set the keyword "swim"
  ... here, if a player types 'swim' in the room they will move to room 3001

]],
  },
  {  
    keywords = {"AEXIT"},
    level = 65,
    htype = "wizhelp",
    text = [[
Syntax:  aexit
         aexit "area filename"

AEXIT shows the exits the area has leading into and out of the area into other
areas.  Useful to make sure connections are all set correctly.


]],
  },
  {  
    keywords = {"AFFECTEDBY", "AFFECTED_BY"},
    level = 51,
    htype = "wizhelp",
    text = [[
The following are affect flags that can be used when osetting an item
(with oset <item> affect affected <affect flag>).  These flags can also
be used when msetting a mobile (mset <mob name> affected <affect flag>).
They may additionally be used to mset players if your level allows it.

Blind          Invisible    Detect_evil  Detect_invis  Detect_magic
Detect_hidden  **Hold**     Sanctuary    Faerie_fire   Infrared
Curse          **Flaming**  Poison       Protect       Paralysis
Sneak          Hide         Sleep        Charm         Flying
Pass_door      Floating     Truesight    Detect_traps  Scrying
Fireshield     Shockshield  Iceshield    Aqua_breath   Possess

Note - Hold and Flaming are current not in use.

See also: OSET AFFECTTYPES
]],
  },
  {  
    keywords = {"AFFECTTYPES", "APPLYTYPES"},
    level = 51,
    htype = "wizhelp",
    text = [[
none        strength    dexterity   intelligence  wisdom       constitution
sex         level       age         height        weight       mana
hit         move        gold        experience    armor        hitroll
damroll     save_para   save_rod    save_poison   save_breath  save_spell
charisma    resistant   immune      susceptible   affected     luck
backstab    pick        track       steal         sneak        hide
detrap      dodge       peek        scan          gouge        search
mount       disarm      kick        parry         bash         stun
punch       climb       grip        scribe        brew

Additionally:
weaponspell <sn>    Will cast a spell on victim with every blow of a weapon
wearspell   <sn>    Will cast a spell on wearer when object is worn
removespell <sn>    Will cast a spell on wearer when object is removed
<skill> <modifier>  Will modify a player's ability in a skill

See AFFECTEDBY
]],
  },
  {  
    keywords = {"ALLOW BAN"},
    level = 58,
    htype = "wizhelp",
    text = [[
ALLOW BAN WARN
Syntax:  allow  site/race/class    <address/race/class>
Syntax:  ban    site/race/class    <address/race/class>   <type>    <duration>
Syntax:  ban    show               <class/site/race>      <number>
Syntax:  warn   <site/class/race>  <number>

BAN site will ban a site from playing the game.
BAN race bans anyone with that race from playing the game.
BAN class bans anyone with that class from playing the game.
BAN site/race/class without any other arguments will give you a list of
currently banned sites/races/classes.
Type can either be a level or one of the following keywords: all,newbie,mortal,
warn. If you set it to a level everyone equal to that level and below will not
be allowed on.  Warn, sends a warning to the Warn: channel that someone if
logging in from the site, with a certain class or race.  If you add the
duration, the ban will expire in that many days. Sites can be banned with the *
wildcard as well.  Be careful however as *.edu would ban every site from .edu,
or *foo* would ban any site that had the string foo in it.
BAN show, will print out the reason why that particular site/race or class was
banned and by who.  Number can be a class or race name, a site address or
you can use # followed by the ban number.
WARN will toggle the warn flag on a CURRENTLY banned site/class or race.

ALLOW site/race/class  <address/race/class>  removes a site, class or race from
the ban list.  This also can be allowed by using # syntax.

]],
  },
  {  
    keywords = {"ARMORCLASS"},
    level = 52,
    htype = "wizhelp",
    text = [[
.
&gThere are two values used with armor class for object type Armor:

&GValue0: Variable amount based on level of item at repop.
Value1: Maximum repairable armor setting for the object.

&gSetting Value0 has no effect. It will re-adjust itself on repop based on
the repop level of the item. Setting Value1 below the expected repop value
for Value0 will result in an item that cannot be repaired until Value0 drops
below Value1's setting. The listing below gives you a rough approximation of
the values returned for Value0 based on level:

&GLevel Invoked   Value0   Level Invoked   Value0   Level Invoked   Value0
-------------   ------   -------------   ------   -------------   ------
      1           1-3         10           3-5         20           6-8
     30           8-10        40          11-13        50          13-15

&gThe amount that Value0 is set to determines the amount the player's A.C. will
be adjusted. Different wear locations have a different multiplying affect:

&G0 X Value0: Wield, Ears.
1 X Value0: Arms,  Finger, Neck, Feet, Hands, Shield, Waist, Wrist, Hold, Eyes.
2 X Value0: Head,  Legs,   About.
3 X Value0: Body.

&gSee also OSET, AFFECTTYPES, WEARFLAGS, OBJECTFLAGS, OBJECTTYPES, ITEMVALUES,
WEAPONTYPES, VARIABLES, and OMENU.
]],
  },
  {  
    keywords = {"ASET"},
    level = 65,
    htype = "wizhelp",
    text = [[
Syntax:  aset <area filename> <field> <value>

Aset is used to set the following fields for an individual area:
author    - The name of the area's author
name      - The full "name" of an area... ie: {10 20} Somegod  Some Area
filename  - The filename (ie: somearea.are)
lo_room   - The lowest room vnum
hi_room   - The highest room vnum
lo_obj    - The lowest obj vnum
hi_obj    - The highest obj vnum
lo_mob    - The lowest mob vnum
hi_mob    - The highest mob vnum
low_economy - minimum amount of gold the area will start with at reboot
max_economy - maximum amount of gold the area _can_ start with at reboot
resetmsg  - Message displayed throughout the area at reset
resetfrq  - Number of minutes between area resets
flags     - Area-wide flags:  nopkill

The area must be folded to make these changes permanent.

See ASTAT, ECONOMY, FOLDAREA
]],
  },
  {  
    keywords = {"ASTAT"},
    level = 59,
    htype = "wizhelp",
    text = [[
Syntax:  astat                      (area stats for the area you are in)
Syntax:  astat <filename of area>   (area stats for specified area)

Astat displays the vital stats of an area, including the following:
Name:            title of the area
Filename:        filename of the area
Prototype:       If the area is prototype or under construction, will be 'yes'
Max_players:     max # of players in the area as of last reboot
IllegalPks:      number of illegal pkills in the area since last reboot
Gold looted:     total amount of gold looted from the area since last reboot
Area Economy:    current pool of gold for the area (not including player gold)
Mdeaths:         number of players mobs killed in the area since last reboot
Mkills:          number of mobs killed in the area since last reboot
Pdeaths/Pkills:  number of players killed by players in area since reboot
Author:          name of the area's author
Number Players:  current number of players in the area
Area flags:      area-wide flags (such as nopkill)
Low/hi_room:     first/last room vnum of the area
Low/hi_obj       first/last object vnum of the area
Low/hi_mob       first/last mob vnum of the area
Soft range:      level range recommended for the area
Hard range:      level range enforced for area (outside range cannot enter)
Resetmsg:        current reset message for the area at repop
Reset frequency: frequency with which the area resets

See ASET
]],
  },
  {  
    keywords = {"AT"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: at <location> <command>

AT executes the given command (which may have arguments) at the given
location.  The location may be specified as a vnum, as the name of
a mobile or player.

AT works by temporarily moving you to that location, executing the
command, and then moving you back (if the command didn't change your
location).
]],
  },
  {  
    keywords = {"ATOBJ"},
    level = 52,
    htype = "wizhelp",
    text = [[
Syntax: atobj <object> <command>

ATOBJ executes the given command (which may have arguments) at the given
object.

ATOBJ works by temporarily moving you to that location, executing the
command, and then moving you back (if the command didn't change your
location).
]],
  },
  {  
    keywords = {"ATTACKS"},
    level = 53,
    htype = "wizhelp",
    text = [[
bite          claws        tail        sting      punch        kick
trip          bash         stun        gouge      backstab     feed
drain         firebreath   frostbreath acidbreath lightnbreath gasbreath
poison        nastypoison  gaze        blindness  causeserious earthquake
causecritical curse        flamestrike harm       fireball     colorspray
weaken

See MSET and DEFENSES  (Some are not implemented).
]],
  },
  {  
    keywords = {"AUCTIONSTOP"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax <auctionstop>

&WAuctionstop is to be used to halt the auctioning of illegal items, ie:
deadly equipment, order/clan/guild items. Auctions are NOT to be
stopped for overbidding, misbidding, or misauctioning.
  Other items the auction can be stopped for are balls of light and
recall scrolls if sold alone. If they are inside a container with other
items, they may be auctioned.
&W
]],
  },
  {  
    keywords = {"AUTHORIZE"},
    level = 52,
    htype = "wizhelp",
    text = [[
Authorize is used to allow new characters.  We don't use it on HoG.
]],
  },
  {  
    keywords = {"BAMFIN", "BAMFOUT"},
    level = 51,
    htype = "wizhelp",
    text = function ()
send(fix_description([[
Syntax: bamfin  <message>
Syntax: bamfout <message>

The default messages for GOTO are:
Bamfin:  '$n arrives in a swirling mist' 
Bamfout: '$n leaves in a swirling mist'.

You can replace these messages with messages of your own choosing using the
BAMFIN and BAMFOUT commands.

You may change the location of where your name appears in the messages by
placing a $$n where you wish your name to be placed.
]]))
end,
  },
  {  
    keywords = {"BAN 50"},
    level = 51,
    htype = "wizhelp",
    text = [[
Seeking to ban a site above level 1 should be an extremely rare situation. One
in which the actions of one or more key persons from a site are deemed to be
a detriment to the enjoyment of a large portion of the players in the game.
Such person(s) are generally deemed to be beyond rehabilitation at this time.

When seeking to ban a site, make use of the Grub command to both see the impact
of the ban, and to get a list of all character names from the site. You can use
this list to keep an eye out for these characters coming in from other sites,
as it's obvious these days that a site ban may not always cure the situation.

All site bans above level one should be set at level 50 or higher. It should be
a rare instance in which a site is banned at some in between level. Only in the
direst of instances would a site be banned above level 50, as this will affect
immortal level players as well.

See also: 'BAN ALLOW", "BAN NEWBIE", "BAN DURATION'
]],
  },
  {  
    keywords = {"BAN DURATION"},
    level = 51,
    htype = "wizhelp",
    text = [[
The standard set for ban durations are as follows:

Newbie Ban:          1) One week on first instance.
                     2) Two weeks for the second.
                     3) One month at newbie, or level 50 for third.
                     4) Permanent at newbie, or level 50 for 4th offense.

Bans for level 2-50: 1) One month for first instance.
                     2) Two months, or permanent for 2nd.
                     3) Permanent for 3rd offense.

All bans above level 50 should be permanent by their very nature.

&WReminder - Without documenting each time we ban a site, we will have no
           source of history on sites. Always remember to post a note
           detailing the reasons for the ban.&w

See also: 'BAN ALLOW", "BAN NEWBIE", "BAN 50'
]],
  },
  {  
    keywords = {"BAN NEWBIE"},
    level = 51,
    htype = "wizhelp",
    text = [[
Banning a site is a form of last resort, as it not only affects the offending
player or players, but will also affect every other player from that site.
Before seeking to ban a site, even for a temporary level 1 banning, make
sure you have exhausted all other options first.

In the case of newbie bans, most such instances arise through the actions of
one or more abusive players who log in a newbie and begin swearing, spamming,
threatening, etc.. Many times this has developed from an immature player's
frustrations over getting a name authed. If you find a player going through a
series of silly names trying to auth them, make every effort to try and talk
with them first. If this fails, use Fquit to discourage them. If you have
Disconnect, use this instead, as it is less provoking than fquit (makes it
appear as if they simply lost their connection). If they continue their
efforts, send them warnings to get their attention. Use freeze if you have it
(or if someone else is on who can use it) to get their attention and make sure
received the message. Then, and only then, once you've exhausted all avenues
at being civil, you can use ban in good conscience. You've given the player(s)
every chance to cease their actions and given them fair warning over the fact
that if they continue they risk getting banned.

See also: 'BAN ALLOW", "BAN 50", "BAN DURATION'
]],
  },
  {  
    keywords = {"BARENUM", "BARESIZE"},
    level = 58,
    htype = "wizhelp",
    text = [[
Syntax: mset <mob> barenum <number>
mset <mob> baresize <num>

These mob fields control the mobs ability to fight without weapons.
Barenum is the low end of the damage done and baresize is the multiplier.
For example: barenum 10 and baresize 5 would have the effect of allowing
the mob to hit barehanded for 10-50 damage.

* This field also affects experience gained.
Experience is calculated as follows:
^level 3*5 + max_hit +barenum *baresize +damroll * 50
+hitroll *ch -> level *10

Right now, I have things set so that no matter what weapon the mob is
wielding, they do damage based on this number.  Big mobs with low range
weapons weren't hitting very hard (;
]],
  },
  {  
    keywords = {"BESTOW", "BESTOWMENTS"},
    level = 60,
    htype = "wizhelp",
    text = [[
Syntax: bestow <victim> command [command] [command] etc
bestow <victim> list
bestow <victim> none

Bestow is used to give a command to a player that the player would not normally
have. Bestow victim command will give the command to the person, bestow victim
list will show all commands currently bestowed on the person, and bestow victim
none will remove all bestowments.
]],
  },
  {  
    keywords = {"BESTOWAREA"},
    level = 55,
    htype = "wizhelp",
    text = [[
Syntax: bestowarea <victim> <filename>.are

This command allows members of the Area Council to bestow area names
to immortals so that they can engage in group building.

Once an AC member bestows a proto area on a player, that player can
use the aassign command to assign themselves that proto area in order
to help the owner of the proto area.

Examples:

bestowarea joe bob.are           allows joe to work on bob's proto area
bestowarea joe                   lists all of joe's bestowed areas
bestowarea joe list              ditto
bestowarea joe none              removes all of joe's bestowed areas

]],
  },
  {  
    keywords = {"BESTOWEDAREAS"},
    level = 56,
    htype = "wizhelp",
    text = [[
Noone is bestowed any areas right now -Drazuk
]],
  },
  {  
    keywords = {"BODYBAG"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: &Wbodybag <name> <bag/yes>
          bodybag <name> will show the status of the corpse.
&w
BODYBAG gets all of <character's> corpses and puts them in your inventory
to do with as you wish.

If you find yourself getting the wrong corpse, post a bug report immediately!
See also TIMER
]],
  },
  {  
    keywords = {"BSET"},
    level = 52,
    htype = "wizhelp",
    text = [[
BSET is used to setup the various note boards on the MUD.]],
  },
  {  
    keywords = {"BSTAT"},
    level = 52,
    htype = "wizhelp",
    text = [[
Get the statistics of a note board.  Use the filename of the board to identify
the one you want info about.  Find the filename with "BOARDS".
]],
  },
  {  
    keywords = {"BUYLOCKER"},
    level = 65,
    htype = "wizhelp",
    text = [[
Use to buy lockers.  Drazuk just makes em for peoples homes though...no need
to buy one right now.
]],
  },
  {  
    keywords = {"CEDIT"},
    level = 61,
    htype = "wizhelp",
    text = [[
Syntax:  cedit save
Syntax:  cedit <command> create [code]
Syntax:  cedit <command> delete
Syntax:  cedit <command> show
Syntax:  cedit <command> [field]

Field being one of:
  level position log code

Cedit create is used to create the entry and name for a new command.
Cedit delete is used to delete a command.
Cedit code is used to assign a defined section of code to a command.
Cedit show displays current statistics on a command.
Cedit level sets the minimum level for usage of a command.
Cedit position sets the min_pos for execution of the command.
Cedit log determines the manner in which the command will be logged.

Use 'cedit save' to save changes permanently.

See RESTRICT
]],
  },
  {  
    keywords = {"CHECKVNUM CHECKVNUMS"},
    level = 58,
    htype = "wizhelp",
    text = [[
Syntax: checkvnums <field> <start vnum> <end vnum>

Checkvnums will allow you to view if any areas conflict with a set
of vnums that you need.
Correct FIELD values include Mob, Object, Room, or All (all three fields).
Starting and ending vnums should not be more than 5k from each other
as you might spam yourself out :)

See Also: AASSIGN, MAASSIGN, OASSIGN, FREEVNUMS, FREEVNUMS2
]],
  },
  {  
    keywords = {"CLIMATE"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax climate <field> <name>

This command allows you to view or modify the climate
settings for an area. There are settings for temperature,
precipitation, and wind. In addition, you may specify
neighboring areas who will affect changes in the current
areas weather. Therefore there are four fields to choose
from. Each field has a different range of values available.

Field name:           Values:
temp                  cold, cool, normal, warm, hot
precip                arid, dry, normal, damp, wet
wind                  still, calm, normal, breezy, windy
neighbor              <area name>

Specifying an area name with neighbor which is already on
the list will remove it. Using climate without any arguments
will display the area's current setting. Note that this
command always refers to the area which you are currently in.
]],
  },
  {  
    keywords = {"CLONES"},
    level = 60,
    htype = "wizhelp",
    text = [[
Syntax: clones&w

This command works like users; it shows you all the active connections, but
it shows them sorted by user@host, making it easier to spot multiplayers.
It also counts the clones for you.

See also: &YUSERS&w
]],
  },
  {  
    keywords = {"CMDTABLE"},
    level = 57,
    htype = "wizhelp",
    text = [[
Syntax: cmdtable

Lists all of the commands in the game, and how many times they have been used
since the last startup.
]],
  },
  {  
    keywords = {"COINDUCT COOUTCAST COIN COOUT"},
    level = 55,
    htype = "wizhelp",
    text = [[
COINDUCT COOUTCAST COIN COOUT

Syntax:  coinduct <playername>
         cooutcast <playername>

Coinduct inducts an player into a council.  Cooutcast removes a player
from a council.
This command should only be used if it is your council unless authorized.
]],
  },
  {  
    keywords = {"COLOR COLOUR"},
    level = 51,
    htype = "wizhelp",
    text = [[
.
The following 16 colors are supported in the commands echo, recho,
mpecho, mpechoat and mpechoaround.

_whi  White
_yel  Yellow
_blu  Blue
_dbl  Dark Blue
_lbl  Light Blue
_cya  Cyan (sort of turquoise)
_gre  Green
_dgr  Dark Green
_cha  Charcoal (grey)
_dch  Dark Charcoal (dark grey)
_pur  Purple
_red  Red
_ora  Orange
_bro  Brown
_pin  Pink
_bla  Black

Note that the indicator is the first three letters of the color itself
so that it is easy to remember.

If the indicator is preceded by an asterisk, the message will blink.
You only need to enter as much of the color indicator as needed to
uniquely identify it.

recho _red              This is an example of recho in red.
recho *red              This is an example of recho in blinking red.
mpe _yel                This is an example of mpecho in yellow.
mpechoat $n _blu        This is an example of mpechoat in blue.
mea $n _blu             This is an example of mpechoat in blue.
mpechoaround $n _bro    This is an example of mpechoaround in brown.
mer $n _bro             This is an example of mpechoaround in brown.
mpe _r                  This is an example of mpecho in red.

]],
  },
  {  
    keywords = {"COLORIZE"},
    level = 65,
    htype = "wizhelp",
    text = [[
Syntax:   colorize
Syntax:   colorize [<LOCATION> <COLOR>]

LOCATION:  Without any arguments will list your current
settings.  Otherwise specify the location you want to change.

COLOR:  This can be the name of the color you want or default
which will set it to the current color in the mud scheme for that
location.

]],
  },
  {  
    keywords = {"COLORS"},
    level = 51,
    htype = "wizhelp",
    text = [[
The ability to color Help and other files is very useful.

If you wish to add other colors to your file, please use good
taste, make sure it is readable and don't get too whacky. If
you follow the above guidelines and stick to using white for
all other text, it will keep the text solid and legible. Should
you choose not to use any colors at all, that is also okay, the
above guidelines are merely for proper use of color, white is
always acceptable.

In addition, please keep in mind that the following topics should
not be colored except by their defaults:
  - Help (area name)
  - Help (skill)
  - Help (spell)
  - Help (class)
]],
  },
  {  
    keywords = {"COMMENT"},
    level = 53,
    htype = "wizhelp",
    text = [[
Used like note, but gets posted to a character.

Use the same commands as note, but use the character as the target for
posting...I guess to mark characters if they need marking.
]],
  },
  {  
    keywords = {"CONSTATES"},
    level = 52,
    htype = "wizhelp",
    text = [[
State | Description
-----------------------------------------------------------
    0 | Player is playing.
    1 | Player is prompted for his or her name.
    2 | Player is prompted for his or her password.
    3 | Player is prompted to confirm his or her name.
    4 | Player is prompted to select a password.
    5 | Player is prompted to confirm the password.
    6 | Player is prompted to select his or her sex.
    7 | Player is prompted to select a class.
    8 | Player is reading the message of the day.
    9 | Player is prompted to select a race.
   10 | Unused.
   11 | Player is in the line editor.
   12 | Player is prompted to select RIP, ANSI or NONE.
   13 | Player is viewing the title screen.
   14 | Player is prompted to PRESS ENTER.
   15 | Player is waiting for authorization (1).
   16 | Player is waiting for authorization (2).
   17 | Player is waiting for authorization (3).
   18 | Player has been authorized.

Doh, stat rolling is in there somewhere...let Drazuk know if its important to find out where!]],
  },
  {  
    keywords = {"CONTAINER_FLAGS"},
    level = 53,
    htype = "wizhelp",
    text = [[
Container flag values:
     Closeable = 1
     Pickproof = 2
     Closed    = 4
     Locked    = 8
]],
  },
  {  
    keywords = {"CONTROLS", "CSET"},
    level = 61,
    htype = "wizhelp",
    text = [[
Cset is used to set the system's 'control panel' settings.
Syntax: cset <field> <level>
Fields: save - saves the control panel settings
        dodge_mod - divide dodge chance (% learned) by this (default 2)
        parry_mod - same as above, for parry                (default 2)
        tumble_mod - same as above, for tumble              (default 4)
        stun - sets normal (mob vs. player / player vs. mob) stun modifier
        stun_pvp - as above, for player vs. player
        bash_pvp - bash modifier player versus player
        bash_nontank - modifier if basher is not tanking the victim
        gouge_pvp - gouge modifier player versus player
        gouge_nontank - gouge modifier if gouger is not tanking the victim
        dam_pvp - percentage adjustment for player vs. player fighting
        dam_pvm - as above, for player vs. mob
        dam_mvp - as above, for mob vs. player
        dam_mvm - as above, for mob vs. mob
        get_notake - level to pick up notake flagged items
        read_all - level to read all mail
        read_free - level to read mail for free
        write_free - level to write mail for free (no items necessary)
        take_all - level to take all mail
        muse - level to see/use muse channel
        think - level to see/use think channel
        log - level to see log channel
        build - level to see build channel
        proto_modify - level to modify prototype objects
        mset_player - level to allow mset to operate on a player
        override_private - level to override private/solitary rooms
        forcepc - level to force pc's
        guild_overseer - name of the Overseer of Guilds
        guild_advisor - name of the Advisor to Guilds
        saveflag - flags/actions on which to save a pfile (drop, give, get,
                   receive, auction, zap, death, auction, auto, password)
        imc_vnum - vnum for imc board
        ban_site_level -  level able to ban sites
        ban_class_level - level able to ban classes
        ban_race_level -  level able to ban races
        bestow_dif - max lvl dif between bestowed cmd level and char lvl
        checkimmhost - imm host checking on or off

]],
  },
  {  
    keywords = {"COUNCILS"},
    level = 65,
    htype = "wizhelp",
    text = [[
List the various councils created.]],
  },
  {  
    keywords = {"COUNCILTALK"},
    level = 65,
    htype = "wizhelp",
    text = [[
Syntax: counciltalk <message>
Syntax: coun <message>

The Counciltalk command will allow your message to be heard by other
characters in your council, should you be a member of one.
]],
  },
  {  
    keywords = {"CREATOR"},
    level = 51,
    htype = "wizhelp",
    text = [[
The following is a guideline of level 53 responsibilities:

   - An Immortal must spend at least 5-7 hours per week or at least
     25 hours per month online to remain active and productive
   - Must be visible to all mortals, unless involved in running a
     quest, watching someone or building.
   - Authorization of new characters
   - Channel monitoring -- should keep all channels on
   - Appraising higher Immortals of Mortal rule violations
   - Advise a 55+ of all reimbursement requests from mortals
   - Cr's at discretion, monitoring note boards, remaining VISIBLE
   - Learning proper mortal discipline techniques and punishments
    - Helping 51 and 52 level immortals as needed.
   - Possible room building work
   - Possible work at 5500 if interested in building or coding
   - Possible council work

Type 'wizhelp' to view your privileged commands.  For a list of Immortal
rules, 'help imm'.  Visit note boards at 1200, 1213, and 1214 regularly.
]],
  },
  {  
    keywords = {"DAMPLUS"},
    level = 51,
    htype = "wizhelp",
    text = [[
.
For those unsure of what damplus is, it is part of the damage
equation for a mob... ie:  10d6 + 10   (the +10 is the damplus)
This "damplus" is always added, whether or not the mob is barehanded or
wielding a weapon.   This is basically the mob's damroll.

]],
  },
  {  
    keywords = {"DAMTYPES", "ACTTYPES", "CLASSTYPES", "POWERTYPES"},
    level = 53,
    htype = "wizhelp",
    text = [[
DAMAGE          ACTION       CLASS         POWER       SAVES
none            none         none          none        none
fire            create       lunar         minor       poison_death
cold            destroy      solar         greater     wands
electricity     resist       travel        major       para_petri
energy          suscept      summon                    breath
acid            divinate     life                      spell_staff
poison          obscure      death
drain           change       illusion

]],
  },
  {  
    keywords = {"DEFENSES"},
    level = 53,
    htype = "wizhelp",
    text = [[
parry        dodge      heal       curelight   cureserious   curecritical
dispelmagic  dispelevil sanctuary  fireshield  shockshield   shield
bless        stoneskin  teleport   monsum1     monsum2       monsum3
monsum4      disarm

See MSET and ATTACKS  (Some are not implemented).
]],
  },
  {  
    keywords = {"DEITIES"},
    level = 65,
    htype = "wizhelp",
    text = [[
Used to list the various deities available for worship.]],
  },
  {  
    keywords = {"DEITYFIELD2", "DEITYFIELDS2"},
    level = 58,
    htype = "wizhelp",
    text = [[
Flee, flee_npcrace, flee_npcfoe: favor adjustment made when fleeing

Kill, kill_npcrace, kill_npcfoe: favor adjustment made when you kill something

Kill_magic: favor adjustment for each offensive spell cast

Sac: favor adjustment for sacrificing a corpse

Bury_corpse/dig_corpse: Favor adjustments for burying/digging up corpses.

Aid_spell: favor adjustment for helping someone with a spell

Aid: favor adjustment for aiding someone physically (aid, rescue)

Steal: favor adjustment for theft

Backstab: favor adjustment for circling and backstabbing

Die, die_npcrace, die_npcfoe: favor adjustment for dying

spell_aid: favor adjustment for having a help spell cast upon you.
]],
  },
  {  
    keywords = {"DEITYFIELDS DEITYFIELD"},
    level = 58,
    htype = "wizhelp",
    text = [[
Alignment: Deities alignment.  Followers lose favor for all actions when
650 or more out of alignment.

Worshippers: # of followers.

Npcrace: A mob race protected by the deity.  The _npcrace fields only apply
to this race.

Npcfoe: A mob race detested by the deity.  The _npcfoe fields only apply to
this race.

Race: A race the deity is restricted to.
Class: A class the deity is restricted to.

Sex: A sex the deity only accepts.

Element: Resistance deity bestows on followers.

Suscept: Susceptible deity bestows on followers.

Affected: Spell deity bestows on followers.

Object: vnum of deity object

Avatar: vnum of deity avatar

Scorpse, Savatar, Sdeityobj, Srecall: Prices (in favor) to supplicate for these
for a particular deity.

SEE HELP DEITYFIELDS2
]],
  },
  {  
    keywords = {"DELAY"},
    level = 58,
    htype = "wizhelp",
    text = [[
Syntax: delay <victim> <rounds>

This command will allow an immortal to "pause" a player. All commands
received by the mud from that player will be delayed by the number of
round determined by the delaying immortal. After the rounds have
elapsed, anything input by the victim during the delay will take affect
on the mud.
NOTE: Mobiles cannot be delayed.
]],
  },
  {  
    keywords = {"DELETE", "DELET"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: delete

Totally destroy this character, you will be asked for your password to confirm
this.  This is a one way thing.  Please be very careful.
]],
  },
  {  
    keywords = {"DENY", "DISCONNECT", "FREEZE"},
    level = 58,
    htype = "wizhelp",
    text = [[
Syntax: deny       <character>
Syntax: disconnect <character>
Syntax: freeze     <character>

DENY denies access to a particular player and throws them out of the game.
DENY persists past reboots and crashes and can only be undone by either loading
up the character and doing a 'mset <character name> flags deny', or by editing
the player file offline.

DISCONNECT <character> immediately disconnects that character.

FREEZE <character> is a toggle which prevents a character from issuing any
commands at all.
]],
  },
  {  
    keywords = {"DESTROY", "DESTRO"},
    level = 65,
    htype = "wizhelp",
    text = [[
-----------------------------------------------------------

     SYNTAX:  destroy <target>

DESCRIPTION: The DESTROY command does exactly as it suggests:
             destroys player files. Caution, the command
             destroys the pfile in use, leaving only the
             backup of the pfile, if there is one. It will
             also remove the locker file associated with that
             player and place it in a backup directory.

-----------------------------------------------------------
]],
  },
  {  
    keywords = {"DESTROYSLAY"},
    level = 55,
    htype = "wizhelp",
    text = [[
Syntax: destroyslay <type>

This command deletes a slay type from the table of options.

See also: SETSLAY, SHOWSLAY, MAKESLAY, SLAY]],
  },
  {  
    keywords = {"DEVOTE"},
    level = 65,
    htype = "wizhelp",
    text = [[
Can be used to have a character worship a deity.]],
  },
  {  
    keywords = {"DIAGNOSE"},
    level = 61,
    htype = "wizhelp",
    text = [[
Syntax:  diagnose of 20

Diagnose of n - object frequency of top "n" objects.  The above example will
return the 20 most numerous object vnums in the game at that time.
]],
  },
  {  
    keywords = {"DICEFORMULAS"},
    level = 55,
    htype = "wizhelp",
    text = [[
To make the special SMAUG spells possible, special dice formula handling
had to be coded in.  (At least to make it nice).  This dice formula code
supports full BEDMAS expressions ( ) ^^ / * + -, plus extra mud related
operators and variables:

D dice         L level          H hit points      M mana
V movement     S strength       I intelligence    W wisdom
X dexterity    C constitution   A charisma        U luck
Y age

Group variables:
B group members - includes mobs
Z group members - PC members only

Percent modifiers:
T# hp percent
G# mana percent
O# move percent
P# percent of max hp
N# percent of max mana
E# percent of max moves

When using percent modifiers, you should indicate the maximum number
to be applied with these options.

T, G, O useage -
Example: To apply 25 damage roll when the player is at 100% health, you
would use T25 as the formula.

P, N, E useage -
Example: To apply 20% of a player's max health to a player, you would use
P20 as the formula. If the player has 250hp max, then this would apply 50hp.

Never use T, G, O, P, N or E without a number.

See SMAUGSPELLS and SSET.
]],
  },
  {  
    keywords = {"DMESG"},
    level = 57,
    htype = "wizhelp",
    text = [[
Syntax: dmesg

Displays the contents of the boot log.

If you have the ability, please fix any problems found in the boot log.
]],
  },
  {  
    keywords = {"DND"},
    level = 51,
    htype = "wizhelp",
    text = [[
On or off syntax: DND

This command toggles your personal dnd flag.
This command effectively secludes immortals from those of lower level.
Each immortal has a personal dnd flag associated with their pfile. In
addition, each room can have a dnd flag associated with the room.

When your personal dnd flag is set, lower level imms can't 'at', 'goto',
'trans', sight you on 'where' or 'where (name). This does not affect LD
immortals, they can still be transferred, even with the DND flag on. To
see the flag's status, 'mstat self', it will be listed under 'pcflags'.
Syntax for room flag: redit flags DND

The DND room flag effectively blocks any 'at', and 'goto' commands
either to the room, or to a mob/object in the room. NOTE: It is only
in effect if:
a) there is an immortal in the room with their DND flag on.
b) the immortal attempting the commands is of lower level than the
   immortal with the activated DND flag in the room.
]],
  },
  {  
    keywords = {"DOORDIRS"},
    level = 53,
    htype = "wizhelp",
    text = [[
Here is the order of the exits, and their corresponding values:

  ---------------------
  | Direction | Value |
  |--------------------
  | NORTH     |   0   |
  | EAST      |   1   |
  | SOUTH     |   2   |
  | WEST      |   3   |
  | UP        |   4   |
  | DOWN      |   5   |
  | NORTHEAST |   6   | Exits 6 - 10 are relatively new, and may not be
  | NORTHWEST |   7   | fully supported by all of the code yet.
  | SOUTHEAST |   8   |
  | SOUTHWEST |   9   |
  | SOMEWHERE |  10   |
  ---------------------

See REDIT, RSTAT and RESETCMDS.
]],
  },
  {  
    keywords = {"ECHO", "RECHO"},
    level = 52,
    htype = "wizhelp",
    text = [[
Syntax:  echo      <color> <message>
         echo  imm <color> <message>
         echo  pc  <color> <message>
Syntax:  recho     <color> <message>

ECHO sends a message to all players in the game, without any prefix indicating
who sent it.  If 'echo imm <message>' is used, only level 51+ characters will
see the message. If 'echo pc <message>' is used, only player characters will
see the message.

ECHO done in color should avoid the use of red and dark red unless it is a
Urgent message containing important information related to the game.

RECHO sends a message to all players in your room, without any prefix
indicating who sent it.

See also : COLOR 'IMM ECHO'
]],
  },
  {  
    keywords = {"ECONOMY"},
    level = 51,
    htype = "wizhelp",
    text = [[
Each area will initialize (on bootup of the mud) with a pool of gold based
on the area's range and the wealth of each mob in that area.

The shopkeepers and thieves will automatically deposit gold into the economy
if they are carrying more than a certain amount (the higher the level of the
shopkeeper, the greater they will carry before depositing).

To allow mobprogs to be created to manipulate area economies, making them
interactive and interdependent, there are two mpcommands:  mpdeposit, and
mpwithdraw (see related helpfiles).  There is also an 'if economy' ifcheck.

The aset command can also be used to adjust an area's economy by hand
(example:  aset <area filename> low_economy <amount>, this will give
the specified area a minimum economy at the level you set).

Mobs will not repop with more gold than what they were originally created
with, but if the area economy runs low they will begin to repop with less
until the economy is replenished (as they all share the same gold pool).

Use foldarea to make changes to an area's economy with aset permanent.

See ASET, FOLDAREA
]],
  },
  {  
    keywords = {"ELEVATE"},
    level = 51,
    htype = "wizhelp",
    text = [[
syntax: elevate (name)

Elevate is for advancing neophytes to acolytes and acolytes to creator.
]],
  },
  {  
    keywords = {"EXFLAGS"},
    level = 51,
    htype = "wizhelp",
    text = [[
The redit exflags <dir> [flag] ... command accepts the following flags:

ISDOOR        | There is a door in that direction
CLOSED        | The door is closed
LOCKED        | The door is locked
SECRET        | The door is a secret door
PICKPROOF     | Door is pickproof
FLY           | Must be able to fly to go that way
CLIMB         | Must be able to climb to go that way
DIG           | Passage is blocked and must be dug out
NOPASSDOOR    | Door is resistant to the passdoor spell
HIDDEN        | Door is not "obvious" -- doesn't appear with autoexits
CAN_CLIMB     | Can use the climb command to go this way
CAN_ENTER     | Can use the enter command to go this way
CAN_LEAVE     | Can use the leave command to go this way
AUTO          | Keyword can be typed to go this way
SEARCHABLE    | Searching in this direction can remove the SECRET flag
BASHED        | Denotes a door that has successfully been bashed open
BASHPROOF     | Cannot bash the door
NOMOB         | Mobs may not pass through this exit
WINDOW        | Points to a destination, but does not allow direct access to it
CAN_LOOK      | Allows a person to view the destination room for a WINDOW exit
PUSHTYPE      | Players will be pushed or pulled by a type of force.
PUSH          | Players will be pushed or pulled with a degree of force.
]],
  },
  {  
    keywords = {"EXITMAKING"},
    level = 51,
    htype = "wizhelp",
    text = [[
The 'redit exit' command is used to create, modify and remove exits in a room.
Currently there can only be one exit in a certain direction.
The syntax of the 'redit exit' command is as follows:
redit exit <direction> [vnum] [exit-type] [key] [keyword(s)]
direction: one of: n, s, e, w, u, d, ne, nw, se, sw or ?
vnum     : the room number in which the exit leads to.
exit-type: a number detailing the exit -- has a door, open/closed/locked etc.
key      : a number corresponding to a key object which can unlock the door.
keywords : keywords used to refer to the door, (or exit).

If only 'redit exit <direction>' is specified, the exit will be removed.
The 'key' field is optional when specifying keywords.  All other fields are
required previous to the field desired.

Examples:
redit exit n 3001           - Creates an exit north to room 3001
redit exit n 3001 3 gate    - Changes the exit north to have a closed "gate"
redit exit n 3001 3 15 gate - Changes the gate to allow use of a key vnum 15
redit exit n                - Removes the north exit

See EXITTYPES for generating the exit-type value.
]],
  },
  {  
    keywords = {"EXITTYPES"},
    level = 51,
    htype = "wizhelp",
    text = [[
These are the currently valid exit-types:
      0 - Plain exit
      1 - Door exists         (Required to be closed or locked)
      2 - Door is Closed
      4 - Door is Locked
      8 - Door is Secret      (Trying to go that way won't reveal door)
     32 - Door is Pickproof   (Door can't be picked by spell or skill)
     64 - Need to be able to fly to go that way
    128 - Need to be able to climb to go that way
   1024 - Door is Passdoor proof

NOTE: You must ADD the values together to generate an exit-type:
        3 = a closed door
        7 = a closed and locked door
       11 = a closed secret door
       15 = a closed, locked and secret door

-- Use the 'redit exflags' command to change these flags, and to set the
   advanced exit flags, most of which are not shown above.

See EXFLAGS and EXITMAKING.
]],
  },
  {  
    keywords = {"FIXCHAR"},
    level = 65,
    htype = "wizhelp",
    text = [[
Will restore stats upon a character that has corrupted values.
This is done automatically at login.
]],
  },
  {  
    keywords = {"FIXCHARMIE"},
    level = 52,
    htype = "wizhelp",
    text = [[
Syntax: fixcharmie charmed mob player

After a hotboot, charmed mobs will stay charmed, but lose their masters.
In addition, if the charmed mob was mounted, that mounted flag will not
clear and the mob cannot be re-mounted.  So...the fixcharmie command
will force the mob to follow the player again, and clear the mounted flag
if it was set.

You must be in the same room as the player and mob (they must be in the same
room together, of course) for this to work.  Make sure the charmed mob really
does belong to the player.
]],
  },
  {  
    keywords = {"FIXED"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax:  fixed <message>
         fixed list

This command records your message (250 chars or so max) to a permanent
record file.  All changes made to live areas, made with foldarea, etc.
should have some kind of entry recorded here.

Your name and the roomvnum in which you are standing at the time are
automatically recorded when you use the command.

If you post a note about the change, please make a fast entry pointing
it out.  (The board in 1215 is best for such notes.)

Using 'fixed list' will display the contents of the current fix record.

NOTE:  This file supports color tokens, be careful with them.
]],
  },
  {  
    keywords = {"FIXMOBM"},
    level = 52,
    htype = "wizhelp",
    text = [[
Syntax: fixmobm victim

Sometimes crashes or hotboots will break a MobMaster Quest.  This command will
check a player and, if needed, fix their quest.  This will not reset a quest
the player finds difficult, it will only reset a broken quest.
]],
  },
  {  
    keywords = {"FOLDAREA"},
    level = 56,
    htype = "wizhelp",
    text = [[
Syntax:  foldarea <area filename>

This command saves an area file, usually after modification.

&rThis command must be used with extreme care.  If you aren't
exactly and intimately familiar with the changes being made
or what the command does -- don't use it.&w

*NOTE*
Area files have backups that record the file as it was prior to foldarea.
If you folda something and realize there's a mistake, and you've only
folded it once -- don't do anything else.  Post a note or find Drazuk.

Do not fold changes into non-quest areas that are quest related.  If you
must do this, write a note or ensure it's changed back.

Any time an area is folded, document it with the fixed command.
(check 'help fixed')

See ASET, UNFOLDAREA and INSTALLAREA.

]],
  },
  {  
    keywords = {"FOR"},
    level = 65,
    htype = "wizhelp",
    text = [[
Hmm, looks like a global command that can be dangerous.  Check out later,
don't mess with it now (:
]],
  },
  {  
    keywords = {"FORCE"},
    level = 52,
    htype = "wizhelp",
    text = [[
Syntax: force <character> <command>
Syntax: force all <command>

FORCE forces one character or mob to execute a command.

FORCE 'all' forces all player characters to execute a command.
This is typically used for 'force all save'.

Immortals are expected to use good judgement when using force...lets not make
it a problem command.

  *Note.. NEVER force a mob to drop eq and give to a player..lest God
   smite thee down in your very tracks.
]],
  },
  {  
    keywords = {"FORCECLOSE"},
    level = 54,
    htype = "wizhelp",
    text = [[
Syntax: forceclose <descriptor>

This command will force a certain descriptor to close.
This is useful to disconnect connections that aren't really connected
due to a poor TCP connection.

It can also be used to forceclose a connection before a potential
problem player can even get to the authorization state of connection.

See USERS, CONSTATES and DISCONNECT.
]],
  },
  {  
    keywords = {"FORMPASS"},
    level = 65,
    htype = "wizhelp",
    text = [[
Used to check the results of an encrypted password.  Use NEWPASSWORD instead.]],
  },
  {  
    keywords = {"FQUIT"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: fquit <character>

FQUIT forces a level one player to quit.

It is used in case you accidently authorize a bad name.

Please be sure to send a tell to the player explaining why you are
forcing them to quit before using FQUIT.

]],
  },
  {  
    keywords = {"FSHOW"},
    level = 58,
    htype = "wizhelp",
    text = [[
-----------------------------------------------------------

     SYNTAX: fshow <moblog | plevel>

DESCRIPTION: The FSHOW command when used with the MOBLOG
             variable, displays the current log of MPLOG. When
             FSHOW is used with the PLEVEL variable, it will
             display the current log of all character levels
             that have occurred since the last reboot.

-----------------------------------------------------------
]],
  },
  {  
    keywords = {"FURNITUREVALUES"},
    level = 52,
    htype = "wizhelp",
    text = [[
It is now possible to sit/sleep/rest/stand on furniture.
Here is how all of this works.
value2 - sit/sleep/rest/stand on furniture (more below)
As for value2, it uses bitvictors, and here are their numbers
SIT ON -    1        SIT IN -    2        SIT AT -    4
STAND ON -  8        STAND IN -  16       STAND AT -  32
SLEEP ON -  64       SLEEP IN -  128      SLEEP AT -  256
REST ON -   512      REST IN -   1024     REST AT -   2048
Furniture is set using the v2 setting and through adding the
values to make it work.  Say you want SIT ON and STAND IN, you
would add 1 and 16 and get 17.
A quick note, you can only be on in at an object.  If you
set all 3 of them to lets say Sit, when type type sit
object, they will sit at the object.  So only select
one.
Furniture Code 1.01 provided by Xerves of Rafermand.
]],
  },
  {  
    keywords = {"GFIGHTING"},
    level = 61,
    htype = "wizhelp",
    text = [[
-----------------------------------------------------------

     SYNTAX: gfighting
             gfighting <low> <high>
             gfighting <low> <high> mobs

DESCRIPTION: The GFIGHTING command does a global search
             for the fighting targets specified, where
             <low> <high> indicates the target's level.

    EXAMPLE: gfighting 1 5 would display a list of PCs
             levels one through five that are fighting,
             who they are fighting and their level, what
             vnum/room name they are fighting in, and the
             name of the area they are fighting in. By
             adding the 'mobs' variable, the command
             would display the same information for mobs
             of the levels specified.
]],
  },
  {  
    keywords = {"GLORYIMM"},
    level = 51,
    htype = "wizhelp",
    text = [[
Some things to keep in mind when giving/taking Glory:

  - Glory is UNtradable between mortals.  (Please do not facilitate trades of
         Glory between mortals.
  - Glory can be "sold" by mortals for direct char changes, but Drazuk
requests this be ran by him before it is done.
  - Currently, appropriate prizes to be awarded for quests are as follows:

  Avatar quests (lvl 40+):
         Suggested Maximum:  500 Glory  (For playing an integral part)
         Suggested Minimum:   50 Glory  (For making a notable effort)
    - Then Glory of appropriate amounts (use your judgement) can be given out
         for intermediate efforts between winning and participating.

  NOTE:  Being integral doesn't necessarily mean landing the killing blow on
         the supermob, it might also mean the person who solved the riddle
         leading to the mob (if it was a difficult riddle).
  NOTE:  Prizes should be scaled up or down to reflect the difficulty and
         participation of the quest.  For example a difficult quest would be
         one that takes more than 2 hours to complete.

  Non-Avatar quests (lvl < 40):
         Suggested Maximum:  350 Glory  (For an integral part)
         Suggested Minimum:   50 Glory  (For a notable effort)
See also: GLORYIMM2, QPSET, GLORY
]],
  },
  {  
    keywords = {"GLORYIMM2"},
    level = 51,
    htype = "wizhelp",
    text = [[
.    Glory does not necessarily have to be the only prize given out.  In fact
     for the lower level quests it is preferred if a combination of Glory and
     minorly affected/renamed objects are given out as prizes.  i.e. a weapon
     renamed to something related to the quest that has a couple +1's or +2's
     on it (that will be useful for a couple levels, but then discarded).



     DISCLAIMER:  These numbers are not set in stone, they are guidelines.  The
                  QC is counting on the good judgement of the immortals to
                  make sure the prizes they are giving out are appropriate.
                  The QC reserves the right to change the guidelines as well
                  the right to set them in stone if we find it is being abused.

See Also: GLORYIMM, GLORY, QPSET.
]],
  },
  {  
    keywords = {"GOTO", "REGOTO"},
    level = 52,
    htype = "wizhelp",
    text = [[
Syntax: goto <location>

GOTO takes you to a location.  The location may be specified as a vnum,
as the name of a mobile, or as the name of an object.

If the location is a vnum, and it does not already exist, and it is within
your room vnum range; it shall be created for your to edit further with
REDIT.

You may not GOTO a room if it is PRIVATE and has two (or more) characters
already present, or if it is SOLITARY and has one (or more) characters
already present.

REGOTO takes you back to where you where.

You may also "GOTO pk" to go to the site of the most recent illegal pkill.
See REDIT.
]],
  },
  {  
    keywords = {"GRANTSIGHT", "GS"},
    level = 55,
    htype = "wizhelp",
    text = [[
Syntax:  grantsight victim

Grantsight turns on godsight on your victim.  This allows the victim to see
an immortal even if they are wizinvis at a level higher than the player. The
same command turns it on and off of a player. There is a limit of 10 on the
number of immortals that can grantsight a single player. Grantsight does not
last once the player has logged out.
]],
  },
  {  
    keywords = {"GRUB"},
    level = 51,
    htype = "wizhelp",
    text = [[
.Here is some reference data you will need in order to use GRUB.
 Sex          Class       Race         Fields   Clans    Councils
 0 Neutral  0 Mage      0 Human        Name     1 Guild  1 CoE
 1 Male     1 Cleric    1 Elf          Sex      2 DS     2 MC
 2 Female   2 Thief     2 Dwarf        Class    3 MS     3 NC
            3 Warrior   3 Halfling     Race     4 RB     4 Pro
            4 Vampire   4 Pixie        Level    5 AR     5 PK
            5 Druid     5 Vampire      Room     6 Bru    6 QC
            6 Ranger    6 Half Ogre    Gold     7 Las    7 Neo
            7 Augurer   7 Half Orc     Clan     8 Nos    8 CC
            8 Paladin   8 Half Troll   Council  9 Tre    9 AC
            9 Nephandi  9 Half Elf     Site    10 Ven   10 TS
                            10 Gith         Last    11 Inc
                             11 Drow     Pkill
                             12 Sea-elf
                             13 Lizard
                             14 Gnome
                                      Pkill

Here are some sample uses of GRUB:

grub 20 pkill=y class=5      Display 20 Druid pkillers
grub 20 level=2 last<=970120 Display 20 L2 players absent since 970120
grub 20 level>=20 level<=30  Display 20 players levels 20 thru 30
grub  0 level=2              Count the number of level 2 players
grub 20 level>50 gold>100000 Display 20 imms with more than 100k gold
grub 50 damroll>100 sex=2    Display 50 females with damroll>150
grub  0 class=5 damroll>150  Count the number of druids with damroll>100
grub 20 site<>123.456.789    Display 20 players from site 123.456.789
grub 10 class=0 race=2       Display 10 dwarven mages
grub  1 name=Joe             Display Joe's info
grub 20 room=7070 class=0    Display 20 mages who logged off in 7070
grub  0 class!=2 class!=3 class!=4   Count the number of mana users

You always need to specify the number of lines you want displayed. The
reason for that is that we don't want to ask for a list and then get
surprised to find that it's 15,000 lines long. You can get a count
of the players that match your criteria by requesting zero lines.

GRUB will tell you how many lines there are in the list no matter how
many you ask to display. So if there are 15,000 players that meet your
criteria and you ask for the first ten, GRUB will tell you there are
15,000 in total but will only show you the first ten.


See also: HELP 'GRUB EXAMPLES'

]],
  },
  {  
    keywords = {"GRUB EXAMPLES"},
    level = 51,
    htype = "wizhelp",
    text = [[
Here are some examples illustrating common usages:

Example:

grub 20 or hitroll>150 damroll>150 gold>200000000

Suppose you want to search for "suspicious players". Suppose you want
to see players who have more than 200 million gold or whose damroll
exceeds 150 or whose hitroll exceeds 150 you can do that as follows:

Normally GRUB lists players who satisfy all the conditions you specify.
But it can also be used like this to list players who satisfy any one of
the conditions.

The operand "or" ensures GRUB will list players who satisfy any one of
the conditions.

If you had specified:

grub 20 hitroll>150 damroll>150 gold>200000000

That would show you players whose hitroll exceeds 150 and whose damroll
exceeds 150 and whose gold exceeds 200 million. It would be a much
smaller list and you would miss many suspicious players.

Example:

grub 20 name>ska name<skb room>=21000 room<=21499

Suppose someone complains that a player with a name like "Skathamaga"
picked up some of their eq and promptly quit the game. The player isn't
sure of the exact name of the thief but is sure it starts with "Ska".
The thief quit the game somewhere in Alden (vnums 21000-21499).

This example will show you players whose name starts with "Ska" and who
last quit the mud somewhere in Alden.

]],
  },
  {  
    keywords = {"GRUB2"},
    level = 54,
    htype = "wizhelp",
    text = [[
Syntax: grub # <or> field operator ## <field operator ##>
Where:  &g#         &GAny valid number.
        &g<or>      &GUsed with multiple expressions to denote that only one of
                  them need be true.
        &gField     &GName, Sex, Class, Race, Level, Room, Gold, Hitroll,
                  Damroll, Site, Last, Pkill.
        &gOperator  &GValid operators are:   =   !=   >   <   >=   <=
        &g##        &GNumeric except for Name and Pkill. For name it is a full
                  or partial name. For Pkill it is a Y or N.

&GLast is:  &WExpressed as "YYMMDD". ie, 970122 is Jan. 22/97.
&GSex is:   &W0 Neutral  1 Male       2 Female
&GClass is: &W0 Mage     1 Cleric     2 Thief     3 Warrior     4 Vampire
          5 Druid    6 Ranger     7 Augurer
&GRace is:  &W0 Human    1 Elf        2 Dwarf     3 Halfling    4 Pixie
          5 Vampire  6 Half Ogre  7 Half Orc  8 Half Troll  9 Half Elf
         10 Gith&w
&GYou can have more than one conditional expression in a Grub search. "And" is
assumed unless "or" is placed before the arguments. ie:
&W    Grub 10    class=3 sex=2    (Gives back a list of 10 female warriors)
    Grub 10 or class=3 sex=2    (Gives back a list of 10 characters that
                                 are either female, or warriors).
You must always specify how many lines the Grub will produce. This prevents
your getting a list 15000+ lines long.

&YSee also: &W'GRUB EXAMPLES', OGRUB
]],
  },
  {  
    keywords = {"GUILD", "GUILDS"},
    level = 65,
    htype = "wizhelp",
    text = [[
Guilds are special organizations for each class within the realms. Belonging
to a Guild has many advantages, such as gaining new knowledge of your class,
making new friends in the Realms, exciting quests, the great feeling of
helping other players, and many other aspects of Guild life make being in a
Guild a memorable experience.  Each Guild has its own separate headquarter
with a healer, a practice room, a Guild store, and many other rooms that makes
each Guild unique unto itself.

Membership in a Guild is not something that is easily obtained, and you must
be a law-abiding player.

There are rules within each Guild, and along with these rules, you must
follow the rules of this MUD.

To gain entry into a Guild, you should speak with a leader of the Guild.  The
leaders are those people who have the title <Leader>, <First> and <Second>.
To find out who is on from a Guild, type "who 'Guild of *****'.  For example,
if you are a Druid, and you wish to find out who is on from the Guild of
Druids, type "who 'Guild of Druids", and you will be given a list of players
that belong to the Guild.

Type &Ghelp guild rules&w for a list of rules about Guild equipment and items.
]],
  },
  {  
    keywords = {"GUILD RULES"},
    level = 65,
    htype = "wizhelp",
    text = [[
.
&RIt is illegal to sell, trade, auction or give away Guild items.&w Including
potions, pills, scrolls, equipment and containers.  Anything you can buy in
a Guild house is off limits for selling.  If you are found to be trading in
these illegal items, you stand the chance of not only being outcast from your
Guild, but your Guild may lose the ability to sell those items.

Please do not engage in buying such items either, as the Immortals reserve
the right to remove Guild items from ANY person not belonging to that Guild.
Just because you can buy it on the "black market" does not mean the Immortals
will allow you to keep it.

If you are in doubt whether an item is a Guild item, you are free to ask an
Immortal. Most Guild items have the name "guild" on it when you use identify.

There are rules that are specific to Guilds.  If you are not sure if something
is legal or illegal within your Guild, please contact a leader.
]],
  },
  {  
    keywords = {"GUILDTALK"},
    level = 65,
    htype = "wizhelp",
    text = [[
Syntax:  guildtalk <message>

Provided that you are in a Guild, guildtalk will send the message to
all members currently online.
]],
  },
  {  
    keywords = {"GWHERE"},
    level = 63,
    htype = "wizhelp",
    text = [[
-----------------------------------------------------------

     SYNTAX: gwhere
             gwhere <low> <high>
             gwhere <low> <high> mobs

DESCRIPTION: The GWHERE command displays a global location
             list of the targets specified; name of target
             and level, vnum/name of room, and name of area
             are all displayed, where <low><high> indicates
             the level of the players or MOBs. If level
             criterias are note defined, all will be displayed.

-----------------------------------------------------------

SEE ALSO: GFIGHTING
]],
  },
  {  
    keywords = {"HEDIT"},
    level = 54,
    htype = "wizhelp",
    text = [[
Syntax: hedit [help topic]

This command allows you to edit a help topic.  If the specified help topic
does not exist, it will be created for you. The default help page (summary)
will be selected if you do not specify a page.

NOTE - Always, when creating a new help entry, type Help <new entry name>
       prior to creating your entry. A pre-existing help file associated
       with that keyword may already exist.
&Y
Colors &wcan now be added to help files using the same command set that changes
a player's prompt. &bMultiple &Ycolor &wcombinations can be set on a given line
including ^bbackground^x colors. However there are a couple of quirks to take
note of:
&Y
    1) At the very least, the first character of a help file cannot be
       either the symbol '&&' or the symbol '^^'.
    2) Color changes have to be separated by at least one character. ie,
       '&&Y.^^r' will work, '&&Y^^r' will cause problems.
    3) Color codes are imbedded within text and _do_ count in note buffers
       for line length. ie, watch out for <Long Line Trimmed>.
&w
Colors should be used to &Yenhance &wthe help file, or specific parts of the
help file. Tact and restraint should be used if considering the use of colors.


See HSET, PCOLORS.
]],
  },
  {  
    keywords = {"HELL", "UNHELL"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: hell <character> <number> <hours or days>
Syntax: unhell <character>

The hell command sends a character to hell for a given period of time.  It
automatically releases the character when their time has been served.  Upon
being helled, the character receives the message, "The immortals are not
pleased with your actions.  You shall remain in hell for <time period>".

Hell takes arguments of either hours or days.  To hell someone for 3 hours,
"hell <character> 3 hours".  To hell someone for three days, "hell <character>
3 days".  Hell will default to hours if hours or days is not specified.

You may not hell someone for more than thirty days with the hell command.

To release a player from hell, simply "unhell <character>".
]],
  },
  {  
    keywords = {"HOLYLIGHT", "INVIS"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: holylight
Syntax: invis

HOLYLIGHT is a toggle that allows you to see (almost) every character and
mobile in the game.  With holy light, you can see what's in the game more
easily.  Without holy light, you can see what mortal players see.

INVIS is a toggle which makes you completely invisible to all player characters
of lower level than you, and to all mobiles.

When an immortal is INVIS, they will have a flag on the who list which
indicates their level of invisibility, such as (51) for INVIS 51.  A
similar flag will also appear when you 'LOOK' in a room - this flag will
say (Invis 51).

HOLYLIGHT will not allow you to see immortal INVIS characters who are
higher level than you.
]],
  },
  {  
    keywords = {"HSET"},
    level = 54,
    htype = "wizhelp",
    text = [[
Syntax: hset  <command> [value] [help topic]
 save                            Saves all help pages (to help.are)
 level <level> <help topic>      Sets help topic to specified level
 keyword <keyword> <help topic>  Sets help keyword to specified keyword
 remove <level.><help topic>     Removes the specified help page

Note:  If you wish to set more than one keyword to a help topic, enclose all
       the keywords, space separated inside quotes.  (Like in spellcasting)
Note:  If you have instances of multiple help files with the same keyname,
       using Hset Remove without a level designation will remove the one with
       the lowest level of access. ie:

       Help file XYZZY at level 57, and help file 'SAVE XYZZY' at level 58.
       Typing 'HSET REMOVE XYZZY' will remove the level 57 XYZZY.
       Typing 'HSET REMOVE 58.XYZZY' will remove the level 58 'SAVE XYZZY'.

Setting a help entry level to -1 prevents the header from showing up
when you view the help with the help command.
See also: HEDIT

]],
  },
  {  
    keywords = {"IFCHECK CANPKILL"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

     &GEXAMPLE:     &cif canpkill($n)
                  mpechoat 0.$n Your fate awaits, $n.
 &GDESCRIPTION:     &cThe CANPKILL ifcheck is used to determine
                  if the target is a:
                     - Minimum age of 17,
                     - Minimum level of 5.

&r*-------------------------------------------------------------------*&w

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK CANSEE"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif cane($n)
                          '$n can see just fine!

          &GDESCRIPTION:    &cThe CANE ifcheck is used to determine if
                          the target is able to see.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK CHA"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif cha($n) > 18
                         'You're very charismatic, $n!

        &GDESCRIPTION:     &cThe CHA ifcheck is used to direct a command
                         based on the charisma stat of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK CHARCOUNT"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:    &cif charcount(21000) > 10

      &GDESCRIPTION:    &cCHARCOUNT ifcheck counts the number of chars
                      in the specified room. This example returns TRUE if
                      there are more than 10 chars in room 21000.
                      You can use this form in room or mob programs and
                      you can have one room program check the number of
                      chars in a different room.
                      Note the number of characters is defined as the
                      number of mortals plus the number of mobs.

          &GEXAMPLE:    &cif charcount(0) > 10

      &GDESCRIPTION:    &cUse a zero room number if you want to have
                      a mob check the number of chars in its room.
                      Note that if the mob changes rooms, the ifcheck
                      applies to whatever room the mob is in.
                      You should use this form in mob programs only.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK CLAN"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

      &GEXAMPLE:   &cif clan($n) == inconnu
                 tell 0.$n You're an Inconnu!

  &GDESCRIPTION:   &cThe CLAN ifcheck is used to determine if the
                 target belongs to a Clan or Order.

&r*-------------------------------------------------------------------*

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK CLANTYPE"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif clantype($n) == 15
                          '$n belongs to an Order.

          &GDESCRIPTION:    &cThe CLANTYPE is used to determine what
                          type of clan the target belongs to.
&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK CLASS"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

     &GEXAMPLE:        &cif class($n) == 0
                     t 0.$n You're a mage!

 &GDESCRIPTION:        &cThe CLASS ifcheck is used to determine the
                     class of the target. (HELP NPCCLASSES)

         &GNEW:        &cismage($n)      iscleric($n)   isthief($n)
                     iswarrior($n)   isthug($n)     isdruid($n)
                     isranger($n)    ismonk($n)     isdiabolist($n)
                     isconjurer($n)  isjester($n)   isshaman($n)
                     isarchmagi($n)  isbishop($n)   ischampion($n)
                     isrogue($n)

 &GDESCRIPTION:        &cThese work similarly as the above "class"
                     ifcheck but allow more flexibility. For instance;
                     ismage($n) will return true if the character's
                     primary class is mage, dualclass is mage or if they
                     are an archmagi (the tier of mage.)

 &r*-------------------------------------------------------------------*

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK CON"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif con($n) < 5
                         'You're constitution is low, $n.

        &GDESCRIPTION:     &cThe CON ifcheck is used to direct a command
                         based on the constitution stat of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK COUNCIL"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:   &cif council($n) == 1
                     '$n is from the Council of Elders.

      &GDESCRIPTION:   &cThe COUNCIL ifcheck determines what
                     council the target belongs to.(HELP COUNCILNUMS)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK DEITY"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:      &cif deity($n) == vl'arescht
                      'May Thoric save your evil soul!

    &GDESCRIPTION:      &cThe DEITY ifcheck is used to determine who
                      the target is devoted to.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK DEX"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif dex($n) > 20
                         'You're pretty nimble, $n

        &GDESCRIPTION:     &cThe DEX ifcheck is used to direct a command
                         based on the dexterity stat of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK DOINGQUEST"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:
DESCRIPTION
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK ECONOMY"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif economy(21001) > 10000000
                          mpecho DH economy is booming!

          &GDESCRIPTION:    &cThe ECONOMY(rvnum) ifcheck is used to base
                          a command on the economy of the area the
                          checker is in. NOTE: area will be specified
                          by default to area the MOB is in, via rvnum.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK FAVOR"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif favor($n) == 2500
                         'You're well loved by your deity, $n.

        &GDESCRIPTION:     &cThe FAVOR ifcheck is used to determine the
                         amount of favor held by the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK GOLDAMT"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

     &GEXAMPLE:        &cif goldamt($i) > 10000
                    'I'm rich!

 &GDESCRIPTION:        &cThe GOLDAMT ifcheck determines the specified
                     amount of coins carried by the target.

 &r*-------------------------------------------------------------------*

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK GUILD"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:       &cif guild($n) == guild of thieves
                       'You belong to the GoT!

    &GDESCRIPTION:       &cThe GUILD ifcheck is used to determine
                       what guild the target belongs to, if any.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK HITPRCNT"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:   &cif hitprcnt($n) < 10
                         'You're going to dieeeeeee!

          &GDESCRIPTION:   &cThe HITPRCNT ifcheck is used to base a
                         command on the targets current hit points.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK HPS"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif hps($n) > 1900
                         'You're buff, $n!!

        &GDESCRIPTION:     &cThe HPS ifcheck is used to base a command
                         on the target's current hit points.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK INROOM"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

     &GEXAMPLE:         &cif inroom($i) == 1200
                      'Look at all the notes to read!

 &GDESCRIPTION:         &cThe INROOM(target) ifcheck is used to
                      determine the target's rvnum location.

 &r*-------------------------------------------------------------------*

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK INT"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:    &cif int($i) == 25
                        'I'm smart!

        &GDESCRIPTION:    &cThe INT ifcheck is used to direct a command
                        based on the intelligence of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISASUPRESSED"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif isasupressed($n) > 10
                          '$n's got a bit of wait ahead of them!

          &GDESCRIPTION:    &cThe ISASUPRESSED ifcheck checks the
                          target's asupress timer.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISATTACKER", "IFCHECK ISKILLER", "IFCHECK ISTHIEF"},
    level = 51,
    htype = "wizhelp",
    text = [[
-----------------------------------------------------------

     SYNTAX: if isattacker($n)
             say Didn't quite pull it off, did you?

DESCRIPTION: The ISATTACKER, ISTHIEF, and ISKILLER, if
             checks are used to determine if the target
             is flagged as an attacker/killer/thief.

-----------------------------------------------------------

SEE ALSO: MPPARDON, FLAGS, PARDON
]],
  },
  {  
    keywords = {"IFCHECK ISCHARMED"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r *-------------------------------------------------------------------*

     &GEXAMPLE:         &cif ischarmed($n)
                      'Wake up!

 &GDESCRIPTION:         &cThe ISCHARMED ifcheck determines if the
                      target is charmed.

 &r*-------------------------------------------------------------------*

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISDEVOTED"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif isdevoted($n)
                         'I see you have devoted your soul, $n.

        &GDESCRIPTION:     &cThe ISDEVOTED ifcheck is used to determine
                         if the target is devoted to a Deity.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISEVIL"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:    &cif isevil($n)
                      'Greetings, evil one.

      &GDESCRIPTION:    &cThe ISEVIL ifcheck is used to determine if
                      the targets alignment is lower than -350.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISFIGHT"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

     &GEXAMPLE:         &cif isfight($i)
                      yell Lookie Mom! I'm fighting!

 &GDESCRIPTION:         &cThe ISFIGHT ifcheck determines if the target
                      is fighting.

 &r*-------------------------------------------------------------------*

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISFOLLOW"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:

DESCRIPTION
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK ISGOOD"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:    &cif isgood($n)
                      'Always a pleasure, $n.

      &GDESCRIPTION:    &cThe ISGOOD ifcheck is used to determine if
                      the target's alignment is +350 or higher.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISIMMORT"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

     &GEXAMPLE:        &cif isimmort($n)
                     bow 0.$n

 &GDESCRIPTION:        &cThe ISIMMORT ifcheck determines if the
                     target is an Immortal.

 &r*-------------------------------------------------------------------*

   &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISLEADER"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:      &cif isleader($n)
                      '$n is an Order, Guild, or Clan leader.

    &GDESCRIPTION:      &cThe ISLEADER ifcheck is used to determine if the
                      target is a leader of an Order, Guild, or Clan.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISLOCKED"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif islocked($n) == 6
                         'The northeast exit is locked.

        &GDESCRIPTION:     &cThe ISLOCKED(dir) ifcheck is used to
                         determine if a specified exit is locked.
                         (HELP DOORDIRS)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISMORPHED"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif ismorphed($n)
                          '$n is not as they appear!

          &GDESCRIPTION:    &cThe ISMORPHED ifcheck is used to determine
                          if the target is morphed. (HELP MORPHTYPES)

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISMOUNTED"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

      &GEXAMPLE:        &cif ismounted($n)
                      mpforce 0.$n dismount

  &GDESCRIPTION:        &cThe ISMOUNTED ifcheck determines if the
                      target is mounted.

 &r*-------------------------------------------------------------------*

   &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISNEUTRAL"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:    &cif isneutral($n)
                      'Make up your mind, $n.

      &GDESCRIPTION:    &cThe ISNEUTRAL ifcheck is used to determine if
                      the target's alignment is:
                      - less than +350 and
                      - greater than -350

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISNPC"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif isnpc($n)
                         '$N is a Non-player character.

        &GDESCRIPTION:     &cThe ISNPC ifcheck is used to determine if
                         the target is a Non-player character. (MOB)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISNUISANCE"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif isnuisance($n)
                          '$n is a bit of a pest.

          &GDESCRIPTION:    &cThe ISNUISANCE ifcheck is used to determine
                          if the PC is nuisanced.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISOPEN"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:      &cif isopen($n) == 6
                        'The northeast exit is open.

      &GDESCRIPTION:      &cThe ISOPEN ifcheck is used to determine if
                        an exit is open in the specified direction.
                        (HELP DOORDIRS)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISPACIFIST"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif ispacifist($n)
                         '$n will not fight.

        &GDESCRIPTION:     &cThe ISPACIFIST ifcheck is used to determine
                         if the target is flagged pacifist. (MOB)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISPASSAGE"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif ispassage($n) == 6
                         'There is a passage leading northeast.

        &GDESCRIPTION:     &cThe ISPASSAGE(dir) ifcheck is used to
                         determine if there is an exit in the
                         specified direction. (HELP DOORDIRS)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISPC"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif ispc($n)
                         '$n is a Player Character.

        &GDESCRIPTION:     &cThe ISPC ifcheck is used to determine if
                         the target is a Player Character. (PC)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISPKILL"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif ispkill($n)
                         '$n is a deadly character.

        &GDESCRIPTION:     &cThe ISPKILL ifcheck is used to determine
                         if the target is a deadly character. (pkiller)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK ISSHELLED"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:       &cif isshelled($n)
                       mpat 0.$n 'Tsk, tsk.

    &GDESCRIPTION:       &cThe ISSHELLED ifcheck is used to determine
                       if the target is helled.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK LCK"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif lck($n) < 5
                         'Betcha don't feel very lucky, $n.

        &GDESCRIPTION:     &cThe LCK ifcheck is used to direct a command
                         based on the luck stat of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK LEADER"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:         if isleader($n)
                 $ is an order, guild, or clan leader
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK LEVEL"},
    level = 52,
    htype = "info",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:      &cif level($n) < 5
                      'You're just a wee baby, $n!

    &GDESCRIPTION:      &cThe LEVEL ifcheck is used to determine the
                      level of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MANA"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:   &cif mana($n) > 100
                     'You're low on mana, $n.

      &GDESCRIPTION:   &cThe MANA ifcheck is used to determine the
                     amount of mana the target has.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MOBCOUNT"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:    &cif mobcount(21000) > 10

      &GDESCRIPTION:    &cMOBCOUNT ifcheck counts the number of mobs
                      in the specified room. This example returns TRUE if
                      there are more than 10 mobs in room 21000.
                      You can use this form in room or mob programs and
                      you can have one room program check the number of
                      mobs in a different room.


          &GEXAMPLE:    &cif mobcount(0) > 10

      &GDESCRIPTION:    &cUse a zero room number if you want to have
                      a mob check the number of mobs in its room.
                      Note that if the mob changes rooms, the ifcheck
                      applies to whatever room the mob is in.
                      You should use this form in mob programs only.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MOBINAREA"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:         &cif mobinarea(3) == 1
                         'The SuperMob is here working.

    &GDESCRIPTION:         &cThe MOBINAREA(vnum) ifcheck is used to
                         determine if the target is in the area.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MOBINROOM"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:         &cif mobinroom(3) > 1
                         'We only need one SuperMob!

    &GDESCRIPTION:         &cThe MOBINROOM(vnum) ifcheck is used to
                         determine if, and/or how many, of target
                         are present in the room.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MOBINVIS"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif ismobinvis($n)
                          '$N is mobinvis

          &GDESCRIPTION:    &cThe ISMOBINVIS ifcheck determines if the
                          target MOB is flagged mobinvis.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MOBINVISLEVEL"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:       &cif mobinvislevel($i) == 50
                       'I'm invisible to all under lvl 50

    &GDESCRIPTION:       &cThe MOBINVISLEVEL is used to determine
                       the level the target is invisible to.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MOBINWORLD"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif mobinworld(21044) < 1
                         'Who killed Harakiem?

        &GDESCRIPTION:     &cThe MOBINWORLD(vnum) ifcheck is used to
                         determine if the specified MOB is anywhere
                         in the realms.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MORTAL"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif mortal($n)
                         'Greetings Mortal.

        &GDESCRIPTION:     &cThe MORTAL ifcheck is used to determine
                         if the target is level 50 or lower.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MORTCOUNT"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:    &cif mortcount(21000) > 10

      &GDESCRIPTION:    &cMORTCOUNT ifcheck counts the number of mortals
                      in the specified room. This example returns TRUE if
                      there are more than 10 mortals in room 21000.
                      You can use this form in room or mob programs and
                      you can have one room program check the number of
                      mortals in a different room.


          &GEXAMPLE:    &cif mortcount(0) > 10

      &GDESCRIPTION:    &cUse a zero room number if you want to have
                      a mob check the number of mortals in its room.
                      Note that if the mob changes rooms, the ifcheck
                      applies to whatever room the mob is in.
                      You should use this form in mob programs only.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MORTINROOM"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif mortinroom(Fred)
                          ruffle fred

          &GDESCRIPTION:    &cThe MORTINROOM ifcheck returns true every time
                          the mortal is in the room. MORTINROOM will
                          work for link dead as well as link live players.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MORTINWORLD"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif mortinworld(Fred)
                          mpat 0.Fred say Hi Fred!

          &GDESCRIPTION:    &cMORTINWORLD ifcheck returns true if the
                          mortal is in the game. MORTINWORLD will
                          work for both link dead as well as link
                          live players.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK MULTI"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif multi($n) > 4
                          '$n has more than four characters logged in.

          &GDESCRIPTION:    &cThe MULTI ifcheck is used to determine if/
                          how many PCs the target has logged in. Also
                          applies to MOBs, objects, rooms.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK NAME"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:      &cif name($n) == haus
                        bow 0.$n

      &GDESCRIPTION:      &cthe NAME ifcheck is used to determine
                        the name of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK NORECALL"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:
DESCRIPTION
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK NUISANCE"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif nuisance($n)
                          'How much of a pest are you....

          &GDESCRIPTION:    &cThe NUISANCE ifcheck is used to determine
                          at what level the target is nuisanced.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK NUMBER"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:

DESCRIPTION
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
EXAMPLE:
DESCRIPTION
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK OBJTYPE"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:      &cif objtype($o) == 19
                      'Yummy! Food!

    &GDESCRIPTION:      &cThe OBJTYPE ifcheck is used to determine the
                      type of object the target is. (HELP OBJTYPENUMS)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OBJVAL0"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif objval($0) = 10
                          (and the object is a drink container)
                          This container has 10 units of fluid in it

          &GDESCRIPTION:    &cThe OBJVAL0(name) ifcheck returns the numeric
                          value of the val0 field of the object referenced
                          by name.  See 'help ITEMVALUES' for what val0
                          can be used for.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OBJVAL1"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif objval($1) == 20
                          (and the object is an armor)
                          The AC of the armor is 20

          &GDESCRIPTION:    &cThe OBJVAL1(name) ifcheck returns the numeric
                          value of the val1 field of the object referenced
                          by name.  See 'help ITEMVALUES' for what val1
                          can be used for.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OBJVAL2"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif objval($2) == 12
                          (And the item is a drinkcon)
                          This container holds coffee

          &GDESCRIPTION:    &cThe OBJVAL(name) ifcheck returns the numeric
                          value of the val2 field of the object referenced
                          by name. See 'help ITEMVALUES' for what val2
                          can be used for.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OBJVAL3"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif objval($3) == 12
                          (And the object is a weapon)
                          This is a suction type weapon

          &GDESCRIPTION:    &cThe OBJVAL(name) ifcheck returns the numeric
                          value of the val3 field of the object referenced
                          by name. See 'help ITEMVALUES' for what val3
                          can be used for.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OBJVAL4"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif objval($4) == 135
                          (And the object is a salve)
                          The 1st spell this salve casts is poison

          &GDESCRIPTION:    &cThe OBJVAL(name) ifcheck returns the numeric
                          value of the val3 field of the object referenced
                          by name. See 'help ITEMVALUES' for what val4
                          can be used for.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OBJVAL5"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif objval($4) == 135
                          (And the object is a salve)
                          The 2nd spell this salve casts is poison

          &GDESCRIPTION:    &cThe OBJVAL(name) ifcheck returns the numeric
                          value of the val3 field of the object referenced
                          by name. See 'help ITEMVALUES' for what val4
                          can be used for.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OTYPEHERE"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:



DESCRIPTION
The OTYPEHERE(name)/OTYPEHERE(number) ifcheck is used to determine
if an object of the given objecttype is in the room.  See
'help OBJECTTYPES.'

SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK OTYPEINV"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:



DESCRIPTION
The OTYPEINV(name)/OTYPEINV(number) ifcheck is used to determine
if an object of the given objecttype is in the checker's inventory.
See 'help OBJECTTYPES.'

SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK OTYPEROOM"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:



DESCRIPTION
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
The OTYPEROOM(name)/OTYPEROOM(number) ifcheck is used to determine
if an object of the given objecttype is in the checker's room.


See 'help OBJECTTYPES.'
SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK OTYPEWEAR"},
    level = 51,
    htype = "wizhelp",
    text = [[
EXAMPLE:



DESCRIPTION
The OTYPEWEAR(name)/OTYPEWEAR(number) ifcheck is used to determine
if an object of the given objecttype is worn by the checker.
See 'help OBJECTTYPES.'

SEE ALSO: mpedit, opedit, rpedit, ifchecks.
]],
  },
  {  
    keywords = {"IFCHECK OVNUMCARRY"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

      &GEXAMPLE:   &cif ovnumcarry(1200) > 1
                 'Why do you have so many general imm boards?

  &GDESCRIPTION:   &cThe OVNUMCARRY(vnum) ifcheck is used to determine
                 if an object with the given vnum is worn OR carried
                 by the CHECKER.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OVNUMHERE"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

      &GEXAMPLE:         &cif ovnumhere(1200)
                       'Reading Imm Sam, I see.

  &GDESCRIPTION:         &cThe OVNUMHERE(vnum) ifcheck is used to
                       determine if an object is:
                       - in the room of the checker
                       - in the inventory of the checker
                       - being worn by the checker
                       - carried by the checker

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OVNUMINV"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

      &GEXAMPLE:         &cif ovnuminv(1200) < 1
                       'Where's my Imm board?

  &GDESCRIPTION:         &cThe OVNUMINV(vnum) ifcheck is used to
                       determine if an object is in the checker's
                       inventory.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OVNUMROOM"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

      &GEXAMPLE:         &cif ovnumroom(1200) > 1
                       'Why are there so many general Imm boards here?

  &GDESCRIPTION:         &cThe OVNUMROOM(vnum) ifcheck is used to determine
                       if an object is in the room the checker is in.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK OVNUMWEAR"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:   &cif ovnumwear(1200)
                         'Why am I wearing the general imm board?

          &GDESCRIPTION:   &cThe OVNUMWEAR(vnum) ifcheck is used to
                         determine if the specified object is being
                         worn by the checker.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK POSITION"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:         &cif position($i) == 6
                         stand

    &GDESCRIPTION:         &cThe POSITION ifcheck is used to determine
                         the position of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK RACE"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

        &GEXAMPLE:           &cif race($n) == drow
                           ,eyes the Drow suspiciously

    &GDESCRIPTION:           &cThe RACE ifcheck is used to determine the
                           race of the target.(HELP NPCRACES)

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK RAND"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:    &cif rand(25)
                      'I will say this 25% of the time, or less.

      &GDESCRIPTION:    &cThe RAND ifcheck is used to vary command
                      strings given to the same trigger.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK SEX"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:      &cif sex($n) == 2
                        'Greetings M'Lady!

      &GDESCRIPTION:      &cThe SEX ifcheck is used to determine the
                        gender of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK STR"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:    &cif str($n) < 5
                        'You need to work out, $n.

        &GDESCRIPTION:    &cThe STR ifcheck is used to direct a command
                        based on the target's strength stat.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK TIME"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

          &GEXAMPLE:      &cif time($n) == 1201
                        'Noon, and all is well.

      &GDESCRIPTION:      &cThe TIME ifcheck is used to determine the
                        time of day in military time. <,>, ! and ==
                        also apply in any combination.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK TIMESKILLED"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:     &cif timeskilled($n) > 200
                         'Try an easier MUD, $n :)

        &GDESCRIPTION:     &cThe TIMESKILLED(name) ifcheck is used
                         to base a command on the specified number of
                         times the target has been killed.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK WAITSTATE"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

              &GEXAMPLE:    &cif waitstate($n) > 5
                          '$n is a bit lagged.

          &GDESCRIPTION:    &cThe WAITSTATE ifcheck is used to check
                          the amount of "wait" a PC has. Does not
                          apply to NPCs.

&r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK WASINROOM"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

     &GEXAMPLE:   &centry_prog 100
                if ispc($n)
                if wasinroom($n) == 1200
                mpe $n was in room 1200

 &GDESCRIPTION:   &cThe WASINROOM ifcheck is used to determine if the
                target was in a specified room. NOTE: wasinroom checks
                for the 'last' room the target was in only.

&r*-------------------------------------------------------------------*

  &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECK WIS"},
    level = 52,
    htype = "wizhelp",
    text = [[
&r*-------------------------------------------------------------------*

            &GEXAMPLE:    &cif wis($n) > 20
                        'You're a wise person, $n.

        &GDESCRIPTION:     &cThe WIS ifcheck is used to direct a command
                         based on the wisdom stat of the target.

 &r*-------------------------------------------------------------------*

    &YSEE ALSO: &wMPEDIT, OPEDIT, RPEDIT, IFCHECKS, IFCHECKS2, IFCHECKS3

]],
  },
  {  
    keywords = {"IFCHECKS"},
    level = 51,
    htype = "wizhelp",
    text = [[
VALUE CHECKS (If check == #/string/vnum)
Ifcheck        Question                      Ifcheck    Question
&r------------   ---------------------------   ---------  ------------------
&GHitprcnt       &cPercentage of hit/max_hit?    &GSex        &cSex?
&GDeity          &cName of deity?  (STRING)      &GName       &cName?  (STRING)
&GLevel          &cExperience level?             &GInroom     &cRoom #?  (VNUM)
&GObjtype        &cType of Object?               &GStr        &c# of strength?
&GObjval#        &cValue# equal to this?         &GInt        &c# of intelligen
&GNumber         &cIs its vnum equal to this?    &GWis        &c# of wisdom?
&GPosition       &cPosition #?                   &GDex        &c# of dexterity?
&GClan           &cClan name?  (STRING)          &GCon        &c# of constituti
&GRace           &cRace name?  (STRING)          &GCha        &c# of charisma?
&GMobinarea      &cIs mob in area?               &GMobinworld &cDoes mob exist?
&GMobinroom      &cHow many of mob?  (VNUM)      &GLck        &c# of luck?
&GGuild          &cGuild name?  (STRING)         &GGoldamt    &c# of gold ya go
&GClass          &cClass name?  (STRING)         &GFavor      &c# of favor?
&GMobinvislevel  &cLevel of invis?               &GEconomy    &c# of economy?
&GCouncil        &cMember of council?            &GHps        &c# of hps?
&GMana           &c# of mana?                    &GMortal      &c*Not In Use*
&r------------   ---------------------------   ---------  ------------------

&wValue checks can use == (equals) > (greater than) < (less than)
and ! (not).  Combine for:  != (not equal) >= (greater than or equal).

&YSee individual help files for each ifcheck: &Whelp 'ifcheck mortcount'

&YContinued on: IFCHECKS2, IFCHECKS3
&rSee Also:     MPSTAT RPSTAT OPSTAT MPEDIT RPEDIT OPEDIT TRIGGER MPTRIGGERS
              RPTRIGGERS OPTRIGGERS MPCOMMANDS RPCOMMANDS OPCOMMANDS VARIABLES
              AFFECTEDBY (for a list of affect types)&w
]],
  },
  {  
    keywords = {"IFCHECKS2"},
    level = 51,
    htype = "wizhelp",
    text = [[
&r----------  ------------------------    -----------  ------------------
&GIsgood      &cAlign +350 or higher?       &GIsdevoted    &ctarget devoted?
&GIsneutral   &cAlign < 350 and > -350?     &GIsimmort     &cImmortal?
&GIsevil      &cAlign -350 or lower?        &GIsmounted    &cMounted?
&GIsfollow    &cFollow master in room?      &GIsnpc        &cMob?
&GRand (#)    &cEqual to or less?           &GIspc         &cPlayer character?
&GIsaffected  &cAffected_by name?           &GIspkill      &cPkill?
&GCanpkill    &cPkill lev>4 and age>17      &GIsfight      &cFighting?
&GIsmobinvis  &cMobinvis? (versus invis)    &GIscharmed    &cCharmed?
&GNorecall    &cIs target's room norecall?  &GIspacifist   &cPacifist?
&GMortinworld &cIs mort anywhere?           &GMortinarea   &cin area?
&GMortinroom  &cIs mort in room?            &GIspassage    &c(DIR)Exit exists?
&GWasInRoom   &cWas target in X room?       &GIsMulti      &cMulti-playing?
&GIsopen      &c(DIR)Exit open?             &GIslocked     &c(DIR)Exit locked?
&GTime        &c(Military)Time of day?      &GWeight       &cTarget's weight?
&GMortCount   &cMortals in room?            &GMobCount     &cNPCs in room?
&GCharCount   &cNPCs + Mortals in room?
&r----------  ------------------------    -----------  ------------------

&wValue checks can use == (equals) > (greater than) < (less than)
and ! (not).  Combine for:  != (not equal) >= (greater than or equal).

&YSee individual help files for each ifcheck: &Whelp 'ifcheck mortcount'

&YContinued on: IFCHECKS, IFCHECKS3
&rSee Also:   MPSTAT RPSTAT OPSTAT MPEDIT RPEDIT OPEDIT TRIGGER MPTRIGGERS
            RPTRIGGERS OPTRIGGERS MPCOMMANDS RPCOMMANDS OPCOMMANDS VARIABLES
            AFFECTEDBY (for a list of affect types)&w

]],
  },
  {  
    keywords = {"IFCHECKS3"},
    level = 51,
    htype = "wizhelp",
    text = [[
.
&GTimesKilled
&c        If timeskilled($* OR vnum) == amount
For character checks only, can use any normal mobprog operator

&GOvnumHere  OvnumRoom  OvnumCarry  OvnumWear  OvnumInv
&c        If ovnum<place>(vnum) == amount
For objects only, counts how many objects of vnum 'vnum' exist in <place>

&GOtypeHere  OtypeRoom  OtypeCarry  OtypeWear  OtypeInv
&c        If otype<place>(type OR value) == amount
For objects only, counts how many objects of type 'value' are in <place>
Will convert the type names (light is 1, for example)

&gDefinitions:
Room  In the room the mobile is in.  Wear   Worn by the mobile as equipment.
Inv   In the mobile's inventory.     Carry  Worn or in inventory
Here  All of the above

&YContinued on: IFCHECKS, IFCHECKS2
&rSee Also:     MPSTAT RPSTAT OPSTAT MPEDIT RPEDIT OPEDIT TRIGGER MPTRIGGERS
              RPTRIGGERS OPTRIGGERS MPCOMMANDS RPCOMMANDS OPCOMMANDS VARIABLES
              AFFECTEDBY (for a list of affect types)&w
]],
  },
  {  
    keywords = {"IFCHECKS4"},
    level = 54,
    htype = "wizhelp",
    text = [[
&GThe following are ifchecks available to port 4000 immortals only:

&Yifcheck           syntax                 usage
&Wisasupressed      if isasupressed($n)    is the target asupressed?
ismorphed         if ismorphed($n)       Is the target morphed? (not in use)
isnuisance        if isnuisance($n)      Is the target nuisanced?
ishelled          if ishelled($n)        Is the target currently helled?
ismulti           if ismulti($n) (value) Is the target multying?
waitstate         if waitstate($n) (val) Is the target in waitstate?

&YAdditional help on each of these subjects is available through
'IFCHECK (IFCHECK NAME)'.

&WSee Also: IMMPROGS
]],
  },
  {  
    keywords = {"IMM"},
    level = 51,
    htype = "wizhelp",
    text = [[
This immortal list of rules and regulations is currently under construction.

The helpfiles that are available are:

'help immrules'
'help imm invis'          'help imm echo'          'help imm recho'
'help imm auth'           'help imm forceclose'    'help imm force'
'help imm snoop'          'help imm freeze'        'help imm bodybag'

'help immortal'           'help creator'           'help savior'
'help demi god'           'help lesser god'
]],
  },
  {  
    keywords = {"IMM BODYBAG", "IMM CR"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: Bodybag && CR

- You are never required to do a CR for a mortal.
- If you do perform an Immortal CR, you are required to take at least one
  item as charge, this item should be one of the best items the player has.
  ** The only exceptions are a CR for a person under level 10 or if you are
  ** running a quest, and the player died in that quest or you have the
  ** approval from a Council of Elders member.  These qualify for a free CR.
- You may never give free CRs to your friends or for your own mortals.
- You may choose more then one item or gold for a CR, but _must_ inform the
  player of your intent prior to bodybagging them.
- You are never allowed to do a cr for a deadly character.
- Corpses should be at least "crawling with vermin" prior to receiving an
  Immortal CR, i.e. a corpse timer of less than 20.

You may never CR for your own mortal unless _all_ the following apply:
   - There is no other Immortal online to do it for you.
   - You have tried to get your corpse on your own, with mortal assistance.
   - Your corpse is in "the last stages of decay", meaning you cannot wait
     any longer, i.e. a corpse timer of less than 8.

If you perform a CR for one of your -own- mortal characters, you must:
   - Take at least one of the better/best items from your mortal, and eat it.
   - Let Darwin and/or Medea know that you cr'd your own mortal's corpse.

***** See 'help timer' to get a list of corpse decay timer and messages.
]],
  },
  {  
    keywords = {"IMM ECHO"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: echo

Echos should generally be medieval in nature, and their use confined
primarily to administrative functions, weddings, quest, role-playing
and the like.  Role-playing should be used rarely, however.

Though there is some leeway within these guidelines, some practices
are frowned upon and should be avoided.  Do not use your name in an echo
unless necessary.  Avoid comical phrases or 'cutsey' terms.  Do not use
:) or other symbols/punctuations at all.

If any of the above are necessary, there exist a sufficient number of
public channels via which the task can be accomplished while still
reaching a wide audience -  without forcing it onto the screen of
every character in the game.
]],
  },
  {  
    keywords = {"IMM FORCE"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: force

This command allows you to make someone execute a command.  Forcing
someone can often be looked at as high-handed.  Most common use of
force is to make someone do something as you are snooping, to check
problems or bugs, without waiting having to tell the character exactly
what to type.  It is always best to ask the person before you begin
forcing them.  You may also use force to make a player quit, drop,
or read something when you are punishing them.

Force all <command> can be done, but causes excessive lag because it
causes every player lower than you to attempt the command.  This should
be reserved to "force all save" in times of numerous crashes.  You should
never force all to use a channel.
]],
  },
  {  
    keywords = {"IMM FORCECLOSE"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: forceclose

This command will force a certain descriptor to close.  To use, you
must first look for the number listed under Desc on the user list.
Then type: forceclose <Desc #>

You can use forceclose to knock a trouble player offline, as well as
knock off someone who it stuck online.
]],
  },
  {  
    keywords = {"IMM FREEZE"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: help freeze

Syntax: deny         <character>
Syntax: disconnect   <character>
Syntax: freeze       <character>

DENY denies access to a particular player and throws them out of the game.
Deny is permanent (persists across reboots) and is not undoable from within
the game.  Only someone with access to the player files directory may repeal
a DENY by editing the appropriate player file.

DISCONNECT <character> immediately disconnects that character.

FREEZE <character> is a toggle which prevents a character from issuing any
commands at all.
]],
  },
  {  
    keywords = {"IMM GOTO"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: goto <name>

This is a reminder to use common courtesy when using such commands
as goto.   Not only is it considered inappropriate to goto higher
level immortals without asking permission, the same could be said
when wanting to visit any player on the mud.  A quick tell requesting
to visit would suffice.  For those of you who frequent headquarters,
either Clans, Guilds or Orders, requesting permission, though not
necessary, is certainly welcome.  Note that if a mortal requests that
you leave their hq, and you have no pressing business, you are obligated
to abide by their wishes.  (This does not apply to high ranking immortals.)

]],
  },
  {  
    keywords = {"IMM INVIS"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: invis and wizinvis

Those Immortals between levels 51 and 54 may invis to level 51 when they
are running or preparing a quest, involved in a building projects that
requires you to be uninterrupted, or you are actively watching a mortal.
At all other times, the Immortal should be visible to all levels of mortals
and Immortals.  Wizinvis is to be used as a tool to assist you in your duties
as an Immortal, it is not a means to spy on others or hide.

Immortals of level 55 and above may use wizinvis beyond 51 to work on
projects or monitor another person.  It is mandatory to be visible to all
other immortals whenever reasonably able to do so.  Keep the use of
"Someone" to a minimum on channels.  Exceptions are when you need to answer
a question, make a comment, or pass on some information, but are too busy
to become visible.
]],
  },
  {  
    keywords = {"IMM RECHO"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: recho

Rechos should generally be medieval in nature, and their use confined
primarily to administrative functions, weddings, quest, role-playing
and the like.  Recho can be seen by all players in one room.  Do not
use recho to "scare" mortals.  Recho is seen on logs, be cautious in
using them in social/private situations.
]],
  },
  {  
    keywords = {"IMM SNOOP"},
    level = 51,
    htype = "wizhelp",
    text = [[
Associated help files: snoop

The snoop command is a very valuable tool, when used appropriately.  Snoop
not only allows you to watch another person, but to see the world through
their eyes, helping to track down problems the person may be experiencing.
The reasons for snooping are too varied to mention here, but the reasons
NOT to snoop are easily listed.

-- Do not snoop people being intimate. <i.e. Mudsex, voyeurism, etc...>
-- Do not repeat information learned in snoop casually, especially to mortals
-- Only snoop a person talking to a higher level Immortal with the higher
   Immortals "Express Permission".
-- If a higher level Immortal begins communication with someone you are
   snooping, inform that higher Immortal immediately of the snoop.
-- If a higher level Immortals requests you to stop snooping, do so quickly.
-- "Spot check" snooping of lower level Immortals is part of being a higher
   level immortal.  All Immortals may be snooped at any time, for any reason.
-- Do not snoop for the purpose of gaining information for personal reasons.
-- Any incidental references learned in snoop should be disregarded.
    ** For example, you learn someone is having a mud affair from snoop.
    ** This information has nothing to do with the reason you are snooping
    ** and should not affect your judgement.  It should not be passed on.
-- Being an Immortal is a privilege and a job.  Snoop is a tool to assist
   you do your job properly.  Snoop is neither a toy nor a right.
]],
  },
  {  
    keywords = {"IMMHOST"},
    level = 55,
    htype = "wizhelp",
    text = [[
Syntax:  immhost add    <name> <host>
Syntax:  immhost delete <name> <host>
Syntax:  immhost save
Syntax:  immhost
This command is for setting the hosts allowed for immortals that are added
with this command.  Wildcards are allowed (*), so *edu, would allow any domain
from edu connect and 127*, would allow any local domain to connect.
IMMHOST without arguments will show a list of names and what domains they are
allowed to connect from.
To delete a command you need to provide the name and the host, this allows
for multiple hosts for a certain name.
This file won't be saved until the immhost save command is issued.
]],
  },
  {  
    keywords = {"IMMORTALIZE"},
    level = 65,
    htype = "wizhelp",
    text = [[
Used to immortalize a character.
]],
  },
  {  
    keywords = {"IMMPROGS"},
    level = 54,
    htype = "wizhelp",
    text = [[
These mpcommands are restricted knowledge to port 4000 immortals.

&Ympcommand          syntax                  basic description
&Wmpapply/mpapplyb   mpapply 0.$n            For use in pre-auth.
mpbodybag          mpbodybag 0.$n          Not currently in use.
mpfillin           mpfillin <dir>          Closes off exits
mplog              mplog <text>            Logs mob activity
mposet/mpmset      mp$set <field> <value>  Osets and Msets objs mobs.
mpnuisance         mpnuisance $n <val>...  Sets player to nuisance (in use?)
mpscatter          mpscatter $n vnum vnum  Do not use.
mpstrew            unknown                 unknown
mppeace            mppeace <victim>        Performs an immortal peace.
mpasurpess         mpasupress $n val       Not in use.
mpdelay            mpdelay <victim><time>  Delays a victim for * rounds

&WNOTE: &CIf flagged "not in use" or "do not use", then &YDON'T USE &W:P
&WFor more on individual mpcommands, type "Help (mpcommandname)".

&YSee also: &WIFCHECKS4
]],
  },
  {  
    keywords = {"IMMPROMPT"},
    level = 51,
    htype = "wizhelp",
    text = [[
In addition to the normal prompt tokens, the following are available for
immortal use only:

  %r  - 'vnum' of current room           %i  - '(Invis Lv) ' wizinvis
  %R  - '<#vnum> ' of current room       %I  - 'Lv' wizinvis
        (with config +vnum set)
  %u  - current number of connections    %F  - display room flags
  %U  - max number of players for
        this boot

See also PROMPT
]],
  },
  {  
    keywords = {"IMMQUEST"},
    level = 51,
    htype = "wizhelp",
    text = [[
This help file will contain the current status as well as the expectations of
what is to be followed of Immortals questing.
  Currently imms &YARE&G allowed to quest.

&WRules for imm's questing:&G

 &W*&G It is expected that no Imm will be multi-playing their imm while they
   are questing.  This includes multi-playing while invis/afk/etc.

 &W*&G It is expected that no imm will log off their imm character in order to
   quest.  We don't want the situation arising where everyone logs off and the
   QC imm is stranded running the quest and fielding everything else.

 &W*&G You may &CNOT&G quest if you log in with your imm at any time during
   the quest.

&WSo when can you quest?&G

 &W*&G It's somewhat limiting, but you can quest &CIF&G you happen to be
   morting when a quest begins, &COR&G if you are given the explicit
   permission of the imm running the quest. &CPlease do not pressure them.&G

]],
  },
  {  
    keywords = {"IMMTALK", ":"},
    level = 51,
    htype = "wizhelp",
    text = [[
Syntax: immtalk <message>

IMMTALK sends a message to all immortals.  : is a synonym for IMMTALK.
]],
  },
  {  
    keywords = {"IMOTD"},
    level = 51,
    htype = "wizhelp",
    text = [[
1. Don't help out mortals too much.  Hints and clues are it, don't make them
eq with outrageous affects, and things like that.  Restrings are fine with us
though.

2. Give directions to areas to PC's in general terms, and please try to avoid
just transporting PCs to places.

3. Use common sense, and if in doubt, run an idea by Medea and/or Darwin, who
have the final word.

4. If building areas, contact Medea for some guidelines, so we can keep
things fairly balanced throughout the mud.

5. Remember, You are the staff of the MUD now. While we will demand that
players respect the Immortals, it's important that we also respect the
players.  Without them, the MUD would be quite boring.

6. All sorts of people play MUDs...some that you personally wouldn't want to
be friends with in real life.  But as long as they follow the rules, they have
every right to be here.

7. We're here for any concerns or problems. Remember the Immortal Board in
room 21420. Email at xdarwinevolved@aim.com (Darwin) or medeamahala@gmail.com
(Medea) if you can't contact us directly in the game.
]],
  },
  
  
  }
}
