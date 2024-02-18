#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdio.h>
#include <cmath>
#include<algorithm>
#include <vector>

using namespace std;

struct Vector {
    double st_x = 0;
    double st_y;
    double end_x;
    double end_y;
    double modul = Module();
    double angle = Angle();

    double Module(); //Возвращает модуль вектора

    double Angle(); //Возвращает наклона между вектором и oсью X
    
    void rotator(double angle, Vector point); //Вращает вектор на угол angle относительно точки point 

    double operator *(const Vector& right) const;

    double operator /(const Vector& right) const;

    Vector operator +(const Vector& right) const;

    Vector operator -(const Vector& right) const;

    Vector division_scalar(const double& right) const; //скалярно

    Vector multiplication_scalar(const double& right) const;

    Vector(double x1, double y1, double x2, double y2);
    Vector(double x2, double y2);

    friend std::ostream& operator << (std::ostream& os, const Vector& b)
    {
        return os << '(' << b.st_x << ", " << b.st_y << ')' << ';' << '(' << b.end_x << ", " << b.end_y << ')';
    }
};


class Figure { //Базовый класс
public:
    virtual int T() = 0; //Функция для возвращения подтипа класса
    virtual double calc_square() = 0; //Функция для вычисления площади(виртуальная)
    virtual double calc_perimeter() = 0; //Функция для вычисления периметра(виртуальная)
    virtual Vector calc_centre() = 0; //Функция для вычисления центра масс(виртуальная)
    virtual vector<Vector> get_vertex() = 0; //Функция получения вершин(виртуальная)
    virtual bool vertex_into(Vector point) = 0; //Функция определения положения точки внутри или вне(виртуальная)
    virtual void move(double x, double y) = 0; //Функция перемещения
    virtual void resize(double angle) = 0; // Функция изменения размера
    virtual void rotate(double angle, Vector point) = 0; // Функция вращения

    friend std::ostream& operator << (std::ostream& strm, Figure& b) // Перегрузка оператора вывода в поток для вывода всех хр-к
    {
        return strm <<  "\nSquare: " << b.calc_square() << "\nPerimeter: " << b.calc_perimeter() << "\nCentre: " << b.calc_centre();
    }
};


class Polygons : public Figure { //Базовый класс(2 уровня)
public:
    virtual double calc_square() = 0; //Функция для вычbсления площади(виртуальная)
    virtual Vector calc_centre() = 0; //Функция для вычисления центра масс(виртуальная)

    // Площадь треугольника
    double sq_triangle(Vector a1, Vector a2, Vector a3) {
        return ((a2.end_x - a1.end_x) * (a3.end_y - a1.end_y) -
            ((a3.end_x - a1.end_x) * (a2.end_y - a1.end_y))) / 2;
    }
    // Центр треугольника
    Vector r_triangle(Vector a1, Vector a2, Vector a3) {
        return (a1 + a2 + a3).division_scalar(3);
    }
    //Площадь любого четырёхугольника
    double calc_sq_four(vector<Vector> sides) {
        double sq = 0;
        int j = 3;
        for (int i = 0; i < 4; i++) {
            sq += (sides.at(j).end_x + sides.at(i).end_x) * (sides.at(j).end_y - sides.at(i).end_y);
            j = i;
        }
        return abs(sq) / 2;
    }
    //Центр любого четырёхугольника
    Vector calc_centre_four(Vector z, vector<Vector> sides) {
        double sq_1 = 0;
        Vector rc_1 = Vector(0, 0);
        for (int i = 0; i < 3; i++) {
            sq_1 += sq_triangle(z, sides.at(i), sides.at(i + 1));
            rc_1 = rc_1 + r_triangle(z, sides.at(i), sides.at(i + 1)).multiplication_scalar(sq_triangle(z, sides.at(i), sides.at(i + 1)));
        }
        sq_1 += sq_triangle(z, sides.at(3), sides.at(0));
        rc_1 = rc_1 + r_triangle(z, sides.at(3), sides.at(0)).multiplication_scalar(sq_triangle(z, sides.at(3), sides.at(0)));
        return rc_1.division_scalar(sq_1);
    }
    //Функция вычисления периметра
    double calc_all_perimeter(vector<Vector> sides) {
        double sum_of_elems = 0;
        for (std::vector<Vector>::iterator it = sides.begin(); it != sides.end() - 1; ++it) {
            Vector side = *it - *(it + 1);
            sum_of_elems += side.modul;
        }
        return sum_of_elems + (*sides.begin() - *(sides.end() - 1)).modul;
    }

