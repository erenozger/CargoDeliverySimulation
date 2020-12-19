#ifndef READINGFUNCTIONS_H_
#define READINGFUNCTIONS_H_
#include "City.h"

class ReadingFunctions {
public:

	//A function that places all packages in the required cities in the system.
	void readPackagesFromFile(City[], std::istream &packagesFile,
			int cityLength);

	//The function that accesses the name of the city from the array the cities are in.
	int findCityIndex(City[], string cityName, int cityLength);

	//A function that places all trucks in the required cities in the system.
	void readTrucksFromFile(City[], std::istream &trucksFile, int cityLength);

	//A function that reads and parse entire mission lines.
	void readMissions(City[], std::istream &missionsFile, int cityLength,TruckPackage &truckPackage);

	//Function that implements the fragmented task line step by step.
	void doMissionOperations(City[], int cityLength, string, string,string, int, int,string,TruckPackage &truckPackage );

	//Prints the last state of all cities to the output file.
	void displayCities(City[], int cityLength,std::ostream &outputFile);

	//Unused test function.
	void displayLinkedList(TruckPackage &truckPackage);

};

#endif
