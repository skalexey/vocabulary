// main.cpp : Defines the entry point for the application.
//
#include <iostream>
extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

bool CheckLua(lua_State *L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}


int lua_Test(lua_State *L)
{
	float a = (float)lua_tonumber(L, 1);
	float b = (float)lua_tonumber(L, 2);
	std::cout << "Test(" << a << ", " << b << ") called from Lua" << std::endl;
	float c = a * b;
	lua_pushnumber(L, c);
	return 1;
}

int main(int argc, char* argv[])
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	// Registerations
	lua_register(L, "Test", lua_Test);

	// Script loading
	if(CheckLua(L, luaL_dofile(L, "random_words.lua")))
	{
	}

	lua_close(L);
}