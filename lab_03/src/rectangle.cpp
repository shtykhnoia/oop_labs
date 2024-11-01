#include <rectangle.h>

Rectangle::Rectangle() : Figure(4)
{
}

Rectangle::Rectangle(std::initializer_list<Point> vertices) : Rectangle{}
{
    if(vertices.size() != numVertices)
        throw std::invalid_argument("invalid number of vertices");
    
    std::copy(vertices.begin(), vertices.end(), points);
}

Rectangle::operator double() {
    return Figure::getArea();
}

bool Rectangle::operator==(const Rectangle &other) const {
    return Figure::compare(other);
}

Rectangle &Rectangle::operator=(const Rectangle &other)
{
    for(int i = 0; i < numVertices; i++)
        points[i] = other.points[i];
    
    return *this;
}

Rectangle &Rectangle::operator=(Rectangle &&other){
    delete[] points;
    points = other.points;
    other.points = nullptr;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Rectangle &rec){
    os << "Rectangle( ";
    for (int i = 0; i < rec.numVertices; i++) {
        os << rec.points[i] << ' ';
    }
    return os << ')';
}

std::istream &operator>>(std::istream &is, Rectangle &rec){
    for(int i = 0; i < rec.numVertices; i++){
        is >> rec.points[i];
    }
    return is;
}

Rectangle::~Rectangle(){

}