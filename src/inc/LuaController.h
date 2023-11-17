//============================================================================
// Name        : LuaController
// Author      : Riyufuchi
// Version     : 1.3
// Created on  : 16.11.2023
// Last Edit   : 17.11.2023
// Copyright   : MIT
// Description : This is Lua controller that simplifies working with embedded Lua
//============================================================================
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
	// Operator
	operator lua_State*() const
	{
		return L;
	}
	// Check methods
	bool checkLua(int result);
	bool checkLuaCLI(int result);
	void checkLuaException(int result);
	// Execute methods
	int executeFile(const char* fileName);
	int executeCode(const char* code);
	bool executeFileCLI(const char* fileName);
	bool executeCodeCLI(const char* code);
	// Setters
	int setLuaModules(const char* path);
	void setLuaModulesCLI(const char* path);
	void setInteger(const char* name, int val);
	void setDouble(const char* name, double val);
	void setBool(const char* name, bool val);
	void setString(const char* name, const char* val);
	// Getters
	int getGlobal(const char* name);
	std::string getErrorMessage(int result);
	std::string getLuaVersion();
	double getLuaVerNum();
	int getInteger(const char* name);
	float getFloat(const char* name);
	double getDouble(const char* name);
	bool getBool(const char* name);
	std::string getString(const char* name);
	lua_State* getLuaState();
private:
	lua_State* L;
};
} // namespace LuaController
#endif /* SRC_LIBRARY_LUACONTROLLER_H_ */
