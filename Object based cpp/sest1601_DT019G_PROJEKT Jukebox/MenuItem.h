// MenuItem.h
#ifndef MenuItemH
#define MenuItemH
#include <string>
#include "Time.h"
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
