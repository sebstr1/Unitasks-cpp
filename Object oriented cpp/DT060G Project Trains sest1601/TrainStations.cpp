/* 2017-05-14
* Filnamn: Simulation.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Används för att hantera Tågstationer. kommunicera med Database, simulation, train och event.
*
*/

#include "TrainStations.h"


// Läs in och skapa stationer från TrainStations.txt
bool Trainstation::readTrainStationsTXT(vector<shared_ptr<Trainstation>> &stationVec)
{
	string bigStationString;
	vector<string> testVector;
	vector<string> fordonsSTRINGvector;    	//Initierar temporära variabler
	vector<int> fordonsINTvector;

	ifstream inFile("TrainStations.txt");  	//Kontrollerar om filen går att öppna (existerar)
	if (inFile.is_open())
	{
		while (true)  // Så länge det går att läsa från filen, läs in kontonr, balans och kredit, skapa sedan kontot
		{
		
			if (!(inFile >> bigStationString)) break; 	//Läser först in stationsNamn.
			StationName = bigStationString;

			if (!(getline(inFile, bigStationString))) break;  //Läser in resten av raden som är fordon

			
			testVector.clear();  // Clearar vector i varje loop
					

			string testString2 = bigStationString; // Sätter testString2 till orginalsträngen
			string ResultString; // Initierar
			string whiteSpaceDetect; // Initierar
			
			while (testString2.size() > 3) // Kör tills det är slut på Strängen
			{
				whiteSpaceDetect = testString2.substr(0, 1);  // Kollar om det finns whitespace och tar bort det isf.
				if (whiteSpaceDetect == " ")
				{
					testString2.erase(0, 1);
				}

				
				auto first_delim_pos = testString2.find_first_of('(');   // Find Delims
				auto last_delim_pos = testString2.find_first_of(')');

				
				ResultString = testString2.substr(first_delim_pos + 1, last_delim_pos - 1);  // Tar en substräng mellan delims (       )

				
				testString2 = testString2.substr(last_delim_pos + 1, testString2.size());  // Klipper ut (        ) och fortsätter med nästa del i nästa loop

				
				fordonsSTRINGvector.clear();   //Clearar vectors vid varje loop för att lägga in ny info.
				fordonsINTvector.clear();
				
				istringstream iss(ResultString); // Splittar strängen vid varje whitespace och lägger in i vectorn
				copy(istream_iterator<string>(iss), istream_iterator<string>(), std::back_inserter(fordonsSTRINGvector));

				
				for (size_t i = 0; i < fordonsSTRINGvector.size(); i++) // Konverterar vectorn från sträng till int
				{
					fordonsINTvector.push_back(stoi(fordonsSTRINGvector[i]));
				}


				int FordonsTYP = fordonsINTvector[1]; // Fordonstyp

				switch (FordonsTYP)      // Skapar nytt fordon beroende på typ och lägger in denna i stationens fordonspool (vector)
				{
				case PersonCart:
					Carts_in_station_vector.push_back(shared_ptr<Train_Cart>(new PersonWagon(fordonsINTvector[0], PersonCart, fordonsINTvector[2], fordonsINTvector[3])));
					break;
				case SleepingCart:
					Carts_in_station_vector.push_back(shared_ptr<Train_Cart>(new SleepingWagon(fordonsINTvector[0], SleepingCart, fordonsINTvector[2])));
					break;
				case OpenCargoCart:
					Carts_in_station_vector.push_back(shared_ptr<Train_Cart>(new OpenCargoWagon(fordonsINTvector[0], OpenCargoCart, fordonsINTvector[2], fordonsINTvector[3])));
					break;
				case ClosedCargoCart:
					Carts_in_station_vector.push_back(shared_ptr<Train_Cart>(new CoveredCargoWagon(fordonsINTvector[0], ClosedCargoCart, fordonsINTvector[2])));
					break;
				case Electric_Loco:
					Carts_in_station_vector.push_back(shared_ptr<Train_Cart>(new  ElectricLoco(fordonsINTvector[0], Electric_Loco, fordonsINTvector[2], fordonsINTvector[3])));
					break;
				case Diesel_Loco:
					Carts_in_station_vector.push_back(shared_ptr<Train_Cart>(new DieselLoco(fordonsINTvector[0], Diesel_Loco, fordonsINTvector[2], fordonsINTvector[3])));
					break;
				}
			}
				stationVec.push_back(shared_ptr<Trainstation>(new Trainstation(StationName, Carts_in_station_vector)));  // Alla fordon inlästa, skapa station
				Carts_in_station_vector.clear(); // Clearar station-fordonsvectorn så att nästa station inte får in föregående stations fordon också
		}
		return true;
	}
	else // Om Filen inte fanns så returnera false
	{

		return false;
	}
	
}


