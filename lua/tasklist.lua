-- tasklist.lua
--[[

All tasks in the task system
----------------------------

Author: Nick Gammon
Date:   6th July 2007

See:  http://www.gammon.com.au/forum/?id=8014  (task file definition)
      http://www.gammon.com.au/forum/?id=8013  (example session)

This is a table of all tasks in the system, keyed by alphanumeric task id.

WARNING! Task ids must be lower case, as we force player input into lower case

Fields:

  name - Summary to show in task list (keep to below about 50 characters) (required)
  
  description - Multiple line description of task purpose.
  
  giver - vnum of task giver mob (required)
  
  receiver - vnum of task to receive the task hand-in
             if omitted, task accepted by task-giver
             
  min_level - minimum level you need to be to see this task
              if omitted, no minimum level
  
  max_level - maximum level you can be to see this task
              if omitted, no maximum level
              
  available - function that returns false if task is not available
              if omitted, task is always available
              you could test for completion of earlier tasks, player class, etc.
              
  accept - function called when task is accepted
           if omitted, nothing special is done   
           returns false if task can not be accepted
           (might return false if you need to put something in inventory, and it is full)          

  complete - function called when task is completed (finished / handed in)
            if omitted, nothing special is done             
            returns false if task can not be finished
            (might return false if you need to put something in inventory, and it is full)          

  abandon - function called when task is abandoned
            if omitted, nothing special is done             
            (might remove task items from inventory)
            
  time_limit - time limit in minutes - task must be completed in that time (real time)
            if omitted, no time limit             
            
  subtasks - table of subtasks which need to be completed - see below
             if omitted, there are no subtasks, and task can be handed in immediately
             subtasks are keyed by number and are shown in order
             
SUBTASKS table item fields
--------------------------

     description - sub task description (keep reasonably short - probably 50 characters max)
                   Task listing shows stuff like: 
                       Buy some bread: 1/1 (Completed)
                   Thus there needs to be room for a couple of leading spaces,
                   counts (eg. 20/30) and the word "(Completed)"
                   
     type - type of subtask
     
     * killmob - must kill 'count' mobs in vnums table
     * visitroom - must visit one of the rooms in the vnums table
     * bribe - must bribe one of the mobs in the vnums table 'count' coins
     * give - must give 'count' objects of vnum 'item' to one of the mobs in the vnums table
     * get      - must get 'count' objects of vnum 'item' (into inventory)
     * buy      - must buy 'count' objects of vnum 'item' 
     * wear     - must wear 'count' objects of vnum 'item' 
     * drop     - must drop 'count' objects of vnum 'item' 
     * repair   - must repair 'count' objects of vnum 'item' 
     * use      - must use 'count' objects of vnum 'item'
     * possess  - must have 'count' objects of vnum 'item' in inventory
             
     count - number of items to get/buy/drop etc., count of mobs to kill, size of bribe
             if omitted, defaults to 1
             
     vnums - table of vnums of mobs (turned into vnum lookup table)
             
     item - vnum of item to get/buy/drop etc. (required, where applicable)
     
     complete - function that is called when this subtask is completed
                if omitted, nothing special is done
                
     Note: 'get' counts when you obtain the item, even if you subsequently lose it.
           'possess' counts possession of the item, giving it away before handing in will fail the subtask. "Possess" items are destroyed on task completion.
           
     
--]]


all_tasks.university1 = {

  -- name of task - shown in task list
  name = "Find teacher Agape",

  -- description - shown when you do "task show x"
  description = [[
&WHeadmaster Eganrac wants you to visit Agape in The Laboratory of 
Skills and Spells.
]],

  giver = 10399,    -- vnum of task giver: Headmaster Eganrac
  
  receiver = 10340, -- vnum of task receiver: Agape
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 10,    -- maximum level to attain task

  flags = {"no_info"},
  
  time_limit = nil,  -- time limit in minutes
  
  -- is task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
  send([[
&WHeadmaster Eganrac tells you 'Please give this note to Agape ('&Ygive note Agape&W').
To find him, go &YN&Worth and then &YE&Wast. If you have become lost, 
type '&Ywhereis skills&W' to get directions to him.
He will reward you with some experience points and gold coins.'
]])
    task_item (36)  -- a note
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      task_xp (40)
      -- task_item (10308)  -- a plate of armour
      task_gold (250)
      send ("&WAgape tells you:")
      hyphens ()
      send ([[
To see what is in your inventory: &Yinven&W
  (or just type '&Yi&W')
To see how much gold you have:    &Ygold&W
You can see what you are wearing: &Yequip&W
]])
      hyphens ()
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks
 
     {  -- subtask 1
     description = "Give note to Agape",
     type = "give",
     flags = {"destroy_item"},
     vnums = { 10340 }, 
     item = 36
     },  -- end subtask

     },   -- end subtasks table

   }   -- end of task university1      
     


all_tasks.university2 = {

 -- name of task - shown in task list
  name = "Visit the Headmaster",

  -- description - shown when you do "task show x"
  description = [[
Agape would like you to return to Headmaster Eganrac. He will have
a task for you to test your fighting skills. As a reward you will
receive a weapon suitable for starting a fight.

]],

  giver = 10340,    -- vnum of task giver: Agape
  
  receiver = 10399, -- vnum of task receiver: Headmaster Eganrac
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 10,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      item_vnum = {
        mage = 10312,   -- dagger
        cleric = 10315, -- mace
        thief = 10312,  -- dagger
        warrior = 10313, -- sword
        thug = 10315,  -- mace
        druid = 10315,  -- mace
        ranger = 10313, -- sword
        monk = 10312,-- dagger
        diabolist = 10313, -- sword
        conjurer = 10313, -- sword
        jester = 10313, -- sword
        shaman = 5056, -- hammer
        }
        
      task_xp (45)
      
      task_item (item_vnum [string.lower (mud.class ())] or 10312)  -- appropriate weapon
      task_gold (300)
      send ("&WHeadmaster Eganrac tells you 'Don't forget to wear your new item'\n")
      send ("&WHeadmaster Eganrac tells you 'Once you have done that, I have another task for you.'\n")
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

     },   -- end subtasks table

   }   -- end of task university2      
     
   


