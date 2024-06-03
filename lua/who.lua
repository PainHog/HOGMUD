-- who.lua
--[[
        replacement for do_who command
        
        2008-01-11
        Darwin @ House of Ghouls MUD
--]]
module (..., package.seeall)
function who_hog_gui()
    local sf = string.format

	mort_str 	= "|WHO_LIST:MORTAL|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|"
	imm_str 	= "|WHO_LIST:IMMORTAL|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|"

	function add_mortal(align, race, sex, level, class, rank, clan_name, deadly, flags, name, title, wiz )
		return sf (mort_str, align, race, sex, level, class, trim(flags), trim(deadly), name, title, rank, clan_name, wiz )
	end
	function add_immortal(align, race, sex, level, class, rank, clan_name, deadly, flags, name, title, wiz)
		return sf (imm_str, align, race, sex, level, class, trim(flags), trim(deadly), name, title, rank, clan_name, wiz )
	end
    immrank = { [65] = "Implementor",
                [64] = "Infinite",
                [63] = "Eternal",
                [62] = "Ancient",
                [61] = "Exalted God",
                [60] = "Supreme God",
                [59] = "Greater God",
                [58] = "God",
                [57] = "Lesser God",
                [56] = "Immortal",
                [55] = "Demigod",
                [54] = "Savior",
                [53] = "Creator",
                [52] = "Acolyte",
                [51] = "Master"
                }
    pc = mud.players_in_game()
    mortals = {}
    for k,v in ipairs(pc) do
        local p = mud.character_info(v)
        local name = p.name..""
        local l = p.level..""
        local a = "n"
        local sex = p.sex..""
        local cname = "|"
        local rk = ""
        local deadly = "0"
        local wiz = ""
        local flags = ""
        local pflags = p.pc["plr_flags"]
        if pflags["afk"] then
            flags = flags .. "a"
        end
        if p.pc["writing"] then
            flags = flags .. "w"
        end
        if p.level < 51 or mud.can_see(name) == true then
            if p.alignment < 0 then 
                a = "e"
            elseif p.alignment > 0 then
                a = "g"
            end
			cl = sf("%d|%d", p.class, p.dualclass)
            if p.pc["clan_name"] ~= "" then
                if p.pc["clan_rank"] ~= nil then
                    cname = sf("%s|%s", p.pc["clan_rank"], p.pc["clan_name"])
                else
                    cname = sf("|%s", p.pc["clan_name"])
                end
            end
            if p.level > 50 then
                if p.pc["rank"] ~= nil and p.pc["rank"] ~= "" then
                    rk = sf("%s", trim(p.pc["rank"]))
                else
                    rk = sf("%s", trim(immrank[p.level]))
                end
                if mud.iswizinvis(v) then
                    wiz = sf("%d", p.pc["wizinvis"])
                end
                info = add_immortal( a, p.race.."", sex, l, cl, rk, cname, deadly, flags, name, p.pc["title"], wiz )
            else
                if p.pc["rank"] ~= "" then
                    rk = trim(p.pc["rank"]) .. ""
                end
                if mud.isdeadly(p.name) then
                    deadly = "1"
                end
				info = add_mortal( a, p.race.."", sex, l, cl, rk, cname, deadly, flags, name, p.pc["title"], wiz )
            end
			mortals[#mortals+1] = info
        end
    end
	send("|WHO_LIST:RESET|")
    if #mortals > 0 then
        for _,v in ipairs(mortals) do
            send(v)
        end
    end
end

function who_hog_gui_inroom()
    local sf = string.format

	room = char.room()
    pc = mud.players_in_room()
	WhoInRoom = "|WHO_LIST:INROOM|"
    for k,v in ipairs(pc) do
		WhoInRoom = WhoInRoom .. v .. "|"
    end
	send(WhoInRoom)
end


function who(line)
	SHOW_SHORT = false
    arg = string.lower(trim(line))
    local sf = string.format
	me = char.info()
	me = me.pc["plr_flags"]
	if me["shortwho"] then
		SHOW_SHORT = true
	end
    if arg == "hog_gui" then
		who_hog_gui()
		who_hog_gui_inroom()
		return
	elseif arg == "inroom" then
		who_hog_gui_inroom()
		return
	end
	
    r = {} 
	for _,v in pairs(race) do 
		r[v] = capitalize(_)
	end
	if SHOW_SHORT then
		c = {"MGE", "CLR", "THF", "WAR", "THG", "DRD", "RGR", "MNK", 
			 "DBT", "CGR", "JST", "SHM", "CPN", "BSP", "ROG", "AMI" }
		class_length = 11
		mort_str 	= "%s%s&w-%s&W[&C%-2s &B%-7s &W]%s%s%s%s&W%s&w%s&D"
		imm_str 	= "%s%s&w-%s&W[&B%-11s&W]%s%s%s&W%s&w%s&D"
		r[0] = "HMN"
		r[1] = "ELF"
		r[2] = "DWF"
		r[3] = "HFG"
		r[4] = "PIX"
		r[5] = "MIN"
		r[6] = "OGR"
		r[7] = "ORC"
		r[8] = "TRL"
		r[9] = "HEL"
		r[10] = "GIT"
		r[11] = "DRW"
		r[12] = "SEL"
		r[13] = "LIZ"
		r[14] = "GNO"
		r[15] = "GHL"
		r[16] = "GOB"
		r[17] = "WLF"
		r[18] = "SHR"
		r[19] = "GUL"
		r[20] = "ZPH"
		r[21] = "JIN"
		r[22] = "AHP"
		function add_mortal(align, race, sex, level, class, rank, clan_name, deadly, flags, name, title )
			return sf (mort_str, align, race, sex, level, class, trim(flags), trim(deadly), " "..name, title, rank, clan_name )
		end
		function add_immortal(align, race, sex, class, clan_name, invis, flags, name, title)
			class_len = string.len(string.gsub(class, "&%a", ""))
			if class_len > 11 then
				class = string.sub(string.gsub(class, "&%a", ""), 1, 11)
			elseif class_len < 11 then
				class = class .. (" "):rep(11 - class_len)
			end
			return sf (imm_str, align, race, sex, class, flags, " "..name, title, clan_name, invis )
		end
	else
		c = {"Mage", "Cleric", "Thief", "Warrior", "Thug", "Druid", "Ranger", "Monk", 
			 "Diabolist", "Conjurer", "Jester", "Shaman", "Champion", "Bishop", "Rogue", "Archmagi" }
		class_length = 20
		imm_str = "&w-%s%-10s&w-%s&w- &W[ &B%-20s &W]%s%s\n\r          %s&W%s&w%s&D"
		mort_str = "&w-%s%-10s&w-%s&w- &W[&C%-2s &B%-18s &W]%s%s\n\r%s%s&W%s&w%s&D"
		function add_mortal(align, race, sex, level, class, rank, clan_name, deadly, flags, name, title )
			return sf (mort_str, align, race, sex, level, class, rank, clan_name, deadly, flags, name, title )
		end
		function add_immortal(align, race, sex, class, clan_name, invis, flags, name, title)
			return sf (imm_str, align, race, sex, class, clan_name, invis, flags, name, title )
		end
	end
    immrank = { [65] = "&RImplementor",
                [64] = "&PInfinite",
                [63] = "&PEternal",
                [62] = "&PAncient",
                [61] = "&PExalted God",
                [60] = "&PSupreme God",
                [59] = "&YGreater God",
                [58] = "&YGod",
                [57] = "&YLesser God",
                [56] = "&YImmortal",
                [55] = "&BDemigod",
                [54] = "&BSavior",
                [53] = "&BCreator",
                [52] = "&BAcolyte",
                [51] = "&BMaster"
                }
    
    pc = mud.players_in_game()
    mortals = {}
    immortals = {}
    for k,v in ipairs(pc) do
        local p = mud.character_info(v)
        local name = p.name
        local l = p.level
        local a = "&w"
        local sex = "&YN"
        local cname = ""
        local rk = ""
        local deadly = "          "
        local wiz = ""
        local flags = ""
        local pflags = p.pc["plr_flags"]
        if pflags["afk"] then
            flags = flags .. "&Y[&RAFK&Y] "
        end
        if p.pc["writing"] then
            flags = flags .. "&Y[&CWRITING&Y] "
        end
        if l < 51 or mud.can_see(name) == true then
            if p.alignment < 0 then 
                a = "&R"
            elseif p.alignment > 0 then
                a = "&B"
            end
            if p.sex == 1 then
                sex = "&BM"
            elseif p.sex == 2 then
                sex = "&PF"
            end
			if p.class ~= p.dualclass and p.class < 12 then 
				cl = sf("%s-%s", c[p.class+1], c[p.dualclass+1])
			else
				cl = c[p.class+1]
			end
            if p.pc["clan_name"] ~= "" then
                if p.pc["clan_rank"] ~= nil then
                    cname = sf(" &R<&Y[&R%s &Wof &C%s&Y]&R>", p.pc["clan_rank"], p.pc["clan_name"])
                else
                    cname = sf(" &R<&Y[&C%s&Y]&R>", p.pc["clan_name"])
                end
            end
            if l > 50 then
                if p.pc["rank"] ~= nil and p.pc["rank"] ~= "" then
                    local len = string.gsub(trim(p.pc["rank"]), "&%a", "")
                    cl = sf("%s", trim(p.pc["rank"]) .. (" "):rep (math.floor (class_length - #len)))
                else
                    local len = string.gsub(trim(immrank[l]), "&%a", "")
                    cl = sf("%s", trim(immrank[l]) .. (" "):rep(math.floor(class_length - #len)))
                end
                if mud.iswizinvis(v) then
                    wiz = sf(" &R<&WInvis &C%d&R>", p.pc["wizinvis"])
                end
                info = add_immortal( a, r[p.race], sex, cl, cname, wiz, flags, name, p.pc["title"] )
                immortals[#immortals+1] = info
            else
                if p.pc["rank"] ~= "" then
                    rk = " &W(" .. trim(p.pc["rank"]) .. "&W)"
                end
                if mud.isdeadly(p.name) then
                    deadly = "     &W[&RPK&W] "
                end
                info = add_mortal( a, r[p.race], sex, l, cl, rk, cname, deadly, flags, name, p.pc["title"] )
                mortals[#mortals+1] = info
            end
        end
    end
    send("")
    if #mortals > 0 then
        heading("&Y[&WMortals&Y]&B","&B")
        send("")
        for _,v in ipairs(mortals) do
            send(v)
        end
        send("")
    end
    if #immortals > 0 then
        heading("&Y[&WImmortals&Y]&B", "&B")
        send("")
        for _,v in ipairs(immortals) do
            send(v)
        end
    end
    mud.set_char_color(at.blue)
    hyphens()
    fsend("&C%d &Yplayer(s).", #mortals+#immortals)
end
