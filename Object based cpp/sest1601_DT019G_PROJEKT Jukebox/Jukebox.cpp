// Jukebox.cpp

#include "Jukebox.h"

using namespace std;


//------------------------------------------------------------------------------
// Definition av medlemsfunktioner
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//Förvald konstruktor (Default constructor)
//------------------------------------------------------------------------------
Jukebox::Jukebox()
{
	MainMenuobj.setMenu_Header("**** JUKEBOX ****");
		//Lägger till MainMenuObjekten i MainMenu vectorn
	MainMenuobj.addItem("File...", true);			// 1
	MainMenuobj.addItem("Add an album", false);	// 2
	MainMenuobj.addItem("Delete an album", false); // 3
	MainMenuobj.addItem("Print...", false);		// 4
	MainMenuobj.addItem("Play...", false);			// 5
	MainMenuobj.addItem("Exit", true);				// 6

	FileMenuobj.setMenu_Header("**** FILE ****");
	//Lägger till FileMenuObjekten i Filemenuobj vectorn
	FileMenuobj.addItem("Open file", true);		    //1
	FileMenuobj.addItem("Save File", false);	    //2
	FileMenuobj.addItem("Back to main menu", true); //3

	PrintMenuobj.setMenu_Header("**** PRINT ****");
	//Lägger till PrintMenuObjekten i vectorn
	PrintMenuobj.addItem("Print one album", false);						    // 1
	PrintMenuobj.addItem("Print all sorted by album name", false);          // 2
	PrintMenuobj.addItem("Print all sorted by album total time", false);    // 3
	PrintMenuobj.addItem("Print simple sorted by album name", false);       // 4
	PrintMenuobj.addItem("Print simple sorted by album total time", false); // 5
	PrintMenuobj.addItem("Back to main menu", false);					    // 6

	PlayMenuobj.setMenu_Header("**** Play ****");
	//Lägger till PrintMenuObjekten i vectorn
	PlayMenuobj.addItem("Create playlist", false);						   // 1
	PlayMenuobj.addItem("Play playlist", false);						   // 2
	PlayMenuobj.addItem("Crate Random playlist", false);				   // 3
	PlayMenuobj.addItem("Return to main menu", false);					   // 4
	

}


//Härifrån körs huvudprogrammet
void Jukebox::run()
{
	// Do while true.
	bool reRun = true;
	do
	{
		// Skriver ut huvudmenyn
		MainMenuobj.printMenuItems();

		//Läser in använderens val från funktionen userInput.
		switch (MainMenuobj.getMenuChoice(MainMenuobj))
		{ // Kör valt delprogram
		case 1:
			FileMenu();		//Anropar undermenyn FileMenu
			break;
		case 2:
			addAlbum();		//Anropar funktionen addAlbum
			break;
		case 3:
			DeleteAlbum();	//Anropar funktionen DeleteAlbum
			break;
		case 4:
			PrintMenu();	//Anropar undermenyn PrintMenu
			break;
		case 5:
			PlayMenu();
			break;
		case 6:
			reRun = false;  //Avsluta
			cout << endl << endl << "The program is being terminated";
			break;
		default:
			cout << endl << "Felaktigt alternativ. Välj ett alternativ mellan 1-6..." << endl << endl;
			break;
		}

	} while (reRun == true);

	cout << endl << endl << "Press enter to exit:  ";
	cin.get();
}


//----------------------------------------------
//----------------------------------------------
//Undermeny till Filemenu (alternativ 1 i huvudmenyn)
//------------------------------------------------
void Jukebox::FileMenu()
{
	// Do while true.
	bool reRunFileMenu = true;
	do
	{
		// Skriver ut filmenyn
		FileMenuobj.printMenuItems();

		//Läser in använderens val från funktionen userInput.
		switch (FileMenuobj.getMenuChoice(FileMenuobj))
		{ // Kör valt delprogram
		case 1:
			OpenFile();				//Anropar funktionen OpenFile
			enableAlternatives();	//Anropar funktionen enableAlternatives
			break;
		case 2:
			SaveFile();				//Anropar funktionen SaveFile
			break;
		case 3:
			reRunFileMenu = false; //Återgår till huvudmenyn
			break;
		default:
			cout << endl << "Felaktigt alternativ. Välj ett alternativ mellan 1-3..." << endl << endl;
			break;
		}

	} while (reRunFileMenu == true);
}

// Sätter alla menyalternativ till true
void Jukebox::enableAlternatives()
{
	for (auto &item : MainMenuobj.getMenu_Vector())
	{
		item.setAlternative(true);

	}

	for (auto &item : FileMenuobj.getMenu_Vector())
	{
		item.setAlternative(true);
	}

	for (auto &item : PrintMenuobj.getMenu_Vector())
	{
		item.setAlternative(true);
	}

	for (auto &item : PlayMenuobj.getMenu_Vector())
	{
		item.setAlternative(true);
	}
}

