//Person.h
#include "Time.h"
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Time::Time()
{
	timmar = 0;
	minuter = 0;
	sekunder = 0;
}

//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
Time::Time(int pTimmar, int pMinuter, int pSekunder)
{
	timmar = pTimmar;
	minuter = pMinuter;
	sekunder = pSekunder;
}



//------------------------------------------------------------------------------
//-------  Set Funktioner  -----------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Timmar
//------------------------------------------------------------------------------
void Time::setTimmar(int pTimmar)
{
	timmar = pTimmar;
}
//------------------------------------------------------------------------------
// Minuter
//------------------------------------------------------------------------------
void Time::setMinuter(int pMinuter)
{
	minuter = pMinuter;
}
//------------------------------------------------------------------------------
// Sekunder
//------------------------------------------------------------------------------
void Time::setSekunder(int pSekunder)
{
	sekunder = pSekunder;
}




//------------------------------------------------------------------------------
//-------  Get Funktioner  -----------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Hämta Timmar...
//------------------------------------------------------------------------------
int Time::getTimmar() const
{
	return timmar;
}
//------------------------------------------------------------------------------
// Hämta Minuter...
//------------------------------------------------------------------------------
int Time::getMinuter() const
{
	return minuter;
}
//------------------------------------------------------------------------------
// Hämta Sekunder...
//------------------------------------------------------------------------------
int Time::getSekunder() const
{
	return sekunder;
}




//Överlagringar

//Överlagring av + operatorn (addera två time objekt)
Time Time::operator+(const Time & tid)
{
	Time tempobj;
	int total = 0;
	total = total + timmar * 3600;
	total = total + minuter * 60;
	total = total + sekunder;

	total = total + tid.getTimmar() * 3600;
	total = total + tid.getMinuter() * 60;
	total = total + tid.getSekunder();

	tempobj.setSekunder(total % 60);
	total /= 60;
	tempobj.setMinuter(total % 60);
	total /= 60;
	tempobj.setTimmar(total);

	return tempobj;
}

// Överlagring för att jämföra om ett timeobjekt är mindre än ett annat
bool Time::operator<(const Time & tid) const
{
	return ((timmar * 3600) + (minuter * 60) + sekunder) < ((tid.timmar * 3600) + (tid.minuter * 60) + tid.sekunder);
}

// Överlagring för jämföra om två time objekt är lika  (Hittade ingen användning för denna men det står att den skall vara med enligt spec)
bool Time::operator==(const Time & tid) const
{
	return timmar == tid.timmar && minuter == tid.minuter && sekunder == tid.sekunder;
}

// Överlagringen av << för att skriva ut ett Timeobjekt
ostream &operator<<(ostream &os, const Time &t)
{
	os << t.getSekunder() + (t.getMinuter() * 60) + (t.getTimmar() * 3600);

	return os;
}

// Överlagringen av >> för att läsa in ett Timeobjekt
istream &operator >> (istream &is, Time &t)
{
	int toSeconds;
	is >> toSeconds;

	t.setTimmar((toSeconds / 3600) % 60);
	t.setMinuter((toSeconds / 60) % 60);
	t.setSekunder(toSeconds % 60);

	return is;
}