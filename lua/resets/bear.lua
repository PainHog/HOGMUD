-- reset area bear.are
function reset_bear ()
    
    function g_rdm(tbl)
        return tbl[math.random(#tbl)]
    end
    
    local bcub = {  {   name    = "small bear cub",
                        short   = "a small bear cub",
                        long    = "A small bear cub growls at you."},
                    {   name    = "bear cub",
                        short   = "a bear cub",
                        long    = "A bear cub growls at you."},
                    {   name    = "hungry bear cub",
                        short   = "a hungry bear cub",
                        long    = "A hungry bear cub is surprised by your presence."},
                    {   name    = "angry bear cub",
                        short   = "an angry bear cub",
                        long    = "This bear cub seems aggitated and looking for its mother."},
                    {   name    = "tired bear cub",
                        short   = "a tired bear cub",
                        long    = "Ready for hibernation, this bear cub lazily moves around the cave."}}
                        
    local blarge = {{   name    = "large bear",
                        short   = "a large bear",
                        long    = "A large bear growls at you in rage."},
                    {   name    = "large white bear",
                        short   = "a large white bear",
                        long    = "A large white bear roars at your presence."},
                    {   name    = "lazy sleepy large bear",
                        short   = "a large, lazy bear",
                        long    = "A rather large bear is looking for a nice place to curl up."}}
                        
    oinv(7056, 7074, 1) -- skeleton
    oinv(7055, 7074, 1) -- skeleton
    oinv(7054, 7073, 1) -- skeleton
    oinv(7053, 7059, 1) -- skeleton
    oinv(7052, 7053, 1) -- skeleton
    minv(7063, 7074, 1, 1, {}, { 7051 }) -- white ice bear with robe
    minv(7062, 7073, 1, 1, {}, {}, g_rdm(blarge)) -- large bear
    minv(7061, 7073, 1, 1, {}, {}, g_rdm(blarge)) -- large bear
    minv(7058, 7073, 1, 1, {}, {}, g_rdm(blarge)) -- large bear
    minv(7059, 7057, 1, 1, {}, {}, g_rdm(blarge)) -- large bear
    minv(7051, 7052, 1, 1, {}, {}, g_rdm(bcub)) -- bear cub
    minv(7052, 7054, 1, 1, {}, {}, g_rdm(bcub)) -- bear cub
    minv(7053, 7055, 1, 1, {}, {}, g_rdm(bcub)) -- bear cub
    minv(7054, 7057, 1, 1, {}, {}, g_rdm(bcub)) -- bear cub
    minv(7055, 7058, 1, 1, {}, {}, g_rdm(bcub)) -- bear cub
    minv(7056, 7066, 1, 1, {}, {}, g_rdm(bcub)) -- bear cub
    minv(7057, 7070, 1, 1, {}, {}, g_rdm(bcub)) -- bear cub
    minv(7060, 7056, 1, 1, {}, {}, g_rdm(blarge)) -- large bear

end
