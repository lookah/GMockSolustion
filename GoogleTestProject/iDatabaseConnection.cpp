#include "iDatabaseConnection.h"
#include <iostream>

iDatabaseConnection::iDatabaseConnection(std::string serversAddress) : mServerAddress{ serversAddress }
{
}

void iDatabaseConnection::connect()
{
	std::cout << "Connecting to database server: " << mServerAddress << "\n";
}

void iDatabaseConnection::disconnect()
{
	std::cout << "Disconnecting from database server: " << mServerAddress << "\n";
}
