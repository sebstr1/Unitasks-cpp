// LAB 2 v 1.0
// Klasser & OBJ
// Sebastian Strindlund 2017-01-25
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include "klassDef.h"using namespace std;//------------------------------------------------------------------------------
int main()
{
	//Testar default konstruktorn
	Name name1;
	cout << name1.getFirstName() << " " << name1.getLastName() << endl;

	//Testar alla medlemsfunktioner
	name1.setFirstName("Adam");
	name1.setLastName("Erikson");
	cout << name1.getFirstName() << " " << name1.getLastName() << endl;
	
	//Testar den alternativa konstruktorn
	Name name2("Banan", "Korv");
	cout << name2.getFirstName() << " " << name2.getLastName() << endl;


	cout << endl << endl << "Press enter to exit:  ";
	cin.get();
	return 0;
}