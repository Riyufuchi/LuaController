--package.path = package.path .. ";../luaFiles/src/?.lua"
local bi = require("math/binomicDist")
local conUtil = require("utilsCLI/code")

function main()
	local result = 0
	local pX = 0;
	conUtil.createHeader("\v  What is a % chance of getting 2x 6 in 5 dice throws?\v")
	print("p(x) = (5 x) * (1/6)^x * (1 - 1/6)^(5 - x)")
	for i = 2, 5 do
		pX =  bi.distribute(i, 1/6, 5)
		print("p(" .. i ..") = " .. pX .. " => " .. pX * 100 .. "%")
		result = result + pX
	end
	conUtil.createHeader("P(p(2) ⋃  p(3) ⋃  p(4) ⋃  p(5)) = " .. result * 100 .. "%")
end


main()
