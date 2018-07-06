#ifndef ArrayClass_H
#define ArrayClass_H
#include <iostream>
#include <random>
#include <iomanip>
#include <string>

class IntArray
{
private:
	int *arr; // Pekare till arrayen
	size_t maxSize; // Arrayens maximala storlek
	size_t size; // IntArrayens aktuella storlek
public:
	// ---------------- Konstruktorer och destruktor
	IntArray();
	IntArray(int pNum);
	IntArray(const IntArray &a);
	~IntArray();

	//------------------ Get- och set-funktioner
	size_t getMaxSize() const { return maxSize; }
	size_t getSize() const { return size; }
	int getValue(int idx) const;
	bool addValue(int value);

	//Mina eget tillagda
	void insert_random(IntArray &array);
	void print_array(IntArray & array);
	
	//Quicksort
	void Sorting(IntArray & array, int selector);
	void quick2(IntArray & array, int first, int last);
	void quick2Wrapper(IntArray & array, int max);

	//SelectionSort
	double SelectionSort();
	//BubbleSort
	double BubbleSort2();
	//InsertionSor
	double insertionSort();


	void saveToFile(std::string sortFunk, IntArray max, double sum);

	void swap(int & a, int & b);

	// Överlagrade operatorer
	int &operator [](int idx);
	int operator [](int idx) const;
	int operator <(const IntArray &a) const;
	int operator >(const IntArray &a) const;


	// ----------------- Överlagra tilldelningsoperatorn
	const IntArray &operator=(const IntArray &a);
};

#endif