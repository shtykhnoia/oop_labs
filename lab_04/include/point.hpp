#pragma once

#include <iostream>
#include <type_traits>
#include <cmath>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
struct Point {
    T x, y;

    Point() : x{0}, y{0} {}
    Point(T x, T y) : x{x}, y{y} {}

    bool operator==(const Point& other) const { return x == other.x && y == other.y; }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }
};
