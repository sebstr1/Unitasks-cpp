/*
* Filnamn: TransactionsAccount.h
* Labb 3 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen inneh�ller en tyst klass som �r �rvd ifr�n Konto.h
* Denna klass hanterar bankkonton av den speciella typen "Transaction" �t bankkunder.
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
	
	
	
	virtual bool withdrawal(double sum); //Virtuell funktion f�r uttag
	virtual bool setCredit(double cred) { credit = cred; return true; } //Virtuell funktion f�r setCredit
	virtual double getCredit() const { return credit; } //Virtuell funktion f�r GetCredit
	virtual string getAccountType() const { return Acctype; } //Virtuell funktion f�r getAcctype

};

#endif
