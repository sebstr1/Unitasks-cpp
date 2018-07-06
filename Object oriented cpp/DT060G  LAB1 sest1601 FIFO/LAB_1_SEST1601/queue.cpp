/*
* Filnamn: queue.cpp
* Labb 1 uppgift 1
* namn: Sebastian Strindlund ses1601
*/

#include "queue.h"
#include <iomanip>
#include <iostream>
using namespace std;

//Överladdad konstruktor
Queue::Queue(int n)
{
	dumbArray.reset(new Type[n]);
	head = -1; //Deque here
	tail = -1; //Enque here
	nElem = 0;
	maxElem = n;
}

void Queue::enqueue(Type elem)
{

	//Om det är första elemetet i kön
	if (head == -1 && tail == -1)
	{
		head = 0;
		tail = 0;
	}

	//Om [tail] nått slutet av arrayen
	else if (tail == maxElem - 1)
	{
		tail = 0;
	}

	else
	{
		tail++;
	}

	//Post Condition Element is inserted as newest element in array
	dumbArray[tail] = elem;
		
	//Uppdaterar antalet element
	nElem++;

}



void Queue::dequeue(Type & elem)
{

	//Elementet som skall tas bort (från head)
	elem = dumbArray[head];

	//Om det endast är ett objekt i kön när Dequeue körs
	if (head == tail)
	{
		head = -1, tail = -1;
		nElem--;
	}

	//Om huvudet når slutet på arrayen så sätt head till 0 för då har den gått runt ett varv.
	else if (head == maxElem - 1)
	{
		head = 0;
	}
	// Flytta fram huvudet och uppdaterar antalet element
	else
	{
		head++;
		nElem--;
	}
		
}

//Returnerar antalet element som finns i arrayen just nu.
int Queue::length() const
{
	return nElem;
}

//Kontrollerar om kön är full
bool Queue::full() const
{
	// Om tail är på sista platsen i arrayen eller om huvdet ligger på tail + 1 så är kön full.
	if (tail == maxElem - 1 && head == 0 || (head == tail + 1))
	{
		return true;
	}
	//Returnera false om kön inte var full.
	else
	{
		return false;
	}

}

//Kontrollerar om kön är tom
bool Queue::empty() const
{
	//Står head på -1 så är kön tom dvs return true
	if (head == -1)
	{
		return true;
	}
	//Returnerar false, kön är inte tom.
	else
	{
		return false;
	}
}

//Returneran maxElem som är maxstorleken på Arrayen.
int Queue::capacity() const
{
	return maxElem;
}


