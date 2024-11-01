#include <rhombus.h>

Rhombus::Rhombus() : Figure(4) {
}

Rhombus::Rhombus(std::initializer_list<Point> vertices) : Rhombus{} {
    if(vertices.size() != numVertices) {
        throw std::invalid_argument("invalid number of vertices");
    }
    std::copy(vertices.begin(), vertices.end(), points);
}

Rhombus &Rhombus::operator=(const Rhombus &other) {
    for(int i = 0; i < numVertices; i++)
        points[i] = other.points[i];
    return *this;
}

Rhombus &Rhombus::operator=(Rhombus &&other) {
    delete[] points;
    points = other.points;

    other.points = nullptr;
    return *this;    
}

bool Rhombus::operator==(const Rhombus &other) const {
    return compare(other);
}

std::ostream &operator<<(std::ostream &os, const Rhombus &rh){
    os << "Rhombus( ";
    for (int i = 0; i < rh.numVertices; i++) {
        os << rh.points[i] << ' ';
    }
    return os << ')';
}

Rhombus::~Rhombus(){
}

std::istream &operator>>(std::istream &is, Rhombus &rh){
    for(int i = 0; i < rh.numVertices; i++){
        is >> rh.points[i];
    }
    return is;
}

