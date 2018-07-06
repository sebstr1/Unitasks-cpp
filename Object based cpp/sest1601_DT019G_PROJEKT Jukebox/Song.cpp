//Song.cpp
#include "Song.h"
using namespace std;
//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//F�rvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Song::Song()
{
	songTitel = "ek";
	songArtist = "daksdk";
	songLengd = (Time(0, 0, 0));
}

//------------------------------------------------------------------------------
//Konstruktor f�r initiering av datamedlemmarna
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
// Set s�ngl�ngd
//------------------------------------------------------------------------------
void Song::setSongLengd(Time pLengd)
{
	songLengd = pLengd;
}




//------------------------------------------------------------------------------
//-------  Get Funktioner  -----------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// H�mta Titel...
//------------------------------------------------------------------------------
string Song::getSongTitel() const
{
	return songTitel;
}
//------------------------------------------------------------------------------
// H�mta Artist...
//------------------------------------------------------------------------------
string Song::getSongArtist() const
{
	return songArtist;
}
//------------------------------------------------------------------------------
// H�mta s�ngl�ngd
//------------------------------------------------------------------------------
Time Song::getSongLengd() const
{
	return songLengd;
}


// Anv�nds som avgr�nsare vid in och utl�sning fr�n fil
const char DELIM = '|';

// �verlagring av << operator f�r utskrift till fil
ostream &operator<<(ostream &os, const Song &song)
{
	os << song.getSongTitel() << DELIM << song.getSongArtist() << DELIM << song.getSongLengd();

	return os;
}

// �verlagring av >> operator f�r inl�sning av l�t
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
