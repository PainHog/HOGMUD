-- reset area drazville.are
function reset_drazville ()

    oinv(21500, 21118, 1)  -- Object: #21500 quest board => #21118 Questmasters Inc.
    minv(21102, 21179, 1, 1)  -- Mob: #21102 Gwen => #21179 An Entrance Way
    oinv(21117, 21175, 1)  -- Object: #21117 a small viewscreen => #21175 A Small Trailer
    oinv(21116, 21175, 1)  -- Object: #21116 a Lazyboy recliner => #21175 A Small Trailer
    oinv(21105, 21169, 2)  -- Object: #21105 a finely-carved wooden chair => #21169 Spoils of War
    oinv(21104, 21169, 1)  -- Object: #21104 a throne carved out of bone => #21169 Spoils of War
    oinv(21103, 21170, 1)  -- Object: #21103 a huge canopy bed => #21170 The Resting Chamber
    oinv(21101, 21165, 1)  -- Object: #21101 a giant magical viewscreen => #21165 A Dark Living Room
    oinv(21100, 21165, 1)  -- Object: #21100 a HUGE black leather sofa with fluffy pillows => #21165 A Dark Living Room
--~     oinv(21096, 21250, 1)  -- Object: #21096 a chair => #21250 Lex's Lair
--~     oinv(21095, 21250, 1)  -- Object: #21095 a chair => #21250 Lex's Lair
--~     oinv(21094, 21250, 1)  -- Object: #21094 a gray marble table => #21250 Lex's Lair
--~     minv(21101, 21250, 1, 1)  -- Mob: #21101 the Spirit of the Black Sable Dragon => #21250 Lex's Lair
    minv(21100, 21163, 1, 1)  -- Mob: #21100 a transportal spirit => #21163 Transportal  Chamber
    minv(21099, 21162, 1, 1, {}, {39, 38} )  -- Mob: #21099 Talesha => #21162 Alden Transportal
    minv(21098, 21161, 1, 1)  -- Mob: #21098 the Conjurer Guildmaster => #21161 Conjurers Guild
    minv(21097, 21160, 1, 1)  -- Mob: #21097 the Shaman Guildmaster => #21160 Shamans Guild
    oinv(21088, 21009, 1)  -- Object: #21088 a chair => #21009 The Temple Of Drazuk -- Resting Room
    oinv(21089, 21009, 1)  -- Object: #21089 a chair => #21009 The Temple Of Drazuk -- Resting Room
    oinv(21091, 21009, 1)  -- Object: #21091 a chair => #21009 The Temple Of Drazuk -- Resting Room
    oinv(21092, 21009, 1)  -- Object: #21092 a chair => #21009 The Temple Of Drazuk -- Resting Room
    minv(21096, 21159, 1, 1)  -- Mob: #21096 Grimwald => #21159 The Lucky Corpse
    minv(21095, 21158, 1, 1)  -- Mob: #21095 the Jester Guildmaster => #21158 Jesters Guild
    minv(21094, 21155, 1, 1, {}, {21115, 21114, 21113, 21112, 21111, 21110, 21109, 21108})  -- Mob: #21094 Valnurana => #21155 A Candlelit Lounge
    mud.set_exit_state (21155, "d", "cl") -- Door: #21155 A Candlelit Lounge/down => closed and locked
    mud.set_exit_state (21071, "u", "cl") -- Door: #21071 Corner Of Trumpy And Argot/up => closed and locked
    minv(21093, 21010, 1, 1)  -- Mob: #21093 Battlesister Amy => #21010 Homer Street
    minv(21092, 21012, 1, 1)  -- Mob: #21092 Battlesister Sara => #21012 Intersection Of Homer And Sturm
    oinv(21212, 21003, 1)  -- Object: #21212 the war noteboard => #21003 The Temple Of Drazuk -- Meeting Room
