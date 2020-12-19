#include "ReadingFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <functional>

using namespace std;

void ReadingFunctions::readPackagesFromFile(City citiesList[],
		std::istream &packagesFile, int cityLength) {
	string onePackage;
	string packageName;
	string targetCity;
	string wholeLine[2];
	int currentCityIndex;
	while (std::getline(packagesFile, onePackage)) {
		stringstream ss(onePackage);
		int i = 0;
		string parseString;
		while (getline(ss, parseString, ' ')) {
			wholeLine[i] = parseString;
			i++;
		}
		packageName = wholeLine[0];
		targetCity = wholeLine[1];
		currentCityIndex = findCityIndex(citiesList, targetCity, cityLength);
		CargoItem newItem;
		newItem.itemName = packageName;
		newItem.itemType = "package";
		newItem.itemIndex = -1;

		citiesList[currentCityIndex].cityPackages.push(newItem);
		//It separates the cities and cargo packages and finds the
		//city to be sent and performs the push to the stack where the packages are kept.
	}

}

int ReadingFunctions::findCityIndex(City citiesList[], string cityName,
		int cityLength) {
	//Searches the incoming city name in the sequence of all cities,
	//finds its position and returns it.
	int finalIndex;
	for (int i = 0; i < cityLength; i++) {
		if (citiesList[i].cityName == cityName) {
			finalIndex = i;
			break;
		} else {
			finalIndex = -1;
		}
	}
	return finalIndex;
}

void ReadingFunctions::readTrucksFromFile(City citiesList[],
		std::istream &trucksFile, int cityLength) {

	string oneTruck;
	string truckName;
	string targetCity;
	string truckPower;
	string wholeLine[3];
	int currentCityIndex;

	while (std::getline(trucksFile, oneTruck)) {

		stringstream ss(oneTruck);

		int i = 0;
		string parseString;
		while (getline(ss, parseString, ' ')) {
			wholeLine[i] = parseString;
			i++;
		}

		truckName = wholeLine[0];
		targetCity = wholeLine[1];
		truckPower = wholeLine[2];

		currentCityIndex = findCityIndex(citiesList, targetCity, cityLength);


		CargoItem newItem;
		newItem.itemName = truckName;
		newItem.itemType = "truck";
		newItem.itemIndex = -1;

		citiesList[currentCityIndex].cityCargoTrucks.enqueue(newItem);
		//It separates the cities and cargo Trucks and finds the
		//city to be sent and performs the enqueue to the QUEUE where the trucks are kept.
	}

}

