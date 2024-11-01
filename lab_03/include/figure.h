#pragma once
#include "point.h"
#include <iostream>

class Figure {
public:

    virtual ~Figure();

    virtual Point center() const;

    double getArea() const;

    virtual operator double() const;

    bool compare(const Figure& other) const;


protected:

    Figure(int verticesCount);
    int numVertices;
    Point* points;

private:
    double calculateArea() const;
    Point calculateCenter() const;
    
};
