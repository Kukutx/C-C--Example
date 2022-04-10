# 在自己的工程中嵌入Lua脚本引擎

嵌入Lua

编译好lualib后，就可以配合头文件，在自己的C++程序中调用Lua了，以下是一个简单例子，它加载并执行一个Lua脚本"hello,lua"：

```cpp
    extern "C" {
    #include "LuaHeader/lua.h"
    #include "LuaHeader/lualib.h"
    #include "LuaHeader/lauxlib.h"
    }

    int main(int argc, char *argv[])
    {
        int s = 0;
        lua_State *L = lua_open();
        // load the libs
        luaL_openlibs(L);
        //run a Lua scrip here
        luaL_dofile(L, "hello.lua");
        lua_close(L);
        return 1;
    }
```

因为Lua是C语言写的，为了链接正常，注意要**extern "C"**。以下是hello.lua脚本的内容，它也可以修改为其它符合lua语法的脚本：

```lua
    io.write("Please enter your name: ")
    name = io.read()
    io.write("Hi " .. string.format("%s",name) .. ", enjoy hacking with Lua\r\n");
```

# 用Lua中调用C++程序的函数

lua常被选为各大程序的内嵌脚本语言的原因，就是它可以将C++ program的函数，注册为API供lua调用，这样可以使编程的逻辑易于调整。以下是一个特别简单的例子：

```cpp
    // function type must be lua_CFunction
    extern "C" static int MYAPI_ShowHello(lua_State *L)
    {
        printf("Hello, World\r\n");
        return 1;
    }

    int main(int argc, char *argv[])
    {
        int s = 0;
        lua_State *lua = lua_open();
        // load the libs
        luaL_openlibs(lua);
        // register C function into lua
        lua_pushcclosure(lua, MYAPI_ShowHello, 0);
        lua_setglobal(lua, "myHello");
        //run a Lua scrip here
        luaL_dofile(lua, "hello.lua");
        lua_close(lua);
        return 1;
    }
```

通过以上pushcclosure与setglobal的注册，在lua中可以通过调用"myHello"来间接调用host程序的MYAPI_ShowHello函数。

```lua
"hello.lua"中的内容：

    myHello()
```