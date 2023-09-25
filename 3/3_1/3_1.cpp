#include <iostream>
#include <typeinfo>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm> // для перемешивания массива
#include<stdlib.h> //для работы функции rand()
#include<time.h> //для работы функции time()

using namespace std;

int f1(int a, int b) { // сумма
	return a + b;
}

int f2(int a, int b) { // разность
	return a - b;
}

int f3(int a, int b) { // деление нацело
	return a / b;
}

int f4(int a, int b) { // остаток
	return a % b;
}

int f5(int a, int b) { // ...
	return a / b + a % b;
}


int main()
{
	int n = 5, control = 3, at = 2; // где n - кол-во функций, а control - проверяемых условий, at - проверок
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился

	int (*A_links[])(int, int) = { f1, f2, f3, f4, f5 }; // массив указателей на функции

	/*for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << A_links[i] << " ";
	}*/
	random_shuffle(begin(A_links), end(A_links));
	/*for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << A_links[i] << " ";
	}*/

	// каждой функции |-> [a, b, c], где a, b, c = 1 if: a - f1 + f2 = 2a; b - f1 - f2 = 2b; c - f3 + f4 = f5
	int** F_at = new int* [n] {0}; // результаты первой проверки
	for (int i = 0; i < n; i++) {
		F_at[i] = new int[control] {0};
	}

	int** S_at = new int* [n] {0}; // результаты второй проверки
	for (int i = 0; i < n; i++) {
		S_at[i] = new int[control] {0};
	}

	srand(unsigned(time(0)));
	for (int i = 0; i < at; i++) {
		int a = rand() % 100;
		int b = rand() % 100;
		//std::cout << a << " " << b << std::endl;
		for (int j = 0; j < n; j++) {
			for (int q = j + 1; q < n; q++) {
				if (A_links[j](a, b) + A_links[q](a, b) == 2 * a) {
					if (i) {
						S_at[j][0] = 1;
						S_at[q][0] = 1;
					}
					else {
						F_at[j][0] = 1;
						F_at[q][0] = 1;
					}
				}
				if ((A_links[j](a, b) - A_links[q](a, b) == 2 * b) or (-A_links[j](a, b) + A_links[q](a, b) == 2 * b)) {
					if (i) {
						S_at[j][1] = 1;
						S_at[q][1] = 1;
					}
					else {
						F_at[j][1] = 1;
						F_at[q][1] = 1;
					}
				}
				for (int k = 0; k < n; k++) {
					if (k != j and k != q) {
						if (A_links[j](a, b) + A_links[q](a, b) == A_links[k](a, b)) {
							if (i) {
								S_at[j][2] = 1;
								S_at[q][2] = 1;
								S_at[k][2] = 1;
							}
							else {
								F_at[j][2] = 1;
								F_at[q][2] = 1;
								F_at[k][2] = 1;
							}
						}
					}
				}
			}
		}
	}
	/*cout << "First attempt" << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << F_at[i][0] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << F_at[i][1] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << F_at[i][2] << " ";
	}
	cout << endl;
	cout << "Second attempt" << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << S_at[i][0] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << S_at[i][1] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << S_at[i][2] << " ";
	}
	cout << endl; */
	// зануляем все, что не соответствует
	for (int i = 0; i < 5; i++) {
		if (F_at[i][0] == 0 or F_at[i][1] == 0 or S_at[i][0] == 0 or S_at[i][1] == 0) {
			F_at[i][0] = 0;
			F_at[i][1] = 0;
			S_at[i][0] = 0;
			S_at[i][1] = 0;
		}
		if (F_at[i][2] == 0 or S_at[i][2] == 0) {
			F_at[i][2] = 0;
			S_at[i][2] = 0;
		}
	}
	/*cout << "После зануления" << endl; // в идеале, получаем не более нужного кол-ва функций, среди которых просто распределяем по соответствию.
	// по-хорошему, нужна третья проверка из-за последних трех функций, но там коллизия очень редко возникает...
	// если хотим взять большое число at, то лучше сделать не как тут различными массивами, а повторить структуру многомерного массива из задачи 3 этой недели. И запихнуть выводы в функцию...
	cout << "First attempt" << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << F_at[i][0] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << F_at[i][1] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << F_at[i][2] << " ";
	}
	cout << endl;
	cout << "Second attempt" << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << S_at[i][0] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << S_at[i][1] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << S_at[i][2] << " ";
	}
	cout << endl;*/
	// распределяем, какая функция who, выбирая из двух\трех. Хз, как короче сделать
	int** Answer_2 = new int* [n] {0};
	for (int i = 0; i < n; i++) {
		Answer_2[i] = new int[2]{ 0 };
	}
	int** Answer_3 = new int* [n] {0};
	for (int i = 0; i < n; i++) {
		Answer_3[i] = new int[3]{ 0 };
	}
	int q = 0, j = 0, i = 0;
	for (int i = 0; i < 5; i++) {
		if (F_at[i][0] == 1) { // неожиданная мысль, но, кажется, третья проверка на три функции излишняя. Мы первые две определять научились, а их выбор однозначно определяет другие три как оставшиеся...
			Answer_2[q][1] = i;
			q++;
		}
		else {
			Answer_3[j][1] = i;
			j++;
		}
	}
	delete[] F_at;
	delete[] S_at;

	int a = rand() % 100;
	int b = rand() % 100;
	if (A_links[Answer_2[0][1]](a, b) - A_links[Answer_2[1][1]](a, b) == 2 * b) {
		cout << Answer_2[0][1] + 1<< " f1" << endl;
		cout << Answer_2[1][1] + 1<< " f2" << endl;
	}
	else {
		cout << Answer_2[0][1] + 1<< " f2" << endl;
		cout << Answer_2[1][1] + 1<< " f1" << endl;
	}
	// а вот с оставшимися тремя функциями сложнее <- вставлен вариант решения с коллизиями. Чтобы без них - большой кусок снизу, который пока не работает.
	for (int i = 0; i < 3; i++) {
			if (A_links[Answer_3[i][1]](a, b)  == a / b) {
				cout << Answer_3[i][1] + 1 << " f3" << endl;
			}
			if (A_links[Answer_3[i][1]](a, b) == a % b) {
				cout << Answer_3[i][1] + 1 << " f4" << endl;
			}
			if (A_links[Answer_3[i][1]](a, b) == a / b + a % b) {
				cout << Answer_3[i][1] + 1 << " f5" << endl;
			}
		}
	}
	/*int** f_at = new int* [3] {0}; // результаты первой проверки
	for (int i = 0; i < 2; i++) {
		f_at[i] = new int[control] {0};
	}

	int** s_at = new int* [3] {0}; // результаты второй проверки
	for (int i = 0; i < 2; i++) {
		s_at[i] = new int[control] {0};
	}

	srand(unsigned(time(0)));
	for (int i = 0; i < at; i++) {
		ia = rand() % 100;
		int b = rand() % 100;
		std::cout << a << " " << b << std::endl;
		for (int j = 0; j < 3; j++) {
			for (int q = j + 1; q < n; q++) {
				if (A_links[Answer_3[j][1]](a, b) == a / b) {
					if (i) {
						s_at[j][0] = 1;
					}
					else {
						f_at[j][0] = 1;
					}
				}
				if (b != 0 and a != 0) {
					if (A_links[Answer_3[j][1]](a, b) == a % b) {
						if (i) {
							s_at[j][1] = 1;
						}
						else {
							f_at[j][1] = 1;
						}
					}
			    }
			}
		}
	}
	/*cout << "First attempt" << endl;
	for (int i = 0; i < 3; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << f_at[i][0] << " ";
	}
	cout << endl;
	for (int i = 0; i < 3; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << f_at[i][1] << " ";
	}
	cout << endl;
	cout << "Second attempt" << endl;
	for (int i = 0; i < 3; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << s_at[i][0] << " ";
	}
	cout << endl;
	for (int i = 0; i < 3; i++) { // вывод массива, можно чекнуть правильность по порядку адресов до и после перемешивания
		cout << S_at[i][1] << " ";
	}
	cout << endl;
	*/
	

