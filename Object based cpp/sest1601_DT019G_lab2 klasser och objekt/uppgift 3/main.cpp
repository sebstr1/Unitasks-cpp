// LAB 2 v 1.0
// Klasser & OBJ
// Sebastian Strindlund 2017-01-25
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "name.h"
#include "address.h"
#include <vector>
#include "Person.h"
#include <ctime>
#include "funktioner.h"
using namespace std;//------------------------------------------------------------------------------
int main()
{
	// G�r s� att man kan skriva ���.
	setlocale(LC_ALL(), "SWEDISH");

	vector<Person> personVectorn;

	//Initierar data f�r 3 personer innan menyn startas...
	personVectorn.push_back(Person(Name("Erik", "Svensson"), Address("Bangatan 8", "81258", "Stockholm"), "920512-1337", 40));
	personVectorn.push_back(Person(Name("Alban", "Nilsson"), Address("Godisgatan 88", "51258", "Stockholm"), "970321-1336", 48));
	personVectorn.push_back(Person(Name("Nils", "Karlsson"), Address("Storgatan 2", "18258", "Stockholm"), "960522-1338", 42));



	// Do while true.
	bool reRun = true;

	do
	{
		//Skriver ut menyn
		menu();

		//L�ser in anv�nderens val fr�n funktionen userInput.
		switch (userInput())
		{ // K�r valt delprogram
			case 1: addPerson(personVectorn);
				break;
			case 2: printVec(personVectorn);
				break;
			case 3: reRun = false; // Avsluta
				break;
			default:
				cout << endl << "Felaktigt alternativ. V�lj ett alternativ mellan 1-3..." << endl << endl;
				cin.get();
				break;
		}
	} while (reRun == true);

	cout << endl << endl << "Press enter to exit:  ";
	cin.get();
	cin.get();
	return 0;
}

