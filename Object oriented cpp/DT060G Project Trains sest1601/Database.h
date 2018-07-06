/* 2017-05-14
* Filnamn: Database.h
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* Definerar klassen Database som lagrar vectorer med data om tåg, stationer mm.
*/
#ifndef DatabaseH
#define DataBaseH

#include "Train.h"
#include "TrainStations.h"
#include <string>
#include <vector>
#include <map>
#include <memory>



class Database {
private:
//---------------------Vectorer-----------------------------
	// Trains to build                                    //
	Train TrainObject;									  //
	vector<shared_ptr<Train>> TrainVECTOR;				  //						  
														  //
 // Stations										      //
	Trainstation StationObject;							  //
	vector<shared_ptr<Trainstation>> StationVector;		  //
	
 // TrainMap											  //
	map<pair<string, string>, int> StationDistance;       //
 //----------------------------------------------------------


public:

	//Trains
	void readTrainTXT();
	vector<shared_ptr<Train>> get_DB_TrainVec()& { return TrainVECTOR; }


	//Stations
	void readTrainStationsTXT();
	vector<shared_ptr<Trainstation>> get_DB_StationVec()& { return StationVector; }


	//Trainmap
	void readTrainMapTXT();
	
	map<pair<string, string>, int> get_DB_Distance() { return StationDistance; }

};

#endif

