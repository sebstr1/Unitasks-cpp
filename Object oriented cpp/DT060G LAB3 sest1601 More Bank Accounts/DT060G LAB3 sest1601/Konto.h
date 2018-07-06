/*
* Filnamn: Konto.h
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen inneh�ller den tysta klassen Konto som
* hanterar bankkonton �t bankkunder.
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
	void setAccountNumber(string setString); //S�tter accountnr

	void Deposit(double valuetoAdd);		//S�tt in pengar p� kontot
	
	
	//void Withdraw(double valuetoWithdraw);	//Ta ut pengar fr�n kontot

	

	//Get funktioner
	string get_AccNR(); //F� Uppgift om kontonummer
	double get_Balance();  //F� Uppgift om aktuellt saldo
	double get_Available_Assets(); // Uppgift om tillg�ngligt belopp
	//double get_credit();		//F� Uppgift om aktuell beviljad kredt
	


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
