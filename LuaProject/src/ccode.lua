--ccode.lua ÎÄ¼şÄÚÈİ
LuaFileStr = "hello lua string"
LuaFileTable = {name = "HanMei", age = 18}
function LuaFileAdd(n1, n2)
 return (n1 + n2);
end;
function ShowTable()
	print("Name:"..LuaFileTable.name);
	print("Age:"..LuaFileTable.age);
end