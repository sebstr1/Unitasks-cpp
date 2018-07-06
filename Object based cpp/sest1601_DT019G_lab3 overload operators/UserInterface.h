// UserInterface.h
#ifndef UserInterfaceH
#define UserInterfaceH
#include "PersonList.h"


class UserInterface
{
	private: 

		PersonList vectorList;
		void UserInterface::menu();
		int UserInterface::userInput();
		void createObjekt(PersonList &vec);
		void printVec();
		void call_sortName(PersonList &vec);
		void call_sortPersnr(PersonList &vec);
		void call_sortShoenr(PersonList &vec);
		void call_writeToFile(PersonList &vec);
		void call_readFromFile(PersonList &vec);
	
	public:
	
		int UserInterface::run();








};
#endif

