#include <iostream>
#include "lua.hpp"
#include "Student.cpp"

using namespace std;

int pcf_CreateStudentClassToLua(lua_State* lua)
{
	int age = (int)luaL_checkinteger(lua, 1);
	std::string name = luaL_checkstring(lua, 2);
	int schoolNum = (int)luaL_checkinteger(lua, 3);
	int classNum = (int)luaL_checkinteger(lua, 4);
	// 创建userdata，搞到对象指针
	Student** ppStu = (Student**)lua_newuserdata(lua, sizeof(Student));
	(*ppStu) = new Student(age, name, schoolNum, classNum);
	// 获取元表
	luaL_getmetatable(lua, "Student");
	lua_setmetatable(lua, -2);

	return 1;
}


Student* GetStudent(lua_State* lua, int arg)
{
	// 从栈顶取userdata，这个是C++的对象指针
	luaL_checktype(lua, arg, LUA_TUSERDATA);
	void* userData = luaL_checkudata(lua, arg, "Student");
	luaL_argcheck(lua, userData != NULL, 1, "user data error");
	return *(Student**)userData;
}

int pcf_DeleteStudentClassToLua(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	if (pStu)
		delete pStu;

	return 1;
}

int pcf_SetAge(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	luaL_checktype(lua, -1, LUA_TNUMBER);
	int age = (int)luaL_checkinteger(lua, -1);
	pStu->SetAge(age);
	return 0;
}

int pcf_GetAge(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	const int age = pStu->GetAge();
	lua_pushinteger(lua, age);
	return 1;
}

int pcf_SetName(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	luaL_checktype(lua, -1, LUA_TSTRING);
	std::string name = luaL_checkstring(lua, -1);
	pStu->SetName(name);
	return 0;
}

int pcf_GetName(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);

	const std::string& name = pStu->GetName();
	lua_pushstring(lua, name.c_str());
	return 1;
}

int pcf_ShowSelfInfo(lua_State* lua)
{
	Student* pStu = GetStudent(lua, 1);
	pStu->ShowSelfInfo();
	return 0;
}

static const luaL_Reg method[] = {
	{"SetAge",pcf_SetAge},
	{"GetAge",pcf_GetAge},
	{"SetName",pcf_SetName},
	{"GetName",pcf_GetName},
	{"ShowSelfInfo",pcf_ShowSelfInfo},
	{"Student", pcf_CreateStudentClassToLua },
	{"__gc",pcf_DeleteStudentClassToLua},
	{NULL,NULL}
};

int luaOpenStudent(lua_State* lua)
{
	luaL_newmetatable(lua, "Student");
	lua_pushvalue(lua, -1);
	lua_setfield(lua, -2, "__index");
	luaL_setfuncs(lua, method, 0);
	return 1;
}

static const luaL_Reg libs[] = {
	{"Student",luaOpenStudent},
	{NULL,NULL}
};

void luaRegisterCppStudentLibs(lua_State* lua)
{
	const luaL_Reg* lib = libs;
	for (; lib->func; lib++)
	{
		luaL_requiref(lua, lib->name, lib->func, 1);
		lua_pop(lua, 1);
	}
}

int main()
{
	lua_State* lua = luaL_newstate();
	luaopen_base(lua);
	luaRegisterCppStudentLibs(lua);
	if (luaL_dofile(lua, "src/student.lua"))
		cout << lua_tostring(lua, -1) << endl;

	lua_close(lua);
}