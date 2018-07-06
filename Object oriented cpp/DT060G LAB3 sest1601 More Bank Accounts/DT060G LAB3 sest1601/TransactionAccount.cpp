/*
* Filnamn: Konto.cpp
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* nyttjar den tysta klassen Banks medlemsfunktioner
* som hanterar Bankkonton �t BankKunder...
*
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "TransactionAccount.h"
using namespace std;

//Standrard konstruktor
TransactionsAccount::TransactionsAccount()
{
}

bool TransactionsAccount::withdrawal(double sum)
{
	if (sum <= Konto::get_Available_Assets())
		// Om inte max antal uttag gjorts och summan �r mindre �n saldo
	{
		return Konto::withdrawal(sum);
		// G�r uttag, true om det finns pengar annars false.
	}
	else
		return false; // Annars returnera false
	
}

// Skapar konto av typen TransactionAccount med hj�lp av konstruktorn fr�n konto
TransactionsAccount::TransactionsAccount(string pNR, size_t AccIdentifier, double pCredit, double pBalance) : Konto(pNR, AccIdentifier, pBalance)
{
	credit = pCredit;
}

//TransactionsAccount::TransactionsAccount(string pNR, size_t AccIdentifier, double pBalance)
//{
//}
