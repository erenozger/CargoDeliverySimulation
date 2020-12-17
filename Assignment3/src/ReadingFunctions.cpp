#include "ReadingFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
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

		citiesList[currentCityIndex].cityCargoTrucks.push(newItem);

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

void ReadingFunctions::displayCities(City citiesList[], int cityLength) {

	for (int i = 0; i < cityLength; i++) {
		cout << citiesList[i].cityName << endl;
		cout << "Packages:" << endl;
		int packageSize = citiesList[i].cityCargoTrucks.size();
		if (packageSize != 0) {
			for (int j = 0; j < packageSize; j++) {
				string takenCargoPacketName;
				takenCargoPacketName =
						citiesList[i].cityCargoTrucks.getCargoPackage(j).itemName;
				cout << takenCargoPacketName << endl;
			}
		}

		cout << "Trucks:" << endl;
		cout << "-------------" << endl;
	}
}
