#include <iostream> //для работы с потоками ввода\вывода
#include<stdlib.h> //для работы функции rand()
#include<time.h> //для работы функции time()
using namespace std;

int n;

int coordinate(int* l, int* dim, int product_f) {
	int address = 0;
	for (int i = 0; i < n; i++) {
		product_f /= dim[i];
		address += l[i] * product_f;
	}
	return address;
}

int* copy_ar(int* Min_f) { // возможно не понадобится....
	int* C_ar = new int[n + 1]{};
	for (int i = 0; i < n; i++) {
		C_ar[i] = Min_f[i];
	}
	return C_ar;
}

int main()
{
	int dif, i, min, max, sum = 0, product = 1;
	bool flag = true;
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	
	cout << "Введите число: ";
	cin >> n;
	int* D = new int[n + 1]{};	// массив для хранения n чисел-размерностей
	cout << "Введите столько чисел: ";
	for (i = 0; i < n; i++){
		cin >> D[i];
		product = product * D[i];
	}

	cout << product << endl;
	
	int* A = new int[product]{};	// n-мерный массив для хранения чисел-измерений
	// Заполним массив случайными числами в из диапазона [-10; 10]
	// Функция rand() нуждается в инициализации, которая производится by srand()
	srand(time(NULL)); // для добавления случайности в качестве начального числа будем брать текущее время с системного таймера
	for (i = 0; i < n; i++) {
		A[i] = rand() % 21 - 10; // будь тут ...%(11);, то диапазон был бы [0; 10]
	}

	for (i = 0; i < n; i++) { // вывод массива
		cout << A[i] << " ";
	}

	int* Min = new int[n + 1]{};	// массив для хранения n чисел-нижних граней
	int* Max = new int[n + 1]{};	// массив для хранения n чисел-верхних граней

	// Имеем n осей. User n раз указывает пару чисел в этом пределе. Считаем, что для границ: [...)
	for (int q = 0; q < n; q++) {
		cout << "Введите числа: ";
		cin >> min >> max;
		Min[q] = min;
		Max[q] = max;
	}

	// и как-то надо дальше поочередно инкрементировать значения в массиве...........


	cout << sum;
	cout << endl;
}