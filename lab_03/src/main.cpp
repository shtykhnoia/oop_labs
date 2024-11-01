#include "rectangle.h"
#include "trapezoid.h"

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
    return 0;
}