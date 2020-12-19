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
int main(int argc, char *argv[]) {

	/*ifstream citiesFile("dests.txt");
	ifstream packagesFile("packages.txt");
	ifstream trucksFile("trucks.txt");
	ifstream missionsFile("missions.txt");
	ofstream outputFile;
	outputFile.open("result.txt");*/

	ifstream citiesFile(argv[1]);
	ifstream packagesFile(argv[2]);
	ifstream trucksFile(argv[3]);
	ifstream missionsFile(argv[4]);
	ofstream outputFile;
	outputFile.open(argv[5]);

	string city;
	string line;

	//Calculates the total number of cities in the document.
	int cityCount = 0;
	while (std::getline(citiesFile, line)) {
		cityCount += 1;

	}
	int index = 0;
	citiesFile.clear();
	citiesFile.seekg(0, ios::beg);
	City citiesList[cityCount];
	//It forms the sequence of the class in which all the cities and
	//packages and cargo trucks within the cities are kept.
	while (std::getline(citiesFile, city)) {
		citiesList[index].cityName = city;
		index += 1;
	}

	//Creates the linked list class in which cargo trucks and packages are kept.
	TruckPackage currentTruck;

	//It reads all packages and saves them to the package storage STACK of the required cities.
	readingFunctions.readPackagesFromFile(citiesList, packagesFile, cityCount);

	//It reads all trucks and saves them to trucks storage QUEUE of the required cities.
	readingFunctions.readTrucksFromFile(citiesList, trucksFile, cityCount);

	//It reads all the missions one by one and performs their operations sequentially.
	readingFunctions.readMissions(citiesList, missionsFile, cityCount,
			currentTruck);

	//Prints the last state of all cities to the output file.
	readingFunctions.displayCities(citiesList, cityCount, outputFile);


	//readingFunctions.displayLinkedList(currentTruck); //unused Display linked list of cargo trucks and packages.

	citiesFile.close();
	packagesFile.close();
	trucksFile.close();
	missionsFile.close();
	outputFile.close();
	return 0;
}
