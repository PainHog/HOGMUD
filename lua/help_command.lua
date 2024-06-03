all_helps.command = {}
all_helps.command = {
  entries = {
  
  {  
    keywords = {"!"},
    level = 0,
    htype = "command",
    text = [[
Syntax: !

! repeats the last command you typed.
]],
  },
  {  
    keywords = {"ACRO", "ACRONYM"},
    level = 1,
    htype = "command",
    text = [[
"Acro" is an interesting little game where players are given an acronym and
then must come up with a sentence using the letters given.  For example, if
the acronym given is "FDJL", then perhaps you can say "Food does jump lively".

After all the Acro players have submitted an answer, a voting phase takes
place.  You cannot vote for your own answer.  The winner is the one with the
most votes.

Acro works like this:  To start or join a game, just type "acro".  The game
will not start until at least five players join in.  Once you are given the
acronym to work with, submit your answer by tying "acro (your answer here)".
Once the voting phase begins, vote by typing "acro (#)", where the number is
the phrase you are voting for.  To leave an Acro game, type "acro quit".  The
game will end itself if people idle or don't submit answers.  Type "acro score"
to see the current score.

This is just for fun and giggles.  There is no prize for winning a game of
Acro, except the laughter you may get with a funny answer (;

 * Acro for SMAUG 1.x            http://dotd.com
 * (C) Jesse DeFer, dotd@dotd.com, dotd.com 4000
]],
  },
  {  
    keywords = {"ADVANCETIER"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  advancetier

Once a single-class character has reached level 50, they can use this command
to achieve a more advanced version of their character.  Search on help for
"TIERED" for more information.
]],
  },
  {  
    keywords = {"AFFECTED", "AFFECTED BY"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  affected       (abbreviation:  af)
Syntax:  affected by    (abbreviation: af by)

'Affected' is a spells-at-a-glance function, which displays only the spells
(and skill affects) your character is currently under.  Each affect will be
listed by name only for the sake of brevity (if you want to know what each
is doing, use help <spell/skill name> or 'score').

Characters level 20 or above and deadly characters will also see the number
of rounds remaining for each affect.  Affects with a remaining lifespan of
less than 25 rounds are displayed in white, and those in immediate danger
of wearing off will flash.

'Affected by' displays a character's affects separate from its spell/skill
affect list.  This is useful for ensuring that affects given from equipment
are actually functioning.  For example, if you are wearing a visor with
detect_invis but 'affected by' does not show you as having that affect, you
are not detecting invisibility.

'Affected by' also displays your current susceptibilities, resistances and
immunities if your character is level 20 or higher.
]],
  },
  {  
    keywords = {"AFK"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  afk (abbreviation for "away from keyboard")

The 'afk' command will place an [AFK] flag beside your name on the who
list when activated, as well as informing those who send tells that you
you are afk.  It can be toggled on or off by typing afk, and will also
go off automatically when you enter any command.

]],
  },
  {  
    keywords = {"ALIAS"},
    level = 1,
    htype = "command",
    text = [[
Syntax : alias
         alias create shortcut command
         alias delete shortcut
         alias list
         alias variables
         alias setvar value
         alias delvar variable
         alias config -/+ setting

The ALIAS command allows you to set shortcuts for commands or long
strings of text. These can be quite useful for shortening routinely
entered commands. 

Typing ALIAS LIST will display your current aliases.  Your aliases
will save with your character upon leaving the game. An alias may 
only contain a shortcut for a single command. Aliases may also 
contain variables defined with the ALIAS SETVAR command.

The ALIAS CREATE command will allow you to create a shortcut that
will execute the command you enter. If the specified alias already
exists, its command will be replaced.

ALIAS DELETE will remove the specified shortcut from your list of
aliases.

ALIAS VARIABLES will list all your currently defined variables.

ALIAS SETVAR will create a variable of the name you specify. When using
these variables in aliases you must use a $ before the variable name.
Do not use the $ when creating the variable.

ALIAS DELVAR will delete the specified variable.

ALIAS CONFIG will allow you to toggle on or off the messages you will
see from creating, editing or deleting aliases and variables. The settings
you can change are displayed when no setting is specified (ie: alias config)

See ALIAS2 and ALIAS3 for examples.
]],
    see_also = {"alias2", "alias3", "alias variables"},
  },
  {  
    keywords = {"ALIAS2"},
    level = 1,
    htype = "command",
    text = [[
Example: alias create heal cast heal
This assigns the command 'cast heal' to the alias 'heal' so that 
typing in 'heal' will issue the full command.

Example: alias edit heal cast heal self
This assigns the command 'cast heal self' to the alias 'heal',
replacing the previously entered command.

Example: alias delete heal
This will remove the 'heal' alias from your list of aliases.

Example: alias setvar target sturm
This will set the $target variable to 'sturm' and can then be used
within an alias command.

Example: alias delvar target
This will remove the $target variable from your list of defined
variables.

Alias config:
These settings will display, or prevent the display of, messages that
will inform you when an alias or variable has been created, edited or
deleted. It may be useful to have these messages on or off at times.
The options for 'alias config' are as follows:
alias config +aliasmsg
  This will turn alias messages on.
alias config -aliasmsg
  This will turn alias messages off.
alias config +varmsg
  This will turn variable messages on.
alias config -varmsg
  This will turn variable messages off.
  
For a more complex example see ALIAS3.
]],
    see_also = {"alias", "alias3", "alias variables"},
  },
  {  
    keywords = {"ALIAS3"},
    level = 1,
    htype = "command",
    text = [[
Complex Example:
1. alias create targ alias setvar target
2. alias create aspell alias setvar attackspell
3. alias create kk cast '$attackspell' "$target"
4. aspell quantum spike
5. targ sturm
6. kk

1. This creates an alias (targ) that will set the 'target' variable
   by using the ALIAS SETVAR command and appending the following text.
2. This creates an alias (aspell) that will set the 'attackspell'
   variable in the same fashion as in step 1.
3. This creates an alias (kk) that will cast the spell stored in
   the $attackspell variable at the victim stored in the $target
   variable.
4. This is using the aspell alias to set the $attackspell variable to
   quantum spike.
5. This is uging the targ alias to set the $target variable to sturm.
6. This is using the kk alias. When this alias is used it will execute
   the command "&Ccast 'quantum spike' sturm&W" after expanding all its
   defined variables.
]],
    see_also = {"alias", "alias2", "alias variables"},
  },
  {
    keywords = {"ALIAS VARIABLES"},
    level = 0,
    htype = "command",
    text = [[
Alias variables are special variables that are created via the
'ALIAS SETVAR' command. Variable names may only contain alphanumeric
characters. When a variable is created it is prefixed with a $. This
is what allows you to use the variable within an alias command.

There is also a special alias variable predefined for you. This is the
$arg variable. When you use an alias, this variable will contain all
the text that follows your alias command. For instance, if you create
an alias 'kk' that issues the command "cast 'dispel magic'" then when
you use the alias as "kk beggar" then the $arg variable will contain
the value 'beggar' and the command "cast 'dispel magic" beggar" will
be executed.

You may also include the $arg variable in your alias command explicitly.
This may be most useful for immortals when using the 'at' command. For
example: alias create ll at $arg look $arg
Using the alias ll such as "ll kallista" will issue the command:
at kallista look kallista

It could also be used for focusing mana when casting a spell.
Example: alias create fs cast $arg fireshield
Now, if the fs alias is used as such: fs 200, then it will execute the
command "cast 200 fireshield"

Note: If the $arg variable is explicitly used in an alias command, the
text following the alias &Rwill not&W be appended to the command. Using the
fs alias above as an example, if you wanted to cast fireshield on another
player using 'fs bob' then it would expand to "cast bob fireshield" which
would not work.

You may use as many variables within an alias as you want. If you use a
variable that you have not defined, it will not get replaced when you use
the alias.

Also note: You cannot override commands or skills with an alias of the same
name. The priority of commands is commands, skills, aliases, socials and
then named exits.
]],
    see_also = {"alias", "alias2", "alias3"},
  },
  {  
    keywords = {"ANSI"},
    level = 0,
    htype = "command",
    text = [[
Syntax: ansi <on/off>

The ansi command will either enable or disable ansi colour.  Ansi colour
will work provided your terminal has a compatible mode.
]],
  },
  {  
    keywords = {"APPRAISE"},
    level = 0,
    htype = "command",
    text = [[
Syntax: appraise <item>
        appraise all

Appraise, when at a repairshop type mob, will tell you the condition of
your equipment in question.  The mob will tell you if it needs repair or
not, and if so, how much it will cost.

]],
  },
  {  
    keywords = {"AQUEST"},
    level = 1,
    htype = "command",
    text = [[
Syntax: aquest <command>

When an adventurer has found a Questmaster, they must use the 'aquest' command
to work with them.  There are several options to be used with this command.

POINTS - Shows how many Glory points the adventurer has collected.

INFO - Shows what the current quest is for.

TIME - Shows how much time is available for the current quest.

REQUEST - Ask the Questmaster for a new quest.

REFUSE - Tell the Questmaster you don't want to accept his quest.

COMPLETE - Tell the Questmaster that you have completed their quest.

LIST - See what items the Questmaster is offering in exchange for Glory.

BUY - But a special item that the Questmaster is offering.

PRACS - Trade practice points for quest points, 1 prac for 15qps.
]],
  },
  {  
    keywords = {"AUC", "AUCTION"},
    level = 1,
    htype = "command",
    text = [[
Syntax: auction (abbreviations: a , auc)
Syntax: auction <item name> <starting value>
Syntax: auction bid <value>

The auction command is used for performing auctions.  Simply typing auction
will display the current item being auctioned, if there is one.

If nothing is being auctioned, auction <item name> <starting value> will
begin an auction.  If no starting value is specified, it begins at 0 gold.

Auction bid <value> will place a bet for the item.

Special thanks to Erwin Andreasen for writing this function.
(Ported to SMAUG from a publicly available source.)

At the present, if the mud crashes in mid auction, you will lose both
your bidded money and the item.  This will at some point be fixed.

You are able to see auction almost from the point of character creation,
however, you cannot USE auction unless you're level FIVE or higher. To remove
the auction channel from your screen, type CHANNEL -AUCTION.
SEE also "help AUCTION2" for more on auction commands
&Y* Auctions will not be stopped for overbidding or misbidding*&w
]],
  },
  {  
    keywords = {"AUCTION2"},
    level = 1,
    htype = "command",
    text = [[
Auction will also work with the following arguments:

au bid 20k      - bids 20000 coins
au bid 20k500   - bids 20500 coins (20,000 + 500)
au bid 20k5003  - bids 20500 coins, too (only checks first 3 chars after "k")
au bid 1m       - bids 1 million coins

On an existing bid of 10000:
au bid +10       - adds 10%, making the bet 11000.
au bid +         - adds 25% (the default if no number given), bet is 12500.
au bid x         - multiplies by 2, making the bet 20000.
au bid x5        - multiplies by 5, making the bet 50000.

Also see: 'HELP AUCTION' for more information.
]],
  },
  {  
    keywords = {"AVTALK"},
    level = 1,
    htype = "command",
    text = [[
Syntax: avtalk <message>

This allows you to use the avtalk (level 50+) channel.
]],
  },
  {  
    keywords = {"BOOK"},
    level = 1,
    htype = "command",
    text = [[
Syntax: book sign

The Book of Death is located in the Judgement Room of the Temple of Drazuk.
Signing this book marks you as "deadly", and allows you to pk other deadly
characters or be pked by them.  Everyone starts out as "nice", but once
you sign the book, there is no turning back.  Being "nice" means you are not
allowed to PK for any reason.  PKing as "nice" will get you an instant KILLER
flag...PKing a "nice" character will get you an instant KILLER flag.

Use the "whois" command to check a player and see their status.

Those who decide to PK a nice player may have to deal with harsh consequences
from the Gods above....this is here to allow people who do not like PK to make
a choice.  Choose wisely!
]],
  },
  {  
    keywords = {"BRANDISH", "QUAFF", "RECITE", "ZAP", "WAND", "STAFF", "SCROLL", "POTION"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  brandish                       (to invoke a staff)
Syntax:  quaff  <potion>                (to quaff potions)
              quaff  <potion> <container>    (quaff directly from container)
Syntax:  recite <scroll> <target>       (to recite a scroll)
Syntax:  zap    <target>                (to use a wand on a target)

BRANDISH invokes a magical staff.

QUAFF quaffs a potion (as opposed to DRINK, which drinks mundane liquids).

RECITE recites a magical scroll; the <target> is optional, depending on the
nature of the scroll.

ZAP fires a magical wand at a target.  If the target is not specified, and
you are fighting someone, then that character is used for a target.

You must be holding a wand or a staff before using BRANDISH or ZAP.

All of these commands use up their objects:  Potions and scrolls have a
single charge.  Wands and staves (staffs) have multiple charges.  When a
magical object has no more charges, it will be consumed.  Use the spell
'identify' to see the remaining charges.

See EAT, BACKFIRE, RECHARGE, MAGICTABLE
]],
  },
  {  
    keywords = {"BRIBE"},
    level = 1,
    htype = "command",
    text = [[
Syntax: bribe

Sometimes thieves steal things.  Sometimes they get caught.  Those who do fail
that steal, can be flagged as a THIEF, making life quite difficult.  The only
way to get that mark removed is to find someone who accepts bribes.  For
25,000 coins, some folks can clear your good name.  However, don't expect it
to happen right away...it does take some time for people to forget about your
crime!
]],
  },
  {  
    keywords = {"BUY", "LIST", "SELL", "VALUE"},
    level = 0,
    htype = "command",
    text = [[
Syntax: buy   <object>
Syntax: buy   <# of object> <object>
Syntax: list
Syntax: list  #
Syntax: list  <object>
Syntax: sell  <object>
Syntax: value <object>

BUY buys an object from a shop keeper.
BUY <# of object> <object> will allow you to buy up to twenty of a normal
store item at once.

LIST lists the objects the shop keeper will sell you.  LIST <object> lists
just the objects with that name.

LIST # will display the details of an item.

SELL sells an object to a shop keeper.

VALUE asks the shop keeper how much he, she, or it will buy the item for.

]],
  },
  {  
    keywords = {"CAST"},
    level = 0,
    htype = "command",
    text = [[
Syntax: cast <spell> <target>
        cast <amount> <spell> <target>

Before you can cast a spell, you have to practice it.  The more you practice,
the higher chance you have of success when casting.  Casting spells costs mana.

The <target> is optional.  Many spells which need targets will use an
appropriate default target, especially during combat.

If the spell name is more than one word, then you must quote the spell name.
Example: cast 'cure critic' frag.  Quoting is optional for single-word spells.
You can abbreviate the spell name.

When you cast an offensive spell, the victim usually gets a saving throw.
The effect of the spell is reduced or eliminated if the victim makes the
saving throw successfully.

See also the help sections for individual spells.

The second syntax will allow you to focus more of your available mana into
the casting of the spell.
Example: cast 100 'lightning bolt' naga
This will cause the spell to use the additional amount of mana. By focusing
more mana into your spell, you may increase the level at which it is cast.
This may have the effect of the spell causing more damage, producing a higher
enchant or lasting longer.
]],
  },
  {  
    keywords = {"CHANNELS"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  channels
Syntax:  channels +<channel|all>
Syntax:  channels -<channel|all>

With no options, CHANNELS show you your current channels.  With a plus or
minus sign and an option, CHANNELS turns that channel on or off.  Using the
'all' option, CHANNELS will turn on/off all normal channels.

Public channels are those that can be seen by everyone, regardless of their
affiliation with clans, guilds, orders or councils.  Private channels are
channels available to those with affiliations of some sort, and also tells.

The first channels you will have as a new player are SAY, TELL, and NEWBIE.

 - to use say, the person you want to talk to must be in the same room,
   just type SAY <message>.
 - to use tell, the target person may be anywhere within the Realms, just
   type TELL <name or 0.name> [message].
 - newbiechat is seen and used only by level 1 characters, members of the
   Newbie Council, and Immortals.

For a more complete explanation of each channel's use and who can
use it, read section 3 of your Adventurer's Guide book.
]],
  },
  {  
    keywords = {"CLEANUP"},
    level = 1,
    htype = "command",
    text = [[
Tired of sacrificing every little thing in the room?  Well, if you're not
interested in that 1 coin you get per object on a Sacrifice, then use CLEANUP!
This will remove every object in the room, unless if runs into a player corpse
or an item that is flagged with an Owner.

Careful!  This command may remove objects you didn't mean to remove, so use
sacrifice if you are nervous about that.  No refunds! (;
]],
  },
  {  
    keywords = {"CLEAR"},
    level = 0,
    htype = "command",
    text = [[
Syntax: clear

This command clears the screen.

See PAGELENGTH.
]],
  },
  {  
    keywords = {"COMPARE"},
    level = 0,
    htype = "command",
    text = [[
Syntax: compare <object-1> <object-2>
Syntax: compare <object>

COMPARE compares two objects in your inventory.  If both objects are weapons,
it will report the one with the better average damage.  If both objects are
armor, it will report the one with the better armor class.

COMPARE with one argument compares an object in your inventory to the object
you are currently wearing or wielding of the same type.

COMPARE doesn't consider any special modifiers of the objects.
]],
  },
  {  
    keywords = {"CONFIG"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  config + or - <option>

This command configures some of your character behavior.  Typing CONFIG
alone shows you your current settings.  With a plus or minus sign and
an option, CONFIG turns that option on or off.  The options are:

 AUTOEXIT   You automatically see exits
 AUTOLOOT   You automatically loot corpses (not on pkilled corpses)
 AUTOSAC    You automatically sacrifice corpses
 AUTOGOLD   You automatically split gold from kills with your group
 AUTOGLANCE You automatically look at your opponent after damaging them
 GAG        Toggle whether you see battle details in full or brief form
 PAGER      Toggle page pausing on long scrolls
 BLANK      You have a blank line before your prompt
 BRIEF      You see brief descriptions only.
 COMBINE    You see object lists in combined format
 NOINTRO    Toggle whether you see the graphic screen at login
 PROMPT     You have a prompt
 ANSI       You receive ANSI color sequences
 RIP        You don't receive RIP graphics
 DRAG       Toggle whether others can drag you if you are incapacitated
 COMPASS    Turns on a compass showing available exits.
 SEEDAM     Toggle whether or not you see a numerical value for damage caused.
 AUTOUPDATE Toggle whether or not your prompt is automatically updated from
            wait states.
 AUTOASSIST Toggle whether or not you will automatically assist group members
            during combat.
 ABBAFFS    Toggle whether or not you see abbreviated affects on other
            characters. See HELP ABBAFFS.
 SHORTWHO   Toggle the display of a full 2-line display for each character
            or a short 1-line dislay for the WHO output.

For more information on the configuration menu, read section 5 in your
Adventurer's Guide book.

See also: PAGER, PROMPT, PCOLORS.
]],
  },
  {  
    keywords = {"CONNECT"},
    level = 1,
    htype = "command",
    text = [[
Syntax: Connect <firstobj> <secondobj>

Connects special items together to create other items.
]],
  },
  {  
    keywords = {"CONSIDER"},
    level = 0,
    htype = "command",
    text = [[
Syntax: consider <character>

CONSIDER tells you what your chances are of killing a character.
Of course, it's only a rough estimate.
]],
  },
  {  
    keywords = {"CR", "CORPSE RETRIEVAL", "CORPSE"},
    level = 1,
    htype = "command",
    text = [[
Syntax: corpse retrieve

Certain "Undertakers" can retrieve the corpses of less fortunate adventurers.
For players level 25 and under the cost is 50gp per level. For non-deadly
players level 26 and higher the cost is 10qp per level. For deadly players
level 26 and higher the cost is 15qp per level.

CR Costs                                           Minimum/Maximum
Level  2-25                                        100gp  / 1250gp
Level 26-50 dual-class (non-deadly)                260qp  / 500qp
Level 26-50 dual-class (deadly)                    390qp  / 750qp
Level  2-50 (max effective 55) tier (non-deadly)   500qp  / 550qp
Level  2-50 (max effective 55) tier (deadly)       750qp  / 825qp

Your other option is to ask another player or Immortal for assistance.
Before asking an immortal for a corpse retrieval, you &r-must-:&w

&r    -&w Attempt to get your corpse yourself, &rand
    -&w Use invis and hidden, this will get you past a lot of mobiles,&r and
    -&w Seek mortal assistance to retrieve your corpse.&r
    -&g If all else fails, wait at least 20 minutes after death to ask for an
      Immortal corpse retrieval.&w

**  "I need to leave now!" is not grounds for an early Immortal CR.
**  Corpses last approximately 40 - 60 minutes after the time of death.
**  Corpse decay will happen even while you are linkdead or after you quit.
**  Characters listed under 'who deadly' are not eligible for Immortal CR.
**  Corpses _will_ save over crashes and reboots, but will continue to decay
    once the Realms comes back online.  Log back on quickly to get corpse.

The cost for CRs is usually one item from your corpse.  An Immortal may
choose to charge MORE or LESS.

&gAn Immortal corpse retrieval is not a right, but a privilege.&w  Pestering
or being demanding is cause for the Immortal to deny your request.  An
Immortal may refuse to do any CR at their discretion.  You may not barter
which items an Immortal can take from your corpse as the charge, the
Immortal's decision is final.
]],
  },
  {  
    keywords = {"CSLIST"},
    level = 1,
    htype = "command",
    text = [[
Syntax: cslist classname range
Example: cslist mage 1 15  <--- to see the skills of a mage, levels 1-15

"CSLIST" is like "SLIST", but is used to check the skills of a class other
than yours.
]],
  },
  {  
    keywords = {"DESCRIPTION", "BIO"},
    level = 0,
    htype = "command",
    text = [[
Syntax: description
        bio

The DESCRIPTION command puts you into an editor to edit your long character
description (what people see when they look at you).
The BIO command puts you into an editor to edit your personal bio: what
people see when they check WHOIS on you.

An Immortal can request you change your description or bio if it contains
inappropriate material.  Do not use profanity, racial slurs, sexual comments,
other players names (without their permission), or off-color remarks.  Refusal
to change your bio, description, or title on Immortal request is grounds for
loss of character privileges.
]],
  },
  {  
    keywords = {"DISMISS"},
    level = 1,
    htype = "command",
    text = [[
Syntax: dismiss <target>
        dismiss all

The dismiss command will force your charmed mobile to follow itself and
will negate the charm effect.

'dismiss all' will force all of your charmed mobiles to stop following and
remove the charm effect upon them.
]],
  },
  {  
    keywords = {"DIVORCE", "MARRY"},
    level = 1,
    htype = "command",
    text = [[
Syntax: divorce <char1> <char2>
Syntax: marry <char1> <char2>

Used to separate a married couple or marry a couple together.  Both players
must be online and give consent for this command to work.  Married couples
gain the use of SPOUSETALK, a private channel for the couple.

Only certain Gods can perform weddings...ask around.
]],
  },
  {  
    keywords = {"DONATE", "DONATION", "DONATIONS"},
    level = 1,
    htype = "command",
    text = [[
Syntax: donate <item>

"Donate" will send an item from your inventory to the Pit Room in the Temple
of Drazuk, where Jerald the Pitboy will place the item in the Pit for others
to grab.

Items in the Pit will not save through a reboot.

Note: Stock items may not be placed in the donation pit.
]],
  },
  {  
    keywords = {"DRAG"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  drag  <character> <direction>

Drag will drag the victim in the specified direction if they are not
standing up.

Characters can drag any other character who is not standing up.

You cannot drag a character if either you or they are under attack.
]],
  },
  {  
    keywords = {"DROP", "GET", "GIVE", "PUT", "TAKE"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  drop <object>
         drop <amount>  coins
Syntax:  get  <object>
         get  <object>  <container>
Syntax:  give <object>  <character>
         give <amount>  coins <character>
Syntax:  put  <object>  <container>
Syntax:  get/put/drop   <# amount>  <object>
Syntax:  get/put        <# amount>  <object> <container>

DROP drops an object, or some coins, on the ground.

GET takes an object, either lying on the ground, or from a container, or
even from a corpse (TAKE is a synonym for get).

GIVE gives an object, or some coins, to another character.

PUT puts an object into a container.

Use 'drop/get/put all' to reference all objects present.
Use 'drop/get/put all.<object>' to reference all objects of the same name.

Examples:
 - drop 1000 coins
 - get all.ball backpack
 - get 5 sword
 - put 15 potion backpack

]],
  },
  {  
    keywords = {"EAT", "DRINK"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  drink <object>                  (drink liquid from a drink container)
Syntax:  eat   <object>                  (eat food or a magical pill)
         eat   <object> <container>      (eat directly from a container)

Drink instructs your character to drink from a fountain or a drink container
to alleviate thirst.

Eat instructs your character to eat an item of food or a magical pill (which
function in a similar fashion as potions); pills do not fill stomach space.

When you are hungry or thirsty (you will see messages at each tick that
tell you if you are starving or dying of thirst, and can check your
current state with either 'score' or 'oldscore'), you will not regain
hitpoints, movement points or mana back as rapidly as if you were well
fed and hydrated.

If you stay hungry or thirsty too long and you are not an Avatar, your
mental state will begin to suffer.  Your combat skills will be affected,
your coordination will suffer and you may begin to either hallucinate or
become depressed.  Eating, drinking and a little rest will solve this
problem after a short period of time.

See MENTALSTATES
]],
  },
  {  
    keywords = {"EMOTE", ","},
    level = 1,
    htype = "command",
    text = [[
Syntax:  emote <text>

Emote is a customized expression of emotions or actions.  For example:

emote justs smiles and nods.

... displays to everyone in the room:

<Your character's name> just smiles and nods.

See also SOCIALS
]],
  },
  {  
    keywords = {"EMPTY"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  empty <container>
Syntax:  empty <container> <container>

This command allows you to empty a container of its contents.

Use 'empty <container>' to dump the contents to the ground.

Use 'empty <container> <container>' will empty the contents of the
first container into the second container.
]],
  },
  {  
    keywords = {"ENTER", "LEAVE"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  enter
Syntax:  leave

In rooms either 'somewhere' exits or exits responding only to keywords,
you can simply type 'enter' or 'leave' to pass through that exit.

The most common use of this is with portals cast by mages.  To use the
portal, simply type 'enter' on either side of it and you will pass
through to the other side.

]],
  },
  {  
    keywords = {"EQUIPMENT", "INVENTORY"},
    level = 0,
    htype = "command",
    text = [[
Syntax: equipment
Syntax: inventory

EQUIPMENT (or eq for short) lists the items you are currently
          wearing and/or using.
INVENTORY (or i for short) lists the items you are carrying
          around that are not currently being used.
]],
  },
  {  
    keywords = {"EXAMINE", "LOOK"},
    level = 0,
    htype = "command",
    text = [[
Syntax: look
Syntax: look    <object>
Syntax: look    <character>
Syntax: look    <direction>
Syntax: look    <keyword>
Syntax: look in <container>
Syntax: look in <corpse>
Syntax: examine <container>
Syntax: examine <corpse>

LOOK looks at something and sees what you can see.

EXAMINE is short for 'LOOK container' followed by 'LOOK IN container'.

In addition, 'EXAMINE container itemtype' will show you only objects
of that certain itemtype in the container.
For example, 'EXAMINE container weapon' will show you all the weapons
in the container.  Itemtypes are usually not pluralized, and can be
seen when you examine or look at an item after it has been IDed.
]],
  },
  {  
    keywords = {"EXITS"},
    level = 0,
    htype = "command",
    text = [[
Syntax: exits

Tells you the visible exits of the room you are in.  Not all exits are visible.
You can use the 'bump' technique to find hidden exits.  (Try to walk in a
certain direction and see what you bump into).
]],
  },
  {  
    keywords = {"FDEPOSIT", "FWITHDRAW"},
    level = 1,
    htype = "command",
    text = [[
Syntax: fdeposit  #   or    fdeposit all
        fwithdraw #   or    fwithdraw all

FDEPOSIT:  If you are a member of a following you can "fdeposit" gold into a
special account.  Your God or Goddess can use this Following gold to purchase
enhancements for their temple.  See "TEMPLECOSTS" for more information about
the upgrades.

FWITHDRAW:  Only Gods of Followings can withdraw money from the Following.  It
is to be used for the Gods only...this money is not to be used for purchasing
any goods or property for adventurers, unless it is something special in the
Following.
]],
  },
  {  
    keywords = {"FILL"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  fill <drincon>
Syntax:  fill <container>
Syntax:  fill <pipe> <herb>

FILL can be used with drink containers, regular containers or pipes.
 - to fill a drink container, go to a fountain and 'fill <drinkcon>'
 - to fill a container such as a backpack with items from the ground,
   type 'fill <container>'
 - to fill a pipe you must have both the pipe and the herb in your
   inventory, then type 'fill <pipe> <herb>'

]],
  },
  {  
    keywords = {"FINDNOTE"},
    level = 1,
    htype = "command",
    text = [[
Syntax: findnote <keyword>

This command searches through all the notes that you have on you. It
searches through portals, within portals, within portals, etc. It will
find the note and place it in your hands. The <keyword> must be words
taken from the subject of the note you are trying to find.
]],
  },
  {  
    keywords = {"FINFO"},
    level = 1,
    htype = "command",
    text = [[
Syntax: finfo
Syntax: finfo <following>

FINFO will give you information on the various followings that can be found in
our Realm.
]],
  },
  {  
    keywords = {"FLEE", "RESCUE"},
    level = 0,
    htype = "command",
    text = [[
Syntax: flee
Syntax: rescue   <character>

Once you start a fight, you can't just walk away from it.  If the fight
is not going well, you can attempt to FLEE, or another character can
RESCUE you.

If you lose your link during a fight, then your character will keep
fighting, and will attempt to RECALL from time to time.  Your chances
of making the recall are reduced, and you will lose much more experience.

In order to RESCUE successfully, you must practice the appropriate skill.
]],
  },
  {  
    keywords = {"FOLLOW"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  follow <character>

'Follow' starts you following another character.  To stop following, type
'follow self'.  You cannot follow those more than ten levels above you.

You may follow lower level characters or characters up to ten levels higher.
You must first follow someone before you can join their group.

See also GROUP
]],
  },
  {  
    keywords = {"FSTORE"},
    level = 1,
    htype = "command",
    text = [[
Syntax: fstore (objectname)

Used to send an object to your Followings special storage pit.  Items in this
pit save between reboots and crashes (most the time (; ).  Due to the magical
nature of these rooms, items can also randomly appear in them.

Only usable by characters in a Following.

Note: Stock items may not be placed into following pits.
]],
  },
  {  
    keywords = {"FTELL"},
    level = 1,
    htype = "command",
    text = [[
Syntax: ftell <message>

Provided that you are in a following, ftell will send the message to all
current members, as well as the deity.
]],
  },
  {  
    keywords = {"GCONSENT"},
    level = 1,
    htype = "command",
    text = [[
Syntax: gconsent

This command toggles on and off a "Consent" flag.  Certain commands may not be
used on characters unless they have their consent flags turned on.  Currently
the only commands that do this are "marry" and "divorce"
]],
  },
  {  
    keywords = {"GLANCE"},
    level = 1,
    htype = "command",
    text = [[
syntax:  glance
syntax:  glance <victim>

Glance alone shows you only the contents of the room you are in,
eliminating the description.  Glance <victim> shows only the health
condition, eliminating their description and equipment from your
screen.

"Autoglance" may be turned on in the CONFIG options.

Glance may be abbreviated as 'gl'.
]],
  },
  {  
    keywords = {"GOLD"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  gold

Displays the current total amount of gold you are carrying.
]],
  },
  {  
    keywords = {"GOSSIP", ".", "MUSIC", "ASK", "ANSWER", "SHOUT", "YELL"},
    level = 0,
    htype = "command",
    text = [[
Syntax: gossip   <message>
Syntax: music    <message>
Syntax: ask      <message>
Syntax: answer   <message>
Syntax: shout    <message>
Syntax: yell     <message>

These commands send messages through communication channels to other players.

SHOUT sends a message to all awake players in the world.  To curb excessive
shouting, SHOUT imposes a three-second delay on the shouter.

GOSSIP, MUSIC, and QUESTION and ANSWER also send messages to all interested
players.  '.' is a synonym for GOSSIP.  The ASK and ANSWER commands
both use the same 'question' channel

YELL sends a message to all awake players within your area.

You can use the CHANNELS command to hear, or not hear, any of these channels.
]],
  },
  {  
    keywords = {"GTELL", ";", "REPLY", "SAY", "TELL", "'"},
    level = 0,
    htype = "command",
    text = [[
Syntax: gtell <message>
Syntax: say   <message>
Syntax: tell  <character> <message>

All of these commands send messages to other players.  GTELL sends a message to
all of the characters in your group, wherever they are, even if they are
sleeping or stunned or dying.  ';' is a synonym for GTELL.

SAY sends a message to all awake players in your room.  The single quote '
is a synonym for SAY.

TELL sends a message to one awake player anywhere in the world.

REPLY sends a message to the last player who sent you a TELL.  REPLY will work
even if you can't see the player, and without revealing their identity.  This
is handy for talking to invisible or switched immortal players.
]],
  },
  {  
    keywords = {"HOLD", "REMOVE", "WEAR", "WIELD"},
    level = 0,
    htype = "command",
    text = [[
Syntax:  hold   <object>
Syntax:  remove <object>
Syntax:  remove all
Syntax:  wear   <object>
Syntax:  wear   all
Syntax:  wield  <object>

Three of these commands will cause you to take an object from your inventory
and use it as equipment:

HOLD is for lights, wands and staves; WEAR is for armor; WIELD is for weapons.

You may not be able to HOLD, WEAR, or WIELD an item if its alignment does not
match yours, if it is too heavy for you, or if you are not experienced enough
to use it properly.

WEAR ALL will attempt to HOLD/WEAR/WIELD each suitable item in inventory.

REMOVE will take an object from your equipment and place it into inventory.

REMOVE ALL will remove all your equipment and place it into inventory.
]],
  },
  {  
    keywords = {"HOMEPAGE"},
    level = 1,
    htype = "command",
    text = [[
Syntax: homepage (webpagename)

Sets a homepage listing in your "WHOIS" information.  You can use the "clear"
argument to remove a homepage listing.
]],
  },
  {  
    keywords = {"IGNORE"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  ignore
Syntax:  ignore <character>
Syntax:  ignore reply/none

Ignore allows you to ignore other characters in the House of Ghouls. All
tells, says, socials, and emotes from these characters will be blocked (gagged
out).  You will still see their communications through public channels,
however.

Simply typing ignore will give you a list of all the characters you are
currently ignoring.

Ignore <character> allows you to add or remove a character from your list
of ignored players.  If the name is already on the list it will be removed.
If the name is not on the list it will be added.  Note that only the names
of actual characters will be accepted and that it is not necessary for
them to be logged on at the time.

Ignore reply will cause you to ignore the last person to send you a tell.
This can be used to prevent invisible people from spamming you.

Ignore none will set you to ignoring no one.
]],
  },
  {  
    keywords = {"IMPALE"},
    level = 1,
    htype = "command",
    text = [[
Syntax: impale corpse

This is ultimate insult, leaving your victims bloody corpse, hanging from the
top of a pike for all to see.  Show everyone who is boss, by placing your
trophies wherever you want!

Note: Impaled corpses do not have 'corpse' as a keyword.
]],
  },
  {  
    keywords = {"INDUCT", "OUTCAST"},
    level = 1,
    htype = "command",
    text = [[
Syntax:  induct  <player>
         outcast <player>

Induct and outcast are following commands.  The leader and deity of the
following receive these commands.  Induct will bring a new player into the
clan, while outcast will remove them.
]],
  },
  {
  keywords = {"RESURRECT"},
  level = 1,
  htype = "command",
  text = [[
Syntax:  resurrect

If your pet should happen to get killed, you will be able to resurrect your
pet in a pet shop with the resurrect command.

You will need to have your pet's corpse in your inventory. The pet must have
belonged to you or else you will not be able to resurrect the pet. 

Resurrecting a pet is not a free service. The cost will depend on the level
of your pet. The higher the level of your pet, the higher the cost will be.

You will not be able to resurrect your pet if you killed it.
]],
  see_also = {"PETS", "PETSAVE"},
  },
  }
}
