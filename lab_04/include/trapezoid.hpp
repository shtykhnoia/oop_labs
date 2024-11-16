#pragma once

#include "figure.hpp"
#include <stdexcept>
#include <cmath>

template <Scalar T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid(std::initializer_list<Point<T>> vertices)
        : Figure<T>(4) {
        if (vertices.size() != 4) {
            throw std::invalid_argument("Trapezoid must have exactly 4 vertices");
        }

        std::copy(vertices.begin(), vertices.end(), this->points.get());
        validate_figure();
    }

    void validate_figure() const override {
        const Point<T>& p0 = this->points[0];
        const Point<T>& p1 = this->points[1];
        const Point<T>& p2 = this->points[2];
        const Point<T>& p3 = this->points[3];

        auto is_parallel = [](const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
            return (b.y - a.y) * (d.x - c.x) == (d.y - c.y) * (b.x - a.x);
        };

        if (!is_parallel(p0, p1, p2, p3)) {
            throw std::invalid_argument("The bases are not parallel, not a trapezoid.");
        }

        auto side_length = [](const Point<T>& a, const Point<T>& b) {
            return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
        };

        if (side_length(p0, p3) != side_length(p1, p2)) {
            throw std::invalid_argument("The non-parallel sides are not equal, not an isosceles trapezoid.");
        }
    }

    void print(std::ostream& os) const override {
        os << "Trapezoid vertices: ";
        for (int i = 0; i < this->numVertices; ++i) {
            os << this->points[i] << " ";
        }
        os << "\n";
    }
};
