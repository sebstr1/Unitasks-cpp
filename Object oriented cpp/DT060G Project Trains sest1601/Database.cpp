/* 2017-05-14
* Filnamn: Database.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Filen används för att att läsa in information från filer, lagra och serva
* informationen till klasser som frågar efter den (Tåg, Tågstationer och Distans mellan stationer)
*/
#include "Database.h"

// Läser in Train.txt
void Database::readTrainTXT()  
{
	//Om det gick att läsa in tåg
	if (TrainObject.readFile(TrainVECTOR))
	{
		cout << "Trains have been loaded from Trains.txt \n \n \n" << endl;

	}
	else
	{
		cout << "Trains could not be loaded." << endl;
	}
}

// Läser in Trainstations.txt
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

// Läser in Trainmap.txt
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