// LAB 2 v 1.0
// Klasser & OBJ
// Sebastian Strindlund 2017-01-25
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include "Header.h"using namespace std;//------------------------------------------------------------------------------
int main()
{
	//Testar default konstruktorn
	cout << "Testar default konstruktorn" << endl;
	Address adress1;
	cout << adress1.getGatu_Address() << endl << adress1.getZipCode() << endl << adress1.getStad() << endl;

	//Testar alla medlemsfunktioner
	cout << "Testar alla medlemsfunktioner" << endl;
	adress1.setGatu_Address("Bangatan 8");
	adress1.setZipCode("912 51");
	adress1.setStad("Stockholm");
	cout << adress1.getGatu_Address() << endl << adress1.getZipCode() << endl << adress1.getStad() << endl << endl;

	//Testar den alternativa konstruktorn
	cout << "Testar den alternativa konstruktorn" << endl;
	Address adress2("Storgatan 9", "939 21", "Halmstad");
	cout << adress2.getGatu_Address() << endl << adress2.getZipCode() << endl << adress2.getStad() << endl;


	cout << endl << endl << "Press enter to exit:  ";
	cin.get();
	return 0;
}