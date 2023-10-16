#pragma once
#include <iostream>
using namespace std;
struct list
{
public:
	//��� ��������� ������ ���������� ��� �������� ������ �������� ������
	struct list_item {
	public:
		int data;  //��� ���� ������ ������
		list_item* next; // ��� ���� ������ ��������� �� ��������� �������
		list_item* previous; //��� ���� - ��������� ��� ����������� ������ � ����������

		list_item(int _data) : data(_data), next(nullptr), previous(nullptr) {}; // ��� nullptr - ������� ���������, � �� use-�� NULL

		~list_item() {
			cout << " ���������� list_item" << endl;
		}
	};
private:
	list_item* first; // ��-� head 
	list_item* last; // tail
public:
	list() : first(nullptr), last(nullptr) {};
	list(const list& l);// ����������� ��������� ����������� (?) ����� ���������� �� ��� ���������, � ��, �� ��� �� ���������
    
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

