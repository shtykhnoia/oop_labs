#pragma once

#include <figure.h>

class Trapezoid : public Figure {
public:
    Trapezoid();
    Trapezoid(std::initializer_list<Point> vertices);
    ~Trapezoid();

    operator double();

    bool operator==(const Trapezoid &other) const;
    Trapezoid &operator=(const Trapezoid &other);
    Trapezoid &operator=(Trapezoid &&other);

    friend std::ostream &operator<<(std::ostream &os, const Trapezoid &tr);
    friend std::istream &operator>>(std::istream &is, Trapezoid &tr);
};