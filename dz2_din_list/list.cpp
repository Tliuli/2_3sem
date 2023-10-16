#include "list.h"
bool flag = 1; // �� ��������� - 1 - ��� ���������������� ��������� - 0 - ��������� �� �������

bool list::is_list_empty()
{
	if (first == nullptr) {
		return true;
	}
	return false;
}

list::list(const list& l)
{
	list_item* p_tmp_old = l.first;
	while (p_tmp_old != nullptr) {
		list_item* p_tmp_new_node = new list_item(p_tmp_old->data);
		if (is_list_empty()) {
			first = p_tmp_new_node;
			last = p_tmp_new_node;
		}
		last->next = p_tmp_new_node;
		p_tmp_new_node->previous = last;
		last = p_tmp_new_node;

		p_tmp_old = p_tmp_old->next;
	}
}

list::list_item* list::pushback(int data, list_item* p)
{
	list_item* p_tmp = new list_item(data); // ��� ��������� �� ��������� ���������� �������� ������, ���������� ����������� ��������
	if (is_list_empty()) { // if true
		first = p_tmp; // �� ��������� �� ������� �������_������ ��������� �� ���� ��������� ��������
		last = p_tmp; // �� ��������� �� ������� �������_��������� ��������� �� ���� ��������� ��������
		p = p_tmp;
		return p;
	} // if false, �� ����� ��������� � ����. ����
	last->next = p_tmp; // �� ��������� ��������_���������� �������� �� ��������� ���������� �� ���� ��������� ��������
	p_tmp->previous = last; // "������" ������ ��������� �������� ��������� ���, ������� ������� ���������
	last = p_tmp; // ��������� ��������� �� ��������� ������� �� ��� ���������. ��������� ������ - ���������.
}

void list::print_list()
{
	list_item* p_tmp = first; // � �������� ���������� ����� ������� ������
	while (p_tmp != nullptr) { // � ���� �� ������ �� �������� ���������, ����������� �����
		cout << p_tmp->data << " "; //�������� �������� �������� �������� � ��������� ������
		p_tmp = p_tmp->next; // ������ ��������� �� ��� ���������
	}
	std::cout << std::endl;
}

void list::print_list_back()
{
	list_item* p_tmp = last; // � �������� ���������� ����� ������� ���������
	while (p_tmp != nullptr) { // � ���� �� ������ �� �������� ���������, ����������� �����
		cout << p_tmp->data << " "; //�������� �������� �������� �������� � ��������� ������
		p_tmp = p_tmp->previous; // ������ ��������� �� ��� ���������� - ����� ������� ����
	}
	std::cout << std::endl;
}

list::list_item* list::pop_list_front(list_item* p)
{
	if (is_list_empty()) {
		return p;
	}
	list_item* p_tmp = first; // � �������� ���������� ����� ������� ������
	first = p_tmp->next; // ������ ������ ������� - ���, ������� ��������� ����� ������������
	if (p = p_tmp) {
		if (flag) {
			p = first;
		}
		else {
			p = first;
			flag = true;
		}
	}
	if (p_tmp->next == nullptr) { //���� ������� �� �������
		last = nullptr;
	}
	else {
		p_tmp->next->previous = nullptr; //�� ������ ������, ������ �� ���������� ��������
	}
	delete p_tmp; //������� ������ ��������� ������� - �.�. ���, ������� �� ��������� ��� ������
	return p;
}

list::list_item* list::pop_list_back(list_item* p)
{
	if (is_list_empty()) {
		return p;
	}
	list_item* p_tmp = last; // � �������� ���������� ����� ������� ���������

	last = p_tmp->previous; // ������ ��������� ������� - ���, ������� ���������� ����� ������������
	if (p_tmp->previous == nullptr) { //���� ������� �� �������
		first = nullptr;
		p = nullptr;
		flag = true;
	}
	else {
		if (p == p_tmp) {
			p = first;
			flag = true;
		}
		p_tmp->previous->next = nullptr; //�� ������ ���������, ������ �� ��������� ��������
	}
	delete p_tmp; //������� ������ ��������� ������� - �.�. ���, ������� �� ��������� ��� ���������
	return p;
}

list::list_item* list::pointer(int data)
{
	list_item* p_tmp = first;
	while (p_tmp->data != data) {
		p_tmp = p_tmp->next;
	}
	return p_tmp;
	flag = false;
}

void list::insert_after_cur(int data, list_item* p)
{
	list_item* p_tmp = new list_item(data); // ������� ��������� �� ����� ����, ������� ���� ��� �� ����� ������ �� �� ���
	p_tmp->next = p->next; // ������ �����, ����� ����� ������� ����� �������� �� ���
	p_tmp->previous = p;
	p->next->previous = p_tmp;
	p->next = p_tmp;
}

list::list_item* list::delete_cur(list_item* p)
{
	if (p == first) {
		p = pop_list_front(p);
	}
	else if (p == last) {
		p = pop_list_back(p);
	}
	else {
		p->previous->next = p->next;
		p->next->previous = p->previous;
		p = first;
		flag = true;
	}
	return p;
}

list::list_item* list::move_cur(list_item* p, bool flag_m)
{
	if (flag_m) { // flag_m ���������������� ���������: 1 - ������, 2 - ����� ��������
		p = p->next;
	}
	else {
		p = p->previous;
	}
	return p;
}

void list::divide_list_cur(list_item* p, list_item* p_2, list& l2)
{
	l2.first = p->next;
	l2.last = last;
	last = p;
	p_2 = l2.first;

	l2.first->previous = nullptr;
	last->next = nullptr;
}

list::list_item* list::pushfront(int data, list_item* p)
{
	list_item* p_tmp = new list_item(data); // ��� ��������� �� ��������� ���������� �������� ������, ���������� ����������� ��������
	if (is_list_empty()) { // if true
		first = p_tmp; // �� ��������� �� ������� �������_������ ��������� �� ���� ��������� ��������
		last = p_tmp; // �� ��������� �� ������� �������_��������� ��������� �� ���� ��������� ��������
		p = p_tmp;
		return p;
	} // if false, �� ����� ��������� � ����. ����
	first->previous = p_tmp; // �� ��������� ��������_������� �������� �� ���������� ���������� �� ���� ��������� ��������
	p_tmp->next = first; // ����� ������ ��������� �������� ��������� ���, ������� ������� ������
	first = p_tmp; // ��������� ��������� �� ������ ������� �� ��� ���������. ��������� ������ - ������.
	if (flag) {
		p = p_tmp;
		return p;
	}
}

list::~list()
{
	list_item* p_tmp = first;
	while (p_tmp->next != nullptr) {
		cout << p_tmp->data << " ";
		p_tmp = p_tmp->next;
		delete p_tmp->previous;
	}
	cout << p_tmp->data << " ";
	delete p_tmp;
	cout << "���������� list" << endl << endl;
}
