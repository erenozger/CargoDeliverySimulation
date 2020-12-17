#ifndef READINGFUNCTIONS_H_
#define READINGFUNCTIONS_H_
#include "City.h"

class ReadingFunctions {
public:

	void readPackagesFromFile(City [],std::istream& packagesFile,int cityLength);
	int findCityIndex(City [], string cityName,int cityLength);

};

#endif
