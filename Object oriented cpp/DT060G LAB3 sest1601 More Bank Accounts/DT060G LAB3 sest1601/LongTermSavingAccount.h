/*
* Filnamn: LongTermSavingsAccount.h
* Labb 3 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller den tysta klassen LongTermSavingsAccount som är ärvd från Konto.h
* Klassen hanterar bankkonton av den speciella typen LongTermSavingsAccount åt bankkunder.
*
*
*/
#ifndef LongTermSavingAccountH
#define LongTermSavingAccountH
#include "SavingsAccount.h"
#include "Konto.h"
#include <string>

using namespace std;

class LongTermSavingsAccount : public SavingsAccount {

private:
	int Withdrawalss = 0;
	int maxWithdrawals = 1;
	
public:
	
	virtual string getAccountType() const { return "Long Term Savingsaccount"; }
	//virtual double getInterest() { return 3; }
	//LongTermSavingsAccount(string pNR, size_t AccIdentifier, double pBalance);
	LongTermSavingsAccount(string pNR, size_t AccIdentifier, double pBalance, int nrWithdrawals) : SavingsAccount(pNR, AccIdentifier, pBalance, nrWithdrawals) { Withdrawalss = nrWithdrawals; }
	
	virtual bool withdrawal(double sum)
	{
		if (Withdrawalss < maxWithdrawals && sum <= Konto::get_Available_Assets())
			// Om inte max antal uttag gjorts och summan är mindre än saldo
		{
			Withdrawalss++; // Öka antal utag med ett
			return Konto::withdrawal(sum);
			// Gör uttag, true om det finns pengar annars false.
		}
		else
			return false; // Annars returnera false
	}

	virtual int getMaxWithdrawals() { return maxWithdrawals; }
	virtual int getWithdrawalCount() { return Withdrawalss; }
	virtual double getInterestRate() { return SavingsAccount::getInterestRate()+2; }

};
#endif
