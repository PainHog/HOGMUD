-- help.lua

--[[

Help file system main processing
--------------------------------

Author: Darwin of House of Ghouls MUD

--]]

module (..., package.seeall)

DEBUG_HELP = false

-- loader for help to load catagories in the module context
function help_loader (name)
  setfenv (assert (loadfile (
           string.format (systeminfo.LUA_DIR .. "help_%s.lua", name))), _M) ()
end -- help_loader

function init_help ()
  all_helps = {}
  all_entries = {}
  help_loader "information"
  help_loader "versions"
  help_loader "skill"
  help_loader "spell"
  help_loader "rule"
  help_loader "class"
  help_loader "race"
  help_loader "wizhelp"
  help_loader "command"

	-- Make help lookups
	for a, b in pairs (all_helps) do
	  for d, e in ipairs(b.entries) do
		-- set level if none given
		e.level = e.level or 0
	  
		-- set text if none given
		e.text = e.text or ""
	  
		-- set type if none given
		e.htype = e.htype or "info"
		
		-- make keyword lookup tables
		e.keyword = {}
		for _, v in ipairs(e.keywords) do
			all_entries[string.lower(v)] = { etype = e.htype, elevel = e.level, cat = a, num = d }
		end
	  end
	end -- end for all helps
end -- end init_help

function get_catagory_list (catagory)
     local a = {}
	 local len = 0
     for _, h in pairs(all_entries) do
		if h.etype == catagory and char.level() >= h.elevel then
			a[#a+1] = string.upper(_)
			if string.len(_) > len then
				len = string.len(_)
			end
		end
	 end
     table.sort(a)
	 columns = math.floor(80 / (len+2))
     colwidth = math.floor(80 / columns)
     n = 0
     local txt = ""
     for _, name in ipairs(a) do
       n = n + 1
       if n % 2 == 0 then
         txt = txt .. "&C"
       else
         txt = txt .. "&c"
       end
       toadd = name
       toadd = toadd .. (" "):rep(colwidth - #toadd)
       txt = txt .. toadd
       if n % columns == 0 then
         txt = txt .. "\n\r"
       end
     end
  return txt
end -- get_catagory_list

function get_help(what)
	
	kw = string.gsub(trim(string.lower(what)), "['\"]", "")

	if kw == "start" then
		mud.interpret("oldhelp start")
		return
	end

	if kw == "" then
		kw = "summary"
	end
  
	if all_entries[kw] ~= nil then
		h = all_entries[kw]
		i = all_helps[h.cat]
		j = i.entries[h.num]
		return j
	end
  
	-- if we get this far, help file was not found
	-- look for it in original help files
	if DEBUG_HELP then
		e = mud.gethelp(kw)
		if e ~= nil then
			return e
		end
	end
  
	-- didn't find it there either
	-- run search again and look for possible matches
	local matches = {}
	local maxlen = 0
	for _,h in pairs(all_entries) do
		if string.find(string.lower(_), string.lower(kw)) then
			matches[#matches+1] = string.upper(_)
			if string.len(_) > maxlen then
				maxlen = string.len(_)
			end
		end
	end
	table.sort(matches)
	local txt = "&WNo matching help files were found. Possible matches:&D\n\n"
	if #matches > 0 then
		n = 0
		cols = math.floor(80 / (maxlen+2))
		colwidth = math.floor(80 / cols)
		for _, name in ipairs(matches) do
			n = n + 1
			if n % 2 == 0 then
				txt = txt .. "&C"
			else
				txt = txt .. "&c"
			end
			toadd = name
			toadd = toadd .. (" "):rep(colwidth - #toadd)
			txt = txt .. toadd
			if n % cols == 0 then
				txt = txt .. "\n\r"
			end
		end
	else
		txt = "&WNo matching help files were found. No possible matches.&D"
	end
	local f = {}
	f = {
			keywords = {""},
			level = -1,
			htype = "Help file not found",
			text = txt
		}
	return f
  
end -- end get_help

-- command handler
function help (line)
 init_help()
 h = get_help(trim(line))
 if h ~= nil then
   if mud.level() >= h.level then
     if h.level >= 0 then
       keys = "&w" .. string.upper(table.concat(h.keywords, ", ")) .. "&D"
       send(keys)
     end -- if h.level check
     if h.htype == nil then h.htype = "info" end
     if h.htype ~= "catagory" then heading("&W[&B " .. string.upper(h.htype) .. " &W]&Y", "&Y") end
     if type(h.text) == "function" then
     	h.text()
     else
       send("&W", h.text, "&D")
     end
     send_nocr("&Y")
     hyphens()

     if h.see_also ~= nil then
       also = "&CSee also: &Y" .. string.upper(table.concat(h.see_also, "&w, &Y"))
       send(also)
     end
     send("&D")
   end -- if level check
 end -- if not nil
 all_helps = nil
 all_entries = nil
end -- help


