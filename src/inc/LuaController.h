/*
 * LuaController.h
 *
 *  Created on: Nov 16, 2023
 *  Author: riyufuchi
 */

#ifndef SRC_LIBRARY_LUACONTROLLER_H_
#define SRC_LIBRARY_LUACONTROLLER_H_

#include <iostream>
#include "../../../lua-5.4.6/src/lua.hpp"
#include "LuaException.h"

namespace LuaController
{
class LuaController
{
public:
	LuaController();
	~LuaController();

	void executeCode(const char* code);
	void setLuaModules(const char* path);

	void checkLuaOOP(int result);
	bool checkLua(int result);

	// Register a C++ function as a Lua function
	template <typename Func> void registerFunction(const char* functionName, Func func)
	{
		void* funcPtr = reinterpret_cast<void*>(func);
		lua_pushlightuserdata(L, funcPtr);
		lua_pushcclosure(L, &LuaController::luaFunctionWrapper<Func>, 1);
		lua_setglobal(L, functionName);
	}

	bool executeFile(const char* fileName);

	int getInteger(const char* name);
	float getFloat(const char* name);
	double getDouble(const char* name);
	bool getBool(const char* name);
	std::string getString(const char* name);
	lua_State* getLuaState();
private:
	lua_State* L;

	// Lua C function wrapper for C++ functions
	template <typename Func> static int luaFunctionWrapper(lua_State* L)
	{
		lua_touserdata(L, lua_upvalueindex(1));
		return 1;
	}
};
} // namespace LuaController
#endif /* SRC_LIBRARY_LUACONTROLLER_H_ */
