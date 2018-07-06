// LAB 1 v 1.0
// Pekare
// Sebastian Strindlund 2017-01-18
//------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include <time.h> // inkluderar tid och datum mm (så att åäö ska funka)
using namespace std;size_t choose_arraysize();void insert_random(int a_array[], int size);void print_array(int a_array[], int size);//------------------------------------------------------------------------------
int main()
{
	//Använderen sätter arraystorleken i funktionen.
	size_t storlek = choose_arraysize();

	//allokerar minne, skapar den dynamiska arrayen "FancyArrayName" och en pekare till denna
	int *FancyArrayName = new int [storlek];

	//Sätter in random tal i intervallet -5000 till 5000 i funktionen
	insert_random(FancyArrayName, storlek);

	//Skriver ut arrayen
	print_array(FancyArrayName, storlek);


	
	int *min = FancyArrayName;
	int *max = FancyArrayName;
	int total = 0;
	//Pekare stegar igenom arrayen för att summera och hitta min, max värde.
	for (int *pointer1 = FancyArrayName; pointer1 < FancyArrayName + storlek; pointer1++)
	{
		
		//Kollar om elementet pekaren pekar på är mindre än nuvarande min
		if (*min > *pointer1)
		{
			min = &*pointer1;
			
		}

		//Kollar om elementet pekaren pekar på är större än nuvarande max.
		if (*max < *pointer1)
		{
			max = &*pointer1;
			//cout << endl << "Max value is now = " << *max << endl << endl;
		}

		// Summerar
		total += *pointer1;
		

	}

	cout << endl << "Max value is now = " << *max << endl << endl;
	cout << endl << "Min value is now = " << *min << endl << endl;
	cout << "Total är just nu = " << total << endl << endl;

	delete []FancyArrayName;
	
		
	cout << endl << endl << "Press enter to exit:  ";
	cin.get();
	return 0;
}

//Funktioner
//*****************************************************************************//

size_t choose_arraysize()
{
	// Gör så att man kan skriva åäö.
	setlocale(LC_ALL(), "SWEDISH");

	size_t storlek = 0;
	cout << "Ange storleken på arrayen: ";
	cin >> storlek;
	cin.get();
	
	return storlek;
	
}

//************************************************************************************//

void insert_random(int a_array[], int size)
{
	//Min och max värde
	const int min = -5000;
	const int max = 5000;

	//Initierar slumpmotorn
	random_device number;		//intervallet -5000 till 5000.
	uniform_int_distribution<int> range(min, max);



	// Lägger in slumpal i arrayen
	for (int *pointer = a_array; pointer < a_array + size; pointer++)		*pointer = range(number);


	cout << endl;
}

//************************************************************************************//
void print_array(int a_array[], int size)
{
	// Skriver ut arrayen
	int counter = 0;
	for (int *pointer = a_array; pointer < a_array + size; pointer++)	{		cout << setw(7) << *pointer;
		counter++;

		//Om 10 tal skrivits ut, gör ny rad.
		if (counter % 10 == 0)
		{
			cout << endl;
		}
		//Om 200 tal skrivits ut, stoppa utskriften.
		if (counter % 200 == 0)
		{
			cout << endl << "Press enter to show next 200 values:  ";
			cin.get();
			cout << endl;
		}
		//Om vi nått slutet på listan, meddela det.
		if (counter == size)
		{
			cout << endl << endl << "Slut på arrayen.." << endl;
		}

	}

	cout << endl << endl;
}
//**********************************************************************************//