//============================================================================
// Name        : LuaControllerDemo.cpp
// Author      : Riyufuchi
// Version     :
// Copyright   : Your copyright notice
// Description : Demonstrate using Lua controller
//============================================================================

#include <iostream>

#include "inc/LuaController.h"
//#include "../library/LuaException.h"

void basicFuncDemo(LuaController::LuaController& lua);
void errorHandelingDemo(LuaController::LuaController& lua);
void valueTransactionBasicDemo(LuaController::LuaController& lua);
void executingLuaFileBasicDemo(LuaController::LuaController& lua);
void callingLuaFunctionBasicDemo(LuaController::LuaController& lua);
void callingLuaFunctionAvancedDemo(LuaController::LuaController& lua);
void arraysFromLuaBasicDemo(LuaController::LuaController& lua, int index);

struct TeamMember
{
	std::string name;
	std::string role;
	std::string joinDate;
	std::string job;
	int id;
} teamMember;

int hostFunctionLua(lua_State* L)
{
	int x = (int)lua_tonumber(L, 1);
	int y = (int)lua_tonumber(L, 2);
	std::cout << "[C++] called X = " << x << " Y: " << y << std::endl;
	lua_pushnumber(L, x * y);
	return 1; // Number of return values
}

int main()
{
	std::cout << "This is demonstrational program that demonstrate embedding Lua to C++\n" << std::endl;
	LuaController::LuaController lua;

	basicFuncDemo(lua);
	errorHandelingDemo(lua);
	valueTransactionBasicDemo(lua);
	executingLuaFileBasicDemo(lua);
	callingLuaFunctionBasicDemo(lua);
	callingLuaFunctionAvancedDemo(lua);
	arraysFromLuaBasicDemo(lua, 1);
	return 0;
}

void arraysFromLuaBasicDemo(LuaController::LuaController& lua, int index)
{
	//if (!lua.executeFileCLI("lua/teamTable.lua"))
		//return;
	lua.setLuaModulesCLI("lua/");
	if (!lua.executeFileCLI("lua/teamTool.lua"))
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

		//lua_pushstring(lua, "none");
		//lua_setfield(lua, -2, "role");

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
	}
}

void callingLuaFunctionAvancedDemo(LuaController::LuaController& lua)
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

void callingLuaFunctionBasicDemo(LuaController::LuaController& lua)
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

void executingLuaFileBasicDemo(LuaController::LuaController& lua)
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

void valueTransactionBasicDemo(LuaController::LuaController& lua)
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

void errorHandelingDemo(LuaController::LuaController& lua)
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

void basicFuncDemo(LuaController::LuaController& lua)
{
	std::cout << "Basic functionality:" << std::endl;
	lua.executeCodeCLI("print('Hello from Lua!')"); // Execute Lua code
	lua.executeCodeCLI("print('Today is: '..os.date('%d.%m.%Y'))");
	std::cout << "\n";
}
