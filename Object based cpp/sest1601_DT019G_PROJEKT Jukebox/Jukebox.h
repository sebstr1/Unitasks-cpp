// Jukebox.h
#ifndef JukeboxH
#define JukeboxH


#include "Album.h"
#include "Menu.h"
#include "Time.h"
#include "queue.h"
#include "usefulFunctions.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

const string FileName = "jukebox.txt";

class Jukebox
{
	private:
		vector <Album> AlbumVector;
		
		//Menyobjekt
		Menu MainMenuobj;
		Menu FileMenuobj;	
		Menu PrintMenuobj;
		Menu PlayMenuobj;

		
		void FileMenu();				 // Huvudmeny val 1
		//Undermeny till FileMenu
		void OpenFile();				 // Menyval 1 i FileMenu
		void SaveFile();				 // Menyval 2 i FileMenu
		
		void addAlbum();				 // Huvudmeny val 2
		
		void DeleteAlbum();				 // Huvudmeny val 3
		
		void PrintMenu();				 // Huvudmeny val 4
		//Undermeny till PrintMenu
		void PrintAlbum();				 // Menyval 1 i PrintMenu
		void PrintAlbumsByName();		 // Menyval 2 i PrintMenu
		void PrintAlbumsByTotTime();	 // Menyval 3 i PrintMenu
		void PrintAlbumTitleByName();	 // Menyval 4 i PrintMenu
		void PrintSimpleByTotTime();	 // Menyval 5 i PrintMenu
		

		void PlayMenu();				// Menyval 5 i huvudmenyn

		//Funktioner

		// Funktion som skriver ut Alla album och antingen all information eller en simpel version beroende på bool.
		void PrintAlbumVectorAllInfo(bool fullInfo);		

		// Funktion som sätter alla alternativ till enabled (true) när fil öppnats.
		void enableAlternatives();
	
	public:
		void run();
		Jukebox();	
	


};
#endif