    //Функция принадлежания точки фигуре
    bool vertex_four_into(Vector z, vector<Vector> sides, double s) {
        double sq_1 = 0;
        for (int i = 0; i < 3; i++) {
            sq_1 += abs(sq_triangle(z, sides.at(i), sides.at(i + 1)));
        }
        sq_1 += abs(sq_triangle(z, sides.at(3), sides.at(0)));
        if (sq_1 > s) {
            return false;
        }
        else {
            return true;
        }
    }

    //Функция вращения фигуры
    vector<Vector> rotator_all(vector<Vector> sides, double angle, Vector point) {
        for (std::vector<Vector>::iterator it = sides.begin(); it != sides.end(); ++it) {
            (* it).rotator(angle, point);
        }
        return sides;
    }
};


class Triangle : public Polygons { //Треугольник
public:
    double x1, y1, x2, y2, x3, y3; //Три стороны треугольника
    Vector a1 = Vector(x1, y1);
    Vector a2 = Vector(x2, y2);
    Vector a3 = Vector(x3, y3);

    int T() { return 1; };

    double calc_square() {
        return abs(sq_triangle(a1, a2, a3));
    }

    Vector calc_centre() {
        return r_triangle(a1, a2, a3);
    }

    double calc_perimeter() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        return calc_all_perimeter(sides);
    }

    vector<Vector> get_vertex() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        cout << a1 << " - " << a2 << " - " << a3;
        return sides;
    }

    bool vertex_into(Vector point) {
        double sq_1 = 0;
        Vector rc_1 = Vector(0, 0);
        sq_1 += abs(sq_triangle(point, a1, a2));
        sq_1 += abs(sq_triangle(point, a2, a3));
        sq_1 += abs(sq_triangle(point, a3, a1));
        if (sq_1 > calc_square()) {
            return false;
        }
        else {
            return true;
        }
    }

    void move(double x, double y) {
        x1 += x;
        x2 += x;
        x3 += x;
        y1 += y;
        y2 += y;
        y3 += y;
        a1 = Vector(x1, y1);
        a2 = Vector(x2, y2);
        a3 = Vector(x3, y3);
    }

    void resize(double koef) {
        Vector new_a1 = (a1 - calc_centre()).multiplication_scalar(koef);
        Vector new_a2 = (a2 - calc_centre()).multiplication_scalar(koef);
        Vector new_a3 = (a3 - calc_centre()).multiplication_scalar(koef);
        x1 = new_a1.end_x + calc_centre().end_x;
        x2 = new_a2.end_x + calc_centre().end_x;
        x3 = new_a3.end_x + calc_centre().end_x;

        y1 = new_a1.end_y + calc_centre().end_y;
        y2 = new_a2.end_y + calc_centre().end_y;
        y3 = new_a3.end_y + calc_centre().end_y;

        a1 = Vector(x1, y1);
        a2 = Vector(x2, y2);
        a3 = Vector(x3, y3);
    }

    void rotate(double angle, Vector point) {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        vector<Vector> new_sides = rotator_all(sides, angle, point);
        a1 = new_sides.at(0);
        a2 = new_sides.at(1);
        a3 = new_sides.at(2);

        x1 = a1.end_x;
        x2 = a2.end_x;
        x3 = a3.end_x;

        y1 = a1.end_y;
        y2 = a2.end_y;
        y3 = a3.end_y;
    }

    //Конструктор
    Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
};


class Quadrilateral : public Polygons { //Четырёхугольник
private:
    double sq_triangle{};
    double r_triangle{};
public:
    double x1, y1, x2, y2, x3, y3, x4, y4;
    Vector a1 = Vector(x1, y1);
    Vector a2 = Vector(x2, y2);
    Vector a3 = Vector(x3, y3);
    Vector a4 = Vector(x4, y4);

