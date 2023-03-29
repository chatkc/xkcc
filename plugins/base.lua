-- This is here as a placeholder for now. We'll implement the ChatKC protocol
-- as a proof of concept for extensions here. ~Alex

xkcc = {["hooks"] = {}}

function addhook(type, method)
    if xkcc["hooks"][type] == nil then
        xkcc["hooks"][type] = {}
    end
    table.insert(xkcc["hooks"][type], method)
end

-- run this function in c++
-- TODO: find a way to pass data through in a way we can retreive in c++
function runhooks(type)
    if xkcc.hooks[type] == nil then
        print("Attempt to run hooks for unknown type: '" .. type .. "'")
        return
    end
    for index=1, #xkcc.hooks[type] do
        if not xkcc.hooks[type][index] == nil then
            xkcc.hooks[type][index]()
        end
    end
end