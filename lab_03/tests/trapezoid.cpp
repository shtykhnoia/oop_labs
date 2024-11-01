#include "gtest/gtest.h"
#include <trapezoid.h>
#include <sstream>

TEST(TrapezoidTests, ConstructorWithPoints) {
    Trapezoid tr{{Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}};
    EXPECT_NEAR(tr.getArea(), 8.0, 1e-3);
}

TEST(TrapezoidTests, DefaultConstructor) {
    Trapezoid tr;
    std::stringstream input("0 0 2 2 4 2 6 0");
    input >> tr;

    EXPECT_NEAR(tr.getArea(), 8.0, 1e-3);
}

TEST(TrapezoidTests, CalculateArea) {
    Trapezoid tr{{Point{4, 0}, Point{3, 1}, Point{1, 1}, Point{0, 0}}};
    EXPECT_NEAR(static_cast<double>(tr), 3.0, 1e-3);
}

TEST(TrapezoidTests, CalculateCenter) {
    Trapezoid tr{{Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}};
    Point center = tr.center();

    EXPECT_NEAR(center.x, 3.0, 1e-3);
    EXPECT_NEAR(center.y, 0.8333, 1e-3);
}

TEST(TrapezoidTests, EqualityOperator) {
    Trapezoid tr1{{Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}};
    Trapezoid tr2{{Point{6, 0}, Point{4, 2}, Point{2, 2}, Point{0, 0}}};

    EXPECT_TRUE(tr1 == tr2);

    Trapezoid tr3{{Point{1, 1}, Point{3, 3}, Point{5, 3}, Point{7, 1}}};
    EXPECT_FALSE(tr1 == tr3);
}

TEST(TrapezoidTests, CopyAssignmentOperator) {
    Trapezoid tr1{{Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}};
    Trapezoid tr2;
    tr2 = tr1;

    EXPECT_EQ(tr1, tr2);
    EXPECT_NEAR(tr2.getArea(), 8.0, 1e-3);
}

TEST(TrapezoidTests, MoveAssignmentOperator) {
    Trapezoid tr1{{Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}};
    Trapezoid tr2;
    tr2 = std::move(tr1);

    EXPECT_NEAR(tr2.getArea(), 8.0, 1e-3);
}

TEST(TrapezoidTests, StreamOutputOperator) {
    Trapezoid tr{{Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}};
    std::stringstream output;
    output << tr;

    EXPECT_EQ(output.str(), "Trapezoid ( {0 ,0} {2 ,2} {4 ,2} {6 ,0} )");
}

TEST(TrapezoidTests, StreamInputOperator) {
    Trapezoid tr;
    std::stringstream input("0 0 2 2 4 2 6 0");
    input >> tr;

    EXPECT_NEAR(tr.getArea(), 8.0, 1e-3);
    EXPECT_EQ(tr, Trapezoid({Point{0, 0}, Point{2, 2}, Point{4, 2}, Point{6, 0}}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
