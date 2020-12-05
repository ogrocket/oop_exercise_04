#include <iostream>
#include <tuple>
#include <cmath>
#include <string>

#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Square.hpp"



template <typename T>
void Input(T &figure){
    int n = sizeof(figure.vertex) / sizeof(figure.vertex[0]);
    for (int i = 0; i < n; i++){
        std::cin >> figure.vertex[i].first >> figure.vertex[i].second;
    }
}

//Print
template <typename T, size_t index>
typename std::enable_if<index == std::tuple_size<T>::value, void>::type Print(T &){}

template <typename T, size_t index>
typename std::enable_if <index <std::tuple_size<T>::value, void>::type Print(T &t){
    auto figure = std::get<index>(t);
    std::cout << figure.name << " {";
    for (int i = 0; i < (sizeof(figure.vertex) / sizeof(figure.vertex[0])); i++){
        std::cout << "(" << figure.vertex[i].first<< ", " << figure.vertex[i].second << ") ";
    }
    std::cout << "}";
    Print<T, index+1>(t);
}

//Summary area

template<typename T, int index>
typename std::enable_if<index >= std::tuple_size<T>::value, double>::type Summary_area(T &tuple){
    return 0;
}

template<class T, int index>
typename std::enable_if<index < std::tuple_size<T>::value, double>::type Summary_area(T &tuple){
    auto figure = std::get<index>(tuple);
    double cur_area = area(figure);
    return cur_area + Summary_area<T, index + 1>(tuple);
}

//Area of Triangle
template<class T>
typename std::enable_if<(sizeof(T::x) > 0), double>::type area(T &figure){
    return figure.vertex[1].first * figure.vertex[2].second;
}

//Area of Square
template<class T>
typename std::enable_if<(sizeof(T::y) > 0), double>::type area(T &figure){
    return figure.vertex[2].first * figure.vertex[2].second;
}

//Area of Rectangle
template<class T>
typename std::enable_if<(sizeof(T::z) > 0), double>::type area(T &figure){
    return figure.vertex[2].first * figure.vertex[2].second;
}

void menu() {
    std::cout << "0. Exit\n";
    std::cout << "1. Add Triangle\n";
    std::cout << "2. Add Square\n";
    std::cout << "3. Add Rectangle\n";
    std::cout << "4. Print all the vertices of tuple's figures\n";
    std::cout << "5. Sum all areas\n";
}

int main(){
    menu();
    std::tuple<Triangle<double>, Square<double>, Rectangle<double>> tp;
    int variant;
    double l,h;
    do {
        std::cin >> variant;
        switch (variant) {
            case 1: // add Triangle
            {
                std::cout << "Enter the base of the triangle: " << std::endl;
                std::cin >> l;
                std::cout << "Enter the height of the triangle: " << std::endl;
                std::cin >> h;

                std::get<0>(tp).vertex[0].first = -l/2;
                std::get<0>(tp).vertex[0].second = 0;

                std::get<0>(tp).vertex[1].first = l/2;
                std::get<0>(tp).vertex[1].second = 0;

                std::get<0>(tp).vertex[2].first = 0;
                std::get<0>(tp).vertex[2].second = h;

                std::cout << std::get<0>(tp).name << " successfully added\n";
                break;
            }
            case 2: // add Square
            {
                 std::cout << "Enter the side of the square: ";
                 std::cin >> l;

                 std::get<1>(tp).vertex[0].first = 0;
                 std::get<1>(tp).vertex[0].second = 0;

                 std::get<1>(tp).vertex[1].first = 0;
                 std::get<1>(tp).vertex[1].second = l;

                 std::get<1>(tp).vertex[2].first = l;
                 std::get<1>(tp).vertex[2].second = l;

                 std::get<1>(tp).vertex[3].first = l;
                 std::get<1>(tp).vertex[3].second = 0;
                 std::cout << std::get<1>(tp).name << " successfully added\n";
                break;
            }
            case 3: // add Rectangle
            {
                std::cout << "Enter the first side of the rectangle: ";
                std::cin >> l;
                std::cout << "Enter the second side of the rectangle: ";
                std::cin >> h;

                std::get<2>(tp).vertex[0].first = 0;
                std::get<2>(tp).vertex[0].second = 0;

                std::get<2>(tp).vertex[1].first = 0;
                std::get<2>(tp).vertex[1].second = l;

                std::get<2>(tp).vertex[2].first = l;
                std::get<2>(tp).vertex[2].second = h;

                std::get<2>(tp).vertex[3].first = h;
                std::get<2>(tp).vertex[3].second = 0;
                std::cout << std::get<2>(tp).name << " successfully added\n";
                break;
            }
            case 4: { // all vertices
                Print<decltype(tp), 0>(tp);
                std::cout << std::endl;
                break;
            }
            case 5: { // total area
                std::cout << "Total area of tuple's figures: " << Summary_area<decltype(tp), 0>(tp) << '\n';
                break;
            }

            case 0: {
                variant = 0;
                break;
            }
        }
    } while (variant != 0);

    return 0;
}

