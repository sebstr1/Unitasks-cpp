/* 2017-05-14
* Filnamn: Simulation.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Filen anv�nds f�r att visa menyerna, kommunicera med Database.h, skapa dem f�rsta eventsen till k�n,
* kommunicera med anv�ndaren och presentera information och statistik
*
*/

#include "Simulation.h"

using namespace std;


//H�r k�rs programmet ig�ng 
void Simulation::run()
{
	//L�ser in filerna.
	db.readTrainMapTXT();   
	db.readTrainStationsTXT();
	db.readTrainTXT();
	remove("Trainsim.log"); // Tar bort filen om den redan fanns s� att inte filen fylls p� vid varje k�rning


	
	for (auto station : db.get_DB_StationVec())
	{
		Carts_at_start.push_back(station->get_Station_Info_StationCARTS().size());  // Sparar statistik fr�n starten av simuleringen (Antalet vagnar p� varje station fr�n b�rjan)
	}
	
	add_StartingEvents();	//L�gger in f�rsta eventen i k�n baserat p� informationen fr�n readTrainTXT (Train.txt)

	
	
	show_StartMenu(); // Visar startmenyn

	if (!exit) // Om anv�ndaren inte valde exit i startmenyn
	{
		show_SimulationMenu(); // Visa simuleringsmenyn

		if (finished) // Om simuleringen �r finished
		{
			show_Simulator_Finished_Menu(); // N�r det �r slut p� events visas denna meny
			
		}
		
	}
	
	//cin.get();
}

//Do while switch-meny f�r startmenyn
void Simulation::show_StartMenu()
{
	bool again = true;

	do
	{
		cout << endl << endl << "===== StartMenu" << endl;
		cout << " 1. Change start time [" << print_MinutesToCLOCK_Format(time_SimulationSTART) << "]" << endl; //print_MinutesToCLOCK_Format(time_SimulationSTART); cout << "]" << endl;
		cout << " 2. Change end time [" << print_MinutesToCLOCK_Format(time_SimulationEND) << "]" << endl;// print_MinutesToCLOCK_Format(time_SimulationEND); cout << "]" << endl;
		cout << " 3. Start simulation" << endl;
		cout << " 4. Exit" << endl;
		
		switch (get_MenuChoice())
		{
		case 1: 
			change_time_for_START_END_or_INTERVAL("simulation start");
			break;
		case 2: 
			change_time_for_START_END_or_INTERVAL("simulation end");
			break;
		case 3: 
			return;//show_SimulationMenu();
			break;
		case 4: 
			again = false;
			exit = true;
			break;
		default: cout << endl << "Wrong choice...";
			cin.get();
		}
	} while (again == true);
}

//Do while switch-meny f�r Simuleringsmenyn     ------------------------------------ INTE KLAR
void Simulation::show_SimulationMenu()
{
	bool again = true;
	do
	{
		if (eventQueue.empty() || time_simulation > time_SimulationEND)   // ----------------------------------------------?????
		{
			finished = true;
			return;
		}


		cout << endl << "===== SimulationMenu =====  Simulation clock is: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << endl;
		if (!eventQueue.empty())
		{
			cout << " 1. Change interval [" << print_MinutesToCLOCK_Format(time_simulationInterval) << "]" << endl;
			cout << " 2. Run next interval" << endl;
			cout << " 3. Next event" << endl;
			cout << " 4. Finish" << endl;
			cout << " 5. Change log level [" << get_loglevel() << "]" << endl;
			cout << " 6. Train menu" << endl;
			cout << " 7. Station menu" << endl;
			cout << " 8. Cart menu" << endl;
		}
		
		cout << " 9. Return" << endl;

		switch (get_MenuChoice())
		{
		case 1: change_time_for_START_END_or_INTERVAL("interval");
			break;
		case 2: 
			next_interval_event("next_interval");
			break; 
		case 3:
			next_interval_event("next_event");
			break; 
		case 4:
			next_interval_event("finish");
			break;
		case 5:
			change_Log_level();
			break;
		case 6:
			show_TrainMenu();
			break;
		case 7:
			show_StationMenu();
			break;
		case 8:
			show_CartMenu();
			break;
		case 9:
			again = false; // Quit
			show_StartMenu();
			break;
		default: cout << endl << "Wrong choice...";
			cin.get();
		}
	} while (again == true);
}

