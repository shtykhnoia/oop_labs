#pragma once
#include "point.h"
#include <iostream>

class Figure {
public:

    virtual ~Figure();

    Point center() const;

    virtual double getArea() const;

    virtual bool compare(const Figure& other) const;

protected:

    Figure(int verticesCount);
    int numVertices;
    Point* points;

private:
    double calculateArea() const;
    Point calculateCenter() const;
    
};
