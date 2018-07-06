// UserInterface.cpp

#include "HousingQ.h"
#include "queue.h"
#include "Person.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


// Menyn till huvudprogrammet
void HousingQ::menu()
{
	cout << "     Bostadskö_Tool" << endl;
	cout << "*************************" << endl;
	cout << "1. Ställ en person sist i bostadskön" << endl;
	cout << "2. Erbjud en person bostad" << endl;
	cout << "3. Skriv ut hela bostadskön" << endl;
	cout << "4. Skriv ut data om en person" << endl;
	cout << "5. Ta bort en person ur bostadskön" << endl;
	cout << "6. Spara kön" << endl;
	cout << "7. Avsluta programmet" << endl;
	cout << "*************************" << endl;
}

///////////////////////////////////////////////////////////////////////////////
//--------userInput-------------------------//
// Läser in userinput och kontrollerar så att det är en int.
int HousingQ::userInput()
{
	int input = 0;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;

	//Kontrollerar så att användaren angav sitt val i form av INT & så att alternativet är 9 eller mindre..
	while (cin.fail() || input <= 0 || input > 7)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast välja alternativ 1-7. " << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
	}

	return input;
}
//---------------------------------------------------------------------------- 
// **************************************************************************
//----------------------------------------------------------------------------


//Härifrån körs huvudprogrammet
int HousingQ::run()
{
	cout << "     Bostadskö_Tool" << endl;
	cout << "*************************" << endl;
	cout << endl << "Ange namnet på filen du vill ladda eller skapa: ";

	// Läser in namnet på filen vi skall använda
	getline(cin, FileName);

	//Läser in data från filen FileName om denna fil existerar
	ReadFile();
		
	// Do while true.
	bool reRun = true;
	do
	{
		//Rensar kommandotolken 		
		cout << string(50, '\n');
		
		
		//Skriver ut menyn
		menu();
		
		//Läser in använderens val från funktionen userInput.
		switch (userInput())
		{ // Kör valt delprogram
		case 1: 
			addPerson(the_que); //Lägg till Person sist i kön
			break;
		case 2: 
			bostad_erbjuden(); // Erbjuden bostad = ta bort den som är först i kön
			break;
		case 3: 
			printQUE(); // Skriv ut hela kön
			break;
		case 4: 
			stalkPerson(); //Sök på personnummer och skriv ut info om personen
			break;
		case 5:
			deletePerson(); // Ta bort person från kön via personnummer
			break;
		case 6: 
			WriteFile(); // Spara till fil
			break;
		case 7: reRun = false; // Avsluta
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

//Köstorlek
int HousingQ::Que_size()
{
	//Skapar iterator
	QIterator iterator;	int que_size = 0;	//Stegar igenom och räknar storleken	for (iterator = the_que.begin(); iterator != the_que.end(); iterator++)	{
		que_size++;
	}
	//Returnera storleken
	return que_size;
}

//Lägg till person sist i kön

//// Menyval 1 - Lägg till en person sist i kön..
void HousingQ::addPerson(QList &person_objekt)
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
	the_que.enque(obj_Persn);

	cout << endl;
}
////---------------------------------------------------------------------------- 
//// ************************************************************************** 
////----------------------------------------------------------------------------
// Menyval 2 - Personen som stod först i kön har blivit erbjuden bostad & 
//antagligen tackatja eftersom vi tar bort denna ur systemet..
void HousingQ::bostad_erbjuden()
{
	//Rensar CMD
	cout << string(50, '\n');
	cin.ignore();
	QIterator iterator = the_que.begin();

	//Kontrollerar så att kön ej är tom
	if (the_que.isEmpty())
	{
		cout << endl << "Kan inte erbjuda bostad eftersom ingen står i kön.." << endl << endl;
	}
	else
	{
		cout << endl << "**** Bostad Erbjuden ****" << endl;
		cout << endl << "Följande kund har tackat ja till bostaden: ";
		cout << endl << "Namn: " << (*iterator).getName().getFirstName() << " " << (*iterator).getName().getLastName() << endl;
		cout << "Personnr: " << (*iterator).getPersNr() << endl;
		cout << endl << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;

		cout << endl << "Denna person har fått sin lägenhet och plockas härmed bort från kölistan." << endl << endl;
		
		//Tar bort första personen från kön
		the_que.deque(*iterator);
	}	

	cout << "Press enter to get back to the menu...";
	cin.get();	
}

////---------------------------------------------------------------------------- 
//// ************************************************************************** 
////----------------------------------------------------------------------------
//Menyval 3  -  Skriv ut kön..
void HousingQ::printQUE()
{
	//Rensar CMD
	cout << string(50, '\n');

	//Kontrollerar så att kön ej är tom
	if (the_que.isEmpty())
	{
		cout << endl << "Yo, da que is emepty so yo cannot print dis" << endl << endl;
	}

	//Var listan inte tom så kör utskriften
	else
	{
		//Iterator
		QIterator iterator;
		
		//counter
		int counter;

		//---------------------------------------------------------------------------- 
		// Skriv listan på skärmen 
		//----------------------------------------------------------------------------
		cout << endl << "******************";
		for (iterator = the_que.begin(), counter = 1; iterator != the_que.end(); iterator++, counter++)
		{
			//cout << endl << "******************";
			cout << endl << "Köplats: " << counter << " av totalt: " << Que_size() << " personer";
			cout << endl << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
			cout << "Namn: " << (*iterator).getName().getFirstName() << " " << (*iterator).getName().getLastName() << endl;
			cout << "Gatuadress: " << (*iterator).getAddress().getGatu_Address() << endl;
			cout << "Postadress: " << (*iterator).getAddress().getZipCode() << " " << (*iterator).getAddress().getStad() << endl;
			cout << "Personnr: " << (*iterator).getPersNr() << endl;
			cout << "Skostorlek: " << (*iterator).getshoeSIZE();
			cout << endl << "******************";
		}
		
	}
	cout << endl << endl;
	cout << "Press enter to get back to the menu...";
	cin.get();
	cin.get();	
}
////---------------------------------------------------------------------------- 
//// ************************************************************************** 
////----------------------------------------------------------------------------
//Menyval 4 - Sök efter personnummer i kön och skriv ut dennes data.
void HousingQ::stalkPerson()
{
	//Tömmar Cmdwindow
	cout << string(50, '\n');
	cin.get();

	//Kollar om kön är tom
	if (the_que.isEmpty())
	{		
		cout << endl << "Du kan inte söka efter någon person eftersom listan är tom..." << endl << endl;
	}

	else
	{
		//Lagra personnummer
		string persnr;

		cout << "Vad har personen du söker för personnummer?: ";
		getline(cin, persnr);

		//Skapar Iterator
		QIterator iterator;

		//Variabler för räknare och träff vid sökning
		int search_hit = 0;
		int counter;

		//Stegar igenom kön
		for (iterator = the_que.begin(), counter = 1; iterator != the_que.end(); iterator++, counter++)
		{
			//Om aktuell nod är = persnr vi söker
			if ((*iterator).getPersNr() == persnr)
			{
				search_hit = 1;
				break;
			}
		}

		//Om personen hittades
		if (search_hit == 1)
		{
			cout << endl << "Köplats: " << counter << " av totalt: " << Que_size() << " personer";
			cout << endl << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
			cout << "Namn: " << (*iterator).getName().getFirstName() << " " << (*iterator).getName().getLastName() << endl;
			cout << "Gatuadress: " << (*iterator).getAddress().getGatu_Address() << endl;
			cout << "Postadress: " << (*iterator).getAddress().getZipCode() << " " << (*iterator).getAddress().getStad() << endl;
			cout << "Personnr: " << (*iterator).getPersNr() << endl;
			cout << "Skostorlek: " << (*iterator).getshoeSIZE();
			cout << endl << "******************";
		}
		else
		{
			cout << endl << "Fel personnummer eller så existerar inte personen i vårat kösystem...";
		}


	}	
	cout << endl << endl;
	cout << "Press enter to get back to the menu...";
	cin.get();
}
////---------------------------------------------------------------------------- 
//// Menyval 5 - Delete Person
////----------------------------------------------------------------------------
void HousingQ::deletePerson()
{
	//Tömmar Cmdwindow
	cout << string(50, '\n');

	//Läser av newline
	cin.get();

	//Kollar om kön är tom
	if (the_que.isEmpty())
	{
		cout << endl << "Error, kön är redan tom så lycka till med att deleta någon :)" << endl << endl;		
	}

	//Gå vidare med att hitta & ta bort person
	else
	{
		//Lagra personnummer
		string persnr;

		cout << "Vad har personen du vill ta bort för personnummer?: ";
		getline(cin, persnr);

		//Skapar Iterator
		QIterator iterator;

		//Variabler för räknare och träff vid sökning
		int search_hit = 0;
		int counter;

		//Söker efter personnummer
		for (iterator = the_que.begin(), counter = 1; iterator != the_que.end(); iterator++, counter++)
		{
			if ((*iterator).getPersNr() == persnr)
			{
				search_hit = 1;
				break;
			}
		}

		//Om personen hittades
		if (search_hit == 1)
		{
			cout << endl << "Personen du vill ta bort är följande: " << endl << endl;
			cout << endl << "Köplats: " << counter << " av totalt: " << Que_size() << " personer";
			cout << endl << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
			cout << "Namn: " << (*iterator).getName().getFirstName() << " " << (*iterator).getName().getLastName() << endl;
			cout << "Gatuadress: " << (*iterator).getAddress().getGatu_Address() << endl;
			cout << "Postadress: " << (*iterator).getAddress().getZipCode() << " " << (*iterator).getAddress().getStad() << endl;
			cout << "Personnr: " << (*iterator).getPersNr() << endl;
			cout << "Skostorlek: " << (*iterator).getshoeSIZE();
			cout << endl << "******************";


			cout << endl << endl << "Vill du ta bort personen? yes/no ";
			string answer;
			getline(cin, answer);

			//Om man vill ta bort personen så..
			if (answer == "yes")
			{
				
				the_que.del(*iterator);
				cout << endl << "Personen med personnummer " << persnr << " har tagits bort ur systemet..";
			}
		}
		else
		{
			cout << endl << "Fel personnummer eller så existerar inte personen i vårat kösystem...";
		}
	}


	cout << endl << endl;
	cout << "Press enter to get back to the menu...";
	cin.get();




}
////---------------------------------------------------------------------------- 
//// Menyval 6 - Spara till fil
////----------------------------------------------------------------------------
void HousingQ::WriteFile()
{			
//	//------------------------------------------------------------------------------	
//	// Kollar om använderen anger filen med .txt i slutet, lägger annars till det.
//	//------------------------------------------------------------------------------
//Kontrollerar så att kön ej är tom
	if (the_que.isEmpty())
	{
		cout << endl << "Error, kön är tom, onödigt att spara en tom fil.." << endl << endl;
	}

	//Var listan inte tom så spara till fil..
	else
	{

		// Jämför och lägger till .txt om det saknas..
		string tmpstring;
		string compare = ".txt";
		tmpstring = FileName.substr(FileName.size() - 4, 4);

		if (compare != tmpstring)
		{
			FileName = FileName + compare;
		}

		//	//------------------------------------------------------------------------------
		//	// Skapa filobjekt (filvariabel) och filnamn
		//	//------------------------------------------------------------------------------
		fstream QueListFile(FileName, ios::out);

		//	//------------------------------------------------------------------------------
		//	// Öppna filen för skrivning
		//	//------------------------------------------------------------------------------
		if (QueListFile.is_open())
		{
			// Skapar iterator
			QIterator iterator;

			// Går igenom hela listan
			for (iterator = the_que.begin(); iterator != the_que.end(); iterator++)
			{
				QueListFile << *iterator << endl;
			}
			cout << endl << "Registret har sparats till " << FileName;
		}
		else
		{
			// Filen kunde ej öppnas av ngn anledning

			cout << endl << "Error, Filen kunde ej öppnas" << endl << endl;
		}
		//Stäng filen
		QueListFile.close();
	}
	cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
	cin.get();
	cin.get();
}

//Read from file
void HousingQ::ReadFile()
{
	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel)
	//------------------------------------------------------------------------------
	fstream QueListFile;
	// Kollar om använderen anger filen med .txt i slutet, lägger annars till det.
	/*string tmpstring;
	string compare = ".txt";
	FileName.substr(FileName.size() - 3, 3);

	if (compare != tmpstring)
	{
		FileName = FileName + compare;
	}*/

	//------------------------------------------------------------------------------
	// Öppna filen för läsning
	//------------------------------------------------------------------------------
	QueListFile.open(FileName, ios::in);
	if (QueListFile.is_open()) //Gick det bra att öppna filen
	{
		Item personItem;


		while (QueListFile >> personItem)
		{
			the_que.enque(personItem);
		}

	}
}

// Standardkonstruktor
HousingQ::HousingQ()
{	
	FileName = "";
}
