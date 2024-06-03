-- randoms.lua
function rnd_stat( t1, t2 )
	mt.srand({os.time(), math.random(os.time()), os.time() + math.random(100)})
	return t1[math.floor(mt.rand() * #t2) + 1]
end

function random_get_art_loc_mod( iType)

    local attrib_types = 	{ 	apply.str,	    apply.str, 
                                apply.dex,	    apply.dex, 
                                apply.int,	    apply.int,	apply.int, 
                                apply.wis,	    apply.wis,	apply.wis, 
                                apply.con,	    apply.con,	apply.con, 
                                apply.lck,	    apply.lck,	apply.lck,	apply.lck,
                                apply.cha,	    apply.cha,	apply.cha, 
                                apply.hr,	    apply.hr,	apply.hr,
                                apply.dr,	    apply.dr, 
                                apply.spelldam,	apply.spelldam,
                            }
          
    local power_types = 	{ 	apply.mana,	apply.mana,	apply.mana, 
                                apply.hp,	apply.hp,	apply.hp,				
                                apply.move,	apply.move,
                            }

    local save_types = 	{ 	apply.svs,	apply.svs,	apply.svs, 
                            apply.svb,	apply.svb,
                            apply.svp,	apply.svp, 
                            apply.svd,
                        }
	
	local affect_mods =	{	affby.iceshield,
							affby.fireshield,
							affby.shockshield,
							affby.imp_invis,
							affby.invis,affby.invis,
							affby.det_hidden,affby.det_hidden,
							affby.det_invis,affby.det_invis,affby.det_invis,
							affby.det_magic,affby.det_magic,affby.det_magic,affby.det_magic,
							affby.det_evil,affby.det_evil,affby.det_evil,affby.det_evil,
							affby.det_good,affby.det_good,affby.det_good,affby.det_good,
							affby.corrupt,
							affby.protect,
							affby.balanced,
							affby.flying,affby.flying,affby.flying,
							affby.floating,affby.floating,affby.floating,
							affby.pass_door,affby.pass_door,
							affby.truesight,
							affby.scrying,
							affby.aqua_breath,
							affby.tongues,affby.tongues,affby.tongues,
							affby.camo,
							affby.demonsight,
							affby.det_traps,
							affby.infrared,affby.infrared,affby.infrared,
							affby.sanctuary,
						}
								

    local attrib_mods = { 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5, 6 }
    local attrib_mod = {}
    for _,v in ipairs(attrib_mods) do
        attrib_mod[_] = v
    end

    local power_mods = { 5, 10, 10, 15, 15, 20, 20, 20, 20, 25, 30, 30, 30, 30, 35, 40, 45, 50 }
    local power_mod = {}
    for _,v in ipairs(power_mods) do
        power_mod[_] = v
    end

    local save_mods = { -6, -5, -4, -4, -3, -3, -3, -2, -2, -2, -2, -2, -1, -1 }
    local save_mod = {}
    for _,v in ipairs(save_mods) do
        save_mod[_] = v
    end
	
	local affect_mod = {}
	for _,v in ipairs(affect_mods) do
		affect_mod[_] = v
	end

	local seed = os.time()
	mt.srand({os.time(), math.random(os.time()), os.time() + math.random(100)})
	
	iType = math.floor (mt.rand () * 4) + 1 
    if iType == 1 or iType == 3 then
        aLoc = rnd_stat(attrib_types, attrib_types)
        aMod = rnd_stat(attrib_mod, attrib_mods)
    end
    if iType == 2 then
        aLoc = rnd_stat(power_types, power_types)
        aMod = rnd_stat(power_mod, power_mods)
    end
    if iType == 4 then
        aLoc  = rnd_stat(save_types, save_types)
        aMod = rnd_stat(save_mod, save_mods)
    end
	
    if math.floor(mt.rand() * 100) + 1 >= 97 then
        aLoc  = apply.ext_affect
		aMod = rnd_stat(affect_mod, affect_mods)
    end

    return aLoc, aMod
end


function random_get_loc_mod( iType )
    local attrib_types = 	{  	apply.str,
                                apply.dex,	apply.dex,
                                apply.int,	apply.int,	apply.int,
                                apply.wis,	apply.wis,	apply.wis,
                                apply.con,	apply.con,	apply.con,
                                apply.lck,	apply.lck,	apply.lck,
                                apply.cha,	apply.cha,	apply.cha,
                                apply.hr,	apply.hr,	
                                apply.dr,	apply.dr,
                                apply.spelldam,
                            }
                
    local power_types = 	{ 	apply.mana,	apply.mana,
                                apply.hp,	apply.hp,
                                apply.move,	apply.move,	apply.move, 
                            }
                
    local save_types = 	{   apply.svs,	apply.svs,	apply.svs,
                            apply.svb,	apply.svb,
                            apply.svp,	apply.svp,
                            apply.svd,
                        }

	local affect_mods =	{	affby.det_magic,affby.det_magic,affby.det_magic,affby.det_magic,
							affby.det_evil,affby.det_evil,affby.det_evil,affby.det_evil,
							affby.det_good,affby.det_good,affby.det_good,affby.det_good,
							affby.flying,affby.flying,affby.flying,
							affby.floating,affby.floating,affby.floating,
							affby.aqua_breath,
							affby.tongues,affby.tongues,affby.tongues,
							affby.infrared,affby.infrared,affby.infrared,
						}

						
	local attrib_mods = { -3, -2, -2, -1, -1, -1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 4 };
    local attrib_mod = {}
    for _,v in ipairs(attrib_mods) do
        attrib_mod[_] = v
    end

    local power_mods = { -30, -20, -15, -15, -10, -10, -5, -5, 5, 5, 5, 10, 10, 10, 15, 15, 20, 20, 20, 30 };
    local power_mod = {}
    for _,v in ipairs(power_mods) do
        power_mod[_] = v
    end

    local save_mods = { -4, -3, -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, 1, 1, 2, 3 };   
    local save_mod = {}
    for _,v in ipairs(save_mods) do
        save_mod[_] = v
    end

	local affect_mod = {}
	for _,v in ipairs(affect_mods) do
		affect_mod[_] = v
	end

	local seed = os.time()
	mt.srand({os.time(), math.random(os.time()), os.time() + math.random(100)})

	iType = math.floor (mt.rand () * 4) + 1 
    if iType == 1 or iType == 3 then
        aLoc = rnd_stat(attrib_types, attrib_types)
        aMod = rnd_stat(attrib_mod, attrib_mods)
    end
    if iType == 2 then
        aLoc = rnd_stat(power_types, power_types)
        aMod = rnd_stat(power_mod, power_mods)
    end
    if iType == 4 then
        aLoc  = rnd_stat(save_types, save_types)
        aMod = rnd_stat(save_mod, save_mods)
    end

    if math.floor(mt.rand() * 100) + 1 >= 97 then
        aLoc  = apply.ext_affect
		aMod = rnd_stat(affect_mod, affect_mods)
    end
	
    return aLoc, aMod
end

local treasureadj1 =    {  "a splendid", "a bizarre", "a dusty", "a scratched",
                           "a flawed", "a burnt", "a heavy", "a gilded", "a spooky", "a flaming", "a plain",
                           "a warm", "a solid", "a serpentine", "a wrinkled", "a hypnotic", "a plain",
                           "a sparkling", "a dull", "a glittering", "a spiked", "a strange", "a chipped",
                           "a runed", "a dirty", "a mystical", "a corrupt", "a thorny", "a cold", "an ugly",
                           "an ornate", "an icy", "an illuminated", "an ethereal", "an eerie", "a twisted",
                           "an antique", "an old", "an elven", "a dwarven", "a ghoulish", "a reptilian",
                           "an ancient", "a corroded", "a dim", "a dark", "a light", "a barbed", "a battered",
                           "a battle-worn", "a blackened", "a bound", "a burnished", "a ceremonial", "a champion",
                           "a crowned", "a corroded", "a cracked", "a curved", "a deadly", "a dented", "a dilapidated",
                           "an engraved", "an enruned", "an evil-looking", "a fanatics", "a fighting", "a galvanized",
                           "a gleaming", "a glimmering", "a glistening", "a glossy", "a hand-forged", "a holy",
                           "a hunter's", "a jagged", "a keen", "a leather wrapped", "a lined", "a lustrous",
                           "an orcish", "a pitted", "a polished", "a radiant", "a ritualistic", "a rune-covered",
                           "a rust stained", "a rusty", "a seared", "a shining", "a silvery", "a studded",
                           "a tarnished", "a tempered", "a trusty", "a warped", "a worn", "an alluring",
                           "an antiquated", "an archaic", "a banded", "a beaded", "a beveled", "a bleached",
                           "a blemished", "a bloodstained", "a bold", "a brilliant", "a brittle", "a brushed",
                           "a buffed", "a bulky", "a charred", "a cloudy", "a coarse", "a courtly", "a crude",
                           "a delicate", "a durable", "a drab", "an elaborate", "an elegant", "an exquisite",
                           "a faded", "a fake", "a featureless", "a fine", "a flawed", "a garish", "a gnarled",
                           "a grand", "a grimy", "a hardened", "a hideous", "an intricate", "a linked", "a majestic",
                           "a modest", "a mottled", "a nightmarish", "an odd", "a plain", "a pure", "a rich",
                           "a round", "a rugged", "a scorched", "a scuffed", "a smooth", "a speckled", "a stark",
                           "a star-shaped", "a stately", "a stylish", "a tinted", "a twisted", "a withering" 
                        }

local treasureadj2 =    {  "diamond", "emerald", "topaz", "wooden", "jade",
                           "white gold", "onyx", "tin", "glass", "marble", "silver", "granite",
                           "amber", "iron", "ruby", "garnet", "turquoise", "mithril", "steel",
                           "ivory", "pearl", "gold", "brass", "ebony", "adamantium", "sapphire",
                           "platinum", "electrum", "turquoise", "opal", "ironwood", "mesquite", 
                           "garnet", "agate", "amethyst", "beryl", "black opal", "blazestar", "bloodjewel",
                           "carnelian", "cat's eye", "crystal", "deathstone", "dragonfire opal", "dreamstone",
                           "feystone", "firestone", "fire pearl", "gold nugget", "jacinth", "jasper",
                           "lapis lazuli", "malachite", "moonstone", "obsidian", "opal", "peridot", "star ruby",
                           "starstone", "tigerfang crystal", "zircon", "abalone shell", "clam shell", "conch shell",
                           "scallop shell", "hessonite", "red coral", "alexandrite", "spinel", "tanzanite", "tsavorite",
                           "amazonite", "azurite", "aventurine", "chrysoberyl", "titanium", "quartz", "peridot",
                           "sillimanite", "tiger eye", "pyrite", "demon skull", "dragon tooth", "lava rock"  
                        }

 --Trinket stuff
local trinket =     { 	"pebble", "bauble", "stone", "charm", "fetish",
                        "bone", "trinket", "knickknack", "curio", "walking stick", "staff", "scepter",
                        "wand", "cane", "rattle", "holy symbol", "jewel", "gem" 
                    }

local badges =      { 	"of might", "of the sun", "of honor", "of blood", "of the Gods", "of Death",
                        "of light", "of dark", "of the forest", "of the mountains", "of the moon", "of the plains",
                        "of pride", "of evil", "of good", "of the sky", "of the Elves", "of the Dwarves", "of the sea",
                        "of the Ghouls", "of horror", "of truth", "of courage", "of the stars", "of battle",
                        "of Hellfire", "of the demons", "of the damned", "of the unlucky", "of bones",
                        "of the dead", "of the undead", "of the earth", "of lust", "of greed", "of vanity",
                        "of sloth", "of glutony", "of envy", "of wrath", "of Famine", "of War", "of the Goddess",
                        "of Pestilence", "of the Apocalypse"
                    }

 -- Armor stuff
local metalarmors = 	{ 	{ name = "scale mail", 		ac = math.random( 9, 12), weight = 2},
                            { name = "chain mail", 		ac = math.random(10, 13), weight = 1},
                            { name = "plate mail", 		ac = math.random(10, 15), weight = 3},
                            { name = "mithril", 		ac = math.random(12, 17), weight = 1},
                            { name = "splint mail", 	ac = math.random( 9, 13), weight = 2},
                            { name = "spiked", 		    ac = math.random(11, 16), weight = 2},
                            { name = "silver", 		    ac = math.random(10, 13), weight = 2},
                            { name = "platinum", 		ac = math.random(11, 16), weight = 2},
                            { name = "gold", 		    ac = math.random(11, 14), weight = 3},
                            { name = "brass", 		    ac = math.random( 9, 13), weight = 3},
                            { name = "augmented chain", ac = math.random(10, 14), weight = 2},
                            { name = "double chain", 	ac = math.random(11, 15), weight = 2},
                            { name = "brigandine", 		ac = math.random( 9, 13), weight = 1},
                            { name = "augmented plate", ac = math.random(11, 17), weight = 2},
                            { name = "half plate", 		ac = math.random(10, 14), weight = 3},
                            { name = "full plate", 		ac = math.random(12, 16), weight = 4},
                            { name = "lamellar", 		ac = math.random(10, 14), weight = 3},
                            { name = "titanium",		ac = math.random(14, 18), weight = 1},
                            { name = "copper",		    ac = math.random( 7, 10), weight = 2},
                        }
				     
local metalarmor_mods = {   "a bright", "a shiny", "a dented", "an ornate", "a runed", "an ugly",
                            "a tarnished", "a sturdy", "a strong", "a heavy", "a scratched",
                            "a battered", "a battle-worn", "a blackened", "a burnished",
                            "a ceremonial", "an engraved", "an enruned", "an etched",
                            "a gilded", "a heavy", "a pitted", "a polished", "a rusty",
                            "a silvery", "a warped", "a trusty", "a knight's", "a warrior's" 
                        }
						
local otherarmor_types =    {   { name = "leather", 		    ac = math.random( 4,  7), weight = 1},
                                { name = "studded leather", 	ac = math.random( 5,  8), weight = 1},
                                { name = "elven chain mail", 	ac = math.random( 6, 10), weight = 1},
                                { name = "thorny", 		        ac = math.random( 3,  7), weight = 1},
                                { name = "boiled leather", 	    ac = math.random( 4,  7), weight = 1},
                                { name = "hardened leather", 	ac = math.random( 5,  8), weight = 1},
                                { name = "ethereal", 		    ac = math.random( 6, 10), weight = 1},
                                { name = "mystical", 		    ac = math.random( 5,  9), weight = 1},
                                { name = "cloth", 		        ac = math.random( 2,  4), weight = 1},
                                { name = "light leather", 	    ac = math.random( 3,  6), weight = 1},
                                { name = "full leather", 	    ac = math.random( 5,  8), weight = 1},
                                { name = "reinforced leather", 	ac = math.random( 5,  8), weight = 1},
                                { name = "double leather", 	    ac = math.random( 5,  8), weight = 1},
                                { name = "cuirbouilli", 	    ac = math.random( 4,  7), weight = 1},
                                { name = "bark", 		        ac = math.random( 4,  6), weight = 1},
                                { name = "bone", 		        ac = math.random( 5,  7), weight = 2},
                                { name = "shell", 		        ac = math.random( 4,  7), weight = 1},
                                { name = "coral", 		        ac = math.random( 5,  8), weight = 1},
                                { name = "dwarven stone", 	    ac = math.random( 7, 10), weight = 2},
                                { name = "chitin", 		        ac = math.random( 5,  9), weight = 1},
                                { name = "elven mithril",	    ac = math.random( 8, 12), weight = 1},
                                { name = "dragon scale",	    ac = math.random(10, 14), weight = 3},
                                { name = "demon hide",		    ac = math.random( 8, 12), weight = 1},
                                { name = "mithril weave",	    ac = math.random( 8, 12), weight = 0},
                                { name = "elfweave",		    ac = math.random( 4,  8), weight = 0},
                                { name = "padded cloth",	    ac = math.random( 2,  4), weight = 1},
                                { name = "heavy cloth",		    ac = math.random( 3,  6), weight = 2},
                                { name = "flox",                ac = math.random( 2,  5), weight = 1},
                            }
				     
local otherarmor_mods = { 	"a ripped", 	"a sturdy", 	"a torn", 	        "a strong", 	"a light", 
                            "a stained",	"an ugly", 	    "a clean", 	        "a dirty", 	    "a worn", 
                            "a battered",	"a ceremonial", "an enruned", 	    "a heavy", 	    "a hunter's",
                            "a lined", 	    "a seared", 	"a trusty", 	    "a woodsman's",	"a bloody",
                            "a flaming",	"a smoking",	"an illuminated",   "a druid's",	"a shaman's",
                            "a burnt",	    "a warm",	    "an icy",	        "a formal",	    "a blood-stained"
                        }
						
 -- Weapon stuff
local weapons = {   { name = "a long sword", 	    weight = math.random( 6,  9), roll = math.random( 7, 10), dam = dtype.slice},
                    { name = "a bastard sword", 	weight = math.random( 9, 13), roll = math.random(10, 14), dam = dtype.slash},
                    { name = "a broad sword", 	    weight = math.random( 7, 11), roll = math.random( 8, 12), dam = dtype.slice},
                    { name = "a scimitar", 		    weight = math.random( 4,  7), roll = math.random( 5,  8), dam = dtype.slice},
                    { name = "a bow", 		        weight = math.random(10, 15), roll = math.random(15, 22), dam = dtype.arrow},
                    { name = "a short sword", 	    weight = math.random( 2,  6), roll = math.random( 4,  7), dam = dtype.stab},
                    { name = "a dagger", 		    weight = math.random( 1,  3), roll = math.random( 4,  5), dam = dtype.pierce},
                    { name = "a tiger claw", 	    weight = math.random( 2,  5), roll = math.random( 4,  6), dam = dtype.claw},
                    { name = "a hammer", 		    weight = math.random( 8, 12), roll = math.random(12, 17), dam = dtype.pound},
                    { name = "a mace", 		        weight = math.random( 7, 10), roll = math.random( 9, 13), dam = dtype.pound},
                    { name = "a spiked mace",	    weight = math.random( 8, 11), roll = math.random( 9, 14), dam = dtype.crush},
                    { name = "a whip", 		        weight = math.random( 3,  5), roll = math.random( 4,  6), dam = dtype.whip},
                    { name = "a spiked whip", 	    weight = math.random( 4,  6), roll = math.random( 5,  7), dam = dtype.whip},
                    { name = "a club", 		        weight = math.random( 5, 11), roll = math.random( 6, 12), dam = dtype.pound},
                    { name = "a crossbow", 		    weight = math.random(11, 16), roll = math.random(15, 22), dam = dtype.bolt},
                    { name = "a flail", 		    weight = math.random( 9, 14), roll = math.random(10, 15), dam = dtype.blast},
                    { name = "a quarter staff", 	weight = math.random( 4,  9), roll = math.random( 5, 10), dam = dtype.pound},
                    { name = "a knife", 		    weight = math.random( 1,  3), roll = math.random( 4,  5), dam = dtype.pierce},
                    { name = "a dirk", 		        weight = math.random( 1,  3), roll = math.random( 4,  5), dam = dtype.stab},
                    { name = "a battle axe", 	    weight = math.random( 9, 14), roll = math.random(12, 18), dam = dtype.aslash},
                    { name = "a hatchet", 		    weight = math.random( 3,  6), roll = math.random( 4,  7), dam = dtype.hack},
                    { name = "a rapier", 		    weight = math.random( 3,  6), roll = math.random( 7,  9), dam = dtype.pierce},
                    { name = "a katana", 		    weight = math.random( 4,  8), roll = math.random( 8, 11), dam = dtype.slash},
                    { name = "an axe", 		        weight = math.random( 5,  9), roll = math.random( 6, 10), dam = dtype.aslice},
                    { name = "a halberd", 		    weight = math.random(12, 20), roll = math.random(17, 25), dam = dtype.pslice},
                    { name = "a spiked gauntlet", 	weight = math.random( 1,  3), roll = math.random( 4,  6), dam = dtype.hit},
                    { name = "a naginata", 		    weight = math.random(12, 20), roll = math.random(17, 25), dam = dtype.pslash},
                    { name = "a combat glove", 	    weight = math.random( 1,  3), roll = math.random( 4,  6), dam = dtype.hit},
                    { name = "a dragon claw", 	    weight = math.random( 2,  5), roll = math.random( 4,  7), dam = dtype.tear},
                    { name = "a leopard claw", 	    weight = math.random( 2,  5), roll = math.random( 4,  7), dam = dtype.rip},
                    { name = "a weighted glove", 	weight = math.random( 1,  3), roll = math.random( 4,  5), dam = dtype.hit},
                    { name = "a steel talon", 	    weight = math.random( 3,  7), roll = math.random( 4,  8), dam = dtype.rip},
                    { name = "a battle gauntlet", 	weight = math.random( 1,  3), roll = math.random( 4,  7), dam = dtype.hit},
                    { name = "a nunchuka", 		    weight = math.random( 2,  6), roll = math.random( 4,  7), dam = dtype.pound},
                    { name = "a bo staff", 		    weight = math.random( 5,  9), roll = math.random( 6, 10), dam = dtype.pound},
                    { name = "a ninja-to", 		    weight = math.random( 3,  5), roll = math.random( 4,  8), dam = dtype.stab},
                    { name = "a khopesh", 		    weight = math.random(11, 15), roll = math.random(12, 16), dam = dtype.slice},
                    { name = "a bolo", 		        weight = math.random( 1,  3), roll = math.random( 4,  6), dam = dtype.whip},
                    { name = "a sai", 		        weight = math.random( 1,  3), roll = math.random( 4,  6), dam = dtype.pierce},
                    { name = "a battle fork", 	    weight = math.random( 9, 15), roll = math.random(12, 18), dam = dtype.tear},
                    { name = "an eagle talon", 	    weight = math.random( 1,  3), roll = math.random( 4,  7), dam = dtype.claw},
                    { name = "a razor staff", 	    weight = math.random(10, 13), roll = math.random(13, 19), dam = dtype.pslash},
                    { name = "a maul", 		        weight = math.random(15, 20), roll = math.random(18, 26), dam = dtype.blast},
                    { name = "a spiked hammer", 	weight = math.random(14, 18), roll = math.random(16, 23), dam = dtype.crush},
                    { name = "a war pick", 		    weight = math.random(12, 16), roll = math.random(15, 20), dam = dtype.apierce},
                    { name = "a battle scepter", 	weight = math.random( 9, 15), roll = math.random(12, 18), dam = dtype.pound},
                    { name="an executioner's sword",weight = math.random(13, 17), roll = math.random(16, 20), dam = dtype.slash},
                    { name = "a deathblade", 	    weight = math.random( 9, 14), roll = math.random(10, 15), dam = dtype.slice},
                    { name = "a thorny whip", 	    weight = math.random( 2,  5), roll = math.random( 4,  8), dam = dtype.whip},
                    { name = "a hand crossbow", 	weight = math.random( 3,  8), roll = math.random( 7, 10), dam = dtype.pierce},
                    { name = "a spiked chain", 	    weight = math.random( 5,  9), roll = math.random( 8, 12), dam = dtype.whip},
                    { name = "a pick axe",		    weight = math.random( 3,  7), roll = math.random( 9, 10), dam = dtype.apierce},
                    { name = "a small crossbow",	weight = math.random( 2,  4), roll = math.random( 7, 12), dam = dtype.bolt},
                    { name = "razor wire",		    weight = math.random( 1,  3), roll = math.random( 6, 10), dam = dtype.slice},
                    { name = "a large club",	    weight = math.random( 8, 12), roll = math.random(10, 12), dam = dtype.pound},
                    { name = "a spiked club",	    weight = math.random( 9, 15), roll = math.random(15, 18), dam = dtype.blast},
                    { name = "a dwarven warhammer",	weight = math.random( 9, 15), roll = math.random(15, 18), dam = dtype.pound},
                    { name = "a cutlass",		    weight = math.random( 4,  7), roll = math.random( 8, 12), dam = dtype.slash},
                    { name = "a foil",		        weight = math.random( 2,  5), roll = math.random( 9, 12), dam = dtype.slash},
                    { name = "a morning star",	    weight = math.random( 4,  8), roll = math.random( 8, 14), dam = dtype.pound},
                }

function gr(list)
	mt.srand({os.time(), math.random(os.time()), os.time() + math.random(100)})
    return list[math.floor(mt.rand() * #list)+1]
end

function generate_random_item(iType, iName, bool)

	if iType == itype.armor or iType == itype.artarmor then
		if bool == 1 then
			local x = math.random(1,#metalarmors)
            name = string.format("%s %s", gr(metalarmor_mods), metalarmors[x].name)
			ac = metalarmors[x].ac
			weight = metalarmors[x].weight
		else
			local x = math.random(1, #otherarmor_types)
            name = string.format("%s %s", gr(otherarmor_mods), otherarmor_types[x].name)
			ac = otherarmor_types[x].ac
			weight = otherarmor_types[x].weight
		end
        name = string.format(iName, name)
		return name, ac, weight, string.format("%s lies here.", capitalize(name))
	end
	
	if iType == itype.worn or iType == itype.artworn then
        name = string.format(iName, gr(badges))
        return name, string.format("%s lies here.", capitalize(name))
	end
	
	if iType == itype.weapon or iType == itype.artweapon then
        local w = gr(weapons)
        name = string.format(iName, w.name)
		return name, w.weight, w.roll, w.dam, string.format("%s lies here.", capitalize(name))
	end
	
	if iType == itype.treasure or iType == itype.arttreasure then
		if bool == 1 then
            name = string.format("%s %s %s", gr(treasureadj1), gr(treasureadj2), gr(trinket))
		else
            name = string.format("%s %s", gr(treasureadj1), gr(treasureadj2))
		end
        name = string.format(iName, name)
		return name, string.format("%s lies here.", capitalize(name))
	end
	
	if iType == itype.light or iType == itype.artlight then
        name = string.format(iName, string.format("%s %s", gr(treasureadj1), gr(treasureadj2)))
		return name, string.format("%s lies here.", capitalize(name))
	end
end
 -- magic items 
local potion_spells = {"shield","shield","shield","shield","shield","shield","shield",
    "refresh","refresh","refresh","refresh","refresh","refresh","refresh",
    "armor","armor","armor","armor","armor","armor","armor",
    "elven beauty","elven beauty","elven beauty","elven beauty","elven beauty","elven beauty","elven beauty",
    "cure light","cure light","cure light","cure light","cure light","cure light","cure light",
    "magic missile","magic missile","magic missile","magic missile","magic missile","magic missile","magic missile",
    "tongues","tongues","tongues","tongues","tongues","tongues","tongues",
    "float","float","float","float","float","float","float",
    "word of recall","word of recall","word of recall","word of recall","word of recall","word of recall","word of recall",
    "scry","scry","scry","scry","scry","scry","scry",
    "infravision","infravision","infravision","infravision","infravision","infravision","infravision",
    "cure serious","cure serious","cure serious","cure serious","cure serious",
    "sagacity","sagacity","sagacity","sagacity","sagacity",
    "detect magic","detect magic","detect magic","detect magic","detect magic",
    "slink","slink","slink","slink","slink",
    "alertness","alertness","alertness","alertness","alertness",
    "inner warmth","inner warmth","inner warmth","inner warmth","inner warmth",
    "grounding","grounding","grounding","grounding","grounding",
    "detect hidden","detect hidden","detect hidden","detect hidden","detect hidden",
    "cure critical","cure critical","cure critical",
    "cause critical","cause critical","cause critical",
    "detect invis","detect invis","detect invis",
    "kindred strength","kindred strength","kindred strength",
    "trollish vigor","trollish vigor","trollish vigor",
    "dragon wit","dragon wit","dragon wit",
    "cure poison","cure poison","cure poison",
    "poison","poison","poison",
    "true sight","true sight","true sight",
    "cure weakness","cure weakness","cure weakness",
    "dragonskin","dragonskin","dragonskin",
    "demonskin","demonskin","demonskin",
    "blazeward","blazeward","blazeward",
    "spirit armor","spirit armor","spirit armor",
    "fly","fly","fly",
    "antimagic shell","antimagic shell","antimagic shell",
    "improved invis","improved invis","improved invis",
    "aqua breath","aqua breath","aqua breath",
    "curse","curse",
    "remove curse","remove curse",
    "heal","heal",
    "sanctuary","sanctuary",
    "nostrum","nostrum",
    "valiance","valiance",
    "dispel magic","dispel magic",
    "stone skin","stone skin",
    "aura of fear","aura of fear",
    "lethargy","lethargy",
    "ethereal shield","ethereal shield",
    "fireshield","fireshield",
    "iceshield","iceshield",
    "shockshield","shockshield",
    "restore mana","restore mana",
    "bless","bless",
    "eldritch sphere","eldritch sphere",
    "spirit shield",
    "divinity",
    "invoke stag",
    "telescape",
    "invoke dragon",
    "invoke wolf"
    }

local scroll_spells = {"shield","shield","shield","shield","shield","shield","shield",
        "armor","armor","armor","armor","armor","armor","armor",
        "elven beauty","elven beauty","elven beauty","elven beauty","elven beauty","elven beauty","elven beauty",
        "cure light","cure light","cure light","cure light","cure light","cure light","cure light",
        "cause light","cause light","cause light","cause light","cause light","cause light","cause light",
        "magic missile","magic missile","magic missile","magic missile","magic missile","magic missile","magic missile",
        "tongues","tongues","tongues","tongues","tongues","tongues","tongues",
        "float","float","float","float","float","float","float",
        "word of recall","word of recall","word of recall","word of recall","word of recall","word of recall","word of recall",
        "scry","scry","scry","scry","scry","scry","scry",
        "infravision","infravision","infravision","infravision","infravision","infravision","infravision",
        "identify","identify","identify","identify","identify","identify","identify",
        "cure serious","cure serious","cure serious","cure serious","cure serious",
        "cause serious","cause serious","cause serious","cause serious","cause serious",
        "sagacity","sagacity","sagacity","sagacity","sagacity",
        "burning hands","burning hands","burning hands","burning hands","burning hands","burning hands","burning hands",
        "shocking grasp","shocking grasp","shocking grasp","shocking grasp","shocking grasp","shocking grasp","shocking grasp",
        "ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist",
        "detect magic","detect magic","detect magic","detect magic","detect magic",
        "slink","slink","slink","slink","slink",
        "alertness","alertness","alertness","alertness","alertness",
        "inner warmth","inner warmth","inner warmth","inner warmth","inner warmth",
        "grounding","grounding","grounding","grounding","grounding",
        "cure critical","cure critical","cure critical",
        "cause critical","cause critical","cause critical",
        "lightning bolt","lightning bolt","lightning bolt",
        "detect invis","detect invis","detect invis",
        "kindred strength","kindred strength","kindred strength",
        "trollish vigor","trollish vigor","trollish vigor",
        "dragon wit","dragon wit","dragon wit",
        "cure poison","cure poison","cure poison",
        "poison","poison","poison",
        "weaken","weaken","weaken",
        "cure weakness","cure weakness","cure weakness",
        "dragonskin","dragonskin","dragonskin",
        "demonskin","demonskin","demonskin",
        "razorbait","razorbait","razorbait",
        "swordbait","swordbait","swordbait",
        "blazebane","blazebane","blazebane",
        "blazeward","blazeward","blazeward",
        "fly","fly","fly",
        "fear","fear","fear",
        "antimagic shell","antimagic shell","antimagic shell",
        "improved invis","improved invis","improved invis",
        "harm","harm","harm",
        "cure blindness","cure blindness","cure blindness",
        "curse","curse",
        "blindness","blindness",
        "remove curse","remove curse",
        "heal","heal",
        "sanctuary","sanctuary",
        "flamestrike","flamestrike",
        "nostrum","nostrum",
        "valiance","valiance",
        "paralyze","paralyze",
        "taint","taint",
        "dispel magic","dispel magic",
        "stone skin","stone skin",
        "aura of fear","aura of fear",
        "fireball","fireball",
        "colour spray","colour spray",
        "sulfurous spray","sulfurous spray",
        "lethargy","lethargy",
        "ethereal shield","ethereal shield",
        "fireshield","fireshield",
        "iceshield","iceshield",
        "shockshield","shockshield",
        "restore mana","restore mana",
        "bless","bless",
        "burning hands","burning hands",
        "chill touch","chill touch",
        "create food","create food",
        "create spring","create spring",
        "binding darkness","binding darkness",
        "dispel good","dispel good",
        "dispel evil","dispel evil",
        "quantum spike",
        "teleport",
        "mindfog",
        "divinity",
        "midas touch",
        "enchant treasure",
        "enchant armor",
        "enchant weapon",
        "enhance treasure",
        "enhance armor",
        "enhance weapon",
        "mindfog"
    }

local wand_spells = {"shield","shield","shield","shield","shield","shield","shield",
        "armor","armor","armor","armor","armor","armor","armor",
        "cure light","cure light","cure light","cure light","cure light","cure light","cure light",
        "cause light","cause light","cause light","cause light","cause light","cause light","cause light",
        "magic missile","magic missile","magic missile","magic missile","magic missile","magic missile","magic missile",
        "float","float","float","float","float","float","float",
        "scry","scry","scry","scry","scry","scry","scry",
        "infravision","infravision","infravision","infravision","infravision","infravision","infravision",
        "cure serious","cure serious","cure serious","cure serious","cure serious",
        "cause serious","cause serious","cause serious","cause serious","cause serious",
        "sagacity","sagacity","sagacity","sagacity","sagacity",
        "burning hands","burning hands","burning hands","burning hands","burning hands","burning hands","burning hands",
        "shocking grasp","shocking grasp","shocking grasp","shocking grasp","shocking grasp","shocking grasp","shocking grasp",
        "ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist",
        "detect magic","detect magic","detect magic","detect magic","detect magic",
        "slink","slink","slink","slink","slink",
        "invis object","invis object","invis object","invis object","invis object",
        "inner warmth","inner warmth","inner warmth","inner warmth","inner warmth",
        "grounding","grounding","grounding","grounding","grounding",
        "cure critical","cure critical","cure critical",
        "cause critical","cause critical","cause critical",
        "lightning bolt","lightning bolt","lightning bolt",
        "kindred strength","kindred strength","kindred strength",
        "trollish vigor","trollish vigor","trollish vigor",
        "dragon wit","dragon wit","dragon wit",
        "cure poison","cure poison","cure poison",
        "poison","poison","poison",
        "weaken","weaken","weaken",
        "cure weakness","cure weakness","cure weakness",
        "razorbait","razorbait","razorbait",
        "swordbait","swordbait","swordbait",
        "blazebane","blazebane","blazebane",
        "fly","fly","fly",
        "fear","fear","fear",
        "improved invis","improved invis","improved invis",
        "curse","curse",
        "remove curse","remove curse",
        "heal","heal",
        "nostrum","nostrum",
        "valiance","valiance",
        "paralyze","paralyze",
        "dispel magic","dispel magic",
        "stone skin","stone skin",
        "fireball","fireball",
        "colour spray","colour spray",
        "sulfurous spray","sulfurous spray",
        "lethargy","lethargy",
        "ethereal shield","ethereal shield",
        "fireshield","fireshield",
        "iceshield","iceshield",
        "shockshield","shockshield",
        "bless","bless",
        "sanctuary","sanctuary",
        "create spring","create spring",
        "create food","create food",
        "binding darkness","binding darkness",
        "dispel good","dispel good",
        "dispel evil","dispel evil",
        "midas touch",
        "unravel defense",
        "fear",
        "quantum spike",
        "enchant treasure",
        "enchant armor",
        "enchant weapon",
        "enhance treasure",
        "enhance armor",
        "enhance weapon",
        "mindfog"
    }
    
local staff_spells = {"cure light","cure light","cure light","cure light","cure light","cure light","cure light",
        "cause light","cause light","cause light","cause light","cause light","cause light","cause light",
        "magic missile","magic missile","magic missile","magic missile","magic missile","magic missile","magic missile",
        "ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist","ethereal fist",
        "cure serious","cure serious","cure serious","cure serious","cure serious",
        "cause serious","cause serious","cause serious","cause serious","cause serious",
        "cure critical","cure critical","cure critical",
        "cause critical","cause critical","cause critical",
        "lightning bolt","lightning bolt","lightning bolt",
        "kindred strength","kindred strength","kindred strength",
        "trollish vigor","trollish vigor","trollish vigor",
        "dragon wit","dragon wit","dragon wit",
        "antimagic shell","antimagic shell","antimagic shell",
        "heal","heal",
        "sanctuary","sanctuary",
        "nostrum","nostrum",
        "taint","taint",
        "dispel magic","dispel magic",
        "bless","bless",
        "divinity",
        "war cry",
        "invoke dragon",
        "restore mana"
    }
function generate_random_potion ( name )
    
    level   = math.random(1, 65)
    cost    = level * 10
    rnd1    = math.random(1, #potion_spells)
    rnd2    = -1
    rnd3    = -1
    new_name = string.format("%s %s", name, potion_spells[rnd1])
    rnd1 = mud.snlookup(potion_spells[rnd1])
    
    if math.random(1,100) > 75 then
        rnd2 = math.random(1, #potion_spells)
        name_new = string.format("%s %s", new_name, potion_spells[rnd2])
        rnd2 = mud.snlookup(potion_spells[rnd2])
        cost = cost + 1000
        if math.random(1,100) > 75 then
            rnd3 = math.random(1, #potion_spells)
            name_new = string.format("%s %s", new_name, potion_spells[rnd3])
            rnd3 = mud.snlookup(potion_spells[rnd3])
            cost = cost + 1000
        end
    end
    
    return level, cost, rnd1, rnd2, rnd3, new_name
    
end

function generate_random_scroll( name )
    
    level   = math.random(1, 65)
    cost    = level * 10
    rnd1    = math.random(1, #scroll_spells)
    rnd2    = -1
    rnd3    = -1
    new_name = string.format("%s %s", name, scroll_spells[rnd1])
    rnd1 = mud.snlookup(scroll_spells[rnd1])
    
    if math.random(1,100) > 75 then
        rnd2 = math.random(1, #scroll_spells)
        name_new = string.format("%s %s", new_name, scroll_spells[rnd2])
        rnd2 = mud.snlookup(scroll_spells[rnd2])
        cost = cost + 1000
        if math.random(1,100) > 75 then
            rnd3 = math.random(1, #scroll_spells)
            name_new = string.format("%s %s", new_name, scroll_spells[rnd3])
            rnd3 = mud.snlookup(scroll_spells[rnd3])
            cost = cost + 1000
        end
    end
    
    return level, cost, rnd1, rnd2, rnd3, new_name
    
end

function generate_random_salve( name )

    level   = math.random(1, 65)
    cost    = level * 10
    charges = math.random(2, 5)
    rnd1    = math.random(1, #potion_spells)
    rnd2    = -1
    new_name = string.format("%s %s", name, potion_spells[rnd1])
    rnd1 = mud.snlookup(potion_spells[rnd1])
    
    if math.random(1,100) > 75 then
        rnd2 = math.random(1, #potion_spells)
        name_new = string.format("%s %s", new_name, potion_spells[rnd2])
        rnd2 = mud.snlookup(potion_spells[rnd2])
        cost = cost + 1000
    end
    
    return level, cost, charges, rnd1, rnd2, new_name
    
end

function generate_random_wand( name )

    level   = math.random(1, 70)
    cost    = level * 20
    charges = math.random(2, 10)
    rnd1    = math.random(1, #wand_spells)
    rnd2    = -1
    new_name = string.format("%s %s", name, wand_spells[rnd1])
    rnd1 = mud.snlookup(wand_spells[rnd1])
    
    return level, cost, charges, rnd1, new_name
    
end

function generate_random_staff( name )

    level   = math.random(1, 70)
    cost    = level * 20
    charges = math.random(2, 10)
    rnd1    = math.random(1, #staff_spells)
    rnd2    = -1
    new_name = string.format("%s %s", name, staff_spells[rnd1])
    rnd1 = mud.snlookup(staff_spells[rnd1])
   
    return level, cost, charges, rnd1, new_name
    
end

 -- generate new short descriptions for these items when they become identified
 
 -- short descriptions for potions, pills and scrolls
function new_short_pps( what, v1, v2, v3 )

    new_name = "%s"
    if what == itype.potion then
        new_name = "&Ga potion of &W'&Y%s&W'"
    elseif what == itype.pill then
        new_name = "&Ga pill of &W'&Y%s&W'"
    elseif what == itype.scroll then
        new_name = "&Ga scroll of &W'&Y%s&W'"
    end
    
    if v1 >= 0 then
        new_name = string.format(new_name, mud.skillname(v1))
    end
    if v2 >= 0 then
        new_name = string.format("%s &W'&Y%s&W'", new_name, mud.skillname(v2))
    end
    if v3 >= 0 then
        new_name = string.format("%s &W'&Y%s&W'", new_name, mud.skillname(v3))
    end
    new_name = new_name .. "&D"
    
    return new_name

end

 -- short descriptions for salves
function new_short_salve( v1, v2 )

    new_name = "a salve of &W'&Y%s&W'"

    if v1 >= 0 then
        new_name = string.format(new_name, mud.skillname(v1))
    end
    if v2 >= 0 then
        new_name = string.format("%s &W'&Y%s&W'", new_name, mud.skillname(v2))
    end
    new_name = new_name .. "&D"
    
    return new_name

end
 -- short descriptions for wands and staves
function new_short_ws( what, v1 )

    new_name = "%s"
    if what == itype.wand then
        new_name = "a wand of &W'&Y%s&W'&D"
    elseif what == itype.staff then
        new_name = "a staff of &W'&Y%s&W'&D"
    end

    if v1 >= 0 then
        new_name = string.format(new_name, mud.skillname(v1))
    end
    
    return new_name

end
