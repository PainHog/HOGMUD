ATTACK_TYPE = {}
attack_types = {
  "ATCK_BITE", "ATCK_CLAWS", "ATCK_TAIL", "ATCK_STING", "ATCK_PUNCH", "ATCK_KICK",
  "ATCK_TRIP", "ATCK_BASH", "ATCK_STUN", "ATCK_GOUGE", "ATCK_BACKSTAB",
  "ATCK_DRAIN",  "ATCK_FIREBREATH", "ATCK_FROSTBREATH", "ATCK_ACIDBREATH",
  "ATCK_LIGHTNBREATH", "ATCK_GASBREATH", "ATCK_POISON", "ATCK_UNUSED1", "ATCK_UNUSED2",
  "ATCK_BLINDNESS", "ATCK_CAUSESERIOUS", "ATCK_EARTHQUAKE", "ATCK_CAUSECRITICAL",
  "ATCK_CURSE", "ATCK_FLAMESTRIKE", "ATCK_HARM", "ATCK_FIREBALL", "ATCK_COLORSPRAY",
  "ATCK_WEAKEN", "ATCK_SPIRALBLAST", "ATCK_AMBUSH", "MAX_ATTACK_TYPE"
}

for _,v in ipairs(attack_types) do
   ATTACK_TYPE[string.lower(string.gsub(v, "ATCK_", ""))] = _
end

-- randoms.lua

attrib_types = { APPLY_STR, APPLY_DEX, APPLY_DEX, APPLY_INT, APPLY_INT, APPLY_INT, APPLY_WIS, APPLY_WIS,
      APPLY_WIS, APPLY_CON, APPLY_CON, APPLY_CON, APPLY_LCK, APPLY_LCK, APPLY_LCK, APPLY_CHA, APPLY_CHA, APPLY_CHA, 
      APPLY_HITROLL, APPLY_DAMROLL, APPLY_SPELLDAM }
      
power_types = { APPLY_MANA, APPLY_MANA, APPLY_MANA, APPLY_HIT, APPLY_HIT, APPLY_MOVE, APPLY_MOVE }

save_types = { APPLY_SAVING_SPELL, APPLY_SAVING_SPELL, APPLY_SAVING_BREATH, APPLY_SAVING_BREATH, 
      APPLY_SAVING_PARA, APPLY_SAVING_DAMAGE }

attrib_mods = { 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5 }
power_mods = { 10, 10, 20, 20, 20, 20, 20, 30, 30, 30, 30, 40, 50 }
save_mods = { -5, -4, -4, -3, -3, -3, -2, -2, -2, -2, -2, -1, -1 }

function random_get_loc_mod( iType )
  
  if iType == 1 or iType == 3 then
    aLoc = math.random(0, #attrib_types-1)
    aMod = math.random(0, #attrib_mods-1)
  end
  if iType == 2 then
    aLoc = math.random(0, #power_types-1)
    aMod = math.random(0, #power_mods-1)
  end
  if iType == 4 then
    aLoc  = math.random(0, #save_types-1)
    aMod = math.random(0, #save_mods-1)
  end
  
  return aLoc, aMod
end
