#pragma once
#include <iostream>
using namespace std;
struct list
{
public:
	//Эта структура данных необходима для хранения одного элемента списка
	struct list_item {
	public:
		int data;  //Это поле хранит данные
		list_item* next; // Это поле хранит указатель на следующий элемент
		list_item* previous; //Это поле - заготовка для превращения списка в двусвязный

		list_item(int _data) : data(_data), next(nullptr), previous(nullptr) {}; // где nullptr - нулевой указатель, в Си use-ся NULL

		~list_item() {
			cout << " Деструктор list_item" << endl;
		}
	};
private:
	list_item* first; // ан-о head 
	list_item* last; // tail
public:
	list() : first(nullptr), last(nullptr) {};
	list(const list& l);// конструктор глубокого копирования (?) Хотим копировать не сам указатель, а то, на что он указывает
    
	bool is_list_empty();
	list_item* pushback(int data, list_item* p);
	list_item* pushfront(int data, list_item* p);
	void print_list();
	void print_list_back();
	list_item* pop_list_front(list_item* p);
	list_item* pop_list_back(list_item* p);
	list_item* pointer(int data);
	void insert_after_cur(int data, list_item* p);
	list_item* delete_cur(list_item* p);
	list_item* move_cur(list_item* p, bool flag_m);
	void divide_list_cur(list_item* p, list_item* p_2, list& l2);

	~list();
};

