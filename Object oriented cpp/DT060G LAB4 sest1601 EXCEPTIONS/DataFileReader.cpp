/*
* Filnamn: DataFileReader.h
* Labb 4 uppgift 1
* namn: Sebastian Strindlund ses1601
*
* Definitionsfil för klassen DataFileReader
* Filtrerar bort värden som ligger out of range.
*
*/

#include "DataFileReader.h"
#include <exception>
#include <stdexcept>


template<typename T>
DataFileReader<T>::DataFileReader()
{
}

/* pre: A file named aDataFile contains values to read.
*/
template<typename T>
DataFileReader<T>::DataFileReader(string aDataFileName, string aErrorFileName)
{
	
	// Kontrollerar om kundfilen går att öppna(existerar)
	ifstream inFile(aDataFileName);
	if (inFile.is_open())
	{
		//Kontrollerar om filen är tom
		if (inFile.eof())
		{
			cout << "Empty file" << endl;
		}
		else
		{
			DataName = aDataFileName;
			ErrorName = aErrorFileName;
		}	
	}
	else
	{
		cout << "File with filename " << aDataFileName << " does not exist!" << endl;
	}
}

/* post: Files are closed */
template<typename T>
DataFileReader<T>::~DataFileReader()
{
	dataStream.close();
	errorStream.close();
}


/* post: An input stream from the file named aDataFile and
an output stream to the file named aErrorFile are
opened. If either of these operations fails a
runtime_error exception is thrown. */
template<typename T>
void DataFileReader<T>::openFiles()
{

	//Kontrollerar om det gick att öppna input och outputstream
	dataStream.open(DataName);
	if (!dataStream.is_open())
	{
		throw std::runtime_error("Runtime error.. Could not open file.");
	}

	errorStream.open(ErrorName, ios::app);
	if (!errorStream.is_open())
	{
		throw std::runtime_error("Runtime error.. Could not open file.");
	}
}


/* pre: openFiles has been successfully called.
post: If a value has been successfully read, aValue
holds that value and true is returned.
Else, the read operation encountered an
end-of-file and false is returned. */
template<typename T>
bool DataFileReader<T>::readNextValue(T & aValue)
{

	ios_base::iostate mask = ios::eofbit | ios::failbit | ios::badbit; // Errorflagor med exklusiv OR
	dataStream.exceptions(mask);  //Sätter errorflaggor för datafilen.
	double tmpDouble = 0;
	try {

		dataStream >> aValue;
		//Testar om strängen endast innehåller siffror
		//tmpDouble = stod(aValue);
		return true;
	
	}
	catch (ios_base::failure &eo) // If it failed to read value
	{

		ios_base::iostate flags = dataStream.rdstate(); // Get flags

		if (flags & ios::eofbit) // If end of file reached
		{
			cout << "End of file reached." << endl;
			dataStream.clear();
			return false;
		}
		else
		{

			cout << "Read error occured, saved data to ReadErrors.dat" << endl;
			string error;
			dataStream.clear();
			getline(dataStream, error);
			
			errorStream << error << endl;
			
			readNextValue(aValue);

		}

	}

}
