#pragma once
#include <string>
class Employee
{
public:
	Employee();
	Employee(int id, std::string name, float salary);
	int id; 
	float salary; 
	std::string name; 
};

