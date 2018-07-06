/* 2017-05-14
* Filnamn: Event.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Filen för att hantera event (skapa nya event m.m)
* Presenterar information när event skett inom intervall för användaren
*
*/

#include "Event.h"
#include "Simulation.h"

using namespace std;


// Trainstate 0 NOT ASSEMBLED  
void EVENT_NOT_ASSEMBLED::processEvent()
{
	Departure_Station->add_Train_to_station(Train_NOT_ASSEMBLED); // Lägger till tåget i dess avgångsstation
	bool found_cart = true;
	Train_NOT_ASSEMBLED->set_TRAINSTATE(NOTASSEMBLED); // Sätter tågets status till not assembled
	
	if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om tiden är inom intervallet, skriv ut information
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << Train_NOT_ASSEMBLED->getTrainNR() << " :: [Tries to assemble]"  <<
			" @ station " << Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;


		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(Train_NOT_ASSEMBLED->getTrainNR()) + " :: [Tries to assemble]" + // Skapar sträng för loggning
			" @ station " + Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata);  // skriver strängen till fil
	}
	
	
	// Försök sätta ihop hela tåget via intar från Carts needed.
	for (auto cartneeded : Train_NOT_ASSEMBLED->get_Train_Info_CARTSNEEDED())
	{
		
		// Kollar om eftersökt fordon fanns tillgängligt på stationen och bygger ihop i sådana fall  Skickar även med extra data för loggning av fordonhistorik.
		if (!(Departure_Station->cart_add_to_train(cartneeded, Train_NOT_ASSEMBLED, SimObjekt->print_MinutesToCLOCK_Format(getTime()))))
		{
			found_cart = false;
		}
	}
	

	// Om alla fordon hittats
	if (found_cart == true)
	{
		// OM tåget är komplett  Ska det skapas ett nytt event för tåget som heter ASSEMBLED
		shared_ptr<Event> e(new EVENT_ASSEMBLED(SimObjekt, Train_NOT_ASSEMBLED, Train_NOT_ASSEMBLED->get_Train_Info_Time_DEPARTURE()));
		SimObjekt->scheduleEvent(e);
	}


	else
	{
		// OM tåget INTE är komplett sätt det till incomplete
		Train_NOT_ASSEMBLED->set_TRAINSTATE(INCOMPLETE);
		

		if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om tiden är inom intervallet, skriv ut information och skriv till fil
		{
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << Train_NOT_ASSEMBLED->getTrainNR() << " ::: [INCOMPLETE]" <<
				" @ station " << Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION() << endl;
			cout << "-------------------------------------------------------------------------------" << endl;

			string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(Train_NOT_ASSEMBLED->getTrainNR()) + " ::: [INCOMPLETE]" + // Skapar sträng för loggning
				" @ station " + Train_NOT_ASSEMBLED->get_Train_Info_Departure_STATION();

			SimObjekt->write_to_file(logdata);  // skriver strängen till fil
		}

	}
	
}

// Trainstate 2 ASSEMBLED
void EVENT_ASSEMBLED::processEvent()
{

	Train_IN_ASSEMBLE->set_TRAINSTATE(ASSEMBLED);  // Sätter state till assembled

	if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om  tiden är inom intervallet, skriv ut info och logga till fil
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << Train_IN_ASSEMBLE->getTrainNR() << " ::: [ASSEMBLED]" <<
			" :: @ station " << Train_IN_ASSEMBLE->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(Train_IN_ASSEMBLE->getTrainNR()) + " ::: [ASSEMBLED]" + // skapa sträng med logdata
			" :: @ station " + Train_IN_ASSEMBLE->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata);  // skriv strängen till fil

	}


	shared_ptr<Event> e(new EVENT_READY(SimObjekt, Train_IN_ASSEMBLE, Train_IN_ASSEMBLE->get_Train_Info_Time_DEPARTURE()));  // Skapar nytt event 
	SimObjekt->scheduleEvent(e); // Lägger till i kön
	
	
}




// Trainstate 3 READY 
void EVENT_READY::processEvent()
{

	TRAIN_IN_READY->set_TRAINSTATE(READY); // Sätter state till ready
	
	if (SimObjekt->get_SimulationTime() <= SimObjekt->get_Simulation_END_TIME() && SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME()) // Om tiden är inom intervallet, skriv ut info och logga till fil
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_READY->getTrainNR() << " ::: [READY]" <<
			" :: @ station " << TRAIN_IN_READY->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_READY->getTrainNR()) + " ::: [READY]" + // Skapar sträng med logdata
			" :: @ station " + TRAIN_IN_READY->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata); // skriver sträng till fil
	}


	//SimObjekt->write_to_file(logdata);

	bool showInfo = true;
	if (getTime() + 10 > SimObjekt->get_Simulation_END_TIME())
	{
		showInfo = false;
	}

	shared_ptr<Event> e(new EVENT_RUNNING(SimObjekt, TRAIN_IN_READY, TRAIN_IN_READY->get_Train_Info_Time_DEPARTURE(), showInfo)); // skapar nytt event och lägger till i kön
	SimObjekt->scheduleEvent(e);
}


