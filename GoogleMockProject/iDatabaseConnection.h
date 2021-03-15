#pragma once
#include "Employee.h"
#include <string>
#include <vector>

class IDatabaseConnection
{
public:
	IDatabaseConnection(std::string serverAddress);

	//virtual float getSalary(int id) const = 0;
	//virtual void updateSalary(int id, float newSalary) = 0;

	//virtual std::vector<Employee> getSalariesRange(float low) const = 0;
	//virtual std::vector<Employee> getSalariesRange(float low, float high) const = 0;

	virtual void connect();
	virtual void disconnect();

protected:
	std::string mServerAddress;
};

