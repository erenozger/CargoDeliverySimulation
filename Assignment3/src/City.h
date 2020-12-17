#ifndef CITY_H_
#define CITY_H_
#include <iostream>
#include "Stack.h"
#include "Queue.h"

using namespace std;
class CargoItem {
public:
	string itemName;
	string itemType;
};
class City {
public:
	string cityName;
	Stack<CargoItem> cityCargoTrucks;
	//Queue<cargoItem> cityPackages;
};

#endif /* CITY_H_ */
