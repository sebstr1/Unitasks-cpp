// Album.h
#ifndef AlbumH
#define AlbumH
#include <string>
#include <iostream>
#include <vector>
#include "Song.h"
#include "Time.h"
#include <sstream>
using namespace std;

class Album
{
private:
	string AlbumNamn;
	vector <Song> Vector_of_Songs;

public:
	//Standardkonstruktorn
	Album();
	//Överlagrad konstruktor
	Album(string pAlbumNamn);


	//Setfunktioner
	void setAlbumNamn(string pAlbumNamn);

	//Getfunktioner
	string getAlbumNamn() const;


	//Medlemsfunktioner
	Time Album::AlbumLengd() const; // Hämtar den totala albumtiden
	void Album::addSong(Song &song); //Lägger till en song
	void Album::clearVector_of_Songs();		//Tömmar Sångvectorn
	int Number_of_Songs() const;			//Hämtar antalet låtar i albumet
	vector<Song> getVector_of_Songs() const { return Vector_of_Songs; } //Hämtar sångvectorn

	// Överlagring av operatorer
	bool Album::operator<(const Album & pAlbum) const;
	
	
	//bool operator<(const Album &name) const;
};

//KDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDLSLKDLSKDLSKDLSKDLSKLD
// Överlagring av operatorer för utskrift och inläsning
ostream &operator<<(ostream &os, const Album &pAlbum);
istream &operator >> (istream &is, Album &pAlbum);


#endif
