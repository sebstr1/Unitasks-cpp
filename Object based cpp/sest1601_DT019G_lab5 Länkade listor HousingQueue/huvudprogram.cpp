// LAB 5 v 1.1
// Länkade Listor
// Sebastian Strindlund 2017-02-14
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include "name.h"
#include "address.h"
#include <vector>
#include "Person.h"
#include <ctime>
#include "HousingQ.h"

using namespace std;
//------------------------------------------------------------------------------
int main()
{
	// Gör så att man kan skriva åäö.
	setlocale(LC_ALL(), "SWEDISH");

	HousingQ ui;
	ui.run();

	
	return 0;
}

