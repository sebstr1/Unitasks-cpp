// Definitions.cpp
// Funktionsdefinitioner till Lab4.h
//-----------------------------------------------
#include "SEST1601_DT018G_PROJEKT_CONSTANTS.h"
#include "SEST1601_DT018G_PROJEKT_PROJEKTHEADER.h"

///////////////////////////////////////////////////////////////////////////////
//--------userInput-------------------------//
// L�ser in userinput och kontrollerar s� att det �r en int.
int userInput()
{
	int input = 0;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;
	
	//Kontrollerar s� att anv�ndaren angav sitt val i form av INT & s� att alternativet �r 9 eller mindre..
	while (cin.fail() || input <= 0 || input > 9)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast v�lja alternativ 1-9. " << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
	}

	return input;
}
////////////////////////////////////////////////////////////////////////////

//-----Funktion f�r Menysystemet---------------
void meny(vector<Personer> &VEKTOR)
{
	//Rensar kommandotolken
	clearCMD();

	//Header till menyn
	cout << "    Antal personer i listan: " << VEKTOR.size();

	cout << endl << endl << "The Menu That Will Change Your LIFE" << endl;

	//Skriver ut menyn..
	for (int i = 0; i < meny_size; i++)
	{
		cout << vector_meny[i] << endl;
	}	
}
/////////////////////////////////////////////////////////////////////////////

// Menyval 1 - L�gg till en person i vectorn..
void addPerson(vector<Personer> &vec)
{
	//Rensar kommandotolken
	clearCMD();

	Personer tmpPerson;
	cout << endl << "L�gg till data f�r personen" << endl << "________________" << endl;
	cout << endl << "F�rnamn : ";
	cin.ignore();
	getline(cin, tmpPerson.namn);
	cout << endl << "Efternamn : ";
	getline(cin, tmpPerson.efternamn);
	
//Signatur
////////////// F�RNAMN //////////////////////////////////////////////////////////////////////////////
	
	//---------G�r om f�rnamn till lowcase f�r signaturen----------------------------
	string namnToLowcase = tmpPerson.namn;	
	for (int i = 0; i < namnToLowcase.size(); i++)
	{
		namnToLowcase[i] = tolower(namnToLowcase[i]);
	}
	// Plockar ut de tre f�rsta tecknen ur f�rnamn f�r signaturen..
	tmpPerson.signatur = namnToLowcase.substr(0, 3);

	//-----------S�tt in "x" om namnet var kortare �n 3 bokst�ver---------------------------------------
	if (namnToLowcase.size() < 3)
	{
		for (int i = namnToLowcase.size(); i < 3; i++)
			tmpPerson.signatur.append("x");
			
	}


///////////////  EFTERNAMN   /////////////////////////////////////////////////////////////////////

	string efternamnToLowcase = tmpPerson.efternamn;
	for (int i = 0; i < efternamnToLowcase.size(); i++)
	{
		efternamnToLowcase[i] = tolower(efternamnToLowcase[i]);
	}
	// Plockar ut de tre f�rsta tecknen ur efternamn f�r signaturen..
	tmpPerson.signatur = tmpPerson.signatur + efternamnToLowcase.substr(0, 3);

																			  
//-----------S�tt in "x" om EFTERnamnet var kortare �n 3 bokst�ver---------------------------------------
	if (efternamnToLowcase.size() < 3)
	{
		for (int i = efternamnToLowcase.size(); i < 3; i++)
			tmpPerson.signatur.append("x");
	}
	
	//L�gger till x om efternamnet inneh�ller space i sina 3 f�rsta bokst�ver)
	 for (int i = 0; i < 2; i++)
		if (efternamnToLowcase[i] == ' ')
			tmpPerson.signatur.insert(i+3, "x");

///////////////////////////////////////////////////////////////////////////////////////////////////
	
// F�r l�ngd

//L�ser in str�ngen 
	cout << endl << "L�ngd : ";
	
	//Tempor�r str�ng f�r att elimenera problem med kommatecken
	string tmpLengd;
	getline(cin, tmpLengd);	
		
	//Variabel f�r while loopen nedan.
	bool korrekt_data = false;
	
	//Kontrollerar s� att str�ngen endast inneh�ller siffror eller , eller .
	while (korrekt_data == false)
	{	
		//Variabel f�r om felaktigt tecken hittats.
		bool found_wrongChar = false;
		for (int i = 0; i < tmpLengd.length(); i++)
		{
			//Om felaktigt tecken hittas
			if (!(tmpLengd[i] >= '0' && tmpLengd[i] <= '9' || tmpLengd[i] == '.' || tmpLengd[i] == ','))
			{
				found_wrongChar = true;
			}			
			
		}
		// OM felaktigt tecken inte hittades s� var inmatningen av anv�ndaren korrekt!
		if (found_wrongChar == false)
		{
			korrekt_data = true;
		}
		
		// Beskriver vad anv�nderen g�r f�r fel.
		if (korrekt_data == false)
		{
			cout << endl << "Error 707: Ange l�ngden i korrekt format (exempelvis 1.6 eller 1,60)" << endl;
			cout << "L�ngd: ";
			getline(cin, tmpLengd);
			
		}
		
	}

	
	
	//F�r att stood ska fungera om str�ngen redan har punkt...
	setlocale(LC_ALL(), "C");

	//Tar bort kommatecken i konverteringen string -> double..
	double tempLengd = stod(tmpLengd);
	
	// G�r s� att man kan skriva ���.
	setlocale(LC_ALL(), "SWEDISH");
	
	//structen.lengd = l�ngden anv�ndaren matade in..
	tmpPerson.lengd = tempLengd;
	
	//Pushar tillbaka allt till vectorn.
	vec.push_back(tmpPerson);
}

