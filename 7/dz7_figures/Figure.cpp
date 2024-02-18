#include "Figure.h"

using namespace std;


// Функции для работы с созданной структурой векторов
Vector::Vector(double x1, double y1, double x2, double y2) : st_x(x1), st_y(y1), end_x(x2), end_y(y2) {};
Vector::Vector(double x2, double y2) : st_x(0), st_y(0), end_x(x2), end_y(y2) {};

double Vector::Module() {
	return  pow(((end_x - st_x) * (end_x - st_x) + (end_y - st_y) * (end_y - st_y)), 0.5);
}

double Vector::Angle() {
	return atan((end_y - st_y) / (end_x - st_x));
}

void Vector::rotator(double angle, Vector point = Vector(0, 0)) {//Поворот вектора влево на angle относительно point
	Vector new_Vector = Vector((*this).st_x - point.end_x, (*this).st_y - point.end_y, (*this).end_x - point.end_x, (*this).end_y - point.end_y);
	double end_x = new_Vector.end_x * cos(angle) - new_Vector.end_y * sin(angle);
	double end_y = new_Vector.end_x * sin(angle) + new_Vector.end_y * cos(angle);

	double st_x = new_Vector.st_x * cos(angle) - new_Vector.st_y * sin(angle);
	double st_y = new_Vector.st_x * sin(angle) + new_Vector.st_y * cos(angle);

	new_Vector.end_x = end_x;
	new_Vector.end_y = end_y;
	new_Vector.st_x = st_x;
	new_Vector.st_y = st_y;
	*this = Vector(st_x + point.end_x, st_y + point.end_y, end_x + point.end_x, end_y + point.end_y);
}

double Vector::operator *(const Vector & right) const {
	return modul * right.modul* cos(angle - right.angle);
}

double Vector::operator /(const Vector & right) const {
	return modul * right.modul* sin(angle - right.angle);
}

Vector Vector::operator +(const Vector & right) const {
	return Vector(st_x, st_y, end_x + right.end_x - right.st_x, end_y + right.end_y - right.st_y);
}

Vector Vector::operator -(const Vector & right) const {
	return Vector(st_x, st_y, end_x - right.end_x + right.st_x, end_y - right.end_y + right.st_y);
}

Vector Vector::division_scalar(const double& right) const {
	return Vector(st_x, st_y, st_x + (end_x - st_x) / right, st_y + (end_y - st_y) / right);
}

Vector Vector::multiplication_scalar(const double& right) const {
	return Vector(st_x, st_y, st_x + (end_x - st_x) * right, st_y + (end_y - st_y) * right);
}

// Инициализация фигур
Circle::Circle(double radius, double x0, double y0) : r(radius), x0(x0), y0(y0) {}
Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3) : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3) {}
Quadrilateral::Quadrilateral(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) : x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3), x4(x4), y4(y4) {}
Square::Square(double side_a, double x0, double y0) : a(side_a), x0(x0), y0(y0) {}

