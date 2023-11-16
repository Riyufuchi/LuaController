/*
 * LuaController.h
 *
 *  Created on: Nov 15, 2023
 *      Author: riyufuchi
 */

#ifndef LUACONTROLLER_H_
#define LUACONTROLLER_H_

#include <iostream>
#include "../../../lua-5.4.6/src/lua.hpp"
#include "LuaException.h"

namespace LuaController
{
class LuaController
{
public:
	LuaController() : L(luaL_newstate())
	{
		luaL_openlibs(L);
	}

	void executeCode(const char* code)
	{
		checkLua(luaL_dostring(L, code));
	}

	void setLuaModules(const char* path)
	{
		std::string luaCode = "package.path = package.path .. ';";
		luaCode += path;
		luaCode += "?.lua'";
		checkLua(luaL_dostring(L, luaCode.c_str()));
	}

	// Register a C++ function as a Lua function
	template <typename Func> void registerFunction(const char* functionName, Func func)
	{
		void* funcPtr = reinterpret_cast<void*>(func);
		lua_pushlightuserdata(L, funcPtr);
		lua_pushcclosure(L, &LuaController::luaFunctionWrapper<Func>, 1);
		lua_setglobal(L, functionName);
	}

	bool executeFile(const char* fileName)
	{
		return checkLua(luaL_dofile(L,fileName));
	}

	void checkLuaOOP(int result)
	{
		if (result != LUA_OK)
			throw LuaException(lua_tostring(L, -1));
	}

	bool checkLua(int result)
	{
		if (result != LUA_OK)
		{
			std::cout << lua_tostring(L, -1) << std::endl;
			return false;
		}
		return true;
	}

	lua_State* getLuaState()
	{
		return L;
	}

	~LuaController()
	{
		lua_close(L);
	}
private:
	lua_State* L;

	// Lua C function wrapper for C++ functions
	template <typename Func> static int luaFunctionWrapper(lua_State* L)
	{
		Func* func = reinterpret_cast<Func*>(lua_touserdata(L, lua_upvalueindex(1)));
		return callCFunction(L, func);
	}

	// Call the registered C++ function from Lua
	template <typename Func> static int callCFunction(lua_State* L, Func* func)
	{
		return 1;
	}
};
}
#endif /* LUACONTROLLER_H_ */