//Header f�r datautskirft av vectorn..
void printHeader()
{
	cout << "    ***** Personregister *****" << endl;
	cout << setw(8) << "Nr" << setw(13) << "Signatur" << setw(12) << "Namn" << setw(34) << right << "L�ngd [m]" << endl;
	cout << setw(8) << "   -------------------------------------------------------------------" << endl;
}

// Utskrifter av Vectorn
void printRegister(vector<Personer> &printVec)
{
	//Rensar kommandotolken
	clearCMD();
	//---------------------------------------------------------------------------- 
	// Skriv registret p� sk�rm 
	//----------------------------------------------------------------------------
	
	cout  << "    Antal personer i listan: " << printVec.size() << endl;
	//Header f�r utskrift av register.
	printHeader();
	
	
	int raknare = 1;
	int lopNr = 0;
	
	// Skriver ut vectorn tills det 20 namn skrivuts ut eller listan tagit slut.
	// N�r 20 namn skrivits ut, v�nta p� att anv�ndaren trycker enter, skriv sedan ut 20 till osv..
	do
	{
	for (auto PersonRegister : printVec)
	{
		cout << "      " << setw(7) << left << to_string(raknare++) + ".";
		cout << setw(16) << left << PersonRegister.signatur;
		cout << setw(25) << left << PersonRegister.namn + " " + PersonRegister.efternamn;
		cout << setw(13) << right << fixed << setprecision(2) << PersonRegister.lengd << endl;
		lopNr++;
		
		if (lopNr == 20)
		{
			lopNr = 0;
			cin.ignore();
			cout << endl << endl << "Tryck p� enter f�r att visa fler personer...." << endl << endl;
			cin.get();
			printHeader();
			
		}
	}

	cout << endl;
	} while (raknare <= printVec.size());

	cin.ignore();
	cout << endl << endl << "Slut p� listan.....";
	cout << endl << endl << "Tryck p� enter f�r att g� tillbaka till menyn..";
	cin.get();
	
}

//Skriver ut datan om signaturen anv�ndaren s�ker p� fanns.
void findPerson(vector<Personer> &findInVec)
{
	//Rensar kommandotolken
	clearCMD();

	cout << endl;
	string hitta_detta;
	cout << endl << "Hitta en person" << endl << "________________" << endl;
	cout << "Ange signaturen : ";
	cin.ignore();
	getline(cin, hitta_detta);
	bool got_result = false;
	
	//Letar signaturen i vectorn
	printHeader();
	for (int i = 0; i < findInVec.size(); i++)
	
	{
		//Om resultat hittades skriv ut den personens data.
		if (findInVec[i].signatur == hitta_detta)
		{
			cout << "      " << setw(7) << left << to_string(i) + "." << left;
			cout << setw(16) << left << findInVec[i].signatur;
			cout << setw(25) << left << findInVec[i].namn + " " + findInVec[i].efternamn;
			cout << setw(13) << right << fixed << setprecision(2) << findInVec[i].lengd << endl;
			got_result = true;
		}
	}
	// Om inget resultat fanns..
	if (got_result == false)
	{
		//t�mmar CMD
		clearCMD();
		cout << endl << "Error 78282: Personen existerar inte i registret.." << endl;
	}

	cout << endl << "Tryck p� enter f�r att g� tillbaka till menyn..";
	cin.get();
		
}

