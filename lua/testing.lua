-- testing.lua

module (..., package.seeall)

function saving (f)
    f:write ("\n-- Character info\n\n")
    f:write ((serialize.save ("character", char.info())), "\n")
end -- saving

-- standard saving routine
table.insert (handlers.saving, saving)
