//klassFUNK.cpp

#include "klassDef.h"
#include <iostream>
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