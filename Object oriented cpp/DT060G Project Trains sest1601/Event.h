/* 2017-05-14
* Filnamn: Event.h
* Projekt Trains
* namn: Sebastian Strindlund ses1601
*
* Definerar den abstrakta klassen Event och dess deriverade klasser.
*/

#ifndef EventH
#define EventH


#include <memory>
#include <iostream>
#include "TrainStations.h"

using namespace std;

// Forward declarations
class Simulation;


class Event {

protected:
	unsigned int time_event; // Time for this event
	
public:
	Event(unsigned int t) : time_event(t) { } // Constructor /tid för event

	virtual ~Event() { }

	virtual void processEvent() = 0; // Processerar event genom denna metod

	unsigned int getTime() const { return time_event; } // Hämtar tid för eventet
};


class EventTimeComparison {
public:
	bool operator() (const shared_ptr<Event> left, const shared_ptr<Event> right) {  // Jämför eventttider för sortering
		return left->getTime() > right->getTime();
	}
};


//--- Deriverade Eventklasser ----------------------------------------------------

// TRAINSTATE 0
class EVENT_NOT_ASSEMBLED : public Event {
public:
	EVENT_NOT_ASSEMBLED(Simulation *obj, shared_ptr<Train> TheTrain, shared_ptr<Trainstation> Station, int TrainStartTid) : Event(TrainStartTid - 30) { Train_NOT_ASSEMBLED = TheTrain; Departure_Station = Station; SimObjekt = obj; }
	
	virtual void processEvent();


protected:
	shared_ptr<Train> Train_NOT_ASSEMBLED;
	
	shared_ptr<Trainstation> Departure_Station;
	
	Simulation *SimObjekt;
	
};


// TRAINSTATE 2
class EVENT_ASSEMBLED : public Event {
public:
	EVENT_ASSEMBLED(Simulation *obj, shared_ptr<Train> TheTrain, int TrainStartTid) : Event(TrainStartTid - 30) { Train_IN_ASSEMBLE = TheTrain;  SimObjekt = obj; }

	virtual void processEvent();


protected:
	
	shared_ptr<Train> Train_IN_ASSEMBLE;
	Simulation *SimObjekt;
};


// TRAINSTATE 3
class EVENT_READY : public Event {
public:
	EVENT_READY(Simulation *obj, shared_ptr<Train> TheTrain, int TrainStartTid) : Event(TrainStartTid - 10) { TRAIN_IN_READY = TheTrain; SimObjekt = obj; }

	virtual void processEvent();


protected:
	shared_ptr<Train> TRAIN_IN_READY;
	Simulation *SimObjekt;
};

// TRAINSTATE 4
class EVENT_RUNNING : public Event {
public:
	EVENT_RUNNING(Simulation *obj, shared_ptr<Train> TheTrain, int TrainStartTid, bool infobool) : Event(TrainStartTid) { TRAIN_IN_RUNNING = TheTrain; SimObjekt = obj; showInfo = infobool; }

	virtual void processEvent();


protected:
	shared_ptr<Train> TRAIN_IN_RUNNING;
	Simulation *SimObjekt;
	bool showInfo;
};

// TRAINSATE 5
class EVENT_ARRIVED : public Event {
public:
	EVENT_ARRIVED(Simulation *obj, shared_ptr<Train> TheTrain, int ArrivedTid, bool infobool) : Event(ArrivedTid) { TRAIN_IN_ARRIVED = TheTrain; SimObjekt = obj; showInfo = infobool; }

	virtual void processEvent();


protected:
	shared_ptr<Train> TRAIN_IN_ARRIVED;
	Simulation *SimObjekt;
	bool showInfo;
};

// TRAINSTATE 6
class EVENT_FINISHED : public Event {
public:
	EVENT_FINISHED(Simulation *obj, shared_ptr<Train> &TheTrain, int Arrivedtid, bool infobool) : Event(Arrivedtid + 20) { TRAIN_IN_FINISHED = TheTrain; SimObjekt = obj; showInfo = infobool; }

	virtual void processEvent();


protected:
	shared_ptr<Train> TRAIN_IN_FINISHED;
	Simulation *SimObjekt;
	bool showInfo;
};


#endif


