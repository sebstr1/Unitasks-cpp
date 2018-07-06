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
	Person();
	Person(Name pName, Address pAddress, string pPersNr, int pshoeSIZE);

	void setName(Name pName);

	void setAddress(Address pAddress);

	void setPersNr(string pPersNr);

	void setshoeSIZE(int shoeSIZE);

	Name getName() const;

	Address getAddress() const;

	string getPersNr() const;
	
	int getshoeSIZE() const;
};
#endif
