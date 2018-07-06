// Menu.cpp
#include "Menu.h"



//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//F�rvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Menu::Menu()
{
	Menu_Header = "";
}
//------------------------------------------------------------------------------
//Konstruktor f�r initiering av datamedlemmarna
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

//L�gg till menyalternativ i menyvectorn
void Menu::addItem(string menutext, bool alt)
{
	//Skapar MenyItem objekt
	MenuItem item;

	//L�gger till texten f�r menyalternativet
	item.setMenuText(menutext);
	//Best�mmer om menyalternativet �r valbart eller inte (dvs true or false)
	item.setAlternative(alt);

	//Pushar menyalternativet till menyvectorn
	menu_vector.push_back(item);
}

//skriver ut menyn
void Menu::printMenuItems()
{
	int menuNumber = 1;
	//G�r igenom vectorn med menyalternativ
	cout << Menu_Header << endl;
	for (auto index : menu_vector)
	{
		//Kontrollerar om menyvalen ska vara m�jliga att v�lja eller inte.
		if (index.getAlternative_Permitted() == true)
		{
			if (menuNumber != 0)
			{
				cout << menuNumber << ". ";
			}
			cout << index.getMenuText() << endl;
			menuNumber++;
		}
		//Om menyvalet inte skulle vara valbart l�gg till (disabled at the moment)
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

//Funktion f�r att hantera anv�nderens input till menyval
int Menu::getMenuChoice(Menu &obj)
{
	int input = 1;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;
	cin.get();	

//Kontrollerar s� att anv�ndaren angav sitt val i form av INT & s� att alternativet �r
//Inom till�ten range dvs 1 till vectorns storlek
	while (cin.fail() || input <= 0 || input > obj.getMenu_Vector().size())
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast v�lja alternativ 1 - " << obj.getMenu_Vector().size() << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
		cin.get();
		
	}

	int matchWithInput = 1;
	bool permitted_alt = false;
	//G�r igenom menyvectorn f�r att hitta r�tt alternativ och s�tter v�r bool till statusen f�r detta val dvs true eller false
	for (auto item : obj.getMenu_Vector())
	{
		if (input == matchWithInput)
		{
			permitted_alt = item.getAlternative_Permitted();
			
		}
		
		matchWithInput++;
	}

	// Om menyvalet inte var valbart (true) meddela detta och l�t anv�nderen f�rs�ka igen..
	if (permitted_alt == false)
	{
		cout << "Alternativet inte tillg�ngligt just nu";
		getMenuChoice(obj);
	
	}
	else
	{
		//Returnerar anv�nderens input till Switchen
		return input;
	}

}

