// PersonList.h
#ifndef PersonListH
#define PersonListH

#include <vector>
#include <string>
#include <iostream>
#include "Person.h"
using namespace std;

class PersonList
{
private:
	// Medlem
	vector <Person> PersonLista;
	string FileName;

public:
	//Standardkonstruktorn
	PersonList();
	//Överlagrad kons
	PersonList(vector <Person> pVEC, string pFileName);

	// Set
	void setFileName(string pFileName);

	//Get
	string getFileName() const;


	// Funktioner för medlemmar
	void addPerson(Person &person_objekt);

	Person PersonList::getPerson(int indexPos);
	
	int PersonList::antal_personer()const;

	//Sorteringsfunktioner
//-------------------------------------------------------------------------------------
	//Sortera per namn
	void sortName();
	static bool compareNames(const Person &obj1, const Person &obj2);
	
	//Sortera efter PersNr
	void sortPersnr();
	static bool PersonList::comparePersNr(const Person &obj1, const Person &obj2);

	//Sortera efter Skostorlek
	void sortShoenr();
	static bool compareShoenr(const Person & obj1, const Person & obj2);
//--------------------------------------------------------------------------------------

	//Skriv till fil
	void writeToFile();

	// Läs från fil
	void readFromFile();






};
#endif