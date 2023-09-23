#include <iostream>
#include <typeinfo>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

int f1(int a, int b) {
	return a + b;
}

int f2(int a, int b) {
	return a - b;
}

int f3(int a, int b) {
	return a / b;
}

int f4(int a, int b) {
	return a % b;
}

int f5(int a, int b) {
	return a / b + a % b;
}

int (*A_links[])(int, int) = { f1, f2, f3, f4, f5 }; // массив указателей на функции

int main()
{
	srand(unsigned(time(0)));
	int a = rand() % 100;
	int b = rand() % 100;
	std::cout << a << " " << b << std::endl;
	std::cout << f1(a, b) << std::endl;
}

