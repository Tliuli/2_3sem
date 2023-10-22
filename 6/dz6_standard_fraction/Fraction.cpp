#include <stdlib.h> // for exit() - ���������� ����������� ��������
#include "Fraction.h"

Fraction::Fraction()
{
	std::cout << "��� ����������" << std::endl;
	numerator = 0;
	denominator = 1;
	
}

Fraction::Fraction(int n)
{
	numerator = 8;
	denominator = 1;
	std::cout << "� 1 ����������" << std::endl;
}

Fraction::Fraction(int n, int d)
{
	std::cout << "wafzgvzsg" << std::endl;
	std::cout << "1r" << n << d << " " << numerator << std::endl;
	if (d == 0) {
		std::cerr << "It is not allowed for denominator to be equal 0." << std::endl; // cerr - ~����� ������ ��������� �� �������
		exit(0); // exit - ���������� ����������� ��������
	} else if (n == 0) {
		numerator = 0;
		denominator = 1;
	} else {
		numerator = n;
		denominator = d;
	}
	std::cout << "2r" << n << d << numerator << std::endl;
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

void Fraction::f(int x, int y) {
	std::cout << "x = " << x << " , y = " << y << std::endl;
}