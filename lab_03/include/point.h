#pragma once

#include <iostream>

struct Point{
    double x, y;

    bool operator==(const Point& other) const {return other.x == x && other.y == y;}

    inline friend std::ostream& operator<<(std::ostream &os, Point &p){
        return os << "{" << p.x << " ," << p.y << "}";
    }

    inline friend std::istream& operator>>(std::istream &is, Point &p){
        return is >> p.x >> p.y;
    }
};
