/*
File:         BurgerBar.cpp
Objective:    Implementation

*/


#include <iostream>
#include "TrainCompany.h"
#include "Simulation.h"

using std::cout;
using std::endl;

//BurgerBar::BurgerBar(Simulation *sim, int chairs)
//	: nChairs(chairs), freeChairs(chairs), theSim(sim)
//{
//	profit = -nChairs * COST_PER_CHAIR;
//}


bool TrainCompany::tryBuildTrain(int nPeople)
// If enough chairs, enter and order
{
	cout << "Time " << theSim->getTime() << ": ";
	cout << "Group of " << nPeople << " customers arrives.";
	/*if (nPeople <= freeChairs) {
		cout << " In queue to order." << endl;
		return true;
	}
	else {
		cout << " No free chairs, they leave." << endl;
		return false;
	}*/

	//TROLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
	return true;
}

//void BurgerBar::order(int nBurgers) {
//	// Place order
//	cout << "Time " << theSim->getTime() << ": ";
//	cout << nBurgers << " BigSmack ordered. " << endl;
//}
//
//
//bool BurgerBar::getChairs(int nPeople) {
//	// Get nPeople chairs if posssible
//	if (nPeople <= freeChairs) {
//		freeChairs -= nPeople;
//		cout << "Time " << theSim->getTime() << ": ";
//		cout << nPeople << " customers found chairs, seated. ";
//		cout << "Free chairs: " << freeChairs << endl;
//		return true;
//	}
//	return false;
//}
//
//
//void BurgerBar::serve(int nBurgers) {
//	// Serve burgers, compute profits
//	cout << "Time " << theSim->getTime() << ": ";
//	cout << "Served " << nBurgers << " BigSmack, searching for chairs." << endl;
//	profit += PROFIT_PER_BURGER * nBurgers;
//}
//
//void BurgerBar::leave(int nPeople) {
//	// People leave, free up chairs
//	freeChairs += nPeople;
//	cout << "Time " << theSim->getTime() << ": ";
//	cout << "Group of size " << nPeople << " leaves.";
//	cout << " Free chairs: " << freeChairs << endl;
//}
//
//void BurgerBar::closeDown() {
//	// Time to close down, no more customers can enter
//
//	cout << "Time " << theSim->getTime() << ": ";
//	cout << "CLOSING DOWN - no entrance" << endl;
//}