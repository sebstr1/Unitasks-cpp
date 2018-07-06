/*
* Filnamn: Menu.cpp
* Labb 1 uppgift 1
* namn: Sebastian Strindlund ses1601
*/

#include <iostream>
#include <iomanip>
#include "TestApp.h"

using namespace std;
//------------------------------------------------------------------------------
int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Kontrollera minnesläckor	
	TestApp Application;
	Application.run();
	return 0;
}

