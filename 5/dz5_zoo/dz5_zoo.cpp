// dz5_zoo.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include "zoo.h"

int main()
{
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	
	zoo z;
	z.animal_descrption(tiger);
}
