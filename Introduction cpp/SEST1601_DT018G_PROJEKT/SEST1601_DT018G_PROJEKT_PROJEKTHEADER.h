// SEST1601_DT018G_PROJEKT_PROJEKTHEADER.H
// Funktiosprototyper
// Sebastian Strindlund 2016-12-12
// V1.0
//----------------------------------------------------------------------------------------

#ifndef SEST1601_DT018G_PROJEKT_PROJEKTHEADERH
#define SEST1601_DT018G_PROJEKT_PROJEKTHEADERH
#include "SEST1601_DT018G_PROJEKT_CONSTANTS.h"


//---------------------------------------------------------------------------//
//Prototyp för Main

//Skriv ut menyn
void meny(vector<Personer>&);

//Töm kommandotolken
void clearCMD();

//Kontrollera använderaens input
int userInput();

//LÄgg till person.
void addPerson(vector<Personer>&);

//Header
void printHeader();
//Skriv ut registret
void printRegister(vector<Personer>&);

//Hitta person
void findPerson(vector<Personer>&);
// Ta bort person
void deletePerson(vector<Personer>&);



//SorteringsPrototyper
void sorteraVectorHelvetet(int sorterigs_Alternativ, vector<Personer>&);
bool testNamn(Personer string_A, Personer string_B);
bool testSignatur(const Personer &personA, const Personer &personB);
bool testLengd(const Personer &personA, const Personer &personB);
/////////////////////////////////////////////////////////////////////////

//Slumpning
void SLUMPA(vector<Personer>&);

// Save & read to/from file
void saveToFile(vector<Personer>&);
void readFromFile(vector<Personer>&);







#endif