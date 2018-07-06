/*
* Filnamn: Bowser.h
* Labb 5 
* namn: Sebastian Strindlund ses1601
*
* Filen inneh�ller klassen Bowser och dess implementationer
* som hanterar en lista av antingen typen Int eller double.
*
*
*/
#pragma once

#include <iomanip>
#include <iostream>
#include <fstream>
#include <list>
#include <random>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <functional>

using std::list;
using std::cout;

template<typename T>
class Bowser {

private:	
	list<T> theList; //Listan som anv�nds
public:
	Bowser() { } // Konstruktor
	Bowser(list<T> aBowzerList); // Konstruktor
	~Bowser() {}   // Destruktor

//________________________________________________________________//

	void fill_list();	 //  Fyller hela listan
	void sumList();		 //	Summera listan
	void Average();		 //	H�mta medel f�r listan
	void findShit();	 //	Hitta f�rsta tal mellan 1500 och 1900
	void dividebytwo();  //	Dela alla tal med tv�
	void iteratorswap(); //	Byt plats p� element
	void MaxMin();		 //	Hitta minsta och st�rsta tal
	void sortASC();		 //	Sortera listan i stigande ordning
	void clearList();	 //	T�m listan
	void writeToFile();  // skriv till fil
	void readFromFile(); //	l�s fr�n fil
	void printAll();     // Skriv ut alla tal
//________________________________________________________________//
	
};

// FunktionsObjekt som testar om n �r inom intervallet
template<typename T>
class InRangeTester {
public:
	bool operator( ) (T n) {
		return (n >= 1500 && n <= 1900);
	}
};// FunktionsObjekt som delar n med tv�
template<typename T>
class Divider {
public:
	T operator( ) (T n) {
		return (n/2);
	}
};

//Funktionsobjekt som kollar om a < b (f�r sortering)
template<typename T>
class Sorter {
public:
	T operator( ) (T a, T b ) {
		return (a < b);
	}
};


//______________________________________________________________________________//

template<typename T>
inline Bowser<T>::Bowser(list<T> intOrDoubleList)
{
	theList = intOrDoubleList;
}


template<typename T>
inline void Bowser<T>::fill_list()
{
	clearList();		// Rensar listan
	theList.resize(20); // S�tter storleken

	
	T MIN = 1000, MAX = 2000;
	std::uniform_real_distribution<> dist(MIN, MAX); //random seed intervall
	std::default_random_engine red(std::time(nullptr)); //randomv�rde
	generate(theList.begin(), theList.end( ), std::bind(dist, red)); // Genererar slumpade v�rden till hela listan

}

// Summerar listan.
template<typename T>
inline void Bowser<T>::sumList()
{
	T x = 0; // Startv�rdet
	T sum = std::accumulate(theList.begin(), theList.end(), x); // Summerar fr�n b�rjan till slutet av listan med startv�rdet x (0)

	
	cout << setprecision(10) << "The sum is: " << sum << endl << endl; 
}

template<typename T>
inline void Bowser<T>::Average() // R�knar ut medelv�rdet p� talen i listan.
{
	T sumAverage = 0;
	auto begin = theList.begin(), end = theList.end(); // Skapar iteratorer
	sumAverage = std::accumulate(begin, end, T(0));      // R�knar ut summan p� listan med accumulate
		sumAverage = sumAverage / theList.size();				// Delar  summan med listans storlek f�r medelv�rdet	cout << "Average is: " << sumAverage << endl << endl;
}

template<typename T>
inline void Bowser<T>::findShit() // Hittar f�rsta talet inom intervallet 1500 - 1900
{
	
	auto start = theList.begin(), stop = theList.end();  //Skapar iteratorer
	auto it = find_if(start, stop, InRangeTester<T>());  //Letar f�rsta in range med hj�lp av funktionsobjekter InRangeTester
	
	
	if (it != stop) // F�rsta in range hittade
		cout << "First in range: " << (*it) << endl;

	else
	{
		cout << "No number in range" << endl;
	}
}

template<typename T>
inline void Bowser<T>::dividebytwo() // Med hj�lp av transform s� utf�r vi funktionsobjektet Divider p� alla v�rden i listan (v�rde/2)
{
	transform(theList.begin(), theList.end(), theList.begin(), Divider<T>());  


}

template<typename T>
inline void Bowser<T>::iteratorswap()  // Byter plats p� f�rsta v�rdet med sista v�rdet, n�st f�rsta, n�st sista osv
{	
	for (auto i = 0; i < theList.size()/2; i++)   //Loopar genom halva listan, eftersom vi �r klar d� vi byter plats p� tv� v�rden varje g�ng.
	{
		std::iter_swap(next(theList.begin(),+i), next(theList.rbegin(),+i)); // Byter plats p� list.begin(), +i och list.reversebegin(), +i (b�rjan+i och slutet-i)
	}
}

template<typename T>
inline void Bowser<T>::MaxMin()		//Hittar max och min i listan med hj�lp av funktionsmallarna min_element och max_element
{
	std::cout << "The smallest element is " << *std::min_element(theList.begin(), theList.end()) << '\n';
	std::cout << "The largest element is " << *std::max_element(theList.begin(), theList.end()) << '\n';
}


//Sorterar listan med hj�lp av lists medlemsfunktion .sort()
template<typename T>
inline void Bowser<T>::sortASC()
{
	theList.sort();
}

template<typename T>
inline void Bowser<T>::clearList()     // Raderar allt inneh�ll i listan.
{
	theList.clear();
	
}

template<typename T>
inline void Bowser<T>::writeToFile()	// Skriver data till fil med ofstream och ostream_iterator.
{
	ofstream filestream("test.txt");
	std::ostream_iterator<T> korv(filestream, "\n");
	std::copy(theList.begin(), theList.end(), korv);
	filestream.close();
}

template<typename T>
inline void Bowser<T>::readFromFile()	// L�ser in fr�n fil med ifStream och istream_iterator
{										//  l�gger sedan till datan i listan med back_inserter
	theList.clear();
	ifstream filestream("test.txt");
	std::copy(istream_iterator<T>(filestream), istream_iterator<T>(), back_inserter(theList));
	filestream.close();

}


template<typename T>
inline void Bowser<T>::printAll()  // Skriver ut hela listan med for_each + lambda
{
	
	cout << "                          Printing!                                  " << endl;
	cout << "---------------------------------------------------------------------" << endl;
	for_each(theList.begin(), theList.end(), [](T&value)
	{
		cout << value << endl;

	});

}


