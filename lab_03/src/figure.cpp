#include <figure.h>
#include <algorithm>

Figure::Figure(int verticesCount) : numVertices(verticesCount)
{
    points = new Point[numVertices];
}

Figure::~Figure(){
    delete[] points;
}

double Figure::calculateArea() const {
    double area = 0.0;
    for (int i = 0; i < numVertices; i++) {
        int j = (i + 1) % numVertices;
        area += points[i].x * points[j].y - points[i].y * points[j].x;
    }
    return area / 2.0;
}

Point Figure::calculateCenter() const {
    double cx = 0.0;
    double cy = 0.0;
    double area = calculateArea();

    if (area > 0)
        std::reverse(points, points + numVertices);

    for(int i = 0; i < numVertices; i++){
        int j = (i + 1) % numVertices;
        cx += (points[i].x + points[j].x) * (points[i].x * points[j].y - points[i].y * points[j].x);
        cy += (points[i].y + points[j].y) * (points[i].x * points[j].y - points[i].y * points[j].x);
    }

    return Point {cx / (6.0 * area), cy / (6.0 * area)};
}

bool Figure::compare(const Figure &other) const {
    if (numVertices != other.numVertices) {
        return false;
    }

    for (int offset = 0; offset < numVertices; ++offset) {
        bool equal = true;

        for (int i = 0; i < numVertices; ++i) {
            if (!(points[i] == other.points[(i + offset) % numVertices])) {
                equal = false;
                break;
            }
        }

        if (equal) {
            return true;
        }
    }

    for (int offset = 0; offset < numVertices; ++offset) {
        bool equal = true;

        for (int i = 0; i < numVertices; ++i) {
            if (!(points[i] == other.points[(numVertices - i - 1 + offset) % numVertices])) {
                equal = false;
                break;
            }
        }

        if (equal) {
            return true;
        }
    }

    return false;
}



double Figure::getArea() const {
    return std::abs(calculateArea());
}

Point Figure::center() const {
    return calculateCenter();
}

