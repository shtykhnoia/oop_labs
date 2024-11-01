#pragma once
#include <figure.h>

class Rectangle : public Figure {
public:
    Rectangle();
    Rectangle(std::initializer_list<Point> vertices);

    bool operator==(const Rectangle &other) const;
    Rectangle &operator=(const Rectangle &other);
    Rectangle &operator=(Rectangle &&other);

    friend std::ostream &operator<<(std::ostream &os, const Rectangle &rect);
    friend std::istream &operator>>(std::istream &is, Rectangle &rect);

    ~Rectangle();

};