    int T() { return 2; };

    double calc_square() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        return calc_sq_four(sides);
    }

    Vector calc_centre() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        return calc_centre_four(Vector(-1, -1), sides);
    }

    double calc_perimeter() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        return calc_all_perimeter(sides);
    }

    vector<Vector> get_vertex() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        cout << a1 << " - " << a2 << " - " << a3 << " - " << a4;
        return sides;
    }

    int sgn(double v) {
        if (v < 0) return -1;
        if (v > 0) return 1;
        return 0;
    }

    int check3(Vector a, Vector b, Vector middle)
    {
        double ax = a.end_x - middle.end_x;
        double ay = a.end_y - middle.end_y;
        double bx = b.end_x - middle.end_x;
        double by = b.end_y - middle.end_y;
        int s = sgn(ax * by - ay * bx);
        if (s == 0 && (ay == 0 || by == 0) && ax * bx <= 0)
            return 0;
        if (ay < 0 ^ by < 0)
        {
            if (by < 0)
                return s;
            return -s;
        }
        return 1;
    }

    bool vertex_into(Vector point) {
        int q = 0;
        q += check3(a1, a2, point);
        q += check3(a2, a3, point);
        q += check3(a3, a4, point);
        q += check3(a4, a1, point);
        if (q % 2 == 0) {
            return false;
        }
        else {
            return true;
        }
    }

    void move(double x, double y) {
        x1 += x;
        x2 += x;
        x3 += x;
        x4 += x;
        y1 += y;
        y2 += y;
        y3 += y;
        y4 += y;
        a1 = Vector(x1, y1);
        a2 = Vector(x2, y2);
        a3 = Vector(x3, y3);
        a4 = Vector(x4, y4);
    }

    void resize(double koef) {
        Vector new_a1 = (a1 - calc_centre()).multiplication_scalar(koef);
        Vector new_a2 = (a2 - calc_centre()).multiplication_scalar(koef);
        Vector new_a3 = (a3 - calc_centre()).multiplication_scalar(koef);
        Vector new_a4 = (a4 - calc_centre()).multiplication_scalar(koef);
        x1 = new_a1.end_x + calc_centre().end_x;
        x2 = new_a2.end_x + calc_centre().end_x;
        x3 = new_a3.end_x + calc_centre().end_x;
        x3 = new_a4.end_x + calc_centre().end_x;

        y1 = new_a1.end_y + calc_centre().end_y;
        y2 = new_a2.end_y + calc_centre().end_y;
        y3 = new_a3.end_y + calc_centre().end_y;
        y3 = new_a4.end_y + calc_centre().end_y;

        a1 = Vector(x1, y1);
        a2 = Vector(x2, y2);
        a3 = Vector(x3, y3);
        a4 = Vector(x4, y4);
    }

    void rotate(double angle, Vector point) {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        vector<Vector> new_sides = rotator_all(sides, angle, point);
        a1 = new_sides.at(0);
        a2 = new_sides.at(1);
        a3 = new_sides.at(2);
        a4 = new_sides.at(3);

        x1 = a1.end_x;
        x2 = a2.end_x;
        x3 = a3.end_x;
        x4 = a4.end_x;

        y1 = a1.end_y;
        y2 = a2.end_y;
        y3 = a3.end_y;
        y4 = a4.end_y;
    }
    //Конструктор
    Quadrilateral(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
};


class Square : public Polygons { //Квадрат
public:
    double a, x0, y0;

    double x1 = x0 - a / 2;
    double y1 = y0 - a / 2;
    double x2 = x0 - a / 2;
    double y2 = y0 + a / 2;
    double x3 = x0 + a / 2;
    double y3 = y0 + a / 2;
    double x4 = x0 + a / 2;
    double y4 = y0 - a / 2;

    Vector a1 = Vector(x1, y1);
    Vector a2 = Vector(x2, y2);
    Vector a3 = Vector(x3, y3);
    Vector a4 = Vector(x4, y4);
    
    int T() { return 3; };

