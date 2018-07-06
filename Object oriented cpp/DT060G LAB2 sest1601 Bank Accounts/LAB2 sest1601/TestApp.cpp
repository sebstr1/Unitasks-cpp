
/*
* Filnamn: TestApp.cpp
* Labb 2 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil.
* Filen anv�nds som ett gr�nssnitt f�r att 
* kommunicera med anv�ndaren och anv�nda dom
* tysta klasserna Konto, Bank och Bankkund och dess funktioner.
*
*/

#include "TestApp.h"
using namespace std;

TestApp::TestApp(){}

void TestApp::run()
{
	//L�gger in menyalternativ i menu1
	menu1.push_back("*** Customer Options ***");
	menu1.push_back("1. Load customer from file.");
	menu1.push_back("2. Create a new customer.");
	menu1.push_back("3. Quit.");

	//L�gger in menyalternativen i menu2
	menu2.push_back("****** Menu *******");
	menu2.push_back("1. Get Customer name.");
	menu2.push_back("2. Get Customer persnr.");
	menu2.push_back("3. Get Customer Nr of Accounts.");
	menu2.push_back("4. Get the Account number(s).");
	menu2.push_back("5. Total Assets of customer.");
	menu2.push_back("6. Account Info.");
	menu2.push_back("7. Withdraw.");
	menu2.push_back("8. Deposit.");
	menu2.push_back("9. Set Credit.");
	menu2.push_back("10. Accounts summery.");
	menu2.push_back("11. Create new account.");
	menu2.push_back("12. Delete account.");
	menu2.push_back("13. Change Customer.");
	menu2.push_back("14. Quit.");
	
	//K�r endast den lilla menyn tills kund laddats/skapats
	if (fullMenu == false)
	{
		switchCase1();
	}
	//N�r kund laddats eller skapats
	if (fullMenu == true)
	{
		switchCase2();
	}
			
}


// Funktion som skriver ut aktuell meny fr�n vector
void TestApp::printMenu(vector<string> menuvec)
{
	cout << endl;
	for (size_t i = 0; i < menuvec.size(); i++)
	{
		cout << menuvec[i];
		if (!(i == menuvec.size() - 1))
		{
			cout << endl;
		}
	}
}

void TestApp::switchCase1()
{
	// Do while true.
	bool reRun = true;
	do
	{
		// Skriver ut huvudmenyn
		printMenu(menu1);
		if (fullMenu == true)
		{
			cout << " back to main menu.";
		}

		//L�ser in anv�nderens val fr�n funktionen userInput.
		switch (getMenuChoice(menu1))
		{ // K�r valt delprogram
		case 1:
			loadCustomer();
			break;
		case 2:
			addCustomer();
			fullMenu = true;
			break;
		case 3:
			reRun = false; //Avsluta
			cout << endl << endl << "Exiting...";
			break;
		default:
			cout << endl << "Wrong alternative, choose between 1-3..." << endl << endl;
			break;
		}

	} while (reRun == true);

}

void TestApp::switchCase2()
{
	// Do while true.
	bool reRun = true;
	do
	{
		//Rensar kommandotolken 		
		//cout << string(50, '\n');


		// Skriver ut huvudmenyn
		printMenu(menu2);
		
		//L�ser in anv�nderens val fr�n funktionen userInput.
		switch (getMenuChoice(menu2))
		{ // K�r valt delprogram
		case 1:
			getCustomerName();
			break;
		case 2:
			getCustomerPnR();
			break;
		case 3:
			getNrOffAccounts();
			break;
		case 4:
			getAccountNumbers();
			break;
		case 5:
			getTotAssets();
			break;
		case 6:
			getAccInfo();
			break;
		case 7:
			Withdraw();
			break;
		case 8:
			Deposit();
			break;
		case 9:
			Credit();
			break;
		case 10:
			AccountSummery();
			break;
		case 11:
			CreatAcc();
			break;
		case 12:
			delAcc();
			break;
		case 13:
			saveCustomer();
			switchCase1();
			break;
		case 14:
			saveCustomer();
			reRun = false; //Avsluta
			cout << "Now exiting the program......";
			break;
		default:
			cout << endl << "Wrong alternative, choose between 1-14..." << endl << endl;
			break;
		}
		
	} while (reRun == true);
}

//Funktion f�r att hantera anv�nderens input till menyval
int TestApp::getMenuChoice(vector<string> menuvec)
{
	int input = 1;
	cout << endl << "Alternative? : ";
	cin >> input;
	cin.get();
	

	//Kontrollerar s� att anv�ndaren angav sitt val i form av INT & s� att alternativet �r
	//Inom till�ten range dvs 1 till vectorns storlek
	while (cin.fail() || input <= 0 || input > menuvec.size() - 1)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Wrong alternative. You can only choose 1 - " << menuvec.size() - 1 << endl << endl;
		cout << "Alternative? : ";
		cin >> input;
	}

	
	//Returnerar anv�nderens input till Switchen
	return input;
	

}
void TestApp::getCustomerName()
{
	cout << "Gettin customer name..." << endl;
	cout << kund1.getName();

}

