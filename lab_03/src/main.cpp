#include "rectangle.h"
#include "trapezoid.h"
#include "container.h"
#include "rhombus.h"

int main() {
    Rectangle rec{{Point{3, 0}, Point{3, 2}, Point{0, 2}, Point{0, 0}}};
    double y = double(rec);
    Point x = rec.center();
    Trapezoid tr{{Point{0, 0}, Point{1, 1}, Point{3, 1}, Point{4, 0}}};
    Point z = tr.center();
    std::cout << x  << y << '\n' <<  z << std::endl;
    Trapezoid tr1{{Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}};
    Trapezoid tr2{{Point{6, 0}, Point{4, 2}, Point{2, 2}, Point{0, 0}}};
    bool a = tr1 == tr2;
    std::cout << a;
    Container container;

    Rectangle rect({Point{0, 0}, Point{4, 0}, Point{4, 3}, Point{0, 3}});  // Площадь 12
    Rhombus rhomb({Point{0, 0}, Point{2, 2}, Point{0, 4}, Point{-2, 2}});   // Площадь 8
    Trapezoid trap({Point{0, 0}, Point{4, 0}, Point{3, 2}, Point{1, 2}}); // Площадь 8

    container.push_back(rect);
    container.push_back(rhomb);
    container.push_back(trap);

    double yy = double(container[1]);

    std::cout << yy << std::endl;
    std::cout << rhomb.getArea() << std::endl;


    return 0;
}