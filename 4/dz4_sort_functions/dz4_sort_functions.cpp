#include <iostream>
#include <stdlib.h> //для работы функции rand()
#include <time.h> //для работы функции time()
using namespace std;

static int AVAL = 1;

bool ascending(const int& v1, const int& v2, int& c_c2 = AVAL) {
	c_c2++;
	if (v1 > v2)
		return true;
	else {
		return false;
	}
}

bool descending(const int& v1, const int& v2, int& c_c2 = AVAL) {
	if (v1 < v2)
		return true;
	else {
		return false;
	}
}

bool ascend_rem_val(const int& v1, const int& v2, int& c_c2 = AVAL) {
	if ((v1 % 1000) > (v2 % 1000))
		return true;
	else if ((v1 % 1000) < (v2 % 1000)) { 
		return false;
	}
	else {
		return ascending(v1, v2);
	}
}

void bubblesort(int* l, int* r, bool f(const int&, const int&, int&), int& c_c2 = AVAL) {
	int i = 0;
	int sz = r - l;
	if (sz <= 1) 
		return;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int* i = l; i + 1 <= r; i++) {
			if (f(*i, *(i + 1), c_c2)) { // компаратор
				swap(*i, *(i + 1));
				flag = true;
			}
		}
		r--;
	}
}

void merge(int list[], int start, int end, int mid, bool f(const int&, const int&, int&), int& c_c2 = AVAL)
{
	int* mergedList = new int[end + 1] {};
	int i, j, k;
	i = start;
	k = start;
	j = mid + 1;

	while (i <= mid && j <= end) {
		if (!f(list[i], list[j], c_c2)) { // компаратор + отрицание для совпадения с пузырем
			mergedList[k] = list[i];
			k++;
			i++;
		}
		else {
			mergedList[k] = list[j];
			k++;
			j++;
		}
	}

	while (i <= mid) {
		mergedList[k] = list[i];
		k++;
		i++;
	}

	while (j <= end) {
		mergedList[k] = list[j];
		k++;
		j++;
	}

	for (i = start; i < k; i++) {
		list[i] = mergedList[i];
	}
}

void mergeSort(int list[], int start, int end, bool f(const int&, const int&, int&), int& c_c2 = AVAL)
{
	int mid;
	if (start < end) {
		mid = (start + end) / 2;
		mergeSort(list, start, mid, f, c_c2);
		mergeSort(list, mid + 1, end, f, c_c2);
		merge(list, start, end, mid, f, c_c2);
	}
}

void print_list(int* list, int len) {
	for (int i = 0; i < len; i++) {
		cout << list[i] << " ";
	}
	cout << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	int n;
	int count_call_b;
	int count_call_m;
	for (int i = 10; i < 1001; i *= 10) {
		n = i;
		int* A = new int[n] {};
		int* B = new int[n] {};
		srand(time(NULL)); // для добавления случайности в качестве начального числа будем брать текущее время с системного таймера
		for (int i = 0; i < n; i++) {
			A[i] = rand() % (101);
			B[i] = rand() % (101);
		}
		count_call_b = 0;
		count_call_m = 0;
		cout << "n = " << n << "; пузырь - ";
		bubblesort(&A[0], &A[n - 1], ascending, count_call_b);

		mergeSort(A, 0, n - 1, ascending, count_call_m);
		cout << count_call_b <<", слияние - " << count_call_m << "." << endl;

		delete[] A;
		delete[] B;
	}

	n = 10;
	int* A = new int[n] {};
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		A[i] = rand() % (101);
	}
	//bubblesort(&A[0], &A[n - 1], ascend_rem_val);
	//mergeSort(A, 0, n - 1, descending);
	//print_list(A, n);

	//Результат для (10, 100, 1000): слияние - (23, 535, 8697), пузырь - (44, 4914, 499310)
}

