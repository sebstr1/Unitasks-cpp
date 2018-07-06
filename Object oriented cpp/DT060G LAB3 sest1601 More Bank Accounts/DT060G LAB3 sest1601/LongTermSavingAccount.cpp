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
#include "LongTermSavingAccount.h"
using namespace std;




LongTermSavingsAccount::LongTermSavingsAccount(string pNR, size_t AccIdentifier, double pBalance) : SavingsAccount(pNR, AccIdentifier, pBalance)
{
}
