#pragma once

#include "figure.hpp"
#include <stdexcept>
#include <cmath>

template <Scalar T>
class Rhombus : public Figure<T> {
public:
    Rhombus(std::initializer_list<Point<T>> vertices)
        : Figure<T>(4) {
        if (vertices.size() != 4) {
            throw std::invalid_argument("Rhombus must have exactly 4 vertices.");
        }

        std::copy(vertices.begin(), vertices.end(), this->points.get());

        validate_figure();
    }

    void validate_figure() const override {
        const Point<T>& p0 = this->points[0];
        const Point<T>& p1 = this->points[1];
        const Point<T>& p2 = this->points[2];
        const Point<T>& p3 = this->points[3];

        auto distance_squared = [](const Point<T>& a, const Point<T>& b) {
            return std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2);
        };

        T side1 = distance_squared(p0, p1);
        T side2 = distance_squared(p1, p2);
        T side3 = distance_squared(p2, p3);
        T side4 = distance_squared(p3, p0);

        if (side1 != side2 || side2 != side3 || side3 != side4) {
            throw std::invalid_argument("The given points do not form a valid rhombus.");
        }
    }

    void print(std::ostream& os) const override {
        os << "Rhombus vertices: ";
        for (int i = 0; i < this->numVertices; ++i) {
            os << this->points[i] << " ";
        }
        os << "\n";
    }
};
