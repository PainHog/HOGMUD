-- luascript.lua
--[[
        execute Lua scripts written on note objects
        
        2008-01-11
        Darwin @ House of Ghouls MUD
--]]
module (..., package.seeall)

function luascript (line)
	if mud.level() == 65 then 
		cmd, arg = string.match (line, "(%a+)(.*)")
		
		cmd = trim(cmd)
		arg = trim(arg)
		
		if string.lower(cmd) == "run" then
			f = setfenv( assert(loadstring(arg)), _M) ()
			if f then f() end
		end
		if string.lower(cmd) == "ex" then
			t = char.inv()
			if not string.find(arg, ":") then arg = arg .. ":" end
			obj, sname = string.match (arg, "(.*):(.*)")
			if sname == "" then sname = "_text_" end
			found = false
			for k,v in ipairs(t) do
				if v["name"] == obj then
					if v.extra_descriptions[sname] then
						f = setfenv(assert(loadstring(v.extra_descriptions[sname])), _M) ()
						found = true
						if f then f() end
					end
				end
			end
			if found ~= true then send("&RScript '" .. sname .. "' in " .. obj .. " not found.&D") end
		end
	end
end
