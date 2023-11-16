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

int main()
{
	std::cout << "This is demonstrational program that demonstrate embedding Lua to C++\n" << std::endl;

	std::cout << "Basic functionality:" << std::endl;
	LuaController::LuaController lua;
	lua.executeCodeCLI("print('Hello from Lua!') print('Today is: '..os.date('%d.%m.%Y'))"); // Execute Lua code
	std::cout << "\n";

	std::cout << "Lua error handling:" << std::endl;
	lua.executeCodeCLI("print('Hello'"); // Execute invalid Lua code
	// Executes invalid code with check method that throws and exception
	try
	{
		// Another option: lua.checkLuaException(lua.executeCode("prnt('Test')"));
		lua.checkLuaException(luaL_dostring(lua.getLuaState(), "prnt('Test')"));
	}
	catch (LuaController::LuaException& e)
	{
		std::cout << e.what() << "\n";
	}
	// How to handle error without exceptions and possibly in GUI application
	int res = lua.executeCode("prnt('Test2')");
	if(!lua.checkLua(res))
		std::cout << lua.getErrorMessage(res) << std::endl;
	std::cout << "\n";

	std::cout << "Setting and getting values from C++ to Lua and from Lua to C++:" << std::endl;
	lua.setInteger("currentYear", 2023);
	lua.setBool("b", true);
	lua.setDouble("PI", 3.14);
	lua.setString("msg", "Cpp is the best!");
	std::cout << lua.getInteger("var") << std::endl; // Don't crash and returns default return value 0
	std::cout << lua.getInteger("currentYear") << std::endl;
	std::cout << lua.getBool("b") << std::endl;
	std::cout << lua.getDouble("PI") << std::endl;
	std::cout << lua.getString("msg") << std::endl;
	std::cout << lua.getLuaVersion() << std::endl;
	std::cout << lua.getLuaVerNum() << std::endl;
	std::cout << "\n";

	std::cout << "Executing code from Lua files:" << std::endl;
	lua.executeFileCLI("lua/testLua.lua"); // Executes simple Lua file
	std::cout << "Continue: " << lua.getBool("boolContinue") << std::endl;
	std::cout << "Lua PI: " << lua.getFloat("pi") << std::endl;
	std::cout << "Lua PI (double): " << lua.getDouble("pi") << std::endl;
	std::cout << "Lua version: " << lua.getString("luaVersion") << std::endl;
	std::cout << "\n";

	lua.setLuaModulesCLI("luaFiles/src/");
	lua.executeFileCLI("lua/mathDemo.lua");
	return 0;
}
