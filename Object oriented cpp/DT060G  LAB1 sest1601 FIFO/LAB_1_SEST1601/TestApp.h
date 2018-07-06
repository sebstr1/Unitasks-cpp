/*
* Filnamn: TestApp.h
* Labb 1 uppgift 1
* namn: Sebastian Strindlund ses1601
*/
#ifndef TestAppH
#define TestAppH

#include "queue.h"
#include <string>
#include "Menu.h"
#include "terminal.h"


class TestApp {
private:
	Menu MenuObj;
	unique_ptr<Queue> LameQ;
	//smart pointer object to hold the dynamically Queue object

	// Menu-alternativ
	void createQueue(); // Skapar en kö av önskad längd
	void enqueue(); // Frågar efter tal
	void dequeue(); // Tar bort tal, skriver ut
	void isEmpty() const;
	void isFull() const;
	void nrElements() const;

	// MaxElement i kön
	void TestApp::maxElementsinQ() const;

	//Sätter alla menyalternativ till true
	void enableAlternatives();


public:
	TestApp();
	void run();
};
#endif

