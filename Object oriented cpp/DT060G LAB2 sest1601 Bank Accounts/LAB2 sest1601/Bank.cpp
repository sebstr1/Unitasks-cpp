/*
* Filnamn: Bank.cpp
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* Filen används mest till ett par kontroller och
* kommunicerar mellan BankKund och Testapp genom
* dess medlemsfunktioner
*
*/

#include "Bank.h"

Bank::Bank()
{
}

Bank::Bank(string name, string pNr)
{

}

//Hämtar kundens namn
string Bank::getName() const
{
	
	return kund->getBankKundName();
}

//Hämtar kundens personnummer
string Bank::getPersnr() const
{
	return kund->getPersNR();
}

//Hämtar antalet konton kunden har
int Bank::getNrAccounts() const
{
	return kund->getNrofAccounts();
}

// Hämtar kundens alla kontonummer
bool Bank::getAccountNumbers(vector<string> &vec) const
{
	return kund->getAccountNumbers(vec);
}

// Hämtar kundens totala tillgångar
double Bank::getAssets() const
{
	return kund->getAccountsAssets();
}

// Hämtar kontoinformation för specifikt konto
bool Bank::getAccountInfo(string & accNR, vector<int>& vec) const
{
	return kund->getAccInfo(accNR, vec);
}

//Ta ut från konto
bool Bank::withdraw(string accNr, int ammount)
{
	return kund->makeWithdrawal(accNr, ammount);
}

//Sätt in på konto
bool Bank::deposit(string accNr, int ammount)
{
	return kund->makeDeposit(accNr, ammount);
}


//Ändra credit
bool Bank::credit(string accNr, int credit)
{
	return kund->changeCredit(accNr, credit);
}

bool Bank::getSummery(vector<string>& accNr, vector<int>& summery) const
{
	return kund->getSummery(accNr, summery);
}

bool Bank::deleteAccount(string accNr)
{
	return kund->delAcc(accNr);
}



//Skapar kund
bool Bank::createCustomer(string name, string pNr)
{
	//Kontrollerar så att inte kunden redan finns
	ifstream inFile(pNr + ".knt");
	if (inFile.is_open())
	{
		inFile.close();
		return  false;
	}
	//Fanns inte kunden så skapa ny kund
	else
	{
		kund.reset(new BankKund(name, pNr));
		return true;
	}
}

//Skapar nytt bankkonto för kunden
bool Bank::createNewAccount(double credit, double balance)
{
	return kund->createAccount(credit, balance);
}

//Läs från fil
bool Bank::ReadFile(string pnr)
{
	kund.reset(new BankKund());
	return kund->ReadFromFile(pnr);
}

//Spara till fil
void Bank::saveFile()
{
	kund->saveToFile();
}



