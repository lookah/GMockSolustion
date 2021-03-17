#include "Employee.h"
#include <iostream>

Employee::Employee()
{
	std::cout << "New employee objecct\n";
}

Employee::Employee(int id, std::string name, float salary)
{
	this->id = id;
	this->name = name;
	this->salary = salary;
}