    double calc_square() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        return calc_sq_four(sides);
    }

    Vector calc_centre() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        return calc_centre_four(Vector(-1, -1), sides);
    }

    double calc_perimeter() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        return calc_all_perimeter(sides);
    }

    vector<Vector> get_vertex() {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        cout << a1 << " - " << a2 << " - " << a3 << " - " << a4;
        return sides;
    }

    bool vertex_into(Vector point) {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        return vertex_four_into(point, sides, calc_square());
    }

    void move(double x, double y) {
        x1 += x;
        x2 += x;
        x3 += x;
        x4 += x;
        y1 += y;
        y2 += y;
        y3 += y;
        y4 += y;
        a1 = Vector(x1, y1);
        a2 = Vector(x2, y2);
        a3 = Vector(x3, y3);
        a4 = Vector(x4, y4);
    }

    void resize(double koef) {
        Vector new_a1 = (a1 - calc_centre()).multiplication_scalar(koef);
        Vector new_a2 = (a2 - calc_centre()).multiplication_scalar(koef);
        Vector new_a3 = (a3 - calc_centre()).multiplication_scalar(koef);
        Vector new_a4 = (a4 - calc_centre()).multiplication_scalar(koef);
        x1 = new_a1.end_x + calc_centre().end_x;
        x2 = new_a2.end_x + calc_centre().end_x;
        x3 = new_a3.end_x + calc_centre().end_x;
        x3 = new_a4.end_x + calc_centre().end_x;

        y1 = new_a1.end_y + calc_centre().end_y;
        y2 = new_a2.end_y + calc_centre().end_y;
        y3 = new_a3.end_y + calc_centre().end_y;
        y3 = new_a4.end_y + calc_centre().end_y;

        a1 = Vector(x1, y1);
        a2 = Vector(x2, y2);
        a3 = Vector(x3, y3);
        a4 = Vector(x4, y4);
        a = (a1 - a2).modul;
    }

    void rotate(double angle, Vector point) {
        vector<Vector> sides;
        sides.push_back(a1);
        sides.push_back(a2);
        sides.push_back(a3);
        sides.push_back(a4);
        vector<Vector> new_sides = rotator_all(sides, angle, point);
        cout << new_sides.at(0);
        a1 = new_sides.at(0);
        a2 = new_sides.at(1);
        a3 = new_sides.at(2);
        a4 = new_sides.at(3);

        x1 = a1.end_x;
        x2 = a2.end_x;
        x3 = a3.end_x;
        x4 = a4.end_x;

        y1 = a1.end_y;
        y2 = a2.end_y;
        y3 = a3.end_y;
        y4 = a4.end_y;
    }

    //Конструктор
    Square(double side_a, double x0, double y0);
};


class Circle : public Figure { //Круг
public:
    double r, x0, y0;
    double calc_square(){//Функция вычисления площади       
    return r;
}
    double calc_perimeter(){ //Функция вычисления периметра            
    return r;
}
    int T() { return 4; };

    Vector calc_centre() { return Vector(x0, y0); }
    //Конструктор
    Circle(double radius, double x0, double y0);

    vector<Vector> get_vertex() {
        vector<Vector> sides;
        sides.push_back(Vector(x0, y0));
        sides.push_back(Vector(0, r));
        cout << Vector(x0, y0) << " - " << Vector(0, r);
        return(sides);
    }

    bool vertex_into(Vector point) {
        if ((point - Vector(x0, y0)).modul > r) {
            return false;
        }
        else {
            return true;
        }
    }

    void move(double x, double y) {
        x0 += x;
        y0 += y;
    }

    void resize(double koef) { r *= koef; }

    void rotate(double angle, Vector point) { 
        Vector x0_y0 = Vector(x0, y0);
        x0_y0.rotator(angle, point);
        x0 = x0_y0.end_x;
        y0 = x0_y0.end_y;
    }
};


// Попытка в пересечение треугольника и треугольника, но непонимание ошибок к принемаемым объектам не даёт закончить



bool figure_intersection(Figure* figure1, Figure* figure2);

void draw_func(vector<Figure*> figures);