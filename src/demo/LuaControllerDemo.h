//==============================================================================
// File       : LuaControllerDemo.h
// Author     : riyufuchi
// Created on : Nov 25, 2023
// Last edit  : Nov 25, 2023
// Copyright  : Copyright (c) 2023, riyufuchi
// Description: LuaController
//==============================================================================

#ifndef SRC_DEMO_LUACONTROLLERDEMO_H_
#define SRC_DEMO_LUACONTROLLERDEMO_H_

#include "../inc/LuaController.h"

namespace LuaDemo
{
class LuaControllerDemo
{
private:
	LuaController::LuaController lua;
	void arraysFromLuaBasicDemo(int index);
	void callingLuaFunctionAvancedDemo();
	void callingLuaFunctionBasicDemo();
	void executingLuaFileBasicDemo();
	void valueTransactionBasicDemo();
	void errorHandelingDemo();
	void basicFuncDemo();
	static int hostFunctionLua(lua_State* L);
public:
	struct TeamMember
	{
		std::string name;
		std::string role;
		std::string joinDate;
		std::string job;
		int id;
	} teamMember;
	LuaControllerDemo();
	virtual ~LuaControllerDemo();
	void runDemo();

};
} /* namespace LuaDemo */
#endif /* SRC_DEMO_LUACONTROLLERDEMO_H_ */
