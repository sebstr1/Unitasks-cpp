//funktioner.h

#include "Person.h"
#include "name.h"
#include "address.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

void menu();

int userInput();

void addPerson(vector<Person> &vector);

void printVec(vector<Person>&);