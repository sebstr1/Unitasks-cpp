//klassFUNK.cpp
#include "Album.h"
using namespace std;

//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Album::Album()
{
	AlbumNamn = "";
	
}

//------------------------------------------------------------------------------
//Konstruktor för initiering av datamedlemmarna
//------------------------------------------------------------------------------
Album::Album(string pAlbumNamn)
{
	AlbumNamn = pAlbumNamn;
}


//------------------------------------------------------------------------------
// Set namn på Album.
//------------------------------------------------------------------------------
void Album::setAlbumNamn(string pAlbumNamn)
{
	AlbumNamn = pAlbumNamn;
}

//------------------------------------------------------------------------------
// Get namn på Album.
//------------------------------------------------------------------------------
string Album::getAlbumNamn() const
{
	return AlbumNamn;
}

//Hämtar den totala albumtiden
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
// Överlagring
//------------------------------------------------------------------------------

// Överlagring av < operatorn
bool Album::operator<(const Album & pAlbum) const
{
	return AlbumLengd() < pAlbum.AlbumLengd();
}	

// Lägger till en låt till ett album
void Album::addSong(Song &song)
{
	// Pushar sångobjekt till Vector
	Vector_of_Songs.push_back(song);
}


// Tömmer sångvectorn
void Album::clearVector_of_Songs()
{
	Vector_of_Songs.clear();
}


// Hämtar antalet låtar i albumvectorn
int Album::Number_of_Songs() const
{
	// Vectorns storlek (antalet låtar)
	return Vector_of_Songs.size();
}


// Avgränsare..
const char DELIM = '|';

// Överlagringen av << till utskrift av album
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
		// Newline varje rad utom sista låten i varje album
		if (h % pAlbum.Number_of_Songs() != 0)
			os << endl;
	}

	return os;
}

// Överlagringen av >> till inläsning av album
istream &operator >> (istream &is, Album &album)
{
	// Skapar ett objekt av typen Song
	Song songObj;
	// För att lagra input
	string tmp;

	// Om vectorn med songs inte är tom
	if (!album.getAlbumNamn().empty())
	{
		// Töm vectorn
		album.clearVector_of_Songs();
	}

	// Läser in Albumnamn
	getline(is, tmp);
	// sätter albumnamn
	album.setAlbumNamn(tmp);

	// Variabel för att lagra antalet songs
	int album_songs = 0;
	// Läser in songs per album
	getline(is, tmp);
	// Strängström med antal songs
	stringstream albumSongs_Stream(tmp);
	// Konverterar til int
	albumSongs_Stream >> album_songs;

	//Läser in songs
	for (int i = 0; i < album_songs; ++i)
	{
		// Lägger till songs i albumets vector
		is >> songObj;
		// Tar bort newline
		is.ignore(10000, '\n');
		album.addSong(songObj);
	}

	return is;
}