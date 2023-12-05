//==============================================================================
// File       : LuaControllerDemo.cpp
// Author     : riyufuchi
// Created on : Nov 25, 2023
// Last edit  : Nov 25, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: LuaController
//==============================================================================

#include "LuaControllerDemo.h"

namespace LuaDemo
{
LuaControllerDemo::LuaControllerDemo()
{
}

LuaControllerDemo::~LuaControllerDemo()
{
}
void LuaControllerDemo::runDemo()
{
	basicFuncDemo();
	errorHandelingDemo();
	valueTransactionBasicDemo();
	executingLuaFileBasicDemo();
	callingLuaFunctionBasicDemo();
	callingLuaFunctionAvancedDemo();
	arraysFromLuaBasicDemo(1);
}
void LuaControllerDemo::arraysFromLuaBasicDemo(int index)
{
	//if (!lua.executeFileCLI("lua/teamTable.lua"))
		//return;
	lua.setLuaModulesCLI("lua/");
	if (!lua.executeFileCLI("lua/teamTools.lua"))
		return;
	lua.getGlobal("getTeamMember");
	if (!lua_isfunction(lua, -1))
		return;
	lua_pushnumber(lua, index);
	if (!lua.checkLuaCLI(lua.callFunction(1, 1, 0)))
		return;
	//TeamMember mem1;
	if (lua_istable(lua, -1))
	{
		lua_getfield(lua, -1, "id");
		teamMember.id = lua_tonumber(lua, -1);
		lua_pop(lua, 1);
		lua_pushstring(lua, "name");
		lua_gettable(lua, -2);
		teamMember.name = lua_tostring(lua, -1);
		lua_pop(lua, 1);

		teamMember.role = lua.getStringField("role");
		teamMember.joinDate = lua.getStringField("joinDate");
		teamMember.job = lua.getStringField("job");

		std::cout << "\n" << std::endl;
		std::cout << "ID: " << teamMember.id << std::endl;
		std::cout << "Name: " << teamMember.name << std::endl;
		std::cout << "Role: " << teamMember.role << std::endl;
		std::cout << "Join Date: " << teamMember.joinDate << std::endl;
		std::cout << "Job: " << teamMember.job << std::endl;

		lua.setStringField("role", "none");
		lua.setStringField("job", "none");
		teamMember.role = lua.getStringField("role");
		teamMember.job = lua.getStringField("job");

		std::cout << "\n" << std::endl;
		std::cout << "ID: " << teamMember.id << std::endl;
		std::cout << "Name: " << teamMember.name << std::endl;
		std::cout << "Role: " << teamMember.role << std::endl;
		std::cout << "Join Date: " << teamMember.joinDate << std::endl;
		std::cout << "Job: " << teamMember.job << std::endl;

		if (!lua.checkLuaCLI(lua.callFunction("saveTable",0, 0, 0)))
				return;
		std::cout << "\nData successfully saved\n";
	}
}
int LuaControllerDemo::hostFunctionLua(lua_State* L)
{
	int x = (int)lua_tonumber(L, 1);
	int y = (int)lua_tonumber(L, 2);
	std::cout << "[C++] called X = " << x << " Y: " << y << std::endl;
	lua_pushnumber(L, x * y);
	return 1; // Number of return values
}
void LuaControllerDemo::callingLuaFunctionAvancedDemo()
{
	lua_register(lua, "cppHostFunction", hostFunctionLua);
	lua.getGlobal("foo");
	if (lua_isfunction(lua, -1))
	{
		lua_pushnumber(lua, 2);
		lua_pushnumber(lua, 6);
		if (lua.checkLua(lua_pcall(lua, 2, 1, 0)))
		{
			std::cout << "Result from Lua function: " << lua_tonumber(lua, -1) << std::endl;
		}
	}
}
void LuaControllerDemo::callingLuaFunctionBasicDemo()
{
	// First we need to execute Lua file with our desired function
	// our is was called in executingLuaFileBasicDemo method).
	lua.getGlobal("power");
	if (lua_isfunction(lua, -1))
	{
		lua_pushnumber(lua, 2);
		lua_pushnumber(lua, 6);
		if (lua.checkLua(lua_pcall(lua, 2, 1, 0)))
		{
			std::cout << "Result from Lua function: " << lua_tonumber(lua, -1) << std::endl;
		}
	}
}
void LuaControllerDemo::executingLuaFileBasicDemo()
{
	std::cout << "Executing code from Lua files:" << std::endl;
	lua.executeFileCLI("lua/testLua.lua"); // Executes simple Lua file
	std::cout << "Continue: " << lua.getBool("boolContinue") << std::endl;
	std::cout << "Lua PI: " << lua.getFloat("pi") << std::endl;
	std::cout << "Lua PI (double): " << lua.getDouble("pi") << std::endl;
	std::cout << "Lua version: " << lua.getString("luaVersion") << std::endl;
	std::cout << "\n";

	lua.setLuaModulesCLI("luaFiles/src/");
	lua.executeFileCLI("lua/mathDemo.lua");
	std::cout << "\n";
}
void LuaControllerDemo::valueTransactionBasicDemo()
{
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
}
void LuaControllerDemo::errorHandelingDemo()
{
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
}
void LuaControllerDemo::basicFuncDemo()
{
	std::cout << "Basic functionality:" << std::endl;
	lua.executeCodeCLI("print('Hello from Lua!')"); // Execute Lua code
	lua.executeCodeCLI("print('Today is: '..os.date('%d.%m.%Y'))");
	std::cout << "\n";
}
} /* namespace NPCs */
