//PersonList.cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include "PersonList.h"
#include "name.h"
using namespace std;



//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
PersonList::PersonList()
{
	string FileName = "";
}
//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
PersonList::PersonList(vector<Person> pVEC, string pFileName)
{
	FileName = pFileName;
	PersonLista = pVEC;	
}
//------------------------------------------------------------------------------
// Set Filename.
//------------------------------------------------------------------------------
void PersonList::setFileName(string pFileName)
{
	FileName = pFileName;
}
//------------------------------------------------------------------------------
// Get FileName.
//------------------------------------------------------------------------------
string PersonList::getFileName() const
{
	return FileName;
}
//------------------------------------------------------------------------------
// Add Person.
//------------------------------------------------------------------------------
void PersonList::addPerson(Person &person_objekt)
{
	PersonLista.push_back(person_objekt);
}
//------------------------------------------------------------------------------
// Get Person
//------------------------------------------------------------------------------
Person PersonList::getPerson(int indexPos)
{
	Person pObjekt = PersonLista[indexPos];

	return pObjekt;
}

//------------------------------------------------------------------------------
// Aktuellt antal Personer i listan
//------------------------------------------------------------------------------
int PersonList::antal_personer() const
{
	
	return PersonLista.size();
}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Sorteringsfunktioner
//------------------------------------------------------------------------------

//Sortera på namn
void PersonList::sortName()
{
	sort(PersonLista.begin(), PersonLista.end(), compareNames);
}

bool PersonList::compareNames(const Person &obj1, const Person &obj2)
{
	if (obj1.getName().getLastName() == obj2.getName().getLastName())
	{
		return obj1.getName().getFirstName() < obj2.getName().getFirstName();
	}

	else
	{
		return obj1.getName().getLastName() < obj2.getName().getLastName();
	}	
}
//-------------------------------------------------------------------------------

//Sortera efter personnummer

void PersonList::sortPersnr()
{
	sort(PersonLista.begin(), PersonLista.end(), comparePersNr);
}

bool PersonList::comparePersNr(const Person & obj1, const Person & obj2)
{
	return obj1.getPersNr() < obj2.getPersNr();
}
//-------------------------------------------------------------------------------

//Sortera efter skostorlek

void PersonList::sortShoenr()
{
	sort(PersonLista.begin(), PersonLista.end(), compareShoenr);
}

bool PersonList::compareShoenr(const Person & obj1, const Person & obj2)
{
	return obj1.getshoeSIZE() < obj2.getshoeSIZE();
}
//---------------------------------------------------------------------------- 
// ***************************************************************************
//----------------------------------------------------------------------------


// Läs från fil
void PersonList::readFromFile()
{
	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel) och filnamn
	//------------------------------------------------------------------------------
	fstream vectorFile;
	string fileName;
	
	fileName = getFileName();

	// Kollar om använderen anger filen med .txt i slutet, lägger annars till det.
	string tmpstring;
	string compare = ".txt";
	fileName.substr(fileName.size() - 3, 3);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	// Tömmer listan innan inläsning..
	if (!PersonLista.empty())
		PersonLista.clear();
	//------------------------------------------------------------------------------
	// Öppna filen för läsning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::in);
	if (vectorFile.is_open()) //Gick det bra att öppna filen
	{
		Person tmpPerson;


		while (vectorFile >> tmpPerson)
		{
			PersonLista.push_back(tmpPerson);
		}

	}
}



//Skriv till fil.txt
void PersonList::writeToFile()
{

	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel) och filnamn
	//------------------------------------------------------------------------------
	fstream vectorFile;
	string fileName;
	
	fileName = getFileName();

	// Kollar om använderen anger filen med .txt i slutet, lägger annars till det.
	string tmpstring;
	string compare = ".txt";
	tmpstring = fileName.substr(fileName.size() - 4, 4);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	//------------------------------------------------------------------------------
	// Öppna filen för skrivning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::out);
	if (vectorFile.is_open()) // Gick det bra att öppna filen
	{
		//size_t count = 1;
		for (auto index : PersonLista)
		{	//Skriver namn, efternamn, signatur och längd med DELIM mellan varje.
			vectorFile << index << endl;

			//if (count++ < PersonLista.size()) //Skriv nyradstecken på alla rader utom sista
			//	vectorFile << endl;
		}
		//Stänger filen.
		vectorFile.close();
	}

	cout << endl << "Registret har sparats till " << fileName;
	cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
	cin.get();
}