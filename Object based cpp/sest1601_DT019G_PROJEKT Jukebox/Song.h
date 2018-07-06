// Song.h
#ifndef SongH
#define SongH
#include <string>
#include "Time.h"
#include <iostream>
#include <sstream>
using namespace std;


class Song
{
	private:
		string songTitel;
		string songArtist;
		Time songLengd;

	public:
		//Standard Konstruktor
		Song();

		//�verlagrad Konstruktor
		Song(string psongTitel, string psongArtist, Time psongLengd);

		//Setfunktioner
		void setSongTitel(string pTitel);

		void setSongArtist(string pArtist);

		void setSongLengd(Time pLengd);

		//Getfunktioner
		string getSongTitel() const;
		string getSongArtist() const;
		Time getSongLengd() const;
};



// �verlagring av << och >> f�r utskrift och inl�sning till / fr�n fil
std::ostream &operator<<(std::ostream &os, const Song &song);
std::istream &operator >> (std::istream &is, Song &song);

#endif