#include "iDatabaseConnection.h"
#include <iostream>

IDatabaseConnection::IDatabaseConnection(std::string serversAddress) : mServerAddress{ serversAddress }
{
}

void IDatabaseConnection::connect()
{
	std::cout << "Connecting to database server: " << mServerAddress << "\n";
	//Initilaze real DB Connection
	if (mOnConnect != nullptr)
	{
		std::cout << "Callback was set!\n";
		mOnConnect();
	}
}

void IDatabaseConnection::disconnect()
{
	std::cout << "Disconnecting from database server: " << mServerAddress << "\n";
	//close real Connection
}

void IDatabaseConnection::setOnConnect(Callback onConnect)
{
	mOnConnect = onConnect;
}
