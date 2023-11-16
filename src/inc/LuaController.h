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
		template <typename Func>
		void registerFunction(const char* functionName, Func func)
		{
			void* funcPtr = reinterpret_cast<void*>(func);
			lua_pushlightuserdata(L, funcPtr);
			lua_pushcclosure(L, &LuaController::luaFunctionWrapper<Func>, 1);
			lua_setglobal(L, functionName);
		}

	bool executeFile(const char* fileName);

	lua_State* getLuaState();
private:
	lua_State* L;

	// Lua C function wrapper for C++ functions
	template <typename Func>
	static int luaFunctionWrapper(lua_State* L)
	{
		Func* func = reinterpret_cast<Func*>(lua_touserdata(L, lua_upvalueindex(1)));
		return callCFunction(L, func);
	}

	// Call the registered C++ function from Lua
	template <typename Func>
	static int callCFunction(lua_State* L, Func* func)
	{
		// Retrieve arguments from Lua stack and call C++ function
		// ...
		// Push the result back to Lua stack
		// ...
		return 1; // Number of return values
	}
};
} // namespace LuaController
#endif /* SRC_LIBRARY_LUACONTROLLER_H_ */
