/*
* Filnamn: SavingsAccount.h
* Labb 3 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller den tysta klassen SavingsAccount som är en ärvd klass från konto.
* Klassen hanterar bankkonton av den speciella typen SavingsAccount åt bankkunder.
*
*
*/
#ifndef SavingsAccountH
#define SavingsAccountH

#include "Konto.h"
#include <string>

using namespace std;

class SavingsAccount : public Konto {

private:
	double interestRate = 2.00;
	int Withdrawals = 0;
	int maxWithdrawals = 4;

public:
	virtual double getInterestRate() { return interestRate; }
	
	virtual bool withdrawal(double sum)
	{
		if (Withdrawals < maxWithdrawals && sum <= Konto::get_Available_Assets())
			// Om inte max antal uttag gjorts och summan är mindre än saldo
		{
			Withdrawals++; // Öka antal utag med ett
			return Konto::withdrawal(sum);
			// Gör uttag, true om det finns pengar annars false.
		}
		else
			return false; // Annars returnera false
	}
		
	virtual int getWithdrawalCount() { return Withdrawals; }
	virtual int getMaxWithdrawals() { return maxWithdrawals; }

	virtual string getAccountType() const { return "Savingsaccount"; }

	SavingsAccount(string pNR, size_t AccIdentifier, double pBalance, int nrWithdrawals) : Konto(pNR, AccIdentifier, pBalance) { Withdrawals = nrWithdrawals; }
	
	//Safe
	//SavingsAccount(string pNR, size_t AccIdentifier, double pBalance);
	
	//virtual void setCredit(double cred) {}
	//virtual double getCredit() const {}

};

#endif
