// SEST1601_DT018G_PROJEKT_CONSTANTS.h
// Includes, Konstanter och Struct
// Sebastian Strindlund 2016-12-12
// V1.0
//----------------------------------------------------------------------------------------
#ifndef SEST1601_DT018G_PROJEKT_CONSTANTSH
#define SEST1601_DT018G_PROJEKT_CONSTANTSH


using namespace std;    //Tar bort std::
#include <clocale>      //f�r stod
#include <fstream> // filhantering
#include <iterator>  // ostream_iterator iterator
#include <vector>
#include <random>    // random generator,distribution 
#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <ctime>     // time()
#include <iostream> // cout, cin
#include <iomanip> // fixed, setprecision()
#include <time.h> // inkluderar tid och datum mm (s� att ��� ska funka)
//---------------------------------------------------------------------------//
//-------------------enum f�r sorteringsalternativ-----------------------------
enum sorterings_Alternativ
{
	namn_sort = 1,
	signatur_sort = 2,
	lengd_sort = 3
};


//-----------------Struct-------------------------------------------------

struct Personer
{
	string namn;
	string efternamn;
	string signatur;
	double lengd;
};


//---------------Konstanter--------------------------------------------------//
const string DELIM = "|";
const size_t meny_size = 10;


const vector<string> vector_meny = 
{ "*********************************** \n",
"1. L�gg till en person",
"2. Skriv ut listan med namn p� sk�rmen",
"3. S�k efter en person i listan",
"4. Ta bort en person fr�n listan",
"5. Sortera listan p� olika s�tt",
"6. Slumpa ordningen av listan",
"7. Spara listan till fil",
"8. L�s in register fr�n fil",
"9. Avsluta"};

#endif