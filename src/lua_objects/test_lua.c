#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>

int main(void) {
    lua_State *L = luaL_newstate();
    if (L) {
        luaL_openlibs(L);
        lua_close(L);
        printf("Lua test successful.\n");
    } else {
        printf("Failed to create Lua state.\n");
    }
    return 0;
}

