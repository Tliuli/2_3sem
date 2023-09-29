#include <iostream> //для работы с потоками ввода\вывода
#include <stdlib.h> //для работы функции rand()
#include <time.h> //для работы функции time()
using namespace std;

int coordinate(int* l, int* dim, int product_f, int dims) {
	int address = 0;
	for (int i = 0; i < dims; i++) {
		product_f /= dim[i];
		address += l[i] * product_f;
	}
	return address;
}


void from_min2max(int* min, int* max, int dims, int* dim, int product_f, int* numbers) {
	int summ = 0;
	int* cur_indexes = new int[dims]; // указатель на тек. индексы - указатель массив размерности dims == n
	for (int i = 0; i < dims; i++) {
		cur_indexes[i] = min[i];
	} //назначаем текущими индексами нижнюю границу
	int cur_index = 0;
	while (cur_index < dims) {
		/*cout << "answer " << endl;
		for (int i = 0; i < dims; i++) {
			std::cout << cur_indexes[i] << " ";
		}
		cout << endl << numbers[coordinate(cur_indexes, dim, product_f, dims)] << " " << coordinate(cur_indexes, dim, product_f, dims) << endl;*/
		summ += numbers[coordinate(cur_indexes, dim, product_f, dims)];
		//Ищем следующий подходящий индекс:
		cur_indexes[0] += 1;
		cur_index = 0;
		bool is_in_bounds = cur_indexes[cur_index] < max[cur_index];
		while (!is_in_bounds) { //if дошли до максимума по тек. индексу
			if (cur_indexes[cur_index] < max[cur_index]) { //после выполнения else - перехода на след. индекс - снова сюда заходим
				for (int j = 0; j < cur_index; j++) {
					cur_indexes[j] = min[j];
				} //возвращаем все, что успели накрутить старшим порядкам на нижнюю границу
				is_in_bounds = true;
			}
			else { //т.е. cur_indexes[cur_index] >= max[cur_index]
				cur_index += 1; //переходим на следующий порядок (т.е. предыдущий вообще-то)
				if (cur_index >= dims) { // кол-во порядков ограничено размерностью массива, т.е. дошли до конца
					break;
				}
				cur_indexes[cur_index] += 1; //на прошлом значении мы рассмотрели случай еще до while, повторяться нет нужды
			}
		}
	}
	cout << endl << summ;
}

int main()
{
	int n, i, min, max, product = 1;
	bool flag = true;
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	
	cout << "Введите число: ";
	cin >> n;
	int* D = new int[n]{};	// массив для хранения n чисел-размерностей
	cout << "Введите столько чисел: ";
	for (i = 0; i < n; i++){
		cin >> D[i];
		product = product * D[i];
	}

	int* A = new int[product]{};	// n-мерный массив для хранения чисел-измерений
	// Заполним массив случайными числами в из диапазона [-10; 10]
	// Функция rand() нуждается в инициализации, которая производится by srand()
	srand(time(NULL)); // для добавления случайности в качестве начального числа будем брать текущее время с системного таймера
	for (i = 0; i < product; i++) {
		A[i] = rand() % 21 - 10; // будь тут ...%(11);, то диапазон был бы [0; 10]
	}

	/*cout << "product " << product << endl;
	for (i = 0; i < product; i++) { // вывод массива
		cout << A[i] << " ";
	}*/

	int* Min = new int[n]{};	// массив для хранения n чисел-нижних граней
	int* Max = new int[n]{};	// массив для хранения n чисел-верхних граней

	cout << "Введите пару чисел для i-ой оси, где первое число - минимум, а второе - максимум : " << endl;
	// Имеем n осей. User n раз указывает пару чисел в этом пределе. Считаем, что для границ: [...)
	for (int q = 0; q < n; q++) {
		cout << q + 1 << "-ая пара:";
		cin >> min >> max;
		Min[q] = min;
		Max[q] = max;
	}

	from_min2max(Min, Max, n, D, product, A);
}