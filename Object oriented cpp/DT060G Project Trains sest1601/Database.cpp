/* 2017-05-14
* Filnamn: Database.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Filen anv�nds f�r att att l�sa in information fr�n filer, lagra och serva
* informationen till klasser som fr�gar efter den (T�g, T�gstationer och Distans mellan stationer)
*/
#include "Database.h"

// L�ser in Train.txt
void Database::readTrainTXT()  
{
	//Om det gick att l�sa in t�g
	if (TrainObject.readFile(TrainVECTOR))
	{
		cout << "Trains have been loaded from Trains.txt \n \n \n" << endl;

	}
	else
	{
		cout << "Trains could not be loaded." << endl;
	}
}

// L�ser in Trainstations.txt
void Database::readTrainStationsTXT()
{
	if (StationObject.readTrainStationsTXT(StationVector))
	{
		cout << "Trainstations have been loaded" << endl;

	}
	else
	{
		cout << "Could not load Trainstations" << endl;
	}
}

// L�ser in Trainmap.txt
void Database::readTrainMapTXT()
{
	ifstream inFile("TrainMap.txt");
	string tempString;

	string station1;
	string station2;
	int distance;

	if (inFile.is_open())
	{
		while (true)
		{
			if (!(getline(inFile, tempString))) break;

			istringstream iss(tempString);

			iss >> station1 >> station2 >> distance;


			StationDistance[make_pair(station1, station2)] = distance;


		}

		inFile.close();
		cout << "TrainMap.txt has been loaded." << endl;
	}
	else
	{
		cout << "Trainmap could not be loaded." << endl;
	}


}