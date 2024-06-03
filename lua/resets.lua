-- Lua reset handling for SMAUG FUSS
--   Written by Nick Gammon
--   15th July 2007

-- See: http://www.gammon.com.au/forum/?id=8027

--     www.gammon.com.au

module (..., package.seeall)

-- debugging displays
SHOW_INVOKED_MOBS = false
SHOW_INVOKED_OBJECTS = false
SHOW_AREA_RESET = false

-- loader for modules to load sub-modules, in the module context
function resets_loader (name)
  setfenv (assert (loadfile (
           string.format (systeminfo.LUA_DIR .. "resets/" .. "%s.lua", name))), _M) ()
end -- resets_loader

resets_loader "drazuni"
resets_loader "bladegrass"
resets_loader "bear"
resets_loader "drazville"
resets_loader "bazabel"
resets_loader "templeofdrazuk"
--- etc.

-- table of areas we know how to reset (filename/function pairs)
available_resets = {
  ["drazuni.are"] = reset_new_academy,
  ["bladegrass.are"] = reset_bladegrass,
  ["bear.are"] = reset_bear,
  ["drazville.are"] = reset_drazville,
  ["bazabel.are"] = reset_bazabel,
  ["templeofdrazuk.are"] = reset_templeofdrazuk,
} -- end of areas we reset
  


-- debugging display to show we have made a mob
function debug_show_mob_invoked (mob, room)
  if SHOW_INVOKED_MOBS then
    print (string.format ("Invoked mob %i (%s) in room %i (%s)", 
            mob, (mud.mob_name (mob)),
            room, (mud.room_name (room))))
  end -- if SHOW_INVOKED_MOBS
end -- debug_show_mob_invoked

-- debugging display to show we have made an object
function debug_show_object_invoked (obj, room)
  if SHOW_INVOKED_OBJECTS then
    print (string.format ("Invoked object %i (%s) in room %i (%s)", 
            obj, (mud.object_name (obj)),
            room, (mud.room_name (room))))
  end -- if SHOW_INVOKED_OBJECTS
end -- debug_show_object_invoked

-- invoke up to 'count' mobs, so we have no more than 'max' mobs in the area
function minv (mob, room, count, max, ...)
  local current = mud.mobinworld (mob, room) or 0  -- present count 
  local most = (max or 1) - current           -- how many we can have
  
  -- invoke the lot of them
  for i = 1, math.min ((count or 1), most) do
    debug_show_mob_invoked (mob, room)
    mud.minvoke (mob, room, ...)
  end -- invoking each one
  
end -- minv

-- invoke so we have 'count' objects in the nominated room
function oinv (obj, room, count)
  local current = mud.objinroom (obj, room) or 0  -- present count 
  local needed = (count or 1) - current                  -- how many we need
  
  -- invoke the lot of them
  for i = 1, needed do
    debug_show_object_invoked (obj, room)
    mud.obj_to_room (room, obj)  -- note different argument order
  end -- invoking each one
  
end -- oinv

-- put a mob in each room in room_list
function multiple_mobs (vnum, room_list, ...)
  for k, v in ipairs (room_list) do
     minv (vnum, v, ...)
  end -- for
end -- multiple_mobs

-- put an object in each room in room_list
function multiple_objects (vnum, room_list)
  for k, v in ipairs (room_list) do
     oinv (vnum, v)
  end -- for
end -- multiple_objects

-- called from reset.c to reset an area - argument is area file name
function reset_area (name)
  
  local f = available_resets [name]
  
  if f then
  
    if SHOW_AREA_RESET then
      mud.msg_game ("Lua - resetting area " .. name, at.reset)
      print ("Doing Lua reset of area", name)
    end -- if debug display
    
    f ()  -- call function to reset area
    return true  -- handled it
  end -- area found
   
  return false
  
end -- reset_area
