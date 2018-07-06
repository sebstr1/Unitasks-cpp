//Person.h
#include "Person.h"
#include <iostream>
#include <sstream>
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//F�rvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Person::Person()
{
	PersNr = "";
	shoeSIZE = 0;
}

//------------------------------------------------------------------------------
//Konstruktor f�r initiering av datamedlemmarna
//------------------------------------------------------------------------------
Person::Person(Name pName, Address pAddress, string pPersNr, int pshoeSIZE)
{
	name = pName;
	address = pAddress;
	PersNr = pPersNr;
	shoeSIZE = pshoeSIZE;
}
//------------------------------------------------------------------------------
// S�ttnamn
//------------------------------------------------------------------------------
void Person::setName(Name pName)
{
	name = pName;
}
//------------------------------------------------------------------------------
// Adress...
//------------------------------------------------------------------------------
void Person::setAddress(Address pAddress)
{
	address = pAddress;
}
//------------------------------------------------------------------------------
// Personnr.
//------------------------------------------------------------------------------
void Person::setPersNr(string pPersNr)
{
	PersNr = pPersNr;
}
//------------------------------------------------------------------------------
// Skostorlek..
//------------------------------------------------------------------------------
void Person::setshoeSIZE(int pshoeSIZE)
{
	shoeSIZE = pshoeSIZE;
}
//------------------------------------------------------------------------------
// H�mta Namn...
//------------------------------------------------------------------------------
Name Person::getName() const
{
	return name;
}
//------------------------------------------------------------------------------
// H�mta Address...
//------------------------------------------------------------------------------
Address Person::getAddress() const
{
	return address;
}
//------------------------------------------------------------------------------
// H�mta PersonNr...
//------------------------------------------------------------------------------
string Person::getPersNr() const
{
	return PersNr;
}
//------------------------------------------------------------------------------
// H�mta Skostorlek...
//------------------------------------------------------------------------------
int Person::getshoeSIZE() const
{
	return shoeSIZE;
}

// �verlagring av < operatorn
bool Person::operator<(const Person &person) const
{
	
	if (name == person.getName())
	{
		return (address) < (person.getAddress());
	}
	else
	{
		return (name) < (person.getName());
	}

}

// �verlagring av == operatorn
bool Person::operator ==(const Person &person) const
{
	return name == person.getName() && address == person.getAddress() && PersNr == person.getPersNr() && shoeSIZE == person.getshoeSIZE();
}

// Avgr�nsare f�r utskrift till fil
const char DELIM = '|';

// �verlagring av << utskriftsoperatorn

ostream & operator<<(ostream & os, const Person & person)
{
	os << person.getName() << person.getAddress() << person.getPersNr() << DELIM << person.getshoeSIZE();

	return os;
}

// �verlagring av >> inmatningsoperatorn
istream &operator >> (istream &is, Person &person)
{
	Name n;
	Address a;
	string s;

	is >> n;
	person.setName(n);

	is >> a;
	person.setAddress(a);

	getline(is, s, DELIM);
	person.setPersNr(s);

	// Str�ngstr�m f�r att kunna anv�nda getline p� en int och sen
	// omvandla str�ngen till en integer
	getline(is, s);
	int shoeSize = 0;
	stringstream Shoestream(s);
	Shoestream >> shoeSize;
	person.setshoeSIZE(shoeSize);

	return is;
}