// HousingQ.h
#ifndef HousingQH
#define HousingQH

#include "queue.h"
#include <string>



class HousingQ
{
	private:
		QList the_que;
		int HousingQ::Que_size();

		int pers;
		string FileName;
		
		
		void HousingQ::menu();
		int HousingQ::userInput();
		
		
/*Ställ en person sist i kön
o Låt användaren mata in data från tangentbordet*/
		void HousingQ::addPerson(QList &person_objekt);

			
/* Erbjud en person bostad, d.v.s.ta bort en person från början av kön.
o Skriv ut data för en person som blev erbjuden bostad.
o Skriv meddelande om kön är tom.*/
		void HousingQ::bostad_erbjuden();


/* Skriv ut hela bostadskön tillsammans med totalt antal personer som står i bostadskön.
o Vid varje person ska dess placering i bostadskön anges.
o Skriv meddelande om kön är tom.*/
		void HousingQ::printQUE();


/* Skriv ut data om en person på skärmen.
o Sökning efter personen görs med personnummer som söknyckel.
o Skriv också ut personens placering i bostadskön.
o Skriv meddelande om kön är tom.*/
		void HousingQ::stalkPerson();


/* Ta bort(stryk) en person från bostadskön.
o Identifiera personen med personnummer.
o Skriv meddelande om kön är tom.*/
		void HousingQ::deletePerson();


//Läs in Från fil
		void HousingQ::ReadFile();

/* Spara kön på fil*/
		void HousingQ::WriteFile();
	
	public:
		
		int HousingQ::run();
		HousingQ();







};
#endif

