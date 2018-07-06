/* 2017-05-14
* Filnamn: Train.cpp
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* implementeringar
* Filen anv�nds f�r att hantera t�g.. kommunicerar med simulation, event och trainstation
*/

#include "Train.h"


// L�ser in T�g fr�n filen Trains.txt
bool Train::readFile(vector<shared_ptr<Train>> &TrainVecFromSimulation)
{
	//Initierar tempor�ra variabler
	string tmpstring;
	string TrainNR;
	string StartStation;
	string EndStation;
	string StartTime;
	string EndTime;
	vector<string> testVector;
	vector<int> fordonstyp;
	vector<shared_ptr<Train_Cart>> Train_Cart_VECTOR;

	ifstream inFile("Trains.txt"); //Kontrollerar om filen g�r att �ppna (existerar)
	if (inFile.is_open())
	{		
	
		while (true) // S� l�nge det g�r att l�sa fr�n filen, l�s in t�g..
		{

			if (!(getline(inFile, tmpstring))) break;
			
		
			testVector.clear(); // T�mmer vectorer mellan varje loop
			fordonstyp.clear();

			istringstream iss(tmpstring);
			copy(istream_iterator<string>(iss), istream_iterator<string>(), std::back_inserter(testVector)); // Delar upp str�ng och s�tter in i vector

			int TrainNR = stoi(testVector[0]); // Trainnr i f�rsta delen
			string StartStation = testVector[1]; // Startstation
			string EndStation = testVector[2];  // End station
			string StartTime = testVector[3];   // Start-tid
			string EndTime = testVector[4];    // Slut-tid
			int maxSpeed = stoi(testVector[5]); // maxspeed




			
			for (size_t index = 6; index < testVector.size(); index++) //L�gger in fordonstyper i t�get.
			{
				fordonstyp.push_back(stoi(testVector[index]));
			}
			
			string depHourStr = StartTime.substr(0, 2);						//G�r om avg�ngs och ankomsttiden till minuter i en INT
			string depMinutStr = StartTime.substr(3, 2);
			int depHour = stoi(depHourStr);
			int depMinut = stoi(depMinutStr);
			int Start_Time_Minutes = (depHour * 60) + depMinut;

			string arrHourStr = EndTime.substr(0, 2);
			string arrMinutStr = EndTime.substr(3, 2);
			int arrHour = stoi(arrHourStr);
			int arrMinut = stoi(arrMinutStr);
			int End_Time_Minutes = (arrHour * 60) + arrMinut;

			//Skapar t�g som l�ggs till i Database.h's trainvector
			TrainVecFromSimulation.push_back(shared_ptr<Train>(new Train(TrainNR, StartStation, EndStation, Start_Time_Minutes, End_Time_Minutes, maxSpeed, fordonstyp, Train_Cart_VECTOR)));
		}
		return true;

	}
	// Om kundfilen inte fanns s� returnera false
	else
	{
		
		return false;
	}


	
	
}




// L�gger till fordon i t�gs vector        ---------------------------------------------------------------- INTE KLAR
bool Train::add_cart_to_trainVECTOR(shared_ptr<Train_Cart> cart, string time) 
{
	Carts_In_Train_Vector.push_back(cart);
	string history = "[" + time + "] Connected to train nr: " + to_string(getTrainNR()) + " at " + get_Train_Info_Departure_STATION();
	cart->add_Cart_history(history);
	return true;
}




// Tar bort fordon fr�n t�gets beh�vda fordon eftersom det lagts till i t�get redan  ----------------------------------------- KLAR????????????
bool Train::remove_cart_from_needed_carts(int needed)
{
	// Letar igenom t�gets vector
	auto iterator = find_if(Carts_Needed_VECTOR.begin(), Carts_Needed_VECTOR.end(), [needed](const int found)
	{
		// Kollar om vagnen vi vill ta borts id matchar n�gon av t�gets faktiskta vagnar
		return needed == found;

	});


	// Om vagn hittades i t�gets vector, ta bort den
	if (iterator != Carts_Needed_VECTOR.end())
	{
		
		Carts_Needed_VECTOR.erase(iterator);


		return true;
	}

	// Vagn hittades inte i t�gets vector, borde ej kunna h�nda
	else
	{
		cout << "Debug::::   MAJOR SUPER ERRRORORRORORORO       CART NOT FOUND IN TRAIN VECTOR TO DELETE ------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return false;
	}
}




// Tar bort fordon fr�n t�g eftersom t�get har ankommit och beh�ver l�mna ifr�n sig sina fordon.
bool Train::remove_cart_from_trainVector(shared_ptr<Train_Cart> cart, shared_ptr<Train> train, string time)
{
	
	// Letar igenom t�gets vector
	auto iterator = find_if(Carts_In_Train_Vector.begin(), Carts_In_Train_Vector.end(), [cart](const shared_ptr<Train_Cart> foundCart)
	{
		// Kollar om vagnen vi vill ta borts id matchar n�gon av t�gets faktiskta vagnar
		return cart->get_Cart_Info_ID() == foundCart->get_Cart_Info_ID();

	});
	

	// Om vagn hittades i t�gets vector, ta bort den
	if (iterator != Carts_In_Train_Vector.end())
	{
		string history = "[" + time + "] Disconnected from train nr: " + to_string(train->getTrainNR()) + " and added to " + train->get_Train_Info_Arrival_STATION() + " cartpool.";
		cart->add_Cart_history(history);
		Carts_In_Train_Vector.erase(iterator);


		return true;
	}

	// Vagn hittades inte i t�gets vector, borde ej kunna h�nda
	else
	{
		cout << "Debug::::   MAJOR SUPER ERRRORORRORORORO       CART NOT FOUND IN TRAIN VECTOR TO DELETE ------------------------------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return false;
	}


}