void TestApp::getCustomerPnR()
{
	cout << "Gettin customer ssn..." << endl;
	cout << kund1.getPersnr();

}

void TestApp::addCustomer()
{	
	string name;
	string pNR;
	cout << endl << endl << "Creating a new Customer." << endl;
	//L�ser in f�rnamn
	cout << "Name: ";
	getline(cin, name);	
	//L�ser in personnr
	cout << endl << "Social Security nr: ";
	getline(cin, pNR);

	//S�tter F�rnamn, Efternamn och persnR
	if (kund1.createCustomer(name, pNR))
	{
		cout << "Customer "<< name << " " << pNR << " created..!" << endl << endl;
	}
	else
	{
		cout << "Failedddddddddd";
	}

}

//H�mtar antalet konton kunden har
void TestApp::getNrOffAccounts()
{
	cout << "Antal konton: " << kund1.getNrAccounts();
}


//-----MainMenu 4. Skriv ut kundens alla kontonr
void TestApp::getAccountNumbers()
{
	if (kund1.getNrAccounts() > 0)
	{
		vector<string> accounts;
		
		if (kund1.getAccountNumbers(accounts))
		{
			cout << endl << "Your account(s): " << endl;

			for (auto index : accounts)
			{
				cout << index << endl;
			}
		}
		else
		{
			cout << endl << endl << "You dont have any accounts....." << endl << endl;
		}		
	}
	else 
	{
		cout << endl << endl << "You dont have any accounts....." << endl << endl;
	}
	
}

//-----Menyval 5 Skriver ut kundens totala tillg�ngar
void TestApp::getTotAssets()
{

	cout << "Customer total assets: " << kund1.getAssets();
}

//----Menyval 6 h�mta information f�r specifikt konto
void TestApp::getAccInfo()
{
	cout << "This is your account(s):" << endl;
	getAccountNumbers();
	cout << endl << endl << "What account do you want info from?: ";
	string acc;
	getline(cin, acc);
	vector<int> info;
	if (kund1.getAccountInfo(acc, info))
	{
		cout << "Balance: " << info[0] << endl;
		cout << "Credit: " << info[1] << endl;
		cout << "Assets: " << info[2] << endl;
	}
	else
	{
		cout << "Account '" << acc << " does not exist" << endl << endl;
	}

}

//---Menyval 7 Ta ut pengar fr�n konto
void TestApp::Withdraw()
{
	cout << "This is your account(s):" << endl;
	getAccountNumbers();
	cout << endl << endl << "From wich account do you want to withdraw?: ";
	string acc;
	getline(cin, acc);
	vector<int> info;
	cout << endl << endl << "Account " << acc << ":" << endl;
	if (kund1.getAccountInfo(acc, info))
	{
		cout << "Balance: " << info[0] << endl;
		cout << "Credit: " << info[1] << endl;
		cout << "Assets: " << info[2] << endl;
	}
	double assets;
	assets = info[2];
	cout << endl << endl << "How much would you like to withdraw?: ";
	int ammount;
	cin >> ammount;
	cin.get();

	if (ammount > assets)
	{
		cout << "You only have '" << assets << "' available, so you cannot withdrawl '" << ammount << "'" << endl << endl;
		return;
	}

	
	if (kund1.withdraw(acc, ammount))
	{
		cout << "Withdrawl '" << ammount << "' from account '" << acc << "'" << endl << endl;
	}
	else
	{
		cout << "Account '" << acc << " does not exist" << endl << endl;
	}
}

//----Menyval 8 S�tt in pengar p� konto
void TestApp::Deposit()
{
	cout << "This is your account(s):" << endl;
	getAccountNumbers();
	cout << endl << endl << "To wich account do you want to deposit?: ";
	string acc;
	getline(cin, acc);
	cout << endl << endl << "How much would you like to deposit?: ";
	int ammount;
	cin >> ammount;
	cin.get();

	
	if (kund1.deposit(acc, ammount))
	{
		cout << "Deposited '" << ammount << "' to account '" << ammount << "'" << endl << endl;
	}
	else
	{
		cout << "Account '" << acc << " does not exist" << endl << endl;
	}

}

