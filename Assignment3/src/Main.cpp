//============================================================================
// Name        : Assignment3.cpp
// Author      : Eren Özger
// Version     : 14
// Student ID  : 21427215
// Description : Stack, Queue Cargo System
//============================================================================

#include <fstream>
#include <string>
#include <iostream>
#include "City.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"
#include "ReadingFunctions.h"

using namespace std;

ReadingFunctions readingFunctions;
int main() {

	ifstream citiesFile("dests.txt");
	ifstream packagesFile("packages.txt");
	ifstream trucksFile("trucks.txt");
	ifstream missionsFile("missions.txt");
	string city;
	string line;

	int cityCount = 0;
	while (std::getline(citiesFile, line)) {
		cityCount += 1;

	}
	int index = 0;
	citiesFile.clear();
	citiesFile.seekg(0, ios::beg);
	City citiesList[cityCount];
	while (std::getline(citiesFile, city)) {
		citiesList[index].cityName = city;
		index += 1;
	}
	TruckPackage currentTruck;
	readingFunctions.readPackagesFromFile(citiesList,packagesFile,cityCount);

	readingFunctions.readTrucksFromFile(citiesList,trucksFile,cityCount);
	cout<<"buraya kadar geldi"<<endl;

	readingFunctions.readMissions(citiesList,missionsFile,cityCount,currentTruck);

	readingFunctions.displayCities(citiesList,cityCount);
	//readingFunctions.displayLinkedList(currentTruck);

	citiesFile.close();
	packagesFile.close();
	trucksFile.close();
	missionsFile.close();
	return 0;
}
