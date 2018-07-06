/*
* Filnamn: Bank.cpp
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* Filen anv�nds mest till ett par kontroller och
* kommunicerar mellan BankKund och Testapp genom
* dess medlemsfunktioner
*
*/

#include "Bank.h"

Bank::Bank(){}

Bank::Bank(string name, string pNr)
{}

//H�mtar kundens namn
string Bank::getName() const
{
	
	return kund->getBankKundName();
}

//H�mtar kundens personnummer
string Bank::getPersnr() const
{
	return kund->getPersNR();
}

//H�mtar antalet konton kunden har
int Bank::getNrAccounts() const
{
	return kund->getNrofAccounts();
}

// H�mtar kundens alla kontonummer
bool Bank::getAccountNumbers(vector<string> &vec) const
{
	return kund->getAccountNumbers(vec);
}

// H�mtar kundens totala tillg�ngar
double Bank::getAssets() const
{
	return kund->getAccountsAssets();
}

// H�mtar kontoinformation f�r specifikt konto
bool Bank::getAccountInfo(string & accNR, vector<int>& vec) const
{
	return kund->getAccInfo(accNR, vec);
}

//Ta ut fr�n konto
bool Bank::withdraw(string accNr, int ammount)
{
	return kund->makeWithdrawal(accNr, ammount);
}

//S�tt in p� konto
bool Bank::deposit(string accNr, int ammount)
{
	return kund->makeDeposit(accNr, ammount);
}


//�ndra credit
bool Bank::credit(string accNr, int credit)
{
	return kund->setCredit(accNr, credit);
}

//Returnera summering av konton
bool Bank::getSummery(vector<string>& accNr, vector<int>& summery, vector<string>& acctype, vector<int> &transactions) const
{
	return kund->getSummery(accNr, summery, acctype, transactions);
}

//Returnera om det gick bra att ta bort konto
bool Bank::deleteAccount(string accNr)
{
	return kund->delAcc(accNr);
}



//Skapar kund
bool Bank::createCustomer(string name, string pNr)
{
	//Kontrollerar s� att inte kunden redan finns
	ifstream inFile(pNr + ".knt");
	if (inFile.is_open())
	{
		inFile.close();
		return  false;
	}
	//Fanns inte kunden s� skapa ny kund
	else
	{
		kund.reset(new BankKund(name, pNr));
		return true;
	}
}

//Skapar nytt bankkonto f�r kunden
bool Bank::createNewAccount(string type, double credit, double balance, int nrWithdrawals)
{
	return kund->createAccount(type, credit, balance, nrWithdrawals);
}

//L�s fr�n fil
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