void ReadingFunctions::readMissions(City citiesList[],
		std::istream &missionsFile, int cityLength,
		TruckPackage &currentTruck) {
	string wholeMissionLine;
	string startingStation;
	string midwayStation;
	string targetStation;
	int takenCountFromStart;
	int takenCountFromMidway;
	string indicesString;
	string wholeLine[6];

	//A-B-C-x-y-z1,z2,...
	//[A-startingStation] , [B-midwayStation] , [C-targetStation] ,
	//[x-takenPackageCount from Start] ,[y-takenPackageCount from Midway] ,
	//[z1,z2- Indices of passing packages at midway]


	while (std::getline(missionsFile, wholeMissionLine)) {
		stringstream ss(wholeMissionLine);
		int i = 0;
		string parseString;
		while (getline(ss, parseString, '-')) {
			wholeLine[i] = parseString;
			i++;
		}
		startingStation = wholeLine[0];
		midwayStation = wholeLine[1];
		targetStation = wholeLine[2];
		takenCountFromStart = std::stoi(wholeLine[3]);
		takenCountFromMidway = std::stoi(wholeLine[4]);
		indicesString = wholeLine[5];
		doMissionOperations(citiesList, cityLength, startingStation,
				midwayStation, targetStation, takenCountFromStart,
				takenCountFromMidway, indicesString, currentTruck);
	}
	//It breaks the entire task line into 6 main headings
	//and sends it to the function that the action will be applied to.

}
void ReadingFunctions::doMissionOperations(City citiesList[], int cityLength,
		string startingStation, string midwayStation, string targetStation,
		int takenCountFromStart, int takenCountFromMidway, string indicesString,
		TruckPackage &currentTruck) {

	stringstream ss(indicesString);
	int indicesSize = 0;

	string parseString;
	while (getline(ss, parseString, ',')) {
		indicesSize++;
	}
	int indicesArray[indicesSize];

	ss.clear();
	ss.seekg(0, ios::beg);
	int midwayCount = 0;
	while (getline(ss, parseString, ',')) {
		indicesArray[midwayCount] = std::stoi(parseString);
		midwayCount++;
	}

	//First, the array in which the indexes of the packages that need to be
	//delivered at the midway station are kept is created and placed inside.

	//The indexes of the cities used in the mission task are calculated.
	int startingStationIndex = findCityIndex(citiesList, startingStation,
			cityLength);
	int midwayStationIndex = findCityIndex(citiesList, midwayStation,
			cityLength);
	int targetStationIndex = findCityIndex(citiesList, targetStation,
			cityLength);

	//The cargo truck to be used in the task is found and saved on the linkedlist.
	CargoItem cargoTruck;
	citiesList[startingStationIndex].cityCargoTrucks.getFront(cargoTruck);
	currentTruck.truckWithPackages.insertToLL(cargoTruck);
	//The cargo truck used is deleted from the starting city's queue.
	citiesList[startingStationIndex].cityCargoTrucks.dequeue();

	//According to the number of packages received, the packages in the cities
	//are registered on the linked list and deleted from the cities.
	for (int i = 0; i < takenCountFromStart; i++) {
		CargoItem cargoPackage;
		citiesList[startingStationIndex].cityPackages.getTop(cargoPackage);
		cargoPackage.itemIndex = i;
		currentTruck.truckWithPackages.insertToLL(cargoPackage);
		citiesList[startingStationIndex].cityPackages.pop();
	}
	for (int j = takenCountFromStart;
			j < takenCountFromStart + takenCountFromMidway; j++) {
		CargoItem cargoPackage;
		citiesList[midwayStationIndex].cityPackages.getTop(cargoPackage);
		cargoPackage.itemIndex = j;
		currentTruck.truckWithPackages.insertToLL(cargoPackage);
		citiesList[midwayStationIndex].cityPackages.pop();
	}
	;

	//Packages that need to be delivered at the midway station after the entire
	//loading process is completed are first saved one by one in the package stack of midway city.
	for (int z = 0; z < midwayCount; z++) {
		int deleteIndex = indicesArray[z];
		CargoItem currentCargoItem;
		currentCargoItem = currentTruck.truckWithPackages.getLLItem(
				deleteIndex + 1);
		currentCargoItem.itemIndex = -1;
		citiesList[midwayStationIndex].cityPackages.push(currentCargoItem);
	}
	;
	//To make the deletion, the index order is desc sorted.
	sort(indicesArray, indicesArray + indicesSize, std::greater<int>());
	for (int i = 0; i < midwayCount; i++) {
		int deleteIndex = indicesArray[i];
		currentTruck.truckWithPackages.deleteFromLL(deleteIndex);
	}

	//In the final stage, the remaining load is calculated and all loads
	//and cargo truck are delivered to the destination city.
	int lastPackageCount = takenCountFromStart + takenCountFromMidway
			- midwayCount;
	CargoItem currentCargoItem;
	currentCargoItem = currentTruck.truckWithPackages.getLLItem(0);
	citiesList[targetStationIndex].cityCargoTrucks.enqueue(currentCargoItem);
	for (int i = 0; i < lastPackageCount; i++) {
		CargoItem currentCargoItem;
		currentCargoItem = currentTruck.truckWithPackages.getLLItem(1);
		citiesList[targetStationIndex].cityPackages.push(currentCargoItem);
		currentTruck.truckWithPackages.deleteFromLL(0);

	}
	//Linked list is reset.
	currentTruck.truckWithPackages.deleteFromLL(0);

}
void ReadingFunctions::displayCities(City citiesList[], int cityLength,std::ostream &outputFile) {

	for (int i = 0; i < cityLength; i++) {
		outputFile << citiesList[i].cityName << endl;
		outputFile << "Packages:" << endl;
		int packageSize = citiesList[i].cityPackages.size();
		if (packageSize != 0) {
			for (int j = 0; j < packageSize; j++) {
				string takenCargoPacketName;
				takenCargoPacketName =
						citiesList[i].cityPackages.getCargoPackage(j).itemName;
				outputFile << takenCargoPacketName << endl;
			}
		}
		outputFile << "Trucks:" << endl;
		int truckSize = citiesList[i].cityCargoTrucks.size();
		if (truckSize != 0) {
			for (int j = 0; j < truckSize; j++) {
				string takenTruckName;
				takenTruckName =
						citiesList[i].cityCargoTrucks.getTruck(j).itemName;
				outputFile << takenTruckName << endl;
			}

		}
		outputFile << "-------------" << endl;
	}
}

void ReadingFunctions::displayLinkedList(TruckPackage &truckPackage) {
	int llSize = truckPackage.truckWithPackages.size();
	for (int j = 0; j < llSize; j++) {
		string takenItemName;
		int takenItemIndex;
		takenItemName = truckPackage.truckWithPackages.getLLItem(j).itemName;
		takenItemIndex = truckPackage.truckWithPackages.getLLItem(j).itemIndex;
		cout << takenItemName << "(" << takenItemIndex << ")" << "->";
	}
	cout << endl;
}

