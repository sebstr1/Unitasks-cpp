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
	cout << "     Bostadsk�_Tool" << endl;
	cout << "*************************" << endl;
	cout << "1. St�ll en person sist i bostadsk�n" << endl;
	cout << "2. Erbjud en person bostad" << endl;
	cout << "3. Skriv ut hela bostadsk�n" << endl;
	cout << "4. Skriv ut data om en person" << endl;
	cout << "5. Ta bort en person ur bostadsk�n" << endl;
	cout << "6. Spara k�n" << endl;
	cout << "7. Avsluta programmet" << endl;
	cout << "*************************" << endl;
}

///////////////////////////////////////////////////////////////////////////////
//--------userInput-------------------------//
// L�ser in userinput och kontrollerar s� att det �r en int.
int HousingQ::userInput()
{
	int input = 0;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;

	//Kontrollerar s� att anv�ndaren angav sitt val i form av INT & s� att alternativet �r 9 eller mindre..
	while (cin.fail() || input <= 0 || input > 7)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast v�lja alternativ 1-7. " << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
	}

	return input;
}
//---------------------------------------------------------------------------- 
// **************************************************************************
//----------------------------------------------------------------------------


//H�rifr�n k�rs huvudprogrammet
int HousingQ::run()
{
	cout << "     Bostadsk�_Tool" << endl;
	cout << "*************************" << endl;
	cout << endl << "Ange namnet p� filen du vill ladda eller skapa: ";

	// L�ser in namnet p� filen vi skall anv�nda
	getline(cin, FileName);

	//L�ser in data fr�n filen FileName om denna fil existerar
	ReadFile();
		
	// Do while true.
	bool reRun = true;
	do
	{
		//Rensar kommandotolken 		
		cout << string(50, '\n');
		
		
		//Skriver ut menyn
		menu();
		
		//L�ser in anv�nderens val fr�n funktionen userInput.
		switch (userInput())
		{ // K�r valt delprogram
		case 1: 
			addPerson(the_que); //L�gg till Person sist i k�n
			break;
		case 2: 
			bostad_erbjuden(); // Erbjuden bostad = ta bort den som �r f�rst i k�n
			break;
		case 3: 
			printQUE(); // Skriv ut hela k�n
			break;
		case 4: 
			stalkPerson(); //S�k p� personnummer och skriv ut info om personen
			break;
		case 5:
			deletePerson(); // Ta bort person fr�n k�n via personnummer
			break;
		case 6: 
			WriteFile(); // Spara till fil
			break;
		case 7: reRun = false; // Avsluta
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

//K�storlek
int HousingQ::Que_size()
{
	//Skapar iterator
	QIterator iterator;	int que_size = 0;	//Stegar igenom och r�knar storleken	for (iterator = the_que.begin(); iterator != the_que.end(); iterator++)	{
		que_size++;
	}
	//Returnera storleken
	return que_size;
}

//L�gg till person sist i k�n

//// Menyval 1 - L�gg till en person sist i k�n..
void HousingQ::addPerson(QList &person_objekt)
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
	
	
	//L�gger PersonObjektet i vecotrn
	the_que.enque(obj_Persn);

	cout << endl;
}
////---------------------------------------------------------------------------- 
//// ************************************************************************** 
////----------------------------------------------------------------------------
// Menyval 2 - Personen som stod f�rst i k�n har blivit erbjuden bostad & 
//antagligen tackatja eftersom vi tar bort denna ur systemet..
void HousingQ::bostad_erbjuden()
{
	//Rensar CMD
	cout << string(50, '\n');
	cin.ignore();
	QIterator iterator = the_que.begin();

	//Kontrollerar s� att k�n ej �r tom
	if (the_que.isEmpty())
	{
		cout << endl << "Kan inte erbjuda bostad eftersom ingen st�r i k�n.." << endl << endl;
	}
	else
	{
		cout << endl << "**** Bostad Erbjuden ****" << endl;
		cout << endl << "F�ljande kund har tackat ja till bostaden: ";
		cout << endl << "Namn: " << (*iterator).getName().getFirstName() << " " << (*iterator).getName().getLastName() << endl;
		cout << "Personnr: " << (*iterator).getPersNr() << endl;
		cout << endl << "�������������������������������������������" << endl;

		cout << endl << "Denna person har f�tt sin l�genhet och plockas h�rmed bort fr�n k�listan." << endl << endl;
		
		//Tar bort f�rsta personen fr�n k�n
		the_que.deque(*iterator);
	}	

	cout << "Press enter to get back to the menu...";
	cin.get();	
}

////---------------------------------------------------------------------------- 
//// ************************************************************************** 
////----------------------------------------------------------------------------
//Menyval 3  -  Skriv ut k�n..
void HousingQ::printQUE()
{
	//Rensar CMD
	cout << string(50, '\n');

	//Kontrollerar s� att k�n ej �r tom
	if (the_que.isEmpty())
	{
		cout << endl << "Yo, da que is emepty so yo cannot print dis" << endl << endl;
	}

	//Var listan inte tom s� k�r utskriften
	else
	{
		//Iterator
		QIterator iterator;
		
		//counter
		int counter;

		//---------------------------------------------------------------------------- 
		// Skriv listan p� sk�rmen 
		//----------------------------------------------------------------------------
		cout << endl << "******************";
		for (iterator = the_que.begin(), counter = 1; iterator != the_que.end(); iterator++, counter++)
		{
			//cout << endl << "******************";
			cout << endl << "K�plats: " << counter << " av totalt: " << Que_size() << " personer";
			cout << endl << "������������������" << endl;
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
//Menyval 4 - S�k efter personnummer i k�n och skriv ut dennes data.
void HousingQ::stalkPerson()
{
	//T�mmar Cmdwindow
	cout << string(50, '\n');
	cin.get();

	//Kollar om k�n �r tom
	if (the_que.isEmpty())
	{		
		cout << endl << "Du kan inte s�ka efter n�gon person eftersom listan �r tom..." << endl << endl;
	}

	else
	{
		//Lagra personnummer
		string persnr;

		cout << "Vad har personen du s�ker f�r personnummer?: ";
		getline(cin, persnr);

		//Skapar Iterator
		QIterator iterator;

		//Variabler f�r r�knare och tr�ff vid s�kning
		int search_hit = 0;
		int counter;

		//Stegar igenom k�n
		for (iterator = the_que.begin(), counter = 1; iterator != the_que.end(); iterator++, counter++)
		{
			//Om aktuell nod �r = persnr vi s�ker
			if ((*iterator).getPersNr() == persnr)
			{
				search_hit = 1;
				break;
			}
		}

		//Om personen hittades
		if (search_hit == 1)
		{
			cout << endl << "K�plats: " << counter << " av totalt: " << Que_size() << " personer";
			cout << endl << "������������������" << endl;
			cout << "Namn: " << (*iterator).getName().getFirstName() << " " << (*iterator).getName().getLastName() << endl;
			cout << "Gatuadress: " << (*iterator).getAddress().getGatu_Address() << endl;
			cout << "Postadress: " << (*iterator).getAddress().getZipCode() << " " << (*iterator).getAddress().getStad() << endl;
			cout << "Personnr: " << (*iterator).getPersNr() << endl;
			cout << "Skostorlek: " << (*iterator).getshoeSIZE();
			cout << endl << "******************";
		}
		else
		{
			cout << endl << "Fel personnummer eller s� existerar inte personen i v�rat k�system...";
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
	//T�mmar Cmdwindow
	cout << string(50, '\n');

	//L�ser av newline
	cin.get();

	//Kollar om k�n �r tom
	if (the_que.isEmpty())
	{
		cout << endl << "Error, k�n �r redan tom s� lycka till med att deleta n�gon :)" << endl << endl;		
	}

	//G� vidare med att hitta & ta bort person
	else
	{
		//Lagra personnummer
		string persnr;

		cout << "Vad har personen du vill ta bort f�r personnummer?: ";
		getline(cin, persnr);

		//Skapar Iterator
		QIterator iterator;

		//Variabler f�r r�knare och tr�ff vid s�kning
		int search_hit = 0;
		int counter;

		//S�ker efter personnummer
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
			cout << endl << "Personen du vill ta bort �r f�ljande: " << endl << endl;
			cout << endl << "K�plats: " << counter << " av totalt: " << Que_size() << " personer";
			cout << endl << "������������������" << endl;
			cout << "Namn: " << (*iterator).getName().getFirstName() << " " << (*iterator).getName().getLastName() << endl;
			cout << "Gatuadress: " << (*iterator).getAddress().getGatu_Address() << endl;
			cout << "Postadress: " << (*iterator).getAddress().getZipCode() << " " << (*iterator).getAddress().getStad() << endl;
			cout << "Personnr: " << (*iterator).getPersNr() << endl;
			cout << "Skostorlek: " << (*iterator).getshoeSIZE();
			cout << endl << "******************";


			cout << endl << endl << "Vill du ta bort personen? yes/no ";
			string answer;
			getline(cin, answer);

			//Om man vill ta bort personen s�..
			if (answer == "yes")
			{
				
				the_que.del(*iterator);
				cout << endl << "Personen med personnummer " << persnr << " har tagits bort ur systemet..";
			}
		}
		else
		{
			cout << endl << "Fel personnummer eller s� existerar inte personen i v�rat k�system...";
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
//	// Kollar om anv�nderen anger filen med .txt i slutet, l�gger annars till det.
//	//------------------------------------------------------------------------------
//Kontrollerar s� att k�n ej �r tom
	if (the_que.isEmpty())
	{
		cout << endl << "Error, k�n �r tom, on�digt att spara en tom fil.." << endl << endl;
	}

	//Var listan inte tom s� spara till fil..
	else
	{

		// J�mf�r och l�gger till .txt om det saknas..
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
		//	// �ppna filen f�r skrivning
		//	//------------------------------------------------------------------------------
		if (QueListFile.is_open())
		{
			// Skapar iterator
			QIterator iterator;

			// G�r igenom hela listan
			for (iterator = the_que.begin(); iterator != the_que.end(); iterator++)
			{
				QueListFile << *iterator << endl;
			}
			cout << endl << "Registret har sparats till " << FileName;
		}
		else
		{
			// Filen kunde ej �ppnas av ngn anledning

			cout << endl << "Error, Filen kunde ej �ppnas" << endl << endl;
		}
		//St�ng filen
		QueListFile.close();
	}
	cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
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
	// Kollar om anv�nderen anger filen med .txt i slutet, l�gger annars till det.
	/*string tmpstring;
	string compare = ".txt";
	FileName.substr(FileName.size() - 3, 3);

	if (compare != tmpstring)
	{
		FileName = FileName + compare;
	}*/

	//------------------------------------------------------------------------------
	// �ppna filen f�r l�sning
	//------------------------------------------------------------------------------
	QueListFile.open(FileName, ios::in);
	if (QueListFile.is_open()) //Gick det bra att �ppna filen
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
