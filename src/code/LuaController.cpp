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

void LuaController::executeCode(const char* code)
{
	checkLua(luaL_dostring(L, code));
}

void LuaController::setLuaModules(const char* path)
{
	std::string luaCode = "package.path = package.path .. ';";
	luaCode += path;
	luaCode += "?.lua'";
	checkLua(luaL_dostring(L, luaCode.c_str()));
}

bool LuaController::executeFile(const char* fileName)
{
	return checkLua(luaL_dofile(L, fileName));
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

void LuaController::checkLuaOOP(int result)
{
	if (result != LUA_OK)
		throw LuaException(lua_tostring(L, -1));
}

bool LuaController::checkLua(int result)
{
	if (result != LUA_OK)
	{
		std::cerr << lua_tostring(L, -1) << std::endl;
		return false;
	}
	return true;
}
} // namespace LuaController
