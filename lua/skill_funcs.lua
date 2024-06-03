-- functions used in "job" skills

local 	m = {	{	name = "coal", melt = -1, val = 15, cat = 0, wep_val = 0, ac_val = 0,
					desc = { "small lump", "lump", "large lump" }, 
				},
				{	name = "tin", melt = 500, val = 1, cat = 1, wep_val = 3, ac_val = 6,
					desc = { "some flakes of", "some", "a chunk of" }, 
				},
				{	name = "nickle", melt = 3000, val = 2, cat = 1, wep_val = 6, ac_val = 7,
					desc = { "some flakes of", "some", "a large chunk of" }, 
				},
				{	name = "copper", melt = 2000, val = 3, cat = 1, wep_val = 7, ac_val = 8,
					desc = { "some flakes of", "some", "a large chunk of" }, 
				},
				{	name = "iron", melt = 3500, val = 4, cat = 1, wep_val = 8, ac_val = 10,
					desc = { "some shavings of", "a nugget of", "a large nugget of" }, 
				},
				{	name = "silver", melt = 2500, val = 7, cat = 1, wep_val = 7, ac_val = 9,
					desc = { "some flakes of", "a chunk of", "a large chunk of" }, 
				},
				{	name = "gold",	melt = 2000, val = 8, cat = 1, wep_val = 5, ac_val = 5,
					desc = { "some flakes of", "a nugget of", "a large nugget of" }, 
				},
				{	name = "platinum", melt = 3500, val = 9, cat = 1, wep_val = 9, ac_val =12,
					desc = { "a small amount of", "some", "a sizable chunk of" }, 
				},
				{	name = "titanium", melt = 3750, val = 10, cat = 1, wep_val = 10, ac_val = 14,
					desc = { "a small amount of", "some", "a sizable chunk of" }, 
				},
				{	name = "quartz", melt = -1, val = 3, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small piece of uncut", "a piece of uncut", "a large piece of uncut" }, 
				},
				{	name = "amethyst", melt = -1, val = 4, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small uncut piece of", "an uncut piece of", "a large uncut piece of" }, 
				},
				{	name = "sapphire", melt = -1, val = 5, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small piece of uncut", "a piece of uncut", "a large piece of uncut" }, 
				},
				{	name = "ruby", melt = -1, val = 6, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small piece of uncut", "a piece of uncut", "a large piece of uncut" }, 
				},
				{	name = "emerald", melt = -1, val = 7, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small piece of uncut", "a piece of uncut", "a large piece of uncut" }, 
				},
				{	name = "moonstone", melt = -1, val = 8, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small piece of uncut", "a piece of uncut", "a large piece of uncut" }, 
				},
				{	name = "bloodstone", melt = -1, val = 9, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small uncut", "an uncut", "a large uncut" }, 
				},
				{	name = "diamond", melt = -1, val = 10, cat = 2, wep_val = 0, ac_val = 0,
					desc = { "a small uncut", "an uncut", "a large uncut" }, 
				},
			}
			
local 	g = {	{	name = "oak", val = 2, },
				{	name = "pine", val = 1, },
				{	name = "ash", val = 8, },
				{	name = "birch", val =7 , },
				{	name = "hawthorn", val = 3, },
				{	name = "yew", val = 6, },
				{	name = "walnut", val = 8, },
				{	name = "willow", val = 5, },
				{	name = "blackthorn", val = 9, },
				{	name = "elder", val = 10, },
			}

