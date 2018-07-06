//Person.h
#include "Person.h"
#include <iostream>
#include <sstream>
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Person::Person()
{
	PersNr = "";
	shoeSIZE = 0;
}

//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
Person::Person(Name pName, Address pAddress, string pPersNr, int pshoeSIZE)
{
	name = pName;
	address = pAddress;
	PersNr = pPersNr;
	shoeSIZE = pshoeSIZE;
}
//------------------------------------------------------------------------------
// Sättnamn
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
// Hämta Namn...
//------------------------------------------------------------------------------
Name Person::getName() const
{
	return name;
}
//------------------------------------------------------------------------------
// Hämta Address...
//------------------------------------------------------------------------------
Address Person::getAddress() const
{
	return address;
}
//------------------------------------------------------------------------------
// Hämta PersonNr...
//------------------------------------------------------------------------------
string Person::getPersNr() const
{
	return PersNr;
}
//------------------------------------------------------------------------------
// Hämta Skostorlek...
//------------------------------------------------------------------------------
int Person::getshoeSIZE() const
{
	return shoeSIZE;
}

// Överlagring av < operatorn
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

// Överlagring av == operatorn
bool Person::operator ==(const Person &person) const
{
	return name == person.getName() && address == person.getAddress() && PersNr == person.getPersNr() && shoeSIZE == person.getshoeSIZE();
}

// Avgränsare för utskrift till fil
const char DELIM = '|';

// Överlagring av << utskriftsoperatorn

ostream & operator<<(ostream & os, const Person & person)
{
	os << person.getName() << person.getAddress() << person.getPersNr() << DELIM << person.getshoeSIZE();

	return os;
}

// Överlagring av >> inmatningsoperatorn
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

	// Strängström för att kunna använda getline på en int och sen
	// omvandla strängen till en integer
	getline(is, s);
	int shoeSize = 0;
	stringstream Shoestream(s);
	Shoestream >> shoeSize;
	person.setshoeSIZE(shoeSize);

	return is;
}