/*
 * LuaException.cpp
 *
 *  Created on: Nov 15, 2023
 *      Author: riyufuchi
 */

#include "LuaException.h"

namespace LuaController {

LuaException::LuaException(char const* const message) throw() : std::runtime_error(message)
{
}

LuaException::~LuaException()
{
}

} /* namespace LuaController */
