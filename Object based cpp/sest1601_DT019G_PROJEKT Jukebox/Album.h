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
	//�verlagrad konstruktor
	Album(string pAlbumNamn);


	//Setfunktioner
	void setAlbumNamn(string pAlbumNamn);

	//Getfunktioner
	string getAlbumNamn() const;


	//Medlemsfunktioner
	Time Album::AlbumLengd() const; // H�mtar den totala albumtiden
	void Album::addSong(Song &song); //L�gger till en song
	void Album::clearVector_of_Songs();		//T�mmar S�ngvectorn
	int Number_of_Songs() const;			//H�mtar antalet l�tar i albumet
	vector<Song> getVector_of_Songs() const { return Vector_of_Songs; } //H�mtar s�ngvectorn

	// �verlagring av operatorer
	bool Album::operator<(const Album & pAlbum) const;
	
	
	//bool operator<(const Album &name) const;
};

//KDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDLSLKDLSKDLSKDLSKDLSKLD
// �verlagring av operatorer f�r utskrift och inl�sning
ostream &operator<<(ostream &os, const Album &pAlbum);
istream &operator >> (istream &is, Album &pAlbum);


#endif
