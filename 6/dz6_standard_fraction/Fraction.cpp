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

Fraction Fraction::operator+(const Fraction& fraction)
{
	Fraction tmp(numerator * fraction.denominator + denominator * fraction.numerator, denominator * fraction.denominator);
	tmp.reduce();
	return tmp;
}

Fraction Fraction::operator-(const Fraction& fraction)
{
	Fraction tmp(numerator * fraction.denominator - denominator * fraction.numerator, denominator * fraction.denominator);
	tmp.reduce();
	return tmp;
}

Fraction Fraction::operator*(const Fraction& fraction)
{
	Fraction tmp(numerator * fraction.numerator, denominator * fraction.denominator);
	tmp.reduce();
	return tmp;
}

Fraction Fraction::operator/(const Fraction& fraction)
{
	Fraction tmp(numerator * fraction.denominator, denominator * fraction.numerator);
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
	if (a.denominator == 1) {
		strm << a.numerator;
	}
	else {
		strm << a.numerator << "/" << a.denominator;
	}
	return strm;
}
