#ifndef CITY_H_
#define CITY_H_
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"

using namespace std;
class CargoItem {
public:
	string itemName;
	string itemType;
	int itemIndex;
};
class City {
public:
	string cityName;
	Stack<CargoItem> cityPackages;
	Queue<CargoItem> cityCargoTrucks;
};

class TruckPackage{
public:
	LinkedList<CargoItem> truckWithPackages;
};

#endif /* CITY_H_ */