// Lägger till fordon i tågs vector.
bool Trainstation::cart_add_to_train(int findType, shared_ptr<Train> train, string time)
{
	
	sort(Carts_in_station_vector.begin(), Carts_in_station_vector.end(), [](shared_ptr<Train_Cart>&a1, shared_ptr<Train_Cart> &a2)  // Sorterar stationens vector med fordon på ID 
	{
		return a1->get_Cart_Info_ID() < a2->get_Cart_Info_ID();
	});

	
	auto iterator = find_if(Carts_in_station_vector.begin(), Carts_in_station_vector.end(), [findType](const shared_ptr<Train_Cart>foundtype)
	{

		return findType == foundtype->get_Cart_TYPE();																								// Letar igenom stationen efter fordon av typen vi sökte

	});

	if (iterator != Carts_in_station_vector.end())					// Om vi hittade rätt typ innan slutet av vectorn
	{
		train->add_cart_to_trainVECTOR(*iterator, time);     // Lägg till fordonet i tågets vector
		
		train->remove_cart_from_needed_carts(findType);             // Tar bort fordon från tågets behövda fordon eftersom det är tillagt i tåget redan

		Carts_in_station_vector.erase(iterator);					// Ta bort fordonet från stationens vector

		return true;

	}

	else
	{
		cout << "Debug::::   Cart not found" << endl;
		return false;
	}

	

}


//Lägger till fordon till stationens vector och skickar samma fordon till tåget för jämförelse och borttagning från tågets vector.
bool Trainstation::cart_dismantle_at_station(shared_ptr<Train> train, string time)
{	
	auto start = train->get_Carts_in_Train_VEC().rbegin(), stop = train->get_Carts_in_Train_VEC().rend();  //Skapar iteratorer

	for (auto SuperCart_Iterator = start; SuperCart_Iterator != stop;) // Går igenom med iteratorer
	{
		Carts_in_station_vector.push_back(*SuperCart_Iterator);   // Lägger in alla vagnar som tåget har i stationens vector

		
				
		train->remove_cart_from_trainVector(*SuperCart_Iterator, train, time); // Skickar in vagnen som som lades in i stationens vector för gemförelse och bortagning från tåget.
		start = train->get_Carts_in_Train_VEC().rbegin();        
		stop = train->get_Carts_in_Train_VEC().rend();           // Sätter nya iteratorer eftersom att vagnar tas bort eftersom
		SuperCart_Iterator = start;
	}

	sort(Carts_in_station_vector.begin(), Carts_in_station_vector.end(), [](shared_ptr<Train_Cart>&a1, shared_ptr<Train_Cart> &a2)  // Sorterar stationens fordonsvector på ID
	{
		return a1->get_Cart_Info_ID() < a2->get_Cart_Info_ID();
	});
	
	return true;
}

// Tar bort tåg från stationens vector
bool Trainstation::remove_Train_from_station(shared_ptr<Train> train)
{
	auto iterator = find_if(Trains_in_station_vector.begin(), Trains_in_station_vector.end(), [train](const shared_ptr<Train> foundTrain)  // Letar igenom tågets vector
	{
		return train->getTrainNR() == foundTrain->getTrainNR();   // Kollar om tåget med [nr] vi vill ta bort matchar hittat tågs nr 
	});

	if (iterator != Trains_in_station_vector.end())   // Om tåg  hittades i stationens vector, ta bort den
	{
		Trains_in_station_vector.erase(iterator); 
		return true;
	}
	
	else // Tåg hittades ej i stationens tågvector, borde ej kunna hända
	{
		cout << "Debug:::: MAJOR ERROR  Train not found in trainvec" << endl;
		return false;
	}

}


















