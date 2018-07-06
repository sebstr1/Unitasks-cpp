/*
* Filnamn: MenuItem.h
* Labb 1 uppgift 1
* namn: Sebastian Strindlund ses1601
*/
#ifndef MenuItemH
#define MenuItemH
#include <string>

using namespace std;


class MenuItem
{
	private:
		string MenuText;
		bool alternativ_permitted;
	

	public:
		//Standard Konstruktor
		MenuItem();
		//Överlagrad Konstruktor
		MenuItem(string menutext, bool trueOrFalse);

		//Setfunktioner
		void setMenuText(string menutext);
		void setAlternative(bool trueOrFalse);
	
		//Getfunktioner
		string getMenuText() const;
		bool getAlternative_Permitted() const;


};

#endif
