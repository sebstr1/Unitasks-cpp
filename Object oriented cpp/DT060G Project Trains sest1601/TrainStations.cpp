/* 2017-05-14
* Filnamn: Simulation.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Anv�nds f�r att hantera T�gstationer. kommunicera med Database, simulation, train och event.
*
*/

#include "TrainStations.h"


// L�s in och skapa stationer fr�n TrainStations.txt
bool Trainstation::readTrainStationsTXT(vector<shared_ptr<Trainstation>> &stationVec)
{
	string bigStationString;
	vector<string> testVector;
	vector<string> fordonsSTRINGvector;    	//Initierar tempor�ra variabler
	vector<int> fordonsINTvector;

	ifstream inFile("TrainStations.txt");  	//Kontrollerar om filen g�r att �ppna (existerar)
	if (inFile.is_open())
	{
		while (true)  // S� l�nge det g�r att l�sa fr�n filen, l�s in kontonr, balans och kredit, skapa sedan kontot
		{
		
			if (!(inFile >> bigStationString)) break; 	//L�ser f�rst in stationsNamn.
			StationName = bigStationString;

			if (!(getline(inFile, bigStationString))) break;  //L�ser in resten av raden som �r fordon

			
			testVector.clear();  // Clearar vector i varje loop
					

			string testString2 = bigStationString; // S�tter testString2 till orginalstr�ngen
			string ResultString; // Initierar
			string whiteSpaceDetect; // Initierar
			
			while (testString2.size() > 3) // K�r tills det �r slut p� Str�ngen
			{
				whiteSpaceDetect = testString2.substr(0, 1);  // Kollar om det finns whitespace och tar bort det isf.
				if (whiteSpaceDetect == " ")
				{
					testString2.erase(0, 1);
				}

				
				auto first_delim_pos = testString2.find_first_of('(');   // Find Delims
				auto last_delim_pos = testString2.find_first_of(')');

				
				ResultString = testString2.substr(first_delim_pos + 1, last_delim_pos - 1);  // Tar en substr�ng mellan delims (       )

				
				testString2 = testString2.substr(last_delim_pos + 1, testString2.size());  // Klipper ut (        ) och forts�tter med n�sta del i n�sta loop

				
				fordonsSTRINGvector.clear();   //Clearar vectors vid varje loop f�r att l�gga in ny info.
				fordonsINTvector.clear();
				
				istringstream iss(ResultString); // Splittar str�ngen vid varje whitespace och l�gger in i vectorn
				copy(istream_iterator<string>(iss), istream_iterator<string>(), std::back_inserter(fordonsSTRINGvector));

				
				for (size_t i = 0; i < fordonsSTRINGvector.size(); i++) // Konverterar vectorn fr�n str�ng till int
				{
					fordonsINTvector.push_back(stoi(fordonsSTRINGvector[i]));
				}


				int FordonsTYP = fordonsINTvector[1]; // Fordonstyp

				switch (FordonsTYP)      // Skapar nytt fordon beroende p� typ och l�gger in denna i stationens fordonspool (vector)
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
				stationVec.push_back(shared_ptr<Trainstation>(new Trainstation(StationName, Carts_in_station_vector)));  // Alla fordon inl�sta, skapa station
				Carts_in_station_vector.clear(); // Clearar station-fordonsvectorn s� att n�sta station inte f�r in f�reg�ende stations fordon ocks�
		}
		return true;
	}
	else // Om Filen inte fanns s� returnera false
	{

		return false;
	}
	
}


// L�gger till fordon i t�gs vector.
bool Trainstation::cart_add_to_train(int findType, shared_ptr<Train> train, string time)
{
	
	sort(Carts_in_station_vector.begin(), Carts_in_station_vector.end(), [](shared_ptr<Train_Cart>&a1, shared_ptr<Train_Cart> &a2)  // Sorterar stationens vector med fordon p� ID 
	{
		return a1->get_Cart_Info_ID() < a2->get_Cart_Info_ID();
	});

	
	auto iterator = find_if(Carts_in_station_vector.begin(), Carts_in_station_vector.end(), [findType](const shared_ptr<Train_Cart>foundtype)
	{

		return findType == foundtype->get_Cart_TYPE();																								// Letar igenom stationen efter fordon av typen vi s�kte

	});

	if (iterator != Carts_in_station_vector.end())					// Om vi hittade r�tt typ innan slutet av vectorn
	{
		train->add_cart_to_trainVECTOR(*iterator, time);     // L�gg till fordonet i t�gets vector
		
		train->remove_cart_from_needed_carts(findType);             // Tar bort fordon fr�n t�gets beh�vda fordon eftersom det �r tillagt i t�get redan

		Carts_in_station_vector.erase(iterator);					// Ta bort fordonet fr�n stationens vector

		return true;

	}

	else
	{
		cout << "Debug::::   Cart not found" << endl;
		return false;
	}

	

}


//L�gger till fordon till stationens vector och skickar samma fordon till t�get f�r j�mf�relse och borttagning fr�n t�gets vector.
bool Trainstation::cart_dismantle_at_station(shared_ptr<Train> train, string time)
{	
	auto start = train->get_Carts_in_Train_VEC().rbegin(), stop = train->get_Carts_in_Train_VEC().rend();  //Skapar iteratorer

	for (auto SuperCart_Iterator = start; SuperCart_Iterator != stop;) // G�r igenom med iteratorer
	{
		Carts_in_station_vector.push_back(*SuperCart_Iterator);   // L�gger in alla vagnar som t�get har i stationens vector

		
				
		train->remove_cart_from_trainVector(*SuperCart_Iterator, train, time); // Skickar in vagnen som som lades in i stationens vector f�r gemf�relse och bortagning fr�n t�get.
		start = train->get_Carts_in_Train_VEC().rbegin();        
		stop = train->get_Carts_in_Train_VEC().rend();           // S�tter nya iteratorer eftersom att vagnar tas bort eftersom
		SuperCart_Iterator = start;
	}

	sort(Carts_in_station_vector.begin(), Carts_in_station_vector.end(), [](shared_ptr<Train_Cart>&a1, shared_ptr<Train_Cart> &a2)  // Sorterar stationens fordonsvector p� ID
	{
		return a1->get_Cart_Info_ID() < a2->get_Cart_Info_ID();
	});
	
	return true;
}

// Tar bort t�g fr�n stationens vector
bool Trainstation::remove_Train_from_station(shared_ptr<Train> train)
{
	auto iterator = find_if(Trains_in_station_vector.begin(), Trains_in_station_vector.end(), [train](const shared_ptr<Train> foundTrain)  // Letar igenom t�gets vector
	{
		return train->getTrainNR() == foundTrain->getTrainNR();   // Kollar om t�get med [nr] vi vill ta bort matchar hittat t�gs nr 
	});

	if (iterator != Trains_in_station_vector.end())   // Om t�g  hittades i stationens vector, ta bort den
	{
		Trains_in_station_vector.erase(iterator); 
		return true;
	}
	
	else // T�g hittades ej i stationens t�gvector, borde ej kunna h�nda
	{
		cout << "Debug:::: MAJOR ERROR  Train not found in trainvec" << endl;
		return false;
	}

}


















