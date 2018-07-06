/*
* Filnamn: main.cpp
* Labb 5
* Namn: Sebastian Strindlund ses1601
*
*
* Main.cpp anv�nds f�r att skapa ett objekt av
* Testklassen f�r att k�ra ig�ng testprogrammet.
*/

#include "TestApp.h"
#include "Bowser.h"
using namespace std;

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Kontrollera minnesl�ckor	

	int val;
	cout << "Int (1) or double (2): ";
	cin >> val;								// Anv�ndaren v�ljer int eller double och objekt skapas d�refter.
	cin.get();

	if (val == 1)
	{
		TestApp<int> app;
		app.run();
	}
	else if (val == 2)
	{
		TestApp<double> app;
		app.run();
	}
	else
	{
		cout << "Error, select 1 or 2: " << endl;
	}
	return 0;
}