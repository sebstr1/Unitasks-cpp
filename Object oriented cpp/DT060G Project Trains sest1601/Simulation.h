/* 2017-05-14
* Filnamn: Simulation.h
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* Definerar klassen Simulation.
*/


#ifndef SimulationH
#define SimulationH

#include "Train.h"
#include "TrainStations.h"
#include "Fordon.h"
#include "Event.h"
#include "Database.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>



class Simulation {
private:

	
	unsigned int time_simulation = 0;       // simulation Time

	unsigned int time_simulationInterval = 10; // Simulation interval

	unsigned int time_SimulationSTART = 0;   // Simulation start

	unsigned int time_SimulationEND = 1439;  // end

	bool exit = false; // om användaren valt exit direkt

	bool finished = false; // När simuleringen är klar

	int input; // input


	// LOGG / DATA STATIstik
	string Log_level = "low";
	vector<int> Carts_at_start; // Lagrar hur många fordon som finns på varje station från start 
	

	priority_queue<shared_ptr<Event>, vector<shared_ptr<Event>>, EventTimeComparison> eventQueue; // Eventkön som alltid är sortered med den minsta (tidigaste eventet först i kön)

	Database db; // obj

	

public:

	Simulation() : time_simulation(), eventQueue() { time_simulation = 0; } // Konstruktor

	void scheduleEvent(shared_ptr<Event> newEvent) { eventQueue.push(newEvent); } // Lägger till event i eventkö

	void add_StartingEvents(); // Lägger till dom första 130 eventen för alla 130 tåg

	void run(); // Kör igång programmet
	
	void change_Log_level(); // Ändrar lognivå
	void print_statistics(); // Skriver ut statistik efter simuleringen
	void write_to_file(string logdata); // Skriver sträng till fil
	
	void show_StartMenu(); // Visar startmeny
	void show_SimulationMenu(); // Visar simuleringsmeny
//-----------------------------------------
	void show_TrainMenu();	// Visar tågmeny
	void print_TrainTimeTable(); // Skriver ut tidtabell
	void find_train_info(); // Hittar specifikt tågnr och skriver ut info
	void print_train_info(shared_ptr<Train> train); // Skriver ut info om tåg
//-----------------------------------------
	void show_StationMenu(); // visar stationsmeny
	void find_station_names(); // Skriver ut stationsnamnen
	void find_station_Info(); // Hittar info om specifik station

//-----------------------------------------
	void show_CartMenu();  // Fordonsmenyn
	void show_all_carts(); // SKriver ut info om alla fordon
	void find_cart();     // Specifikt fordonsid
	void print_CartInfo(shared_ptr<Train_Cart> cart); // Skriver ut info om fordon

//------------------------------------------
	void show_Simulator_Finished_Menu(); // Meny för slut på simuleringen

	int get_MenuChoice();  // kontrollerar och returnerar användarinput

	string get_loglevel() const { return Log_level; } // returnerar log-nivå (high / low )

	vector<shared_ptr<Trainstation>> get_get__DB_StationVec() { return db.get_DB_StationVec(); } // Returnerar stationsvectorn från databas

	// Funktioner för tid och intervaller
	void change_time_for_START_END_or_INTERVAL(string task);
	void next_interval_event(string next);
	
	unsigned int get_SimulationTime() const { return time_simulation; }	
	unsigned int get_Simulation_END_TIME() const { return time_SimulationEND; }
	unsigned int get_Simulation_START_TIME() const { return time_SimulationSTART; }

	string print_MinutesToCLOCK_Format (unsigned int minutes);  // tar input i minuter och returnerar en sträng i klockformat

	int get_StationsDistance(string station1, string station2); // Hämtar stationsdistans
	
	//Helpers
	string myTolowerfunction(string str) { transform(str.begin(), str.end(), str.begin(), tolower); return str; }//[](unsigned char c) { return std::tolower(c); });
	

};

#endif

