// Defintionsfil
// Filnamn: queue.cpp
//---------------------------------------------------------------------------
// Nodeklassen placeras i cpp-filen för att den ska bli åtkomlig ENBART för
// klasserna QList och QIterator. På detta sätt kan datamedlemmarna göras
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
// Fyll på med funktionsdefinitioner för medlemsfunktionerna i QIterator och
// QList nedan!

//**************************************************************
//QIterator
//***************************************************************

//Specifikationer för medlemsfunktionerna i klassen QIterator :
//Namn: QIterator
//	Uppgift : Sätter datamedlemmen node att peka på nullptr
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
//Uppgift : Överlagrar dereferensoperatorn.
//Indata : -
//Utdata : Returnerar en referens till data som ligger i den nod som datamedlemmen node pekar
//på.
//Returdatatyp : Item &, d.v.s.en referens till ett Person - objekt.
//Med denna operator ska man kunna läsa värden från en nod i Qlist och tilldela nya
//värden till en nod i QList
Item & QIterator::operator*() const
{
	return node->data;
}

/*Namn : operator++ (prefix)
Uppgift : Överlagrar ++ operatorn genom att flytta iteratorn till nästa nod.Denna syntax för
överlagringen av++ - operatorn ger en prefix++ operator.
Indata : -
Utdata : Returnerar innehållet i den nod som iteratorn pekar på sedan ++ utförts, genom att
returnera en referens till det som det egna objektet pekar på dvs. *this.
Returdatatyp : QIterator &*/
QIterator & QIterator::operator++()
{
	node = node->next;
	
	return *this;

}

/*Namn : operator++ (postfix)
Uppgift : Överlagrar ++ operatorn genom att flytta iteratorn till nästa nod.Denna syntax för
överlagringen av++ - operatorn ger en postfix++ operator.
Indata : -
Utdata : Returnerar innehållet i den nod som iteratorn pekar på innan ++ utförs.
Returdatatyp : QIterator*/
QIterator QIterator::operator++(int)
{
	Node *postfix = node;
	node = node->next;
	return postfix;
}

/*Namn : operator!=
Uppgift : Överlagrar olikhetsoperatorn för två QIteratorobjekt
Indata : Ett konstant QIteratorobjekt, const QIterator &qi
Utdata : true om det vänstra och det högra objektet inte är lika annars false*/
bool QIterator::operator!=(const QIterator & qi) const
{
	return !(node == qi.node);
}

//*******************************************************************************************
//QLIST
//*******************************************************************************************

//Kölista
//I klassen QList(kölista) tillkommer följande medlemsfunktioner jämfört med en ”äkta” köklass :
//QIteator begin()
//QIterator end()
//bool del(Item item)
//begin() och end() är inline - funktioner definierade i headerfilen ovan, medan del() specificeras
//nedan.
//Specifikationer för medlemsfunktionerna i klassen QList :
//*******************************************************************************************
//Namn: QList
//Uppgift : Sätter first = nullptr och last = nullptr
//Indata : -
//Utdata : -
//////////////////////////////////////////////////////////////
//Namn : ~QList
//Uppgift : Frigör den plats som allokerats för listans noder.
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
//Uppgift : Lägg till en nod i sist listan och lägg in data för en person(item) i denna nod.
//Låt last - pekaren peka på denna nod
//Indata : Item item, d.v.s.data för en person(Person)
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
//Uppgift : Tar bort en nod i början av listan.Data för den person som ligger i noden returneras via
//en referensdeklarerad parameter.Vidare returneras false om listan är tom annars true
//Indata : -
//Utdata : false om listan är tom annars true.Item &item, data för den person som tas bort från
//listan.
bool QList::deque(Item & item)
{
	if (isEmpty())
		return false;
	
	Node *n = first;
	item = n->data;
	first = first->next;
	if (isEmpty()) //Om kön BLEV tom
		last = 0; //=NULL
	delete n;
	/////////////////////////////////////////////////////////////////size--;
	return true;
}
//Namn : del
//Uppgift : Tar bort den nod i listan som innehåller den person som skickas med som argument
//Indata : Item item, d.v.s.data för den person som ska tas bort ur kön.
//Utdata : true om personen angiven i item togs bort, annars false.
bool QList::del(Item item)
{
	
	//Skapar två noder
	Node *AktuellNod;
	Node *nodenEfterAktuell;

	//Sätter noderna till köhuvve
	nodenEfterAktuell = first;
	for (AktuellNod = first; AktuellNod->data.getPersNr() != item.getPersNr(), AktuellNod != last; AktuellNod = AktuellNod->next)
	{
		//För att kolla om vi hittar det vi söker
		bool rightSpot = true;
		rightSpot = AktuellNod->data.getPersNr() != item.getPersNr();
		
		//hittade vi det vi sökte så hoppa ur for loopen.
		if (rightSpot == false)
		{
			
			break;
		}
		
	}

	//Specialfall: Om noden som ska tas bort dvs AktuellNod så sätt första noden till nästa nod
	if (AktuellNod == first)
	{
		first = first->next;
	}
	//Annars..
	else
	{
		// Eftersom Aktuell Nod ska tas bort sätter vi nodenEfterAktuell till att peka på noden som kommer efter aktuell.
		nodenEfterAktuell->next = AktuellNod->next;

		// Specialfall: Om noden som ska tas bort är sista noden så är nästa nod nullptr..
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
//Uppgift : Undersöker om det finns några noder i listan.
//Indata : -
//Utdata : true om listan är tom annars false
bool QList::isEmpty() const
{
	return first == nullptr; // 0 eller nullptr?
}