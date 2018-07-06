/* 2017-05-14
* Filnamn: Event.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Filen f�r att hantera event (skapa nya event m.m)
* Presenterar information n�r event skett inom intervall f�r anv�ndaren
*
*/

#include "Event.h"
#include "Simulation.h"

using namespace std;


// Trainstate 0 NOT ASSEMBLED  
void EVENT_NOT_ASSEMBLED::processEvent()
{
	Departure_Station->add_Train_to_station(Train_NOT_ASSEMBLED); // L�gger till t�get i dess avg�ngsstation
	bool found_cart = true;
	Train_NOT_ASSEMBLED->set_TRAINSTATE(NOTASSEMBLED); // S�tter t�gets status till not assembled
	
	if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om tiden �r inom intervallet, skriv ut information
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << Train_NOT_ASSEMBLED->getTrainNR() << " :: [Tries to assemble]"  <<
			" @ station " << Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;


		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(Train_NOT_ASSEMBLED->getTrainNR()) + " :: [Tries to assemble]" + // Skapar str�ng f�r loggning
			" @ station " + Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata);  // skriver str�ngen till fil
	}
	
	
	// F�rs�k s�tta ihop hela t�get via intar fr�n Carts needed.
	for (auto cartneeded : Train_NOT_ASSEMBLED->get_Train_Info_CARTSNEEDED())
	{
		
		// Kollar om efters�kt fordon fanns tillg�ngligt p� stationen och bygger ihop i s�dana fall  Skickar �ven med extra data f�r loggning av fordonhistorik.
		if (!(Departure_Station->cart_add_to_train(cartneeded, Train_NOT_ASSEMBLED, SimObjekt->print_MinutesToCLOCK_Format(getTime()))))
		{
			found_cart = false;
		}
	}
	

	// Om alla fordon hittats
	if (found_cart == true)
	{
		// OM t�get �r komplett  Ska det skapas ett nytt event f�r t�get som heter ASSEMBLED
		shared_ptr<Event> e(new EVENT_ASSEMBLED(SimObjekt, Train_NOT_ASSEMBLED, Train_NOT_ASSEMBLED->get_Train_Info_Time_DEPARTURE()));
		SimObjekt->scheduleEvent(e);
	}


	else
	{
		// OM t�get INTE �r komplett s�tt det till incomplete
		Train_NOT_ASSEMBLED->set_TRAINSTATE(INCOMPLETE);
		

		if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om tiden �r inom intervallet, skriv ut information och skriv till fil
		{
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << Train_NOT_ASSEMBLED->getTrainNR() << " ::: [INCOMPLETE]" <<
				" @ station " << Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION() << endl;
			cout << "-------------------------------------------------------------------------------" << endl;

			string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(Train_NOT_ASSEMBLED->getTrainNR()) + " ::: [INCOMPLETE]" + // Skapar str�ng f�r loggning
				" @ station " + Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION();

			SimObjekt->write_to_file(logdata);  // skriver str�ngen till fil
		}

	}
	
}

// Trainstate 2 ASSEMBLED
void EVENT_ASSEMBLED::processEvent()
{

	Train_IN_ASSEMBLE->set_TRAINSTATE(ASSEMBLED);  // S�tter state till assembled

	if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om  tiden �r inom intervallet, skriv ut info och logga till fil
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << Train_IN_ASSEMBLE->getTrainNR() << " ::: [ASSEMBLED]" <<
			" :: @ station " << Train_IN_ASSEMBLE->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(Train_IN_ASSEMBLE->getTrainNR()) + " ::: [ASSEMBLED]" + // skapa str�ng med logdata
			" :: @ station " + Train_IN_ASSEMBLE->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata);  // skriv str�ngen till fil

	}


	shared_ptr<Event> e(new EVENT_READY(SimObjekt, Train_IN_ASSEMBLE, Train_IN_ASSEMBLE->get_Train_Info_Time_DEPARTURE()));  // Skapar nytt event 
	SimObjekt->scheduleEvent(e); // L�gger till i k�n
	
	
}




// Trainstate 3 READY 
void EVENT_READY::processEvent()
{

	TRAIN_IN_READY->set_TRAINSTATE(READY); // S�tter state till ready
	
	if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om tiden �r inom intervallet, skriv ut info och logga till fil
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_READY->getTrainNR() << " ::: [READY]" <<
			" :: @ station " << TRAIN_IN_READY->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_READY->getTrainNR()) + " ::: [READY]" + // Skapar str�ng med logdata
			" :: @ station " + TRAIN_IN_READY->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata); // skriver str�ng till fil
	}


	//SimObjekt->write_to_file(logdata);

	bool showInfo = true;
	if (getTime() + 10 > SimObjekt->get_Simulation_END_TIME())
	{
		showInfo = false;
	}

	shared_ptr<Event> e(new EVENT_RUNNING(SimObjekt, TRAIN_IN_READY, TRAIN_IN_READY->get_Train_Info_Time_DEPARTURE(), showInfo)); // skapar nytt event och l�gger till i k�n
	SimObjekt->scheduleEvent(e);
}


