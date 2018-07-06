/* 2017-05-14
* Filnamn: Fordon.h
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* Definerar den abstrakta klassen Train_Cart och dess deriverade klasser.
*/

#ifndef FordonH
#define FordonH
#include <vector>
#include <string>

using namespace std;

enum Type { PersonCart, SleepingCart, OpenCargoCart, ClosedCargoCart, Electric_Loco, Diesel_Loco }; //Enumstyper

class Train_Cart {
private:
	int Cart_ID = 0;
	int Cart_Type = 0;
	vector<string> Cart_Statebytext_Vector{ "PersonCart", "SleepingCart", "OpenCargoCart", "ClosedCargoCart", "Electric_Loco", "Diesel_Loco" }; // State i text
	vector<string> Cart_History_Vector; // Historik
	Type ENUM_CART_TYPE; // typ i enum

public:
	Train_Cart() {}	
	Train_Cart(int fordonsid, Type enum_type) {	Cart_ID = fordonsid, ENUM_CART_TYPE = enum_type; }		// Konstruktor
	virtual ~Train_Cart() {};														// Destruktor
	int get_Cart_Info_ID() const { return Cart_ID; }								// returnerar id
	vector<string> get_Cart_Type_IN_TEXT() const { return Cart_Statebytext_Vector; } // returerar vector med state i text
	void add_Cart_history(string history) { Cart_History_Vector.push_back(history); } // lägger till historik i vectorn
	vector<string> get_Cart_History() const { return Cart_History_Vector; }          // Returnerar vector med historik
	
	//Virtual
	virtual int get_Cart_TYPE() const = 0;			// Get fordonstyp	

	// SleepingWagon
	virtual int get_Cart_Info_BEDS() const { return 0; }	// Get Beds
	
	// PersonWagon	
	virtual int get_Cart_Info_INTERNET() const { return 0; }	 // Get Internet
	virtual int get_Cart_Info_SEATS() const { return 0; }		// Get Seats

	// OpenCargoWagon
	virtual int get_Cart_Info_LOADAREA() const { return 0; }	   // Get area
	virtual int get_Cart_Info_LOADCAPACITY() const { return 0; }	// Get cap

	// CoveredCargoWagon
	virtual int get_Cart_Info_VOLUME() const { return 0; }				// Get volume				 
	virtual int get_Cart_Info_LOCOSPEED() const { return 0; }           // Get Lokmaxhastighet
	virtual int get_Cart_Info_LOCOEFFECT() const { return 0; }			// Get Effekt
	virtual int get_Cart_Info_LOCOCONSUMPTION() const { return 0; }		// Get konsumption

};


// Deriverade klasser ----------------------------------------------------------------------------------


class ElectricLoco : public Train_Cart {
private:
	int Speed = 0;
	int LocoEffect = 0;

public:
	ElectricLoco() {}
	ElectricLoco(int fordonsid, Type enum_type, int electric_speed, int effect) : Train_Cart(fordonsid, enum_type) { Speed = electric_speed, LocoEffect = effect; }

	//Get
	virtual int get_Cart_Info_LOCOSPEED() const { return Speed; }        // Get Lokmaxhastighet
	virtual int get_Cart_Info_LOCOEFFECT() const { return LocoEffect; }  // Get effekt
	virtual int get_Cart_TYPE() const { return 4; }	                     // Get fordonstyp
};
/*---------------------------------------------------------------------------------------------------*/class DieselLoco : public Train_Cart {
private:
	int Speed = 0;
	int Consumption = 0;

public:
	DieselLoco() {}
	DieselLoco(int fordonsid, Type enum_type, int disel_speed, int consump) : Train_Cart(fordonsid, enum_type) { Speed = disel_speed, Consumption = consump; }

	virtual int get_Cart_Info_LOCOSPEED() const { return Speed; }              // Get Lokmaxhastighet
	virtual int get_Cart_Info_LOCOCONSUMPTION() const { return Consumption; }  // get konsumption
	virtual int get_Cart_TYPE() const { return 5; }							   // Get fordonstyp
};
//-----------------------------------------------------------------------------------------------------
class SleepingWagon : public Train_Cart {
private:
	int Beds = 0;

public:
	SleepingWagon() {}
	SleepingWagon(int fordonsid, Type enum_type, int beds) : Train_Cart(fordonsid, enum_type) { Beds = beds; };

	virtual int get_Cart_TYPE() const { return 1; }           // Get fordonstyp
	virtual int get_Cart_Info_BEDS() const { return Beds; }	  // Get Beds
	
	
};
//---------------------------------------------------------------------------------------------------------
class PersonWagon : public Train_Cart {
private:
	int Seats = 0;
	int HasInternet = 0;

public:
	PersonWagon() {}
	PersonWagon(int fordonsid, Type enum_type, int seats, int internet) : Train_Cart(fordonsid, enum_type) { Seats = seats, HasInternet = internet; };

	virtual int get_Cart_TYPE() const { return 0; }                          // Get fordonstyp
	virtual int get_Cart_Info_INTERNET() const { return HasInternet; }		 // Get Internet
	virtual int get_Cart_Info_SEATS() const { return Seats; }				 // Get Seats

};
//---------------------------------------------------------------------------------------------------------
class OpenCargoWagon : public Train_Cart {
private:
	int loadCapacity = 0;
	int loadArea = 0;

public:
	OpenCargoWagon() {}
	OpenCargoWagon(int fordonsid, Type enum_type, int loadcap, int loadarea) : Train_Cart(fordonsid, enum_type) { loadCapacity = loadcap, loadArea = loadarea; };

	virtual int get_Cart_TYPE() const { return 2; }							 // Get fordonstyp
	virtual int get_Cart_Info_LOADAREA() const { return loadArea; }		     // Get area
	virtual int get_Cart_Info_LOADCAPACITY() const { return loadCapacity; }  // Get cap

};
//---------------------------------------------------------------------------------------------------------
class CoveredCargoWagon : public Train_Cart {
private:
	int loadVolume = 0;
	
public:
	CoveredCargoWagon() {}
	CoveredCargoWagon(int fordonsid, Type enum_type, int vol) : Train_Cart(fordonsid, enum_type) { loadVolume = vol; };

	virtual int get_Cart_TYPE() const { return 3; }                    // Get fordonstyp
	virtual int get_Cart_Info_VOLUME() const { return loadVolume; }	   // Get volume

};

#endif

