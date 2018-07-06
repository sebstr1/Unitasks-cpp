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
	// G�r s� att man kan skriva ���.
	setlocale(LC_ALL(), "SWEDISH");	
	
	// Deklarerar personregister
	vector<Personer> PersonRegister;	
	
	// Variabel f�r anv�ndarens sorteringsval i case 5
	int sorterings_val = 0;

	// Do while true.
	bool reRun = true;
	
	do
	{
		meny(PersonRegister);	
		
		switch (userInput())
		{ // K�r valt delprogram
			case 1: addPerson(PersonRegister);
				break;
			case 2: printRegister(PersonRegister);
				break;
			case 3: findPerson(PersonRegister);
				break;
			case 4: deletePerson(PersonRegister);
				break;

			case 5:
				// Fr�ga efter och l�s in sorteringsvalet med teckenverifiering
				while ((cout << endl << "Sortera listan p� namn [1] \nSortera listan p� signatur [2] \nSortera listan p� l�ng [3] \nDitt val: ")
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
				cout << endl << "Felaktigt alternativ. V�lj ett alternativ mellan 1-9..." << endl << endl;
				cout << "Tryck p� enter f�r att vissa til menyn och v�lja alternativ igen..";
				cin.get();
				break;
			}
		} while (reRun == true);
	

	return 0;
}