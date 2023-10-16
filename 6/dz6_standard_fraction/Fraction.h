#pragma once
#include <iostream>
class Fraction
{
public:
	int numerator; //���������
	int denominator; //�����������

	Fraction(int n, int d); // �����������

	// ����������� ��������� �������� ��������
	Fraction operator+(const Fraction& fraction);
	Fraction operator-(const Fraction& fraction);
	Fraction operator*(const Fraction& fraction);
	Fraction operator/(const Fraction& fraction);

	//���(a, b) = ���(a, a mod b)
	int gcd(int a, int b); //greatest common diviser (�.�. ���)

	//���(a, b) = (a * b) / ���(a, b)
	int lcm(int a, int b); //least common multiple (�.�. ���)

	void reduce(); // f-�� ��� ���������� �����

	friend std::ostream& operator<<(std::ostream& strm, const Fraction& a); // ���������� ��������� ������ � �����
	//friend, �.�. � ������ ��� ������� � ���, �� �� ����� ���� ������ ������ -> ���. ��. �������� -> ������ ���� ���������� ��� ��������� � ������

	~Fraction();
};

