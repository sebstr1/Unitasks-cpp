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
	double credit = 0.00;



public:
	Konto();
	Konto(string pSSN, size_t pBankAccountsSize, double pBalance = 0.00, double pGrantedCredit = 0.00);
	void setAccountNumber(string setString); //Sätter accountnr

	void Deposit(double valuetoAdd);		//Sätt in pengar på kontot
	void Withdraw(double valuetoWithdraw);	//Ta ut pengar från kontot

	void Change_Credit(double changeCredit); // Ändra beviljad kredit


	//Get funktioner
	string get_AccNR(); //Få Uppgift om kontonummer
	double get_Balance();  //Få Uppgift om aktuellt saldo
	double get_Available_Assets(); // Uppgift om tillgängligt belopp
	double get_credit();		//Få Uppgift om aktuell beviljad kredt
	
};
#endif
