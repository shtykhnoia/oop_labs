#include "gtest/gtest.h"
#include <rectangle.h>
#include <sstream>

TEST(RectangleTests, ConstructorWithPoints) {
    Rectangle rec{{Point{0, 0}, Point{0, 2}, Point{3, 2}, Point{3, 0}}};
    EXPECT_EQ(rec.getArea(), 6.0);
}

TEST(RectangleTests, DefaultConstructor) {
    Rectangle rec;
    std::stringstream input("0 0 0 2 3 2 3 0");
    input >> rec;

    EXPECT_EQ(rec.getArea(), 6.0);
}

TEST(RectangleTests, CalculateArea) {
    Rectangle rec{{Point{3, 0}, Point{3, 2}, Point{0, 2}, Point{0, 0}}};
    EXPECT_EQ(static_cast<double>(rec), 6.0);
}

TEST(RectangleTests, CalculateCenter) {
    Rectangle rec{{Point{0, 0}, Point{0, 2}, Point{3, 2}, Point{3, 0}}};
    Point center = rec.center();
    
    EXPECT_NEAR(center.x, 1.5, 1e-3);
    EXPECT_NEAR(center.y, 1.0, 1e-3);
}

TEST(RectangleTests, EqualityOperator) {
    Rectangle rec1{{Point{0, 0}, Point{0, 2}, Point{3, 2}, Point{3, 0}}};
    Rectangle rec2{{Point{3, 2}, Point{3, 0}, Point{0, 0}, Point{0, 2}}};

    EXPECT_TRUE(rec1 == rec2);

    Rectangle rec3{{Point{1, 1}, Point{1, 3}, Point{4, 3}, Point{4, 1}}};
    EXPECT_FALSE(rec1 == rec3);
}

TEST(RectangleTests, CopyAssignmentOperator) {
    Rectangle rec1{{Point{0, 0}, Point{0, 2}, Point{3, 2}, Point{3, 0}}};
    Rectangle rec2;
    rec2 = rec1;

    EXPECT_EQ(rec1, rec2);
    EXPECT_EQ(rec2.getArea(), 6.0);
}

TEST(RectangleTests, MoveAssignmentOperator) {
    Rectangle rec1{{Point{0, 0}, Point{0, 2}, Point{3, 2}, Point{3, 0}}};
    Rectangle rec2;
    rec2 = std::move(rec1);

    EXPECT_EQ(rec2.getArea(), 6.0);
}

TEST(RectangleTests, StreamOutputOperator) {
    Rectangle rec{{Point{0, 0}, Point{0, 2}, Point{3, 2}, Point{3, 0}}};
    std::stringstream output;
    output << rec;

    EXPECT_EQ(output.str(), "Rectangle( {0 ,0} {0 ,2} {3 ,2} {3 ,0} )");
}

TEST(RectangleTests, StreamInputOperator) {
    Rectangle rec;
    std::stringstream input("0 0 0 2 3 2 3 0");
    input >> rec;

    EXPECT_EQ(rec.getArea(), 6.0);
    EXPECT_EQ(rec, Rectangle({Point{0, 0}, Point{0, 2}, Point{3, 2}, Point{3, 0}}));
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}