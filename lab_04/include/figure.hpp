#pragma once

#include <memory>
#include <algorithm>
#include <stdexcept>
#include "point.hpp"

template <Scalar T>
class Figure {
protected:
    int numVertices;                                
    std::unique_ptr<Point<T>[]> points;            


    virtual void validate_figure() const = 0;

    double calculateArea() const {                
        double area = 0.0;
        for (int i = 0; i < numVertices; ++i) {
            int j = (i + 1) % numVertices;
            area += points[i].x * points[j].y - points[i].y * points[j].x;
        }
        return area / 2.0;
    }

    Point<T> calculateCenter() const {             
        double cx = 0.0, cy = 0.0;
        double area = calculateArea();

        for (int i = 0; i < numVertices; ++i) {
            int j = (i + 1) % numVertices;
            double factor = (points[i].x * points[j].y - points[j].x * points[i].y);
            cx += (points[i].x + points[j].x) * factor;
            cy += (points[i].y + points[j].y) * factor;
        }

        return Point<T>{cx / (6.0 * area), cy / (6.0 * area)};
    }

public:
    Figure(int verticesCount) : numVertices(verticesCount), points(std::make_unique<Point<T>[]>(verticesCount)) {}

    virtual ~Figure() = default;

    Figure(const Figure& other) : numVertices(other.numVertices), points(std::make_unique<Point<T>[]>(other.numVertices)) {
        std::copy(other.points.get(), other.points.get() + numVertices, points.get());
    }

    Figure(Figure&& other) noexcept : numVertices(other.numVertices), points(std::move(other.points)) {
        other.numVertices = 0; 
    }

    Figure& operator=(const Figure& other) {
        if (this != &other) {
            numVertices = other.numVertices;
            points = std::make_unique<Point<T>[]>(numVertices);
            std::copy(other.points.get(), other.points.get() + numVertices, points.get());
        }
        return *this;
    }

    Figure& operator=(Figure&& other) noexcept {
        if (this != &other) {
            numVertices = other.numVertices;
            points = std::move(other.points);
            other.numVertices = 0;
        }
        return *this;
    }

    bool operator==(const Figure& other) const {
        if (numVertices != other.numVertices) return false;

        for (int offset = 0; offset < numVertices; ++offset) {
            bool equal = true;
            for (int i = 0; i < numVertices; ++i) {
                if (!(points[i] == other.points[(i + offset) % numVertices])) {
                    equal = false;
                    break;
                }
            }
            if (equal) return true;
        }

        for (int offset = 0; offset < numVertices; ++offset) {
            bool equal = true;
            for (int i = 0; i < numVertices; ++i) {
                if (!(points[i] == other.points[(numVertices - i - 1 + offset) % numVertices])) {
                    equal = false;
                    break;
                }
            }
            if (equal) return true;
        }
        return false;
    }

    double getArea() const { return std::abs(calculateArea()); }
    operator double() const { return std::abs(calculateArea()); }
    Point<T> center() const { return calculateCenter(); }

    virtual void print(std::ostream& os) const {
        os << "Figure vertices: ";
        for (int i = 0; i < numVertices; ++i) {
            os << points[i] << " ";
        }
        os << "\n";
    }

    void read(std::istream& is) {
        for (int i = 0; i < numVertices; ++i) {
            is >> points[i];
        }
    }
};

template <Scalar T>
inline std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}

template <Scalar T>
inline std::istream& operator>>(std::istream& is, Figure<T>& fig) {
    fig.read(is);
    return is;
}
