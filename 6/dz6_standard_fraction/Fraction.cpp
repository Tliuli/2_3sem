#include "Fraction.h"

Fraction::Fraction(int n, int d)
{
	numerator = n;
	denominator = d;
	if (denominator == 0) {
		cerr << "It is not allowed for denominator to be equal 0." << endl;
		exit(0);
	}
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
