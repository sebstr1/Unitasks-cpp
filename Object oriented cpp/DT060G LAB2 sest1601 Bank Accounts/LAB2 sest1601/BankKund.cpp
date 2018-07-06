/*
* Filnamn: BankKund.cpp
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* Filen definerar funktionerna f�r klassen BankKund
* som �r en tyst klass som skickar och tar emot data (kommunicerar)
* mellan klassen Bank och Konto
*/
#include "BankKund.h"
#include <algorithm>
//Standard konstruktor
BankKund::BankKund()
{
}


//�verladdad konstruktor
BankKund::BankKund(string name, string pNR)
{
	Name = name;
	persNR = pNR;

}


//Returnerar kundens f�r och efternamn som en str�ng
string BankKund::getBankKundName()
{
	return Name;
}

//Returnerar Kundens personNR
string BankKund::getPersNR()
{
	return persNR;
}

// Returnerar antalet konton
int BankKund::getNrofAccounts()
{
	return bankAccounts.size();
}

//Returnerar alla kontonummer f�r kunden
bool BankKund::getAccountNumbers(vector<string> &konto) const
{
	//Om antalet konton �r mindre �n 1
	if (bankAccounts.size() < 1)
	{
		return false;
	}

	// H�mta kontonummren till vectorn som skapades i TestApp.cpp
	else
	{
		for (auto &i : bankAccounts)
		{
			konto.push_back(i->get_AccNR());
		}

		return true;
	}
}

double BankKund::getAccountsAssets()
{
	double totAsset = 0;

	for (auto &i : bankAccounts)
	{
		totAsset += i->get_Available_Assets();
	}

	return totAsset;
}

bool BankKund::getAccInfo(string &accNR, vector<int> &vec) const
{
	for (auto &i : bankAccounts) //Per konto
	{
		if (accNR == i->get_AccNR()) //Korrekt konto?
		{
			vec.push_back(i->get_Balance());			// L�gg till saldo i vectorn
			vec.push_back(i->get_credit());				// L�gg till kredit i vectorn
			vec.push_back(i->get_Available_Assets());	// L�gg till tillg�ngar i vectorn
			return true;								//S�kning klar return true
		}
	}
	return false; // Om KontoNr ej hittades
}

bool BankKund::makeWithdrawal(string accNr, int ammount)
{
	for (auto &i : bankAccounts) //Per konto
	{
		if (accNr == i->get_AccNR()) //Korrekt konto?
		{
			i->Withdraw(ammount);	// Ta bort summa fr�n kontot
			return true;			//S�kning klar return true
		}
	}
	return false; // Om KontoNr ej hittades
}

bool BankKund::makeDeposit(string accNr, int ammount)
{
	for (auto &i : bankAccounts) //Per konto
	{
		if (accNr == i->get_AccNR()) //Korrekt konto?
		{
			i->Deposit(ammount);	// L�gg till summa p� kontot
			return true;			//S�kning klar return true
		}
	}
	return false; // Om KontoNr ej hittades
}

bool BankKund::changeCredit(string accNr, int credit)
{
	for (auto &i : bankAccounts) //Per konto
	{
		if (accNr == i->get_AccNR()) //Korrekt konto?
		{
			i->Change_Credit(credit);	// L�gg till summa p� kontot
			return true;			//S�kning klar return true
		}
	}
	return false; // Om KontoNr ej hittades
}

bool BankKund::getSummery(vector<string>& accNr, vector<int>& summery) const
{
	for (auto &i : bankAccounts) //Per konto
	{
		accNr.push_back(":::: " + i->get_AccNR() + " ::::");
		summery.push_back(i->get_Balance());			// L�gg till saldo i vectorn
		summery.push_back(i->get_credit());				// L�gg till kredit i vectorn
		summery.push_back(i->get_Available_Assets());	// L�gg till tillg�ngar i vectorn			
	}
	//Om kontovectorn inneh�ller mindre �n 1 kontonr (dvs 0 konton) returnera false
	if (accNr.size() < 1)
	{
		return false;
	}
	else
	{
		return true;
	}
	
	
}

bool BankKund::delAcc(string accNr)
{
		

	//Letar upp kontoNr i vectorn.
	auto it = find_if(bankAccounts.begin(), bankAccounts.end(),
		[accNr](unique_ptr<Konto> &b1)
	{
		//Kontrollerar om kontot existerade		
		return (b1->get_AccNR()) == accNr;
	});
	//Om kontot existerade, ta bort det.
	if (it != bankAccounts.end())
	{
		bankAccounts.erase(it);
		return true;

	}
	// Om kontot inte fanns returnara false
	else
	{
		return false;
	}

}

// Set funktioner --------------------------------------------

void BankKund::setFirstname(string name)
{
	Name = name;

}


void BankKund::setPersNR(string pNR)
{
	persNR = pNR;
}


//Skapar konto
bool BankKund::createAccount(double balance, double credit)
{
	size_t AccNumber = 1;
	bool one = false;
	bool two = false;
	bool three = false;
	//Om inte redan 3 konton finns
	if (bankAccounts.size() < 3)// && accountNr < 4)
	{
		for (auto &i : bankAccounts)
		{
			if (i->get_AccNR() == persNR + "-" + "1")
			{
				one = true;
				
			}

			if (i->get_AccNR() == persNR + "-" + "2")
			{
				two = true;
				
			}
			if (i->get_AccNR() == persNR + "-" + "3")
			{
				three = true;
				
			}
		}

		//Skapar kontonrsIdentifierare (1 till 3)
		if (one == false)
		{
			AccNumber = 1;
			
		}
		else if (two == false)
		{
			AccNumber = 2;
		}
		else if (three == false)
		{
			AccNumber = 3;
		}

	
		//Skapar Nytt konto med hj�lp av konstruktorn i konto.cpp
		bankAccounts.push_back(unique_ptr<Konto>(new Konto(persNR, AccNumber, balance, credit)));
		sort(bankAccounts.begin(), bankAccounts.end(), [](unique_ptr<Konto> &a1, unique_ptr<Konto> &a2)
		{
			return a1->get_AccNR() < a2->get_AccNR();
		});
		return true;
	}
	else
	{
		return false;
	}
}

bool BankKund::ReadFromFile(string pnr)
{
	//Initierar tempor�ra variabler
	string tmpKontoNR;
	double tmpBalance;
	double tmpCredit;

	//Kontrollerar om kundfilen g�r att �ppna (existerar)
	ifstream inFile(pnr + ".knt");
	if (inFile.is_open())
	{
		//L�ser in Namn och personnummer
		getline(inFile, Name);
		inFile >> persNR;
		// S� l�nge det g�r att l�sa fr�n filen, l�s in kontonr, balans och kredit, skapa sedan kontot
		while (true)
		{
			if (!(inFile >> tmpKontoNR)) break;
			if (!(inFile >> tmpBalance)) break;
			if (!(inFile >> tmpCredit)) break;
			createAccount(tmpBalance, tmpCredit);
		}
		return true;
	}
	// Om kundfilen inte fanns s� returnera false
	else
	{
		return false;
	}


}


void BankKund::saveToFile()
{
	ofstream outFile(persNR + ".knt");

	outFile << Name << endl << persNR << endl;

	for (auto &i : bankAccounts)
	{
		outFile << i->get_AccNR() << endl
		<< i->get_Balance() << endl << i->get_credit() << endl;

	}

	outFile.close();
}