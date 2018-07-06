/*
* Filnamn: TransactionsAccount.h
* Labb 3 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller en tyst klass som är ärvd ifrån Konto.h
* Denna klass hanterar bankkonton av den speciella typen "Transaction" åt bankkunder.
*
*
*/
#ifndef TransactionAccountH
#define TransactionAccountH

#include "Konto.h"
#include <string>

using namespace std;

class TransactionsAccount : public Konto {

private:
	string Acctype = "Transactionsaccount";
	double credit = 0.00;

public:
	TransactionsAccount();
	TransactionsAccount(string pNR, size_t AccIdentifier, double pCredit, double pBalance);
	//TransactionsAccount(string pNR, size_t AccIdentifier, double pBalance);
	
	
	
	virtual bool withdrawal(double sum); //Virtuell funktion för uttag
	virtual bool setCredit(double cred) { credit = cred; return true; } //Virtuell funktion för setCredit
	virtual double getCredit() const { return credit; } //Virtuell funktion för GetCredit
	virtual string getAccountType() const { return Acctype; } //Virtuell funktion för getAcctype

};

#endif
