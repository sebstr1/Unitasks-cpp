//Time.h
///////////////////////
//////////////////////
#ifndef TimeH
#define TimeH
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Time
{
	private:
		int timmar;
		int minuter;
		int sekunder;

	public:
		//Standard konstruktorn
		Time();
		// �verlagrad kons~
		Time(int timmar, int minuter, int sekunder);

		//Setfunktioner
		void setTimmar(int pTimmar);
		void setMinuter(int pMinuter);
		void setSekunder(int pSekunder);


		//Getfunktioner
		int getTimmar() const;
		int getMinuter() const;
		int getSekunder() const;

		// �verlagring av klassens operatorer
		Time operator+(const Time &tid);
		bool operator<(const Time &tid) const;
		bool operator ==(const Time &tid) const;
};

// �verlagring av operatorer f�r utskrift och inl�sning
std::ostream &operator<<(std::ostream &os, const Time &t);
std::istream &operator >> (std::istream &is, Time &t);

#endif
