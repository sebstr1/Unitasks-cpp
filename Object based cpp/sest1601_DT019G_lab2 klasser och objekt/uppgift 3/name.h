// klassDef.h
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
	Name();
	Name(string pFirstName, string pLastName);

	void setFirstName(string pFirstName);

	void setLastName(string pLastName);

	string getFirstName() const;

	string getLastName() const;
};
#endif
