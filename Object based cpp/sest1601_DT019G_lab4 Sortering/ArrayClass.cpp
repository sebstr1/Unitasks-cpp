//ArrayClass.cpp

#include "ArrayClass.h"
#include "Timer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>



using namespace std;

////------------------------------------------------------------------------------
//// Definition av medlemsfunktioner
////------------------------------------------------------------------------------
////------------------------------------------------------------------------------
////Förvald konstruktor (Default constructor)
////------------------------------------------------------------------------------
IntArray::IntArray() : maxSize(0), size(0)
{
	arr = nullptr;
}////------------------------------------------------------------------------------
////Konstruktor för initiering av datamedlemmarna
////------------------------------------------------------------------------------
IntArray::IntArray(int pMaxSize) : maxSize(pMaxSize), size(0)
{
	arr = new int[maxSize];
}

////------------------------------------------------------------------------------
//// Destruktor
////------------------------------------------------------------------------------
IntArray:: ~IntArray()
{
	delete[] arr;
	arr = NULL;
	
}
////------------------------------------------------------------------------------
//// Läs ett värde från arrayen
////------------------------------------------------------------------------------
int IntArray::getValue(int idx) const
{
	return arr[idx];
}////------------------------------------------------------------------------------
//// Lägg in ett värde i arrayen
////------------------------------------------------------------------------------
bool IntArray::addValue(int value)
{
	bool valueAdded = false;
	if (size < maxSize)
	{
		arr[size] = value;
		size++;
		valueAdded = true;
	}
	return valueAdded;
}////------------------------------------------------------------------------------
//// Kopieringskonstruktorn
////------------------------------------------------------------------------------
IntArray::IntArray(const IntArray &a) : maxSize(a.maxSize), size(a.size)
{
	arr = new int[a.maxSize];
	for (int i = 0; i<a.size; i++)
		arr[i] = a.arr[i];
}
////------------------------------------------------------------------------------
//// Tilldelningsoperatorn
////------------------------------------------------------------------------------
const IntArray &IntArray::operator=(const IntArray &a)
{
	if (this != &a)
	{
		delete[]arr;
		arr = new int[a.maxSize];
		maxSize = a.maxSize;
		size = a.size;
		for (int i = 0; i < a.size; i++)
			arr[i] = a.arr[i];
	}
	return *this;
}
//------------------------------------------------------------------------------
//******************************************************************************
//------------------------------------------------------------------------------
//Fyll arrayen med slumptal
void IntArray::insert_random(IntArray &array)
{
	//Min och max värde
	const int min = 0;
	const int max = maxSize;

	
	//Initierar slumpmotorn
	random_device number;	//intervallet 0 till arrayens maximala storlek.
	uniform_int_distribution<int> range(min, max);

	// Lägger in slumpal i arrayen
	for (int i = 0; i < maxSize; i++)		array[i] = range(number);


	cout << endl;
}

void IntArray::print_array(IntArray &array)
{
	// Skriver ut arrayen
	
	for (int i = 0; i < 25; i++)	{		cout << setw(7) << array[i];
	}

	cout << endl << endl;
}

//--------------------------------------------------------------------------------
//Quicksort----------------------------------------------------------------------
//------------------------------------------------------------------------------
void IntArray::Sorting(IntArray &array, int selector)
{
	//Timer objekt.
	Timer myTimer;

	// Variabler för aktuell timer och totaltid
	double activeTimer, totalTime = 0.0;

	//Hämtar det aktuella maxvärdet
	const int max = array.getMaxSize();
		
		
	// 1 = Quicksort2
	if (selector == 1)
	{
		//Kör sorteringen 10 gånger för att ta ut ett medelvärde
		for (int i = 0; i < 10; i++)
		{
			IntArray array(max);
			//Slumpar arrayen
			array.insert_random(array);

			myTimer.start();
			//Sorterar arrayen
			array.quick2Wrapper(array, max);
			//Stoppar timern
			activeTimer = myTimer.stop();
			cout << "QuickSort Nr: " << i + 1 << " = " << activeTimer/1000000 << " sek, arraystorlek " << max << endl;

			totalTime += activeTimer;
		}
		totalTime = totalTime / 10;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl << "Medeltid för Quicksort2 @ Array av storleken " << max << " är: " << totalTime/1000000 << " sek" << endl;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		array.saveToFile("Quicksort", array.getMaxSize(), totalTime);
	}

	// 2 = BubbleSort2
	if (selector == 2)
	{
		//Kör sorteringen 10 gånger för att ta ut ett medelvärde
		for (int i = 0; i < 10; i++)
		{
			IntArray array(max);
			//Slumpar arrayen
			array.insert_random(array);
					
			//Sorterar arrayen
			activeTimer = array.BubbleSort2();
						
			cout << "Bubblesort2 nr " << i + 1 << " = " << activeTimer/1000000 << " sek, arraystorelk: " << max << endl;	

			totalTime += activeTimer;
		}
		totalTime = totalTime / 10;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl << "Medeltid för BubbleSort2 @ Array av storleken " << max << " är: " << totalTime/1000000 << " sek" << endl;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		array.saveToFile("Bubblesort2", array.getMaxSize(), totalTime);
	}

	// 3 = InsertionsSort
	if (selector == 3)
	{
		//Kör sorteringen 10 gånger för att ta ut ett medelvärde
		for (int i = 0; i < 10; i++)
		{
			IntArray array(max);
			//Slumpar arrayen
			array.insert_random(array);

			//Sorterar arrayen
			activeTimer = array.insertionSort();

			cout << "Insertionsort nr " << i + 1 << " = " << activeTimer / 1000000 << " sek, arraystorlek: " << max << endl;

			totalTime += activeTimer;
		}
		totalTime = totalTime / 10;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl << "Medeltid för Insertionsort @ Array av storleken " << max << " är: " << totalTime / 1000000 << " sek" << endl;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		array.saveToFile("Insertionsort", array.getMaxSize(), totalTime);
	}
		
	// 4 = SelectionsSort
	if (selector == 4)
	{
		//Kör sorteringen 10 gånger för att ta ut ett medelvärde
		for (int i = 0; i < 10; i++)
		{
			IntArray array(max);
			//Slumpar arrayen
			array.insert_random(array);

			//Sorterar arrayen
			activeTimer = array.SelectionSort();

			cout << "SelectionSort nr " << i + 1 << " = " << activeTimer / 1000000 << " sek " << endl;

			totalTime += activeTimer;
		}
		totalTime = totalTime / 10;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		cout << endl << "Medeltid för SelectionSort @ Array av storleken " << max << " är: " << totalTime / 1000000 << " sek" << endl;
		cout << endl << "---------------------------------------------------------------------------------------------------------------" << endl;
		array.saveToFile("SelectionSort", array.getMaxSize(), totalTime);
	}
}


