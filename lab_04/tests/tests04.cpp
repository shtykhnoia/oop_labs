#include <gtest/gtest.h>
#include "rectangle.hpp"
#include "point.hpp"
#include "rhombus.hpp"
#include <sstream>

TEST(RectangleTest, TestConstructorAndValidation) {
    Rectangle<double> rect({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    std::ostringstream oss;
    rect.print(oss);
    EXPECT_EQ(oss.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");

    EXPECT_THROW(Rectangle<double>({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 5}, Point<double>{0, 6}}), std::invalid_argument);
}

TEST(RectangleTest, TestEquality) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    Rectangle<double> rect2({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    Rectangle<double> rect3({Point<double>{0, 0}, Point<double>{5, 0}, Point<double>{5, 3}, Point<double>{0, 3}});

    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
}

TEST(RectangleTest, TestCopyConstructor) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    
    Rectangle<double> rect2 = rect1;

    std::ostringstream oss;
    rect2.print(oss);
    EXPECT_EQ(oss.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");
    EXPECT_TRUE(rect1 == rect2); // Они должны быть равны
}

// Тесты для оператора присваивания
TEST(RectangleTest, TestAssignmentOperator) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    Rectangle<double> rect2({Point<double>{0, 0}, Point<double>{5, 0}, Point<double>{5, 3}, Point<double>{0, 3}});
    
    rect2 = rect1;
    std::ostringstream oss;
    rect2.print(oss);
    EXPECT_EQ(oss.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");
    EXPECT_TRUE(rect1 == rect2); // Они должны быть равны
}

// Тесты для оператора перемещения
TEST(RectangleTest, TestMoveConstructor) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    
    // Использование конструктора перемещения
    Rectangle<double> rect2 = std::move(rect1);
    std::ostringstream oss;
    rect2.print(oss);
    EXPECT_EQ(oss.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");

    // После перемещения rect1 не должен содержать данных
    std::ostringstream oss2;
    rect1.print(oss2);
    EXPECT_EQ(oss2.str(), "Rectangle vertices: \n");
}

// Тесты для оператора перемещения присваивания
TEST(RectangleTest, TestMoveAssignmentOperator) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    Rectangle<double> rect2({Point<double>{0, 0}, Point<double>{5, 0}, Point<double>{5, 3}, Point<double>{0, 3}});
    
    // Присваивание через перемещающий оператор =
    rect2 = std::move(rect1);
    std::ostringstream oss;
    rect2.print(oss);
    EXPECT_EQ(oss.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");

    // После перемещения rect1 не должен содержать данных
    std::ostringstream oss2;
    rect1.print(oss2);
    EXPECT_EQ(oss2.str(), "Rectangle vertices: \n");
}

// Тесты для работы с фигурой
TEST(FigureTest, TestFigureAssignment) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    Rectangle<double> rect2({Point<double>{0, 0}, Point<double>{5, 0}, Point<double>{5, 3}, Point<double>{0, 3}});

    // Использование оператора присваивания для базового класса
    rect2 = rect1;
    std::ostringstream oss;
    rect2.print(oss);
    EXPECT_EQ(oss.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");
    EXPECT_TRUE(rect1 == rect2); // Они должны быть равны
}

// Тесты для проверки работы с оператором преобразования в double (площадь)
TEST(RectangleTest, TestOperatorDouble) {
    Rectangle<double> rect({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    
    // Проверим, что оператор double корректно возвращает площадь
    double area = static_cast<double>(rect);
    EXPECT_EQ(area, 12.0);  // Площадь прямоугольника с шириной 4 и высотой 3 = 4 * 3
}

// Тесты для работы с центром прямоугольника
TEST(RectangleTest, TestCenter) {
    Rectangle<double> rect({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    
    // Проверим, что центр прямоугольника вычисляется корректно
    Point<double> center = rect.center();
    EXPECT_DOUBLE_EQ(center.x, 2.0);  // Ожидаем x-координату центра = 2
    EXPECT_DOUBLE_EQ(center.y, 1.5);  // Ожидаем y-координату центра = 1.5
}

TEST(RectangleTest, OperatorOutput) {
    Rectangle<double> rect{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(4, 3), Point<double>(0, 3)}};

    std::ostringstream os;
    os << rect; // Используем перегруженный оператор <<
    std::string expected_output = "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n";
    
    ASSERT_EQ(os.str(), expected_output);
}

TEST(RectangleTest, OperatorInput) {
    std::istringstream is("0 0 4 0 4 3 0 3 "); // Вводим данные о прямоугольнике
    Rectangle<double> rect{{Point<double>(0, 0), Point<double>(0, 0), Point<double>(0, 0), Point<double>(0, 0)}}; // Инициализация пустыми точками

    is >> rect; // Считываем фигуру с помощью перегруженного оператора >>

    ASSERT_DOUBLE_EQ(static_cast<double>(rect), 12.0); 
    std::ostringstream os;
    os << rect;
    ASSERT_EQ(os.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");
}

// Тест конструктора с валидными данными
TEST(RhombusTest, ValidConstruction) {
    Rhombus<double> rhombus{{Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4), Point<double>(-2, 2)}};
    EXPECT_DOUBLE_EQ(rhombus.getArea(), 8.0); // Проверяем площадь
    EXPECT_EQ(rhombus.center(), Point<double>(0, 2)); // Проверяем центр
}

// Тест конструктора с некорректными вершинами (разные стороны)
TEST(RhombusTest, InvalidConstruction) {
    EXPECT_THROW(
        Rhombus<double>({Point<double>(0, 0), Point<double>(3, 3), Point<double>(0, 5), Point<double>(-1, 2)}),
        std::invalid_argument
    );
}

// Тест конструктора с некорректным количеством точек
TEST(RhombusTest, InvalidVertexCount) {
    EXPECT_THROW(
        Rhombus<double>({Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4)}), // Только 3 вершины
        std::invalid_argument
    );
}

// Тест квадрата как валидного ромба
TEST(RhombusTest, SquareIsValidRhombus) {
    Rhombus<double> square{{Point<double>(0, 0), Point<double>(2, 0), Point<double>(2, 2), Point<double>(0, 2)}};
    EXPECT_DOUBLE_EQ(square.getArea(), 4.0); // Площадь квадрата
    EXPECT_EQ(square.center(), Point<double>(1, 1)); // Проверяем центр квадрата
}

// Тест копирующего конструктора
TEST(RhombusTest, CopyConstructor) {
    Rhombus<double> original{{Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4), Point<double>(-2, 2)}};
    Rhombus<double> copy = original;

    EXPECT_DOUBLE_EQ(copy.getArea(), original.getArea());
    EXPECT_EQ(copy.center(), original.center());
    EXPECT_EQ(copy, original);
}

// Тест перемещающего конструктора
TEST(RhombusTest, MoveConstructor) {
    Rhombus<double> original{{Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4), Point<double>(-2, 2)}};
    Rhombus<double> moved = std::move(original);

    EXPECT_DOUBLE_EQ(moved.getArea(), 8.0);
    EXPECT_EQ(moved.center(), Point<double>(0, 2));
}

// Тест оператора копирующего присваивания
TEST(RhombusTest, CopyAssignment) {
    Rhombus<double> rhombus1{{Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4), Point<double>(-2, 2)}};
    Rhombus<double> rhombus2{{Point<double>(1, 1), Point<double>(3, 3), Point<double>(1, 5), Point<double>(-1, 3)}};

    rhombus2 = rhombus1;

    EXPECT_DOUBLE_EQ(rhombus2.getArea(), rhombus1.getArea());
    EXPECT_EQ(rhombus2.center(), rhombus1.center());
    EXPECT_EQ(rhombus2, rhombus1);
}

// Тест оператора перемещающего присваивания
TEST(RhombusTest, MoveAssignment) {
    Rhombus<double> rhombus1{{Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4), Point<double>(-2, 2)}};
    Rhombus<double> rhombus2{{Point<double>(1, 1), Point<double>(3, 3), Point<double>(1, 5), Point<double>(-1, 3)}};

    rhombus2 = std::move(rhombus1);

    EXPECT_DOUBLE_EQ(rhombus2.getArea(), 8.0);
    EXPECT_EQ(rhombus2.center(), Point<double>(0, 2));
}

TEST(RhombusTest, EqualityOperator) {
    Rhombus<double> rhombus1{{Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4), Point<double>(-2, 2)}};
    Rhombus<double> rhombus2{{Point<double>(0, 0), Point<double>(2, 2), Point<double>(0, 4), Point<double>(-2, 2)}};

    EXPECT_TRUE(rhombus1 == rhombus2);
}

