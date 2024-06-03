-- ---------------------------------------------------------------------------
-- Skill awarding tasks
-- ---------------------------------------------------------------------------
local is_magic = { 	mage = true, 		cleric = true, 		druid = true, 		diabolist = true, 
					conjurer = true, 	shaman = true, 		archmagi = true, 	bishop = true,
					thief = false, 		warrior = false, 	thug = false, 		ranger = false,
					monk = false, 		jester = false, 	champion = false, 	rogue = false }
-- if is_magic[string.lower(char.class())] then
all_tasks.gather = {
  name = "Learn: Gather",
  description = [[
Ranger Richard will teach you how to gather wood in forested areas.
]],
  giver = 21050,
  receiver = 21050,
  min_level = 1,
  max_level = 50,
  time_limit = 15,
  flags = {"no_info"},
  
  available = function ()
	return not char.has_skill_percent("gather", 1)
    end,
  accept = function ()
    send([[
&WRanger Richard tells you 'I can teach you how to collect wood from the forests.
You may think that this is some simple task, but if it was, why can you not
already do it? I'll tell you what, if you can collect a few items for me, I'll 
teach you the first step to gathering wood, but you must do it quickly!'&D

&WType '&Ytask show gather&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      send ([[
&WRanger Richard tells you 'Ah, thank you! Now then, to gather wood the first 
part would be to get in the forest. Once you are in a forested area, all you 
need to do is type the command &YGATHER&W. It may take a few tries at first, 
but you will get better the more you use it. Many of the shopkeeps will pay 
you for your hard work gathering wood.'
]])
      char.sset( "gather", 1)
      end, 

 subtasks = {  
      {  
      description = "Give Ranger Richard a sharp stick",
      item = 1004,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21050 },
      complete = function ()
      send([[
&WRanger Richard tells you 'This sharp stick is good for poking the beggars
in front of my shop, but not much else. It's certainly not good for building
any fires. I thank you for it none-the-less.'
]])
      end,
      },
      {
      description = "Give Ranger Richard a small yew branch",
      item = 1616,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21050 },
      complete = function ()
      send([[
&WRanger Richard tells you 'Yes, a branch would make a good fire, not by itself,
mind you. You would need many more of these to make a nice fire. I, however, like
to make bows out of these.'
]])
      end,
      },
      {
      description = "Give Ranger Richard a seadragon scale pack",
      item = 1715,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21050 },
      complete = function ()
      send([[
&WRanger Richard tells you 'Thanks much. This seadragon pack is much larger than
my beltpouches and will help me move more of my things from place to place.'
]])
      end,
      },
      },
} -- end gather

all_tasks.ignite = {
  name = "Learn: Ignite",
  description = [[
Ranger Richard will teach you how to ignite gathered wood.
]],
  giver = 21050,
  receiver = 21050,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
    return char.has_skill_percent("gather", 5) and not char.has_skill_percent("ignite", 1)
    end,
  accept = function ()
    send([[
&WRanger Richard tells you 'Fire? Why, yes, that &wwould&W be nice. Oh! You
don't know how to make a fire? Well, then, I can show you the trick.
Quickly, bring me some wood and we'll get started!'

&WType '&Ytask show ignite&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      send ([[
&WRanger Richard tells you 'Yes, these will do nicely. Now that we have our wood,
we can now use the &YIGNITE&W skill to create a small fire. A fire can be
useful for several things. The temperature of the fire may be important for
some things so you may want to EXAMINE the fire from time to time.  The
temperature of the fire will decrease as the fire burns unless you add more
wood by using the &YSTOKE&W command. You may also want to know that since
these fires generate smoke, you may not create one while indoors.'
]])
      char.sset( "ignite", 1)
      end, 

 subtasks = {  
      {  
      description = "Give Ranger Richard a 'log' of wood",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21050 },
      complete = function ()
      send([[
&WRanger Richard tells you 'A log is a very large and heavy piece of wood
gathered from a forested area. You can use it with the &YIGNITE&W skill
to create a fire.'
]])
      end,
      item = 72
      },
      {
      description = "Give Ranger Richard a 'branch' of wood",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21050 },
      complete = function ()
      send([[
&WRanger Richard tells you 'A branch is a good piece of wood. It's not overly
large or heavy and can be used with the &YIGNITE&W skill to create a fire.'
]])
      end,
      item = 71
      },
      {
      description = "Give Ranger Richard some 'sticks and twigs'",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21050 },
      complete = function ()
      send([[
&WRanger Richard tells you 'Sticks and twigs are small scraps of wood gathered
from forested areas. Sticks and twigs can be used with the &YIGNITE&W skill
to start a fire, but it won't burn long unless you add more wood.'
]])
      end,
      item = 70
      },
      },
} -- end ignite

