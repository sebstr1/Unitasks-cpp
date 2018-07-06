// Definitions.cpp
// Funktionsdefinitioner till Lab4.h
//-----------------------------------------------
#include "SEST1601_DT018G_PROJEKT_CONSTANTS.h"
#include "SEST1601_DT018G_PROJEKT_PROJEKTHEADER.h"

///////////////////////////////////////////////////////////////////////////////
//--------userInput-------------------------//
// Läser in userinput och kontrollerar så att det är en int.
int userInput()
{
	int input = 0;
	cout << endl << "Ditt alternativ? : ";
	cin >> input;
	
	//Kontrollerar så att användaren angav sitt val i form av INT & så att alternativet är 9 eller mindre..
	while (cin.fail() || input <= 0 || input > 9)
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << endl << "Felaktigt alternativ. Du kan endast välja alternativ 1-9. " << endl << endl;
		cout << "Ditt alternativ? : ";
		cin >> input;
	}

	return input;
}
////////////////////////////////////////////////////////////////////////////

//-----Funktion för Menysystemet---------------
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

// Menyval 1 - Lägg till en person i vectorn..
void addPerson(vector<Personer> &vec)
{
	//Rensar kommandotolken
	clearCMD();

	Personer tmpPerson;
	cout << endl << "Lägg till data för personen" << endl << "________________" << endl;
	cout << endl << "Förnamn : ";
	cin.ignore();
	getline(cin, tmpPerson.namn);
	cout << endl << "Efternamn : ";
	getline(cin, tmpPerson.efternamn);
	
//Signatur
////////////// FÖRNAMN //////////////////////////////////////////////////////////////////////////////
	
	//---------Gör om förnamn till lowcase för signaturen----------------------------
	string namnToLowcase = tmpPerson.namn;	
	for (int i = 0; i < namnToLowcase.size(); i++)
	{
		namnToLowcase[i] = tolower(namnToLowcase[i]);
	}
	// Plockar ut de tre första tecknen ur förnamn för signaturen..
	tmpPerson.signatur = namnToLowcase.substr(0, 3);

	//-----------Sätt in "x" om namnet var kortare än 3 bokstäver---------------------------------------
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
	// Plockar ut de tre första tecknen ur efternamn för signaturen..
	tmpPerson.signatur = tmpPerson.signatur + efternamnToLowcase.substr(0, 3);

																			  
//-----------Sätt in "x" om EFTERnamnet var kortare än 3 bokstäver---------------------------------------
	if (efternamnToLowcase.size() < 3)
	{
		for (int i = efternamnToLowcase.size(); i < 3; i++)
			tmpPerson.signatur.append("x");
	}
	
	//Lägger till x om efternamnet innehåller space i sina 3 första bokstäver)
	 for (int i = 0; i < 2; i++)
		if (efternamnToLowcase[i] == ' ')
			tmpPerson.signatur.insert(i+3, "x");

///////////////////////////////////////////////////////////////////////////////////////////////////
	
// För längd

//Läser in strängen 
	cout << endl << "Längd : ";
	
	//Temporär sträng för att elimenera problem med kommatecken
	string tmpLengd;
	getline(cin, tmpLengd);	
		
	//Variabel för while loopen nedan.
	bool korrekt_data = false;
	
	//Kontrollerar så att strängen endast innehåller siffror eller , eller .
	while (korrekt_data == false)
	{	
		//Variabel för om felaktigt tecken hittats.
		bool found_wrongChar = false;
		for (int i = 0; i < tmpLengd.length(); i++)
		{
			//Om felaktigt tecken hittas
			if (!(tmpLengd[i] >= '0' && tmpLengd[i] <= '9' || tmpLengd[i] == '.' || tmpLengd[i] == ','))
			{
				found_wrongChar = true;
			}			
			
		}
		// OM felaktigt tecken inte hittades så var inmatningen av användaren korrekt!
		if (found_wrongChar == false)
		{
			korrekt_data = true;
		}
		
		// Beskriver vad använderen gör för fel.
		if (korrekt_data == false)
		{
			cout << endl << "Error 707: Ange längden i korrekt format (exempelvis 1.6 eller 1,60)" << endl;
			cout << "Längd: ";
			getline(cin, tmpLengd);
			
		}
		
	}

	
	
	//För att stood ska fungera om strängen redan har punkt...
	setlocale(LC_ALL(), "C");

	//Tar bort kommatecken i konverteringen string -> double..
	double tempLengd = stod(tmpLengd);
	
	// Gör så att man kan skriva åäö.
	setlocale(LC_ALL(), "SWEDISH");
	
	//structen.lengd = längden användaren matade in..
	tmpPerson.lengd = tempLengd;
	
	//Pushar tillbaka allt till vectorn.
	vec.push_back(tmpPerson);
}