TEST(RhombusTest, InputOutputOperators) {
    std::istringstream is("0 0 2 2 0 4 -2 2");
    Rhombus<double> rhombus{{Point<double>(0, 0), Point<double>(0, 0), Point<double>(0, 0), Point<double>(0, 0)}};
    is >> rhombus;

    std::ostringstream os;
    os << rhombus;
    EXPECT_EQ(os.str(), "Rhombus vertices: (0, 0) (2, 2) (0, 4) (-2, 2) \n");
}

#include "trapezoid.hpp"
// Тест конструктора с валидными данными
TEST(TrapezoidTest, ValidConstruction) {
    Trapezoid<double> trapezoid{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}};
    EXPECT_DOUBLE_EQ(trapezoid.getArea(), 6.0);
}

// Тест конструктора с некорректными данными (не параллельные стороны)
TEST(TrapezoidTest, InvalidParallelConstruction) {
    EXPECT_THROW(
        Trapezoid<double>({Point<double>(0, 0), Point<double>(4, 0), Point<double>(2, 2), Point<double>(1, 2)}),
        std::invalid_argument
    );
}

// Тест конструктора с некорректными данными (неравные боковые стороны)
TEST(TrapezoidTest, InvalidSidesConstruction) {
    EXPECT_THROW(
        Trapezoid<double>({Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(0, 2)}),
        std::invalid_argument
    );
}

