#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Employee.h"
#include "EmployeeManager.h"

class MockEmployee : public Employee
{
public:
	MockEmployee();
};

class MockDatabaseConnection : public IDatabaseConnection
{
public:
	MockDatabaseConnection(std::string serverAddress);

	MOCK_METHOD(void, connect, ());
	MOCK_METHOD(void, disconnect, ());
};

class MockTest 
{
public:
	MOCK_METHOD(void, SomeMethod, ());
};
TEST(TestCaseName, TestName) {
	MockTest mock;
	EXPECT_CALL(mock, SomeMethod);
	mock.SomeMethod();

	MockEmployee mockingEmp;

	MockDatabaseConnection dbCon("Testing");
	EXPECT_EQ(1, 1);
}