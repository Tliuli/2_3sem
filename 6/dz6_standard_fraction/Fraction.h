#pragma once
#include <iostream>
class Fraction
{
public:
	int numerator; //числитель
	int denominator; //знаменатель
	Fraction(int n = 0, int d = 1); // конструктор

	// Перегружаем операторы основных операций
	friend Fraction operator+(const Fraction& l_fraction, const Fraction& r_fraction);
	friend Fraction operator-(const Fraction& l_fraction, const Fraction& r_fraction);
	friend Fraction operator*(const Fraction& l_fraction, const Fraction& r_fraction);
	friend Fraction operator/(const Fraction& l_fraction, const Fraction& r_fraction);

	//НОД(a, b) = НОД(a, a mod b)
	int gcd(int a, int b); //greatest common diviser (т.е. НОД)

	//НОК(a, b) = (a * b) / НОД(a, b)
	int lcm(int a, int b); //least common multiple (т.е. НОК)

	void reduce(); // f-ия для сокращения дроби

	friend std::ostream& operator<<(std::ostream& strm, const Fraction& a); // перегрузка оператора вывода в поток
	//friend, т.к. к потоку нет доступа у нас, он не может быть членом класса -> явл. вн. объектом -> должно быть определено его отношение к классу

	~Fraction();
};



