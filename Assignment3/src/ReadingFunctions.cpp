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

	}

}

int ReadingFunctions::findCityIndex(City citiesList[], string cityName,
		int cityLength) {
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
		cout<<"Truck name : "<<truckName<<" ---targetCity : "<<targetCity<<" ---truckPower : "<<truckPower<<endl;

		currentCityIndex = findCityIndex(citiesList, targetCity, cityLength);
		cout<<"buraya da geldi"<<endl;

		CargoItem newItem;
		newItem.itemName = truckName;
		newItem.itemType = "truck";
		newItem.itemIndex = -1;

		citiesList[currentCityIndex].cityCargoTrucks.enqueue(newItem);
		cout<<"enqueue tamamlandý!"<<endl;
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
	cout<<"indicesSize : "<<indicesSize<<endl;
	ss.clear();
	ss.seekg(0, ios::beg);
	int midwayCount = 0;
	while (getline(ss, parseString, ',')) {
		indicesArray[midwayCount] = std::stoi(parseString);
		midwayCount++;
	}
	cout << "indicesArray 0 : " << indicesArray[0] << endl;
	cout << "indicesArray 1 : " << indicesArray[1] << endl;

	int startingStationIndex = findCityIndex(citiesList, startingStation,
			cityLength);
	int midwayStationIndex = findCityIndex(citiesList, midwayStation,
			cityLength);
	int targetStationIndex = findCityIndex(citiesList, targetStation,
			cityLength);
	CargoItem cargoTruck;
	citiesList[startingStationIndex].cityCargoTrucks.getFront(cargoTruck);
	currentTruck.truckWithPackages.insertToLL(cargoTruck);
	citiesList[startingStationIndex].cityCargoTrucks.dequeue();
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
	ReadingFunctions readingFunctions;
	readingFunctions.displayLinkedList(currentTruck);
	for (int z = 0; z < midwayCount; z++) {
		int deleteIndex = indicesArray[z];
		CargoItem currentCargoItem;
		currentCargoItem = currentTruck.truckWithPackages.getLLItem(
				deleteIndex + 1);
		cout << "currentCargoItem.itemName : " << currentCargoItem.itemName
				<< endl;
		currentCargoItem.itemIndex = -1;
		citiesList[midwayStationIndex].cityPackages.push(currentCargoItem);
	}
	;

	sort(indicesArray, indicesArray + indicesSize, std::greater<int>());
	for (int i = 0; i < midwayCount; i++) {
		int deleteIndex = indicesArray[i];
		cout << "deleteIndex : " << deleteIndex << endl;
		currentTruck.truckWithPackages.deleteFromLL(deleteIndex);
	}
	readingFunctions.displayLinkedList(currentTruck);
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
		readingFunctions.displayLinkedList(currentTruck);
	}
	currentTruck.truckWithPackages.deleteFromLL(0);

}
void ReadingFunctions::displayCities(City citiesList[], int cityLength) {

	for (int i = 0; i < cityLength; i++) {
		cout << citiesList[i].cityName << endl;
		cout << "Packages:" << endl;
		int packageSize = citiesList[i].cityPackages.size();
		if (packageSize != 0) {
			for (int j = 0; j < packageSize; j++) {
				string takenCargoPacketName;
				takenCargoPacketName =
						citiesList[i].cityPackages.getCargoPackage(j).itemName;
				cout << takenCargoPacketName << endl;
			}
		}
		cout << "Trucks:" << endl;
		int truckSize = citiesList[i].cityCargoTrucks.size();
		if (truckSize != 0) {
			for (int j = 0; j < truckSize; j++) {
				string takenTruckName;
				takenTruckName =
						citiesList[i].cityCargoTrucks.getTruck(j).itemName;
				cout << takenTruckName << endl;
			}

		}
		cout << "-------------" << endl;
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