//Header för datautskirft av vectorn..
void printHeader()
{
	cout << "    ***** Personregister *****" << endl;
	cout << setw(8) << "Nr" << setw(13) << "Signatur" << setw(12) << "Namn" << setw(34) << right << "Längd [m]" << endl;
	cout << setw(8) << "   -------------------------------------------------------------------" << endl;
}

// Utskrifter av Vectorn
void printRegister(vector<Personer> &printVec)
{
	//Rensar kommandotolken
	clearCMD();
	//---------------------------------------------------------------------------- 
	// Skriv registret på skärm 
	//----------------------------------------------------------------------------
	
	cout  << "    Antal personer i listan: " << printVec.size() << endl;
	//Header för utskrift av register.
	printHeader();
	
	
	int raknare = 1;
	int lopNr = 0;
	
	// Skriver ut vectorn tills det 20 namn skrivuts ut eller listan tagit slut.
	// När 20 namn skrivits ut, vänta på att användaren trycker enter, skriv sedan ut 20 till osv..
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
			cout << endl << endl << "Tryck på enter för att visa fler personer...." << endl << endl;
			cin.get();
			printHeader();
			
		}
	}

	cout << endl;
	} while (raknare <= printVec.size());

	cin.ignore();
	cout << endl << endl << "Slut på listan.....";
	cout << endl << endl << "Tryck på enter för att gå tillbaka till menyn..";
	cin.get();
	
}

//Skriver ut datan om signaturen användaren söker på fanns.
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
		//tömmar CMD
		clearCMD();
		cout << endl << "Error 78282: Personen existerar inte i registret.." << endl;
	}

	cout << endl << "Tryck på enter för att gå tillbaka till menyn..";
	cin.get();
		
}

//Delete Person
void deletePerson(vector<Personer> &deleteInVec)
{
	//Tömmer fönstret..
	clearCMD();

	//Läser in vad användaren vill ta bort..
	string delete_detta;
	cout << endl << "Ta bort person med signatur" << endl << "________________" << endl;
	cout << "Ange signaturen : ";
	cin.ignore();
	getline(cin, delete_detta);
	bool got_result = false;

	//Söker igenom signaturerna
	for (int i = 0; i < deleteInVec.size(); i++)
	{
		//Hittades signaturen så ta bort personen helt.
		if (deleteInVec[i].signatur == delete_detta)
		{
			deleteInVec.erase(deleteInVec.begin() + i);
			cout << endl << "Personen har raderats från registret..";
			got_result = true;
		}
		
	}
	//Om personen inte hittades..
	if (got_result == false)
	{
		cout << endl << "Error 29992: Ingen person med signaturen " << delete_detta << " hittades i registret...";
	}

	cout << endl << "Tryck på enter för att gå tillbaka till menyn...";
	cin.get();
}


void sorteraVectorHelvetet(int sorterings_Alternativ, vector<Personer> &VEKTORN)
{
	//ClearCMD..
	clearCMD();
		
		switch (sorterings_Alternativ)
		{ // Sortera på namn, signatur eller längd..
		case namn_sort:
			sort(VEKTORN.begin(), VEKTORN.end(), testNamn);
			
			cout << "Registret har sorterats på namn...";
			cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
			cin.ignore();
			cin.get();
			break;

		case signatur_sort:
			sort(VEKTORN.begin(), VEKTORN.end(), testSignatur);	
			
			cout << "Registret har sorterats på signatur...";
			cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
			cin.ignore();
			cin.get();
			break;

		case lengd_sort:
			sort(VEKTORN.begin(), VEKTORN.end(), testLengd);

			cout << "Registret har sorterats på längd...";
			cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
			cin.ignore();
			cin.get();
			break;

		default: cout << endl << "Felaktigt alternativ. Välj ett alternativ mellan 1-3..." << endl << endl;
			break;
		}
}


//------------------------------------------------------------------------------
// testNamn
//------------------------------------------------------------------------------
// Gör om strängarna till VERSALER & slå ihop efternamn + förnamn för jämförelse.

