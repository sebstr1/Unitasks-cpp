/*
* Filnamn: BankKund.h
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller klassen BankKund som
* är en tyst klass som kommunicerar med klassen
* Konto och Bank.
*
*/
#ifndef BankKundH
#define BankKundH


#include "Konto.h"
#include "TransactionAccount.h"
#include "SavingsAccount.h"
#include "LongTermSavingAccount.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "BankKund.h"

using namespace std;


class BankKund {
private:
	string Name;
	string persNR;	
	vector<unique_ptr<Konto>>bankAccounts;
	

public:
	
	//Default konstruktor
	BankKund();
	
	// Överlagrad konstruktor
	BankKund(string name, string persNR);
	
	//Läs från fil
	bool ReadFromFile(string pnr);
	//Spara till fil
	void saveToFile();


	//Get funktioner
	
	string getBankKundName();
	string getPersNR();
	int getNrofAccounts();
	bool getAccountNumbers(vector<string> &konto) const;
	
	bool getAccInfo(string &accNR, vector<int> &vec) const;
	bool makeWithdrawal(string accNr, int ammount);
	bool makeDeposit(string accNr, int ammount);
	bool setCredit(string accNr, int credit);
	double getAccountsAssets();
	bool getSummery(vector<string> &accNr, vector<int> &summery, vector<string>& accType, vector<int>& transactions) const;
	bool delAcc(string accNr);

	//vector<string> getVectorOfAccounts() const { return bankAccounts; }

	//Set funktioner
	void setFirstname(string fName);
	void setPersNR(string pNR);
	bool createAccount(string type, double balance, double credit, int nrwithdrawals);



};
#endif

