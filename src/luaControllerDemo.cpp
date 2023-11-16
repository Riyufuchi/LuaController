//============================================================================
// Name        : CppTesting.cpp
// Author      : Riyufuchi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "inc/LuaController.h"
//#include "../library/LuaException.h"

int addFunction(int a, int b)
{
	return a + b;
}

int main()
{
	std::cout << "This is demonstrational program that demonstrated embedding Lua to C++" << std::endl;
	LuaController::LuaController lua;
	lua.executeCode("print('Hello from Lua!') print('Today is: '..os.date('%d.%m.%Y'))"); // Execute Lua code
	lua.executeCode("print('Hello'"); // Execute invalid Lua code
	// Executes invalid code with check method that throws and exception
	try
	{
		lua.checkLuaOOP(luaL_dostring(lua.getLuaState(), "print('Hello world!)"));
	}
	catch (LuaController::LuaException& e)
	{
		std::cout << e.what() << "\n";
	}
	std::cout << "\n";

	lua.registerFunction("add", addFunction); // Register C++ function with Lua
	lua.executeCode("result = add(5, 3)"); // Execute Lua code that calls the registered C++ function
	std::cout << "Lua calculated: " << lua.getInteger("result") << std::endl; // Gets result from Lua
	std::cout << "\n";

	lua.executeFile("lua/testLua.lua"); // Executes simple Lua file
	std::cout << "Continue: " << lua.getBool("boolContinue") << std::endl;
	std::cout << "Lua PI: " << lua.getFloat("pi") << std::endl;
	std::cout << "Lua PI (double): " << lua.getDouble("pi") << std::endl;
	std::cout << "Lua version: " << lua.getString("luaVersion") << std::endl;
	std::cout << "\n";

	lua.setLuaModules("luaFiles/src/");
	lua.executeFile("luaFiles/src/programMains/demo.lua");
	return 0;
}