void IntArray::quick2(IntArray & array, int first, int last)
{
	int low = first;
	int high = last;
	int x = array[(first + last) / 2]; // Välj mittvärdet som pivotelement
	do
	{
		// Gå från början och sök första värdet som är större än x
		while (array[low] < x) { low++; }

		// Gå från slutet och sök första värdet som är mindre än x
		while (array[high] > x) { high--; }

		if (low <= high)
		{
			swap(array[low], array[high]);
			low++;
			high--;
		}
	} while (low <= high); // Loopa genom vektorn medan low <= high
						   // Rekursion
						   // "Sortera" vänster halva om high inte nått vektorns första element
	if (first < high) quick2(array, first, high);
	// "Sortera" höger halva om low inte nått vektorns sista element
	if (low < last) quick2(array, low, last);
}

//Wrapper för quicksort2
void IntArray::quick2Wrapper(IntArray & array, int max)
{
	quick2(array, 0, max - 1);}double IntArray::SelectionSort()
{
	Timer time;
	time.start();
	int smallIdx = 0;
	for (int i = 0; i < maxSize - 1; i++)
	{
		smallIdx = i; //Index för det minsta elementet till höger om pos i
		for (int j = i + 1; j < maxSize; j++) // Sök det minsta "osorterade" elementet
			if (arr[j] < arr[smallIdx])
				smallIdx = j; // Spara index för det minsta elementet

		if (smallIdx != i) // Byt plats om det fanns något mindre än a[i]
			swap(arr[i], arr[smallIdx]);
	}	return time.stop();
}
double IntArray::BubbleSort2(){	Timer time;	time.start();	for (int pass = 0; pass < maxSize - 1; pass++)
		for (int i = 0; i < maxSize - 1; i++)
			if (arr[i] > arr[i + 1]) // Jämför elementen i och i+1
			{
				swap(arr[i], arr[i + 1]); // Byt plats om element i > element i+1
			}	return time.stop();}double IntArray::insertionSort()
{
	Timer time;
	time.start();
	int i, j, tmp;
	for (i = 1; i < maxSize; i++) {
		j = i;
		while (j > 0 && arr[j - 1] > arr[j]) {
			tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;
			j--;
		}
	}
	return time.stop();
}// Byt plats på två heltal
void IntArray::swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
	
}// Skriv resultat till fil
void IntArray::saveToFile(std::string sortFunk, IntArray max, double sum)
{
	
	// ASCII-tab
	char tab = 9;

	// Öppna filen för skrivning
	fstream outFile("result.txt", ios::out | ios::app);

	// Om det gick bra att öppna filen
	if (outFile.is_open())
	{
		// Skriv resultatets medelvärde (sum/10) till fil med 6 decimaler
		outFile << fixed << setprecision(6);
		outFile << sortFunk << tab << max.getMaxSize() << tab << sum / 10 << endl;
	}
	else
		// Filen kunde inte öppnas
		cout << "Gick inte att öppna filen." << endl;

	// Stäng utfilen
	outFile.close();
}
// Överlagrad []operator
int &IntArray::operator [](int idx)
{
	return arr[idx];
}

// Överlagrad const []operator
int IntArray::operator [](int idx) const
{
	return arr[idx];
}