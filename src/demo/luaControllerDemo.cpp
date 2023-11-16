//============================================================================
// Name        : CppTesting.cpp
// Author      : Riyufuchi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "../inc/LuaController.h"
//#include "../library/LuaException.h"

int addFunction(int a, int b)
{
	return a + b;
}

int main()
{
	std::cout << "!!!Hello World!!!" << std::endl;
	LuaController::LuaController lua;
	lua.executeCode("print('Hello from Lua Controller!')"); // Execute Lua code
	lua.executeCode("print('Hello'"); // Execute invalid Lua code

	try
	{
		lua.checkLuaOOP(luaL_dostring(lua.getLuaState(), "print('Hello world!)"));
	}
	catch (LuaController::LuaException& e)
	{
		std::cout << e.what() << "\n";
	}

	lua.registerFunction("add", addFunction); // Register C++ function with Lua
	lua.executeCode("result = add(5, 3) print('Result:', result)"); // Execute Lua code that calls the registered C++ function
	lua.executeFile("lua/testLua.lua");

	lua.setLuaModules("luaFiles/src/");
	lua.executeFile("luaFiles/src/programMains/mathDemo.lua");
	return 0;
}
