//---------------------------------------------------------------------------//
// Filnamn: SEST1601_DT018G_PROJEKT_MAIN.cpp
// Sebastian Strindlund
// Skapat datum: 2016-12-04
// Kurs: DT018G Introduktion till programmering i C++
// Handledare: Per Ekeroot
// Beskrivning: Projekt skapat enligt anvisningar
//---------------------------------------------------------------------------//
#include "SEST1601_DT018G_PROJEKT_PROJEKTHEADER.h"
#include "SEST1601_DT018G_PROJEKT_CONSTANTS.h"
//-------------------Huvudfunktionen----------------------------------------//

int main()
{
	// Gör så att man kan skriva åäö.
	setlocale(LC_ALL(), "SWEDISH");	
	
	// Deklarerar personregister
	vector<Personer> PersonRegister;	
	
	// Variabel för användarens sorteringsval i case 5
	int sorterings_val = 0;

	// Do while true.
	bool reRun = true;
	
	do
	{
		meny(PersonRegister);	
		
		switch (userInput())
		{ // Kör valt delprogram
			case 1: addPerson(PersonRegister);
				break;
			case 2: printRegister(PersonRegister);
				break;
			case 3: findPerson(PersonRegister);
				break;
			case 4: deletePerson(PersonRegister);
				break;

			case 5:
				// Fråga efter och läs in sorteringsvalet med teckenverifiering
				while ((cout << endl << "Sortera listan på namn [1] \nSortera listan på signatur [2] \nSortera listan på läng [3] \nDitt val: ")
					&& (!(cin >> sorterings_val)
					|| sorterings_val < 1 
					|| sorterings_val > 3))
				{
					

				}
				sorteraVectorHelvetet(sorterings_val, PersonRegister);
				break;

			case 6: SLUMPA(PersonRegister);
				break;
			case 7: saveToFile(PersonRegister);
				break;
			case 8: readFromFile(PersonRegister);
				break;
			case 9: reRun = false; // Avsluta
				break;
			default: 
				cout << endl << "Felaktigt alternativ. Välj ett alternativ mellan 1-9..." << endl << endl;
				cout << "Tryck på enter för att vissa til menyn och välja alternativ igen..";
				cin.get();
				break;
			}
		} while (reRun == true);
	

	return 0;
}