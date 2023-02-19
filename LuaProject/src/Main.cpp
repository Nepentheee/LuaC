#include <iostream>
#include "lua.hpp"
#include "Student.cpp"

using namespace std;

extern "C" long long CCode_MyAdd(long long a, long long b)
{
	return a + b;
}

extern "C" int pcf_CCode_MyAdd(lua_State * L)
{
	long long n1 = lua_tointeger(L, -1);
	long long n2 = lua_tointeger(L, -2);
	long long iRet = CCode_MyAdd(n2, n1);
	lua_pushinteger(L, iRet);

	return 1;
}

void Test_CCode_For_Lua(lua_State* L)
{
	cout << "---------------test c code for lua--------------------" << endl;
	lua_register(L, "CCode_MyAdd", pcf_CCode_MyAdd);
	luaL_dostring(L, "print(\"lua add:\"..CCode_MyAdd(100,1000))");

	cout << "---------------test c code for lua--------------------" << endl;
}

void Test_CPP_Call_Lua(lua_State* L)
{
	// lua加载字符，生成lua全局函数LuaCode_MyAdd
	luaL_dostring(L, "function LuaCode_MyAdd(x,y) return x-y end");

	// lua栈和压入数据
	lua_getglobal(L, "LuaCode_MyAdd");
	lua_pushinteger(L, 100);
	lua_pushinteger(L, 200);

	// C调用lua中的函数，2个传入参数，1个返回参数
	lua_call(L, 2, 1);
	cout << "lua function ret: " << lua_tointeger(L, -1) << endl;

	// 栈回到原始状态
	lua_pop(L, 1);
}

void Test_ReadLuaFile(lua_State* L)
{
	if (luaL_dofile(L, "src/ccode.lua"))
	{
		cout << lua_tostring(L, -1) << endl;
		return;
	}

	lua_getglobal(L, "LuaFileAdd");
	lua_pushnumber(L, 200);
	lua_pushnumber(L, 300);
	lua_call(L, 2, 1);
	cout << "lua file function ret:" << lua_tonumber(L, -1) << endl;
	lua_pop(L, 1);

	lua_getglobal(L, "LuaFileStr");
	cout << "lua file str:" << lua_tostring(L, -1) << endl;

	lua_getglobal(L, "LuaFileTable");
	lua_getfield(L, -1, "name");
	cout << "lua file table name:" << lua_tostring(L, -1) << endl;
	lua_getfield(L, -2, "age");
	cout << "lua file table age:" << lua_tonumber(L, -1) << endl;
	lua_getglobal(L, "ShowTable");
	lua_call(L, 0, 0);

	// 修改
	lua_pushstring(L, "Lilei");
	lua_setfield(L, 2, "name");
	lua_getfield(L, 2, "name");
	cout << "lua file new table name:" << lua_tostring(L, -1) << endl;
	lua_getglobal(L, "ShowTable");
	lua_call(L, 0, 0);
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//Test_CPP_Call_Lua(L);
	//Test_ReadLuaFile(L);

	lua_close(L);

	return 0;
}