//Song.cpp
#include "Song.h"
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Song::Song()
{
	songTitel = "ek";
	songArtist = "daksdk";
	songLengd = (Time(0, 0, 0));
}

//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
Song::Song(string psongTitel, string psongArtist, Time psongLengd)
{
	songTitel = psongTitel;
	songArtist = psongArtist;
	songLengd = psongLengd;
}



//------------------------------------------------------------------------------
//-------  Set Funktioner  -----------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Set titel
//------------------------------------------------------------------------------
void Song::setSongTitel(string pTitel)
{
	songTitel = pTitel;
}
//------------------------------------------------------------------------------
// Set Artist
//------------------------------------------------------------------------------
void Song::setSongArtist(string pArtist)
{
	songArtist = pArtist;
}
//------------------------------------------------------------------------------
// Set sånglängd
//------------------------------------------------------------------------------
void Song::setSongLengd(Time pLengd)
{
	songLengd = pLengd;
}




//------------------------------------------------------------------------------
//-------  Get Funktioner  -----------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Hämta Titel...
//------------------------------------------------------------------------------
string Song::getSongTitel() const
{
	return songTitel;
}
//------------------------------------------------------------------------------
// Hämta Artist...
//------------------------------------------------------------------------------
string Song::getSongArtist() const
{
	return songArtist;
}
//------------------------------------------------------------------------------
// Hämta sånglängd
//------------------------------------------------------------------------------
Time Song::getSongLengd() const
{
	return songLengd;
}


// Används som avgränsare vid in och utläsning från fil
const char DELIM = '|';

// Överlagring av << operator för utskrift till fil
ostream &operator<<(ostream &os, const Song &song)
{
	os << song.getSongTitel() << DELIM << song.getSongArtist() << DELIM << song.getSongLengd();

	return os;
}

// Överlagring av >> operator för inläsning av låt
istream &operator >> (istream &is, Song &song)
{
	Time obj;
	string tmp;

	getline(is, tmp, DELIM);
	song.setSongTitel(tmp);

	getline(is, tmp, DELIM);
	song.setSongArtist(tmp);

	is >> obj;
	song.setSongLengd(obj);

	return is;
}
