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
BankKund::BankKund() {}

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

//Summerar totala tillg�ngar & returnerar dessa
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
			vec.push_back(i->getCredit());				// L�gg till kredit i vectorn
			vec.push_back(i->get_Available_Assets());	// L�gg till tillg�ngar i vectorn
			vec.push_back(i->getInterestRate());
			vec.push_back(i->getMaxWithdrawals());
			vec.push_back(i->getWithdrawalCount());
			accNR = i->getAccountType();
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
			return i->withdrawal(ammount);	// Ta bort summa fr�n kontot
			
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

bool BankKund::setCredit(string accNr, int credit)
{
	for (auto &i : bankAccounts) //Per konto
	{
		if (accNr == i->get_AccNR()) //Korrekt konto?
		{    
			return i->setCredit(credit);	// L�gg till summa p� kontot
			return true;			//S�kning klar return true
		}
	}
	return false; // Om KontoNr ej hittades
}

//Returnerar vectorer med information om konton
bool BankKund::getSummery(vector<string>& accNr, vector<int>& summery, vector<string>& acctype, vector<int>& transactions ) const
{
	for (auto &i : bankAccounts) //Per konto
	{
		accNr.push_back(":::: " + i->get_AccNR() + " ::::"); // L�gg till kontonr i vectorn
		acctype.push_back(i->getAccountType());			// L�gg till kontotyp i vectorn
		transactions.push_back(i->getMaxWithdrawals());	// L�gg till max uttag i vectorn
		transactions.push_back(i->getWithdrawalCount()); // L�gg till antal uttag i vecotrn
		summery.push_back(i->get_Balance());			// L�gg till saldo i vectorn
		summery.push_back(i->getCredit());				// L�gg till kredit i vectorn
		summery.push_back(i->get_Available_Assets());	// L�gg till tillg�ngar i vectorn
		summery.push_back(i->getInterestRate());		// L�gg till r�ntan i vectorn

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
bool BankKund::createAccount(string type, double balance, double credit, int nrWithdrawals)
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

		// Transaktionskonto
		if (type == "Transactionsaccount")
		{
			//Skapar Nytt konto med hj�lp av konstruktorn i TransactionsAccount
			bankAccounts.push_back(unique_ptr<Konto>(new TransactionsAccount(persNR, AccNumber, balance, credit)));
		}

		// Sparkonto
		if (type == "Savingsaccount")
		{
			//Skapar Nytt konto med hj�lp av konstruktorn i SavingsAccount.cpp
			bankAccounts.push_back(unique_ptr<Konto>(new SavingsAccount(persNR, AccNumber, balance, nrWithdrawals)));
		}

		// L�ngtidsSparkonto
		if (type == "Long Term Savingsaccount")
		{
			//Skapar Nytt konto med hj�lp av konstruktorn i LongTermSavingsAccount.cpp
			bankAccounts.push_back(unique_ptr<Konto>(new LongTermSavingsAccount(persNR, AccNumber, balance, nrWithdrawals)));
		}
		

		//Sorterar vectorn i nummerordning av namnet
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
	string tmpKontotyp;
	double tmpBalance;
	double tmpCredit;
	int tmpWithdrawals;

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
			inFile.get();
			if (!(getline(inFile, tmpKontotyp))) break;
			if (!(inFile >> tmpBalance)) break;
			if (!(inFile >> tmpCredit)) break;
			if (!(inFile >> tmpWithdrawals)) break;
			createAccount(tmpKontotyp, tmpBalance, tmpCredit, tmpWithdrawals);
		}
		return true;
	}
	// Om kundfilen inte fanns s� returnera false
	else
	{
		return false;
	}


}

// Skriver till fil
void BankKund::saveToFile()
{
	ofstream outFile(persNR + ".knt");

	// Skriver ut Namn och personnummer
	outFile << Name << endl << persNR << endl;

	//Loopar igenom alla konton
	for (auto &i : bankAccounts)
	{
		outFile 
		<< i->get_AccNR() << endl            //KontoNR
		<< i->getAccountType() << endl		//Kontotyp
		<< i->get_Balance() << endl			//Saldo
		<< i->getCredit() << endl			//Kredit
		<< i->getWithdrawalCount() << endl; //Antal uttag
	}

	outFile.close();
}