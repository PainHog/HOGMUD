#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>

int main(void) {
    lua_State *L = luaL_newstate();  /* opens Lua */
    luaL_openlibs(L);                /* opens the standard libraries */
    lua_close(L);
    printf("Lua test successful.\n");
    return 0;
}