//Do while switch-meny f�r t�gmenyn
void Simulation::show_TrainMenu()
{
	bool again = true;
	do
	{
		cout << endl << "===== Train Menu =====  Simulation clock is: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << endl;
		cout << "1. Print train schedule" << endl;
		cout << "2. Search train by number" << endl;
		cout << "3. Change log level [" << get_loglevel() << "]" << endl;
		cout << "4. Return" << endl;
	
		switch (get_MenuChoice())
		{
		case 1:
			print_TrainTimeTable();
			break;
		case 2:
			find_train_info();
			break;
		case 3:
			change_Log_level();
			break;
		case 4:
			again = false; // Quit
			break;
		default:
			cout << endl << "Wrong choice...";
			cin.get();
		}

	} while (again == true);
}

// Skriver ut tidtabellen f�r t�g
void Simulation::print_TrainTimeTable()
{
	int printCounter = 1;

	cout << endl << "---------------------------------------------------------------------------------" << endl;
	for (auto train : db.get_DB_TrainVec())
	{
		cout << "Train[" << train->getTrainNR() << "] From: "
			<< train->get_Train_Info_Departure_STATION() << " To: "
			<< train->get_Train_Info_Arrival_STATION() << endl;
		cout << "Departure time: "
			<< print_MinutesToCLOCK_Format(train->get_Train_Info_Time_DEPARTURE()) << " Arrival time: "
			<< print_MinutesToCLOCK_Format(train->get_Train_Info_Time_ARRIVAL()) << endl;
		cout << "---------------------------------------------------------------------------------" << endl;

		if (printCounter % 70 == 0)                                                                            //Om 70 rader skrivits  ut
		{
			cout << endl << "Press a key to show more of the timetable...";
			cin.get();
			cout << endl << "---------------------------------------------------------------------------------" << endl;
		}

		printCounter++;
	}
}

// S�ker efter ett t�g och skriver ut info om t�get fanns  ------------------------------------- T�g som borde finnas p� station skivs inte ut
void Simulation::find_train_info()
{
	cout << "\n \n";
	cout << "Search for train with nr: ";
	int find_trainNR;
	bool hit = false;
	find_trainNR = get_MenuChoice(); // Felkontroll
	

	for (auto train : db.get_DB_TrainVec())         // G� igenom alla t�g
	{
		if (find_trainNR == train->getTrainNR())   // Om r�tt t�g hittats
		{
			hit = true;	// Hittade t�g
			print_train_info(train); // Skriv ut t�ginfo

		}
	}

	if (!(hit)) // om t�g inte hittats
	{
		cout << "Train does not exist OR have been dismantled.." << endl;
	}

}

//Skriver ut information om ett t�g
void Simulation::print_train_info(shared_ptr<Train> train)
{
	cout << endl << endl;
	cout << "---- Train nr: <" << train->getTrainNR() << "> ----" << endl;
	cout << "State: " << train->get_TrainStateintext()[train->get_Train_Info_STATE()] << endl;
	cout << "Top speed: " << train->get_Train_Info_MAXSPEED() << "km/h" << endl;
	
	if (train->get_Train_Info_STATE() == RUNNING) // Om t�get �r running skriv ut dess medelhastighet
	{
		double avgSpeed = get_StationsDistance(train->get_Train_Info_Departure_STATION(), train->get_Train_Info_Arrival_STATION()) * 60.0 / (train->get_Train_Info_Time_ARRIVAL() - train->get_Train_Info_Time_DEPARTURE()); // R�knar ut medelhastighet
		cout << "Average speed: "  << setprecision(2) << fixed << avgSpeed	<< "km/h" << endl;
	} 
	cout << "Departure at [" << print_MinutesToCLOCK_Format(train->get_Train_Info_Time_DEPARTURE()) << "] from " << train->get_Train_Info_Departure_STATION() << endl;
	cout << "Arrives [" << print_MinutesToCLOCK_Format(train->get_Train_Info_Time_ARRIVAL()) << "] at " << train->get_Train_Info_Arrival_STATION() << endl << endl;
		
	cout << "Nr of carts in train: " << train->get_Carts_in_Train_VEC().size() << endl;

	cout << "-------------------------------------------------------------------------------" << endl;

	for (auto cart : train->get_Carts_in_Train_VEC())
	{
		print_CartInfo(cart);
	}
	

}

