//Usefulfunctions.cpp
//Funktioner för jukebox...

#include "usefulFunctions.h"




string toLowerFunction(string convertThis)
{
	string tmp = convertThis;
	for (auto i = 0; tmp[i]; i++)
	{
		tmp[i] = tolower(tmp[i]);
	}

	return tmp;
}
