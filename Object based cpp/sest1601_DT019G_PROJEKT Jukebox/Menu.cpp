// Menu.cpp
#include "Menu.h"



//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Menu::Menu()
{
	Menu_Header = "";
}
//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
Menu::Menu(string header)
{
	Menu_Header = header;

}


//------------------------------------------------------------------------------
// Set menu header
//------------------------------------------------------------------------------
void Menu::setMenu_Header(string header)
{
	Menu_Header = header;

}

//------------------------------------------------------------------------------
// Get menytexten.
//------------------------------------------------------------------------------
string Menu::getMenu_Header() const
{
	return Menu_Header;
}
//------------------------------------------------------------------------------
// returnera menyn
//------------------------------------------------------------------------------
vector<MenuItem>& Menu::getMenu_Vector()
{
	return menu_vector;
}

//Lägg till menyalternativ i menyvectorn
void Menu::addItem(string menutext, bool alt)
{
	//Skapar MenyItem objekt
	MenuItem item;

	//Lägger till texten för menyalternativet
	item.setMenuText(menutext);
	//Bestämmer om menyalternativet är valbart eller inte (dvs true or false)
	item.setAlternative(alt);

	//Pushar menyalternativet till menyvectorn
	menu_vector.push_back(item);
}

//skriver ut menyn
void Menu::printMenuItems()
{
	int menuNumber = 1;
	//Går igenom vectorn med menyalternativ
	cout << Menu_Header << endl;
	for (auto index : menu_vector)
	{
		//Kontrollerar om menyvalen ska vara möjliga att välja eller inte.
		if (index.getAlternative_Permitted() == true)
		{
			if (menuNumber != 0)
			{
				cout << menuNumber << ". ";
			}
			cout << index.getMenuText() << endl;
			menuNumber++;
		}
		//Om menyvalet inte skulle vara valbart lägg till (disabled at the moment)
		else
		{
			if (menuNumber != 0)
			{
				cout << menuNumber << ". ";
			}
			cout << index.getMenuText() << " (disabled at the moment)" << endl;
			menuNumber++;
		}
	}
}

//Funktion för att hantera använderens input till menyval
int Menu::getMenuChoice(Menu &obj)
{
	int input = 1;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;
	cin.get();	

//Kontrollerar så att användaren angav sitt val i form av INT & så att alternativet är
//Inom tillåten range dvs 1 till vectorns storlek
	while (cin.fail() || input <= 0 || input > obj.getMenu_Vector().size())
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast välja alternativ 1 - " << obj.getMenu_Vector().size() << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
		cin.get();
		
	}

	int matchWithInput = 1;
	bool permitted_alt = false;
	//Går igenom menyvectorn för att hitta rätt alternativ och sätter vår bool till statusen för detta val dvs true eller false
	for (auto item : obj.getMenu_Vector())
	{
		if (input == matchWithInput)
		{
			permitted_alt = item.getAlternative_Permitted();
			
		}
		
		matchWithInput++;
	}

	// Om menyvalet inte var valbart (true) meddela detta och låt använderen försöka igen..
	if (permitted_alt == false)
	{
		cout << "Alternativet inte tillgängligt just nu";
		getMenuChoice(obj);
	
	}
	else
	{
		//Returnerar använderens input till Switchen
		return input;
	}

}

