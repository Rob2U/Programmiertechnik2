#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Route
{
	int airlineId = -1;
	int sourceId = -1;
	int destinationId = -1;
};

struct RoutesData
{
	std::vector<Route> routes;
	int minAirlineId = std::numeric_limits<int>::max();
	int maxAirlineId = std::numeric_limits<int>::min();
};

bool operator<(const Route& r1, const Route& r2)
{
	return r1.destinationId < r2.destinationId;
}

RoutesData importRoutesData(const std::string& path)
{
	RoutesData routesData;

	std::cout << "Importing routes data..." << std::endl;

	std::ifstream file(path);
	std::string field;
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		Route route;

		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
					case 1: // airline id
						route.airlineId = std::stoi(field);
						break;
					case 3: // source id
						route.sourceId = std::stoi(field);
						break;
					case 5: // dest id
						route.destinationId = std::stoi(field);
						break;
					default:
						break;
				}
			}
			catch (...)
			{}

			fieldNum++;
		}
		if (route.airlineId > -1 && route.sourceId > -1 && route.destinationId > -1)
		{
			routesData.routes.push_back(route);
			routesData.maxAirlineId = std::max(routesData.maxAirlineId, route.airlineId);
			routesData.minAirlineId = std::min(routesData.minAirlineId, route.airlineId);
		}
	}

	return routesData;
}

// TODO 4.3a - Return the number of routes for the given destination id based on a linear search. Count the
// number of lookups.
int linearSearch(int destID, const std::vector<Route>& routes, long long& numLookups)
{
	int numRoutes = 0;

	return numRoutes;
}

// TODO 4.3a - Evaluate the linearSearch function by calling it for every possible destination id.
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
std::pair<long long, long long> evaluateLinearSearch(const RoutesData& routesData)
{
	long long numLookups = 0;
	long long duration = 0;

	return std::make_pair(numLookups, duration);
}

// TODO 4.3b - Return the number of routes for the given destination id based on a binary search. Count the
// number of lookups. The vector should have been sorted before calling this function.
int binarySearch(int destID, const std::vector<Route>& routes, long long& numLookups)
{
	return 0;
}

// TODO 4.3b - Evaluate the binarySearch function by calling it for every possible destination id.
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
// Attention: sorting is *not* part of the evaluation and should be conducted beforehand.
std::pair<long long, long long> evaluateBinarySearch(RoutesData& routesData)
{
	long long numLookups = 0;
	long long duration = 0;

	return std::make_pair(numLookups, duration);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "not enough arguments - USAGE: sort [ROUTE DATASET]" << std::endl;
		return -1; // invalid number of parameters
	}
	std::cout << "Given path to routes.csv: " << argv[1] << std::endl;

	auto routesData = importRoutesData(argv[1]);

	auto result = evaluateLinearSearch(routesData);
	std::cout << "Lookups: " << result.first << "; Time: " << result.second << " ms" << std::endl;
	result = evaluateBinarySearch(routesData);
	std::cout << "Lookups: " << result.first << "; Time: " << result.second << " ms" << std::endl;

	return 0;
}
