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
#include "Konto.h"
using namespace std;

void Konto::setAccountNumber(string setString)
{
	string accString = setString;
	accountNumber = accString;
}

//-----Konstruktor
Konto::Konto(string pNR, size_t AccIdentifier, double pBalance)
{
	string accountsize = to_string(AccIdentifier);
	accountNumber = pNR + "-" + accountsize;
	Balance = pBalance;
	
}

// Insättning på konto
void Konto::Deposit(double valuetoAdd)
{
	Balance = Balance + valuetoAdd;
}

//Utför uttag av från konto
bool Konto::withdrawal(double sum)
{
	Balance = Balance - sum;
	return true;
}
	

//Returnerar aktuellt kontonummer
string Konto::get_AccNR()
{
	return accountNumber;
}

//Returnerar aktuell kontosaldo
double Konto::get_Balance()
{
	return Balance;
}

//Summerar och returnerar tillgångar
double Konto::get_Available_Assets()
{
	double ammount;
	ammount = Balance + getCredit();
	return ammount;
}


// Standard konstruktor
Konto::Konto()
{
}

