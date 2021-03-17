#include "LibraryCode.h"

#include <math.h>
#include <stdexcept>
#include <iostream>
#include <vector>

std::vector<int> generateNumbers(int n, int limit)
{
	std::vector<int> result;
	if (limit <= 0)
	{
		throw std::runtime_error("Limit is 0 or below!\n");
	}
	for (int i = 0; i < n; i++)
	{
		result.push_back(i % limit);
	}
	return result; 
}
