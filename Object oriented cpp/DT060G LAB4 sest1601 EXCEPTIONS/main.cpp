/*
* Filnamn: main.cpp
* Labb 2 uppgift 1
* Namn: Sebastian Strindlund ses1601
*
*
* Main.cpp används för att skapa ett objekt av
* Testklassen för att köra igång testprogrammet.
*/

#include "TestApp.h"
using namespace std;
int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Kontrollera minnesläckor	

	TestApp app;
	app.run();

	cin.get();
	return 0;
}