//Do while switch-meny f�r stationsmenyn
void Simulation::show_StationMenu()
{
	bool again = true;
	do
	{
		cout << endl << "===== Station Menu =====  Simulation clock is: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << endl;
		cout << "1. Show all station names" << endl;
		cout << "2. Show station by name" << endl;
		cout << "3. Change log level [" << get_loglevel() << "]" << endl;
		cout << "4. Return" << endl;

		switch (get_MenuChoice())
		{
		case 1:
			find_station_names();
			break;
		case 2:
			find_station_Info();
			break;
		case 3:
			change_Log_level();
			break;
		case 4:
			again = false; // Quit
			break;
		default:
			cout << endl << "Wrong choice...";
			cin.get();
		}

	} while (again == true);
}

//Skriver bara ut namnen p� alla stationer
void Simulation::find_station_names()
{
	cout << "Available stations: " << endl;
	for (auto station : db.get_DB_StationVec())
	{
		cout << station->get_Station_Info_StationName() << endl;
	}
}

// Tar en str�ng som input, k�r felkontroll p� str�ngen, s�ker igenom alla stationer
// efter en station med samma namn som anv�ndaren gav i input och skriver i s�dana fall 
// ut information om stationen.
void Simulation::find_station_Info()
{
	string stationname;

	cout << "Enter station name: ";
	getline(cin, stationname);          
	
	try
	{
		size_t found = stationname.find_first_not_of("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ"); // Kollar om str�ngen inneh�ller annat �n A-z och whitespace.
		if (found != std::string::npos)
		{
			throw invalid_argument("Station names does only contain A-z and whitespace.");                     // Throwar
		}

		

		cout << endl;
		bool hit = false;
		for (auto station : db.get_DB_StationVec())   // Loopar igenom alla stationer
		{
			if (myTolowerfunction(stationname) == myTolowerfunction(station->get_Station_Info_StationName())) // Letar specifik station
			{
				hit = true; // Station was found	
				cout << "Information about station '" << station->get_Station_Info_StationName() << "'" << endl;  
				for (auto train : station->get_Station_Info_StationTRAINS())								// Loopar igenom alla t�g som finns p� stationen
				{
					print_train_info(train);																// Skriver ut info om potentiella t�g beroende p� LogLevel
				
				}
				cout << endl << "Available Carts: (" << station->get_Station_Info_StationCARTS().size() << ")" << endl;

				for (auto cart : station->get_Station_Info_StationCARTS())                                  // Loopar igenom stationens fordonspool
				{

					print_CartInfo(cart);						// Skriver ut info beroende p� logLevel

				}
			}
		}
		if (!(hit)) // if station not found
		{
			cout << "'" << stationname << "' does not exist." << endl;
		}
	}
	catch (invalid_argument &ia)                        // F�ngar exception
	{
		cerr << endl << ia.what() << endl;
	}
}


