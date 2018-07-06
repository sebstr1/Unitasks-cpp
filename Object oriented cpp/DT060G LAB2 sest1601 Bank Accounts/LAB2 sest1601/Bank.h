/*
* Filnamn: Bank.h
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen den tysta klassen Bank som kommunicerar 
* mellan klassen TestApp och BankKund.
*
*/

#ifndef BankH
#define BankH

#include <string>
#include "BankKund.h"
#include <vector>
#include <memory>
using namespace std;

class Bank {
private:
	unique_ptr<BankKund> kund;
	
public:
	Bank();
	//KADWKDDDDDDDDDDDDDDDDDDDDDDDDDDDD DELETE?
	Bank(string name, string pNr);
	
	//Get funktioner
	string getName() const;
	string getPersnr() const;
	int getNrAccounts() const;
	bool getAccountNumbers(vector<string> &vec) const;
	double getAssets() const;
	bool getAccountInfo(string &accNR, vector<int> &vec) const;
	bool withdraw(string accNr, int ammount);
	bool deposit(string accNr, int ammount);
	bool credit(string accNr, int credit);
	bool getSummery(vector<string> &accNr, vector<int> &summery) const;
	bool deleteAccount(string accNr);
	bool ReadFile(string pnr);
	void saveFile();

	//Set funktioner
	bool createCustomer(string Name, string pNr);
	bool createNewAccount(double credit = 0.00, double balance = 0.00);

};
#endif
