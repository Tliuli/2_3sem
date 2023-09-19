﻿// 2_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

//Этот код Односвязного списка
//Этот список умеет совсем немного.
//Добавлять элементы в конец себя и печатать себя.

// structure: first-[]...<->[next, data, previous]<->...[]-last

//Эта структура данных необходима для хранения одного элемента списка
struct list_item {
	int data;  //Это поле хранит данные
	list_item* next; // Это поле хранит указатель на следующий элемент
	list_item* previous; //Это поле - заготовка для превращения списка в двусвязный

	//Это конструктор,
	//Он нужен для инициализации элемента списка
	//Пока не важно как это рабоает, используйте по аналогии с вызовом в 46 строке
	list_item(int _data) : data(_data), next(nullptr) ,previous(nullptr) {}; // где nullptr - нулевой указатель, в Си use-ся NULL

};


//Эта структура данных необходима для работы со списком в целом
struct list {
	list_item* first; // ан-о head 
	list_item* last; // tail
	list() : first(nullptr), last(nullptr) {};
};


// Тут все ясно
bool is_list_empty(list* my_list) {
	if (my_list->first == nullptr) {
		return true;
	}
	return false;
}

// Здесь реализовано добавление нового элемента в конец списка
// Как только вы поймете как это работает - вы успешны
// Оператор -> означает разыминование указателя, и обращение к полю
// То-есть cur_list->last - Это то-же самое что (*cur_list).last
void pushback(list* cur_list, int data) {
	list_item* p_tmp = new list_item(data); // для указателя на временную переменную выделяем память, содержащую добавляемое значение
	if (is_list_empty(cur_list)) { // if true
		cur_list->first = p_tmp; // то указатель на текущий элемент_первый указывает на наше временное значение
		cur_list->last = p_tmp; // то указатель на текущий элемент_последний указывает на наше временное значение
		return;
	} // if false, то сразу переходим к след. шагу
	cur_list->last->next = p_tmp; // то указатель текущего_последнего элемента на следующий пуказывает на наше временное значение
	p_tmp->previous = cur_list->last; // "позади" нашего временный элемента находится тот, который считаем последним
	cur_list->last = p_tmp; // переносим указатель на последний элемент на наш временный. Временный теперь - последний.
}

void pushfront(list* cur_list, int data) {
	list_item* p_tmp = new list_item(data); // для указателя на временную переменную выделяем память, содержащую добавляемое значение
	if (is_list_empty(cur_list)) { // if true
		cur_list->first = p_tmp; // то указатель на текущий элемент_первый указывает на наше временное значение
		cur_list->last = p_tmp; // то указатель на текущий элемент_последний указывает на наше временное значение
		return;
	} // if false, то сразу переходим к след. шагу
	cur_list->first->previous = p_tmp; // то указатель текущего_первого элемента на предыдущий пуказывает на наше временное значение
	p_tmp->next = cur_list->first; // после нашего временный элемента находится тот, который считаем первым
	cur_list->first = p_tmp; // переносим указатель на первый элемент на наш временный. Временный теперь - первый.
}

// Эта штука проходится по списку и печатает элементы в порядке добавления
void print_list(list* cur_list) {
	list_item* p_tmp = cur_list->first; // в качестве временного берем текущий первый
	while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
		std::cout << p_tmp->data << std::endl; //печатаем значение текущего элемента в отдельной строке
		p_tmp = p_tmp->next; // меняем временный на его следующий
	}
}

void print_list_back(list* cur_list) {
	list_item* p_tmp = cur_list->last; // в качестве временного берем текущий последний
	while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
		std::cout << p_tmp->data << std::endl; //печатаем значение текущего элемента в отдельной строке
		p_tmp = p_tmp->previous; // меняем временный на его предыдущий - задом наперед идем
	}
}

void clean_list(list* cur_list) {
	list_item* p_tmp = cur_list->first; // в качестве временного берем текущий первый
	while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
		p_tmp = p_tmp->next; // меняем временный на его следующий
		delete p_tmp->previous; //удаляем предыдущий элемент
	}
}

void pop_list_front(list* cur_list) {
	if (is_list_empty(cur_list)) {
		return;
	}
	list_item* p_tmp = cur_list->first; // в качестве временного берем текущий первый
	cur_list->first = p_tmp->next;
	if (p_tmp->next == nullptr) {
		cur_list->last == nullptr;
	}
	else {
		p_tmp->next->previous = nullptr;
	}
	delete p_tmp;
}

void clean_list_back(list* cur_list) {
	list_item* p_tmp = cur_list->last; // в качестве временного берем текущий последний
	while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
		p_tmp = p_tmp->previous; // меняем временный на его предыдущий - задом наперед идем
		delete p_tmp->next; //удаляем следующий элемент
	}
}

int main()
{
	list l;
	//cout << is_list_empty(&l) << std::endl; //печатаем, верно ли, что список пустой - ответ - true - 1. Создаем первый элемент списка, нулевой
	//прошлую строчку спокойно можем опустить
	//pushback(&l, 28); unneed for check
	//pushback(&l, 37);
	//pushback(&l, 21);
	//pushback(&l, 4);
	pushfront(&l, 2); // добавление в начало - success
	pushfront(&l, 3);
	pushfront(&l, 4);
	pushfront(&l, 5);

	print_list(&l);
	cout << "\n";
	print_list_back(&l); // печать в обратном порядке - success
	pop_list_front(&l);
	print_list(&l);

	//cout << is_list_empty(&l) << std::endl; ан-о
	cout << l.first; // if add ->data , то будет выводить первое значение, а не адрес
	clean_list_back(&l);
	//check clean both
	print_list(&l);
	cout << "\n";
	print_list_back(&l);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
