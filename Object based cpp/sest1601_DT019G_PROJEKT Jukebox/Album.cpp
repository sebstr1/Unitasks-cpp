//klassFUNK.cpp
#include "Album.h"
using namespace std;

//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//F�rvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Album::Album()
{
	AlbumNamn = "";
	
}

//------------------------------------------------------------------------------
//Konstruktor f�r initiering av datamedlemmarna
//------------------------------------------------------------------------------
Album::Album(string pAlbumNamn)
{
	AlbumNamn = pAlbumNamn;
}


//------------------------------------------------------------------------------
// Set namn p� Album.
//------------------------------------------------------------------------------
void Album::setAlbumNamn(string pAlbumNamn)
{
	AlbumNamn = pAlbumNamn;
}

//------------------------------------------------------------------------------
// Get namn p� Album.
//------------------------------------------------------------------------------
string Album::getAlbumNamn() const
{
	return AlbumNamn;
}

//H�mtar den totala albumtiden
Time Album::AlbumLengd() const
{
	Time totalTime;

	for (auto e : Vector_of_Songs)
	{
		totalTime = totalTime + e.getSongLengd();
	}

	return totalTime;
}

//------------------------------------------------------------------------------
// �verlagring
//------------------------------------------------------------------------------

// �verlagring av < operatorn
bool Album::operator<(const Album & pAlbum) const
{
	return AlbumLengd() < pAlbum.AlbumLengd();
}	

// L�gger till en l�t till ett album
void Album::addSong(Song &song)
{
	// Pushar s�ngobjekt till Vector
	Vector_of_Songs.push_back(song);
}


// T�mmer s�ngvectorn
void Album::clearVector_of_Songs()
{
	Vector_of_Songs.clear();
}


// H�mtar antalet l�tar i albumvectorn
int Album::Number_of_Songs() const
{
	// Vectorns storlek (antalet l�tar)
	return Vector_of_Songs.size();
}


// Avgr�nsare..
const char DELIM = '|';

// �verlagringen av << till utskrift av album
ostream &operator<<(ostream &os, const Album &pAlbum)
{
	// Albumtitel
	os << pAlbum.getAlbumNamn() << endl;
	// Antal songs
	os << pAlbum.Number_of_Songs() << endl;
	// Alla songs i hela albumet..
	for (int i = 0, h = 1; i < pAlbum.Number_of_Songs(); i++, h++)
	{
		os << pAlbum.getVector_of_Songs()[i];
		// Newline varje rad utom sista l�ten i varje album
		if (h % pAlbum.Number_of_Songs() != 0)
			os << endl;
	}

	return os;
}

// �verlagringen av >> till inl�sning av album
istream &operator >> (istream &is, Album &album)
{
	// Skapar ett objekt av typen Song
	Song songObj;
	// F�r att lagra input
	string tmp;

	// Om vectorn med songs inte �r tom
	if (!album.getAlbumNamn().empty())
	{
		// T�m vectorn
		album.clearVector_of_Songs();
	}

	// L�ser in Albumnamn
	getline(is, tmp);
	// s�tter albumnamn
	album.setAlbumNamn(tmp);

	// Variabel f�r att lagra antalet songs
	int album_songs = 0;
	// L�ser in songs per album
	getline(is, tmp);
	// Str�ngstr�m med antal songs
	stringstream albumSongs_Stream(tmp);
	// Konverterar til int
	albumSongs_Stream >> album_songs;

	//L�ser in songs
	for (int i = 0; i < album_songs; ++i)
	{
		// L�gger till songs i albumets vector
		is >> songObj;
		// Tar bort newline
		is.ignore(10000, '\n');
		album.addSong(songObj);
	}

	return is;
}