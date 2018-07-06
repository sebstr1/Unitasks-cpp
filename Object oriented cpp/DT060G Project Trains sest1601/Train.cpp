/* 2017-05-14
* Filnamn: Train.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Filen används för att hantera tåg.. kommunicerar med simulation, event och trainstation
*/

#include "Train.h"


// Läser in Tåg från filen Trains.txt
bool Train::readFile(vector<shared_ptr<Train>> &TrainVecFromSimulation)
{
	//Initierar temporära variabler
	string tmpstring;
	string TrainNR;
	string StartStation;
	string EndStation;
	string StartTime;
	string EndTime;
	vector<string> testVector;
	vector<int> fordonstyp;
	vector<shared_ptr<Train_Cart>> Train_Cart_VECTOR;

	ifstream inFile("Trains.txt"); //Kontrollerar om filen går att öppna (existerar)
	if (inFile.is_open())
	{		
	
		while (true) // Så länge det går att läsa från filen, läs in tåg..
		{

			if (!(getline(inFile, tmpstring))) break;
			
		
			testVector.clear(); // Tömmer vectorer mellan varje loop
			fordonstyp.clear();

			istringstream iss(tmpstring);
			copy(istream_iterator<string>(iss), istream_iterator<string>(), std::back_inserter(testVector)); // Delar upp sträng och sätter in i vector

			int TrainNR = stoi(testVector[0]); // Trainnr i första delen
			string StartStation = testVector[1]; // Startstation
			string EndStation = testVector[2];  // End station
			string StartTime = testVector[3];   // Start-tid
			string EndTime = testVector[4];    // Slut-tid
			int maxSpeed = stoi(testVector[5]); // maxspeed




			
			for (size_t index = 6; index < testVector.size(); index++) //Lägger in fordonstyper i tåget.
			{
				fordonstyp.push_back(stoi(testVector[index]));
			}
			
			string depHourStr = StartTime.substr(0, 2);						//Gör om avgångs och ankomsttiden till minuter i en INT
			string depMinutStr = StartTime.substr(3, 2);
			int depHour = stoi(depHourStr);
			int depMinut = stoi(depMinutStr);
			int Start_Time_Minutes = (depHour * 60) + depMinut;

			string arrHourStr = EndTime.substr(0, 2);
			string arrMinutStr = EndTime.substr(3, 2);
			int arrHour = stoi(arrHourStr);
			int arrMinut = stoi(arrMinutStr);
			int End_Time_Minutes = (arrHour * 60) + arrMinut;

			//Skapar tåg som läggs till i Database.h's trainvector
			TrainVecFromSimulation.push_back(shared_ptr<Train>(new Train(TrainNR, StartStation, EndStation, Start_Time_Minutes, End_Time_Minutes, maxSpeed, fordonstyp, Train_Cart_VECTOR)));
		}
		return true;

	}
	// Om kundfilen inte fanns så returnera false
	else
	{
		
		return false;
	}


	
	
}




// Lägger till fordon i tågs vector        ---------------------------------------------------------------- INTE KLAR
bool Train::add_cart_to_trainVECTOR(shared_ptr<Train_Cart> cart, string time) 
{
	Carts_In_Train_Vector.push_back(cart);
	string history = "[" + time + "] Connected to train nr: " + to_string(getTrainNR()) + " at " + get_Train_Info_Departure_STATION();
	cart->add_Cart_history(history);
	return true;
}




// Tar bort fordon från tågets behövda fordon eftersom det lagts till i tåget redan  ----------------------------------------- KLAR????????????
bool Train::remove_cart_from_needed_carts(int needed)
{
	// Letar igenom tågets vector
	auto iterator = find_if(Carts_Needed_VECTOR.begin(), Carts_Needed_VECTOR.end(), [needed](const int found)
	{
		// Kollar om vagnen vi vill ta borts id matchar någon av tågets faktiskta vagnar
		return needed == found;

	});


	// Om vagn hittades i tågets vector, ta bort den
	if (iterator != Carts_Needed_VECTOR.end())
	{
		
		Carts_Needed_VECTOR.erase(iterator);


		return true;
	}

	// Vagn hittades inte i tågets vector, borde ej kunna hända
	else
	{
		cout << "Debug::::   MAJOR SUPER ERRRORORRORORORO       CART NOT FOUND IN TRAIN VECTOR TO DELETE ------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return false;
	}
}




// Tar bort fordon från tåg eftersom tåget har ankommit och behöver lämna ifrån sig sina fordon.
bool Train::remove_cart_from_trainVector(shared_ptr<Train_Cart> cart, shared_ptr<Train> train, string time)
{
	
	// Letar igenom tågets vector
	auto iterator = find_if(Carts_In_Train_Vector.begin(), Carts_In_Train_Vector.end(), [cart](const shared_ptr<Train_Cart> foundCart)
	{
		// Kollar om vagnen vi vill ta borts id matchar någon av tågets faktiskta vagnar
		return cart->get_Cart_Info_ID() == foundCart->get_Cart_Info_ID();

	});
	

	// Om vagn hittades i tågets vector, ta bort den
	if (iterator != Carts_In_Train_Vector.end())
	{
		string history = "[" + time + "] Disconnected from train nr: " + to_string(train->getTrainNR()) + " and added to " + train->get_Train_Info_Arrival_STATION() + " cartpool.";
		cart->add_Cart_history(history);
		Carts_In_Train_Vector.erase(iterator);


		return true;
	}

	// Vagn hittades inte i tågets vector, borde ej kunna hända
	else
	{
		cout << "Debug::::   MAJOR SUPER ERRRORORRORORORO       CART NOT FOUND IN TRAIN VECTOR TO DELETE ------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return false;
	}


}

