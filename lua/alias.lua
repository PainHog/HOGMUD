-- alias.lua

module (..., package.seeall)

aliases = {}
alias_variables = {}
settings = { ["aliasmsg"] = true, ["varmsg"] = true }

function saving (f)
   f:write ("\n--  Aliases\n\n")
   f:write ((serialize.save ("alias.aliases", aliases)), "\n")
   f:write ("\n--  Alias variables\n\n")
   f:write ((serialize.save ("alias.alias_variables", alias_variables)), "\n")
   f:write ("\n--  Alias settings\n\n")
   f:write ((serialize.save ("alias.settings", settings)), "\n")
end -- saving

function is_alias ( line )
    id, rest = string.match(line, "(%a)(.*)")
    
    return aliases[id] ~= nil
    
end -- end is_alias

--[[ check for existing alias, executes command 
     and returns true if exits, false otherwise --]]
function check_alias ( line )
    id, arg = string.match ( line, "([%a%d]+)(.*)" )
    id = trim(id)
    alias_variables["$arg"] = trim(arg)
   
    if aliases[id] ~= nil then
        if not string.find(aliases[id], "$arg") then
            command = aliases[id] .. " $arg" or ""
        else
            command = aliases[id]
        end
        command = trim(string.gsub (trim(command), "$[%a%d]*", alias_variables))
        char.command(command)
        alias_variables["$arg"] = nil
        return 1
    else
        alias_variables["$arg"] = nil
        return 0
    end    
    
end -- end check_alias

function alias_setvar ( line )
    
    var, value = string.match( line, "([%d%a]+)(.*)" )
    var = "$" .. var
    value = trim(value)
    
    if settings["varmsg"] then
        if alias_variables[var] ~= nil then
            fsend("&WVariable '&Y%s&W' has been set to: &Y%s&D", var, value)
        else
            fsend("&WVariable '&Y%s&W' created with value of: &Y%s&D", var, value)
        end
    end
    alias_variables[var] = value
    
end -- end alias_setvar

function alias_delvar ( line )
    var = "$" .. trim( line )
    
    if alias_variables[var] ~= nil then
        alias_variables[var] = nil
        if settings["varmsg"] then
            fsend("&WVariable '&Y%s&W' has been deleted.&D", var)
        end
    else
        if settings["varmsg"] then
            fsend("&WVariable '&Y%s&W' is not defined.&D", var)
        end
    end
    
end -- end alias_delvar

function alias_list_variables ( )

    var_list = {}
    var_num = 0
    
    for _,v in pairs(alias_variables) do
        var_list[#var_list+1] = string.format("&Y%-10s      &C%s&D", _, v)
        var_num = var_num + 1
    end
    if var_num > 0 then
        send("&WVariable        Value set for variable&D")
        for _,v in ipairs(var_list) do
            send(v)
        end
        fsend("&C%d&W total variables defined.", var_num)
    else
        send("&WYou do not have any variables defined.&D")
    end
        
end -- end alias_list_variables

function alias_create ( line )

    id, cmd = string.match( line, "([%a%d]+)(.*)" )
    id = string.lower(trim(id))
    cmd = trim(cmd)
    
    if settings["aliasmsg"] then
        if aliases[id] ~= nil then
            fsend("&WAlias &Y%s&W has been edited.&D", id)
        else
            fsend("&WAlias &Y%s&W has been created.&D", id)
        end
    end
    aliases[id] = cmd
    -- infinite loop check, do not allow alias to call another alias
    if is_alias(cmd) then
        fsend("&WCannot create alias &Y%s&W: Cannot call an alias within an alias.", id, cmd)
        aliases[id] = nil
    end
    
end -- end alias_create

function alias_delete ( id )

    id = string.lower(trim(id))
    
    if aliases[id] ~= nil then
        aliases[id] = nil
        if settings["aliasmsg"] then
            fsend("&WAlias &Y%s&W has been deleted.&D", id)
        end
    else
        if settings["aliasmsg"] then
            fsend("&WAlias &Y%s&W is not defined.&D", id)
        end
    end
    
end -- end alias_delete

function alias_config ( line )

    toggle, setting = string.match( trim(line), "([+-])(%a*)")
    if not toggle then
        send("&WYour current message settings:")
        for _,v in pairs(settings) do
            if v then
                toggle = "ON"
                punc = "!"
            else
                toggle = "off"
                punc = "."
            end
            fsend("&C%s &Wis &Y%s&W%s", string.upper(_), toggle, punc)
        end
        return
    end
    if string.lower(setting) == "aliasmsg" then
        if toggle == "+" then
            settings["aliasmsg"] = true
            send("&WAlias messages are now &YON&W!")
        else
            settings["aliasmsg"] = false
            send("&WAlias messages are now &Yoff&w.")
        end
        return
    end
    if string.lower(setting) == "varmsg" then
        if toggle == "+" then
            settings["varmsg"] = true
            send("&WVariable messages are now &YON&W!")
        else
            settings["varmsg"] = false
            send("&WVariable messages are now &Yoff&w.")
        end
        return
    end
    send("Invalid setting.")
    
end -- end alias_config

function alias_list ( )
    
    alias_list = {}
    alias_num = 0
    
    for _,v in pairs(aliases) do
        alias_list[#alias_list+1] = string.format("&Y%-10s      &C%s&D", _, v)
        alias_num = alias_num + 1
    end
    if alias_num > 0 then
        send("&WAlias           Command executed by alias&D")
        for _,v in ipairs(alias_list) do
            send(v)
        end
        fsend("&C%d&W total aliases defined.", alias_num)
    else
        send("&WYou do not have any aliases defined.&D")
    end

end -- end alias_list

alias_commands = {
    create = alias_create,
    delete = alias_delete,
    list = alias_list,
    setvar = alias_setvar,
    delvar = alias_delvar,
    variables = alias_list_variables,
    config = alias_config,
    }

function do_alias ( line )

    cmd, arg = string.match ( line, "(%a+)(.*)" )
    
    f = alias_commands[string.lower (cmd or "")]
    if f then
        f ( arg )
    else
        send [[&WAvailable &YALIAS&W commands:
alias create    --> create a new alias
alias delete    --> delete an alias
alias list      --> display a list of created aliases.
alias variables --> display a list of defined variables
alias setvar    --> create or edit a defined variable
alias delvar    --> delete a defined variable
alias config    --> toggle messages on or off

See &YHELP ALIAS&W for more details.&D
]]
    end

end

-- standard saving routine
table.insert (handlers.saving, saving)
