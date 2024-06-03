-- whereis_destinations.lua


--[[

Whereis module - table of known locations
-----------------------------------------

Author: Nick Gammon
Date:   8th July 2007

This file consists of one table: known_destinations

Inside are sub-tables, one for each "zone" that you want to give directions
around (eg. Darkhaven).

Each zone is given a first_room / last_room pair.

If the player is inside that range (inclusive) then the destinations listed 
in available_dests are available to them.

If they are outside all ranges then they cannot use "whereis" in that place.

The examples below are a long list for Darkhaven, and to illustrate the idea of
a secondary set of directions, a shorter one for Redferne's residence.

There is no limit to the number of zones you can incorporate in this way.

They are searched sequentially, so if you want to have a smaller subzone inside 
a main zone, put the subzone further up the list.

--]]

known_destinations = { 
{ -- Alden University
  first_room = 10300,
  last_room = 10499,

  available_dests = {
     headmaster = 10300,
     languages = 10306,
     skills = 10303,
     healer = 10319,
     battleground = 10368,
     fountain = 10300,
     supplies = 10357,
  } -- end available_dests
}, -- end Draz-uni

{ -- Alden
  first_room = 21001,
  last_room = 21500,

  available_dests = {
     pit = 21007,
     healer = 21001,
     notes = 21001,
     chairs = 21009,
     ["the book"] = 21005,
     bank = 21119,
     questmaster = 21118,
     weapons = 21120,
     bribe = 21121,
     broker = 21127,
     leathers = 21126,
     ["repair shop"] = 21143,
     ["recharge shop"] = 21145,
     ["magic shop"] = 21123,
     armor = 21122,
     taylor = 21125,
     fashions = 21124,
     ["the bar"] = 21139,
     lockers = 21171,
     transportal = 21162,
     ["ranger guild"] = 21129,
     ["warrior guild"] = 21128,
     ["shaman guild"] = 21160,
     ["conjurer guild"] = 21161,
     ["mage guild"] = 21130,
     ["cleric guild"] = 21131,
     ["jester guild"] = 21158,
     ["thug guild"] = 21141,
     ["monk guild"] = 21142,
     ["diabolist guild"] = 21153,
     ["thief guild"] = 21132,
     ["druid guild"] = 21133,
     artificer = 21154,
     ["pet shop"] = 21184,
  } -- end available_dests

} -- end Alden


}  -- end of all known_destinations
   