//-------------------------------------------------------------------------------------------------------
// Alternativ 1 i undermenyn file "Open file"
//---------------------------------------------------------------------------------------------------------
////Read from file
void Jukebox::OpenFile()
{
	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel)
	//------------------------------------------------------------------------------
	fstream JukeboxFile;
	if (AlbumVector.empty() != true)
	{
		//Tömmr vectorn
		AlbumVector.clear();
	}
		
	//------------------------------------------------------------------------------
	// Öppna filen för läsning
	//------------------------------------------------------------------------------
	JukeboxFile.open(FileName, ios::in);
	if (JukeboxFile.is_open()) //Gick det bra att öppna filen
	{
		Album obj;

		while (JukeboxFile >> obj)
		{
			AlbumVector.push_back(obj);
			
		}

	}
	JukeboxFile.close();

	cout << endl << endl << "Filen Har lästs in" << endl;
}

//Sparar till fil
void Jukebox::SaveFile()
{
	fstream JukeboxFile;

	//Öppnar filen
	JukeboxFile.open(FileName, ios::out);
	if (JukeboxFile.is_open()) //Gick bra att öppna filen
	{
		for (auto item : AlbumVector)
		{
			JukeboxFile << item << endl;
		}

		JukeboxFile.close();
	}

	cout << endl << "Filen har sparats till " << FileName;
}