//Do while switch-meny f�r fordonsmenyn
void Simulation::show_CartMenu()
{
	bool again = true;
	do
	{
		cout << endl << "===== Cart Menu =====  Simulation clock is: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << endl;
		cout << "1. Show cart by id" << endl;
		cout << "2. Show all carts" << endl;
		cout << "3. Change log level [" << get_loglevel() << "]" << endl;
		cout << "4. Return" << endl;

		switch (get_MenuChoice())
		{
		case 1:
			find_cart();
			break;
		case 2:
			show_all_carts();
			break;
		case 3:
			change_Log_level();
			break;
		case 4:
			again = false;
			show_Simulator_Finished_Menu();
			break;
		default:
			cout << endl << "Wrong choice...";
			cin.get();
		}

	} while (again == true);
}

// Skriver ut information om alla fordon beroende p� log-level
void Simulation::show_all_carts()
{
	for (auto station : db.get_DB_StationVec()) // Loopar alla stationer
	{
		cout << "At station " << station->get_Station_Info_StationName() << ": " << endl;
		for (auto cart : station->get_Station_Info_StationCARTS()) // Loopar igenom alla fordon i station
		{
			print_CartInfo(cart); // skriver ut info beroende p� log-level
		}
		cout << "--------------------" << endl;
	}

	for (auto train : db.get_DB_TrainVec()) // Loopar igenom alla t�g
	{
		if (train->get_Carts_in_Train_VEC().size() >= 1)
		{
			cout << "Carts in train nr " << train->getTrainNR() << ": " << endl;
			for (auto cart : train->get_Carts_in_Train_VEC()) // Loopar alla fordon i t�g
			{
				print_CartInfo(cart); // skriver ut info beroende p� loglevel
			}
			cout << "--------------------" << endl;
		}
	}

}

// S�ker igenom f�rst alla stationer efter angivet fordons ID, om inget resultat, s�k igenom alla t�g.
void Simulation::find_cart()
{
	int find_ID;
	bool found = false;
	cout << endl << endl;
	cout << "Find cart by id" << endl;
	cout << "Input ID: ";
	find_ID = get_MenuChoice(); // Felkontroll

//---------------------------------------------------------------------------------------------------------------------------------------------------
	for (auto station : db.get_DB_StationVec()) // Loopar alla stationer
	{
		for (auto cart : station->get_Station_Info_StationCARTS()) // Letar igenom varje stations fordonspool
		{
			if (find_ID == cart->get_Cart_Info_ID())                 // Om ID matchas
			{
				cout << "Found at: " << station->get_Station_Info_StationName() << "'s cartpool!" << endl;
				print_CartInfo(cart);
				for (auto history : cart->get_Cart_History())
				{
					cout << history << endl;
				}
				found = true;
				break;
			}
		}
	}
//----------------------------------------------------------------------------------------------------------------------------------------------------
	if (found == false) // Om fordon ej hittats i n�gon av stationerna, s�k igenom alla t�g.
	{
		for (auto train : db.get_DB_TrainVec()) // Loopar alla t�g
		{
			for (auto cart : train->get_Carts_in_Train_VEC()) // Loopar igenom aktuellt t�gs fordonsvector
			{
				if (find_ID == cart->get_Cart_Info_ID())                 // Om ID matchas
				{
					cout << "Cart was found among Train nr " << train->getTrainNR() << "'s carts!" << endl;
					print_CartInfo(cart);
					for (auto history : cart->get_Cart_History())   // Skriver ut fordonets historik
					{
						cout << history << endl;
					}
					found = true;
					break;
				}
			}
		}
	}

	if (found == false) // Fordon med ID som s�ktes existerar inte
	{
		cout << "Train with id [" << find_ID << "] does not exist." << endl;
	}

}

