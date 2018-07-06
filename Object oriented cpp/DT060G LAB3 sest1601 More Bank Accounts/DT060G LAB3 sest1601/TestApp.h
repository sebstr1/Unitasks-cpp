/*
* Filnamn: TestApp.h
* Labb 3 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Filen innehåller klassen TestApp som 
* fungerar som ett gränsnitt för använderen
* mot dem tysta klasserna Bank, Bankkund och Konto.
*
*/
#ifndef TestAppH
#define TestAppH


#include <string>
#include <vector>
#include "Bank.h"
#include "BankKund.h"


using namespace std;


class TestApp {
private:
	Bank kund1;
	
	vector<string> menu1; // MenuVector 1
	vector<string> menu2; // MenuVector 2
	void printMenu(vector<string> menuvec); //Function that prints out the alternatives from active MenuVector
	bool fullMenu = false; // To make the fullMenu show up after customer is active

	int getMenuChoice(vector<string> menuvec); // Get the users menuchoice
	void switchCase1();	       // Visar menyn med en switch för följande alternativ:
	void loadCustomer();	   // Val 1: Ladda kund från fil
	void addCustomer();		   // Val 2: Lägg till kund
	//------------------>      // Val 3: Avsluta
	
	void switchCase2();		   // Visar menyn med en switch för följande alternativ:
	void getCustomerName();    // Val 1: Hämta kundnamn 
	void getCustomerPnR();     // Val 2: Hämta personnr
	void getNrOffAccounts();   // Val 3: Hämta Antalet konton
	void getAccountNumbers();  // Val 4: Hämta kundens kontonr
	void getTotAssets();	   // Val 5: Hämtar kundens totala tillgångar
	void getAccInfo();		   // Val 6: Hämtar information från specifikt konto
	void Withdraw();		   // Val 7: Tar ut pengar från kontot
	void Deposit();			   // Val 8: Sätter in pengar på kontot
	void Credit();			   // Val 9: Sätter kredit på kontot
	void AccountSummery();     // Val 10: Summering från konton
	void CreatAcc();           // Val 11: Lägg till konto
	void delAcc();		       // Val 12: Ta bort konto
	//------------------>      // Val 13: Byt kund (gå till andra menyn)
	//------------------>      // Val 14: Avsluta programmet (och spara kund)
		
	
	void saveCustomer(); //Spara kund till fil
		
public:
	TestApp();
	void run();

};
#endif

