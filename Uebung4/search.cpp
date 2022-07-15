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
	for (int i = 0; i < routes.size(); i++) {
		if (routes.at(i).destinationId == destID) {
			numRoutes++;
		}
		numLookups++;
	}

	return numRoutes;
}

// TODO 4.3a - Evaluate the linearSearch function by calling it for every possible destination id.
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
std::pair<long long, long long> evaluateLinearSearch(const RoutesData& routesData)
{
	long long numLookups = 0;
	long long duration = 0;
	
	//min und max DestID finden und anhand diesen suchen, statt destIDs aus Vektor nehmen für Suche (soll so gemacht werden (siehe Forum))
	int minDestID = std::numeric_limits<int>::max();
	int maxDestID = std::numeric_limits<int>::min();
	for (int i = 0; i < routesData.routes.size(); i++) {
		minDestID = std::min(minDestID, routesData.routes.at(i).destinationId);
		maxDestID = std::max(maxDestID, routesData.routes.at(i).destinationId);
	}

	//Zeitmessung + Lookups zählen für alle destIDs zwischen min und maxDestID
	auto start = std::chrono::steady_clock::now();

	for (int i = minDestID; i <= maxDestID; i++) {
		linearSearch(i, routesData.routes, numLookups);
	}

	auto end = std::chrono::steady_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

	return std::make_pair(numLookups, duration);
}

// TODO 4.3b - Return the number of routes for the given destination id based on a binary search. Count the
// number of lookups. The vector should have been sorted before calling this function.
int binarySearch(int destID, const std::vector<Route>& routes, long long& numLookups)
{
	int numRoutes = 0;
	int leftBorder = 0;
	int rightBorder = routes.size() - 1;

	while(leftBorder <= rightBorder) {
		int position = (leftBorder + rightBorder) / 2;
		if(routes.at(position).destinationId == destID) {
			int pos = position;
			while (position < routes.size() && routes.at(position).destinationId == destID){
				numRoutes++;
				numLookups++;
				position++;
			}
			while (pos > 0 && routes.at(pos).destinationId == destID){
				numRoutes++;
				numLookups++;
				pos--;
			}

			return numRoutes;
		}
		if(routes.at(position).destinationId < destID) {
			leftBorder = position + 1;
		} else {
			rightBorder = position - 1;
		}
		numLookups++;
	}

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

	//min und max DestID finden und anhand diesen suchen, statt destIDs aus Vektor nehmen für Suche (soll so gemacht werden (siehe Forum))
	int minDestID = std::numeric_limits<int>::max();
	int maxDestID = std::numeric_limits<int>::min();
	for (int i = 0; i < routesData.routes.size(); i++) {
		minDestID = std::min(minDestID, routesData.routes.at(i).destinationId);
		maxDestID = std::max(maxDestID, routesData.routes.at(i).destinationId);
	}
	//Daten sortieren (Voraussetzung für binarySearch)
	std::sort(routesData.routes.begin(), routesData.routes.end());
	//Zeitmessung + Lookups zählen für alle destIDs zwischen min und maxDestID
	auto start = std::chrono::steady_clock::now();

	for (int i = minDestID; i <= maxDestID; i++) {
		binarySearch(i, routesData.routes, numLookups);
	}
	
	auto end = std::chrono::steady_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

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
