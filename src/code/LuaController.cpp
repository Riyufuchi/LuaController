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
