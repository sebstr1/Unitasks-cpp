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
//F�rvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
PersonList::PersonList()
{
	string FileName = "";
}
//------------------------------------------------------------------------------
//Konstruktor f�r initiering av datamedlemmarna
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

//Sortera p� namn
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


// L�s fr�n fil
void PersonList::readFromFile()
{
	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel) och filnamn
	//------------------------------------------------------------------------------
	fstream vectorFile;
	string fileName;
	
	fileName = getFileName();

	// Kollar om anv�nderen anger filen med .txt i slutet, l�gger annars till det.
	string tmpstring;
	string compare = ".txt";
	fileName.substr(fileName.size() - 3, 3);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	// T�mmer listan innan inl�sning..
	if (!PersonLista.empty())
		PersonLista.clear();
	//------------------------------------------------------------------------------
	// �ppna filen f�r l�sning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::in);
	if (vectorFile.is_open()) //Gick det bra att �ppna filen
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

	// Kollar om anv�nderen anger filen med .txt i slutet, l�gger annars till det.
	string tmpstring;
	string compare = ".txt";
	tmpstring = fileName.substr(fileName.size() - 4, 4);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	//------------------------------------------------------------------------------
	// �ppna filen f�r skrivning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::out);
	if (vectorFile.is_open()) // Gick det bra att �ppna filen
	{
		//size_t count = 1;
		for (auto index : PersonLista)
		{	//Skriver namn, efternamn, signatur och l�ngd med DELIM mellan varje.
			vectorFile << index << endl;

			//if (count++ < PersonLista.size()) //Skriv nyradstecken p� alla rader utom sista
			//	vectorFile << endl;
		}
		//St�nger filen.
		vectorFile.close();
	}

	cout << endl << "Registret har sparats till " << fileName;
	cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
	cin.get();
}