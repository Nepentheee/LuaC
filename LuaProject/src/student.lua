print("begin hello lua");
local stu = Student.Student(19,"Li Lei",111,22);
print(stu:GetName());
stu:ShowSelfInfo();
stu:SetAge(18);
stu:SetName("Han Meimei");
stu:ShowSelfInfo();
print("end hello lua");