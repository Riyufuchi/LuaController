-- Require the team data file
local teamData = require("teamTable")

-- Access the 'team' table
function printTeam()
	for _, member in ipairs(teamData) do
	    print("Name:", member.name)
	    print("Role:", member.role)
	    print("Join Date:", member.joinDate)
	    print("Job:", member.job)
	    print("--------------------------")
	end
end

function getTeam()
    return teamData
end

function getTeamMember(ID)
    return teamData[ID]
end

-- Function to convert a table to a string
function tableToString(tbl)
	local keys = {}
    local result = "\t{"
    
    for key, _ in pairs(tbl) do
        table.insert(keys, key)
    end

    -- Sort the keys to maintain order
    table.sort(keys)

    for _, key in ipairs(keys) do
        local value = tbl[key]
        if type(value) == "string" then
            result = result .. key .. '="' .. value .. '", '
        else
            result = result .. key .. "=" .. tostring(value) .. ", "
        end
    end

    -- Remove the trailing comma and space
    result = result:gsub(", $", "")

    result = result .. " }"

    return result
end

function prepLuaTableFile(tableName, table)
	local content = ""
	for i = 1, #table do
		content = content .. tableToString(table[i]) .. "\n"
	end
	local fileContent = "local "..tableName.." = {\n" .. content .. "}\nreturn "..tableName
	return fileContent
end

-- Convert the 'team' table to a string and print it
print(prepLuaTableFile("team", teamData))

