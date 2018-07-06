// UserInterface.cpp

#include "UserInterface.h"
#include "PersonList.h"
#include "Person.h"


// Menyn till huvudprogrammet
void UserInterface::menu()
{
	cout << "*************************" << endl;
	cout << "        The Menu" << endl;
	cout << "1. Mata in en ny person" << endl;
	cout << "2. Printa Vectorn" << endl;
	cout << "3. Spara lista till fil" << endl;
	cout << "4. L�s in lista fr�n fil" << endl;
	cout << "5. Sortera per namn" << endl;
	cout << "6. Sortera p� personnummer" << endl;
	cout << "7. Sortera p� skonummer" << endl;
	cout << "8. Exit program" << endl;
	cout << "*************************" << endl;
}

///////////////////////////////////////////////////////////////////////////////
//--------userInput-------------------------//
// L�ser in userinput och kontrollerar s� att det �r en int.
int UserInterface::userInput()
{
	int input = 0;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;

	//Kontrollerar s� att anv�ndaren angav sitt val i form av INT & s� att alternativet �r 9 eller mindre..
	while (cin.fail() || input <= 0 || input > 8)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast v�lja alternativ 1-8. " << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
	}

	return input;
}
//---------------------------------------------------------------------------- 
// **************************************************************************
//----------------------------------------------------------------------------


//H�rifr�n k�rs huvudprogrammet
int UserInterface::run()
{
	

	// Skapa testpersoner(objekt)
	Person p1(Name("Greger", "Zeezon"), Address("Bangatan 8", "81258", "Stockholm"), "920512-1337", 40);
	Person p2(Name("Zanzi", "Andersson"), Address("Godisgatan 88", "51258", "Stockholm"), "970321-1336", 48);
	Person p3(Name("Adam", "Andersson"), Address("Storgatan 2", "18258", "Stockholm"), "960522-1338", 42);
	
		
	// L�gg till testpersoner
	vectorList.addPerson(p1);
	vectorList.addPerson(p2);
	vectorList.addPerson(p3);
	

	// Do while true.
	bool reRun = true;

	do
	{
		//Skriver ut menyn
		menu();

		//L�ser in anv�nderens val fr�n funktionen userInput.
		switch (userInput())
		{ // K�r valt delprogram
		case 1: createObjekt(vectorList);
			break;
		case 2: printVec();
			break;
		case 3: call_writeToFile(vectorList); // Skriv Vectorn till fil
			break;
		case 4: call_readFromFile(vectorList); // L�s in fr�n fil
			break;
		case 5: call_sortName(vectorList); // Sortera p� Efternam / F�rnamn
			break;
		case 6: call_sortPersnr(vectorList); // Sortera p� Personnummer
			break;
		case 7: call_sortShoenr(vectorList); // Sortera p� Skonummer
			break;
		case 8: reRun = false; // Avsluta
			break;
		default:
			cout << endl << "Felaktigt alternativ. V�lj ett alternativ mellan 1-8..." << endl << endl;
			cin.get();
			break;
		}

	} while (reRun == true);

	cout << endl << endl << "Press enter to exit:  ";
	cin.get();
	cin.get();
	return 0;
}
//---------------------------------------------------------------------------- 
// ***************************************************************************
//----------------------------------------------------------------------------

// Menyval 1 - L�gg till en person i vectorn..
void UserInterface::createObjekt(PersonList &vec)
{
	//N�dv�ndiga objekt
	Person obj_Persn;
	Name obj_Name;
	Address obj_Address;

	// Variabler f�r att lagra inmatning
	string firstName, lastName, gatu_address, zip_code, stad, PersNr;
	int shoeSIZE;

	//L�gg till F�rnamn
	cin.ignore();
	cout << endl << "L�gg till data f�r personen" << endl << "________________" << endl;
	cout << endl << "F�rnamn: ";
	getline(cin, firstName);
	obj_Name.setFirstName(firstName);

	//L�gg till Efternamn
	cout << endl << "Efternamn: ";
	getline(cin, lastName);
	obj_Name.setLastName(lastName);

	//L�gg till Personnummer
	cout << endl << "Personnummer: ";
	getline(cin, PersNr);
	obj_Persn.setPersNr(PersNr);

	//L�gg till Gatuaddress
	cout << endl << "GatuAddress: ";
	getline(cin, gatu_address);
	obj_Address.setGatu_Address(gatu_address);

	//L�gg till Postnummer
	cout << endl << "Postnummer: ";
	getline(cin, zip_code);
	obj_Address.setZipCode(zip_code);

	//L�gg till Stad
	cout << endl << "Stad: ";
	getline(cin, stad);
	obj_Address.setStad(stad);

	//L�gg till Skostorlek
	cout << endl << "Skostorlek: ";
	cin >> shoeSIZE;
	obj_Persn.setshoeSIZE(shoeSIZE);

	//L�gger till data i respektive objekt
	obj_Persn.setName(obj_Name);
	obj_Persn.setAddress(obj_Address);
	
	cout << endl << obj_Persn;
	//L�gger PersonObjektet i vecotrn
	vectorList.addPerson(obj_Persn);

	cout << endl;
}
//---------------------------------------------------------------------------- 
// ************************************************************************** 
//----------------------------------------------------------------------------

void UserInterface::printVec()
{
	//---------------------------------------------------------------------------- 
	// Skriv listan p� sk�rmen 
	//----------------------------------------------------------------------------

	for (size_t i = 0; i < vectorList.antal_personer(); i++)
	{
		cout << "Namn: " << vectorList.getPerson(i).getName().getFirstName() << " " << vectorList.getPerson(i).getName().getLastName() << endl; 
		cout << "Gatuadress: " << vectorList.getPerson(i).getAddress().getGatu_Address() << endl;
		cout << "Postadress: " << vectorList.getPerson(i).getAddress().getZipCode() << " " << vectorList.getPerson(i).getAddress().getStad() << endl;
		cout << "Personnr: " << vectorList.getPerson(i).getPersNr() << endl;
		cout << "Skostorlek: " << vectorList.getPerson(i).getshoeSIZE() << endl << endl;
	}
	
}

//---------------------------------------------------------------------------- 
// F�r sorteringen (per namn, personnummer och skostorlek)
//----------------------------------------------------------------------------
//Kallar p� sorteringen i PersonList
void UserInterface::call_sortName(PersonList &vec)
{
	vec.sortName();
}
// Kallar p� sorteringen av personnummer i PersonList -----------------------
void UserInterface::call_sortPersnr(PersonList &vec)
{
	vec.sortPersnr();
}
// Kallar p� sorteringen av skostorlek i PersonList----------------------------
void UserInterface::call_sortShoenr(PersonList &vec)
{
	vec.sortShoenr();
}
//---------------------------------------------------------------------------- 
//***************************************************************************
//----------------------------------------------------------------------------

// Spara till fil
void UserInterface::call_writeToFile(PersonList &vec)
{
	string fileName;
	cout << "Vad vil du att filen skall heta? : ";
	cin.ignore();
	getline(cin, fileName);

	vectorList.setFileName(fileName);
	vectorList.writeToFile();
}
//----------------------------------------------------------------------------

//L�s fr�n fil
void UserInterface::call_readFromFile(PersonList &vec)
{
	string fileName;
	cout << "Vad heter filen du vill l�sa in fr�n? : ";
	cin.ignore();
	getline(cin, fileName);

	vectorList.setFileName(fileName);
	vectorList.readFromFile();
}