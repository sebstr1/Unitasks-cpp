// address.h
#ifndef addressH
#define addressH
#include <string>
using namespace std;

class Address
{
private:
	string Gatu_Address;
	string ZipCode;
	string Stad;

public:
	//Standardkonstruktorn
	Address();
	//Överlagrad kons
	Address(string pGatu_Adress, string pStad, string ZipCode);

	//Set
	void setGatu_Address(string pFirstName);

	void setStad(string pLastName);

	void setZipCode(string pZipCode);

	//Get
	string getGatu_Address() const;

	string getStad() const;

	string getZipCode() const;
	
	// Överlagrade operatorer
	bool operator<(const Address &add) const;
	bool operator==(const Address &add) const;
};

	// Överlagring av operatorer för inläsning och utskrift
	ostream &operator<<(ostream &os, const Address &add);
	istream &operator >> (istream &is, Address &add);
#endif
