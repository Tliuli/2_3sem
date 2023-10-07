// dz5_WhatDoesTheFoxSay.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
enum animals {
	dog,
	cat,
	chicken
};

void animal_sound(animals animal){
	switch (animal) {
	case dog:
		cout << "woof-woof";
		return;
	case cat:
		cout << "meow";
		return;
	case chicken:
		cout << "cluck-cluck";
		return;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	//animals input;
	//cout << "Введите животное из списка: dog, cat, chicken" << endl;
	//cin >> s;
	animals an = cat; // с консоли если вводить, перевод в тип animals сложнее...
	animal_sound(an);
}