all_tasks.skin = {

  name = "Learn: Skin",

  description = [[
Ranger Richard will teach you how to skin corpses.
]],

  giver = 21050,
  receiver = 21050,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function () 
	return not char.has_skill_percent("skin", 1)
   end,
  
  accept = function ()
    send([[
&WRanger Richard tells you 'The corpses of monsters and other creatures that
you kill in your adventures have more purposes than just littering the ground
and carrying treasures. It is possible to take the hides from these corpses.
If you can quickly complete this task for me, I can teach you the skill needed
to obtain the hides from corpses.'

&WType '&Ytask show skin&W' for details on what to collect.
]])    
    end,
  
  abandon = function ()
    end,

  complete = function ()
      send ([[
&WRanger Richard tells you 'Ah, ready to learn, are you? Well then, there is
but one thing you must do to obtain a hide from a corpse and that is to &YSKIN&W it.
Once you skin the corpse, the corpse will be destroyed. Anything that was in 
the corpse at the time will fall to the ground. The skins will be useful later on
when you will be able to make clothing out of them. In the mean time, you should
practice skinning corpses so that you may improve your skill.'
]])
      char.sset("skin", 1)
      end,
      
 subtasks = {

     {
     description = "Give Ranger Richard a pair of yeti skin boots",
     type = "give",
     flags = {"destroy_item"},
     vnums = { 21050 }, 
	 complete = function ()
      send([[
&WRanger Richard tells you 'Ah, very good. It gets cold in here sometimes
and these yeti skin boots will do well to keep my feet warm.'
]])
      end,
	  item = 10502
     },
  
     },
}   -- end skin
all_tasks.tan = {
  name = "Learn: Tan",
  description = [[
Ranger Richard will teach you how to tan skins.
]],
  giver = 21050,
  receiver = 21050,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
    return char.has_skill_percent("skin", 5) and not char.has_skill_percent("tan", 1)
    end,
  accept = function ()
    send([[
&WRanger Richard tells you 'To make your own clothes and armors there are some
steps you will have to first take. The first step, you have already done, which
is to lean how to obtain skins. The next step involves learning how to tan the
skins to make a suitable hide for crafting new items.'

&WType '&Ytask show tan&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      function x ()
	  send ([[
&WRanger Richard tells you 'The tanning processes takes a while to complete.
You must tan the skins several times before they are ready to be made into
any kind of clothing or armor. Once you get a skin, simply &YTAN skin&W until
it becomes a piece of tanned hide.'
]])
pause(2)
send([[
&WRanger Richard tells you 'Once you are more experienced in tanning, you
will be able to learn how to taylor some items from the hides you make.
]])
      char.sset( "tan", 1)
	  end
	  wait.make(x)
      end, 

 subtasks = {  
      {  
      description = "Give Ranger Richard 5 fresh skins",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21050 },
      complete = function ()
      send([[
&WRanger Richard tells you 'Ah, thank you. My own supply has been running a
bit low since I'm not able to get out much these days.'
]])
      end,
      item = 23,
	  count = 5,
      },
      },
} -- end tan

all_tasks.mine = {
  name = "Learn: Mine",
  description = [[
Samuel will teach you how to mine for ores and gems.
]],
  giver = 21081,
  receiver = 21081,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
	return not char.has_skill_percent("mine", 1)
    end,
  accept = function ()
    send([[
&WSamuel tells you 'Before I began repairing armor I had to first learn how to
obtain the materials to do the repairing with. These come in the form of raw
ores from underground and from within the mountains. If you will collect a few
items for me and bring them back, I will teach you what you will need to know.
I'm a busy man, so hurry. I haven't got all day, you know.'

&WType '&Ytask show mine&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      wait.make( function ()
	  send ([[
&WSamuel tells you 'Now that you've returned with all the items I requested,
you must listen carefully. In order to mine anything valuable from the earth
you must first be in a location suitable for mining. These areas will be
underground or in the mountains. Once you begin mining, it is possible that
you will mine all the valuables from that spot. If that happens, you will
notice that you keep coming up empty handed.'
]])
pause(2)
send([[
&WSamuel tells you 'There are a variety of things you will uncover once you
begin mining an area. First, there is coal. Coal isn't very good for anything
except burning. Coal is very good at creating very hot fires very fast and
is therefore good for when you want to smelt ores.'
]])
pause(2)
send([[
&WSamuel tells you 'Secondly, there are the ores. These raw ores will need to
be smelted into slabs before you can make use of them. Smelting requires there
to be a very hot fire by you.'
]])
pause(2)
send([[
&WSamuel tells you 'And lastly there are the gems. These gems, as I've said
before, will need to be cut and polished or crushed into a powder before they
are of any use. You will be able to decorate equipment you make with these
gems. The powers, on the other hand, are used in magical concoctions.'
]])
	  end)
      char.sset( "mine", 1)
      end, 

 subtasks = {  
      {  
      description = "Give Samuel a small, glittery gem",
      item = 1523,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21081 },
      complete = function ()
      send([[
&WSamuel tells you 'Gems like these are often used for decorations in some
armors, weapons and trinkets. However, the gems that you can mine yourself
are far more valuable than this.'
]])
      end,
      },
      {
      description = "Give Samuel a red ruby",
      item = 1203,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21081 },
      complete = function ()
      send([[
&WSamuel tells you 'This ruby is like the kind you can mine yourself. There
is a difference, however, in that the ones that you can mine yourself will
be rough and will need to be cut and polished before they can be used. You
can also find other uses for them by crushing them into a fine powder.'
]])
      end,
      },
      {
      description = "Give Samuel a mining pick",
      item = 1202,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21081 },
      complete = function ()
      send([[
&WSamuel tells you 'Mining picks are tools used by many miners. You might think
that this kind of tool is necessary to efficiently mine the earth, but it's
not required for the technique I will teach you. You will be just as effective
using your hands or your weapons as you would using a mining pick.'
]])
      end,
      },
      },
} -- end mine
all_tasks.smelt = {
  name = "Learn: Smelt",
  description = [[
Samuel will teach you how to smelt raw materials.
]],
  giver = 21081,
  receiver = 21081,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
    return char.has_skill_percent("mine", 5) and not char.has_skill_percent("smelt", 1)
    end,
  accept = function ()
    send([[
&cSamuel scuffles around his shop for a bit before noticing you standing there.
&WSamuel tells you 'Oh! I was just looking for some more materials to repair
these pieces of armor. It seems I've let myself run a little low on supplies.
If you can bring me some more ore before my customer comes back to pick up his
armor, I'll teach you a little trade skill.'

&WType '&Ytask show smelt&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      wait.make( function ()
	  send ([[
&WSamuel tells you 'The smelting processes requires that you have built a fire
hot enough to melt the ores into a solid slab of material. You will be informed
if the fire is not hot enough for the ore you are trying to smelt. If it's not
hot enough, you should stoke the fire with more wood or coal.'
]])
pause(2)
send([[
&WSamuel tells you 'Once you are more experienced in smelting, you will be able
to learn how to forge some items from the slabs you make.
]])
      char.sset( "smelt", 1)
	  end)
      end, 

 subtasks = {  
      {  
      description = "Give Samuel 5 mined ores",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21081 },
      complete = function ()
      wait.make( function ()
	  send([[
&WSamuel tells you 'Ah, you're just in time. Give me just a moment and I'll get
back to you.'
]])
pause(1)
send([[
&cSamuel quickly takes the ore and smelts a few slabs of it, cooling it rapidly.
&cSamuel makes it look so easy.
]])
pause(1)
send("&cSamuel works on the armor a bit more with the fresh slabs.&D")
pause(1)
send("&GA stranger arrives from the west.&D")
pause(1)
send("&cSamuel hands over a piece of armor to the stranger and shakes his hand.&D")
send("&GA stranger leaves west.&D")
end)
      end,
      item = 73,
	  count = 5,
      },
      },
} -- end smelt

all_tasks.forge = {
  name = "Learn: Forge",
  description = [[
Samuel will teach you how to forge new equipment.
]],
  giver = 21081,
  receiver = 21081,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
    return char.has_skill_percent("smelt", 5) and not char.has_skill_percent("forge", 1)
    end,
  accept = function ()
    send([[
&WSamuel tells you 'Ah, you seem sufficiantly experienced in smelting now.
I suppose you want to learn how to turn these slabs of metal into new armors
and weapons then, huh? I'll tell you what, my shop is running low on slabs.
If you can quickly bring me a few slabs I'll share my trade secret with you.'

&WType '&Ytask show forge&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
	  send ([[
&WSamuel tells you 'Oh, yes... the trade secret. Now then, the first thing you
must do is build a fire. The fire can't be too hot or you may end up melting
your slab. The trick is to make the fire hot enough to heat the slab so that
you can shape it. There is a different heat range for each metal.'

Read the help file to see a list of the various items you can now forge.'
]])
      char.sset("forge", 1)
      char.command("help forge")
      end, 

 subtasks = {  
      {  
      description = "Give Samuel 10 slabs of material",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21081 },
      complete = function ()
send([[
&WSamuel tells you 'Ah, many thanks, honorable adventurer. These will aid me
in repairing etched equipment for those battling dragons.'
]])
      end,
      item = 76,
	  count = 10,
      },
      },
} -- end forge

all_tasks.tailor = {
  name = "Learn: Tailor",
  description = [[
Joseph the Tailor will teach you how to tailor new equipment.
]],
  giver = 21049,
  receiver = 21049,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
    return char.has_skill_percent("tan", 5) and not char.has_skill_percent("tailor", 1)
    end,
  accept = function ()
    wait.make( function ()
send([[
&WJoseph the Tailor tells you 'I know my stock of items is very limited and
doesn't have a large variety of styles to choose from. That is because I no
longer have time to go out and gather my own skins to tan and must rely on
young adventurers such as yourself to bring me some new materials. I remember
this one time in the Elder Forest...'
]])
pause(1)
send([[
&WJoseph the Tailor tells you 'Oh, right. Sorry. The look on your face tells
me your not interested in stories of my past adventures but rather in my
talents of tailoring. Very well. As I said before, I must rely on young
adventurers for new materials, and I am a bit low on new stock. So, if you
can bring me some new skins, I will share my skills with you.'

&WType '&Ytask show tailor&W' for details on what to collect.
]])
end)
    end,
    abandon = function ()
      end,

    complete = function ()
	  send ([[
&WJoseph the Tailor tells you 'Tailoring isn't as easy as you might think. It
has taken me years to master the skill. It is very likely that you will destroy
many hides before you make your first creation. Do not get discouraged, you
will get better in time. Now then, the first thing you need is a tanned hide
to work with. There are a few types of things you can make with these hides.
Drink containers are the smallest and you may make two or more from one hide.
Everything else will consume the entire hide. Above all, be patient.'

Read the help file to see a list of the various items you can now tailor'
]])
      char.sset("tailor", 1)
      char.command("help tailor")
      end, 

 subtasks = {  
      {  
      description = "Give Joseph the Tailor 10 fresh skins",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21049 },
      complete = function ()
send([[
&WJoseph the Tailor tells you 'These will certainly spice up my inventory a
bit. This should be plenty to keep me busy for a couple of weeks at least.'
]])
      end,
      item = 23,
	  count = 10,
      },
      },
} -- end tailor

all_tasks.butcher = {
  name = "Learn: Butcher",
  description = [[
Ranger Richard will teach you how to butcher meat from corpses.
]],

  giver = 21050,
  receiver = 21050,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function () 
	return char.has_skill_percent("skin", 10) and not char.has_skill_percent("butcher", 1)
   end,
  
  accept = function ()
    send([[
&WRanger Richard tells you 'The corpses of monsters and other creatures that
you kill in your adventures have more purposes than just littering the ground
and carrying treasures. Young adventurers often get hungry while out exporing
and experiencing the realm and it isn't always possible to carry an adiquate
amount of food with them. I always say you should eat what you kill.'

&WType '&Ytask show butcher&W' for details on what to collect.
]])    
    end,
  
  abandon = function ()
    end,

  complete = function ()
      send ([[
&WRanger Richard tells you 'Butchering a corpse is similar to skinning a corpse.
Just like skinning, once you butcher a corpse you have destroyed the corpse. In
this case, however, you are able to get a nice chunk of meat that you can eat
when you start feeling a bit hungry. It takes time to master this skill, but it
is not a very difficult one.'
]])
      char.sset("butcher", 1)
      end,
      
 subtasks = {

     {
     description = "Give Ranger Richard 20 corpses",
     type = "give",
     flags = {"destroy_item"},
     vnums = { 21050 }, 
	 complete = function ()
      send([[
&WRanger Richard tells you 'I'll have to get these to Joyce soon. I'm sure she
will make something delicious with them.'
]])
      end,
	  item = 10,
	  count = 20,
     },
  
     },
}   -- end butcher
all_tasks.disenchant = {
  name = "Learn: Disenchant",
  description = [[
Kar'tanth will teach you how to remove alignment enchants.
]],
  giver = 21008,
  receiver = 21008,
  min_level = 1,
  max_level = 50,
  time_limit = 15,
  flags = {"no_info"},
  
  available = function ()
	return is_magic[string.lower(char.class())] or is_magic[string.lower(char.dualclass())]
    end,
  accept = function ()
    send([[
&WKar'tanth tells you 'Adventurers, like yourself, have asked me many times, 
over the years, to help them &Rremove&W enchantments. A feat of magic such as
that takes some time to master and is not something I would just &wgive&W away.'&D
]])
send([[
&WKar'tanth tells you 'There is a lesser magic similar in nature that I would
be willing to teach you to use... if you can obtain some items for me.'&D

&WType '&Ytask show disenchant&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      send ([[
&WKar'tanth tells you 'As I promised, I will teach you the spell &YDISENCHANT&W.
This spell can only remove specific enchantments upon an item and only if that
enchantment was placed on the item after its creation. Disenchant will remove the
alignment-specific enchantments, allowing the removal of anti-evil, anti-good and
anti-neutral flags from an enchanted item.'
]])
send([[
&WKar'tanth tells you 'To use this spell, you simply type &Yc disenchant <item>&W
This spell will also improve with use.'
]])
      char.sset( "disenchant", 20)
      end, 

 subtasks = {  
      {  
      description = "Give Kar'tanth some diamond dust",
      item = 21452,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21008 },
      complete = function ()
      send([[
&cKar'tanth's eyes get wide.
&WKar'tanth tells you 'Diamond dust! A most vital component to many spells.'
]])
      end,
      },
      {
      description = "Give Kar'tanth some ruby powder",
      item = 21454,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21008 },
      complete = function ()
      send([[
&cKar'tanth eyes the ruby powder intensely.
&WKar'tanth tells you 'Ruby powder! A necessary component to many of my fire spells.'
]])
      end,
      },
      {
      description = "Give Kar'tanth some emerald shards",
      item = 21460,
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21008 },
      complete = function ()
      send([[
&cKar'tanth snatches the emerald shards from your hands.
&WKar'tanth tells you 'Emerald shards! These fragments give life to spells!'
]])
      end,
      },
      },
} -- end disenchant