//Функция пересечения 
bool figure_intersection(Figure * figure1, Figure * figure2) {
	if (figure1->T() != 4 && figure2->T() != 4) { // Без окружностей 
		vector<Vector> sides1 = figure1->get_vertex();
		vector<Vector> sides2 = figure2->get_vertex();

		for (std::vector<Vector>::iterator it = sides1.begin(); it != sides1.end() - 1; ++it) {
			if (figure1->vertex_into(*it)) {
				return true;
			}
			Vector G_side = *it - *(it + 1);

			double a1 = (G_side.end_y - G_side.st_y) / (G_side.end_x - G_side.st_x);
			double b1 = G_side.st_y - G_side.st_x * a1;

			for (std::vector<Vector>::iterator it2 = sides2.begin(); it2 != sides2.end() - 1; ++it2) {
				if (figure2->vertex_into(*it2)) {
					return true;
				}
				Vector sub_side = *it2 - *(it2 + 1);
				double a2 = (sub_side.end_y - sub_side.st_y) / (sub_side.end_x - sub_side.st_x);
				double b2 = sub_side.st_y - sub_side.st_x * a2;

				if (a1 == a2) {
					continue;
				}
				double cx = (b2 - b1) / (a1 - a2);
				if (max(min(G_side.st_x, G_side.end_x), min(sub_side.st_x, sub_side.end_x)) <= cx && cx <= min(max(G_side.st_x, G_side.end_x), max(sub_side.st_x, sub_side.end_x))) {
					return true;
				}
			}
			// Для последней стороны
			Vector sub_side = *sides2.begin() - *sides2.end();
			double a2 = (sub_side.end_y - sub_side.st_y) / (sub_side.end_x - sub_side.st_x);
			double b2 = sub_side.st_y - sub_side.st_x * a2;

			if (a1 == a2) {
				continue;
			}
			double cx = (b2 - b1) / (a1 - a2);
			if (max(min(G_side.st_x, G_side.end_x), min(sub_side.st_x, sub_side.end_x)) <= cx && cx <= min(max(G_side.st_x, G_side.end_x), max(sub_side.st_x, sub_side.end_x))) {
				return true;
			}
		}
		// Для последней стороны
		Vector G_side = *sides1.begin() - *sides1.end();

		double a1 = (G_side.end_y - G_side.st_y) / (G_side.end_x - G_side.st_x);
		double b1 = G_side.st_y - G_side.st_x * a1;

		for (std::vector<Vector>::iterator it2 = sides2.begin(); it2 != sides2.end() - 1; ++it2) {
			if (figure2->vertex_into(*it2)) {
				return true;
			}
			Vector sub_side = *it2 - *(it2 + 1);
			double a2 = (sub_side.end_y - sub_side.st_y) / (sub_side.end_x - sub_side.st_x);
			double b2 = sub_side.st_y - sub_side.st_x * a2;

			if (a1 == a2) {
				continue;
			}
			double cx = (b2 - b1) / (a1 - a2);
			if (max(min(G_side.st_x, G_side.end_x), min(sub_side.st_x, sub_side.end_x)) <= cx && cx <= min(max(G_side.st_x, G_side.end_x), max(sub_side.st_x, sub_side.end_x))) {
				return true;
			}
		}
		Vector sub_side = *sides2.begin() - *sides2.end();
		double a2 = (sub_side.end_y - sub_side.st_y) / (sub_side.end_x - sub_side.st_x);
		double b2 = sub_side.st_y - sub_side.st_x * a2;

		double cx = (b2 - b1) / (a1 - a2);
		if (max(min(G_side.st_x, G_side.end_x), min(sub_side.st_x, sub_side.end_x)) <= cx && cx <= min(max(G_side.st_x, G_side.end_x), max(sub_side.st_x, sub_side.end_x))) {
			return true;
		}
		// Закончилась последняя сторона
		return false;
	}
	if (figure1->T() == 4 && figure2->T() == 4) { // Две окружности
		vector<Vector> sides1 = figure1->get_vertex();
		vector<Vector> sides2 = figure2->get_vertex();
		if ((sides1.at(1).modul + sides1.at(1).modul) < (sides1.at(1) - sides1.at(1)).modul) {
			return true;
		}
		return false;
	}
	if (figure1->T() == 4 || figure2->T() == 4) { // Окружность и...
		vector<Vector> sides1 = figure1->get_vertex();
		vector<Vector> sides2 = figure2->get_vertex();
		if (figure1->T() == 4) {
			Vector centre = figure1->calc_centre();
			if (figure2->vertex_into(figure1->calc_centre())) {
				return true;
			}
			for (std::vector<Vector>::iterator it2 = sides2.begin(); it2 != sides2.end() - 1; ++it2) {
				if (figure1->vertex_into(*it2)) {
					return true;
				}
				Vector sub_side = *it2 - *(it2 + 1);
				double per = abs((sub_side.end_y - sub_side.st_y) * centre.end_x - (sub_side.end_x - sub_side.st_x) * centre.end_y + sub_side.end_x * sub_side.st_y - sub_side.end_y * sub_side.st_x) / sqrt(pow(sub_side.end_y - sub_side.st_y, 2.0) + pow(sub_side.end_x - sub_side.st_x, 2.0));
				double ras = min((*it2 - centre).modul, (*(it2 + 1) - centre).modul);
				if (min(sub_side.st_x, sub_side.end_x) <= centre.end_x && centre.end_x <= max(sub_side.st_x, sub_side.end_x) && per <= sides1.at(1).modul) {
					return true;
				}
				if (min(sub_side.st_x, sub_side.end_x) >= centre.end_x || centre.end_x <= max(sub_side.st_x, sub_side.end_x) && ras <= sides1.at(1).modul) {
					return true;
				}
			}
			// Последняя сторона
			Vector sub_side = *sides2.begin() - *sides2.end();

			double per = abs((sub_side.end_y - sub_side.st_y) * centre.end_x - (sub_side.end_x - sub_side.st_x) * centre.end_y + sub_side.end_x * sub_side.st_y - sub_side.end_y * sub_side.st_x) / sqrt(pow(sub_side.end_y - sub_side.st_y, 2.0) + pow(sub_side.end_x - sub_side.st_x, 2.0));
			if (min(sub_side.st_x, sub_side.end_x) <= centre.end_x && centre.end_x <= max(sub_side.st_x, sub_side.end_x) && per <= sides1.at(1).modul) {
				return true;
			}
			// Закончилась сторона
		}
		else {
			Figure* most = figure1;
			figure1 = figure2;
			figure2 = most;
			Vector centre = figure1->calc_centre();
			if (figure2->vertex_into(figure1->calc_centre())) {
				return true;
			}
			for (std::vector<Vector>::iterator it2 = sides2.begin(); it2 != sides2.end() - 1; ++it2) {
				if (figure1->vertex_into(*it2)) {
					return true;
				}
				Vector sub_side = *it2 - *(it2 + 1);
				double per = abs((sub_side.end_y - sub_side.st_y) * centre.end_x - (sub_side.end_x - sub_side.st_x) * centre.end_y + sub_side.end_x * sub_side.st_y - sub_side.end_y * sub_side.st_x) / sqrt(pow(sub_side.end_y - sub_side.st_y, 2.0) + pow(sub_side.end_x - sub_side.st_x, 2.0));
				double ras = min((*it2 - centre).modul, (*(it2 + 1) - centre).modul);
				if (min(sub_side.st_x, sub_side.end_x) <= centre.end_x && centre.end_x <= max(sub_side.st_x, sub_side.end_x) && per <= sides1.at(1).modul) {
					return true;
				}
				if (min(sub_side.st_x, sub_side.end_x) >= centre.end_x || centre.end_x <= max(sub_side.st_x, sub_side.end_x) && ras <= sides1.at(1).modul) {
					return true;
				}
			}
			// Последняя сторона
			Vector sub_side = *sides2.begin() - *sides2.end();

			double per = abs((sub_side.end_y - sub_side.st_y) * centre.end_x - (sub_side.end_x - sub_side.st_x) * centre.end_y + sub_side.end_x * sub_side.st_y - sub_side.end_y * sub_side.st_x) / sqrt(pow(sub_side.end_y - sub_side.st_y, 2.0) + pow(sub_side.end_x - sub_side.st_x, 2.0));
			if (min(sub_side.st_x, sub_side.end_x) <= centre.end_x && centre.end_x <= max(sub_side.st_x, sub_side.end_x) && per <= sides1.at(1).modul) {
				return true;
			}
			// Закончилась сторона
		}
		return false;
	}
}


