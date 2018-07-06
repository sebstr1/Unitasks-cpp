/*
* Filnamn: MenuItem.cpp
* Labb 1 uppgift 1
* namn: Sebastian Strindlund ses1601
*/


#include "MenuItem.h"
#include <string>


//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
MenuItem::MenuItem()
{
	MenuText = "";
	alternativ_permitted;
}

//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
MenuItem::MenuItem(string menutext, bool trueOrFalse)
{
	MenuText = menutext;
	alternativ_permitted = trueOrFalse;
}
//------------------------------------------------------------------------------
// Set menytext..
//------------------------------------------------------------------------------
void MenuItem::setMenuText(string menutext)
{
	MenuText = menutext;
}
//------------------------------------------------------------------------------
// Set alternativ (tru or false)
//------------------------------------------------------------------------------
void MenuItem::setAlternative(bool trueOrFalse)
{
	alternativ_permitted = trueOrFalse;
}
//------------------------------------------------------------------------------
// Get menytexten.
//------------------------------------------------------------------------------
string MenuItem::getMenuText() const
{
	return MenuText;
}
//------------------------------------------------------------------------------
// Get alternativ (tru or false).
//------------------------------------------------------------------------------
bool MenuItem::getAlternative_Permitted() const
{
	return alternativ_permitted;
}
