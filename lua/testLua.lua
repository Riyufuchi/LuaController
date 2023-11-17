function main()
	print("Output from test lua file\nThis file defines:\n\tbool boolContinue\n\tdecimal pi\n \tstring luaVerion")
	boolContinue = true
	pi = math.pi
	luaVersion = _VERSION
end

function power(x, n)
	return x^n
end

function foo(x, y)
	print("[LUA] called X = " .. x .. " Y = " .. y)
	z = cppHostFunction(x * 10, y)
	return z
end

main()
