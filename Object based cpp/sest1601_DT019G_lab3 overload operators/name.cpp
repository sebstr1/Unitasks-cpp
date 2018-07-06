//klassFUNK.cpp
#include <iostream>
#include <string>
#include "name.h"
#include "Person.h"
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Name::Name()
{
	FirstName = "";
	LastName = "";
}

//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
Name::Name(string pFirstName, string pLastName)
{
	FirstName = pFirstName;
	LastName = pLastName;
}

//------------------------------------------------------------------------------
// SetFirstname sätt Förnamn...
//------------------------------------------------------------------------------
void Name::setFirstName(string pFirstName)
{
	FirstName = pFirstName;
}

//------------------------------------------------------------------------------
// SetLastname sätt efternamn...
//------------------------------------------------------------------------------
void Name::setLastName(string pLastName)
{
	LastName = pLastName;
	;
}

//------------------------------------------------------------------------------
// getFirstname hämta förnamn...
//------------------------------------------------------------------------------
string Name::getFirstName() const
{
	return FirstName;
}
//------------------------------------------------------------------------------
// getLastname hämta efternamn...
//------------------------------------------------------------------------------
string Name::getLastName() const
{
	return LastName;
}

// Överlagring av < operatorn
bool Name::operator<(const Name &name) const
{

	if (LastName == name.getLastName())
	{
		return (FirstName) < (name.getFirstName());
	}
	else
	{
		return (LastName) < (name.getLastName());
	}

	
}

// Överlagring av == operatorn
bool Name::operator==(const Name &name) const
{
	
	return LastName == name.getLastName() && FirstName == name.getFirstName();
	
	
}

// Avgränsare i fil
const char DELIM = '|';

//Överlagring av << utskriftsoperatorn
ostream &operator<<(ostream &os, const Name &n)
{
	os << n.getFirstName() << DELIM << n.getLastName() << DELIM;

	return os;
}

// Överlagring av >> inläsningsoperatorn
istream &operator >> (istream &is, Name &n)
{
	string s;

	getline(is, s, DELIM);
	n.setFirstName(s);

	getline(is, s, DELIM);
	n.setLastName(s);

	return is;
}