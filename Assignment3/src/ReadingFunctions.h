#ifndef READINGFUNCTIONS_H_
#define READINGFUNCTIONS_H_
#include "City.h"

class ReadingFunctions {
public:

	void readPackagesFromFile(City[], std::istream &packagesFile,
			int cityLength);
	int findCityIndex(City[], string cityName, int cityLength);
	void readTrucksFromFile(City[], std::istream &trucksFile, int cityLength);
	void readMissions(City[], std::istream &missionsFile, int cityLength,TruckPackage &truckPackage);
	void doMissionOperations(City[], int cityLength, string, string,string, int, int,string,TruckPackage &truckPackage );
	void displayCities(City[], int cityLength);

	void displayLinkedList(TruckPackage &truckPackage);

};

#endif
