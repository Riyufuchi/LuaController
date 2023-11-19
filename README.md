# LuaController

## Table of Contents

- [About](#about)
- [Compilation](#compilation)
- [Documentation](#documentation)
- [Donate](#donate)

## About

Controller for simplified embedding and controlling Lua from C++. I made this out of boredom so implementation might not be ideal. If you are going to use this Lua controller lib in your application, please give credit to me as well.

## Compilation

1. If you are going to use this library, you still need to incluse liblua.a (This was made for version 5.4.6)
2. Folder **luaFiles** is [my Lua repository](https://github.com/Riyufuchi/Trying-out-Lua) so I will not include it in this reposiry
3. Default path Lua in header file is "../../../lua-5.4.6/src/lua.hpp"
4. Header files are in this repository **src/inc**
5. You can use makefile to compile it yourself
   ```bash
   git clone https://github.com/Riyufuchi/LuaController.git
   make
   ```

## Documentation

- Methods with CLI extension can be considered save as they check and print error message into CLI

## Donate

I'm a 🇨🇿 student, so a few dollars will be enough. If you are planning to use this library in a commercial application, then it would be fair if you would send more, possibly a small share of 5-10% of monthly profits.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
