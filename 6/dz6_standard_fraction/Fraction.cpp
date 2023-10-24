#include <stdlib.h> // for exit() - завершение вызывающего процесса
#include "Fraction.h"

Fraction::Fraction(int n, int d)
{
	if (d == 0) {
		std::cerr << "It is not allowed for denominator to be equal 0." << std::endl; // cerr - ~поток вывода сообщений об ошибках
		exit(0); // exit - завершение вызывающего процесса
	} else if (n == 0) {
		numerator = 0;
		denominator = 1;
	} else {
		numerator = n;
		denominator = d;
	}
}

Fraction operator+(const Fraction& l_fraction, const Fraction& r_fraction)
{
	Fraction tmp(l_fraction.numerator * r_fraction.denominator + l_fraction.denominator * r_fraction.numerator, l_fraction.denominator * r_fraction.denominator);
	tmp.reduce();
	return tmp;
}

Fraction operator-(const Fraction& l_fraction, const Fraction& r_fraction)
{
	Fraction tmp(l_fraction.numerator * r_fraction.denominator - l_fraction.denominator * r_fraction.numerator, l_fraction.denominator * r_fraction.denominator);
	tmp.reduce();
	return tmp;
}

Fraction operator*(const Fraction& l_fraction, const Fraction& r_fraction)
{
	Fraction tmp(l_fraction.numerator * r_fraction.numerator, l_fraction.denominator * r_fraction.denominator);
	tmp.reduce();
	return tmp;
}

Fraction operator/(const Fraction& l_fraction, const Fraction& r_fraction)
{
	Fraction tmp(l_fraction.numerator * r_fraction.denominator, l_fraction.denominator * r_fraction.numerator);
	tmp.reduce();
	return tmp;
}

int Fraction::gcd(int a, int b)
{
	while (b > 0) {
		int c = a % b;
		a = b;
		b = c;
	}
	return a;
}

int Fraction::lcm(int a, int b)
{
	return (a * b) / gcd(a, b);
}

void Fraction::reduce()
{
	int gcd = Fraction::gcd(numerator, denominator);
	if (gcd != 1) {
		numerator = numerator / gcd;
		denominator = denominator / gcd;
	}
}

Fraction::~Fraction()
{
}

std::ostream& operator<<(std::ostream& strm, const Fraction& a)
{
	//std::cout << "We are here ";
	if (a.denominator == 1) {
		strm << a.numerator;
	}
	else {
		strm << a.numerator << "/" << a.denominator;
	}
	return strm;
}