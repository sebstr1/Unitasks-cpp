/* 2017-05-14
* Filnamn: TrainStations.h
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* Definerar klassen Trainstation
*/


#ifndef TrainStationsH
#define TrainStationsH

#include "Fordon.h"
#include "Train.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;


class Trainstation {
private:
	string StationName;
	vector<shared_ptr<Train_Cart>> Carts_in_station_vector; // Fordon i stationens pool
	vector<shared_ptr<Train>> Trains_in_station_vector;  // T�g p� stationen just nu

public:
	Trainstation() {}
    Trainstation(string stationname, vector<shared_ptr<Train_Cart>> stationsfordon) { StationName = stationname, Carts_in_station_vector = stationsfordon; }     // Konstruktor
	~Trainstation() {}  // Destruktor


	//Funktioner
	bool readTrainStationsTXT(vector<shared_ptr<Trainstation>> &stationVec);											// L�ser in stationer fr�n fil
	bool cart_add_to_train(int type, shared_ptr<Train> train, string time);												// Funktion som tar fordon fr�n stationens pool och l�gger till i ett t�g.
	bool cart_dismantle_at_station(shared_ptr<Train> train, string time);												// Funktion som tar fordon fr�n t�g och l�gger till i stationens pool.
	bool add_Train_to_station(shared_ptr<Train> train) { Trains_in_station_vector.push_back(train); return true; }		// Funktion som l�gger till t�g i station
	bool remove_Train_from_station(shared_ptr<Train> train);															// Funktion som tar bort t�g fr�n station
	
	string get_Station_Info_StationName() const { return StationName; }													// Returnerar Stations Namn
	vector<shared_ptr<Train_Cart>> get_Station_Info_StationCARTS() const { return Carts_in_station_vector; }			// Returnerar stations fordon (vector)
	vector<shared_ptr<Train>> get_Station_Info_StationTRAINS() const { return Trains_in_station_vector; }				// Returnerar stations t�g (vector)
	
	
};
//------------------------------------------------------------------------------------------------------
#endif