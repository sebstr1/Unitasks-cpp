// LAB 2 v 1.0
// Klasser & OBJ
// Sebastian Strindlund 2017-01-25aa
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "name.h"
#include "address.h"
#include <vector>
#include "Person.h"
#include <ctime>
#include "UserInterface.h"

using namespace std;
//------------------------------------------------------------------------------
int main()
{
	// G�r s� att man kan skriva ���.
	setlocale(LC_ALL(), "SWEDISH");

	UserInterface ui;
	ui.run();

	
	return 0;
}

