
//Этот код Односвязного списка
//Этот список умеет совсем немного.
//Добавлять элементы в конец себя и печатать себя.

// structure: first-[]...<->[next, data, previous]<->...[]-last

#include "list.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	
	list l;
	list::list_item *p_cur = nullptr; //тут было l.first // это ссылка на первый элемента списка, но она не меняется, когда что-то производим с этим элементом списка Why. -
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
	cout << "Также есть метод для разделения списка на две части по текущему элементу. Получаем два списка:" << endl;
	list l2;
	list::list_item* p_cur2 = nullptr; //тут было l2.first
	l.divide_list_cur(p_cur, p_cur2, l2);
	cout << "l - ";
	l.print_list();
	cout << "l2 - ";
	l2.print_list();
	cout << "При выходе из main запускается деструктор, последовательно удаляющий все элементы списков." << endl;

	return 0;
}

