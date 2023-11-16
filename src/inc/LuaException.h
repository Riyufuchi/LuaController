/*
 * LuaException.h
 *
 *  Created on: Nov 15, 2023
 *      Author: riyufuchi
 */

#ifndef SRC_LIBRARY_LUAEXCEPTION_H_
#define SRC_LIBRARY_LUAEXCEPTION_H_

//#include <bits/exception.h>
#include <stdexcept>

namespace LuaController {

class LuaException: public std::runtime_error
{
public:
	LuaException(char const* const message) throw();
	virtual ~LuaException();
};

} /* namespace LuaController */

#endif /* SRC_LIBRARY_LUAEXCEPTION_H_ */
