//Person.h
///////////////////////
//////////////////////
#ifndef PersonH
#define PersonH
#include <string>
#include "name.h"
#include "address.h"
using namespace std;

class Person
{
private:
	Name name;
	Address address;
	string PersNr;
	int shoeSIZE;

public:
	//Standard konstruktorn
	Person();
	// Överlagrad kons~
	Person(Name pName, Address pAddress, string pPersNr, int pshoeSIZE);

	//Setfunktioner
	void setName(Name pName);

	void setAddress(Address pAddress);

	void setPersNr(string pPersNr);

	void setshoeSIZE(int shoeSIZE);

	//Getfunktioner
	Name getName() const;

	Address getAddress() const;

	string getPersNr() const;
	
	int getshoeSIZE() const;

	// Överlagring av klassens operatorer
	bool operator<(const Person &k) const;
	bool operator ==(const Person &k) const;
};

// Överlagring av operatorer för utskrift och inläsning
ostream &operator<<(ostream &os, const Person &person);
istream &operator >> (istream &is, Person &person);

#endif
