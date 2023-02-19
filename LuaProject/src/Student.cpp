#pragma once

#include <string>
#include <iostream>
using namespace std;

class Student
{
public:
	Student(int age, const std::string& name, int schoolNum, int classNum) :
		iAge(age), sName(name), iSchoolNum(schoolNum), iClassNum(classNum)
	{
		cout << "Constructor Student" << endl;
	};
	~Student()
	{
		cout << "Destructor Student" << endl;
	}

	void SetAge(int age) { iAge = age; }
	const int GetAge() const { return iAge; }
	void SetName(const std::string& name) { sName = name; }
	const std::string& GetName() const { return sName; }

	virtual void ShowSelfInfo() {
		cout << "Age:" << iAge <<
			" Name:" << sName <<
			" School:" << iSchoolNum <<
			" Class:" << iClassNum << endl;
	};

private:
	int iAge;
	std::string sName;
	int iSchoolNum;
	int iClassNum;
};