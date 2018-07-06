/*
* Filnamn: TestApp.h
* Labb 5
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller klassen TestApp som används för att testa klassen Bowser och dess implementationer.
* 
* 
*
*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Bowser.h"
using namespace std;

template<typename T>
class TestApp {

private:
	Bowser<T> ListManipulatorObjekt; // Object som utför olika opertioner på en list		
public:
	TestApp();  // Konstruktor
	void run(); // Här körs testprogrammet

};

template<typename T>
inline TestApp<T>::TestApp()
{
}

template<typename T>
inline void TestApp<T>::run()
{	
	bool rerun = true;
	char input;
	do // Körs sålänge rerun är true.
	{
		cout << endl << endl;
		cout << "(a) Fill list with 20 random numbers." << endl;
		cout << "(b) Calculate sum of the list." << endl;
		cout << "(c) Calculate average number of list ." << endl;
		cout << "(d) Find first number of list in range 1500-1900." << endl;
		cout << "(e) Divide all numbers of list by 2." << endl;
		cout << "(f) Swap places of first and last and so on." << endl;
		cout << "(g) Find max and min of list." << endl;
		cout << "(h) Sort by Ascedning order." << endl;
		cout << "(i) Write the list to file." << endl;
		cout << "(j) Clear the list." << endl;
		cout << "(k) Read values from file to list." << endl;
		cout << "(l) Print all numbers." << endl;
		cout << "(q) Exit." << endl;

		cout << endl << "Alternative: ";
		cin >> input;
		cin.get();

		switch (input)
		{
		case 'a':
			ListManipulatorObjekt.fill_list();    // Funktion för att fylla listan.
			ListManipulatorObjekt.printAll();     // Skriver ut alla tal.
			break;
		case 'b':
			ListManipulatorObjekt.sumList();      // Funktion för att summera listan.
			break;
		case 'c':
			ListManipulatorObjekt.Average();      // Funktion för att räkna ut medelvärdet.
			break;
		case 'd':
			ListManipulatorObjekt.findShit();     // Funktion för att hitta första talet inom ett interval.
			break;
		case 'e':
			ListManipulatorObjekt.dividebytwo();  // Funktion för att dela alla värden med 2.
			ListManipulatorObjekt.printAll();     // Skriver ut alla tal.
			break;
		case 'f':
			ListManipulatorObjekt.iteratorswap(); // Funktion för att byta plats på tal i listan.
			ListManipulatorObjekt.printAll();     // Skriver ut alla tal.
			break;
		case 'g':
			ListManipulatorObjekt.MaxMin();		  // Funktion för att hitta max och min i listan.
			break;
		case 'h':
			ListManipulatorObjekt.sortASC();	  // Funktion för att sortera listan i stigande ordning.
			ListManipulatorObjekt.printAll();	  // Skriver ut alla tal.
			break;
		case 'i':
			ListManipulatorObjekt.writeToFile();  // Funktion som skriver listan till fil.
			break;
		case 'j':
			ListManipulatorObjekt.clearList();    // Funktion som raderar listans innehåll.
			break;
		case 'k':
			ListManipulatorObjekt.readFromFile(); // Funktion sok läser från fil till lista.
			break;
		case 'l':
			ListManipulatorObjekt.printAll();     // Skriver ut alla tal.
			break;
		case 'q':								  //Quit
			cout << "Exiting program..." << endl;
			rerun = false;
			break;

		}

	} while (rerun);
}
