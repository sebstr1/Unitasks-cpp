//address.cpp
#include <iostream>
#include "address.h"
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Address::Address()
{
	Gatu_Address = "";
	ZipCode = "";
	Stad = "";
}

//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
Address::Address(string pGatu_Address, string pStad, string pZipCode)
{
	Gatu_Address = pGatu_Address;
	ZipCode = pZipCode;
	Stad = pStad;
}

//------------------------------------------------------------------------------
// GatuAdress...
//------------------------------------------------------------------------------
void Address::setGatu_Address(string pGatu_Address)
{
	Gatu_Address = pGatu_Address;
}

//------------------------------------------------------------------------------
// Stad...
//------------------------------------------------------------------------------
void Address::setStad(string pStad)
{
	Stad = pStad;

}

//------------------------------------------------------------------------------
// Postnummer..
//------------------------------------------------------------------------------

void Address::setZipCode(string pZipCode)
{
	ZipCode = pZipCode;

}

//------------------------------------------------------------------------------
// Hämta Gatuadress..
//------------------------------------------------------------------------------
string Address::getGatu_Address() const
{
	return Gatu_Address;
}
//------------------------------------------------------------------------------
// Hämta stad...
//------------------------------------------------------------------------------
string Address::getStad() const
{
	return Stad;
}

string Address::getZipCode() const
{
	return ZipCode;
}

// Överlagring av < operatorn
bool Address::operator<(const Address &a) const
{
	if (Stad == a.getStad())
	{
		return (Gatu_Address) < (a.getGatu_Address());
	}
	else
	{
		return (Stad) < (a.getStad());
	}
}

// Överlagring av == operatorn
bool Address::operator==(const Address &a) const
{
	return Stad == a.getStad() && Gatu_Address == a.getGatu_Address();
}


// Avgränsare i fil
const char DELIM = '|';

//Överlagring av << utskriftsoperatorn
ostream &operator<<(ostream &os, const Address &a)
{
	os << a.getGatu_Address() << DELIM << a.getZipCode() << DELIM << a.getStad() << DELIM;

	return os;
}

// Överlagring av >> inläsningsoperatorn
istream &operator >> (istream &is, Address &a)
{
	string s;

	getline(is, s, DELIM);
	a.setGatu_Address(s);

	getline(is, s, DELIM);
	a.setZipCode(s);

	getline(is, s, DELIM);
	a.setStad(s);

	return is;
}