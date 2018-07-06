#pragma once

/*
* Filnamn: DataFilter.h
* Labb 4 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Innehåller klassen DataFilter. Används för att läsa nästa värde
* och filtrera bort värden som ligger utanför intervall.
*
*/

#include <string>
#include <iostream>
#include <fstream>
#include "DataFileReader.h"
#include <exception>
#include <stdexcept>
using namespace std;


template<typename T>
class DataFilter {
public:

	//Default Konstruktor
	DataFilter() {}
	
	/* pre: aReader points to an instance of DataFileReader<T>
	for which openFiles() has been succesfully called.
	*/


	DataFilter(DataFileReader<T> *aReader, T aMin, T aMax) 
	{
		cpPekare = aReader;
		min = aMin;
		max = aMax;


	}

	~DataFilter();

	bool getNextValue(T &aValue);
	/* pre: an earlier call to getNextValue() has not returned
	false.
	post: true is returned if aValue holds a value read from
	aReader. If a value could not be read, false
	is returned. If a value is read but is not within
	the interval specified by aMin and aMax parameters
	to the constructor, a range_error exception is
	thrown.
	*/

	void OpenReaderFiles();


private:
	T min;
	T max;
	DataFileReader<T> *cpPekare;
	ofstream RangeErrorStream;
	string rangeErrorName = "RangeErrors.dat";
};


//Destruktor, stänger RangeErrorStream och tar bort pekaren.
template<typename T>
inline DataFilter<T>::~DataFilter()
{
	RangeErrorStream.close();
	delete cpPekare;
}

/* pre: an earlier call to getNextValue() has not returned
false.
post: true is returned if aValue holds a value read from
aReader. If a value could not be read, false
is returned. If a value is read but is not within
the interval specified by aMin and aMax parameters
to the constructor, a range_error exception is
thrown.
*/
template<typename T>
inline bool DataFilter<T>::getNextValue(T & aValue)
{
	//Kör om tills readNextValue returnerar true, dvs har läst in ett värde utan ReadErrors.
	while (cpPekare->readNextValue(aValue))
	{
		//När vi läst in utan ReadError, kolla att aValue är inom range.
		if (aValue < min || aValue > max)
		{
			RangeErrorStream << aValue << endl; //Skriver värdet till RangeErrors.
			throw std::range_error("Range Error, value outside range."); //Throwar range_error som fångas i testapp.cpp
			
		}
		return true;
	}
	return false;	
}

template<typename T>
inline void DataFilter<T>::OpenReaderFiles()
{	
	RangeErrorStream.open(rangeErrorName, ios::app); // Appendar till RangeError.dat
	cpPekare->openFiles(); //Öppnar filerna
}
