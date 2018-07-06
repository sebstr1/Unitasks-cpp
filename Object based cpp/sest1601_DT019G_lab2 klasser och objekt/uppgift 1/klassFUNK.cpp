//klassFUNK.cpp

#include "klassDef.h"
#include <iostream>
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