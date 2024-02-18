#pragma once
#include "Figure.h"

int main() {
    Figure** figure = new Figure * [5];
    cout << "Output of the program:\n";
    cout << "\nFigure #1 (triangle):";
    figure[0] = new Triangle(0, 0, 0, 3, 4, 3); //Создаем треугольник со сторонами 3, 4, 5
    cout << "\nSquare: " << figure[0]->calc_square(); //Вычисляем площадь треугольника
    cout << "\nPerimeter: " << figure[0]->calc_perimeter(); //Вычисляем периметр треугольника
    cout << "\nCentre: " << figure[0]->calc_centre(); //Вычисляем центр треугольника
    cout << "\n Poitnt (6, 6) in triangle?: " << figure[0]->vertex_into(Vector(6, 6));//Принадлежание (6; 6) данному треугольнику
    cout << "\n Poitnt (2, 2) in triangle?: " << figure[0]->vertex_into(Vector(2, 2));//Принадлежание (2; 2) данному треугольнику
    cout << "\nStart coords: ";
    figure[0]->get_vertex();
    cout << "\nAfter resize on 4 : ";
    figure[0]->resize(4);
    figure[0]->get_vertex();
    cout << "\nSquare: " << figure[0]->calc_square();//Вычисляем площадь треугольника
    cout << "\nPerimeter: " << figure[0]->calc_perimeter();//Вычисляем периметр треугольника
    cout << "\nCentre: " << figure[0]->calc_centre();//Вычисляем центр треугольника

    cout << "\n\nFigure #2 (circle):";
    figure[1] = new Circle(5, 0, 0); //Создаем круг с радиусом 5
    cout << "\nSquare: " << figure[1]->calc_square();//Вычисляем площадь круг
    cout << "\nPerimeter: " << figure[1]->calc_perimeter();//Вычисляем периметр круг
    cout << "\nCentre: " << figure[1]->calc_centre(); //Вычисляем центр круга
    cout << "\n Poitnt (6, 6) in circle?: " << figure[1]->vertex_into(Vector(6, 6));//Принадлежание (6; 6) данному кругу
    cout << "\n Poitnt (2, 2) in circle?: " << figure[1]->vertex_into(Vector(2, 2));//Принадлежание (2; 2) данному кругу

    cout << "\n\nFigure #3 (quadrilateral):";
    figure[2] = new Quadrilateral(0, 5, 3, 0, 6, 5, 3, 1); //Создаем Случайный четырёхугольник 
    cout << "\nSquare: " << figure[2]->calc_square();//Вычисляем площадь четырёхугольника
    cout << "\nPerimeter: " << figure[2]->calc_perimeter();//Вычисляем периметр четырёхугольника
    cout << "\nCentre: " << figure[2]->calc_centre();//Вычисляем центр четырёхугольника
    cout << "\n Poitnt (6, 6) in quadrilateral?: " << figure[2]->vertex_into(Vector(6, 6));//Принадлежание (6; 6) данному четырёхугольнику
    cout << "\n Poitnt (2, 2) in quadrilateral?: " << figure[2]->vertex_into(Vector(2, 2));//Принадлежание (2; 2) данному четырёхугольнику
    // cout << "\n Peresechenie s triangle(0, 0, 0, 3, 4, 3): " << figure_intersection(figure[0], figure[2]);
    cout << "\nStart coords: ";
    figure[2]->get_vertex();
    figure[2]->move(4, 4);
    cout << "\nAfter move on(4, 4) : ";
    figure[2]->get_vertex();
    cout << "\nSquare: " << figure[2]->calc_square();//Вычисляем площадь четырёхугольника
    cout << "\nPerimeter: " << figure[2]->calc_perimeter();//Вычисляем периметр четырёхугольника
    cout << "\nCentre: " << figure[2]->calc_centre();//Вычисляем центр четырёхугольника
    cout << "\nStart coords: ";
    figure[2]->get_vertex();
    cout << "\nAfter resize on 4 : ";
    figure[2]->resize(4);
    figure[2]->get_vertex();
    cout << "\nSquare: " << figure[2]->calc_square();//Вычисляем площадь четырёхугольника
    cout << "\nPerimeter: " << figure[2]->calc_perimeter();//Вычисляем периметр четырёхугольника
    cout << "\nCentre: " << figure[2]->calc_centre();//Вычисляем центр четырёхугольника

    cout << "\n\nFigure #4 (square):";
    figure[3] = new Square(5, 0, 0); //Создаем квадрат со стороной 5
    cout << "\nSquare: " << figure[3]->calc_square();//Вычисляем площадь квадрата
    cout << "\nPerimeter: " << figure[3]->calc_perimeter();//Вычисляем периметр квадрата
    cout << "\nCentre: " << figure[3]->calc_centre();//Вычисляем центр квадрата
    cout << "\n Poitnt (6, 6) in square?: " << figure[3]->vertex_into(Vector(6, 6));//Принадлежание (6; 6) данному квадрату
    cout << "\n Poitnt (2, 2) in square?: " << figure[3]->vertex_into(Vector(2, 2));//Принадлежание (2; 2) данному квадрату
    cout << "\nStart coords: ";
    figure[3]->get_vertex();
    figure[3]->rotate(M_PI / 4, figure[3]->calc_centre());
    cout << "\nAfter rotation on PI/2 otnositelno centra kvadrata: ";
    figure[3]->get_vertex();
    cout << "\nSquare: " << figure[3]->calc_square();//Вычисляем площадь квадрата
    cout << "\nPerimeter: " << figure[3]->calc_perimeter();//Вычисляем периметр квадарата
    cout << "\nCentre: " << figure[3]->calc_centre();//Вычисляем центр квадрата

    cout << "\n\nItog";
    cout << "\n Triangle";
    cout << *figure[0];
    cout << "\n Circle";
    cout << *figure[1];
    cout << "\n Quadrilateral";
    cout << *figure[2];
    cout << "\n Square";
    cout << *figure[3];

    cout << "\nPeresechenie triangle and quadrilateral: " << figure_intersection(figure[0], figure[1]) << "\n";
    
    vector<Figure*> fig;
    fig.push_back(figure[0]);
    fig.push_back(figure[1]);
    fig.push_back(figure[2]);
    fig.push_back(figure[3]);

    //draw_func(fig);

    cout << "\nuspeh";
    
    delete figure[0];
    delete figure[1];
    delete figure[2];
    delete figure[3];
    delete[] figure;
    return 0;
}