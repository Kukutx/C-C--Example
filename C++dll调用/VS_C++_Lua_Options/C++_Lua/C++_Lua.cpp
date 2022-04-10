#include <iostream>
extern "C" {

#include "lua.h"

#include "lualib.h"

#include "lauxlib.h"

}
using namespace std;
extern "C" static int MYAPI_ShowHello(lua_State * L)
{
    printf("Hello, World\r\n");
    return 1;
}

int main()
{
    int s = 0;
    lua_State* L = luaL_newstate();
    // load the libs
    luaL_openlibs(L);
    // register C function into lua
    lua_pushcclosure(L, MYAPI_ShowHello, 0);
    lua_setglobal(L, "myHello"); //将MYAPI_ShowHello函数注册成myHello的Lua函数名
    luaL_dofile(L, "main.lua");
    lua_close(L);
    system("pause");
}
