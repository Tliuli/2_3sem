#include "zoo.h"

void zoo::animal_descrption(animals input) {
	animal = input;
	cout << "name " << info.name[animal] << endl;
	cout << "age " << info.age[animal] << endl;
	cout << "aviary " << info.aviary[animal] << endl;
}
