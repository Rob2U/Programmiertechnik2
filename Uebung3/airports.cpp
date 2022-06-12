#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

// Using a custom struct increases readability compared to using std::pair<float, float> or
// std::array<float, 2>
struct Point
{
	float latitude = 0.0F;
	float longitude = 0.0F;
};

// Calculates the distance between two points on earth specified by longitude/latitude.
// Function taken and adapted from
// http://www.codeproject.com/Articles/22488/Distance-using-Longitiude-and-latitude-using-c
float calculateDistanceBetween(const Point& p1, const Point& p2)
{
	// Up to C++17, there is no constant for PI in the standard, even though support POSIX-API can use M_PI.
	// tarting with C++20 there is a constant in the standard for it: std::numbers::pi
	constexpr double pi = 3.14159265358979323846;

	auto dlat1 = p1.latitude * pi / 180.0;
	auto dlong1 = p1.longitude * pi / 180.0;
	auto dlat2 = p2.latitude * pi / 180.0;
	auto dlong2 = p2.longitude * pi / 180.0;

	auto dLong = dlong1 - dlong2;
	auto dLat = dlat1 - dlat2;

	auto aHarv = std::pow(std::sin(dLat / 2.0), 2.0)
				 + std::cos(dlat1) * std::cos(dlat2) * std::pow(std::sin(dLong / 2.0), 2.0);
	auto cHarv = 2.0 * std::atan2(std::sqrt(aHarv), std::sqrt(1.0F - aHarv));
	// Earth's radius from wikipedia varies between 6,356.750 km and 6,378.135 km
	// The IUGG value for the equatorial radius of the Earth is 6378.137 km
	constexpr double earth = 6378.137;
	return static_cast<float>(earth * cHarv);
}

struct AirportInfo
{
	std::string name;
	std::string city;
	std::string country;
	Point pos;

	std::vector<std::pair<int, int>> routes; // dest_id + numStops
	std::vector<float> routeLengths;
	float averageRouteLength = 0.0F;
};

void importAirportData(const std::string& path, std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Importing airport data..." << std::endl;
	std::ifstream file(path);
	std::string field;
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		int currentID = -1;

		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
					case 0: // id
						currentID = std::stoi(field);
						airportInfo.insert(std::make_pair(currentID, AirportInfo()));
						break;
					case 1: // name
						airportInfo[currentID].name = field;
						break;
					case 2: // city
						airportInfo[currentID].city = field;
						break;
					case 3: // country
						airportInfo[currentID].country = field;
						break;
					case 6: // latitude
						airportInfo[currentID].pos.latitude = std::stof(field);
						break;
					case 7: // longitude
						airportInfo[currentID].pos.longitude = std::stof(field);
						break;
					default:
						break;
				}
			}
			catch (...)
			{}

			fieldNum++;
		}
	}
}

void importRoutesData(const std::string& path, std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Importing routes data..." << std::endl;
	std::ifstream file(path);
	std::string field;
	std::string line;

	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		int sourceID = -1;
		int destID = -1;
		int stops = -1;

		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
					case 3: // source id
						sourceID = std::stoi(field);
						break;
					case 5: // dest id
						destID = std::stoi(field);
						break;
					case 7: // stops
						stops = std::stoi(field);
						break;
					default:
						break;
				}
			}
			catch (...)
			{}

			fieldNum++;
		}
		if (sourceID != -1 && destID != -1 && stops != -1)
		{
			try
			{
				// operator[] doesn't throw in case airport doesn't exists, therefore use at()
				airportInfo.at(sourceID).routes.emplace_back(destID, stops);
			}
			catch (const std::out_of_range&)
			{
				std::cerr << "Source airport with ID " << sourceID << " not present in airport dataset!"
						  << std::endl;
			}
		}
	}
}

// TODO 3.2a - remove all routes from AirportInfo::routes with at least one stop (so that only direct
// flights remain). Use std::remove_if().
void removeNonDirectFlights(std::map<int, AirportInfo>& airportInfo) {
	std::cout << "Remove non-direct flights (i.e., at least one stop)" << std::endl;

	for (auto& airportpair : airportInfo){
		airportpair.second.routes.erase(std::remove_if(airportpair.second.routes.begin(),airportpair.second.routes.end(),
		[&](const std::pair<int,int>& elem){
			return (elem.second > 1);
		 }
		), airportpair.second.routes.end());
	}
}

// TODO 3.2b - For each route in AirportInfo::routes, calculate the distance between start and destination.
// Store the results in AirportInfo::routeLengths. Use std::transform() and calculateDistanceBetween().
void calculateDistancePerRoute(std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Calculate distance for each route" << std::endl;

	for (auto& airportpair : airportInfo) {
		std::transform(airportpair.second.routes.begin(), airportpair.second.routes.end(), std::back_inserter(airportpair.second.routeLengths),
			[&](const std::pair<int, int>& elem) {
				std::cout << "Calculating distance for route " << airportpair.first << " to " <<  elem.first<< std::endl;
				return calculateDistanceBetween(airportpair.second.pos, airportInfo.at(elem.first).pos);
			});
	}

	std::cerr << "Bin da" << std::endl;
}

// TODO 3.2c - Based on AirportInfo::m_routeLengths, calculate for each airport the average distance of
// outgoing routes. Store the results in AirportInfo::averageRouteLength. Use std::accumulate().
void calculateAverageRouteDistances(std::map<int, AirportInfo>& airportInfo)
{
	std::cout << "Calculate average distance for each source airport" << std::endl;
	for (auto& airportpair : airportInfo){
		auto avgCalc = [&](double a, double b){return a+(b/airportpair.second.routeLengths.size());};
		airportpair.second.averageRouteLength = std::accumulate(airportpair.second.routeLengths.begin(), 
		airportpair.second.routeLengths.end(), 0.0, avgCalc);
	}
}

void printResults(std::map<int, AirportInfo>& airportInfo)
{
	for (auto& airport : airportInfo)
	{
		if (!airport.second.routeLengths.empty())
		{
			std::cout << airport.second.name << " (" << airport.second.city << ", " << airport.second.country
					  << "): " << airport.second.averageRouteLength << "km ("
					  << airport.second.routeLengths.size() << " direct outgoing routes)" << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "not enough arguments - USAGE: airports [AIRPORT DATASET] [ROUTES DATASET]" << std::endl;
		return -1; // invalid number of parameters
	}

	static std::map<int, AirportInfo> airportInfo;

	std::cout << "Given path to airports.dat: " << argv[1] << "\n"
			  << "Given path to routes.dat: " << argv[2] << std::endl;

	importAirportData(argv[1], airportInfo);
	importRoutesData(argv[2], airportInfo);

	removeNonDirectFlights(airportInfo);
	calculateDistancePerRoute(airportInfo);
	calculateAverageRouteDistances(airportInfo);
	printResults(airportInfo);

	return 0;
}
