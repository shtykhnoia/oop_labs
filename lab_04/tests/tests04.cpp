#include <gtest/gtest.h>
#include "rectangle.hpp"
#include "point.hpp"
#include <sstream>

// Тесты для конструктора и валидации
TEST(RectangleTest, TestConstructorAndValidation) {
    // Создание прямоугольника с корректными точками
    Rectangle<double> rect({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    std::ostringstream oss;
    rect.print(oss);
    EXPECT_EQ(oss.str(), "Rectangle vertices: (0, 0) (4, 0) (4, 3) (0, 3) \n");

    // Проверка на выброс исключения при некорректных точках
    EXPECT_THROW(Rectangle<double>({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 5}, Point<double>{0, 6}}), std::invalid_argument);
}

// Тесты для оператора == (сравнение)
TEST(RectangleTest, TestEquality) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    Rectangle<double> rect2({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    Rectangle<double> rect3({Point<double>{0, 0}, Point<double>{5, 0}, Point<double>{5, 3}, Point<double>{0, 3}});

    // Проверка на равенство
    EXPECT_TRUE(rect1 == rect2);
    EXPECT_FALSE(rect1 == rect3);
}

// Тесты для конструктора копирования
TEST(RectangleTest, TestCopyConstructor) {
    Rectangle<double> rect1({Point<double>{0, 0}, Point<double>{4, 0}, Point<double>{4, 3}, Point<double>{0, 3}});
    
    // Создание нового объекта с помощью конструктора копирования
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
    
    // Присваивание через оператор =
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


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}