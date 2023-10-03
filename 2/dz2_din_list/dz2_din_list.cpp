#include <iostream>
using namespace std;

//Этот код Односвязного списка
//Этот список умеет совсем немного.
//Добавлять элементы в конец себя и печатать себя.

// structure: first-[]...<->[next, data, previous]<->...[]-last
bool flag = 1; // по умолчанию - 1 - или пользовательское положение - 0 - указателя на текущий
//Эта структура данных необходима для хранения одного элемента списка
struct list_item {
	int data;  //Это поле хранит данные
	list_item* next; // Это поле хранит указатель на следующий элемент
	list_item* previous; //Это поле - заготовка для превращения списка в двусвязный

	//Это конструктор,
	//Он нужен для инициализации элемента списка
	//Пока не важно как это рабоает, используйте по аналогии с вызовом в 46 строке
	list_item(int _data) : data(_data), next(nullptr), previous(nullptr) {}; // где nullptr - нулевой указатель, в Си use-ся NULL

};


//Эта структура данных необходима для работы со списком в целом
struct list {
	list_item* first; // ан-о head 
	list_item* last; // tail
	list() : first(nullptr), last(nullptr) {};

	bool is_list_empty() {
		if (first == nullptr) {
			return true;
		}
		return false;
	}

	list_item* pushback(int data, list_item* p) {
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

	// Эта штука проходится по списку и печатает элементы в порядке добавления
	void print_list() {
		list_item* p_tmp = first; // в качестве временного берем текущий первый
		while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
			cout << p_tmp->data << " "; //печатаем значение текущего элемента в отдельной строке
			p_tmp = p_tmp->next; // меняем временный на его следующий
		}
		std::cout << std::endl;
	}
	
	void print_list_back() {
		list_item* p_tmp = last; // в качестве временного берем текущий последний
		while (p_tmp != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
			cout << p_tmp->data << " "; //печатаем значение текущего элемента в отдельной строке
			p_tmp = p_tmp->previous; // меняем временный на его предыдущий - задом наперед идем
		}
		std::cout << std::endl;
	}
	