// Tar ett fordon som argument och skriver ut all info som finns beroende p� loglevel
void Simulation::print_CartInfo(shared_ptr<Train_Cart> cart)
{

	cout << "ID: " << cart->get_Cart_Info_ID() << " | Type: " << cart->get_Cart_Type_IN_TEXT()[cart->get_Cart_TYPE()] << " | "; // Loglevel = low

	if (get_loglevel() == "high")
	{
		switch (cart->get_Cart_TYPE())  // Log level = high
		{
		case PersonCart:
			cout << "Seats: " << cart->get_Cart_Info_SEATS() << " | Internet: ";
			if (cart->get_Cart_Info_INTERNET() == 0) { cout << "No " << endl; }
			else if (cart->get_Cart_Info_INTERNET() == 1) { cout << "Yes " << endl; }
			break;
		case SleepingCart:
			cout << "Beds: " << cart->get_Cart_Info_BEDS() << endl;
			break;
		case OpenCargoCart:
			cout << "Loadcapacity: " << cart->get_Cart_Info_LOADCAPACITY() << "tons | LoadAREA: " << cart->get_Cart_Info_LOADAREA() << " m^2" << endl;
			break;
		case ClosedCargoCart:
			cout << "LoadVolume: " << cart->get_Cart_Info_VOLUME() << " m^3" << endl;
			break;
		case Electric_Loco:
			cout << "Max speed: " << cart->get_Cart_Info_LOCOSPEED() << "km/h | Effect: " << cart->get_Cart_Info_LOCOEFFECT() << " kw" << endl;
			break;
		case Diesel_Loco:
			cout << "Max speed: " << cart->get_Cart_Info_LOCOSPEED() << "km/h | Consumption: " << cart->get_Cart_Info_LOCOCONSUMPTION() << " Liter per hour" << endl;
			break;

		}
		cout << "-------------------------------------------------------------------------------" << endl;




	}
	else
	{
		cout << "-------------------------------------------------------------------------------" << endl;
	}

}

//Do while switch-meny f�r Simulation finished menu
void Simulation::show_Simulator_Finished_Menu()
{
	bool again = true;
	do
	{
		cout << endl << "===== Simulation Complete =====  Simulation clock is: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << endl;
		cout << "1. Change log level[" << get_loglevel() << "]" << endl;
		cout << "2. Print Statistics" << endl;
		cout << "3. Train menu" << endl;
		cout << "4. Station menu" << endl;
		cout << "5. Cart menu" << endl;
		cout << "6. Return" << endl;

		switch (get_MenuChoice())
		{
		case 1:
			change_Log_level();
			break;
		case 2:
			print_statistics();
			break;
		case 3:
			show_TrainMenu();
			break;
		case 4:
			show_StationMenu();
			break;
		case 5:
			show_CartMenu();
		case 6:
			again = false; // Quit
			break;
		default:
			cout << endl << "Wrong choice...";
			cin.get();
		}

	} while (again == true);
}

//Input kontroll av int
int Simulation::get_MenuChoice()
{
	cout << endl;
	int menuChoice = 0;
	cout << "Input >> ";
	cin >> menuChoice;
	cin.get();

	while (cin.fail() || menuChoice < 0)            //Medans input inte �r en integer
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Wrong! Input must be an integer!"
			<< endl << endl << "Input again: ";
		cin >> menuChoice;
		cin.get();
	}

	return menuChoice;
}  //-----Get Meny val

