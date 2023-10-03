#include <iostream>
using namespace std;

bool ascending(const int& v1, const int& v2) {
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
			if (ascend_rem_val(*i, *(i + 1))) {
				swap(*i, *(i + 1));
				flag = true;
			}
		}
		r--;
	}
}

void merge(int list[], int start, int end, int mid)
{
	int mergedList[8];
	int i, j, k;
	i = start;
	k = start;
	j = mid + 1;

	while (i <= mid && j <= end) {
		if (list[i] < list[j]) {
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
	//setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	int A[] = { 5, 1, 4000, 2, 8 };
	bool (*A_links[])(const int& v1, const int& v2) = { ascending, descending, ascend_rem_val }; // массив указателей на функции
	bubblesort(&A[0], &A[4]);
	//mergeSort(arr, 0, 4);
	for (int i = 0; i < 5; i++) {
		cout << A[i] << " ";
	}
}

