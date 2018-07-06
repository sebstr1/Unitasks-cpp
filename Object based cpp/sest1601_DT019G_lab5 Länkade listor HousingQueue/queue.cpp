// Defintionsfil
// Filnamn: queue.cpp
//---------------------------------------------------------------------------
// Nodeklassen placeras i cpp-filen f�r att den ska bli �tkomlig ENBART f�r
// klasserna QList och QIterator. P� detta s�tt kan datamedlemmarna g�ras
// public.

#include "queue.h"
#include <iomanip>
#include <iostream>
using namespace std;



class Node
{
public:
	Node *next;
	Item data;
	Node(Node *n, Item newData) : next(n), data(newData) {}
};
// Fyll p� med funktionsdefinitioner f�r medlemsfunktionerna i QIterator och
// QList nedan!

//**************************************************************
//QIterator
//***************************************************************

//Specifikationer f�r medlemsfunktionerna i klassen QIterator :
//Namn: QIterator
//	Uppgift : S�tter datamedlemmen node att peka p� nullptr
//	Indata : -
//	Utdata : -
QIterator::QIterator()
{
	node = nullptr;
}

/*Namn : QIterator
Uppgift : Initierar datamedlemmen node med den pekare som ges som indata
Indata : En pekare till en nod i listan, Node *node
Utdata : -*/
QIterator::QIterator(Node * n)
{
	node = n;
}

//Namn : operator*
//Uppgift : �verlagrar dereferensoperatorn.
//Indata : -
//Utdata : Returnerar en referens till data som ligger i den nod som datamedlemmen node pekar
//p�.
//Returdatatyp : Item &, d.v.s.en referens till ett Person - objekt.
//Med denna operator ska man kunna l�sa v�rden fr�n en nod i Qlist och tilldela nya
//v�rden till en nod i QList
Item & QIterator::operator*() const
{
	return node->data;
}

/*Namn : operator++ (prefix)
Uppgift : �verlagrar ++ operatorn genom att flytta iteratorn till n�sta nod.Denna syntax f�r
�verlagringen av++ - operatorn ger en prefix++ operator.
Indata : -
Utdata : Returnerar inneh�llet i den nod som iteratorn pekar p� sedan ++ utf�rts, genom att
returnera en referens till det som det egna objektet pekar p� dvs. *this.
Returdatatyp : QIterator &*/
QIterator & QIterator::operator++()
{
	node = node->next;
	
	return *this;

}

/*Namn : operator++ (postfix)
Uppgift : �verlagrar ++ operatorn genom att flytta iteratorn till n�sta nod.Denna syntax f�r
�verlagringen av++ - operatorn ger en postfix++ operator.
Indata : -
Utdata : Returnerar inneh�llet i den nod som iteratorn pekar p� innan ++ utf�rs.
Returdatatyp : QIterator*/
QIterator QIterator::operator++(int)
{
	Node *postfix = node;
	node = node->next;
	return postfix;
}

/*Namn : operator!=
Uppgift : �verlagrar olikhetsoperatorn f�r tv� QIteratorobjekt
Indata : Ett konstant QIteratorobjekt, const QIterator &qi
Utdata : true om det v�nstra och det h�gra objektet inte �r lika annars false*/
bool QIterator::operator!=(const QIterator & qi) const
{
	return !(node == qi.node);
}

//*******************************************************************************************
//QLIST
//*******************************************************************************************

//K�lista
//I klassen QList(k�lista) tillkommer f�ljande medlemsfunktioner j�mf�rt med en ��kta� k�klass :
//QIteator begin()
//QIterator end()
//bool del(Item item)
//begin() och end() �r inline - funktioner definierade i headerfilen ovan, medan del() specificeras
//nedan.
//Specifikationer f�r medlemsfunktionerna i klassen QList :
//*******************************************************************************************
//Namn: QList
//Uppgift : S�tter first = nullptr och last = nullptr
//Indata : -
//Utdata : -
//////////////////////////////////////////////////////////////
//Namn : ~QList
//Uppgift : Frig�r den plats som allokerats f�r listans noder.
//Indata : -
//Utdata : -
QList::~QList()
{
	while (!isEmpty())
	{
		Node *tmp = first;
		first = first->next;
		delete tmp;
	}
}

//Namn : enque
//Uppgift : L�gg till en nod i sist listan och l�gg in data f�r en person(item) i denna nod.
//L�t last - pekaren peka p� denna nod
//Indata : Item item, d.v.s.data f�r en person(Person)
//Utdata : -
void QList::enque(Item item)
{
	Node *pNew = new Node(0, item);
	if (isEmpty())
	{
		first = pNew;
	}
	else
	{
		last->next = pNew;
	}

	last = pNew;
}


//Namn : deque
//Uppgift : Tar bort en nod i b�rjan av listan.Data f�r den person som ligger i noden returneras via
//en referensdeklarerad parameter.Vidare returneras false om listan �r tom annars true
//Indata : -
//Utdata : false om listan �r tom annars true.Item &item, data f�r den person som tas bort fr�n
//listan.
bool QList::deque(Item & item)
{
	if (isEmpty())
		return false;
	
	Node *n = first;
	item = n->data;
	first = first->next;
	if (isEmpty()) //Om k�n BLEV tom
		last = 0; //=NULL
	delete n;
	/////////////////////////////////////////////////////////////////size--;
	return true;
}
//Namn : del
//Uppgift : Tar bort den nod i listan som inneh�ller den person som skickas med som argument
//Indata : Item item, d.v.s.data f�r den person som ska tas bort ur k�n.
//Utdata : true om personen angiven i item togs bort, annars false.
bool QList::del(Item item)
{
	
	//Skapar tv� noder
	Node *AktuellNod;
	Node *nodenEfterAktuell;

	//S�tter noderna till k�huvve
	nodenEfterAktuell = first;
	for (AktuellNod = first; AktuellNod->data.getPersNr() != item.getPersNr(), AktuellNod != last; AktuellNod = AktuellNod->next)
	{
		//F�r att kolla om vi hittar det vi s�ker
		bool rightSpot = true;
		rightSpot = AktuellNod->data.getPersNr() != item.getPersNr();
		
		//hittade vi det vi s�kte s� hoppa ur for loopen.
		if (rightSpot == false)
		{
			
			break;
		}
		
	}

	//Specialfall: Om noden som ska tas bort dvs AktuellNod s� s�tt f�rsta noden till n�sta nod
	if (AktuellNod == first)
	{
		first = first->next;
	}
	//Annars..
	else
	{
		// Eftersom Aktuell Nod ska tas bort s�tter vi nodenEfterAktuell till att peka p� noden som kommer efter aktuell.
		nodenEfterAktuell->next = AktuellNod->next;

		// Specialfall: Om noden som ska tas bort �r sista noden s� �r n�sta nod nullptr..
		if (AktuellNod->next == nullptr)
		{
			last = nodenEfterAktuell;
		}
	}
	//Tar bort aktuel nod, dvs personen med personnummeret vi ville ta bort
	delete AktuellNod;
	return true;
}

//Namn : isEmpty
//Uppgift : Unders�ker om det finns n�gra noder i listan.
//Indata : -
//Utdata : true om listan �r tom annars false
bool QList::isEmpty() const
{
	return first == nullptr; // 0 eller nullptr?
}