/*
* Filnamn: DataFileReader.h
* Labb 4 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Innehåller klassen DataFileReader. Används för att läsa igenom fil
* och filtrera bort värden som ej kunde läsas in ordentligt.
*
*/

#ifndef DataFileReaderH
#define DataFileReaderH

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

template<typename T>
class DataFileReader {

public:
	

	DataFileReader();
	DataFileReader(string aDataFileName, string aErrorFileName);
	/* pre: A file named aDataFile contains values to read.
	*/


	~DataFileReader();
	
	


	void openFiles();
	/* post: An input stream from the file named aDataFile and
	an output stream to the file named aErrorFile are
	opened. If either of these operations fails a
	runtime_error exception is thrown. */


	bool readNextValue(T &aValue);
	/* pre: openFiles has been successfully called.
	post: If a value has been successfully read, aValue
	holds that value and true is returned.
	Else, the read operation encountered an
	end-of-file and false is returned. */

private:
	string DataName;
	string ErrorName;
	ifstream dataStream; 
	ofstream errorStream;

};
#endif