--~     mud.set_exit_state (21260, "s", "cl") -- Door: #21260 Lardar's Shack/south => closed and locked
--~     mud.set_exit_state (21038, "n", "cl") -- Door: #21038 Sturm Way/north => closed and locked
    minv(21090, 21154, 1, 1, {}, {21454, 21451, 21450})  -- Mob: #21090 Vorthan => #21154 The Grand Artificer
    minv(21089, 21153, 1, 1)  -- Mob: #21089 the Diabolist Guildmaster => #21153 Diabolists Guild
--~     mud.set_exit_state (21021, "e", "cl") -- Door: #21021 Homer Street/east => closed and locked
--~     mud.set_exit_state (21150, "w", "cl") -- Door: #21150 The Den/west => closed and locked
--~     minv(21088, 21150, 1, 1, {}, {21208, 21207, 21206})  -- Mob: #21088 the succubus => #21150 The Den
    minv(21087, 21025, 1, 1)  -- Mob: #21087 a scrawny rat => #21025 South Of Alden
    minv(21086, 21009, 1, 1)  -- Mob: #21086 Yoyoman => #21009 The Temple Of Drazuk -- Resting Room
    minv(21085, 21121, 1, 1)  -- Mob: #21085 Sturm the Wurm => #21121 The Sneaky Shadow
    minv(21084, 21016, 1, 1)  -- Mob: #21084 Battlesister Tressa => #21016 Intersection Of Homer And Trumpy
    oinv(21099, 21005, 1)  -- Object: #21099 The Book of Death => #21005 The Temple Of Drazuk -- Judgement Room