// Trainstate 4 RUNNING  
void EVENT_RUNNING::processEvent()
{
	TRAIN_IN_RUNNING->set_TRAINSTATE(RUNNING);  // Sätter state

	string Departurestationname = TRAIN_IN_RUNNING->get_Train_Info_Departure_STATION(); // Skapar sträng med aktuellt tågs avgånsstation



	for (auto station : SimObjekt->get_get__DB_StationVec()) // Hittar rätt station för att då kunna ta bort tåget från dess vector eftersom att tåget gått in i running.
	{
		if (Departurestationname == station->get_Station_Info_StationName()) // Hittar rätt station
		{
			station->remove_Train_from_station(TRAIN_IN_RUNNING); // Tar bort stationen
		}
	}


	if (SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME() && showInfo)  // Om tiden ligger efter eller på starttiden för intervallet och blev running innan intervallets slut, skriv ut info och logga
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_RUNNING->getTrainNR() << " ::: [RUNNING]" <<
			" :: from station " << TRAIN_IN_RUNNING->get_Train_Info_Departure_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_RUNNING->getTrainNR()) + " ::: [RUNNING]" + // Skapa sträng med logdata
			" :: from station " + TRAIN_IN_RUNNING->get_Train_Info_Departure_STATION();

		SimObjekt->write_to_file(logdata); // Skriv sträng till fil
	}


	shared_ptr<Event> e(new EVENT_ARRIVED(SimObjekt, TRAIN_IN_RUNNING, TRAIN_IN_RUNNING->get_Train_Info_Time_ARRIVAL(), showInfo));  // Skapar nytt event och lägger till i kön
	SimObjekt->scheduleEvent(e);

}

// Trainstate 5 ARRIVED
void EVENT_ARRIVED::processEvent()
{
	TRAIN_IN_ARRIVED->set_TRAINSTATE(ARRIVED);  // Sätter state


	if (SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME() && showInfo)   // Om tiden ligger efter eller på starttiden för intervallet och blev running innan intervallets slut, skriv ut info och logga
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_ARRIVED->getTrainNR() << " ::: [ARRIVED]" <<
			" :: @ station " << TRAIN_IN_ARRIVED->get_Train_Info_Arrival_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_ARRIVED->getTrainNR()) + " ::: [ARRIVED]" +  // Skapar sträng med loggdata
			" :: @ station " + TRAIN_IN_ARRIVED->get_Train_Info_Arrival_STATION();

		SimObjekt->write_to_file(logdata); //  Skriver sträng till fil
	}



	string Arrivalstationname = TRAIN_IN_ARRIVED->get_Train_Info_Arrival_STATION();  // Skapar sträng med ankomsstationens namn

	for (auto station : SimObjekt->get_get__DB_StationVec())  // Hittar rätt station för att då kunna lägga till tåg i ankomststationens vector eftersom att det ankommit.
	{
		if (Arrivalstationname == station->get_Station_Info_StationName()) // Hittar rätt station
		{
			station->add_Train_to_station(TRAIN_IN_ARRIVED); // Lägger till tåg i station
		}
	}



	shared_ptr<Event> e(new EVENT_FINISHED(SimObjekt, TRAIN_IN_ARRIVED, TRAIN_IN_ARRIVED->get_Train_Info_Time_ARRIVAL(), showInfo)); // Skapar nytt event och lägger till i kön
	SimObjekt->scheduleEvent(e);

}

// Trainstate 6 FINISHED 
void EVENT_FINISHED::processEvent()
{
	TRAIN_IN_FINISHED->set_TRAINSTATE(FINISHED); // Sätter state

	if (SimObjekt->get_SimulationTime() >= SimObjekt->get_Simulation_START_TIME() && showInfo)  // Om tiden ligger efter eller på starttiden för intervallet och blev running innan intervallets slut, skriv ut info och logga
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "[" << SimObjekt->print_MinutesToCLOCK_Format(getTime()) << "]" << " Train_NR " << TRAIN_IN_FINISHED->getTrainNR() << " ::: [FINISHED]" <<
			" :: @ station " << TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION() << endl;
		cout << "-------------------------------------------------------------------------------" << endl;

		string logdata = "[" + SimObjekt->print_MinutesToCLOCK_Format(getTime()) + "]" + " Train_NR " + to_string(TRAIN_IN_FINISHED->getTrainNR()) + " ::: [FINISHED]" + // Skapar sträng med logdata
			" :: @ station " + TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION();

		SimObjekt->write_to_file(logdata); // Skriver strängen till fil
	}



	string Arrivalstation = TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION(); // Skapar sträng med ankomsstationens namn

	for (auto station : SimObjekt->get_get__DB_StationVec()) // Loopar igenom alla stationer
	{
		if (Arrivalstation == station->get_Station_Info_StationName()) // Om stationsnamn stämmer med ankomsstation
		{

			station->cart_dismantle_at_station(TRAIN_IN_FINISHED, SimObjekt->print_MinutesToCLOCK_Format(getTime())); // Ta bort fordon från tåg och logga historik för fordon

		}
	}

	for (auto station : SimObjekt->get_get__DB_StationVec())          // Tar bort tåg från stationsvector eftersom det blivit dismantlat och existerar inte längre
	{
		if (TRAIN_IN_FINISHED->get_Train_Info_Arrival_STATION() == station->get_Station_Info_StationName()) // Hittar rätt station
		{
			station->remove_Train_from_station(TRAIN_IN_FINISHED); // Tar bort tåg från stationen eftersom det är finished (dismantlat)
		}
	}
	
}