//�ndrar tid f�r start eller stop intrervallet, kontrollerar anv�ndarens input
void Simulation::change_time_for_START_END_or_INTERVAL(string task)
{
	string input;
	cout << endl << "Enter new time for " << task << " in format HH:MM: ";
	getline(cin, input);

	string hoursStr;
	string minutesStr;														// L�ser in / initierar variabler
	string timeDelimiter;
	int hoursInt;
	int minutesInt;

	try
	{
		if (input.size() == 5)
		{
			hoursStr = input.substr(0, 2);
			minutesStr = input.substr(3, 2);
			timeDelimiter = input.substr(2, 1);								// Kontrollerar l�ngden av input
		}
		else
		{
			throw invalid_argument("Wrong length of your input...");    // Throwar
		}

		size_t found = input.find_first_not_of("0123456789:");			// Om str�ngen inneh�ller annat �n siffror eller :
		if (found == string::npos)
		{
			hoursInt = stoi(hoursStr);
			minutesInt = stoi(minutesStr);

			if (hoursInt > 23 || hoursInt < 0 || minutesInt > 59 || minutesInt < 0 || timeDelimiter != ":") // Timmar kan inte vara �ver 23, under 0, minuter kan inte vara �ver 59 eller under 0
			{
				throw invalid_argument("Something was wrong with your input...");
			}

			else // input korrekt av anv�ndaren
			{
				int new_minutes = (hoursInt * 60) + minutesInt; // g�r om inmatat tid fr�n timmar och minuter till minuter

				if (task == "interval") // Uppdaterar interval
				{
					time_simulationInterval = new_minutes;           
					cout << endl << "Time for [" << task << "] updated" << endl;
				}
				else if (task == "simulation start")      // Uppdaterar start tid
				{		
					time_SimulationSTART = new_minutes;
					time_simulation = new_minutes;
					cout << endl << "Time for [" << task << "] updated" << endl;
				}
				else if (task == "simulation end") // Uppdaterar sluttid
				{
					if (new_minutes > time_SimulationSTART) // sluttid kan inte vara f�re startid
					{
						time_SimulationEND = new_minutes;
						cout << endl << "Time for [" << task << "] updated" << endl;
					}
					else
					{
						cout << "Error; Cant set END time Earlier than START time" << endl;
					}
				}
			}
		}
		else
		{
			throw invalid_argument("Something was wrong with yout input...");
		}
	}
	catch (invalid_argument &ia)  // Catchar
	{
		cerr << endl << ia.what() << endl;
	}
}

//Tar tiden i minuter som argument och returnerar en str�ng i formatet hh:mm
string Simulation::print_MinutesToCLOCK_Format(unsigned int inserted_minutes)
{
	string Clock_String = "";
	int hour;
	int min;

	if (inserted_minutes > 1439)      // Om det har blivit en ny tag s� r�tta till timmarna
	{
		min = inserted_minutes % 60;
		hour = (inserted_minutes / 60) - 24;
	}

	else
	{
		hour = inserted_minutes / 60;
		min = inserted_minutes % 60;
	}

	
	// Bygger ihop klockstr�ngen

	if (hour < 10)  // �r timmvisaren under tv�siffrigt m�ste vi fylla ut med en 0:a
	{
		Clock_String = "0" + to_string(hour) + ":";
	}
	else
	{
		Clock_String = to_string(hour) + ":";
	}

	if (min < 10)  // �r minutvisaren under tv�siffrigt s� fyll ut med en 0:a
	{
		Clock_String += "0" + to_string(min);
	}
	else
	{
		Clock_String += to_string(min);
	}

	return Clock_String; // Returnerar klockstr�ngen
}

//K�r n�sta intervall, n�sta event eller alla event beroende p� vad anv�ndaren valt.
void Simulation::next_interval_event(string next)
{
	
	if (next == "next_interval")   // Om anv�ndaren valt next interval
	{
		time_simulation += time_simulationInterval; // stegar fram ett intervall

		
	}

	bool occured = false;


	while ((!(eventQueue.empty())))                           
	{
		shared_ptr<Event> nextEvent = eventQueue.top(); // Plockar fram eventet ur k�n
		
		if (next == "next_event" || next == "finish")						// om anv�ndaren valt att hoppa till n�sta event
		{
			time_simulation = nextEvent->getTime();		// s�tt kllockan till n�sta event
			eventQueue.pop();							//  Tar bort eventet ur k�n
			nextEvent->processEvent();					// Processerar eventet
			
			if (next == "next_event")
			{
				if (!(time_simulation < time_SimulationSTART))
				{
					cout << endl << "Clock is now: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << " Event occoured!" << endl;
					break;
				}
			
			}
		}


		else if (time_simulation >= nextEvent->getTime())  // Om anv�ndaren valt att stega via intervall s� kollas alla event som ligger inom tiden
		{
			eventQueue.pop();
			nextEvent->processEvent();
			occured = true;
		}


		else // Om n�sta event inte ligger inom interval s� �r det dags f�r utskrift
		{
			if (occured == true) // Om events intr�ffat skriv ut att events intr�ffat
			{
				
				cout << endl << "Clock is now: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << " Events above occoured  interval!" << endl;
				break;
			}
			else // Om inga events intr�ffat skriv ut det.
			{
				
				cout << endl << "Clock is now: [" << print_MinutesToCLOCK_Format(time_simulation) << "]" << " No events above occoured in interval!" << endl;
				break;
			}


		}
		
	}

}

