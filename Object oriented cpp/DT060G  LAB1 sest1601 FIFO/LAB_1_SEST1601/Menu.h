
/*
* Filnamn: Menu.h
* Labb 1 uppgift 1
* namn: Sebastian Strindlund ses1601
*/
#ifndef MenuH
#define MenuH
#include <string>
#include "MenuItem.h"
#include <vector>
using namespace std;



class Menu
{
	private:
		vector <MenuItem> menu_vector;
		string Menu_Header;


	public:
		//Standard Konstruktor
		Menu();
		//Överlagrad Konstruktor
		Menu(string header);

		//Setfunktioner
		void setMenu_Header(string header);
		
		//Getfunktioner
		string getMenu_Header() const;
		vector <MenuItem> &getMenu_Vector();

		//Funktioner
		//Lägger till menyalternativ i vectorn
		void addItem(string menutext, bool alt);
		
		//Skriver ut menyalternativ
		void printMenuItems();

		//Hanterar använderens input för menyalternativ
		int getMenuChoice(Menu &obj);
};

#endif


