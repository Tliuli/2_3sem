#include <iostream>
#include <stdlib.h> //для работы функции rand()
#include <time.h> //для работы функции time()
using namespace std;

int count_call = 0;
int* c_c = &count_call;

bool ascending(const int& v1, const int& v2) {
	(*c_c)++;
	if (v1 > v2)
		return true;
	else {
		return false;
	}
}

bool descending(const int& v1, const int& v2) {
	if (v1 < v2)
		return true;
	else {
		return false;
	}
}

bool ascend_rem_val(const int& v1, const int& v2) {
	if ((v1 % 1000) > (v2 % 1000))
		return true;
	else if ((v1 % 1000) < (v2 % 1000)) { 
		return false;
	}
	else {
		return ascending(v1, v2);
	}
}

void bubblesort(int* l, int* r) {
	int i = 0;
	int sz = r - l;
	if (sz <= 1) 
		return;
	bool flag = true;
	while (flag) {
		flag = false;
		for (int* i = l; i + 1 <= r; i++) {
			if (ascending(*i, *(i + 1))) { // компаратор
				swap(*i, *(i + 1));
				flag = true;
			}
		}
		r--;
	}
}

void merge(int list[], int start, int end, int mid)
{
	int* mergedList = new int[end + 1] {};
	//int mergedList[20];
	int i, j, k;
	i = start;
	k = start;
	j = mid + 1;

	while (i <= mid && j <= end) {
		if (!ascending(list[i], list[j])) { // компаратор + отрицание для совпадения с пузырем
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

void mergeSort(int list[], int start, int end)
{
	int mid;
	if (start < end) {
		mid = (start + end) / 2;
		mergeSort(list, start, mid);
		mergeSort(list, mid + 1, end);
		merge(list, start, end, mid);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	int n = 10;
	int* A = new int[n] {};
	srand(time(NULL)); // для добавления случайности в качестве начального числа будем брать текущее время с системного таймера
	for (int i = 0; i < n; i++) {
		A[i] = rand() % (101);
	}

	//bool (*A_links[])(const int& v1, const int& v2) = { ascending, descending, ascend_rem_val }; // массив указателей на функции
	//bool* p = A_links;

	cout << "Пузырь" << endl;
	bubblesort(&A[0], &A[n - 1]);
	//cout << "Слияние" << endl;
	//mergeSort(A, 0, n - 1);
	/*for (int i = 0; i < n; i++) {
		cout << A[i] << " ";
	}*/
	cout << endl << count_call;

	//Результат для (10, 100, 1000): слияние - (23, 535, 8697), пузырь - (44, 4914, 499310)
}

