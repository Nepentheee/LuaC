#include <iostream>
#include "lua.hpp"

using namespace std;

extern "C" long long CCode_MyAdd(long long a, long long b)
{
	return a + b;
}

extern "C" int pcf_CCode_MyAdd(lua_State * lua)
{
	long long n1 = lua_tointeger(lua, -1);
	long long n2 = lua_tointeger(lua, -2);
	long long iRet = CCode_MyAdd(n2, n1);
	lua_pushinteger(lua, iRet);

	return 1;
}

void Test_CCode_For_Lua()
{
	cout << "---------------test c code for lua--------------------" << endl;
	lua_State* lua = luaL_newstate();
	luaL_openlibs(lua);
	lua_register(lua, "CCode_MyAdd", pcf_CCode_MyAdd);
	luaL_dostring(lua, "print(\"lua add:\"..CCode_MyAdd(100,1000))");

	lua_close(lua);
	cout << "---------------test c code for lua--------------------" << endl;
}

int main()
{
	Test_CCode_For_Lua();
}