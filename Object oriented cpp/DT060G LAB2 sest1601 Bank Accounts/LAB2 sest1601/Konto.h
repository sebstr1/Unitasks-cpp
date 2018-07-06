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
	double credit = 0.00;



public:
	Konto();
	Konto(string pSSN, size_t pBankAccountsSize, double pBalance = 0.00, double pGrantedCredit = 0.00);
	void setAccountNumber(string setString); //S�tter accountnr

	void Deposit(double valuetoAdd);		//S�tt in pengar p� kontot
	void Withdraw(double valuetoWithdraw);	//Ta ut pengar fr�n kontot

	void Change_Credit(double changeCredit); // �ndra beviljad kredit


	//Get funktioner
	string get_AccNR(); //F� Uppgift om kontonummer
	double get_Balance();  //F� Uppgift om aktuellt saldo
	double get_Available_Assets(); // Uppgift om tillg�ngligt belopp
	double get_credit();		//F� Uppgift om aktuell beviljad kredt
	
};
#endif