// �ndrar log-level
void Simulation::change_Log_level()
{
	if (Log_level == "low")
	{
		Log_level = "high";
	}
	else if (Log_level == "high")
	{
		Log_level = "low";
	}
}

// Skriver ut statistik efter simuleringen
void Simulation::print_statistics()
{
	cout << endl << endl;
	cout << "-----------------------------" << endl;
	cout << "Carts at start of simulation: " << endl;


	for (size_t i = 0; i < Carts_at_start.size(); i++)
	{
		cout << db.get_DB_StationVec()[i]->get_Station_Info_StationName() << " = " << Carts_at_start[i] << endl;
	}
	cout << "-----------------------------" << endl;

	cout << endl;
	cout << "Results for end of simulation: " << endl;
	cout << "End time for simulation " << print_MinutesToCLOCK_Format(time_simulation) << endl;
	cout << endl;

	cout << "Trains that arrived on time: " << endl;
	for (auto train : db.get_DB_TrainVec())
	{
		if (train->get_Train_Info_STATE() == FINISHED)
		{
			cout << train->getTrainNR() << ", ";
		}
	}

	cout << endl << endl;
	cout << "Trains that never left their station:" << endl;
	cout << "Nr: ";
	for (auto train : db.get_DB_TrainVec())
	{
		if (train->get_Train_Info_STATE() == INCOMPLETE)
		{
			cout << train->getTrainNR() << " ";
		}
	}
	

	cout << endl << "----------------------------------------------------------------------------" << endl;


}

// Skriver till fil
void Simulation::write_to_file(string logdata)
{
	ofstream stream;
	stream.open("Trainsim.log", std::ofstream::out | std::ofstream::app);
	stream << logdata << endl;

}

//L�gger till starteventen
void Simulation::add_StartingEvents()
{
	for (size_t trainNR = 0; trainNR < db.get_DB_TrainVec().size(); trainNR++) // Loopar igenom alla t�g
	{
		string departureStation = db.get_DB_TrainVec()[trainNR]->get_Train_Info_Departure_STATION();

		for (size_t station = 0; station < db.get_DB_StationVec().size(); station++) // Loopar igenom alla stationer
		{
			if (departureStation == db.get_DB_StationVec()[station]->get_Station_Info_StationName()) // Om t�gets avg�ngsstation matchar stationens namn
			{
				// L�gg till event med *simulationsobjekt, t�g, dess avg�ngsstation och avg�ngstid
				eventQueue.push(shared_ptr<Event>(new EVENT_NOT_ASSEMBLED(this, db.get_DB_TrainVec()[trainNR], db.get_DB_StationVec()[station], db.get_DB_TrainVec()[trainNR]->get_Train_Info_Time_DEPARTURE())));
			}
		}
	}
}

//-----Tar fram distansen mellan 2 stationer
int Simulation::get_StationsDistance(string station1, string station2)
{
	auto distances = db.get_DB_Distance();
	auto it = distances.find(make_pair(station1, station2));        //Iteratorn ska s�ka par station1 och 2

	if (it != distances.end())                                    //Om paret fanns innan slutet p� mappen
	{
		return it->second;                                                //Returnera int (avst�ndet mellan stationerna)
	}
	else                                                                //Annars om paret inte hittades
	{
		it = distances.find(make_pair(station2, station1));    //V�nder p� s�kningen efter par station2 och 1

		if (it != distances.end())
		{
			return it->second;
		}
		else                    //Ska aldrig kunna ske
			return -1;
	}
}
