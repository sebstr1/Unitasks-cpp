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
	cout << "4. Läs in lista från fil" << endl;
	cout << "5. Sortera per namn" << endl;
	cout << "6. Sortera på personnummer" << endl;
	cout << "7. Sortera på skonummer" << endl;
	cout << "8. Exit program" << endl;
	cout << "*************************" << endl;
}

///////////////////////////////////////////////////////////////////////////////
//--------userInput-------------------------//
// Läser in userinput och kontrollerar så att det är en int.
int UserInterface::userInput()
{
	int input = 0;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;

	//Kontrollerar så att användaren angav sitt val i form av INT & så att alternativet är 9 eller mindre..
	while (cin.fail() || input <= 0 || input > 8)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast välja alternativ 1-8. " << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
	}

	return input;
}
//---------------------------------------------------------------------------- 
// **************************************************************************
//----------------------------------------------------------------------------


//Härifrån körs huvudprogrammet
int UserInterface::run()
{
	

	// Skapa testpersoner(objekt)
	Person p1(Name("Greger", "Zeezon"), Address("Bangatan 8", "81258", "Stockholm"), "920512-1337", 40);
	Person p2(Name("Zanzi", "Andersson"), Address("Godisgatan 88", "51258", "Stockholm"), "970321-1336", 48);
	Person p3(Name("Adam", "Andersson"), Address("Storgatan 2", "18258", "Stockholm"), "960522-1338", 42);
	
		
	// Lägg till testpersoner
	vectorList.addPerson(p1);
	vectorList.addPerson(p2);
	vectorList.addPerson(p3);
	

	// Do while true.
	bool reRun = true;

	do
	{
		//Skriver ut menyn
		menu();

		//Läser in använderens val från funktionen userInput.
		switch (userInput())
		{ // Kör valt delprogram
		case 1: createObjekt(vectorList);
			break;
		case 2: printVec();
			break;
		case 3: call_writeToFile(vectorList); // Skriv Vectorn till fil
			break;
		case 4: call_readFromFile(vectorList); // Läs in från fil
			break;
		case 5: call_sortName(vectorList); // Sortera på Efternam / Förnamn
			break;
		case 6: call_sortPersnr(vectorList); // Sortera på Personnummer
			break;
		case 7: call_sortShoenr(vectorList); // Sortera på Skonummer
			break;
		case 8: reRun = false; // Avsluta
			break;
		default:
			cout << endl << "Felaktigt alternativ. Välj ett alternativ mellan 1-8..." << endl << endl;
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

// Menyval 1 - Lägg till en person i vectorn..
void UserInterface::createObjekt(PersonList &vec)
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
	
	cout << endl << obj_Persn;
	//Lägger PersonObjektet i vecotrn
	vectorList.addPerson(obj_Persn);

	cout << endl;
}
//---------------------------------------------------------------------------- 
// ************************************************************************** 
//----------------------------------------------------------------------------

void UserInterface::printVec()
{
	//---------------------------------------------------------------------------- 
	// Skriv listan på skärmen 
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
// För sorteringen (per namn, personnummer och skostorlek)
//----------------------------------------------------------------------------
//Kallar på sorteringen i PersonList
void UserInterface::call_sortName(PersonList &vec)
{
	vec.sortName();
}
// Kallar på sorteringen av personnummer i PersonList -----------------------
void UserInterface::call_sortPersnr(PersonList &vec)
{
	vec.sortPersnr();
}
// Kallar på sorteringen av skostorlek i PersonList----------------------------
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

//Läs från fil
void UserInterface::call_readFromFile(PersonList &vec)
{
	string fileName;
	cout << "Vad heter filen du vill läsa in från? : ";
	cin.ignore();
	getline(cin, fileName);

	vectorList.setFileName(fileName);
	vectorList.readFromFile();
}