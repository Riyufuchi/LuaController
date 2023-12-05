//============================================================================
// Name        : LuaControllerDemo.cpp
// Author      : Riyufuchi
// Version     :
// Copyright   : Your copyright notice
// Description : Demonstrate using Lua controller
//============================================================================

#include <iostream>

#include "demo/LuaControllerDemo.h"
//#include "../library/LuaException.h"

int main()
{
	std::cout << "This is demonstrational part that demonstrate embedding Lua to C++\n" << std::endl;
	LuaDemo::LuaControllerDemo demo;
	demo.runDemo();
}
