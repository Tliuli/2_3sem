#pragma once
#include <iostream>
#include <string> //for chars array
using namespace std;
enum animals { tiger = 0, wolf, snake };

struct zoo {
	struct description {
		string name[3]{ "Котя", "Клык", "Северус" };
		int age[3]{ 7, 2, 3 };
		int aviary[3]{ 1, 15, 37 }; //вольер
	};

	animals animal;
	description info;

	void animal_descrption(animals);
};