//Функция рисования
void draw_func(vector<Figure*> figures) {
	char window[120][30]{};
	for (std::vector<Figure*>::iterator it = figures.begin(); it != figures.end(); it++) {
		cout << *it;
		vector<Vector> point = (*it)->get_vertex();
		for (std::vector<Vector>::iterator it2 = point.begin(); it2 != point.end() - 1; it2++) {
			Vector side = Vector(it2->end_x, it2->end_y, (it2 + 1)->end_x, (it2 + 1)->end_y);

			double a2 = (side.end_y - side.st_y) / (side.end_x - side.st_x);
			double b2 = side.st_y - side.st_x * a2;

			for (int x = side.st_x; x <= side.end_x; x += 1) {
				double y = a2 * x + b2;
				if (x >= 0 && y >= 0) {
					if (0.4 < abs(round(y * 10) / 10 - round(y)) && abs(round(y * 10) / 10 - round(y)) < 0.6) {
						window[x][int(round(y - 0.5))] = '@';
						window[x][int(round(y + 0.5))] = '@';
					}
					else {
						window[x][int(round(y))] = '@';
					}
				}
			}
		}

	}

	for (int j = 0; j <= 29; j++) {
		for (int i = 0; i <= 120; i++) {
			if (window[i][j] == '@') {
				cout << "@";
			}
			else {
				cout << "'";
			}
		}
	}
};


