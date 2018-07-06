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
	Address();
	Address(string pGatu_Adress, string pStad, string ZipCode);

	void setGatu_Address(string pFirstName);

	void setStad(string pLastName);

	void setZipCode(string pZipCode);

	string getGatu_Address() const;

	string getStad() const;

	string getZipCode() const;
};
#endif
