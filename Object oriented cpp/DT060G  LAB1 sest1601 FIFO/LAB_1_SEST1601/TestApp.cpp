
/*
* Filnamn: TestApp.cpp
* Labb 1 uppgift 1
* namn: Sebastian Strindlund ses1601
*/

#include "TestApp.h"
#include "queue.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;




// Skapar en k� av storleken anv�ndaren v�ljer
void TestApp::createQueue()
{
	
	//L�ser in storleken anv�ndaren vill anv�nda
	int Qsize;
	cout << "Select the maximum size of your Queue: ";
	cin >> Qsize;

	//Resetar objektet och skapar ett nytt.
	LameQ.reset(new Queue(Qsize));

	cout << endl << "Queue with size of: " << LameQ->capacity()  << " has been created." << endl;

}

//L�gger till ett element i k�n
void TestApp::enqueue()
{
	//Pre condition: Que (array) has not reached maximum capacity
	if (LameQ->full() == true)
	{
		cout << endl << endl << "Que is full";
		return;
	}
	else
	{
				
		//L�ser in elementet anv�ndaren vill ENQUEa
		int element;
		cout << endl << endl << "Enter an int: ";
		cin >> element;

		LameQ->enqueue(element);
	}

}

//"Tar bort" ett element fr�n k�n genom att flytta head pekare.
void TestApp::dequeue()
{
	//Skapar int f�r att skicka in till dequeue() i queue.cpp
	int element;

	//Kontrollerar om k�n �r tom
	if (LameQ->empty() == true)
	{
		cout << endl << "Q is empty" << endl;
	}
	//Var k�n inte tom s� avk�a elementet
	else
	{
		LameQ->dequeue(element);
	}
}


//Kontrollerar om k�n �r tom genom att kalla p� empty() fr�n queue.cpp
void TestApp::isEmpty() const
{
	if (LameQ->empty() == true)
	{
		cout << endl << "Q is empty" << endl << endl;
	}
	else
	{
		cout << endl << "Que is not empty" << endl << endl;
	}

}

//Kontrollerar om k�n �r full genom att kalla p� full() fr�n queue.cpp
void TestApp::isFull() const
{
	
	if (LameQ->full() == true)
	{
		cout << endl << "The queue is full" << endl << endl;
	}
	else
	{
		cout << endl << "The queue is not full" << endl << endl;
	}
}

//Kallar p� max antal element fr�n length() i queue.cpp
void TestApp::maxElementsinQ() const
{
	cout << "Maximum size of Q is: " << LameQ->capacity() << endl << endl;
}

//Kallar p� antalet element fr�n Capacity i queue.cpp
void TestApp::nrElements() const
{
	cout << "Numbah of elements in Q is: " << LameQ->length() << endl << endl;
}

TestApp::TestApp()
{
}

void TestApp::run()
{
	//L�gger till MainMenuObjekten i Menu vectorn
	MenuObj.setMenu_Header("**** Queueueueueu Menu ****");
	MenuObj.addItem("Create queue. (Old will be removed)", true); // 1
	MenuObj.addItem("Enqueue object.", false);			// 2
	MenuObj.addItem("Dequeue object.", false);			// 3
	MenuObj.addItem("Test if queue is empty.", false);	// 4
	MenuObj.addItem("Test if queue is full.", false);	// 5
	MenuObj.addItem("Nr of elements in queue.", false);	// 6
	MenuObj.addItem("Maximum size of queue.", false);	// 7
	MenuObj.addItem("Quit.", true);						// 8


														// Do while true.
	bool reRun = true;
	do
	{
		//Rensar kommandotolken 		
		//cout << string(50, '\n');


		// Skriver ut huvudmenyn
		
		MenuObj.printMenuItems();


		//L�ser in anv�nderens val fr�n funktionen userInput.
		switch (MenuObj.getMenuChoice(MenuObj))
		{ // K�r valt delprogram
		case 1:
			createQueue();
			enableAlternatives();
			break;
		case 2:
			enqueue();
			break;
		case 3:
			dequeue();
			break;
		case 4:
			isEmpty();
			break;
		case 5:
			isFull();
			break;
		case 6:
			nrElements();
			break;
		case 7:
			maxElementsinQ();
			break;
		case 8:
			reRun = false; //Avsluta
			cout << "Now quitting";
			break;
		default:
			cout << endl << "Felaktigt alternativ. V�lj ett alternativ mellan 1-8..." << endl << endl;
			cin.get();
			break;
		}

	} while (reRun == true);
}


// S�tter alla menyalternativ till true
void TestApp::enableAlternatives()
{
	for (auto &item : MenuObj.getMenu_Vector())
	{
		item.setAlternative(true);

	}
}