// Trainstate 4 RUNNING  
void EVENT_RUNNING::processEvent()
{
	TRAIN_IN_RUNNING->set_TRAINSTATE(RUNNING);  // S�tter state

	string Departurestationname = TRAIN_IN_RUNNING->get_Train_Info_Departure_STATION(); // Skapar str�ng med aktuellt t�gs avg�nsstation



	for (auto station : SimObjekt->get_get__DB_StationVec()) // Hittar r�tt station f�r att d� kunna ta bort t�get fr�n dess vector eftersom att t�get g�tt in i running.
	{
		if (Departurestationname == station->get_Station_Info_StationName()) // Hittar r�tt station
		{
			station->remove_Train_from_station(TRAIN_IN_RUNNING); // Tar bort stationen
		}
	}


	if (SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME() && showInfo)  // Om tiden ligger efter eller p� starttiden f�r intervallet och blev running innan intervallets slut, skriv ut info och logga
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_RUNNING->getTrainNR() << " ::: [RUNNING]" <<
			" :: from station " << TRAIN_IN_RUNNING->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_RUNNING->getTrainNR()) + " ::: [RUNNING]" + // Skapa str�ng med logdata
			" :: from station " + TRAIN_IN_RUNNING->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata); // Skriv str�ng till fil
	}


	shared_ptr<Event> e(new EVENT_ARRIVED(SimObjekt, TRAIN_IN_RUNNING, TRAIN_IN_RUNNING->get_Train_Info_Time_ARRIVAL(), showInfo));  // Skapar nytt event och l�gger till i k�n
	SimObjekt->scheduleEvent(e);

}

// Trainstate 5 ARRIVED
void EVENT_ARRIVED::processEvent()
{
	TRAIN_IN_ARRIVED->set_TRAINSTATE(ARRIVED);  // S�tter state


	if (SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME() && showInfo)   // Om tiden ligger efter eller p� starttiden f�r intervallet och blev running innan intervallets slut, skriv ut info och logga
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_ARRIVED->getTrainNR() << " ::: [ARRIVED]" <<
			" :: @ station " << TRAIN_IN_ARRIVED->get_Train_Info_Arrival_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_ARRIVED->getTrainNR()) + " ::: [ARRIVED]" +  // Skapar str�ng med loggdata
			" :: @ station " + TRAIN_IN_ARRIVED->get_Train_Info_Arrival_STATION();

		SimObjekt->write_to_file(logdata); //  Skriver str�ng till fil
	}



	string Arrivalstationname = TRAIN_IN_ARRIVED->get_Train_Info_Arrival_STATION();  // Skapar str�ng med ankomsstationens namn

	for (auto station : SimObjekt->get_get__DB_StationVec())  // Hittar r�tt station f�r att d� kunna l�gga till t�g i ankomststationens vector eftersom att det ankommit.
	{
		if (Arrivalstationname == station->get_Station_Info_StationName()) // Hittar r�tt station
		{
			station->add_Train_to_station(TRAIN_IN_ARRIVED); // L�gger till t�g i station
		}
	}



	shared_ptr<Event> e(new EVENT_FINISHED(SimObjekt, TRAIN_IN_ARRIVED, TRAIN_IN_ARRIVED->get_Train_Info_Time_ARRIVAL(), showInfo)); // Skapar nytt event och l�gger till i k�n
	SimObjekt->scheduleEvent(e);

}

// Trainstate 6 FINISHED 
void EVENT_FINISHED::processEvent()
{
	TRAIN_IN_FINISHED->set_TRAINSTATE(FINISHED); // S�tter state

	if (SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME() && showInfo)  // Om tiden ligger efter eller p� starttiden f�r intervallet och blev running innan intervallets slut, skriv ut info och logga
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_FINISHED->getTrainNR() << " ::: [FINISHED]" <<
			" :: @ station " << TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_FINISHED->getTrainNR()) + " ::: [FINISHED]" + // Skapar str�ng med logdata
			" :: @ station " + TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION();

		SimObjekt->write_to_file(logdata); // Skriver str�ngen till fil
	}



	string Arrivalstation = TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION(); // Skapar str�ng med ankomsstationens namn

	for (auto station : SimObjekt->get_get__DB_StationVec()) // Loopar igenom alla stationer
	{
		if (Arrivalstation == station->get_Station_Info_StationName()) // Om stationsnamn st�mmer med ankomsstation
		{

			station->cart_dismantle_at_station(TRAIN_IN_FINISHED, SimObjekt->print_MinutesToCLOCK_Format(getTime())); // Ta bort fordon fr�n t�g och logga historik f�r fordon

		}
	}

	for (auto station : SimObjekt->get_get__DB_StationVec())          // Tar bort t�g fr�n stationsvector eftersom det blivit dismantlat och existerar inte l�ngre
	{
		if (TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION() == station->get_Station_Info_StationName()) // Hittar r�tt station
		{
			station->remove_Train_from_station(TRAIN_IN_FINISHED); // Tar bort t�g fr�n stationen eftersom det �r finished (dismantlat)
		}
	}
	
}
