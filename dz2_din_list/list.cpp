#include "list.h"
bool flag = 1; // по умолчанию - 1 - или пользовательское положение - 0 - указателя на текущий

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
	list_item* p_tmp = new list_item(data); // для указателя на временную переменную выделяем память, содержащую добавляемое значение
	if (is_list_empty()) { // if true
		first = p_tmp; // то указатель на текущий элемент_первый указывает на наше временное значение
		last = p_tmp; // то указатель на текущий элемент_последний указывает на наше временное значение
		p = p_tmp;
		return p;
	} // if false, то сразу переходим к след. шагу
	last->next = p_tmp; // то указатель текущего_последнего элемента на следующий пуказывает на наше временное значение
	p_tmp->previous = last; // "позади" нашего временный элемента находится тот, который считаем последним
	last = p_tmp; // переносим указатель на последний элемент на наш временный. Временный теперь - последний.
}

void list::print_list()
{
	list_item* p_tmp = first; // в качестве временного берем текущий первый
	while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
		cout << p_tmp->data << " "; //печатаем значение текущего элемента в отдельной строке
		p_tmp = p_tmp->next; // меняем временный на его следующий
	}
	std::cout << std::endl;
}

void list::print_list_back()
{
	list_item* p_tmp = last; // в качестве временного берем текущий последний
	while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
		cout << p_tmp->data << " "; //печатаем значение текущего элемента в отдельной строке
		p_tmp = p_tmp->previous; // меняем временный на его предыдущий - задом наперед идем
	}
	std::cout << std::endl;
}

list::list_item* list::pop_list_front(list_item* p)
{
	if (is_list_empty()) {
		return p;
	}
	list_item* p_tmp = first; // в качестве временного берем текущий первый
	first = p_tmp->next; // теперь первый элемент - тот, который следующий после времененного
	if (p = p_tmp) {
		if (flag) {
			p = first;
		}
		else {
			p = first;
			flag = true;
		}
	}
	if (p_tmp->next == nullptr) { //если перешли на нулевой
		last = nullptr;
	}
	else {
		p_tmp->next->previous = nullptr; //он теперь первый, ссылку на предыдущий зануляем
	}
	delete p_tmp; //удаляем взятый временный элемент - т.е. тот, который до махинаций был первым
	return p;
}

list::list_item* list::pop_list_back(list_item* p)
{
	if (is_list_empty()) {
		return p;
	}
	list_item* p_tmp = last; // в качестве временного берем текущий последний

	last = p_tmp->previous; // теперь последний элемент - тот, который предыдущий после времененного
	if (p_tmp->previous == nullptr) { //если перешли на нулевой
		first = nullptr;
		p = nullptr;
		flag = true;
	}
	else {
		if (p == p_tmp) {
			p = first;
			flag = true;
		}
		p_tmp->previous->next = nullptr; //он теперь последний, ссылку на следующий зануляем
	}
	delete p_tmp; //удаляем взятый временный элемент - т.е. тот, который до махинаций был последний
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
	list_item* p_tmp = new list_item(data); // создаем указатель на новый узел, который пока еще не имеет ссылок ни на что
	p_tmp->next = p->next; // меняем связи, ставя новый элемент после текущего из вне
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
	if (flag_m) { // flag_m пользовательская настройка: 1 - вправо, 2 - влево сдвигаем
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
	list_item* p_tmp = new list_item(data); // для указателя на временную переменную выделяем память, содержащую добавляемое значение
	if (is_list_empty()) { // if true
		first = p_tmp; // то указатель на текущий элемент_первый указывает на наше временное значение
		last = p_tmp; // то указатель на текущий элемент_последний указывает на наше временное значение
		p = p_tmp;
		return p;
	} // if false, то сразу переходим к след. шагу
	first->previous = p_tmp; // то указатель текущего_первого элемента на предыдущий пуказывает на наше временное значение
	p_tmp->next = first; // после нашего временный элемента находится тот, который считаем первым
	first = p_tmp; // переносим указатель на первый элемент на наш временный. Временный теперь - первый.
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
	cout << "Деструктор list" << endl << endl;
}
