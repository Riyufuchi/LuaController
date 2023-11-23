local teamData = require("lua/teamTable") -- Require the team data file
local tableTools = require("utils/tableTools")

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

function saveTable()
	tableTools.printTableToFile("teamTable", teamData)
end
