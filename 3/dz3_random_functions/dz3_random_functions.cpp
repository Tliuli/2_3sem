#include <iostream>
#include <stdio.h>
#include <algorithm> // для перемешивания массива random_shuffle(begin(), end())
#include <stdlib.h> //для работы функции rand()
#include <time.h> //для работы функции time()

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

int coordinate(int* l_of_crds, int* l_dim, int product_f, int len_l_dim) {
	int address = 0;
	for (int i = 0; i < len_l_dim; i++) {
		product_f /= l_dim[i];
		address += l_of_crds[i] * product_f;
	}
	return address;
}

// не понадобилась функция, но ! ->
int* copy_ar(int* l, int l_len) { //int* copy_ar(int(* l[](int, int)), int l_len) <- возможно ли как-то передавать массивы функций в функции в качестве аргументов?
	int* C_ar = new int[l_len]{};
	for (int i = 0; i < l_len; i++) {
		C_ar[i] = l[i];
	}
	return C_ar;
}


int main()
{
	int count_functions = 5, count_tests = 5; // где от count_tests зависит точность
	int product = count_functions * count_functions * count_tests;
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	srand(time(NULL));

	int (*A_links[])(int, int) = { f1, f2, f3, f4, f5 }; // массив указателей на функции
	int (*Jumble_links[])(int, int) = { f1, f2, f3, f4, f5 }; // копия, которую буду перемешивать

	random_shuffle(begin(Jumble_links), end(Jumble_links));
	/*for (int i = 0; i < 5; i++) { // вывод массива
		cout << Jumble_links[i] << " ";
	}*/
	int* A = new int[product] {0};	// f_j |-> count_functions * [ [i] ], где i = [0, count_tests - 1]
	int Dim[3] = { count_functions, count_functions, count_tests };
	// Проведем count_tests тестов и заполним массив результатов
	for (int i = 0; i < count_tests; i++) {
		int a = rand() % 100;
		int b = rand() % 100;
		for (int j = 0; j < count_functions; j++) { //идем по fj
			for (int q = 0; q < count_functions; q++){ //идем по [ [i] ]
				if (Jumble_links[j](a, b) == A_links[q](a, b)) {
					int Index[3] = { j, q, i }; // является ли хорошим способом перезаписывать массив?
					A[coordinate(Index, Dim, product, 3)] = 1;
				}
			}
		}
	}
	bool flag = false;
	// Занулим все те варианты для f_j, где та дала неверное значение
	for (int i = 0; i < count_tests; i++) { //идем по fi
		for (int j = 0; j < count_functions; j++) { //идем по [ [q] ]
			for (int q = 0; q < count_functions; q++) { // идем по [q]
				int Index[3] = { i, j, q };
				if (A[coordinate(Index, Dim, product, 3)] == 0) {
					flag = true;
					break;
				}
			}
			if (flag) {
				for (int q = 0; q < count_functions; q++) { // идем по [q]
					int Index[3] = { i, j, q };
					A[coordinate(Index, Dim, product, 3)] = 0;
				}
				flag = false;
			}
		}
	}
	//Сопоставим ненулевые строчки неизвестных функций с названиями
	for (int i = 0; i < count_tests; i++) { //идем по fi
		for (int j = 0; j < count_functions; j++) { //идем по [ [q] ]
			int Index[3] = { i, j, 0 }; // достаточно проверить первый элемент: q = 0
			if (A[coordinate(Index, Dim, product, 3)] == 1){
				cout << "Функция f" << j + 1 << " пришла " << i + 1 << " -й;" << endl;
				break;
			}
		}
	}
	cout << "Проверка результата" << endl;
	for (int i = 0; i < count_functions; i++) {
		for (int j = 0; j < count_functions; j++) {
			if (A_links[i] == Jumble_links[j]) {
				cout << "Функция f" << i + 1 << " в перемешанном массиве находится на " << j + 1 << " -м месте;" << endl;
			}
		}
	}
}