all_tasks.university3 = {

 -- name of task - shown in task list
  name = "The Automaton must die!",

  -- description - shown when you do "task show x"
  description = [[
Headmaster Eganrac would like you to head north, and find the Automaton
to kill. Return once it is slain.

]],

  giver = 10399,    -- vnum of task giver:  Headmaster Eganrac
  
  -- receiver = 10399, -- vnum of task receiver: Headmaster Eganrac
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 10,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   return completed_tasks.university2 ~= nil
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      task_xp (50)
      task_item (10311)  -- an eye of enlightenment
      task_gold (500)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

    {  -- subtask 1
     description = "Automaton slain",
     type = "killmob",
     vnums = { 10345 }, 
     },  -- end subtask
 
     },   -- end subtasks table

   }   -- end of task university3      
     


all_tasks.university4 = {

 -- name of task - shown in task list
  name = "Getting your hands dirty",

  -- description - shown when you do "task show x"
  description = [[
Headmaster Eganrac would like you to head for the battlegrounds, and
kill 4 wolves, 3 naga and 2 carrion crawlers.

Your reward for doing this is 1000 gold.

]],

  giver = 10399,    -- vnum of task giver:  Headmaster Eganrac
  
  -- receiver = 10399, -- vnum of task receiver: Headmaster Eganrac
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 10,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   return completed_tasks.university3 ~= nil
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      task_xp (1000)
      task_gold (1000)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

     {  -- subtask 1
     description = "Naga slain",
     type = "killmob",
     vnums = { 10302 }, 
     count = 3,
     },  -- end subtask
  
    {  -- subtask 2
     description = "Wolf slain",
     type = "killmob",
     vnums = { 10300 }, 
     count = 4,
     },  -- end subtask
 
      {  -- subtask 3
     description = "Carrior crawler slain",
     type = "killmob",
     vnums = { 10303 }, 
     count = 2,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task university4      
     
   
 
all_tasks.university5 = {

 -- name of task - shown in task list
  name = "Find some food",

  -- description - shown when you do "task show x"
  description = [[
Headmaster Eganrac would like you to go up and east to buy some
meat to eat for sustenance during your adventures.
]],

  giver = 10399,    -- vnum of task giver:  Headmaster Eganrac
  
  receiver = 21003, -- vnum of task receiver: Kallista
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 10,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
send([[
&WHeadmaster Eganrac tells you 'Although it may be a while before you get
hungry, it is a wise idea to carry some food with you at all times. There
are many things that are beneficial to you if you eat them. Please find
Phooey and purchase some dried rabbit meat from him. You can find him in
the University Supply Store.
]])
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      task_xp (200)
      -- task_item (10314)
      task_gold (200)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

    {  -- subtask 1
     description = "Meat purchased",
     type = "buy",
     item = 10317,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task university5      
     

all_tasks.university6 = {

 -- name of task - shown in task list
  name = "Bring me bread",

  -- description - shown when you do "task show x"
  description = [[
Headmaster Eganrac would like you to find 3 loaves of bread and bring
them to him.
]],

  giver = 10399,    -- vnum of task giver:  Headmaster Eganrac
  
  receiver = 10399, -- vnum of task receiver: Headmaster Eganrac
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 10,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    send ([[
&WHeadmaster Eganrac tells you 'Food, though rarely used these days, may play a
vital role in your survival. It is important that you know where to locate food
just in case you find yourself in a situation where you need it.'
Headmaster Eganrac tells you 'You will need to venture UP into Alden and use
the &Ywhereis &Wcommand to find the bar where the bread is sold. Buy three
loaves of bread and bring them back to me.'
]])
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      send ("&WHeadmaster Eganrac tells you 'Very good, young adventurer! Here is your reward.'")
      task_xp (1000)
      task_gold (200)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

    {  -- subtask 1
     description = "Bread obtained",
     type = "possess",
     flags = {"no_destroy"},
     item = 21085,
     count = 3,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task university6


-- ---------------------------------------------------------------------------
-- Alden tasks
-- ---------------------------------------------------------------------------
all_tasks.richard1 = {

 -- name of task - shown in task list
  name = "Kill the beggars",

  -- description - shown when you do "task show x"
  description = [[
Ranger Richard is tired of the beggars sitting outside of his
shop and asks that you slay 3 as a demonstration of his dislike
for beggars. Return to Ranger Richard to collect your reward.
]],

  giver = 21050,    -- vnum of task giver:  Ranger Richard
  
  receiver = 21050, -- vnum of task receiver: Ranger Richard
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    send ([[
&WRanger Richard tells you 'Those beggars! They're always sitting outside my
shop begging my customers for money. They're bad for business I tell ya.'
Ranger Richard tells you 'Hey... I'll give you a little something for "relocating"
a few of them, if you know what I mean.'
]])
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      task_xp (1000)
      task_gold (200)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

     {  -- subtask 1
     description = "Beggars slain",
     type = "killmob",
     vnums = { 21057, 21056, 21055 }, 
     count = 3,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task richard1

all_tasks.lilyan1 = {

 -- name of task - shown in task list
  name = "Animal control",

  -- description - shown when you do "task show x"
  description = [[
Lilyan has a hard enough time trying to concentrate when
recharging items without the likes of these mangy mutts
coming in her shop with their fleas and barking. Assert
some animal control and kill 4 mangy mutts. Return to
Lilyan to collect your reward.
]],

  giver = 21082,    -- vnum of task giver:  Lilyan
  
  receiver = 21082, -- vnum of task receiver: Lilyan
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
send ([[
&cLilyan groans loudly as she shoos another mutt out of her shop.
&WLilyan tells you 'I don't know what to do any more. These mutts have
invaded my shop and I can't concentrate with all their barking. Could
you please help me?'
]])
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
send ([[
&WLilyan tells you 'Peace! Finally. Perhaps now I can get this wand recharged.
Thank you. I offer you this as guesture of my appreciation.'
]])
      task_xp (1000)
      task_gold (200)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

     {  -- subtask 1
     description = "Mutts slain",
     type = "killmob",
     vnums = { 21027, 21028 }, 
     count = 4,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task lilyan1

all_tasks.lilyan2 = {

  name = "Pest control",

  description = [[
It seems that mangy mutts aren't all that's breaking Lilyan's
concentration these days.
]],

  giver = 21082,
  receiver = 21082,
  
  min_level = 1,
  max_level = 50,
  
  time_limit = nil,
  
  available = function () 
    if completed_tasks.lilyan1 ~= nil and completed_tasks.lilyan1 + 300 > os.time() then
        return true
    else
        return false
    end
   end,
  
  accept = function ()
  send ([[
&WLilyan tells you 'Oh, thank the Gods you're here. These animals are
driving me insane. I can't concentrate on anything long enough to get
anything recharged. Some of the other adventurers are getting tired of
waiting for their staves and wands to be replenished. Please! You've
got to help me!'
]])
    end,
  
  abandon = function ()
    end,  -- end accept

  complete = function ()
  send ([[
&WLilyan tells you 'Finally, some peace and quiet. No more barking. No more
squeeking. No more scratching. Thank you, oh so much. Now I can finally get back
to work. Take this as thanks for your help.'
]])
      task_xp (1500)
      task_gold (500)
      task_qp (150)
      end, -- complete function
      
 
 subtasks = {  -- table of sub tasks

     {
     description = "Mangy Mutts slain",
     type = "killmob",
     vnums = { 21027, 21028 }, 
     count = 4,
     },
     {
     description = "Scruffy Dogs slain",
     type = "killmob",
     vnums = { 21026, 21025 },
     count = 4,
     },
     {
     description = "Dirty Rats slain",
     type = "killmob",
     vnums = { 21051, 21052, 21053, 21054 },
     count = 8,
     },
  
     },   -- end subtasks table

   }   -- end of task lilyan2

all_tasks.sturm1 = {

 -- name of task - shown in task list
  name = "De-comissioning the guards",

  -- description - shown when you do "task show x"
  description = [[
Sturm's profession calls for him to avoid the Alden
athorities whenever possible. Killing off about a dozen
should help Sturm make his way around a little easier.
]],

  giver = 21085,    -- vnum of task giver:  Sturm
  
  receiver = 21085, -- vnum of task receiver: 21085
  
  min_level = 15,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
	send ("&WSturm tells you 'Thanks, mate. You won't regret this.'\n")
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      task_xp (2000)
      task_gold (1000)
      task_qp (100)
      send ("&WSturm tells you 'I hope this made it worth your troubles.'\n")
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

     {  -- subtask 1
     description = "Cityguards relieved of duty",
     type = "killmob",
     vnums = { 21024, 21023, 21022, 21021, 21020, 21019, 21018, 21017,
               21016, 21015, 21014, 21013, 21012, 21011, 21010, 21009 }, 
     count = 12,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task sturm1

all_tasks.jerald1 = {

 -- name of task - shown in task list
  name = "Bring me water",

  -- description - shown when you do "task show x"
  description = [[
Jerald the Pitboy slaves over the donation pit all day long.
He's never allowed to leave the room and spends long hours
without food or water. He's really parched at the moment and
would love to have a sip of water.
]],

  giver = 21001,    -- vnum of task giver:  Jerald the Pitboy
  
  receiver = 21001, -- vnum of task receiver: Jerald the Pitboy
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
send([[
&WJerald the Pitboy tells you 'I'm simply DYING of thirst! You MUST help me!
Joyce the Barmistress keeps some water on tap in The Nightgaunt's Tickler, the
bar to the north. Please! Bring me a waterskin. I'll reward you with what
little I have.
]])
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      send ("&WJerald the Pitboy tells you 'Oh, thank the Gods! You're too kind.'")
      task_xp (1000)
      task_gold (300)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

    {  -- subtask 1
     description = "Give waterskin to Jerald",
     type = "give",
     flags = {"destroy_item"},
     vnums = { 21001 },
     item = 21079,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task jerald1

all_tasks.kallista1 = {

 -- name of task - shown in task list
  name = "Tour the City",

  -- description - shown when you do "task show x"
  description = [[
Kallista would like you to get to know the city a little better.
In order to do that, she has some locations she would like you
to visit. Once you have visited all the locations return to
Kallista to recieve your reward.
]],

  giver = 21003,    -- vnum of task giver:  Jerald the Pitboy
  
  receiver = 21003, -- vnum of task receiver: Jerald the Pitboy
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      send ("&WKallista tells you 'I hope this gives you a better understanding of the city.'")
      send ("&WKallista tells you 'This should help get you on your way to achieving great glory at House of Ghouls'")
      task_xp (2000)
      task_gold (1000)
      task_qp (200)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

    {  -- subtask 1
     description = "Visit the Donation Room",
     type = "visitroom",
     vnums = { 21007 },
    },  -- end subtask
    {
     description = "Visit the Chairs",
     type = "visitroom",
     vnums = { 21009 },
    },
    {
     description = "Visit Ranger Richard",
     type = "visitroom",
     vnums = { 21126 },
    },
    {
     description = "Visit the Broker",
     type = "visitroom",
     vnums = { 21127 },
    },
    {
     description = "Visit the bar",
     type = "visitroom",
     vnums = { 21139 },
    },
    {
     description = "Visit the transportal",
     type = "visitroom",
     vnums = { 21162 },
    },
    {
     description = "Visit the North entrance",
     type = "visitroom",
     vnums = { 21017 },
    },
    {
     description = "Visit the West entrance",
     type = "visitroom",
     vnums = { 21037 },
    },
    {
     description = "Visit the Questmaster",
     type = "visitroom",
     vnums = { 21118 },
    },
    {
     description = "Visit the Bank",
     type = "visitroom",
     vnums = { 21119 },
    },
    {
     description = "Visit the South entrance",
     type = "visitroom",
     vnums = { 21025 },
    },
    {
     description = "Visit the Artificer",
     type = "visitroom",
     vnums = { 21154 },
    },
    {
     description = "Visit the East entrance",
     type = "visitroom",
     vnums = { 21031 },
    },
    {
     description = "Visit the Sorcerer",
     type = "visitroom",
     vnums = { 21123 },
    },

  
     },   -- end subtasks table

   }   -- end of task kallista1

all_tasks.kallista2 = {

  name = "Window Shopping",

  description = [[
&WKallista likes shopping. Unfortunatly she doesn't have much money
most of the time and being the healer of the temple, she doesn't
have much free time to go on a shopping spree. Visit the town's
shops and return to Kallista with news of what was in stock.
Use the &Ywhereis&W command to help you find your way around.
  ]],

  giver = 21003,
  receiver = 21003,
  
  min_level = 1,
  max_level = 50,
  
  time_limit = nil,
  
  available = function () 
   return completed_tasks.kallista1 ~= nil
   end,
  
  accept = function ()
    send ([[
&WKallista tells you 'Wonderful! I was so hoping you would accept this small
task for me. You see, I'm planning for a special day... eventually, though, I can't
leave the temple and abandon my duties here. So, if you could visit these shops for
me, perhaps I could figure out what it is I should get.'
    ]])
    end,
  
  abandon = function ()
    end,

  complete = function ()
      send ([[
Kallista tells you 'Oh, what wonderful news! It is a shame that I cannot leave to buy
anything yet. I do wish I had time, if just to buy a new pair of shoes.'
      ]])
      task_xp (2000)
      task_gold (1000)
      task_qp (100)
      end, -- complete function
      
 subtasks = {  -- table of sub tasks

    {  -- subtask 1
     description = "&WGarth's Armor Emporium - &Ywhereis armor&W",
     type = "visitroom",
     vnums = { 21122 },
    },  -- end subtask
    {
     description = "&WThe Grand Artificer - &Ywhereis artificer&W",
     type = "visitroom",
     vnums = { 21154 },
    },
    {
     description = "&WOutdoor Outfitters - &Ywhereis leathers&W",
     type = "visitroom",
     vnums = { 21126 },
    },
    {
     description = "&WMistress Leah's Fashions - &Ywhereis fashions&W",
     type = "visitroom",
     vnums = { 21124 },
    },
    {
     description = "&WThe Sorcerer Store - &Ywhereis magic shop&W",
     type = "visitroom",
     vnums = { 21123 },
    },
    {
     description = "&WSamuels Repairshop - &Ywhereis repair shop&W",
     type = "visitroom",
     vnums = { 21143 },
    },
    {
     description = "&WThe Refined Warrior - &Ywhereis taylor&W",
     type = "visitroom",
     vnums = { 21125 },
    },
    {
     description = "&WLilyans Recharging - &Ywhereis recharge shop&W",
     type = "visitroom",
     vnums = { 21145 },
    },
    {
     description = "&WKhent's Weapon Shack - &Ywhereis weapons&W",
     type = "visitroom",
     vnums = { 21120 },
    },
  
     },

   }   -- end of task kallista2
 local guild_vnum = { mage = 21130, cleric = 21131, thief = 21132, warrior = 21128, thug = 21141, druid = 21133,
                     ranger = 21129, monk = 21142, diabolist = 21153, conjurer = 21161, jester = 21158,
                     shaman = 21160, archmagi = 21130, bishop = 21131, champion = 21128, rogue = 21132 }
 local is_magic = { mage = true, cleric = true, druid = true, diabolist = true, conjurer = true, shaman = true,
                   archmagi = true, bishop = true, thief = false, warrior = false, thug = false, ranger = false,
                   monk = false, jester = false, champion = false, rogue = false }
 local magic_text = [[
&WIn this room is where you will usually go to practice your new skills
as they become available to you from leveling. There are several factors
that determine how well you learn new skills. One of them is your 
intellegence. Intelligence is very important for a magic user. In some
cases, a high intelligence increases your spell power. You may also come 
here to request a speciallized quest for magic users via the &Ymquest&W
command. Completing these quests will earn you magic points that will
lead to increasing your magical damage. With enough magic points your name
will be added to a ranking of top magic questors. You can see this ranking
by using the &Yscoremp&W command.
]]

 local skill_text = [[
&WIn this room is where you will usually go to practice your new skills
as they become available to you from leveling. There are several factors
that determine how well you learn new skills. One of them is your 
intelligence. You may also come here to request a speciallized quest for
fighters via the &Ysquest&W command. Completing these quests will earn you
skill points that will lead to increasing your physical damage. With enough
skill points your name will be added to a ranking of top skill questors. 
You can see this ranking by using the &Yscoresp&W command.
]]

all_tasks.kallista3 = {
name = "Finding Your Guild",
description = [[
&WPraticing your skills and doing quests are important parts
of daily life at House of Ghouls.
]],

  giver = 21003,
  receiver = 21003,
  
  min_level = 1,
  max_level = 50, 
  
  time_limit = nil,
  
  available = function ()  -- return completed_tasks.TASK ~= nil
   end,
  
  accept = function ()
    end,
  
  abandon = function ()
    end,

  complete = function ()
send([[
&cKallista looks surprised at your return.
&WKallista tells you 'Back so soon? Well, I hope you're finding everything you need.
Remember that doing quests at your guild masters will help you increase your powers.'&D
]])
		task_xp(200)
      end,

                   
 subtasks = {
	     { -- begin subtask

	     description = "Find the Guild for " .. mud.class(),
	     type = "visitroom",
	     vnums = {guild_vnum [string.lower (mud.class ())]},
	     complete = function()
	     hyphens()
	     if is_magic[string.lower(mud.class())] then
	     	send (magic_text)
	     else
	     	send (skill_text)
	     end
	     hyphens()
	        end,
	     }, --end subtask
	     { -- begin subtask
	     description = "Find the Guild for " .. mud.dualclass(),
	     type = "visitroom", -- must visit one of the rooms in the vnums table
	     vnums = {guild_vnum [string.lower (mud.dualclass ())]},
	     complete = function() -- can use for removing given items
	     hyphens()
	     if is_magic[string.lower(mud.class())] then
	     	send (magic_text)
	     else
	     	send (skill_text)
	     end
	     hyphens()
	        end,
	     }, --end subtask

     },   -- end subtasks table

      
} -- end kallista3
   
all_tasks.grimwald1 = {

 -- name of task - shown in task list
  name = "Bring me a corpse",

  -- description - shown when you do "task show x"
  description = [[
Grimwald has been down on his luck lately and business has
been slow. So much so in fact that he's just aching to bury
SOMETHING. If you bring him a corpse he will surely reward
you well.
]],

  giver = 21096,    -- vnum of task giver:  Grimwald the Undertaker
  
  receiver = 21096, -- vnum of task receiver: Grimwald the Undertaker
  
  min_level = 1,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    send([[
&WGrimwald tells you 'I tells ya, I thinks the gods have cursed me again. I've
not had any work in ages. I'll tell ya what, if you can bring me a corpse of
some wild critter or somethin, I'll see whats I can do ta reward ye.'
]])    
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      send ("&WGrimwald tells you 'Ah, finally! I've got somethin ta bury. Thank ye!'\n")
      task_xp (900)
      task_gold (200)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

     {  -- subtask 1
     description = "Give a corpse to Grimwald",
     type = "give",
     flags = {"destroy_item"},
     vnums = { 21096 }, 
     item = 10
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task grimwald1

all_tasks.grimwald2 = {
  name = "Animating the dead",

  description = [[
Life as an undertake can be lonely most of the time. Most of the
people you know are dead and burried. In magical planes, things
don't always stay dead and undertakers with too much time on their
hands have a nasty habit of experimentations.
]],

  giver = 21096,
  receiver = 21096,

  min_level = 1,
  max_level = 50,

  time_limit = nil,

  available = function ()
    return completed_tasks.grimwald1 ~= nil
    end,
  
  accept = function ()
    send ([[
&WGrimwald tells you 'Experiments with the dead, or even parts of the dead, isn't safe.
You mustn't let anyone know of my plans. It may upset the balance of things. But I am
lonely and dead are the only ones I know how to live with. If this works, I will never
be lonely again! I will need several severed body parts to complete my experiment. Here
is the list...'
&W   Type &Y'task show grimwald2'&W to see the list of items required for this task.
]])
    end,
  
  abandon = function ()
    end,

  complete = function ()
    send ([[
&WGrimwald tells you 'Excellent! With these parts, I may create the best friend man
has ever seen, and I'm not talkin' 'bout a dog here. Thank you for your assistance.
Take this as compensation for your troubles.'
]])
    task_xp (1000)
    task_gold (1000)
    end,

  subtasks = {

    {
      description = "Give a severed head to Grimwald",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21096 },
      item = 12,
    },
    {
      description = "Give a torn-out heart to Grimwald",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21096 },
      item = 13,
    },
    {
      description = "Give a sliced-off arm to Grimwald",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21096 },
      item = 14,
    },
    {
      description = "Give a sliced off leg to Grimwald",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21096 },
      item = 15,
    },
    {
      description = "Give a torn-out brain to Grimwald",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 21096 },
      item = 44,
    },
    {
      description = "Give a pair of eyes to Grimwald",
      type = "give",
      flags = {"destroy_item"},
      count = 2,
      vnums = { 21096 },
      item = 49,
    },

  },

  } -- end task grimwald2
all_tasks.sturm2 = {

 -- name of task - shown in task list
  name = "Become the hunter",

  -- description - shown when you do "task show x"
  description = [[
It seems Sturm has angered someone in a powerful position and
have sent masked hunters after him. Surely, if someone could
kill three masked hunters for him, he would be most gracious
and rewarding.
]],

  giver = 21085,    -- vnum of task giver:  Sturm
  
  receiver = 21085, -- vnum of task receiver: 21085
  
  min_level = 45,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = nil,  -- time limit in minutes
  
  -- it task available? (check prerequisites, class, etc.)
  available = function ()
   return completed_tasks.sturm1 ~= nil
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
	send ("&WSturm tells you 'Thanks, mate. I owe ya one.'\n")
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      task_xp (2000)
      task_gold (3000)
      task_qp (450)
      send ("&WSturm tells you 'I hope this made it worth your troubles.'\n")
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks

     {  -- subtask 1
     description = "Hunters hunted down",
     type = "killmob",
     vnums = { 21073, 21074, 21075, 21076, 21077, 21078, 21079, 21080 }, 
     count = 3,
     },  -- end subtask
  
     },   -- end subtasks table

   }   -- end of task sturm2
-- ---------------------------------------------------------------------------
-- Bee tasks
-- ---------------------------------------------------------------------------
all_tasks.bee1 = {

  -- name of task - shown in task list
  name = "Bee on the lookout",

  -- description - shown when you do "task show x"
  description = [[
The warrior bee may have spotted trouble heading towards the hive.
Take a note to the queen so that she may be informed and alert the
others of dangers that may be approaching.
]],

  giver = 659,    -- vnum of task giver: Warrior bee
  
  receiver = 10999, -- vnum of task receiver: Queen Bee
  
  min_level = 5,    -- minimum level to attain task
  
  max_level = 50,    -- maximum level to attain task
  
  time_limit = 60,  -- time limit in minutes
  
  -- is task available? (check prerequisites, class, etc.)
  available = function () 
   end,
  
    -- do stuff for accepting (like put things in inventory)
  accept = function ()
    send ([[
&WA warrior bee tells you 'I have an important message that must find its way to the Queen.'
A warrior bee tells you 'I beg of you to take this note so that the Queen may be informed.'
A warrior bee tells you 'Quickly! You must hurry! There is no time to waste!'
    ]])
    task_item (36)  -- a note
    end,  -- end accept
  
  -- do stuff for abandoning (like removing task items)
  abandon = function ()
    end,  -- end accept

  -- do stuff for completing (like task rewards)
  complete = function ()
      send ([[
&WThe Queen reads over the note.
The Queen tells you 'Oh dear. This does not sound good at all. I must inform the others at once.'
The Queen tells you 'Thank you for delivering this message to me.'
]])
      task_xp (550)
      task_gold (3000)
      task_qp (300)
      end, -- complete function
      
 -- table of subtasks 
 -- each subtask is its own table
 -- required fields: description / type
 
 subtasks = {  -- table of sub tasks
 
     {  -- subtask 1
     description = "Deliver message to the Queen Bee",
     type = "give",
     flags = {"destroy_item"},
     vnums = { 10999 }, 
     item = 36
     },  -- end subtask

     },   -- end subtasks table

   }   -- end of task bee1      

-- ---------------------------------------------------------------------------
-- Ant tasks
-- ---------------------------------------------------------------------------

-- ---------------------------------------------------------------------------
-- Mermen tasks
-- ---------------------------------------------------------------------------
all_tasks.merman1 = {
    name = "King for a day",
    
    description = [[
Oh what a lowly life it is for a merman of the lake. If only he could
feel powerful, even if only for a day. Maybe the Sea-Elf king's coral
crown and mithril trident would cheer him up.
]],

    giver = 5130,
    receiver = 5130,

    min_level = 40,
    max_level = 50,

    time_limit = nil,

    available = function () 
      end,

    accept = function ()
      send ([[
&WA merman tells you 'These are sad times for merfolk. We have no real realm of
our own. We are limited by this rather small lake with nothing to do and noone
to rule over. The birds and butterflies mock us. If only we had some true symbols
of power.'
A merman tells you 'I've heard a story or two about a powerful king of the sea
folk. Perhaps, if you could bring back symbols of his power... Yes! That may
brighten our mood.'
]])
      end,

    abandon = function ()
      end,

    complete = function ()
      send ([[
&WA merman tells you 'Powerful you are and powerful we will look. My thanks go out to you,
noble adventurer!'
]])
      task_xp (750)
      task_gold (3500)
      task_qp (150)
      end, 

 subtasks = {  
      {  
        description = "Kill the Sea-Elf King",
        type = "killmob",
        vnums = { 1708 }, 
      }, 
      {
        description = "Obtain the coral crown",
	type = "get",
	item = 1722,
      },
      {
        description = "Obtain the mithril trident",
        type = "get",
	item = 1724,
      },
      {
        description = "Deliver the crown",
	type = "give",
    flags = {"destroy_item"},
	item = 1722,
	vnums = { 5130 },
      },
      {
        description = "Deliver the trident",
	type = "give",
    flags = {"destroy_item"},
	item = 1724,
	vnums = { 5130 },
      },

    },   -- end subtasks table

} -- end of task merman1

-- ---------------------------------------------------------------------------
-- Bazabel tasks
-- ---------------------------------------------------------------------------
-- Karlof> for a 25-35 level task, you might have Lady Nygen be angry with 
-- the vendors in bazabel and want them all killed.
all_tasks.general1 = {
name = "Corporal Punishment",
description = [[
The General is upset that so many soldiers have decided to go off-duty
at a time like this. He wants his soldiers to be disciplined, harshly.
]],
giver = 6118,
receiver = 6118,

min_level = 25,
max_level = 50,

time_limit = nil,

available = function () end,
accept = function ()
send ([[
&WThe General tells you 'Boys! They're all boys! Plain and simple. They're children, I
tell you! I thought I had trained these soldiers better than this. This is no time to
be "off-duty."'
The General tells you 'I'll tell you what. You find all the lazy, off-duty soldiers you
can find and hand them their tail for me. I'll have something for you when you're done.'
]]) 
end,
abandon = function () end,
complete = function ()
send ([[
&WThe General tells you 'Nice work. I wish I had you in my ranks. Here's that little
something I told you about...'
]])
task_xp (1500)
task_gold (2000)
task_qp (300)
end,

subtasks = {
 {
 description = "Soldiers disciplined",
 type = "killmob",
 vnums = { 6100, 6101, 6102, 6104, 6105, 6106, 6107 },
 count = 7,
 },
 }
} -- end general1

-- ---------------------------------------------------------------------------
-- Templar academy tasks
-- ---------------------------------------------------------------------------
all_tasks.valhun1 = {
  name = "A spy among us",
  description = [[
Captain Valhun has been alerted by some cadets that something just isn't
right around the academy. They suspect someone is snooping around the grounds.
]],

    giver = 8044,
    receiver = 8044,

    min_level = 35,
    max_level = 50,

    time_limit = nil,

    available = function () 
      end,

    accept = function ()
      send ([[
&WCaptain Valhun tells you 'Some of the cadets are a little suspicious of
some "activities" they've seen around here. They think a Zanzen spy may
be lurking in the halls somewhere. If you find one, kill him!'
]])
      end,

    abandon = function ()
      end,

    complete = function ()
      send ([[
&WCaptain Valhun tells you 'Good work! Maybe Zanzen will think twice about
sticking his nose where it doesn't belong. Let's hope that sends a clear
enough message back to him.'
]])
      task_xp (1300)
      task_gold (1500)
      end, 

 subtasks = {  
      {  
      description = "Zanzen spy slain",
      type = "killmob",
      vnums = { 8041 },
      count = 1,
      },
      },
} -- end valhun1

all_tasks.valhun2 = {
  name = "Alert the others",
  description = [[
The recent incident with the Zanzen spy has made it clear that the
Alden army must be informed of the happenings at the academy.
]],

    giver = 8044,
    receiver = 8044,

    min_level = 35,
    max_level = 50,

    time_limit = nil,

    available = function () 
    return completed_tasks.valhun1 ~= nil
      end,

    accept = function ()
      send ([[
&WCaptain Valhun tells you 'General Thadius must be informed. Take this note
and deliver it to him. Pray that he can spare a few soldiers.'
]])
	task_item (36)
      end,

    abandon = function ()
      end,

    complete = function ()
      send ([[
&cGeneral Thadius looks over the note.
&WGeneral Thadius tells you 'This is interesting. I wonder what Zanzen would want
with the templar academy. No matter, I'll dispatch a few of my soldiers to stand
guard at the academy at once. I hope they will not arrive too late.'
]])
      task_xp (500)
      task_gold (500)
      end, 

 subtasks = {  
      {  
      description = "Deliver message to General Thadius",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 4631 },
      count = 1,
      item = 36,
      },
      },
} -- end valhun2

-- ---------------------------------------------------------------------------
-- Last Stand tasks (usually given by General Thadius - 4631)
-- ---------------------------------------------------------------------------
all_tasks.thadius1 = {
  name = "Thinning the ranks",
  description = [[
General Thadius requires your assistance to thin the ranks of
the Zanzen Raiders.
]],

    giver = 4631,
    receiver = 4631,

    min_level = 45,
    max_level = 50,

    time_limit = nil,

    available = function () 
      end,

    accept = function ()
      send ([[
&WGeneral Thadius tells you 'It's not like me to request help from outside of our
own army, but times are harsh these days and the battle is harsher still. Our
sources tell me that if we were able to eliminate a few more raiders, we may be
able to gain some ground. I leave this task to you. Good luck, soldier!'
]])
      end,

    abandon = function ()
      end,

    complete = function ()
      send ([[
&WGeneral Thadius tells you 'You must have been sent by the Gods! It's a miracle
you were not slain. My soldiers and I thank you!'
]])
      task_xp (2500)
      task_gold (4000)
      task_qp (500)
      end, 

 subtasks = {  
      {  
      description = "Zanzen Raiders slain",
      type = "killmob",
      vnums = { 4616, 4617, 4618, 4619, 4620 },
      count = 3,
      },
      },
} -- end thadius1

all_tasks.thadius2 = {
  name = "Gaining Ground",
  description = [[
General Thadius has received intel that Zanzen combatwizards have entered the fray.
You must assist him and his soldiers in their elimination.
]],

    giver = 4631,
    receiver = 4631,

    min_level = 45,
    max_level = 50,

    time_limit = nil,

    available = function () 
    return completed_tasks.thadius1 ~= nil
      end,

    accept = function ()
      send ([[
&WGeneral Thadius tells you 'Zanzen has unleased a group of combatwizards into the battle.
We are taking quite a beating from these monsterous magi. Defeating them would surely allow
us to advance on the battlefield.'
]])
      end,

    abandon = function ()
      end,

    complete = function ()
      send ([[
&WGeneral Thadius tells you 'I've been informed of your success. Congratulations, soldier!
It is hard to tell at this point whether or not we have actually gained any ground. The
battle is fierce. I have no doubt, however, that we have achieved a great victory today.'
]])
      task_xp (3000)
      task_gold (4000)
      task_qp (1000)
      end, 

 subtasks = {  
      {  
      description = "Zanzen combatwizards slain",
      type = "killmob",
      vnums = { 4624, 4625, 4626 },
      count = 5,
      },
      },
} -- end thadius2

-- ---------------------------------------------------------------------------
-- Underhill tasks
-- ---------------------------------------------------------------------------
all_tasks.tomkins1 = {
  name = "Underhill Patrol Duty",
  description = [[
Shiriff Tomkins is worried about visitors and residents of Underhill. He's been
notified that there are bandits on the Southern Road and leading up to Underhill.
]],
  giver = 421,
  receiver = 421,
  min_level = 20,
  max_level = 50,
  time_limit = nil,
  
  available = function ()
    end,
  accept = function ()
    send([[
&WShiriff Tomkins tells you 'I'm a bit worried about the safety of the Underhill
residents and the visitors alike. You see, there have been bandits walking the
Southern Road and I fear they may come into Underhill and cause havok. I hope you
can do a good service for us, brave adventurer. Please, seek out the bandits and
send them a message that their kind is not welcomed here.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      send ([[
&WShiriff Tomkins tells you 'I and the residents of Underhill thank you, brave
adventurer. We hope you will come to our aid again if ever we shall need it.'
]])
      task_gold (500)
      task_qp (100)
      end, 

 subtasks = {  
      {  
      description = "Dirty bandits slain",
      type = "killmob",
      vnums = { 204, 209, 210, 211 },
      count = 4,
      },
      },
} -- end tomkins1

-- ---------------------------------------------------------------------------
-- Hermit tasks (Ben hermit Vnum: 1339)
-- ---------------------------------------------------------------------------
all_tasks.ben1 = {
  name = "Learn: Gather",
  description = [[
The hermit, Old Ben, will teach you how to gather wood in forested areas.
]],
  giver = 1339,
  receiver = 1339,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
    end,
  accept = function ()
    send([[
&WOld Ben tells you 'I can teach you how to collect wood from the forests.
You may think that this is some simple task, but if it was, why are you
asking me how to do it? I'll tell you what, if you can collect a few items
for me, I'll teach you the first step to gathering wood, but you must do it
quickly!'&D

&WType '&Ytask show ben1&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      send ([[
&WOld Ben tells you 'Ah, thank you! Now then, to gather wood the first part
would be to get in the forest. Once you are in a forested area, all you need
to do is type the command &YGATHER&W. It may take a few tries at first, but
you will get better the more you use it. Many of the shopkeeps will pay you
for your hard work gathering wood.'
]])
      mud.sset( "gather", 1)
      end, 

 subtasks = {  
      {  
      description = "Give Ben a crude pot",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 1339 },
      complete = function ()
      send([[
&WOld Ben tells you 'My last pot was stolen by a band of thieves while
I was out one day. It'll be nice to be able to eat in again.'
]])
      end,
      item = 1524
      },
      {
      description = "Give Ben a carving knife",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 1339 },
      complete = function ()
      send([[
&WOld Ben tells you 'My last knife was broken in a fight with a band of
thieves that were trying to steal from me. Unfortunately, they got away.'
]])
      end,
      item = 16030
      },
      {
      description = "Give Ben a bowl of stew",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 1339 },
      complete = function ()
      send([[
&WOld Ben tells you 'My last bowl of soup was lost while fighting off a
band of thieves. I kicked the bowl during the scuffle and it broke.'
]])
      end,
      item = 411
      },
      },
} -- end ben1

all_tasks.ben2 = {
  name = "Learn: Ignite",
  description = [[
The hermit, Old Ben, will teach you how to ignite gathered wood.
]],
  giver = 1339,
  receiver = 1339,
  min_level = 1,
  max_level = 50,
  time_limit = 10,
  flags = {"no_info"},
  
  available = function ()
    return completed_tasks.ben1 ~= nil
    end,
  accept = function ()
    send([[
&WOld Ben tells you 'Fire? Why, yes, that &wwould&W be nice. Oh! You
don't know how to make a fire? Well, then, I can show you the trick.
Quickly, bring me some wood and we'll get started!'

&WType '&Ytask show ben2&W' for details on what to collect.
]])
    end,
    abandon = function ()
      end,

    complete = function ()
      send ([[
&WOld Ben tells you 'Yes, these will do nicely. Now that we have our wood,
we can now use the &YIGNITE&W skill to create a small fire. A fire can be
useful for several things. The temperature of the fire may be important for
some things so you may want to EXAMINE the fire from time to time.  The
temperature of the fire will decrease as the fire burns unless you add more
wood by using the &YSTOKE&W command. You may also want to know that since
these fires generate smoke, you may not create one while indoors.'
]])
      mud.sset( "ignite", 1)
      end, 

 subtasks = {  
      {  
      description = "Give Ben a 'log' of wood",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 1339 },
      complete = function ()
      send([[
&WOld Ben tells you 'A log is a very large and heavy piece of wood
gathered from a forested area. You can use it with the &YIGNITE&W skill
to create a fire.'
]])
      end,
      item = 72
      },
      {
      description = "Give Ben a 'branch' of wood",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 1339 },
      complete = function ()
      send([[
&WOld Ben tells you 'A branch is a good piece of wood. It's not overly
large or heavy and can be used with the &YIGNITE&W skill to create a fire.'
]])
      end,
      item = 71
      },
      {
      description = "Give Ben some 'sticks and twigs'",
      type = "give",
      flags = {"destroy_item"},
      vnums = { 1339 },
      complete = function ()
      send([[
&WOld Ben tells you 'Sticks and twigs are small scraps of wood gathered
from forested areas. Sticks and twigs can be used with the &YIGNITE&W skill
to start a fire, but it won't burn long unless you add more wood.'
]])
      end,
      item = 70
      },
      },
} -- end ben2
