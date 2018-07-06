//Person.h
#include "Time.h"
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//F�rvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Time::Time()
{
	timmar = 0;
	minuter = 0;
	sekunder = 0;
}

//------------------------------------------------------------------------------
//Konstruktor f�r initiering av datamedlemmarna
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
// H�mta Timmar...
//------------------------------------------------------------------------------
int Time::getTimmar() const
{
	return timmar;
}
//------------------------------------------------------------------------------
// H�mta Minuter...
//------------------------------------------------------------------------------
int Time::getMinuter() const
{
	return minuter;
}
//------------------------------------------------------------------------------
// H�mta Sekunder...
//------------------------------------------------------------------------------
int Time::getSekunder() const
{
	return sekunder;
}




//�verlagringar

//�verlagring av + operatorn (addera tv� time objekt)
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

// �verlagring f�r att j�mf�ra om ett timeobjekt �r mindre �n ett annat
bool Time::operator<(const Time & tid) const
{
	return ((timmar * 3600) + (minuter * 60) + sekunder) < ((tid.timmar * 3600) + (tid.minuter * 60) + tid.sekunder);
}

// �verlagring f�r j�mf�ra om tv� time objekt �r lika  (Hittade ingen anv�ndning f�r denna men det st�r att den skall vara med enligt spec)
bool Time::operator==(const Time & tid) const
{
	return timmar == tid.timmar && minuter == tid.minuter && sekunder == tid.sekunder;
}

// �verlagringen av << f�r att skriva ut ett Timeobjekt
ostream &operator<<(ostream &os, const Time &t)
{
	os << t.getSekunder() + (t.getMinuter() * 60) + (t.getTimmar() * 3600);

	return os;
}

// �verlagringen av >> f�r att l�sa in ett Timeobjekt
istream &operator >> (istream &is, Time &t)
{
	int toSeconds;
	is >> toSeconds;

	t.setTimmar((toSeconds / 3600) % 60);
	t.setMinuter((toSeconds / 60) % 60);
	t.setSekunder(toSeconds % 60);

	return is;
}