#include <trapezoid.h>

Trapezoid::Trapezoid() : Figure(4){
}

Trapezoid::Trapezoid(std::initializer_list<Point> vertices) : Trapezoid{} {
    if(vertices.size() != numVertices)
        throw std::invalid_argument("invalid number of vertices");
    std::copy(vertices.begin(), vertices.end(), points);
}

Trapezoid::~Trapezoid(){
}

bool Trapezoid::operator==(const Trapezoid &other) const {
    return compare(other);
}

Trapezoid &Trapezoid::operator=(const Trapezoid &other) {
    for (int i = 0; i < numVertices; ++i)
        points[i] = other.points[i];
    
    return *this;
}

Trapezoid &Trapezoid::operator=(Trapezoid &&other) {
    delete[] points;
    points = other.points;
    other.points = nullptr;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Trapezoid &tr) {
    os << "Trapezoid ( ";
    for(int i = 0; i < tr.numVertices; i++)
        os << tr.points[i] << ' ';
    os << ')';
    return os;
}

std::istream &operator>>(std::istream &is, Trapezoid &tr) {
    for(int i = 0; i < tr.numVertices; i++)
        is >> tr.points[i];
    return is;
}