//MenyAlternativ 2 I huvudmenyn
void Jukebox::addAlbum()
{
	Album tmpAlbum;
	cout << "Enter name for the new album: ";
	string tmp;
	getline(cin, tmp);
	//Gör om till lowcase för att jämföra oberende av versaler/gemener
	toLowerFunction(tmp);
	string dupe = tmp;
	
	//Kontrollerar om användarens nya albumnamn existerar i vectorn redan
	for (auto i : AlbumVector)
	{
		if (toLowerFunction(i.getAlbumNamn()) == dupe)
		{
			cout << endl << "Duplicate found";
			return;
		}
	}

	//Om albumet Inte fanns redan
	
	cout << endl << endl;
	//Sätter albumnamnet
	tmpAlbum.setAlbumNamn(tmp);
	bool addmoresongs = true;
	
	//Add more songs while
	do
	{
		Song tempsong;
		cout << "Enter name of song: ";
		getline(cin, tmp);
		cout << endl << endl;
		//Sätter namnet på songen
		tempsong.setSongTitel(tmp);
		
		cout << "Enter artist name: ";
		getline(cin, tmp);
		cout << endl << endl;
		//Sätter namnet på artisten
		tempsong.setSongArtist(tmp);
		
		cout << "Enter song length in seconds: ";
		
		Time seconds;
		cin >> seconds;
		cin.get();
		cout << endl << endl;
		//Sätter namnet på artisten
		tempsong.setSongLengd(seconds);

		tmpAlbum.addSong(tempsong);

		AlbumVector.push_back(tmpAlbum);


		cout << "Do you want to add more songs? (yes/no) ";
		string choice;
		getline(cin, choice);
		cout << endl;

		if (choice == "no")
		{
			addmoresongs = false;
			return;
		}


	} while (addmoresongs = true);

	
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

//Menyval 3 I huvudmenyn
void Jukebox::DeleteAlbum()
{
	//Initierar söksträng
	string DeleteThisAlbum;
	
	cout << "Enter name of album you want to print: ";
	getline(cin, DeleteThisAlbum);
	string original = DeleteThisAlbum;
	//Gör om söksträngen till lowercase
	DeleteThisAlbum = toLowerFunction(DeleteThisAlbum);

	string tempp;


	//Letar upp albumet genom att jämföra aktuellt album med söksträngen i lowercase
	auto it = find_if(AlbumVector.begin(), AlbumVector.end(),
		[DeleteThisAlbum](const Album &b1)
	{
		
		//Kontrollerar om aktuellt album i lowercase är == albumet som eftersöks		
		return toLowerFunction(b1.getAlbumNamn()) == DeleteThisAlbum;
	});

	Album deleted = *it;
	//	
	if (it != AlbumVector.end())
	{
		AlbumVector.erase(it);
		cout << "Albumet " << deleted.getAlbumNamn() << " har tagits bort.." << endl << endl;
		
		return;
	}

	else
	{
		cout << "Albumet " << original << " fins inte i listan" << endl << endl;
		return;
	}


}

//------------------------------------------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------
//Menyutskrift av undermeny till Alternativ 4 (Print...)
//----------------------------------------------------------
void Jukebox::PrintMenu()
{
	// Do while true.
	bool reRunPrintMenu = true;
	do
	{
		// Skriver ut filmenyn
		PrintMenuobj.printMenuItems();

		//Läser in använderens val från funktionen userInput.
		switch (PrintMenuobj.getMenuChoice(PrintMenuobj))
		{ // Kör valt delprogram
		case 1:
			PrintAlbum();				//Anropar PrintAlbum
			break;
		case 2:
			PrintAlbumsByName();		//Anropar PrintAlbumsByName
			break;
		case 3:
			PrintAlbumsByTotTime();		//Anropar PrintAlbumsByTotTime
			break;
		case 4:
			PrintAlbumTitleByName();	//Anropar PrintAlbumsByTitle
			break;
		case 5:
			PrintSimpleByTotTime();		//Anropar PrintSimpleByTotTime
			break;
		case 6:
			reRunPrintMenu = false;		//Går tillbaka till huvudmenyn
			break;			
		default:
			cout << endl << "Felaktigt alternativ. Välj ett alternativ mellan 1-6..." << endl << endl;
			break;
		}

	} while (reRunPrintMenu == true);
}



//----------------------------------------------
//----------------------------------------------
//Alternativ 1 i undermenyn Print "Print one album"
//------------------------------------------------
void Jukebox::PrintAlbum()
{
	//Initierar söksträng
	string findThisAlbum;
	cout << "Enter name of album you want to print: ";
	getline(cin, findThisAlbum);
	
	//Gör om söksträngen till lowercase
	findThisAlbum = toLowerFunction(findThisAlbum);
	

	//Letar upp albumet genom att jämföra aktuellt album med söksträngen i lowercase
	auto it = find_if(AlbumVector.begin(), AlbumVector.end(),
		[findThisAlbum](const Album &b1) 
	{
		//Kontrollerar om aktuellt album i lowercase är == albumet som eftersöks		
		return toLowerFunction(b1.getAlbumNamn()) == findThisAlbum;	
	});

	//	
	if (it != AlbumVector.end())
	{
		Album album = *it;
		Album calcTime = *it;
		Time tot;
		//Loop för att räkna ut albumets totala tid
		for (auto i = 0; i < calcTime.Number_of_Songs(); i++)
		{
			tot = tot + calcTime.getVector_of_Songs()[i].getSongLengd();
		}
		


		//Skriver ut Header
		cout << endl << endl;
		cout << "===================================================================================" << endl;
		cout << "Album: " << setfill(' ') << left << setw(50) << album.getAlbumNamn() << right << setw(20) << "Total Playtime:";
		if (tot.getTimmar() <= 0)
		{

			cout << " " << tot.getMinuter() << ":" << setw(2) << setfill('0') << tot.getSekunder() << endl;
		}
		else
		{
			cout << " " << tot.getTimmar() << ":" << setw(2) << setfill('0') << tot.getMinuter() << setw(2) << setfill('0') << tot.getSekunder() << endl;
		}
		cout << "===================================================================================" << endl;


		// Skriver ut album
		cout << setfill(' ');
		cout << left << setw(50) << "Title" << setw(15) << "Artist" << right << setw(15) << "Length" << endl;
		// Skriver ut album
		for (auto i = 0; i < album.Number_of_Songs(); i++)
		{
			cout << setfill(' ');
			cout << left << setw(50) << album.getVector_of_Songs()[i].getSongTitel();
			cout << setw(15) << album.getVector_of_Songs()[i].getSongArtist();
			Time t = album.getVector_of_Songs()[i].getSongLengd();


			// Skriver ut tid beroende på om timmar <=0 eller >0
			if (t.getTimmar() <= 0)
			{

				cout << right << setw(10) << t.getMinuter() << ":" << setw(2) << setfill('0') << t.getSekunder() << endl;
			}
			else
			{
				cout << right << setw(10) << t.getTimmar() << ":" << setw(2) << setfill('0') << t.getMinuter() << ":" << setw(2) << setfill('0') << t.getSekunder() << endl;
			}
		}
		
	}

	else
		cout << endl << findThisAlbum << " does not exist" << endl;

	cout << "===================================================================================" << endl;

	
}
//=====================================================================================

//Menyval 2 i printmenu
void Jukebox::PrintAlbumsByName()
{
	
	//Sorterar AlbumVectorn efter Albumnamn
	sort(AlbumVector.begin(), AlbumVector.end(), [](Album a, Album b)
	{
		return toLowerFunction(a.getAlbumNamn()) < toLowerFunction(b.getAlbumNamn());
	});

	//Skriver ut hela albumvectorn (all information)
	PrintAlbumVectorAllInfo(true);

}

//Menyval 3 i printmenu
void Jukebox::PrintAlbumsByTotTime()
{
	//Sorterar AlbumVectorn efter albums totala tid (längst albumtid först)
	sort(AlbumVector.begin(), AlbumVector.end(), [](Album a, Album b)
	{
		return !(a.AlbumLengd() < b.AlbumLengd());
	});

	//Skriver ut hela albumvectorn (all information)
	PrintAlbumVectorAllInfo(true);
}


//Menyval 4 i printmenu
void Jukebox::PrintAlbumTitleByName()
{
	//Sorterar AlbumVectorn efter Albumnamn
	sort(AlbumVector.begin(), AlbumVector.end(), [](Album a, Album b)
	{
		return toLowerFunction(a.getAlbumNamn()) < toLowerFunction(b.getAlbumNamn());
	});

	cout << endl << "Printing Album names... " << endl << endl;
	//Skriver ut album
	for_each(AlbumVector.begin(), AlbumVector.end(), [](Album a)
	{
		cout << a.getAlbumNamn() << endl;
	});

	cout << endl << endl;
}




//Menyval 5 i pritmenu
void Jukebox::PrintSimpleByTotTime()
{
	//Sorterar AlbumVectorn efter albums totala tid (längsta först)
	sort(AlbumVector.begin(), AlbumVector.end(), [](Album a, Album b)
	{
		return !(a.AlbumLengd() < b.AlbumLengd());
	});

	//Skriver ut hela albumvectorn (inte all information (false))
	PrintAlbumVectorAllInfo(false);
}

//Funktion som skriver ut alla album i vectorn i ordningen dessa ligger just nu.
void Jukebox::PrintAlbumVectorAllInfo(bool fullInfo)
{
	//Går igenom vectorn, räknar ut albumets totala tid och lagrar detta
	for (auto item : AlbumVector)
	{
		Time tot;
		//Loop för att räkna ut albumets totala tid
		for (auto i = 0; i < item.Number_of_Songs(); i++)
		{
			tot = tot + item.getVector_of_Songs()[i].getSongLengd();
		}

		//Skriver ut Header
		cout << endl << endl << "===================================================================================" << endl;
		cout << "Album: " << setfill(' ') << left << setw(50) << item.getAlbumNamn() << right << setw(20) << "Total Playtime:";
		if (tot.getTimmar() <= 0)
		{
			
			cout << " " << tot.getMinuter() << ":" << setw(2) << setfill('0') << tot.getSekunder() << endl;
		}
		else
		{
			cout << " " << tot.getTimmar() << ":" << setw(2) << setfill('0') << tot.getMinuter() << ":" << setw(2) << setfill('0') << tot.getSekunder() << endl;
		}
		cout << "===================================================================================" << endl;
		
		//Om all info skall skrivas ut om albumet
		if (fullInfo == true)
		{
			cout << setfill(' ');
			cout  << left << setw(50) << "Title" << setw(15)  << "Artist" << right << setw(15) << "Length" << endl;
			// Skriver ut album
			for (auto i = 0; i < item.Number_of_Songs(); i++)
			{
				cout << setfill(' ');
				cout << left << setw(50) << item.getVector_of_Songs()[i].getSongTitel();
				cout << setw(15) << item.getVector_of_Songs()[i].getSongArtist();
				Time t = item.getVector_of_Songs()[i].getSongLengd();

				// Skriver ut tid beroende på om antalet timmar >0 eller <=0
				if (t.getTimmar() <= 0)
				{
					
					cout << right << setw(10) << t.getMinuter() << ":" << setw(2) << setfill('0') << t.getSekunder() << endl;
				}
				else
				{
					cout << right << setw(10) << t.getTimmar() << ":" << setw(2) << setfill('0') << t.getMinuter() << ":" << setw(2) << setfill('0') << t.getSekunder() << endl;
				}
			}
		}

		if (fullInfo == true)
		{
			cout << "===================================================================================" << endl;
			cout << "###################################################################################" << endl;
		}		
	}
}


//Undermeny Playmenu

void Jukebox::PlayMenu()
{

	// Do while true.
	bool reRunPlayMenu = true;
	do
	{
		// Skriver ut filmenyn
		PlayMenuobj.printMenuItems();

		//Läser in använderens val från funktionen userInput.
		switch (PlayMenuobj.getMenuChoice(PlayMenuobj))
		{ // Kör valt delprogram
		case 1:
			cout << "Creating playlist...." << endl;
			break;
		case 2:
			cout << "Play Playlist......." << endl;
			break;
		case 3:
			cout << "Random Playlist...." << endl;
			break;
		case 4:
			reRunPlayMenu = false; //Återgår till huvudmenyn
			break;
		default:
			cout << endl << "Felaktigt alternativ. Välj ett alternativ mellan 1-4..." << endl << endl;
			break;
		}

	} while (reRunPlayMenu == true);
}