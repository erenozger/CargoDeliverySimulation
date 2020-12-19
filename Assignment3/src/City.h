#ifndef CITY_H_
#define CITY_H_
#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"

using namespace std;

//Cargo items are divided into 2 as packages and trucks.
//index is dummy data that is not used in functions.
class CargoItem {
public:
	string itemName;
	string itemType;
	int itemIndex;
};

//Each city class consists of its own name, packages within
//the city, and cargo trucks currently in the city.
class City {
public:
	string cityName;
	Stack<CargoItem> cityPackages;
	Queue<CargoItem> cityCargoTrucks;
};

//The linked list class where the packages transported by cargo trucks are kept instantly.
class TruckPackage{
public:
	LinkedList<CargoItem> truckWithPackages;
};

#endif /* CITY_H_ */
