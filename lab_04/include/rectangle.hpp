#pragma once

#include "figure.hpp"
#include <stdexcept>

template <Scalar T>
class Rectangle : public Figure<T> {
public:
    Rectangle(std::initializer_list<Point<T>> vertices)
        : Figure<T>(4) {
        if (vertices.size() != 4) {
            throw std::invalid_argument("Rectangle must have exactly 4 vertices");
        }

        std::copy(vertices.begin(), vertices.end(), this->points.get());

        validate_figure();
    }

    void validate_figure() const override {
        const Point<T>& p0 = this->points[0];
        const Point<T>& p1 = this->points[1];
        const Point<T>& p2 = this->points[2];
        const Point<T>& p3 = this->points[3];

        if (!(p0.x == p3.x && p1.x == p2.x && p0.y == p1.y && p2.y == p3.y)) {
            throw std::invalid_argument("The given points do not form a valid rectangle.");
        }

        auto dot_product = [](const Point<T>& p1, const Point<T>& p2) {
            return p1.x * p2.x + p1.y * p2.y;
        };

        Point<T> side1{p1.x - p0.x, p1.y - p0.y};
        Point<T> side2{p2.x - p1.x, p2.y - p1.y};  
        Point<T> side3{p3.x - p2.x, p3.y - p2.y};  
        Point<T> side4{p0.x - p3.x, p0.y - p3.y};  

        if (dot_product(side1, side2) != 0 || dot_product(side2, side3) != 0 ||
            dot_product(side3, side4) != 0 || dot_product(side4, side1) != 0) {
            throw std::invalid_argument("The given points do not form a valid rectangle.");
        }
    }

    void print(std::ostream& os) const override {
        os << "Rectangle vertices: ";
        for (int i = 0; i < this->numVertices; ++i) {
            os << this->points[i] << " ";
        }
        os << "\n";
    }
};
