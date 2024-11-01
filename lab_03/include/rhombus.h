#pragma once

#include <figure.h>

class Rhombus : public Figure {
public:
    Rhombus();
    Rhombus(std::initializer_list<Point> vertices);
    ~Rhombus();


    bool operator==(const Rhombus &other) const;
    Rhombus &operator=(const Rhombus &other);
    Rhombus &operator=(Rhombus &&other);

    friend std::ostream &operator<<(std::ostream &os, const Rhombus &rh);
    friend std::istream &operator>>(std::istream &is, Rhombus &rh);
};

