#include "rectangle.h"

int main() {
    Rectangle rec{{Point{3, 0}, Point{3, 2}, Point{0, 2}, Point{0, 0}}};
    double y = double(rec);
    Point x = rec.center();
    std::cout << x  << y << std::endl;
    return 0;
}