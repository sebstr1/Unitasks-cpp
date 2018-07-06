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
Konto::Konto(string pNR, size_t pBankAccountsSize, double pCredit, double pBalance)
{
	string accountsize = to_string(pBankAccountsSize);
	accountNumber = pNR + "-" + accountsize;
	Balance = pBalance;
	credit = pCredit;
}


void Konto::Deposit(double valuetoAdd)
{
	Balance = Balance + valuetoAdd;
}

void Konto::Withdraw(double valuetoWithdraw)
{
	Balance = Balance - valuetoWithdraw;
}

void Konto::Change_Credit(double changeCredit)
{
	credit = changeCredit;
}


//GET functions
string Konto::get_AccNR()
{
	return accountNumber;
}

double Konto::get_Balance()
{
	return Balance;
}

double Konto::get_Available_Assets()
{
	double ammount;
	ammount = Balance + credit;
	return ammount;
}

double Konto::get_credit()
{
	return credit;
}

Konto::Konto()
{
}

