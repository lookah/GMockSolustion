#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../GoogleMockProject/Employee.h"
#include "../GoogleMockProject/EmployeeManager.h"
#include "../GoogleMockProject/IDatabaseConnection.h"
#include "../GoogleMockProject//LibraryCode.h"
#include <iostream>

class MockEmployee : public Employee
{
public:
	MockEmployee() = default;
};

class MockDatabaseConnection : public IDatabaseConnection
{
public:
	MockDatabaseConnection(std::string serverAddress);

	MOCK_METHOD(void, connect, ());
	MOCK_METHOD(void, disconnect, ());

	MOCK_METHOD(float, getSalary, (int), (const));
	MOCK_METHOD(void, updateSalary, (int, float));

	MOCK_METHOD(std::vector<Employee>, getSalariesRange, (float), (const));
	MOCK_METHOD(std::vector<Employee>, getSalariesRange, (float, float), (const));

	//When the return type has a comma "," --> std::map<std::string, int>
	MOCK_METHOD((std::map<std::string, int>), doSomething, ());

	void someMemberMethod()
	{
		std::cout << "MEMBER METHOD THROWN ERROR!!\n";
		throw std::runtime_error("memberMethod Error!\n");
	};
};

MockDatabaseConnection::MockDatabaseConnection(std::string serverAddress) : IDatabaseConnection{ serverAddress }
{
	std::cout << "MockDatabaseConnection constructor\n";
}

ACTION(myThrow)
{
	std::cout << "Thorwing an ACTION error :\n!";
	throw std::runtime_error("Dummy action thrown error!!\n");
}

TEST(TestEmployeeManager, TestConnectionError)
{
	MockDatabaseConnection dbConnection("IdiotServer");
	EXPECT_CALL(dbConnection, connect()).WillOnce(myThrow());

	ASSERT_ANY_THROW(EmployeeManager employeeManager(&dbConnection));
}

TEST(TestEmployeeManager, TestConnectionErrorAction)
{
	MockDatabaseConnection dbConnection("IdiotServer");
	EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Throw(std::runtime_error("DummyError")));

	ASSERT_ANY_THROW(EmployeeManager employeeManager(&dbConnection));
}

void someUnrelatedFunction()
{
	std::cout << "INVOKED function to throw an error!!\n";
	throw std::runtime_error("InvokedError\n");
}

TEST(TestEmployeeManager, TestConnectionErrorInvoke)
{
	MockDatabaseConnection dbConnection("IdiotServer");
	EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Invoke(someUnrelatedFunction));

	ASSERT_ANY_THROW(EmployeeManager employeeManager(&dbConnection));
}

TEST(TestEmployeeManager, TestConnectionErrorInvokeLambda)
{
	MockDatabaseConnection dbConnection("IdiotServer");
	EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Invoke(
		[]() 
		{
			std::cout << "LAMBDA INVOKED ERROR!\n";
			throw std::runtime_error("LambdaThrownError");
		}));

	ASSERT_ANY_THROW(EmployeeManager employeeManager(&dbConnection));
}

TEST(TestEmployeeManager, TestConnectionErrorInvokeMemberMethod)
{
	MockDatabaseConnection dbConnection("IdiotServer");
	//std::bind needed, if the method has parameters, add them after the
	//object reference as an additional parameter
	auto boundMemberMethod = std::bind(&MockDatabaseConnection::someMemberMethod, &dbConnection);

	//using InvokedWithoutArgs for bound methods
	EXPECT_CALL(dbConnection, connect()).WillOnce(testing::InvokeWithoutArgs(boundMemberMethod));

	ASSERT_ANY_THROW(EmployeeManager employeeManager(&dbConnection));
}
TEST(TestEmployeeManager, BasicTest) {
	// this uses real functions - a real connection is made
	//IDatabaseConnection dbConnection("myTestServer");
	MockDatabaseConnection dbConnection("MyTestServer");
	EXPECT_CALL(dbConnection, connect());
	EXPECT_CALL(dbConnection, disconnect());
	EmployeeManager employeeManager(&dbConnection);

}

TEST(TestEmployeeManager, TestUpdateSalaryTimesTest) {
	// this uses real functions - a real connection is made
	//IDatabaseConnection dbConnection("myTestServer");
	MockDatabaseConnection dbConnection("MyTestServer");
	EXPECT_CALL(dbConnection, connect());
	EXPECT_CALL(dbConnection, disconnect());
	EXPECT_CALL(dbConnection, updateSalary(50, 20020)).Times(1);

	EmployeeManager employeeManager(&dbConnection);
	employeeManager.setSalary(50, 20020);
}

TEST(TestEmployeeManager, TestGetSalaryReturnTest)
{
	const int employeeId = 40;
	const float employeeSalary = 2000;
	MockDatabaseConnection dbConnection("MyTestServer");
	EXPECT_CALL(dbConnection, connect());
	EXPECT_CALL(dbConnection, disconnect());
	EXPECT_CALL(dbConnection, getSalary(testing::_)).WillOnce(testing::Return(employeeSalary));

	EmployeeManager employeeManager(&dbConnection);
	float returnSalary = employeeManager.getSalary(40);

	ASSERT_EQ(employeeSalary, returnSalary);
}

TEST(TestEmployeeManager, TestGetSalaryInRangeMatchers)
{
	const int low = 100, high = 600;
	std::vector<Employee> returnEmployeeVector{ Employee{1, "John", 300}, 
												Employee{2, "Vesna", 500}, 
												Employee{3, "Luka", 150} };

	MockDatabaseConnection dbConnection("MyTestServer");
	EXPECT_CALL(dbConnection, connect());
	EXPECT_CALL(dbConnection, disconnect());
	EXPECT_CALL(dbConnection, getSalariesRange(100, 600)).WillOnce(testing::Return(returnEmployeeVector));

	EmployeeManager employeeManager(&dbConnection);
	std::map<std::string, float> returnMap = employeeManager.getSalariesBetween(low, high);
	
	//iterate the map to print
	for (auto it = returnMap.begin(); it != returnMap.end(); ++it)
	{
		std::cout << it->first << " " << it->second << "\n";
		ASSERT_THAT(it->second, testing::AllOf(testing::Gt(low), testing::Le(high)));
	}
}

TEST(VectorTests, ElementsAreTest)
{
	std::vector<int> v = generateNumbers(5, 3);
	// this will be 0, 1, 2, 0, 1

	ASSERT_THAT(v, testing::ElementsAre(0, 1, 2, 0, 1));
}

TEST(VectorTests, ElementsLimitTest)
{
	std::vector<int> v = generateNumbers(5, 3);
	// this will be 0, 1, 2, 0, 1

	ASSERT_THAT(v, testing::Each(testing::AllOf(testing::Ge(0), testing::Lt(3))));
}

//Testing callbacks

void realCallback()
{
	std::cout << "Real callback invoked!\n";
}

TEST(TestEmployeeManager, CallbackTest)
{
	MockDatabaseConnection dbConnection("DummyAddress");

	//instead of wrapping a funtion in a class, you can do this:
	testing::MockFunction<void()> mockFunction;

	//then you need to use .AsStdFunction() for compiling
	dbConnection.setOnConnect(mockFunction.AsStdFunction());
	EXPECT_CALL(mockFunction, Call());

	dbConnection.connect();
}