//---Menyval 9 �ndra krediten p� kontot
void TestApp::Credit()
{
	cout << "This is your account(s):" << endl;
	getAccountNumbers();
	cout << endl << endl << "For what account do you want to edit the credit?: ";
	string acc;
	getline(cin, acc);
	cout << endl << endl << "Change credit to?: ";
	int credd;
	cin >> credd;
	cin.get();

	if (kund1.credit(acc, credd))
	{
		cout << "Credit changed on account '" << acc << "' to '" << credd << "'" << endl << endl;
	}
	else
	{
		cout << "Account '" << acc << " does not exist" << endl << endl;
	}
}

//---Menyval 10 Skriver ut info om alla kundens konton
void TestApp::AccountSummery()
{
	double totBalance = 0.00; //variabel f�r att summera balansen av konton
	double totCredit = 0.00; //Variabel f�r att summera krediten p� konton
	vector<string> accNrs;	//Vector f�r att lagra kontoNr
	vector<int> summery;	//Vector f�r att lagra tillg�ngar
	if (kund1.getSummery(accNrs, summery)) // Skickar in vectorerna mot bank.cpp f�r att h�mta kontonummer och saldo/kredit f�r upp till 3 konton.
	{
		cout << endl << endl << accNrs[0] << endl << endl;

		for (size_t i = 0; i < summery.size(); i++)
		{
			cout << "Balance: " << summery[i] << endl;
			cout << "Credit: " << summery[i + 1] << endl;
			cout << "Assets: " << summery[i + 2] << endl;
			totBalance = totBalance + summery[i];		//Summerar kontosaldot
			totCredit = totCredit + summery[i + 1];		//Summerar kontokredit

			i = i + 2; // �ndrar iteratorn f�r utskrift av n�sta konto
			
			//N�r all info f�r ett konto skriv ut n�sta kontonr
			if (i == 2 && accNrs.size() > 1)
			{
				cout << endl << endl << accNrs[1] << endl << endl;
			}
			if (i == 5 && accNrs.size() > 2)
			{
				cout << endl << endl << accNrs[2] << endl << endl;
			}


		}
		//Skriver ut totalen
		cout << endl << endl << ":::: Total ::::" << endl << endl;
		cout << "Balance: " << totBalance << endl;
		cout << "Credit: " << totCredit << endl;
		getTotAssets();
		cout << endl << endl;
	}
	else
	{
		cout << endl << endl << "No accounts existed........." << endl << endl;
	}

}


//--Menyval 11 Skapar nytt konto
void TestApp::CreatAcc()
{
	if (kund1.getNrAccounts() == 3)
	{
		cout << endl << "You already have max amount of accounts...";
		cin.get();
		return;
	}
	

	//Initierar
	double credit, balance;
	//S�tter alltid balance till 0 p� ett nytt konto
	balance = 0.00;
	//L�ser in krediten
	cout << "Enter Credit for account: ";
	cin >> credit;
	cin.get();	

	//Om konto skapats
	if (kund1.createNewAccount(credit, balance)) //Skickar vald kredit och balance till Bank.cpp
	{
		cout << "True";
		fullMenu = true; //Eftersom kund skapats f�r man tillg�ng till fulla menyn.
		
	}
	//B�r aldrig kunna hamna h�r
	else
	{
		cout << "Error code: Haxxxxx1337doubleTrouble";
		
	}
}

////---Menyval 12 ta bort konto
void TestApp::delAcc()
{
	cout << "This is your account(s):" << endl;
	getAccountNumbers();
	cout << endl << endl << "What account would you like to delete?: ";
	string acc;
	getline(cin, acc);
	if (kund1.deleteAccount(acc))
	{
		cout << endl << endl << "Account '" << acc << "' has been deleted." << endl << endl;
	}
	else
	{
		cout << endl << endl << "Account '" << acc << "' does not exist." << endl << endl;
	}
}

// --- Laddar kund fr�n fil
void TestApp::loadCustomer()
{
	string loadThisClient;

	cout << endl << endl << "What is the social Security number of the Client you want to load?: ";
	getline(cin, loadThisClient);

	//Kontrollerar s� att inte kunden redan finns
	ifstream inFile(loadThisClient + ".knt");
	if (!(inFile.is_open()))
	{
		cout << endl << endl << "**** ERROR Customer with psn '" << loadThisClient << "' does not exist!*******" << endl << endl;
		return;
	}

	if (kund1.ReadFile(loadThisClient))
	{
		cout << endl << endl << ":::: Customer with psn '" << loadThisClient << "' loaded. ::::" << endl << endl;
		fullMenu = true; //Eftersom kund laddats f�r man tillg�ng till fulla menyn.
		
	}
	else
	{
		cout << endl << endl << "****** Client with ssn '" << loadThisClient << "' does not exist... ******" << endl << endl;
	}
}

//Sparar kunden
void TestApp::saveCustomer()
{
	kund1.saveFile();
	cout << endl << endl << ":::: Customer saved ::::" << endl << endl;
}