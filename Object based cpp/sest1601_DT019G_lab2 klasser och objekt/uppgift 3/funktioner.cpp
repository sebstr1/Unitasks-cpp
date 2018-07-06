// Definitions.cpp
// Funktionsdefinitioner till Lab4.h
//-----------------------------------------------//

#include "funktioner.h"
#include <sstream>


//Skriver ut menyalternativen
void menu()
{
	cout << "1. Mata in en ny person" << endl;
	cout << "2. Skriv ut hela vectorn" << endl;
	cout << "3. Exit program" << endl;
}

///////////////////////////////////////////////////////////////////////////////
//--------userInput-------------------------//
// Läser in userinput och kontrollerar så att det är en int.
int userInput()
{
	int input = 0;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;

	//Kontrollerar så att användaren angav sitt val i form av INT & så att alternativet är 9 eller mindre..
	while (cin.fail() || input <= 0 || input > 3)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast välja alternativ 1-9. " << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
	}

	return input;
}


// Menyval 1 - Lägg till en person i vectorn..
void addPerson(vector<Person> &vector)
{
	//Nödvändiga objekt
	Person obj_Persn;
	Name obj_Name;
	Address obj_Address;

	// Variabler för att lagra inmatning
	string firstName, lastName, gatu_address, zip_code, stad, PersNr;
	int shoeSIZE;

	//Lägg till Förnamn
	cin.ignore();
	cout << endl << "Lägg till data för personen" << endl << "________________" << endl;
	cout << endl << "Förnamn: ";
	getline(cin, firstName);
	obj_Name.setFirstName(firstName);

	//Lägg till Efternamn
	cout << endl << "Efternamn: ";
	getline(cin, lastName);
	obj_Name.setLastName(lastName);

	//Lägg till Personnummer
	cout << endl << "Personnummer: ";
	getline(cin, PersNr);
	obj_Persn.setPersNr(PersNr);

	//Lägg till Gatuaddress
	cout << endl << "GatuAddress: ";
	getline(cin, gatu_address);
	obj_Address.setGatu_Address(gatu_address);

	//Lägg till Postnummer
	cout << endl << "Postnummer: ";
	getline(cin, zip_code);
	obj_Address.setZipCode(zip_code);

	//Lägg till Stad
	cout << endl << "Stad: ";
	getline(cin, stad);
	obj_Address.setStad(stad);

	//Lägg till Skostorlek
	cout << endl << "Skostorlek: ";
	cin >> shoeSIZE;
	obj_Persn.setshoeSIZE(shoeSIZE);

	//Lägger till data i respektive objekt
	obj_Persn.setName(obj_Name);
	obj_Persn.setAddress(obj_Address);
	
	//Lägger PersonObjektet i vecotrn
	vector.push_back(obj_Persn);

	cout << endl;
}



// Utskrift av Vectorn
void printVec(vector<Person> &vector)
{

	//---------------------------------------------------------------------------- 
	// Skriv registret på skärm 
	//----------------------------------------------------------------------------

	for (auto personVectorn : vector)
	{
		cout << "Namn: " << personVectorn.getName().getFirstName() << " " << personVectorn.getName().getLastName() << endl;
		cout << "Gatuadress: " << personVectorn.getAddress().getGatu_Address() << endl;
		cout << "Postadress: " << personVectorn.getAddress().getZipCode() << " " << personVectorn.getAddress().getStad() << endl;
		cout << "Personnr: " << personVectorn.getPersNr() << endl;
		cout << "Skostorlek: " << personVectorn.getshoeSIZE() << endl << endl;
	}

}