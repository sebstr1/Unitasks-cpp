/*
* Filnamn: Konto.cpp
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* nyttjar den tysta klassen Banks medlemsfunktioner
* som hanterar Bankkonton åt BankKunder...
*
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "SavingsAccount.h"
using namespace std;

double SavingsAccount::getInterestRate()
{
	return interestRate;
}

bool SavingsAccount::withdrawal(double sum)
{
	return false;
}


SavingsAccount::SavingsAccount(string pNR, size_t AccIdentifier, double pBalance) : Konto(pNR, AccIdentifier, pBalance)
{	

}