# LuaController

## Table of Contents

- [About](#about)
- [Compilation](#compilation)
- [Documentation](#documentation)

## About

Controller for simplified embedding and controlling Lua from C++. I made this out of boredom so implementation might not be ideal. If you are going to use this Lua controller lib in your application, please give credit to me as well.

## Compilation

1. If you are going to use this library, you still need to incluse liblua.a (This was made for version 5.4.6)
2. Folder **luaFiles** is [my Lua repository](https://github.com/Riyufuchi/Trying-out-Lua) so I will not include it in this reposiry
3. Default path Lua in header file is "../../../lua-5.4.6/src/lua.hpp"

## Documentation

- Methods with CLI extension can be considered save as they check and print error message into CLI