bool testNamn(Personer string_A, Personer string_B)
{
	// Sakpar två temporära strängar för jämförelse
	string tmpA;
	string tmpB;

	// Gör om efter och förnamn A till Versaler för jämförelse
	transform(string_A.efternamn.begin(), string_A.efternamn.end(), string_A.efternamn.begin(), toupper);
	transform(string_A.namn.begin(), string_A.namn.end(), string_A.namn.begin(), toupper);

	// Slår ihop efternamn + förnamn till en sträng för enkel jämförelse
	tmpA = string_A.efternamn + string_A.namn;

	// Gör om efter och förnamn B till Versaler för jämförelse
	transform(string_B.efternamn.begin(), string_B.efternamn.end(), string_B.efternamn.begin(), toupper);
	transform(string_B.namn.begin(), string_B.namn.end(), string_B.namn.begin(), toupper);

	// Slår ihop efternamn + förnamn till en sträng för enkel jämförelse
	tmpB = string_B.efternamn + " " + string_B.namn;

	// Jämför strängA (efternamn A, förnamn A) < strängB (efternamn B, förnamn A)
	return (tmpA < tmpB);
}


// Jämför signatur A med signatur B och returnerar resultatet
bool testSignatur(const Personer &personA, const Personer &personB)
{
	{	// Jämför signaturerna
		return personA.signatur < personB.signatur;
	}
}



// Jämför längd A & längd B för att sedan returnera resultatet
bool testLengd(const Personer &personA, const Personer &personB)
{
	// Jämför längderna
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
	cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
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

	// Kollar om använderen anger filen med .txt i slutet, lägger annars till det.
	string tmpstring;
	string compare = ".txt";
	tmpstring = fileName.substr(fileName.size()-4, 4);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	//------------------------------------------------------------------------------
	// Öppna filen för skrivning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::out);
	if (vectorFile.is_open()) // Gick det bra att öppna filen
	{
		size_t count = 1;
		for (auto index : saveVec)
		{	//Skriver namn, efternamn, signatur och längd med DELIM mellan varje.
			vectorFile << index.namn << DELIM << index.efternamn << DELIM << index.signatur << DELIM << index.lengd;
			
			if (count++ < saveVec.size()) //Skriv nyradstecken på alla rader utom sista
				vectorFile << endl;
		}
		//Stänger filen.
		vectorFile.close();
	}

	cout << endl << "Registret har sparats till " << fileName;
	cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
	cin.get();
}

//Läs från fil.txt
void readFromFile(vector<Personer> &readToVec)
{
	//ClearCMD
	clearCMD();

	//------------------------------------------------------------------------------
	// Skapa filobjekt (filvariabel) och filnamn
	//------------------------------------------------------------------------------
	fstream vectorFile;

	string fileName;
	cout << "Vad heter filen du vill läsa in från? : ";
	cin.ignore();
	getline(cin, fileName);

	// Kollar om använderen anger filen med .txt i slutet, lägger annars till det.
	string tmpstring;
	string compare = ".txt";
	fileName.substr(fileName.size() - 3, 3);

	if (compare != tmpstring)
	{
		fileName = fileName + compare;
	}

	// Tömmer listan innan inläsning..
	if (!readToVec.empty())
		readToVec.clear();
	//------------------------------------------------------------------------------
	// Öppna filen för läsning
	//------------------------------------------------------------------------------
	vectorFile.open(fileName, ios::in);
	if (vectorFile.is_open()) //Gick det bra att öppna filen
	{
		Personer tmpPerson;
		
		// Temporära strängar att lagra filens olika poster i
		string tmpStr, namn, efternamn, signatur, str_lengd;
		

		// Så länge filen har innehåll
		while (getline(vectorFile, tmpStr))
		{
			// Omvandla filens innehåll till en strängström
			stringstream ss(tmpStr);
						
			// Om det går bra att läsa fram till DELIM  |
			if (getline(ss, namn, '|') &&
				getline(ss, efternamn, '|') &&
				getline(ss, signatur, '|') &&
				getline(ss, str_lengd))
			{
				
				
				// Tilldela värdena till structen pers
				tmpPerson.namn = namn;
				tmpPerson.efternamn = efternamn;
				tmpPerson.signatur = signatur;
				
				//För att stod ska fungera...
				setlocale(LC_ALL, "C");
				tmpPerson.lengd = stod(str_lengd);
				// Gör så att man kan skriva åäö igen..
				setlocale(LC_ALL(), "SWEDISH");
				
		
				// Lägg in data i Vectorn
				readToVec.push_back(tmpPerson);
			}
			else
				// I/O error, om filen inte kunde läsas
				cout << "Filens data kunde inte läsas, kontrollera formatet." << endl;
		}

	}
	else
	{
		cout << endl << endl << "Filen du ville läsa in existerade inte...";
	}
	// Stäng filen
	vectorFile.close();

	cout << endl << "Du har läst in data från filen " << fileName;
	cout << endl << endl << "Tryck på enter för att ladda menyn igen..";
	cin.get();
	
}


// Tömmer CMD fönstret för en bättre känsla
void clearCMD()
{
	cout << string(50, '\n');
}