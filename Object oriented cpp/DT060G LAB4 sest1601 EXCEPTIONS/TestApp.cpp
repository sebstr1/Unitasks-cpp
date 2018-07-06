
/*
* Filnamn: TestApp.cpp
* Labb 4 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* Filen anv�nds som ett testprogram f�r att testa klassen DataFileReader och DataFilter.
* 
*
*/

#include "TestApp.h"
#include "DataFileReader.cpp"
#include <algorithm>
#include <string>
using namespace std;



TestApp::TestApp()
{
}



void TestApp::run()
{
	
	//Initierar pekare med max och minv�rden
	DataFilter<double> filter(dfr, 0.00, 10.00);
	double aValue;
	
	//Testar att �ppna filerna
	filter.OpenReaderFiles();

	// Initierar variabler
	int readNumValues = 0;
	int valuesOutOfRange = 0;
	double sum = 0.00;


	bool Rerun = true;
	while (Rerun) // K�r....
	{
		try
		{
			while (filter.getNextValue(aValue)) // K�rs s�l�nge getNextValue returnerar true.
			{
				++readNumValues; //R�knar korrekt l�sta v�rden
				sum = sum + aValue; // Summerar korrekt l�sta v�rden

			}
			//F�rdigk�rt
			Rerun = false;


		}
		//F�nger exceptions, prim�rt OutofRange
		catch (range_error &e)
		{
			cerr << e.what() << endl;
			//R�knar l�sta v�rden som �r out of range
			valuesOutOfRange++;


		}
	}
	
	// Skriver ut resultaten
	cout << "\n \nResults........" << endl;
	cout << "Correct Read numeric values: " << readNumValues << endl;
	cout << "Numeric Values out of range: " << valuesOutOfRange << endl;
	cout << "Sum of correct read values: " << sum << endl;
	cout << "Average value:" << sum / readNumValues << endl;

}