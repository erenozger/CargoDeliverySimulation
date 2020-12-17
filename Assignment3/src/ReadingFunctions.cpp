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
