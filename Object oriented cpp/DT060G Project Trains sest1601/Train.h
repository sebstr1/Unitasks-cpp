/* 2017-05-14
* Filnamn: Train.h
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* Definerar klassen Train
*/

#ifndef CrazyTrainH
#define CrazyTrainH

#include "Fordon.h"
#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;


enum States { NOTASSEMBLED, INCOMPLETE, ASSEMBLED, READY, RUNNING, ARRIVED, FINISHED }; // Tågstate

// Tåg som innehåller info nedan
class Train {
private:
	int trainNR = 0; // Tågnr
	string startStation; // Avgångsstation
	string endStation; // Ankomststation
	int time_start_time_minutes; // avgångstid
	int time_end_time_minutes; // ankomsttid
	int maxSpeed; // Maxspeed
	vector<int> Carts_Needed_VECTOR; // Fordon som tåget behöver
	vector<shared_ptr<Train_Cart>> Carts_In_Train_Vector; // Fordon som tåget har just nu
	vector<string> Statebytext{ "NOTASSEMBLED", "INCOMPLETE", "ASSEMBLED", "READY", "RUNNING", "ARRIVED", "FINISHED" }; // state i text
	States TrainState; // state

public:
	Train() {}
	~Train() {}
	Train(int trainid, string startstation, string endstation, int starttime, int endtime, int maxspeed, vector<int> type, vector<shared_ptr<Train_Cart>> Trainvec)
	{
		trainNR = trainid;
		startStation = startstation;
		endStation = endstation;
		time_start_time_minutes = starttime;
		time_end_time_minutes = endtime;
		maxSpeed = maxspeed;
		Carts_Needed_VECTOR = type;
		Carts_In_Train_Vector = Trainvec;
		TrainState = NOTASSEMBLED;
	}

	
	// Set
	void set_TRAINSTATE(States setstate) { TrainState = setstate; }											// Sätter state på tåget
	bool add_cart_to_trainVECTOR(shared_ptr<Train_Cart> cart, string time);									// Lägger till fordon till tågvector
	bool remove_cart_from_needed_carts(int needed);															// Tar bort fordon från tågets behövda fordon
	bool remove_cart_from_trainVector(shared_ptr<Train_Cart> cart, shared_ptr<Train> train, string time);   // Tar bort fordon från tågvector
	bool readFile(vector<shared_ptr<Train>> &crayTrainVec);													// Läser in tåg från fil

	
	// Getters
	int getTrainNR() { return trainNR; }																	// Returnerar tågnr
	string get_Train_Info_Departure_STATION() const { return startStation; }								// Returnerar Avgångsstation
	string get_Train_Info_Arrival_STATION() const { return endStation; }									// Returnerar Slutstation
	int get_Train_Info_Time_DEPARTURE() const { return time_start_time_minutes; }							// Returnerar avgångstid
	int get_Train_Info_Time_ARRIVAL() const { return time_end_time_minutes; }								// Returnerar ankomsttid
	int get_Train_Info_MAXSPEED() const { return maxSpeed; }												// Returnerar max hastighet
	vector<int> get_Train_Info_CARTSNEEDED() const { return Carts_Needed_VECTOR; }							// Returnerar fordon som tåget behöver (int för typ av fordon)
	vector<shared_ptr<Train_Cart>>& get_Carts_in_Train_VEC() { return Carts_In_Train_Vector; }				// Returnerar vector med fordon i tåget
	vector<string> get_TrainStateintext() const { return Statebytext; }										// Returnerar fordons state fast i text
	States get_Train_Info_STATE() const { return TrainState; }												// Returnerar fordonets state i enum.


	
	
	


	

	
	
	
};



#endif