--~     mud.set_exit_state (21011, "u", "cl") -- Door: #21011 Homer Street/up => closed and locked
--~     mud.set_exit_state (21250, "d", "cl") -- Door: #21250 Lex's Lair/down => closed and locked
    minv(21083, 21164, 1, 1, {}, {21254, 21253, 21252, 21251})  -- Mob: #21083 a scaly bartender => #21164 Lair Of The Fur(r)y Dragon
    minv(21082, 21145, 1, 1)  -- Mob: #21082 Lilyan => #21145 Lilyans Recharging
    minv(21081, 21143, 1, 1)  -- Mob: #21081 Samuel => #21143 Samuels Repairshop
    minv(21068, 21010, 1, 1)  -- Mob: #21068 Thornton => #21010 Homer Street
    minv(21071, 21142, 1, 1)  -- Mob: #21071 the Monk Guildmaster => #21142 Monks Guild
    oinv(3750, 21420, 1)  -- Object: #3750 (not in area) => #21420 Drazuk's Office
    minv(21080, 21025, 1, 2)  -- Mob: #21080 a masked hunter => #21025 South Of Alden
    minv(21079, 21017, 1, 1)  -- Mob: #21079 a masked hunter => #21017 North Of Alden
    minv(21078, 21037, 1, 2)  -- Mob: #21078 a masked hunter => #21037 West Of Alden
    minv(21077, 21031, 1, 2)  -- Mob: #21077 a masked hunter => #21031 East Of Alden
    minv(21076, 21026, 1, 1)  -- Mob: #21076 a masked hunter => #21026 Pendragon Way
    minv(21075, 21032, 1, 1)  -- Mob: #21075 a masked hunter => #21032 Pendragon Way
    minv(21074, 21018, 1, 1)  -- Mob: #21074 a masked hunter => #21018 Homer Street
    minv(21073, 21010, 1, 1)  -- Mob: #21073 a masked hunter => #21010 Homer Street
    oinv(21090, 21001, 1)  -- Object: #21090 the main noteboard => #21001 The Temple Altar
    minv(21072, 21141, 1, 1)  -- Mob: #21072 the Thug Guildmaster => #21141 Thugs Guild
    minv(21070, 21140, 1, 1)  -- Mob: #21070 Thalen => #21140 The Portal Room
    minv(21069, 21025, 1, 1)  -- Mob: #21069 Malaclypse => #21025 South Of Alden
    oinv(21087, 21001, 1)  -- Object: #21087 a large map => #21001 The Temple Altar
    oinv(21086, 21001, 1)  -- Object: #21086 a bright white marble fountain => #21001 The Temple Altar
    minv(21067, 21139, 1, 1, {}, {21085, 21084, 21083, 21082, 21081, 21080, 21079})  -- Mob: #21067 Joyce the Barmistress => #21139 The Nightgaunt's Tickler
    minv(21066, 21127, 1, 1, {}, {21078, 21077, 21076})  -- Mob: #21066 Fargo => #21127 Alden Real Estate Brokers
    minv(21065, 21133, 1, 1)  -- Mob: #21065 the Druid Guildmaster => #21133 Druids Guild
    minv(21064, 21130, 1, 1)  -- Mob: #21064 the Mage Guildmaster => #21130 Mages Guild
    minv(21063, 21131, 1, 1)  -- Mob: #21063 the Cleric Guildmaster => #21131 Clerics Guild
    minv(21062, 21132, 1, 1)  -- Mob: #21062 the Thief Guildmaster => #21132 Thieves Guild
    minv(21061, 21129, 1, 1)  -- Mob: #21061 the Ranger Guildmaster => #21129 Rangers Guild
    minv(21060, 21128, 1, 1)  -- Mob: #21060 the Warrior Guildmaster => #21128 Warriors Guild
    minv(21059, 21138, 1, 1, {}, {21071})  -- Mob: #21059 Sarah the Chef => #21138 The Kitchen
    oinv(21074, 21138, 1)  -- Object: #21074 an ornately-carved wooden cupboard => #21138 The Kitchen
    mud.set_exit_state (21137, "w", "cl") -- Door: #21137 The Ghoul Hideaway/west => closed and locked
    mud.set_exit_state (21136, "e", "cl") -- Door: #21136 A Brightly Lit Hallway/east => closed and locked
    minv(21058, 21134, 1, 1, {}, {21071})  -- Mob: #21058 Jeeves the Butler => #21134 Above The Temple
    minv(21057, 21028, 1, 1)  -- Mob: #21057 a shabby beggar => #21028 Intersection Of Pendragon And Airwalk
    minv(21056, 21030, 1, 1)  -- Mob: #21056 a shabby beggar => #21030 Intersection Of Pendragon And Argot
    minv(21055, 21010, 1, 1)  -- Mob: #21055 a shabby beggar => #21010 Homer Street
    minv(21054, 21108, 1, 2)  -- Mob: #21054 a dirty rat => #21108 Sohcahtoa Street
    minv(21053, 21074, 1, 2)  -- Mob: #21053 a dirty rat => #21074 Argot Street
    minv(21052, 21039, 1, 2)  -- Mob: #21052 a dirty rat => #21039 Sturm Way
    minv(21051, 21029, 1, 2)  -- Mob: #21051 a dirty rat => #21029 Pendragon Way
    minv(21050, 21126, 1, 1, {}, {21070, 21069, 21068, 21067, 21066, 21065, 21064, 21063})  -- Mob: #21050 Ranger Richard => #21126 Outdoor Outfitters
    minv(21049, 21125, 1, 1, {}, {21062, 21061, 21060, 21059, 21058, 21057, 21056, 21055, 21054, 21053, 21052, 21051})  -- Mob: #21049 Joseph the Tailor => #21125 The Refined Warrior
    minv(21048, 21124, 1, 1, {}, {21050, 21049, 21048, 21047, 21046, 21044, 21045, 21043, 21042, 21041, 21040, 21039})  -- Mob: #21048 Mistress Leah => #21124 Mistress Leah's Fashions
    minv(21047, 21075, 1, 2)  -- Mob: #21047 the citizen => #21075 Argot Street
    minv(21046, 21094, 1, 2)  -- Mob: #21046 the citizen => #21094 Marley Way
    minv(21045, 21064, 1, 2)  -- Mob: #21045 the citizen => #21064 Sturm Way
    minv(21044, 21044, 1, 2)  -- Mob: #21044 the citizen => #21044 Airwalk Street
    minv(21043, 21026, 1, 2)  -- Mob: #21043 the citizen => #21026 Pendragon Way
    minv(21042, 21060, 1, 2)  -- Mob: #21042 the citizen => #21060 Shylok Street
    minv(21041, 21116, 1, 2)  -- Mob: #21041 the citizen => #21116 Trumpy Street
    minv(21040, 21106, 1, 2)  -- Mob: #21040 the citizen => #21106 Sohcahtoa Street
    minv(21039, 21014, 1, 2)  -- Mob: #21039 the citizen => #21014 Homer Street
    minv(21038, 21020, 1, 2)  -- Mob: #21038 the citizen => #21020 Intersection Of Homer And Scroll
    minv(21036, 21017, 1, 2, {body = 21038})  -- Mob: #21036 an elven mage => #21017 North Of Alden
    minv(21037, 21037, 1, 2, {body = 21038})  -- Mob: #21037 an elven mage => #21037 West Of Alden
    minv(21035, 21025, 1, 2, {wield = 21037})  -- Mob: #21035 a dwarven adventuress => #21025 South Of Alden
    minv(21034, 21031, 1, 2, {wield = 21037})  -- Mob: #21034 a dwarven adventuress => #21031 East Of Alden
    minv(21033, 21102, 1, 2)  -- Mob: #21033 a janitor => #21102 Sohcahtoa Street
    minv(21032, 21046, 1, 1)  -- Mob: #21032 a janitor => #21046 Airwalk Street
    minv(21031, 21074, 1, 1)  -- Mob: #21031 a janitor => #21074 Argot Street
    minv(21030, 21034, 1, 2)  -- Mob: #21030 a janitor => #21034 Intersection Of Pendragon And Shylok
    minv(21029, 21020, 1, 1)  -- Mob: #21029 a janitor => #21020 Intersection Of Homer And Scroll
    minv(21028, 21042, 1, 2)  -- Mob: #21028 a mangy mutt => #21042 Airwalk Street
    minv(21027, 21054, 1, 3)  -- Mob: #21027 a mangy mutt => #21054 Scroll Way
    minv(21026, 21085, 1, 2)  -- Mob: #21026 a scruffy dog => #21085 Argot Street
    minv(21025, 21111, 1, 3)  -- Mob: #21025 a scruffy dog => #21111 Sohcahtoa Street
    minv(21024, 21037, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036})  -- Mob: #21024 a cityguard => #21037 West Of Alden
    minv(21023, 21037, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036}) --  Mob: #21023 a cityguard => #21037 West Of Alden
    minv(21022, 21031, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036}) --  Mob: #21022 a cityguard => #21031 East Of Alden
    minv(21021, 21031, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036}) --  Mob: #21021 a cityguard => #21031 East Of Alden
    minv(21020, 21025, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036}) --  Mob: #21020 a cityguard => #21025 South Of Alden
    minv(21019, 21025, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036}) --  Mob: #21019 a cityguard => #21025 South Of Alden
    minv(21018, 21017, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036}) --  Mob: #21018 a cityguard => #21017 North Of Alden
    minv(21017, 21017, 1, 1, {light=10316, head=21025, legs=21028, feet=21031,body=21027, hands=21026, arms=21029, shield=21030, wield=math.random(21018, 21024), finger1=21035, pride1=21036}) --  Mob: #21017 a cityguard => #21017 North Of Alden
    minv(21016, 21041, 1, 2, {body=21027, finger1=21035, wield=math.random(21018, 21024)}) --  Mob: #21016 a cityguard => #21041 Corner Of Sturm And Airwalk
    minv(21015, 21048, 1, 2, {shield=21030, wield=math.random(21018, 21024), pride1=21036}) --  Mob: #21015 a cityguard => #21048 Corner Of Airwalk And Scroll
    minv(21014, 21055, 1, 2, {feet=21031, wield=math.random(21018, 21024), finger1=21035}) --  Mob: #21014 a cityguard => #21055 Corner Of Scroll And Shylok
    minv(21013, 21062, 1, 2, {legs=21028, wield=math.random(21018, 21024), pride1=21036}) --  Mob: #21013 a cityguard => #21062 Corner Of Shylok And Sturm
    minv(21012, 21071, 1, 2, {finger1=21035, hands=21026, wield=math.random(21018, 21024)}) --  Mob: #21012 a cityguard => #21071 Corner Of Trumpy And Argot
    minv(21011, 21086, 1, 2, {pride1=21036, wield=math.random(21018, 21024), head=21025}) --  Mob: #21011 a cityguard => #21086 Corner Of Argot And Marley
    minv(21010, 21097, 1, 2, {finger1=21035, wield=math.random(21018, 21024), arms=21029}) --  Mob: #21010 a cityguard => #21097 Corner Of Marley And Sohcahtoa
    minv(21009, 21112, 1, 2, {pride1=21036, body=21027, wield=math.random(21018, 21024)}) --  Mob: #21009 a cityguard => #21112 Corner Of Sohcahtoa And Trumpy
    minv(21008, 21123, 1, 1, {}, {35, 34, 21022, 21017, 21016, 21015, 21014, 21013, 21012})  -- Mob: #21008 Kar'tanth => #21123 The Sorcerer Store
    minv(21007, 21122, 1, 1, {}, {21025, 21026, 21027, 21028, 21029, 21030, 21031})  -- Mob: #21007 Garth => #21122 Garth's Armor Emporium
    minv(21006, 21121, 1, 1, {}, {21020, 21019, 21034, 21033, 21032, 33})  -- Mob: #21006 Franklin => #21121 The Sneaky Shadow
    minv(21005, 21120, 1, 1, {}, {7, 21024, 21023, 21022, 21021, 21020, 21019, 21018})  -- Mob: #21005 Khent => #21120 Khent's Weapon Shack
    minv(21004, 21119, 1, 1)  -- Mob: #21004 Carlyle => #21119 The First (And Only) Bank Of Alden.
    minv(21003, 21001, 1, 1)  -- Mob: #21003 Kallista => #21001 The Temple Altar
    minv(21002, 21118, 1, 1)  -- Mob: #21002 Joey the Questmaster => #21118 Questmasters Inc.
    minv(21001, 21007, 1, 1)  -- Mob: #21001 Jerald the Pitboy => #21007 The Temple Of Drazuk -- Donation Room
    oinv(21011, 21007, 1)  -- Object: #21011 donation pit => #21007 The Temple Of Drazuk -- Donation Room
    oinv(21100, 21183, 1)  -- Object: #21100 a HUGE black leather sofa with fluffy pillows => #21183 Kynn's Haven House
    minv(21103, 21184, 1)  -- Mob: #21103 Petro the petshop owner => The Pet Shop
    minv(21104, 21185, 1)  -- Mob: #21104 A battle wolf => The Pet Room
    minv(21105, 21185, 1)  -- Mob: #21105 A griffon => The Pet Room
    minv(21106, 21185, 1)  -- Mob: #21106 A nightmare => The Pet Room
    minv(21107, 21185, 1)  -- Mob: #21107 A small rat => The Pet Room
	minv(21108, 21185, 1)  -- Mob: #21108 donkey => The Pet Room
	minv(21109, 21185, 1)  -- Mob: #21109 dragon welp => The Pet Room
	minv(21111, 21185, 1)  -- Mob: #21111 lion => The Pet Room
	minv(21112, 21185, 1)  -- Mob: #21112 newt => The Pet Room
    

end
