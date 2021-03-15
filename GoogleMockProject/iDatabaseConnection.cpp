#include "iDatabaseConnection.h"
#include <iostream>

IDatabaseConnection::IDatabaseConnection(std::string serversAddress) : mServerAddress{ serversAddress }
{
}

void IDatabaseConnection::connect()
{
	std::cout << "Connecting to database server: " << mServerAddress << "\n";
}

void IDatabaseConnection::disconnect()
{
	std::cout << "Disconnecting from database server: " << mServerAddress << "\n";
}