	list_item* pushfront(int data, list_item* p) {
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

	list_item* clean_list(list_item* p) {
		list_item* p_tmp = first; // в качестве временного берем текущий первый
		while (p_tmp->next != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
			p_tmp = p_tmp->next; // меняем временный на его следующий
			//cout << p_tmp->previous << endl;
			delete p_tmp->previous; //удаляем предыдущий элемент <- Ничего не делает
			//cout << p_tmp->previous;
			//cout << " del ";
			//print_list();
		}
		delete p_tmp;
		p = p_tmp = nullptr;
		flag = true;
		//cout << "del ";
		//print_list();
		return p;
	}

	list_item* clean_list_back(list_item* p) {
		list_item* p_tmp = last; // в качестве временного берем текущий последний
		while (p_tmp->previous != nullptr) { // и пока не дойдем до нулевого указателя, означающего конец
			p_tmp = p_tmp->previous; // меняем временный на его предыдущий - задом наперед идем
			delete p_tmp->next; //удаляем следующий элемент <- Ничего не делает
		}
		delete p_tmp;
		p = p_tmp = nullptr;
		flag = true;
		//cout << "del_back ";
		//print_list();
		return p;
	}

	list_item* pop_list_front(list_item* p) { //удаляем 1! элемент из начала
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

	list_item* pop_list_back(list_item* p) { //удаляем 1! элемент из начала
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
	// эта функция возвращает указатель на названный элемент
	list_item* pointer(int data) { // считаем, что названный элемент точно есть в списке
		list_item* p_tmp = first;
		while (p_tmp->data != data) {
			p_tmp = p_tmp->next;
		}
		return p_tmp;
		flag = false;
	}

	void insert_after_cur(int data, list_item* p){
		list_item* p_tmp = new list_item(data); // создаем указатель на новый узел, который пока еще не имеет ссылок ни на что
		p_tmp->next = p->next; // меняем связи, ставя новый элемент после текущего из вне
		p_tmp->previous = p;
		p->next->previous = p_tmp;
		p->next = p_tmp;
	}

	list_item* delete_cur(list_item* p) {
		if (p == first) {
			p = pop_list_front(p);
		}
		else if(p == last) {
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

	list_item* move_cur(list_item* p, bool flag_m) {
		if (flag_m) { // flag_m пользовательская настройка: 1 - вправо, 2 - влево сдвигаем
			p = p->next;
		}
		else {
			p = p->previous;
		}
		return p;
	}

	list_item* divide_list_cur(list_item* p, list_item* p_1, list_item* p_2, list& l1, list& l2) {
		list_item* p_tmp = last;
		while (p_tmp != p) {
			p_2 = l2.pushfront(p_tmp->data, p_2);
			p_tmp = p_tmp->previous;
		}
		p_tmp = first;
		while (p_tmp != p->next) {
			p_1 = l1.pushback(p_tmp->data, p_1);
			p_tmp = p_tmp->next;
		}
		cout << endl << "ВЫВОД ОШИБКИ" << endl; //не совсем ошибка, как поняла, особенность C\С++ из-за использования ассемблера при компиляции; т.е. вовзврат состоит только из одного элемента.
		cout << "p_cur1 в функции перед выходом " << p_1 << endl;
		cout << "p_cur2 в функции перед выходом " << p_2 << endl;
		return p_1, p_2;
	}

	~list(){
		cout << "Деструктор list" << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	
	list l;
	list_item *p_cur = l.first; // это ссылка на первый элемента списка, но она не меняется, когда что-то производим с этим элементом списка Why. -
	//т.к. она указывает на ту ячейку памяти, куда и указатель l.first, а когда меняется первый элемент, указатель l.first мы переносим, а вот этот - нет.
	cout << "Рассмотрим, какие методы есть у созданной нами структуры и как они работают." << endl;
	cout << "Умеем добавлять элементы в конец списка. Добавим последовательно 28, 37, 41." << endl;
	p_cur = l.pushback(28, p_cur);
	p_cur = l.pushback(37, p_cur);
	p_cur = l.pushback(41, p_cur);
	//p_cur = l.pushback(&l, 28, p_cur);
	cout << "Умеем печатать список в прямом порядке ";
	l.print_list();
	cout << " ...и обратном - ";
	l.print_list_back();
	cout << "Добавим в начало списка 2, 3, 5. Тогда: ";
	p_cur = l.pushfront(2, p_cur);
	p_cur = l.pushfront(3, p_cur);
	p_cur = l.pushfront(5, p_cur);
	l.print_list();
	cout << "Имеем в наличии указатель на выбранный элемент - текущий - который по умолчанию указывает на первый элемент в списке." << endl;
	cout << "Вернем значение, на которое ссылается указатель - " << p_cur->data << endl;
	cout << "Умеем удалять элементы из конца и начала списка - " << endl;
	cout << p_cur->data << endl;
	p_cur = l.pop_list_back(p_cur);
	//cout << p_cur->data << endl;
	p_cur = l.pop_list_front(p_cur);
	l.print_list();
	cout << "Есть возможность назначать текущий элемент по его значению, например, ";
	p_cur = l.pointer( 28);
	cout << p_cur->data << endl;
	cout << "Можем вставлять новые элементы после текущего и удалять текущий - ";
	l.insert_after_cur(101, p_cur);
	p_cur = l.delete_cur(p_cur);
	l.print_list();
	cout << "Т.к. \"текущий элемент\" был удален, указатель вернулся в начало - ";
	cout << p_cur->data << endl;
	cout << "Добавим новых элементов в начало. И выберем указателем элемент из ~середины - ";
	for (int i = 8; i < 15; i++) {
		p_cur = l.pushfront(i, p_cur);
	}
	p_cur = l.pointer( 9);
	cout << p_cur->data << endl;
	l.print_list();
	cout << "Помимо назначения по элементу, указатель мы можем просто сдвигать вправо - " << endl;
	p_cur = l.move_cur(p_cur, 1);
	cout << p_cur->data << endl;
	cout << "...и влево - " << endl;
	p_cur = l.move_cur(p_cur, 0);
	cout << p_cur->data << endl;
	cout << "Также есть метод для разделения списка на две части по текущему элементу. Однако работа продолжается только с частью, включащей элемент - левой." << endl;
	list l1;
	list l2;
	list_item* p_cur1 = l1.first;
	list_item* p_cur2 = l2.first;
	p_cur1, p_cur2 = l.divide_list_cur(p_cur, p_cur1, p_cur2, l1, l2); // в принципе, раз так, то можем получить значение как p_curi = li.first
	cout << "p_cur1 после выхода из функции " << p_cur1 << endl;
	cout << "p_cur2 после выхода из функции " << p_cur2 << endl;
	cout << "-//-" << endl;
	cout << endl << "l1" << endl;
	l1.print_list();
	cout << "l2" << endl;
	l2.print_list();
	p_cur1 = l1.first;
	p_cur2 = l2.first;
	cout << "И можем удалять список - не можем" << endl;
	//p_cur = l.clean_list(p_cur);
	//l.print_list();
	//p_cur1 = l1.clean_list(p_cur1);
	//p_cur2 = l2.clean_list_back(p_cur2);
	//l1.print_list();
	//l2.print_list();
	
	return 0;
}

