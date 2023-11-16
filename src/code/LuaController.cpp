/*
 * LuaController.cpp
 *
 *  Created on: Nov 16, 2023
 *      Author: riyufuchi
 */
// LuaController.cpp
#include "../inc/LuaController.h"

namespace LuaController
{
LuaController::LuaController() : L(luaL_newstate())
{
	luaL_openlibs(L);
}

LuaController::~LuaController()
{
	lua_close(L);
}

bool LuaController::executeCodeCLI(const char* code)
{
	return checkLuaCLI(luaL_dostring(L, code));
}

bool LuaController::executeFileCLI(const char* fileName)
{
	return checkLuaCLI(luaL_dofile(L, fileName));
}

int LuaController::executeCode(const char* code)
{
	return luaL_dostring(L, code);
}

int LuaController::executeFile(const char* fileName)
{
	return luaL_dofile(L, fileName);
}

int LuaController::setLuaModules(const char* path)
{
	std::string luaCode = "package.path = package.path .. ';";
	luaCode += path;
	luaCode += "?.lua'";
	return luaL_dostring(L, luaCode.c_str());
}

void LuaController::setLuaModulesCLI(const char* path)
{
	std::string luaCode = "package.path = package.path .. ';";
	luaCode += path;
	luaCode += "?.lua'";
	checkLuaCLI(luaL_dostring(L, luaCode.c_str()));
}

void LuaController::setInteger(const char* name, int val)
{
	lua_pushinteger(L, val);
	lua_setglobal(L, name);
}

void LuaController::setDouble(const char* name, double val)
{
	lua_pushnumber(L, val);
	lua_setglobal(L, name);
}

void LuaController::setBool(const char* name, bool val)
{
	lua_pushboolean(L, val);
	lua_setglobal(L, name);
}

void LuaController::setString(const char* name, const char* val)
{
	lua_pushstring(L, val);
	lua_setglobal(L, name);
}

std::string LuaController::getLuaVersion()
{
	return getString("_VERSION");
}

double LuaController::getLuaVerNum()
{
	std::string ver = getString("_VERSION");
	try
	{
		return std::stod(ver.substr(ver.find(' ') + 1));
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << "Error converting substring to double: " << e.what() << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Error converting substring to double (out of range): " << e.what() << std::endl;
	}
	return 0;
}

int LuaController::getInteger(const char* name)
{
	lua_getglobal(L, name);
	if(lua_isinteger(L, -1))
		return (int)lua_tonumber(L, -1);
	return 0;
}

float LuaController::getFloat(const char* name)
{
	lua_getglobal(L, name);
	if(lua_isnumber(L, -1))
		return (float)lua_tonumber(L, -1);
	return -3.14f;
}

double LuaController::getDouble(const char* name)
{
	lua_getglobal(L, name);
	if(lua_isnumber(L, -1))
		return (double)lua_tonumber(L, -1);
	return -3.14;
}

bool LuaController::getBool(const char* name)
{
	lua_getglobal(L, name);
	if(lua_isboolean(L, -1))
		return lua_toboolean(L, -1);
	return true;
}

std::string LuaController::getString(const char* name)
{
	lua_getglobal(L, name);
	if(lua_isstring(L, -1))
		return lua_tostring(L, -1);
	return "std::string";
}

lua_State* LuaController::getLuaState()
{
	return L;
}

void LuaController::checkLuaException(int result)
{
	if (result != LUA_OK)
		throw LuaException(lua_tostring(L, -1));
}

std::string LuaController::getErrorMessage(int result)
{
	if (result != LUA_OK)
		return lua_tostring(L, -1) ;
	return "No error occured";
}

bool LuaController::checkLua(int result)
{
	if (result != LUA_OK)
		return false;
	return true;
}

bool LuaController::checkLuaCLI(int result)
{
	if (result != LUA_OK)
	{
		std::cerr << lua_tostring(L, -1) << std::endl;
		return false;
	}
	return true;
}
} // namespace LuaController
