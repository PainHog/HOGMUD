-- buffer_utils.lua

function gr(list)
    return list[math.random(1, #list)]
end

function sprintf( txt, ... )
    return string.format( txt, ...)
end

function strcat( txt1, txt2 )
    return txt1 .. txt2
end

function get_mflag( i )
    
    if i <= 0 then
        return "&G(&PToken Magic&G) "
    end
    
    if i > 0 and i < 3 then
        return "&G(&PFaint Magic&G) "
    end

    if i >= 3 and i < 7 then
        return "&G(&PWeak Magic&G) "
    end
    
    if i >= 7 and i < 12 then
        return "&G(&PModerate Magic&G) "
    end
    
    if i >= 12 and i < 17 then
        return "&G(&PPotent Magic&G) "
    end
    
    if i >= 17 and i < 25 then
        return "&G(&PPowerful Magic&G) "
    end

    if i >= 25 and i < 35 then
        return "&G(&PArtifact Magic&G) "
    end

    if i >= 35 then
        return "&G(&PGodlike Magic&G) "
    end
end

function str_lower( text )
    return string.lower(text) or ""
end

function str_upper( text )
    return string.upper(text) or ""
end
function one_arg( text )
    arg, rest = string.match(text, "(%S+)(.*)")
    return arg or "", rest or ""
end

function to_number( text )
    return tonumber(text) or 0
end

function get_num_arg( text )
    local num
    local arg
    num, arg = string.match(text, "(%d+)%s(.+)")
    return num or 0, arg or text
end

function show_condition( name, hp, maxhp )
    name = capitalize(name)
    hp = hp or 1
    maxhp = maxhp or 1
    percent = math.min(math.floor(math.max((hp / maxhp)*100, 1)/10) + 1, 11)
    isare = "is"
    hashave = "has"
    
    if name == "You" then 
        isare = "are"
        hashave = "have"
    end
    
    msgs =  {   string.format("%s %s DYING.\n\r", name, isare),
                string.format("%s %s almost dead.\n\r", name, isare),
                string.format("%s %s leaking guts.\n\r", name, isare),
                string.format("%s %s covered in blood.\n\r", name, isare),
                string.format("%s %s bleeding freely.\n\r", name, isare),
                string.format("%s %s many nasty wounds.\n\r", name, hashave),
                string.format("%s %s several wounds.\n\r", name, hashave),
                string.format("%s %s some cuts.\n\r", name, hashave),
                string.format("%s %s a few bruises.\n\r", name, hashave),
                string.format("%s %s slightly scratched.\n\r", name, isare),
                string.format("%s %s in perfect health.\n\r", name, isare),
            }

    return msgs[percent]
end

function swap ( val1, val2 )
    return val2, val1
end

function parse_num( text )
    return tonumber(string.match(text, "%d+")) or 0
end

function parse_bamfout( name, bamf )

    if bamf == "" then
        bamf = "leaves in a swirling mist."
    end
    
    if string.find( bamf, "$n" ) then
        bamf = string.gsub(bamf, "$n", name)
    else
        bamf = string.format("%s %s", name, bamf)
    end
    
    return bamf

end

function parse_bamfin( name, bamf )

    if bamf == "" then
        bamf = "appears in a swirling mist."
    end

    if string.find( bamf, "$n" ) then
        bamf = string.gsub(bamf, "$n", name)
    else
        bamf = string.format("%s %s", name, bamf)
    end
    
    return bamf

end

function show_race_line( name, height, weight )

    t = {isare = "is", weigh = "weighs", feet = height/12, inch = height%12 }
    
    if name == "You" then
        t.isare = "are"
        t.weigh = "weigh"
    end
    
    return string.format("%s %s %d'%d\" and %s %d pounds.\n\r", name, t.isare, t.feet, t.inch, t.weigh, weight)

end

function num_punct( num )
-- code provided by Nick Gammon

  assert (type (num) == "number" or
          type (num) == "string")
  
  local result = ""

  -- split number into 3 parts, eg. -1234.545e22
  -- sign = + or -
  -- before = 1234
  -- after = .545e22

  local sign, before, after =
    string.match (tostring (num), "^([%+%-]?)(%d*)(%.?.*)$")

  -- pull out batches of 3 digits from the end, put a comma before them

  while string.len (before) > 3 do
    result = "," .. string.sub (before, -3, -1) .. result
    before = string.sub (before, 1, -4)  -- remove last 3 digits
  end -- while

  -- we want the original sign, any left-over digits, the comma part,
  -- and the stuff after the decimal point, if any
  return sign .. before .. result .. after
end


