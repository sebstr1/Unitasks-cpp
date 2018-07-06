/*
* Filnamn: Konto.h
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller den tysta klassen Konto som
* hanterar bankkonton åt bankkunder.
*
*
*/
#ifndef KontoH
#define KontoH


#include <string>

using namespace std;


class Konto {
private:	
	string accountNumber;
	double Balance = 0.00;
	



public:
	virtual ~Konto() {};
	Konto();
	Konto(string pNR, size_t AccIdentifier, double pBalance);
	void setAccountNumber(string setString); //Sätter accountnr

	void Deposit(double valuetoAdd);		//Sätt in pengar på kontot
	
	
	//void Withdraw(double valuetoWithdraw);	//Ta ut pengar från kontot

	

	//Get funktioner
	string get_AccNR(); //Få Uppgift om kontonummer
	double get_Balance();  //Få Uppgift om aktuellt saldo
	double get_Available_Assets(); // Uppgift om tillgängligt belopp
	//double get_credit();		//Få Uppgift om aktuell beviljad kredt
	


	//Virtuella funktioner
	virtual int getWithdrawalCount() { return 0; }
	virtual int getMaxWithdrawals() { return 0; }
	virtual double getInterestRate() { return 0.00; }
	virtual string getAccountType() const = 0;
	virtual bool withdrawal(double sum);
	virtual bool setCredit(double cred) { return false; }
	virtual double getCredit() const { return 0; }


};
#endif