//Delete Person
void deletePerson(vector<Personer> &deleteInVec)
{
	//T�mmer f�nstret..
	clearCMD();

	//L�ser in vad anv�ndaren vill ta bort..
	string delete_detta;
	cout << endl << "Ta bort person med signatur" << endl << "________________" << endl;
	cout << "Ange signaturen : ";
	cin.ignore();
	getline(cin, delete_detta);
	bool got_result = false;

	//S�ker igenom signaturerna
	for (int i = 0; i < deleteInVec.size(); i++)
	{
		//Hittades signaturen s� ta bort personen helt.
		if (deleteInVec[i].signatur == delete_detta)
		{
			deleteInVec.erase(deleteInVec.begin() + i);
			cout << endl << "Personen har raderats fr�n registret..";
			got_result = true;
		}
		
	}
	//Om personen inte hittades..
	if (got_result == false)
	{
		cout << endl << "Error 29992: Ingen person med signaturen " << delete_detta << " hittades i registret...";
	}

	cout << endl << "Tryck p� enter f�r att g� tillbaka till menyn...";
	cin.get();
}


void sorteraVectorHelvetet(int sorterings_Alternativ, vector<Personer> &VEKTORN)
{
	//ClearCMD..
	clearCMD();
		
		switch (sorterings_Alternativ)
		{ // Sortera p� namn, signatur eller l�ngd..
		case namn_sort:
			sort(VEKTORN.begin(), VEKTORN.end(), testNamn);
			
			cout << "Registret har sorterats p� namn...";
			cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
			cin.ignore();
			cin.get();
			break;

		case signatur_sort:
			sort(VEKTORN.begin(), VEKTORN.end(), testSignatur);	
			
			cout << "Registret har sorterats p� signatur...";
			cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
			cin.ignore();
			cin.get();
			break;

		case lengd_sort:
			sort(VEKTORN.begin(), VEKTORN.end(), testLengd);

			cout << "Registret har sorterats p� l�ngd...";
			cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
			cin.ignore();
			cin.get();
			break;

		default: cout << endl << "Felaktigt alternativ. V�lj ett alternativ mellan 1-3..." << endl << endl;
			break;
		}
}


//------------------------------------------------------------------------------
// testNamn
//------------------------------------------------------------------------------
// G�r om str�ngarna till VERSALER & sl� ihop efternamn + f�rnamn f�r j�mf�relse.

bool testNamn(Personer string_A, Personer string_B)
{
	// Sakpar tv� tempor�ra str�ngar f�r j�mf�relse
	string tmpA;
	string tmpB;

	// G�r om efter och f�rnamn A till Versaler f�r j�mf�relse
	transform(string_A.efternamn.begin(), string_A.efternamn.end(), string_A.efternamn.begin(), toupper);
	transform(string_A.namn.begin(), string_A.namn.end(), string_A.namn.begin(), toupper);

	// Sl�r ihop efternamn + f�rnamn till en str�ng f�r enkel j�mf�relse
	tmpA = string_A.efternamn + string_A.namn;

	// G�r om efter och f�rnamn B till Versaler f�r j�mf�relse
	transform(string_B.efternamn.begin(), string_B.efternamn.end(), string_B.efternamn.begin(), toupper);
	transform(string_B.namn.begin(), string_B.namn.end(), string_B.namn.begin(), toupper);

	// Sl�r ihop efternamn + f�rnamn till en str�ng f�r enkel j�mf�relse
	tmpB = string_B.efternamn + " " + string_B.namn;

	// J�mf�r str�ngA (efternamn A, f�rnamn A) < str�ngB (efternamn B, f�rnamn A)
	return (tmpA < tmpB);
}


// J�mf�r signatur A med signatur B och returnerar resultatet
bool testSignatur(const Personer &personA, const Personer &personB)
{
	{	// J�mf�r signaturerna
		return personA.signatur < personB.signatur;
	}
}



// J�mf�r l�ngd A & l�ngd B f�r att sedan returnera resultatet
bool testLengd(const Personer &personA, const Personer &personB)
{
	// J�mf�r l�ngderna
	return personA.lengd > personB.lengd;
}
/////////////////////////////////////////////////////////////////


