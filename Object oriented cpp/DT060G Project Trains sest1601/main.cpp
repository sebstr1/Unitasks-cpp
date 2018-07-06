/* 2017-05-10
* Filnamn: main.cpp
* Projekt Trains
* Namn: Sebastian Strindlund ses1601
*
*
* Main.cpp används för att skapa ett objekt av
* Simuleringsklassen för att köra igång simuleringen.
*/

#include "Simulation.h"
using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Kontrollera minnesläckor	

	Simulation app;
	app.run();

	
	return 0;
}