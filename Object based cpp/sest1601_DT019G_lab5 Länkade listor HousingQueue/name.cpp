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
//F�rvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Name::Name()
{
	FirstName = "";
	LastName = "";
}

//------------------------------------------------------------------------------
//Konstruktor f�r initiering av datamedlemmarna
//------------------------------------------------------------------------------
Name::Name(string pFirstName, string pLastName)
{
	FirstName = pFirstName;
	LastName = pLastName;
}

//------------------------------------------------------------------------------
// SetFirstname s�tt F�rnamn...
//------------------------------------------------------------------------------
void Name::setFirstName(string pFirstName)
{
	FirstName = pFirstName;
}

//------------------------------------------------------------------------------
// SetLastname s�tt efternamn...
//------------------------------------------------------------------------------
void Name::setLastName(string pLastName)
{
	LastName = pLastName;
	;
}

//------------------------------------------------------------------------------
// getFirstname h�mta f�rnamn...
//------------------------------------------------------------------------------
string Name::getFirstName() const
{
	return FirstName;
}
//------------------------------------------------------------------------------
// getLastname h�mta efternamn...
//------------------------------------------------------------------------------
string Name::getLastName() const
{
	return LastName;
}

// �verlagring av < operatorn
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

// �verlagring av == operatorn
bool Name::operator==(const Name &name) const
{
	
	return LastName == name.getLastName() && FirstName == name.getFirstName();
	
	
}

// Avgr�nsare i fil
const char DELIM = '|';

//�verlagring av << utskriftsoperatorn
ostream &operator<<(ostream &os, const Name &n)
{
	os << n.getFirstName() << DELIM << n.getLastName() << DELIM;

	return os;
}

// �verlagring av >> inl�sningsoperatorn
istream &operator >> (istream &is, Name &n)
{
	string s;

	getline(is, s, DELIM);
	n.setFirstName(s);

	getline(is, s, DELIM);
	n.setLastName(s);

	return is;
}