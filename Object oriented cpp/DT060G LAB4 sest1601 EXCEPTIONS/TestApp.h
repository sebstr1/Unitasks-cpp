/*
* Filnamn: TestApp.h
* Labb 4 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller klassen TestApp som används för att testa klasserna DataFileReader och Datafilter
* 
* 
*
*/
#ifndef TestAppH
#define TestAppH

#include "DataFilter.h"
#include "DataFileReader.h"
#include <string>
#include <vector>
#include <iostream>



using namespace std;




class TestApp {
private:
	DataFileReader<double> *dfr = new DataFileReader<double>("Values.dat", "ReadErrors.dat");
		
public:
	TestApp();
	void run();

};
#endif

