all_helps.spell = {}
all_helps.spell = {
  entries = {
 
  {
    keywords = {"spells", "spell", "spells list", "spell list", "spell helps"},
    htype = "catagory",
    level = -1,
    text = function ()
     send("&WHelp files catagorized as 'spell'&D")
     send_nocr("&Y")
     hyphens()
     txt = "&W" .. get_catagory_list ("spell") .. "&Y"
     send(txt)
     hyphens()
     send([[
&WType 'practice' to get a list of spells currently available to you and
to see to what extent you have them practiced.  Type 'slist' to view a
list of all spells available at each level to your class.  Type 'mana all' to
see a list of how much mana each of your spells and skills cost, if any.
]])
   end,
  },
  {  
    keywords = {"ACETUM PRIMUS"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'acetum primus'      <victim>

This spell unleashes a powerful jet of acid, burning the flesh right of the
bones of his enemies.  The jet is thin enough that it only hits one enemy,
however.
]],
  },
  {  
    keywords = {"ACID BLAST"},
    level = 1,
    htype = "spell",
    text = [[
This spell creates a huge bubble of acid to burst in the midst of your foes.
All enemies within its radius will take acid damage.  This is an area-effect
spell.
]],
  },
  {  
    keywords = {"ACID BREATH", "FIRE BREATH", "FROST BREATH", "GAS BREATH", "LIGHTNING BREATH"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'acid breath'      <victim>
Syntax: cast 'fire breath'      <victim>
Syntax: cast 'frost breath'     <victim>
Syntax: cast 'gas breath'
Syntax: cast 'lightning breath' <victim>

Acid, fire, frost, and lightning damage one victim, whereas gas damages every
character in the room.  Fire and frost can break objects, and acid can damage
armor. All breath spells are non-verbal.

Gas breath is an area attack, the other breath spells are not.


]],
  },
  {  
    keywords = {"ACIDIC WEAPON", "SHOCKING WEAPON", "BURNING WEAPON", "FREEZING WEAPON"},
    level = 1,
    htype = "spell",
    text = [[
Special weapons can sometimes strike with elemental damage along with its
normal strike.  These mighty weapons should be taken care of, as they are rare
and command respect all over the Realms.
]],
  },
  {  
    keywords = {"ALCHEMY"},
    level = 1,
    htype = "spell",
    text = [[
Alchemy allows a shaman to use various magical components to create potions
that bestow magical effects on those who quaff them.  Due to the magical
nature of alchemical recipes, these items do not survive the death of the
carrier.  For more information about each type of alchemy, do "HELP 'ALCHEMY
(TYPE)".
Example: HELP 'ALCHEMY SHIELD'
]],
  },
  {  
    keywords = {"ALCHEMY ARMOR"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of armor.  Requires one charge of some iron shavings.
]],
  },
  {  
    keywords = {"ALCHEMY BALANCE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of balance.  Requires one charge from a mithril cylinder.
]],
  },
  {  
    keywords = {"ALCHEMY BLESS"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of bless.  Requires one charge of some gold flakes.
]],
  },
  {  
    keywords = {"ALCHEMY BLINDNESS"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of cure blindness.  Requires one charge from some rose essence.
]],
  },
  {  
    keywords = {"ALCHEMY CORRUPT"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of corruption.  Requires one charge from a dragon tooth.
]],
  },
  {  
    keywords = {"ALCHEMY CRITICAL"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of cure critical damage.  Requires one charge from an angel feather.
]],
  },
  {  
    keywords = {"ALCHEMY CURSE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of remove curse.  Requires one charge from some fish scales.
]],
  },
  {  
    keywords = {"ALCHEMY DEMON"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of demonsight.  Requires one charge from some emerald shards
and a mithril cylinder.
]],
  },
  {  
    keywords = {"ALCHEMY DIVINITY"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of divinity.  Requires an entire bundle of some oak leaves
and a silver orb.
]],
  },
  {  
    keywords = {"ALCHEMY ELDRITCH"},
    level = 1,
    htype = "spell",
    text = [[
Creates an eldritch sphere around the user.  Requires one charge from a dragon
tooth and some diamond dust.
]],
  },
  {  
    keywords = {"ALCHEMY ESCAPE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion useful for escaping to a safer place.  Requires one charge
from some oak leaves and some rose essence.
]],
  },
  {  
    keywords = {"ALCHEMY FIRE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of fireshield.  Requires one charge from a dragon tooth and a
demon horn.
]],
  },
  {  
    keywords = {"ALCHEMY FLY"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of fly.  Requires one charge of a steel cube.
]],
  },
  {  
    keywords = {"ALCHEMY GRACE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that can grant Immortal Grace to the user.  Requires an
entire angel feather, some fish scales, and some emerald shards.
]],
  },
  {  
    keywords = {"ALCHEMY HEAL"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of healing.  Requires one charge from some oak leaves and a
silver orb.
]],
  },
  {  
    keywords = {"ALCHEMY ICE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of iceshield.  Requires one charge from a demon horn and an
angel feather.
]],
  },
  {  
    keywords = {"ALCHEMY LEVEL"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that is beneficial to those about to level.  Requires one
charge from a demon horn.
]],
  },
  {  
    keywords = {"ALCHEMY LIGHT"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of cure light damage.  Requires one charge of some diamond dust.
]],
  },
  {  
    keywords = {"ALCHEMY MANA"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that will restore mana.  Requires an entire steel cube and a
silver orb.
]],
  },
  {  
    keywords = {"ALCHEMY METAL"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that give great magical shielding to the user.  Requires an
entire bundle of some oak leaves and some rose essence.
]],
  },
  {  
    keywords = {"ALCHEMY PANIC"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that help those stuck in places where regular recall spells
don't work.  Be aware that you can't always escape some situations!  Requires
an entire collection of some rose essence and some fish scales.
]],
  },
  {  
    keywords = {"ALCHEMY PIERCEBANE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that helps protect from piercing weapons.  Requires one
charge from an angel feather and some pine sap.
]],
  },
  {  
    keywords = {"ALCHEMY POISON"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of cure poison.  Requires one charge from some rose essence.]],
  },
  {  
    keywords = {"ALCHEMY PROTECT"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of protection.  Requires one charge from some emerald shards.
]],
  },
  {  
    keywords = {"ALCHEMY REFRESH"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of refresh.  Requires one charge of some ruby powder.
]],
  },
  {  
    keywords = {"ALCHEMY SANCTUARY"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of sanctuary.  Requires one charge from a steel cube and a
silver orb.
]],
  },
  {  
    keywords = {"ALCHEMY SERIOUS"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of cure serious damage.  Requires one charge from some oak leaves.
]],
  },
  {  
    keywords = {"ALCHEMY SHELTER"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that heals and protects the user.  Requires one charge from a
mithril cylinder and a dragon tooth.
]],
  },
  {  
    keywords = {"ALCHEMY SHIELD"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of shielding.  Requires one charge from some pine sap.
]],
  },
  {  
    keywords = {"ALCHEMY SHOCK"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of shockshield.  Requires one charge from an angel feather
and a dragon tooth.
]],
  },
  {  
    keywords = {"ALCHEMY SIGHT"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of true sight.  Requires one charge from some fish scales and
some emerald shards.
]],
  },
  {  
    keywords = {"ALCHEMY SLASHBANE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that helps protect from slashing weapons.  Requires one
charge from a demon horn and some iron shavings.
]],
  },
  {  
    keywords = {"ALCHEMY STONE"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of stone skin.  Requires one charge from some rose essence
and some fish scales.
]],
  },
  {  
    keywords = {"ALCHEMY TRAVEL"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that greatly refreshes adventurers.  Requires one charge from
some ruby powder and some emerald shards.
]],
  },
  {  
    keywords = {"ALCHEMY UNSEEN"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion that turns the user invisible.  Requires one charge from some
gold flakes and a mithril cylinder.
]],
  },
  {  
    keywords = {"ALCHEMY WATERBREATH"},
    level = 1,
    htype = "spell",
    text = [[
Creates a potion of aqua breath.  Requires one charge of a silver orb.
]],
  },
  {  
    keywords = {"ALERTNESS"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c alertness <self>

Alertness renders the target resistant to the sleep spell.
]],
  },
  {  
    keywords = {"ANIMATE DEAD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'animate dead' <victim>

After a mobile has been killed, the magic user has the ability to animate
the corpse of the recently deceased mob.  The mob will be animated with full
hitpoints and will be under the caster's control for a short period of time.
The undead can only exist in the living realm for a short period of time
before returning to the underworld.
]],
  },
  {  
    keywords = {"ANTIMAGIC SHELL"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'antimagic shell'      <victim>

This spell makes you more resistant to all types (including beneficial
types) of magic.  It also reduces the amount of damage you take from any
magical source.
]],
  },
  {  
    keywords = {"AQUA BREATH", "AQUA"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'aqua breath' <character>

This spell allows you to breath in water areas and underwater.  Certain
water sectors will require the use of aqua breath to prevent damage from
drowning.  If you are in an area and your movement suddenly begins to
drop and/or you begin losing hps <hitpoints>, you should either cast
aqua breath immediately or leave the area.
]],
  },
  {  
    keywords = {"ARMOR"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast armor <character>

This spell decreases (improves) the armor class of the target character
by 30 points.
]],
  },
  {  
    keywords = {"ARMORSMITH STANDARD", "ARMORSMITH SPELLWARD", "ARMORSMITH SPIKED", "ARMORSMITH SHIELD", "ARMORSMITH STEEL", "ARMORSMITH MAGESTONE", "ARMORSMITH BLADED", "ARMORSMITH DRAGONTEAR", "ARMORSMITH REINFORCED", "ARMORSMITH BLOODSTONE", "ARMORSMITH MIRROR", "ARMORSMITH VITALITY", "ARMORSMITH BARBED", "ARMORSMITH AVATAR"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'armorsmith (type)' <item>

A conjurer can imbue many different magical effects on armor.  These effects
can be placed on both magical and nonmagical armor, but only one can be
placed on an item at a time.  In addition, only conjurers may wear the item
once it has been smithed. Smithing requires components, and the entire
component is used when the spell is cast. Conjurer-enchanted items become
fragile and prone to change once the conjurer has been slain by another
player. See HELP 'CONJURERS EQUIPMENT'

Standard - some pine sap, some iron shavings
Spellward - some pine sap, some iron shavings, some diamond dust
Spiked = some pine sap, some iron shavings, some diamond dust, some gold
         flakes
Shield - some pine sap, some iron shavings, some diamond dust, some gold
         flakes, some ruby powder
Steel - some pine sap, some iron shavings, some diamond dust, some gold
        flakes, some ruby powder, a steel cube
Magestone - some pine sap, some iron shavings, some diamond dust, some gold
            flakes, some ruby powder, a steel cube, a silver orb
Bladed - some pine sap, some iron shavings, some diamond dust, some gold
         flakes, some ruby powder, a steel cube, a silver orb, some oak leaves
Dragontear - some pine sap, some iron shavings, some diamond dust, some gold
             flakes, some ruby powder, a steel cube, a silver orb, some oak
             leaves, some rose essence
Reinforced - some pine sap, some iron shavings, some diamond dust, some gold
             flakes, some ruby powder, a steel cube, a silver orb, some oak
             leaves, some rose essence, some fish scales
Bloodstone - some pine sap, some iron shavings, some diamond dust, some gold
             flakes, some ruby powder, a steel cube, a silver orb, some oak
             leaves, some rose essence, some fish scales, some emerald shards
Mirror - some pine sap, some iron shavings, some diamond dust, some gold
         flakes, some ruby powder, a steel cube, a silver orb, some oak
         leaves, some rose essence, some fish scales, some emerald shards, a
         mithril cylinder
Vitality - some pine sap, some iron shavings, some diamond dust, some gold
           flakes, some ruby powder, a steel cube, a silver orb, some oak
           leaves, some rose essence, some fish scales, some emerald shards, a
           mithril cylinder, a dragon tooth
Barbed - some pine sap, some iron shavings, some diamond dust, some gold
         flakes, some ruby powder, a steel cube, a silver orb, some oak
         leaves, some rose essence, some fish scales, some emerald shards, a
         mithril cylinder, a dragon tooth, a demon horn
Avatar - some pine sap, some iron shavings, some diamond dust, some gold
         flakes, some ruby powder, a steel cube, a silver orb, some oak
         leaves, some rose essence, some fish scales, some emerald shards, a
         mithril cylinder, a dragon tooth, a demon horn, an angel feather
]],
  },
  {  
    keywords = {"ARMORSMITH", "WEAPONSMITH"},
    level = 1,
    htype = "spell",
    text = [[
Smithing allows a conjurer to use components to imbue armor and weapons with
extra magical abilities.  These are very powerful skills, and conjurers can
smith both magical and nonmagical items.  The drawbacks to smithing is that
the item is set in tune with the conjurer, ensuring that only they can use
that item.  Due to the magical nature of smithed items, they may disappear
when the conjurer dies, depending on their power and intelligence.
]],
  },
  {  
    keywords = {"ASTRAL WALK", "FARSIGHT", "PORTAL"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'astral walk'  <victim>
Syntax:  cast 'farsight'     <victim>
Syntax:  cast 'portal'       <victim>

These spells allow the very shape of space and time to be warped at the
caster's bidding:

'Astral walk' instantaneously moves the caster to the victim's location.

'Farsight' allows you to see the room in which the victim stands.

'Portal' forms a temporary tunnel through space to the victim.  A portal
will not succeed if a portal already exists in either the caster's or
the victim's location.  Type 'enter' or 'enter portal' to pass through.

These spells may fail if either the victim or the caster is in a location
which blocks their use, such as no-recall areas, no-summon areas, etc.

See also TRANSPORT
]],
  },
  {  
    keywords = {"AURA OF FEAR"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'aura of fear'

A diabolist can learn to wrap an aura of chaos, which causes unease and
downright fear in those around him.  This causes most opponents to want to
avoid the diabolist, somehow unable to get close during combat.
]],
  },
  {  
    keywords = {"BENEDICTION"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast benediction

This spell lays upon the members of the casters group a strong, but
short-lived Protection affect.  It casts a little bit slower than other
spells.

]],
  },
  {  
    keywords = {"BENEFIC AURA"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c 'benefic aura'

The caster may infuse itself with a general protection from evil with
this ancient cantrip.  It requires the utilization of a holy symbol.


]],
  },
  {  
    keywords = {"BETHSAIDEAN TOUCH"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c 'bethsaidean touch' <target>

With the use of a holy symbol, one may endeavor to lift the blindness of the
afflicted.
]],
  },
  {  
    keywords = {"BINDING DARKNESS"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'binding darkness' victim

This spell causes tendrils of pure darkness to appear and wrap themselves
around the diabolist's foe, severely hampering their movements.  This makes it
easier for the caster and his allies to hit the enemy.
]],
  },
  {  
    keywords = {"BLACK FIST"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'black fist' <victim>

The spell 'Black Fist' calls from the Ethereal Plane a disembodied clenched
fist to pummel the calling Mage's opponents in combat with draining damage.
]],
  },
  {  
    keywords = {"BLACK HAND"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'black hand' <victim>

The spell 'Black Hand' calls from the Ethereal Plane a disembodied hand
to pummel the calling Diabolist's opponents in combat with lifedraining damage.
]],
  },
  {  
    keywords = {"BLACK LIGHTNING"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'black lightning' <victim>

The spell 'Black Lightning' calls from the Ethereal Plane a highly
organized spike of the Ethereal analogue to electricity.  This spike
orients itself on the calling Mage's main opponent in combat, onto
whom it unleashes its awesome destructive draining power.
]],
  },
  {  
    keywords = {"BLADE SHIELD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'blade shield'

This spell helps the caster avoid melee strikes.  By momentarily enhancing
their armor and assisting them with parrying blows, this spell is quite
powerful in protecting the user in battle.
]],
  },
  {  
    keywords = {"BLAZEBANE"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'blazebane' <mob>
Syntax:  cast 'blazebane' <player>

This spell makes the victim more susceptible to fire and heat.
]],
  },
  {  
    keywords = {"BLAZEWARD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast blazeward <victim>

This spell makes you more resistant to fire and heat.
]],
  },
  {  
    keywords = {"BLESS"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast bless <character>

This spell improves the to-hit roll and saving throw versus spell of the
target character.  The degree depends on the level of the caster.
]],
  },
  {  
    keywords = {"BLESS OBJECT"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'bless object' victim

Some items have powerful curses on them, causing them to stick to your person.
Sometimes this is a good thing...sometimes it is a bad thing.  If you find
yourself in need of having a curse from an object lifted, find an Immortal to
cast this spell on you.  Kallista will also help out for 50000 coins.
]],
  },
  {  
    keywords = {"BLIND BLINDNESS"},
    level = 1,
    htype = "spell",
    text = [[
syntax:  cast blindness <victim>

This spell renders the target character blind.

See also BLINDED, GOUGE
]],
  },
  {  
    keywords = {"BOTTLE", "UNBOTTLE"},
    level = 1,
    htype = "spell",
    text = [[
syntax: cast 'bottle' victim
syntax: unbottle (bottlename)

Bottle is a handy spell that entraps a creature inside a magical vial.
Creatures that are naturally aggressive cannot be bottled.

Unbottle will release a creature from a bottle, where it will serve some time
as your loyal companion.
]],
  },
  {  
    keywords = {"BROTHERHOOD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast brotherhood

When clerics have a group of allies together, they can call upon their spirit
of Brotherhood.  This casts an armor spell upon each member of the group.
]],
  },
  {  
    keywords = {"BURNING HANDS"},
    level = 1,
    htype = "spell",
    text = [[
This spell shoots a thin jet of flame from each fingertip of the caster,
causing fire damage to a single enemy.]],
  },
  {  
    keywords = {"CALL LIGHTNING"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'call lightning'

This spell works only out of doors, and only when the weather is bad.
It calls down lightning bolts from the gods.  This attack strikes the whole area.

Be aware that area attacks are aggressive to all mobs in the room,
including pets, mounts and charmed creatures.
]],
  },
  {  
    keywords = {"CAUSE LIGHT", "CAUSE SERIOUS", "CAUSE CRITICAL", "HARM"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'cause light'    <victim>
Syntax: cast 'cause serious'  <victim>
Syntax: cast 'cause critical' <victim>
Syntax: cast harm             <victim>

These spells inflict damage on the victim.  The higher-level spells do
more damage.
]],
  },
  {  
    keywords = {"CAUSTIC FOUNT"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'caustic fount' (victim)

'Caustic Fount' causes a fountain of acid to levitate about the casting
druid's victim, bathing him in a malodorous and painful concoction.  The
combination of magical and physical attack gives this spell appreciable effect
in combat versus a wide variety of physical types.
]],
  },
  {  
    keywords = {"CHANGE SEX"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'change sex' <victim>

This spell changes the sex of the victim (temporarily).
]],
  },
  {  
    keywords = {"CHARGED BEACON"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c 'charged beacon' <victim>

Charged beacon renders the victim susceptible to electricity attacks.
]],
  },
  {  
    keywords = {"CHARM", "CHARM PERSON"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'charm person' victim

The charm spell, if successful, will place the victim (only mobs, attempts
to charm other player-characters may incur the wrath of the gods) under
your control for the duration of the spell.  While under your control
the creature is your servant, and may assist you in combat and other
more minor duties.  Use the 'order' command to give them orders.

Be warned, you are responsible for the actions of your charmed beast.  If
it should go awry and take the life of another player-character, you will
be charged as a murderer and will be hunted by several creatures around
the Realms.

Aggressive mobs will lose their aggressiveness while charmed, but will
immediately return to their violent ways when the spell wears off.  For
this reason, charmed aggressive mobs should not be taken into any area
lower from the one from which they came, and should *never* be taken
into Alden or the University.  Those found doing so will pay dearly.

As a matter of etiquette, charmed mobs should not be attacked.  You can
tell a mob is charmed if it is wandering "in a dazed, zombie-like state."
Be aware when taking your charmed mobs around other characters that any
area attack such as call lightning, gas breath or earthquake will hit
your creature and cause it to engage in combat.

SEE ALSO: Help dismiss
]],
  },
  {  
    keywords = {"CHILL TOUCH"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: c 'chill touch' <victim>

This spell inflicts damage on the victim, and reduces their strength for a
short period of time.
]],
  },
  {  
    keywords = {"COLOUR SPRAY"},
    level = 1,
    htype = "spell",
    text = [[
One of a mages first area-effect spells, colour spray causes several extremely
bright strobes of colored light to explode in the face of your enemies.  The
light causes energy damage, and can temporarily blind them also!  This is an
area-effect spell.
]],
  },
  {  
    keywords = {"CONJURERS SWORD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'conjurers sword'

This mighty spell summons up a powerful blade, that only a conjurer can wield.
It hits very hard, and blasts those it strikes with bolts of lightning.
However, this sword is tied tightly to the ethereal plane, and will eventually
return to where it came from, leaving the conjurer weaponless!  Conjurers
sword requires an entire set of some diamond dust, a steel cube, a silver orb,
and a mithril cylinder.
]],
  },
  {  
    keywords = {"CONTINUAL LIGHT"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'continual light'

This spell creates a ball of light, which you can hold as a light source.
The ball of light will last indefinitely.
]],
  },
  {  
    keywords = {"CONTROL WEATHER"},
    level = 0,
    htype = "spell",
    text = [[
Syntax:  cast 'control weather' <warmer/colder>
Syntax:  cast 'control weather' <wetter/drier>
Syntax:  cast 'control weather' <windier/calmer>

This spell allows you to change either the temperature, amount of
precipitation, or amount of wind.  Note that these changes do not
take effect until the next tick.
]],
  },
  {  
    keywords = {"CREATE FIRE"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'create fire'

This spell brings forth a magical fire from the ground.  It will light up a
room, and some skills may need a fire available to use correctly.
]],
  },
  {  
    keywords = {"CREATE FOOD"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'create food'

This spell creates a Magic Mushroom, which you or anyone else can eat.
]],
  },
  {  
    keywords = {"CREATE SPRING"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'create spring'

This spell brings forth a magical spring from the ground, which has the
same properties as a fountain.
]],
  },
  {  
    keywords = {"CREATE SYMBOL"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'create symbol'

This spell creates a holy symbol which is required as a component in
powerful clerical spells.
]],
  },
  {  
    keywords = {"CREATE WATER"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'create water' <drink-container>

This spell replenishes a drink container with water.
]],
  },
  {  
    keywords = {"CURE BLINDNESS"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'cure blindness' <character>

This spell cures blindness in one so unfortunate.
]],
  },
  {  
    keywords = {"CURE LIGHT", "CURE SERIOUS", "CURE CRITICAL", "HEAL"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast heal            <character>
Syntax:  cast 'cure critical' <character>
Syntax:  cast 'cure serious'  <character>
Syntax:  cast 'cure light'    <character>

These spells heal damage suffered by the target character.  The higher-level
spells heal more damage.
]],
  },
  {  
    keywords = {"CURE POISON"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'cure poison' <character>

This spell cures poison in one so unfortunate.
]],
  },
  {  
    keywords = {"CURE WEAKNESS"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'cure weakness' victim

Many foes in the Realm have the ability to drain your strength right out of
your body with a simple spell.  Clerics have learned to remove that curse,
restoring your might.
]],
  },
  {  
    keywords = {"CURSE"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'curse' <character>

This spell reduces the character's to-hit roll by -5 and save versus spells
by 5.  It also renders the character unclean in the eyes of the gods and
unable to RECALL.
]],
  },
  {  
    keywords = {"DAEMON GUARDIAN"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'daemon guardian'

The most mighty diabolists can expend a tremendous amount of magical power in
an attempt to bring forth a daemon from the warp.  This daemon is often near
equal in power to the caster, and wields its own wicked spells in combat.
Only one can be controlled at a time...no other creatures can be under the
diabolists control.  A daemon guardian is not to be faced lightly...and with a
skilled diabolist supporting them in combat, know that you are in great danger
indeed...
]],
  },
  {  
    keywords = {"DEMONIC BEAST"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'demonic beast'
Syntax: c demonic

This spell allows the Diabolist to summon up a creature from the Nether
Realms, and force it to do their bidding for a time.  When the spell wears
off, the beast dissipates and returns to where it came from.
]],
  },
  {  
    keywords = {"DEMONSIGHT"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast demonsight

Demonsight allows the caster to see a victims alignment or detect hidden
persons or objects...even those camouflaged by high-level crooks.
]],
  },
  {  
    keywords = {"DEMONSKIN"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast demonskin

This spell makes you less susceptible to slashing attacks.]],
  },
  {  
    keywords = {"DETECT EVIL", "DETECT GOOD"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'detect evil'
Syntax: cast 'detect good'

These spells enables the caster to detect evil or good characters, which will
reveal a characteristic red or blue aura.
]],
  },
  {  
    keywords = {"DETECT HIDDEN"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'detect hidden'

This spell enables the caster to detect hidden creatures.
]],
  },
  {  
    keywords = {"DETECT INVIS"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'detect invis'

This spell enables the caster to detect invisible objects and characters.
]],
  },
  {  
    keywords = {"DETECT MAGIC"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'detect magic'

This spell enables the character to detect the presence of magic in
objects, and is also necessary to detect the magical affects of
others for the successful use of the 'dispel magic' spell.

See also DISPEL MAGIC
]],
  },
  {  
    keywords = {"DETECT POISON"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'detect poison' <object>

This spell detects the presence of poison in food or drink.
]],
  },
  {  
    keywords = {"DETECT TRAPS"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'detect traps'

This spell makes one magically aware of dangerous traps for a period of
time.

]],
  },
  {  
    keywords = {"DISPEL EVIL", "DISPEL GOOD", "DISPEL NEUTRAL"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'dispel evil' <victim>
Syntax: cast 'dispel good' <victim>
Syntax: cast 'dispel neutral' <victim>

These spells invoke the wrath of the gods upon a victim of a certain
alignment.  If you do not specify a target, the spell's effect will strike you
instead of a secondary target.

If a good person tries to dispel good, or evil tries to dispel evil, the gods
will be angered, and strike the caster instead.  Neutral clerics can also
dispel good and evil, but the damage is a lot less, due to their balanced
nature.  Neutrals trying to dispel neutral will hit themselves, while good or
evil characters will hit the neutral character for a bit less damage than
their other dispel spells.
]],
  },
  {  
    keywords = {"DISPEL MAGIC"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'dispel magic' <character>

This spell dispels magical affects on the victim.  It may be used as an
offensive spell to remove an enemy's magical advantages, or as a benign
spell to completely remove your own magical affects.

If you are not a mage, you must be affected by the 'detect magic' to be
able to use this spell.  Though mages do not necessarily need to use it,
being under the affects of 'detect magic' will reveal more information
unavailable to other classes.

'Dispel magic' can be used by players and mobiles alike against either
players or mobiles.  It cannot remove affects from equipment, your race
or your deity; some other affects are immune to this spell as well.

When a caster successfully casts 'dispel magic' on themselves they will
remove all of their dispellable magical affects.  If a mage successfully
dispels a victim, the number of affects stripped will depend on their
success and intelligence.  Otherwise a successful cast of 'dispel magic'
on a victim will result in the removal of a single affect each time
(victims will notice when and what affects are stripped).

WARNING:  this is an offensive spell, and its use on anyone other than
yourself will be treated as an attack on your target.
]],
  },
  {  
    keywords = {"DISRUPTION"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast disruption (victim)

With the spell 'Disruption,' the casting Diabolist causes his opponent to
be enveloped in a weird energy field that momentarily alters the plane
which the victim inhabits.  The spell was an early attempt by the Dark
Wizard Thanatos to cause teleportation, but it was a failed attempt.
Instead of teleporting it causes a horrendous nerve-wracking pain as
the victim exits and reenters his current plane of existence.]],
  },
  {  
    keywords = {"DIVINITY"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c divinity <target>

This spell heals the target of 200 hitpoints of damage.  It requires the use
of a holy symbol to cast.
]],
  },
  {  
    keywords = {"DRAGON WIT", "DRAGONWIT"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'dragon wit'

This spell increases your ability to reason for its duration.
]],
  },
  {  
    keywords = {"DRAGONSKIN"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'dragonskin'

This spell makes you less susceptible to piercing weapons.
]],
  },
  {  
    keywords = {"DREAM"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast 'dream' <player>  <message>

This spell enables you to cast a dream or message on a sleeping player.
]],
  },
  {  
    keywords = {"EARTHQUAKE"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'earthquake'

This spell inflicts damage on every enemy character in the room.
Beware that other characters who are not yet fighting may attack
you as a result!

Be aware that area attacks are aggressive to all mobs in the room,
including pets, mounts and charmed creatures.
]],
  },
  {  
    keywords = {"ELDRITCH SPHERE"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'eldritch sphere'

This powerful spell increases your resistance to both magical and nonmagical
attacks.
]],
  },
  {  
    keywords = {"ELVEN BEAUTY"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'elven beauty'

This spell makes you more charismatic for its duration.
]],
  },
  {  
    keywords = {"ENCHANT ARMOR"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'enchant armor' <object>

Items of type 'armor' or 'artarmor' may be enchanted with this spell,
yielding an addition to hit points, armor class and svp. This spell can
enchant magical as well as non-magical items but may not be used to enchant
an item that is already enchanted. However, if the item is magical the
enchant will not be as powerful as it could be otherwise. This spell also
causes the item to be aligned with the alignment with the caster.
]],
  },
  {  
    keywords = {"ENCHANT WEAPON"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'enchant weapon' <weapon>

Items of type 'weapon' or 'artweapon' may be enchanted with this spell,
yielding an addition to damage roll and hit roll. This spell can enchant
magical as well as non-magical weapons but may not be used to enchant
a weapon that is already enchanted. However, if the weapon is magical the
enchant will not be as powerful as it could be otherwise. This spell also
causes the weapon to be aligned with the alignment with the caster.
]],
  },
  {  
    keywords = {"ENERGY DRAIN"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'energy drain' <victim>

This spell saps the hit points, mana, and movement points of its
target.  This is an attack spell and should not be used against other
players.
]],
  },
  {  
    keywords = {"ETHEREAL FIST"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'ethereal fist' (victim)

'Ethereal Fist' is an enchantment in which the casting Mage
conjures from the ether about himself a solid manifestation of a
cubical volume of ether.  As if this weren't great fun in and of
itself, the final syllables of the spell cause the fist to
repeatedly and mercilessly pound into a victim of the caster's choice.

Fun to cast in a room by yourself, and always a hit at parties,
'Ethereal Fist' is a low-level Mage's best friend.
]],
  },
  {  
    keywords = {"ETHEREAL FUNNEL"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'ethereal funnel'

This spell increases the damage done to the victim by energy attacks.
]],
  },
  {  
    keywords = {"ETHEREAL SHIELD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'ethereal shield'

This spell decreases the amount of damage taken from energy attacks.
]],
  },
  {  
    keywords = {"EXPURGATION"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  cast expurgation

This spell was granted by the Gods, when it was discovered that many of
their devout Paladins were falling prey to poisons. This spell will cure
the poison, but if the Paladin's state of mind has been affected..it will
still require rest.
]],
  },
  {  
    keywords = {"EXTRADIMENSIONAL PORTAL", "EXTRADIMENSIONAL"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'extradimensional portal'

The Great Wizard Thanatos, after creating his fabled WarMagicks,
found himself snubbed and abused in and about The Realms for his
researches.  Much time would pass before mages and other classes
alike would learn the true power of these spells.

In the interim, disguised as an assassin, Thanatos became interested
in a more minor problem: that of carrying off the loot he gained
from all those he slew with Quantum Spike.  Realizing that such a
formula would be easily grasped by his class, he thought to extend
it freely.
]],
  },
  {  
    keywords = {"EYES OF THE HUNTER"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'eyes of the hunter'
        cast eyes

The most adept hunters have the ability to recreate the vision of the mighty
cats of the realm.  Able to detect hidden objects and things that are trapped
is nice enough, but their catlike vision also allows them to hit more
accurately and for a bit more damage.
]],
  },
  {  
    keywords = {"FAERIE FIRE"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'faerie fire' <victim>

This spell increases (makes worse) the armor class of its victim.  For each
level of the caster, the victim's armor class is increased by two points.
]],
  },
  {  
    keywords = {"FAERIE FOG"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'faerie fog'

This spell reveals all manner of invisible, hidden, and sneaking creatures in
the same room as you.
]],
  },
  {  
    keywords = {"FATIGUE"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c fatigue <victim>

Fatigue renders the victim susceptible to sleep and also saps them of
their energy, making movement difficult.
]],
  },
  {  
    keywords = {"FEAR"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast fear (victim)

Druids reaching a high enough level can call upon the forces of Nature and
twist the basic emotions of a foe.  A horrifying spell, this causes the victim
to run blindly in fear, fleeing all about with no control.
]],
  },
  {  
    keywords = {"FEEBLENESS"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c feebleness <victim>

Feebleness renders your victim susceptible to draining attacks.
]],
  },
  {  
    keywords = {"FIREBALL"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast fireball

A favorite spell of most mages, fireball lets loose a large explosion of flame
amongst your enemies.  Anyone caught in the blast will take damage.  This is
an area-effect spell.
]],
  },
  {  
    keywords = {"FLAMESTRIKE"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast 'flamestrike' <victim>

This spell inflicts a very heavy amount of flame damage on the victim.
]],
  },
  {  
    keywords = {"FLAMING BLAST"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'flaming blast' victim

A powerful attack spell, conjurers can summon forth a huge ball of flame and
hurl it at their foes.  It burns them for quite a bit of damage.  Flaming
blast requires one charge from some oak leaves and some fish scales.
]],
  },
  {  
    keywords = {"FLARE"},
    level = 1,
    htype = "spell",
    text = [[
This spell causes magical flames to erupt around an opponent.  Care must be
used not to burn one's self up during its use!  This is used for Fireshield.]],
  },
  {  
    keywords = {"FLOAT"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'float' <character>

This spell enables the target character to float.  It is useful in saving
mv (movement points), makes a character float slowly to the ground when
falling from in the air, and allows you to move over water and through the
air as well as preventing an opponent from tripping you.  It does not allow
you to travel through areas which require you to fly, however..

Some water areas require the use of float to prevent damage from drowning.
If you are in an area and your movement suddenly begins to drop, then you
begin losing hps <hitpoints>, you should cast float immediately.
]],
  },
  {  
    keywords = {"FLY"},
    level = 0,
    htype = "spell",
    text = [[
Syntax:  cast 'fly' <character>

This spell enables the target character to fly.  It is useful in saving
mv (movement points), preventing a character from falling when in the
air, moving over water or through the air, and in preventing an opponent
from tripping you.

Some water areas require the use of fly to prevent damage from drowning.
If you are in an area and your movement suddenly begins to drop, then you
begin losing hps <hitpoints>, you should cast fly immediately.
]],
  },
  {
    keywords = {"FORTIFY"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast fortify

Sometimes, groups of characters may all be hurt during combat.  A cleric can
use the 'fortify' spell to heal each member of the group at once.  While the
healing is not extensive, it is useful to keep everyone from expiring at once.
]],
  },
  {  
    keywords = {"GALVANIC WHIP"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'galvanic whip' (victim)

The spell 'Galvanic Whip' allows the casting druid to form in the air
a highly charged rope of air that automatically lashes out at his
opponents in combat.  The Whip may be called once per combat round.
]],
  },
  {  
    keywords = {"GATE"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast gate

This spell gates in a guardian vampire.  The vampire will be charmed and
following the caster for a short time, and will help them in combat.
]],
  },
  {  
    keywords = {"GODSTORM"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast godstorm

Using two rare components, a Conjurer can summon up a storm created from the
very Fury of the Gods!  This spell rips through a small area, causing great
damage to all.  The more intelligent the Conjurer is, the more damage this
spell does.  This spell uses up all charges in the angel feather and demon
horn needed.
]],
  },
  {  
    keywords = {"GOLEM CLOAK"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'golem cloak' item

A conjurer can enchant any non-magical armor that is worn about the body with
this spell.  Of course, only a golem can wear that armor after the enchantment
is cast, but the golem who wears a golem cloak is granted more hitpoints,
better armor class, and a huge increase in hitroll and damroll.  Golem cloak
requires one charge from some gold flakes, some fish scales, and a dragon
tooth.
]],
  },
  {  
    keywords = {"GOLEM FISTS"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'golem fists' item

This spell can be used by a conjurer to enchant any non=magical hand armor
such as gloves or gauntlets.  After the enchantment, they can only be used by
golems, but the golem is granted much more hitroll and damroll than they have
normally.  This spell requires one charge from some iron shaving, some oak
leaves, and some emerald shards.
]],
  },
  {  
    keywords = {"GOLEM PLATE"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'golem plate' item

A conjurer can enchant a non-magical piece of body armor with this spell.  It
provides extra armor and hitpoints to a golem wearing the armor.  Once cast on
a piece of armor, only golems can make use of it from that point on.  This
spell requires one charge from some diamond dust, a steel cube, and a silver
orb.
]],
  },
  {  
    keywords = {"GOLEM SHIELD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'golem shield' item

Using a non-magical shield, an conjurer can place a mighty enchantment which
turns the shield into a golem shield.  This shield grants a golem greater
hitpoints, better armor, and even more hitroll and damroll.  Only a golem can
use a golem shield.  Golem shield requires one charge from some diamond dust,
some rose essence, and a demon horn.
]],
  },
  {  
    keywords = {"GOLEM WEAPON"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'golem weapon' item

Turning a non-magical weapon into a mighty tool for the golem is one of the
conjurers more powerful spells.  A golem weapon can only be used by a golem,
of course, but it grants higher armor, more hitpoints, a huge boost to hitroll
and damroll, and allows the golem the ability to hit its foes with freezing
blasts!  Golem weapon requires one charge from a steel cube, some emerald
shards, and an angel feather.
]],
  },
  {  
    keywords = {"GRANT AURALINK", "AURALINK"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'grant auralink' victim

Mages and Gods have the ability of "auralink".  This is the ability to see
both on the magical and prime planes at the same time.  Mainly this affect is
useful for sensing the power levels of magical items...but it may be more
useful in other places...Note that this ability is useless unless the bearer
already has the ability to sense a magical aura in the first place!

Mages can grant this ability to others, but it drains quite a bit of their
mana reserves.
]],
  },
  {  
    keywords = {"GROUNDING"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c grounding

Grounding renders the victim resistant to electricity attacks.
]],
  },
  {  
    keywords = {"HELICAL FLOW"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'helical flow' (victim)

Teleports the caster through the ether to their victim.
]],
  },
  {  
    keywords = {"HEZEKIAH", "HEZEKIAHS", "HEZEKIAHS CURE"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c 'hezekiahs cure' <target>
         c hezekiahs        <target>

Hezekiah was a great Paladin for whom the Gods showed great pleasure.
As a reminder of his greatness, the Gods granted a spell in his honor.
The spell brings about a mild cure to the wounded, with the use of
a Holy Symbol.
]],
  },
  {  
    keywords = {"HOLY SANCTITY"},
    level = 1,
    htype = "spell",
    text = [[
Syntax:  c 'holy sanctity'

This spell casts sanctuary on every member of the cleric's group.  This spell
requires the use of a holy symbol.
]],
  },
  {  
    keywords = {"HOLY WORD"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'holy word'

This spell allows a Cleric to shout forth any one of a number of words that
takes on its own awesome power when mixed with Clerics faith.  The energy is
focused into a great flash that damages all foes in the room, and also blinds
them for a short time!
]],
  },
  {  
    keywords = {"ICE BLAST"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast 'ice blast' (victim)

This blast of ice causes your opponents bones to chill, to the point where
they are weakened by the cold, and cannot fight back as effectively as normal.
]],
  },
  {  
    keywords = {"ICESHARD"},
    level = 1,
    htype = "spell",
    text = [[
Iceshard is the spell effect used by Iceshield.
]],
  },
  {  
    keywords = {"ICESHIELD", "FIRESHIELD", "SHOCKSHIELD"},
    level = 1,
    htype = "spell",
    text = [[
Iceshield conjures an encompassing shield of ice which will return the
attacks of your enemy with tongues of cold.
Syntax:  cast iceshield

Fireshield surrounds the caster with a wall of fire which returns your
enemies' attacks with balls of fire.
Syntax:  cast fireshield

Shockshield surrounds the caster with a field of electric energy which will
return your enemies' attacks with bolts of lightning.
Syntax:  cast shockshield

The chances of your shields striking your opponent increase with your level,
with the odds at low levels being very low.

Like shields will negate each other's effects.  For example, if your enemy
has fireshield, your fireshield will counter any fireballs thrown by his,
and his will counter any fireballs thrown by yours.
]],
  },
  {  
    keywords = {"IDENTIFY"},
    level = 0,
    htype = "spell",
    text = [[
Syntax: cast identify <target>

This spell reveals information about the target
]],
  },
  {  
    keywords = {"IMMORTAL GRACE"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: c 'immortal grace' victim

This is a special spell for Immortals, which they can use to heal and restore
their followers mana.  It costs quite a bit of their mana, but is sure to save
the lives of many of their worshippers.
]],
  },
  {  
    keywords = {"INDIGNATION"},
    level = 1,
    htype = "spell",
    text = [[
Syntax: cast indignation

Priests of the Realm at times must enter combat to protect their values.
Their gods support them by instilling righteous indignation into their bodies,
causing the caster and anyone in their group to hit more often.
This effect may not last long, but can turn the tide in a difficult battle.
This spell is useful in groups, as it casts itself on each grouped player.
]],
  },
  {
    keywords = {"spirit syphon"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'spirit syphon' <victim>

By using a small amount of mana and one's life force, the caster's victim
is damaged, stealing some of the victim's magic in the process.

This spell can only be used to initiate combat.
]],
  },
  {
    keywords = {"disrupt gravity"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'disrupt gravity'

The laws of gravity are bent around the caster, protecting the caster from the
rushing attacks of enemies and lessening damage dealt.
]],
  },
  {
    keywords = {"disrupt physics"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'disrupt physics' <victim>

The caster alters and corrupts the laws of physics around the victim,
weakening the victim's ability to cast spells and making them more susceptable
to spell damage.
]],
  },
  {
    keywords = {"kinetic shield"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'kinetic shield'

By tampering with the laws of energy and motion, the caster is shielded from
the physical attacks and abilities of enemies.
]],
  },
  {
    keywords = {"ethereal storm"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'ethereal storm' <victim>

The caster channels a great flood of ethereal energy into a singular blast
that can send even the strongest opponent into the afterlife. Due to the
concentration involved, this spell cannot be cast in combat.
]],
  },
  {
    keywords = {"spell surge"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'spell surge'

The caster consumes both health and magic to provide a huge boost to spell
abilities and defenses against spells.
]],
  },
  {
    keywords = {"magika rage"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'magika rage'

The caster consumes much of their mana and health to enter an enraged state
where all their defenses are weakened while their magical offense increases by
an awesome amount.
]],
  },
  {
    keywords = {"divine wings"},   
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'divine wings'

The caster asks the celestial plane for shelter. Divine wings envelope the
caster, providing protecting from damage.
]],
  },
  {
    keywords = {"daemonic grace"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'daemonic grace'

The caster asks the demon realm for its blessing, giving a boost to defense
against magic.
]],
  },
  {
    keywords = {"spirit guide"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'spirit guide'
        cast 'spirit guide' <target>

The caster asks the spirit world to grant a guide to themself or others,
offering the blessed with an increased protection from physical dangers.
]],
  },
  {
    keywords = {"daemonic flame"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'daemonic flame' <victim>

The caster summons black fire from the nightmare realms to damage the target
who is then afflicted with a slight weakness to spells and damage.
]],
  },
  {
    keywords = {"darkness binds"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'darkness binds' <victim>

The caster entangles the victim in the bondage of the demon realms, making the
victim's armor brittle, increasing damage done by spells, and making the
victim more vulnerable to drain and paralysis.
]],
  },
  {
    keywords = {"poltergiest"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast poltergeist <victim>

The caster uses a vast repetoire of knowledge to summon a poltergeist that
flings a few objects at the victim, inflicting damage.
]],
  },
  {
    keywords = {"sword serenade"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'sword serenade' <victim>

The caster sings to the victim's weapon, weakening the victim's ability to
fight.
]],
  },
  {
    keywords = {"whisper blade"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'whisper blade' <victim>

The caster summons the inherent power of their own weapon to weaken the power
of the victim's voice.
]],
  },
  {
    keywords = {"celestial guardian"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'celestial guardian' <target>

The caster asks the Celestial plane to both protect and restore. The target of
the blessing receivings a temporary boost to damage absorbtion and a portion
of hitpoints is restored.
]],
  },
  {
    keywords = {"spirit charger"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'spirit charger' <victim>

This spell can only be used to initiate combat.
The caster focuses righteous energies and unleashes a powerful attack that
also lowers the magical powers of the victim.
]],
  },
  {
    keywords = {"answered prayers"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'answered prayers'

Your prayers are answered by your deity in the form of a generous portion of
your hitpoints being restored.
]],
  },
  {
    keywords = {"daemonic scythe"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'daemonic scythe' <victim>

Summon forth a powerful daemonic scythe to slice through your opponents.
]],
  },
  {
    keywords = {"divine avatar"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'divine avatar'

Invoke the avatar of your deity to provide a burst of protection and healing.
]],
  },
  {
    keywords = {"desperate plea"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'desperate plea'

Make a desperate plea in the most critical of times and recieve a generous
restoration to a portion of your hitpoints.
]],
  },
  {
    keywords = {"heaven and hell"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'heaven and hell'

This is an area attack spell.
Summon forth the fiery fury of both Heaven and Hell to devistate all nearby
foes.
]],
  },
  {
    keywords = {"ghost strike"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'ghost strike' <victim>

Strike out at an enemy with unnatural speed.
]],
  },
  {
    keywords = {"disrupt reality"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'disrupt reality'

The caster alters reality long enough to disengage and summon forth two
guardians from the ether to engage the caster's combatant. This spell can
only be used in combat.
]],
  },
  {
    keywords = {"armor of leaves"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'armor of leaves'

The caster invokes an armor of leaves and twigs, offering no physical
protection but shielding from the breath attacks of others.
]],
  },
  {
    keywords = {"natures wrath"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'natures wrath'

The caster is able to summon the inherent destructive nature of the earth to
provide a boost to spell damage.
]],
  },
  {
    keywords = {"mute"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast mute <victim>

Render your victim unable to cast verbal spells.
]],
  },
  {
    keywords = {"blade spirit"},    
    level = 1,    
    htype = "spell",
    text = [[
]],
  },
  {
    keywords = {"corrupt armor"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'corrupt armor' <victim>

The diabolist calls forth the lords of the abyss to taint the armor of his
opponent, making it brittle and weak.
]],
  },
  {
    keywords = {"daemonic armor"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'daemonic armor'

The diabolist shields themself with dark energies, providing a small bonus to
their armor's strength but also protecting them against the more vile magiks
of the world.
]],
  },
  {
    keywords = {"higher calling"},    
    level = 1,    
    htype = "spell",
    text = [[
]],
  },
  {
    keywords = {"holy flame"},    
    level = 1,    
    htype = "spell",
    text = [[
]],
  },
  {
    keywords = {"idol"},    
    level = 1,    
    htype = "spell",
    text = [[
]],
  },
  {
    keywords = {"enhance aura"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'enhance aura' <object>

The archmagi can imbue any unenchanted item with a small boost to her spell
damage.
]],
  },
  {
    keywords = {"daemonic pact"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'daemonic pact'

The Bishop calls upon the daemon lords to heal herself and all others in her
party, although the Bishop receives much less healing than the rest of her
group.
]],
  },
  {
    keywords = {"celestial trumpets"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'celestial trumpets'

The Bishop calls upon the celestial choir to provide a huge boost to the
morale of the party, increasing all protections for a short time.
]],
  },
  {
    keywords = {"pierce shadows"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'pierce shadows'

The caster of this spell summons forth a powerful glowing blade that will
slice through anyone or anything trying to be unseen in the room, leaving them
damaged and stunned.
]],
  },
  {
    keywords = {"enhance treasure"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'enhance treasure' <object>

Items of type 'treasure' or 'arttreasure' may be enhanced with this spell,
yielding an addition to spell damage and mana points. This spell can enhance
magical as well as non-magical items but may not be used to enhance an item
that is already enchanted.
]],
  },
  {
    keywords = {"enhance armor"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'enhance armor' <object>

Items of type 'armor' or 'artarmor' may be enhanced with this spell,
yielding an addition to mana points, armor class and svs. This spell can
enchant magical as well as non-magical items but may not be used to enhance
an item that is already enchanted. However, if the item is magical the
enhancement will not be as powerful as it could be otherwise. This spell also
causes the item to be aligned with the alignment with the caster.
]],
  },
  {
    keywords = {"enhance weapon"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'enhance weapon' <object>

Items of type 'weapon' or 'artweapon' may be enhanced with this spell,
yielding an addition to spell damage. This spell can enhance magical as
well as non-magical weapons but may not be used to enhance a weapon that
is already enchanted. However, if the weapon is magical the enhancement
will not be as powerful as it could be otherwise. This spell also causes
the weapon to be aligned with the alignment with the caster.
]],
  },
  {
    keywords = {"venom arrow"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'venom arrow' <target>

Using a stash of poisoned bolts, one can fire one at their opponent causing
them to become poisoned and injured. This spell requires the use of a missile
type weapon.
]],
  },
  {
    keywords = {"barbed arrow"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'barbed arrow' <target>

With the use of barbed bolts and a missile type weapon, one can inflict damage
upon their opponent. The barb stays with the victim causing them to take more
damage than usual.
]],
  },
  {
    keywords = {"numbing arrow"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'numbing arrow' <target>

With the use of a missile type weapon, one can fire a special poisoned bolt at
their opponent to inflict a great bit of damage as well as causing some form
of paralysis.
]],
  },
  {
    keywords = {"summon spirit"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'summon spirit' <target>

After a mob has been killed, the caster initiates a ritual that can summon the
spirit of the slain mob. The spirit will be under the caster's control for a
period of time and able to assist in combat. The spirit can only exist in the
living realm for a period of time before returning to the afterlife.
]],
  },
  {
    keywords = {"prismashield"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast prismashield

By summoning up a prismatic ward of ether, the caster can protect thierself
from the effects of the elemental shields.
]],
  },
  {
    keywords = {"magika armor"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'magika armor'

This spell surrounds the caster in a protective caccoon of raw magik,
drastically improving their armor.
]],
  },
  {
    keywords = {"channel"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast channel

By channeling their life force, the caster damages their health in order to
restore mana quickly.
]],
  },
  {
    keywords = {"ethereal cloak"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'ethereal cloak'

By surrounding oneself in the ether of the magical world, the is shielded from
spells, temporarily blocking them.
]],
  },
  {
    keywords = {"mana burn"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'mana burn'

The caster expends some their mana in order to temporarily boost their magical
power.
]],
  },
  {
    keywords = {"enchant treasure"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast 'enchant treasure' <item>

Items of type 'treasure' or 'arttreasure' may be enchanted with this spell,
yielding an addition to hit points and svd. This spell can enchant magical
as well as non-magical items but may not be used to enchant an item that is
already enchanted.
]],
  },
  {
    keywords = {"astral rift"},    
    level = 1,    
    htype = "spell",
    text = [[
LEGENDARY SPELL:

The astral plane generously comes to the aid of those who seek out, learn, and
apply this legendary spell. With the casting of this spell, a blast of pure
energy slices through time and space to damage your opponent with horrifying
results. With the power brought forth, it is no wonder that this spell is
legendary throughout this realm.

This high powered spell costs mana.
]],
    see_also = {"legendary"},
  },
  {
    keywords = {"disenchant"},    
    level = 1,    
    htype = "spell",
    text = [[
Syntax: cast disenchant <item>

If an item has been enchanted and given the anti-good, anti-evil or anti-
neutral flag may be disenchanted. Disenchanting will remove these flags from
such an item.
]],
  },
   
  }
}