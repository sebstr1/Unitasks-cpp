// name.h
#ifndef nameH
#define nameH
#include <string>
using namespace std;

class Name
{
private:
	string FirstName;
	string LastName;

public:
	//Standardkonstruktorn
	Name();
	//Överlagrad konstruktor
	Name(string pFirstName, string pLastName);


	//Set
	void setFirstName(string pFirstName);

	void setLastName(string pLastName);
	//Get
	string getFirstName() const;

	string getLastName() const;



	// Överlagring av operatorer
	bool operator<(const Name &name) const;
	bool operator==(const Name &name) const;
};

// Överlagring av operatorer för utskrift och inläsning
ostream &operator<<(ostream &os, const Name &n);
istream &operator >> (istream &is, Name &n);


#endif