//Slumpar registret i vectorn......
void SLUMPA(vector<Personer> &slumpaVECTOR)
{
	//ClearCMD
	clearCMD();

	//Initierar slumpmotorn
	default_random_engine generator{ random_device{}() };

	//Slumpar vectorn.
	shuffle(slumpaVECTOR.begin(), slumpaVECTOR.end(), generator);

	cout << "Registret har slumpats! Ha en fortsatt bra dag.";
	cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
	cin.ignore();
	cin.get();

	
}




//Skriv till fil.txt
void saveToFile(vector<Personer> &saveVec)
{
	//ClearCMD
	clearCMD();
	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel) och filnamn
	//------------------------------------------------------------------------------
	fstream vectorFile;
	
	string fileName;
	cout << "Vad vil du att filen skall heta? : ";
	cin.ignore();
	getline(cin, fileName);

	// Kollar om anv�nderen anger filen med .txt i slutet, l�gger annars till det.
	string tmpstring;
	string compare = ".txt";
	tmpstring = fileName.substr(fileName.size()-4, 4);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	//------------------------------------------------------------------------------
	// �ppna filen f�r skrivning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::out);
	if (vectorFile.is_open()) // Gick det bra att �ppna filen
	{
		size_t count = 1;
		for (auto index : saveVec)
		{	//Skriver namn, efternamn, signatur och l�ngd med DELIM mellan varje.
			vectorFile << index.namn << DELIM << index.efternamn << DELIM << index.signatur << DELIM << index.lengd;
			
			if (count++ < saveVec.size()) //Skriv nyradstecken p� alla rader utom sista
				vectorFile << endl;
		}
		//St�nger filen.
		vectorFile.close();
	}

	cout << endl << "Registret har sparats till " << fileName;
	cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
	cin.get();
}

//L�s fr�n fil.txt
void readFromFile(vector<Personer> &readToVec)
{
	//ClearCMD
	clearCMD();

	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel) och filnamn
	//------------------------------------------------------------------------------
	fstream vectorFile;

	string fileName;
	cout << "Vad heter filen du vill l�sa in fr�n? : ";
	cin.ignore();
	getline(cin, fileName);

	// Kollar om anv�nderen anger filen med .txt i slutet, l�gger annars till det.
	string tmpstring;
	string compare = ".txt";
	fileName.substr(fileName.size() - 3, 3);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	// T�mmer listan innan inl�sning..
	if (!readToVec.empty())
		readToVec.clear();
	//------------------------------------------------------------------------------
	// �ppna filen f�r l�sning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::in);
	if (vectorFile.is_open()) //Gick det bra att �ppna filen
	{
		Personer tmpPerson;
		
		// Tempor�ra str�ngar att lagra filens olika poster i
		string tmpStr, namn, efternamn, signatur, str_lengd;
		

		// S� l�nge filen har inneh�ll
		while (getline(vectorFile, tmpStr))
		{
			// Omvandla filens inneh�ll till en str�ngstr�m
			stringstream ss(tmpStr);
						
			// Om det g�r bra att l�sa fram till DELIM  |
			if (getline(ss, namn, '|') &&
				getline(ss, efternamn, '|') &&
				getline(ss, signatur, '|') &&
				getline(ss, str_lengd))
			{
				
				
				// Tilldela v�rdena till structen pers
				tmpPerson.namn = namn;
				tmpPerson.efternamn = efternamn;
				tmpPerson.signatur = signatur;
				
				//F�r att stod ska fungera...
				setlocale(LC_ALL, "C");
				tmpPerson.lengd = stod(str_lengd);
				// G�r s� att man kan skriva ��� igen..
				setlocale(LC_ALL(), "SWEDISH");
				
		
				// L�gg in data i Vectorn
				readToVec.push_back(tmpPerson);
			}
			else
				// I/O error, om filen inte kunde l�sas
				cout << "Filens data kunde inte l�sas, kontrollera formatet." << endl;
		}

	}
	else
	{
		cout << endl << endl << "Filen du ville l�sa in existerade inte...";
	}
	// St�ng filen
	vectorFile.close();

	cout << endl << "Du har l�st in data fr�n filen " << fileName;
	cout << endl << endl << "Tryck p� enter f�r att ladda menyn igen..";
	cin.get();
	
}


// T�mmer CMD f�nstret f�r en b�ttre k�nsla
void clearCMD()
{
	cout << string(50, '\n');
}