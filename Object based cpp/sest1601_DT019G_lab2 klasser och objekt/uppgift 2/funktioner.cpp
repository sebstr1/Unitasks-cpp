//klassFUNK.cpp

#include "Header.h"
#include <iostream>
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