
/*
* Filnamn: TestApp.cpp
* Labb 4 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* Filen används som ett testprogram för att testa klassen DataFileReader och DataFilter.
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
	
	//Initierar pekare med max och minvärden
	DataFilter<double> filter(dfr, 0.00, 10.00);
	double aValue;
	
	//Testar att öppna filerna
	filter.OpenReaderFiles();

	// Initierar variabler
	int readNumValues = 0;
	int valuesOutOfRange = 0;
	double sum = 0.00;


	bool Rerun = true;
	while (Rerun) // Kör....
	{
		try
		{
			while (filter.getNextValue(aValue)) // Körs sålänge getNextValue returnerar true.
			{
				++readNumValues; //Räknar korrekt lästa värden
				sum = sum + aValue; // Summerar korrekt lästa värden

			}
			//Färdigkört
			Rerun = false;


		}
		//Fånger exceptions, primärt OutofRange
		catch (range_error &e)
		{
			cerr << e.what() << endl;
			//Räknar lästa värden som är out of range
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