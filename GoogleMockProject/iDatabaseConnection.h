#pragma once
#include "Employee.h"
#include <string>
#include <vector>
#include <functional>

class IDatabaseConnection
{
public:
	using Callback = std::function<void()>;
	IDatabaseConnection(std::string serverAddress);

	virtual float getSalary(int id) const = 0;
	virtual void updateSalary(int id, float newSalary) = 0;

	virtual std::vector<Employee> getSalariesRange(float low) const = 0;
	virtual std::vector<Employee> getSalariesRange(float low, float high) const = 0;

	virtual void connect();
	virtual void disconnect();

	void setOnConnect(Callback onConnect);

protected:
	std::string mServerAddress;

	Callback mOnConnect;
};

