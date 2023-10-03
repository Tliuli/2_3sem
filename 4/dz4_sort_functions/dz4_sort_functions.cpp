#include <iostream>
using namespace std;

//ascend_rem_val

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


int main()
{
	//setlocale(LC_ALL, "Russian");  // чтобы русский язык при печати верно выводился
	int arr[] = { 5, 1, 4000, 2, 8 };
	bubblesort(&arr[0], &arr[4]);
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << " ";
	}
}