TEST(TrapezoidTest, InvalidVertexCount) {
    EXPECT_THROW(
        Trapezoid<double>({Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2)}),
        std::invalid_argument
    );
}

TEST(TrapezoidTest, CopyConstructor) {
    Trapezoid<double> original{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}};
    Trapezoid<double> copy = original;

    EXPECT_DOUBLE_EQ(copy.getArea(), original.getArea());
    EXPECT_EQ(copy.center(), original.center());
    EXPECT_EQ(copy, original);
}

// Тест перемещающего конструктора
TEST(TrapezoidTest, MoveConstructor) {
    Trapezoid<double> original{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}};
    Trapezoid<double> moved = std::move(original);

    EXPECT_DOUBLE_EQ(moved.getArea(), 6.0);
}

// Тест оператора копирующего присваивания
TEST(TrapezoidTest, CopyAssignment) {
    Trapezoid<double> trapezoid1{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}};
    Trapezoid<double> trapezoid2{{Point<double>(1, 1), Point<double>(5, 1), Point<double>(4, 3), Point<double>(2, 3)}};

    trapezoid2 = trapezoid1;

    EXPECT_DOUBLE_EQ(trapezoid2.getArea(), trapezoid1.getArea());
    EXPECT_EQ(trapezoid2.center(), trapezoid1.center());
    EXPECT_EQ(trapezoid2, trapezoid1);
}

// Тест оператора перемещающего присваивания
TEST(TrapezoidTest, MoveAssignment) {
    Trapezoid<double> trapezoid1{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}};
    Trapezoid<double> trapezoid2{{Point<double>(1, 1), Point<double>(5, 1), Point<double>(4, 3), Point<double>(2, 3)}};

    trapezoid2 = std::move(trapezoid1);

    EXPECT_DOUBLE_EQ(trapezoid2.getArea(), 6.0);
}

// Тест оператора сравнения ==
TEST(TrapezoidTest, EqualityOperator) {
    Trapezoid<double> trapezoid1{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}};
    Trapezoid<double> trapezoid2{{Point<double>(0, 0), Point<double>(4, 0), Point<double>(3, 2), Point<double>(1, 2)}};

    EXPECT_TRUE(trapezoid1 == trapezoid2);
}

// Тест операторов ввода/вывода
TEST(TrapezoidTest, InputOutputOperators) {
    std::istringstream is("0 0 4 0 3 2 1 2");
    Trapezoid<double> trapezoid{{Point<double>(0, 0), Point<double>(0, 0), Point<double>(0, 0), Point<double>(0, 0)}};
    is >> trapezoid;

    std::ostringstream os;
    os << trapezoid;
    EXPECT_EQ(os.str(), "Trapezoid vertices: (0, 0) (4, 0) (3, 2) (1, 2) \n");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}