function get_random_mined()

	return math.random(1, #m)

end

function get_random_gathered()
	
	return math.random(1, #g)
	
end

function aoran( what )

    l = string.sub(what, 1, 1)
    vowels = {a = true, e = true, i = true, o = true, u = true}
    
    if vowels[l] then
        return "an"
    else
        return "a"
    end

end

function get_mined_values( which, size )

	what = m[which] or nil
	if what then
		return what.name, what.desc[size], what.cat, what.melt, what.val, what.wep_val, what.ac_val
	else
		return "", "", 0, 0, 0, 0, 0
	end
	-- ssiiiii

end

function get_gathered_values( which )

	what = g[which] or nil
	if what then
		return what.name, what.val
	else
		return "", 0
	end

end

function forge_type_item( tTxt, iTxt )

	forge_item = 	{	treasure = 		{	["ears"] = { item = 13, itype = 1 },
											["neck"] = { item = 14, itype = 1 },
											["wrist"] = { item = 15, itype = 1 },
											["finger"] = { item = 16, itype = 1 },
											["ankle"] = { item = 17, itype = 1 },
										},
						armor = 		{	["head"] = { item = 1, itype = 2 },
											["face"] = { item = 2, itype = 2 },
											["body"] = { item = 3, itype = 2 },
											["arms"] = { item = 4, itype = 2 },
											["hands"] = { item = 5, itype = 2 },
											["about"] = { item = 6, itype = 2 },
											["back"] = { item = 7, itype = 2 },
											["waist"] = { item = 8, itype = 2 },
											["legs"] = { item = 9, itype = 2 },
											["feet"] = { item = 10, itype = 2 },
											["shield"] = { item = 11, itype = 2 },
											["ankle"] = { item = 12, itype = 2 },
										},
						weapon = 		{	["axe"] = { item = 18, itype = 3 },
											["sword"] = { item = 19, itype = 3 },
											["dagger"] = { item = 20, itype = 3 },
											["mace"] = { item = 21, itype = 3 },
											["claw"] = { item = 22, itype = 3 },
										}
					}
					
    t = string.lower(string.match(tTxt, "%a+"))
    i = string.lower(string.match(iTxt, "%a+"))
    i_type = 0
    i_item = 0
    
    if #t < 1 or #i < 1 then
        return i_type, i_item
    end
	
	if forge_item[t] and forge_item[t][i] then
		item = forge_item[t][i]
    
		i_item = item.item or 0
		i_type = item.itype or 0
		
		return tonumber(i_type), tonumber(i_item)
	else
		return i_type, i_item
	end
    
end

function forge_name(i, m)

    local item_keys  =  {   {"helmet %s", "%s helm"},
                            {"%s faceguard"},
                            {"%s plate suit", "%s leafmail suit", "suit %s chain mail"},
                            {"%s sleeves", "%s sleeves", "%s armlets"},
                            {"%s gloves", "%s gaunlets", "%s plated gauntlets"},
                            {"%s sash"},
                            {"%s backguard", "%s backplate"},
                            {"%s girth"},
                            {"%s leggings", "%s legguards"},
                            {"%s boots"},
                            {"%s shield"},
                            {"%s ankleguard"},
                            {"%s earrings"},
                            {"%s necklace", "%s amulet"},
                            {"%s bracelet", "%s wristlet"},
                            {"%s ring"},
                            {"%s anklet"},
                            {"%s axe", "%s dwarven axe", "%s hatchet"},
                            {"%s long sword", "%s sword"},
                            {"small %s dagger", "%s dagger"},
                            {"%s mace"},
                            {"%s claw"}
                        }
    local item_names =  {   {"a helmet of %s", "$a %s helm"},
                            {"%s faceguard"},
                            {"$a %s plate suit", "$a %s leaf-mail suit", "a suit of %s chain mail"},
                            {"some %s sleeves", "a pair of %s sleeves", "%s armlets"},
                            {"%s gloves", "%s gaunlets", "%s plated gauntlets"},
                            {"$a %s sash"},
                            {"$a %s backguard", "$a %s backplate"},
                            {"$a %s girth"},
                            {"%s leggings", "%s legguards"},
                            {"a pair of %s boots"},
                            {"$a %s shield"},
                            {"$a %s ankleguard"},
                            {"a pair of %s earrings"},
                            {"$a %s necklace", "$a %s amulet"},
                            {"$a %s bracelet", "$a %s wristlet"},
                            {"$a %s ring"},
                            {"$a %s anklet"},
                            {"$a %s axe", "$a %s dwarven axe", "$a %s hatchet"},
                            {"$a %s long sword", "$a %s sword"},
                            {"a small %s dagger", "$a %s dagger"},
                            {"$a %s mace"},
                            {"$a %s claw"}
                        }
	
    t = item_keys[i]
    x = math.random(1, #t)
    tt = item_names[i]
    
    item_key = string.format(t[x], m)
    item_name = string.format(string.gsub(tt[x], "$a", aoran(m)), m)
--~     
    return item_key, item_name 
--~ 	return "invalid item number", "invalid item number"

end

function skin_ac( race )

	ac = 1
	
	race_ac = { ["human"] = ac + 1,
				["elf"] = ac + 1,
				["dwarf"] = ac + 3,
				["halfling"] = ac + 1,
				["pixie"] = ac + 1,
				["minotaur"] = ac + 4,
				["half-ogre"] = ac + 5,
				["half-orc"] = ac + 5,
				["half-troll"] = ac + 6,
				["half-elf"] = ac + 1,
				["gith"] = ac + 1,
				["drow"] = ac + 2,
				["sea-elf"] = ac + 1,
				["lizardman"] = ac + 4,
				["gnome"] = ac + 2,
				["ghoul"] = ac + 1,
				["goblin"] = ac + 1,
				["wolfen"] = ac + 4,
				["demon"] = ac + 7,
				["troll"] = ac + 9,
				["ant"] = ac + 1,
				["ape"] = ac + 2,
				["baboon"] = ac + 2,
				["bat"] = ac + 1,
				["bear"] = ac + 3,
				["bee"] = ac + 1,
				["beetle"] = ac + 1,
				["boar"] = ac + 3,
				["bugbear"] = ac + 3,
				["cat"] = ac + 2,
				["dog"] = ac + 2,
				["dragon"] = ac + 12,
				["ferret"] = ac + 2,
				["fly"] = ac + 1,
				["gargoyle"] = ac + 11,
				["gelatin"] = ac + 1,
				["devil"] = ac + 10,
				["gnoll"] = ac + 6,
				["ghost"] = ac + 1,
				["elemental"] = ac + 9,
				["golem"] = ac + 11,
				["mechanical"] = ac + 13,
				["harpy"] = ac + 1,
				["hobgoblin"] = ac + 4,
				["kobold"] = ac + 4,
				["reptile"] = ac + 5,
				["locust"] = ac + 1,
				["lycanthrope"] = ac + 6,
				["wyvern"] = ac + 7,
				["plant"] = ac + 1,
				["bird"] = ac + 2,
				["fish"] = ac + 1,
				["ooze"] = ac + 1,
				["orc"] = ac + 6,
				["rat"] = ac + 1,
				["rustmonster"] = ac + 5,
				["shadow"] = ac + 1,
				["shapeshifter"] = ac + 1,
				["shrew"] = ac + 1,
				["shrieker"] = ac + 1,
				["skeleton"] = ac + 0,
				["slime"] = ac + 1,
				["snake"] = ac + 3,
				["spider"] = ac + 1,
				["giant"] = ac + 7,
				["vampire"] = ac + 1,
				["troglodyte"] = ac + 1,
				["undead"] = ac + 1,
				["wight"] = ac + 1,
				["wolf"] = ac + 3,
				["worm"] = ac + 1,
				["zombie"] = ac + 1,
				["bovine"] = ac + 3,
				["canine"] = ac + 2,
				["feline"] = ac + 2,
				["ogre"] = ac + 9,
				["mammal"] = ac + 1,
				["rodent"] = ac + 1,
				["elderspawn"] = ac + 9,
				["illusion"] = ac + 1,
				["amphibian"] = ac + 1,
				["angel"] = ac + 8,
				["crustacean"] = ac + 3,
				["insect"] = ac + 1,
				["spirit"] = ac + 1,
				["magical"] = ac + 14,
				["horse"] = ac + 3,
				["animal"] = ac + 1,
				["humanoid"] = ac + 1,
				["monster"] = ac + 6,
				["god"] = ac + 14,
		}
		
	return race_ac[race]

end

function tailor_armor( i )

    if i == "head" then
        return 1
    elseif i == "face" then
        return 2
    elseif i == "body" then
        return 3
    elseif i == "arms" then
        return 4
    elseif i == "hands" then
        return 5
    elseif i == "about" then
        return 6
    elseif i == "back" then
        return 7
    elseif i == "waist" then
        return 8
    elseif i == "legs" then
        return 9
    elseif i == "feet" then
        return 10
    elseif i == "ankle" then
        return 11
    else
        return 0
    end
    

end

function tailor_type_item( tTxt, iTxt )

    t = string.lower(tTxt)
    i = string.lower(iTxt)
    i_type = 0
    i_item = 0
    
    if #t < 1 or #i < 1 then
        return i_type, i_item
    end
    
    if t == "container" then 
        i_type = 2
        i_item = 13
    elseif t == "drinkcon" then 
        i_type = 1
        i_item = 12
    elseif t == "armor" then
        i_type = 3
        i_item = tailor_armor(i)
    else
        i_type = 0
    end

    
    return tonumber(i_type), tonumber(i_item)
    
end

function tailor_name(i, m)

    local item_keys  =  {   {"cap %s", "%s hat"},
                            {"%s hide faceguard"},
                            {"%s hide shirt", "%s hide vest", "shirt %s hide"},
                            {"%s hide sleeves", "%s hide sleeves", "%s hide armlets"},
                            {"%s hide gloves"},
                            {"%s hide sash"},
                            {"%s hide backguard"},
                            {"%s hide girth", "%s hide belt"},
                            {"%s hide leggings", "%s hide legguards"},
                            {"%s hide boots", "%s hide shoes"},
                            {"%s hide ankleguard"},
							{"%shide waterskin"},
							{"%s hide bag"}
                        }
    local item_names =  {   {"a cap of %s hide", "$a %s hide hat"},
                            {"$a %s hide faceguard"},
                            {"$a %s hide shirt", "$a %s hide vest", "a shirt of %s hide"},
                            {"some %s hide sleeves", "a pair of %s hide sleeves", "%s hide armlets"},
                            {"%s hide gloves"},
                            {"$a %s hide sash"},
                            {"$a %s hide backguard"},
                            {"$a %s hide girth", "a %s hide belt"},
                            {"%s hide leggings", "%s hide legguards"},
                            {"a pair of %s hide boots", "a pair of %s hide shoes"},
                            {"$a %s hide ankleguard"},
							{"$a %shide waterskin"},
							{"$a %s hide bag"}
                        }

    t = item_keys[i]
    x = math.random(1, #t)
    tt = item_names[i]
    
    item_key = string.format(t[x], m)
    item_name = string.format(string.gsub(tt[x], "$a", aoran(m)), m)
    
    return item_key, item_name 

end

function mine_time( size )
	return 3 * size
end

function tailor_time( typ, itm )

	t = typ
	
	if t == 1 then
		t = 3
	elseif t == 2 then
		t = 7
	elseif t == 3 then
		if 	itm == 3 or 
			itm == 7 or 
			itm == 9 then 
			t = 15
		else
			t = 11
		end
	else
		t = t + 1
	end
	
	return t
	
end

function forge_time( typ, itm )

	t = typ
	
	if t == 1 then -- treasure
		t = 5
	elseif t == 2 then -- armor
			if itm == 3 or
				itm == 7 or
				itm == 9 or
				itm == 11 then
				t = 15
			else
			t = 10
			end
	elseif t == 3 then -- weapon
			t = 20
	else
		t = t + 1
	end
	
	return t

end
