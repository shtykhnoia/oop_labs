#include "gtest/gtest.h"
#include <rhombus.h>
#include <sstream>

TEST(RhombusTests, ConstructorWithPoints) {
    Rhombus rh{{Point{0, 0}, Point{2, 2}, Point{4, 0}, Point{2, -2}}};
    EXPECT_NEAR(rh.getArea(), 8.0, 1e-3);
}

TEST(RhombusTests, DefaultConstructor) {
    Rhombus rh;
    std::stringstream input("0 0 2 2 4 0 2 -2");
    input >> rh;

    EXPECT_NEAR(rh.getArea(), 8.0, 1e-3);
}

TEST(RhombusTests, CalculateArea) {
    Rhombus rh{{Point{2, 2}, Point{4, 4}, Point{6, 2}, Point{4, 0}}};
    EXPECT_NEAR(static_cast<double>(rh), 8.0, 1e-3);
}

TEST(RhombusTests, CalculateCenter) {
    Rhombus rh{{Point{0, 0}, Point{2, 2}, Point{4, 0}, Point{2, -2}}};
    Point center = rh.center();

    EXPECT_NEAR(center.x, 2.0, 1e-3);
    EXPECT_NEAR(center.y, 0.0, 1e-3);
}

TEST(RhombusTests, EqualityOperator) {
    Rhombus rh1{{Point{0, 0}, Point{2, 2}, Point{4, 0}, Point{2, -2}}};
    Rhombus rh2{{Point{4, 0}, Point{2, -2}, Point{0, 0}, Point{2, 2}}};

    EXPECT_TRUE(rh1 == rh2);

    Rhombus rh3{{Point{1, 1}, Point{3, 3}, Point{5, 1}, Point{3, -1}}};
    EXPECT_FALSE(rh1 == rh3);
}

TEST(RhombusTests, CopyAssignmentOperator) {
    Rhombus rh1{{Point{0, 0}, Point{2, 2}, Point{4, 0}, Point{2, -2}}};
    Rhombus rh2;
    rh2 = rh1;

    EXPECT_EQ(rh1, rh2);
    EXPECT_NEAR(rh2.getArea(), 8.0, 1e-3);
}

TEST(RhombusTests, MoveAssignmentOperator) {
    Rhombus rh1{{Point{0, 0}, Point{2, 2}, Point{4, 0}, Point{2, -2}}};
    Rhombus rh2;
    rh2 = std::move(rh1);

    EXPECT_NEAR(rh2.getArea(), 8.0, 1e-3);
}

TEST(RhombusTests, StreamOutputOperator) {
    Rhombus rh{{Point{0, 0}, Point{2, 2}, Point{4, 0}, Point{2, -2}}};
    std::stringstream output;
    output << rh;

    EXPECT_EQ(output.str(), "Rhombus( {0 ,0} {2 ,2} {4 ,0} {2 ,-2} )");
}

TEST(RhombusTests, StreamInputOperator) {
    Rhombus rh;
    std::stringstream input("0 0 2 2 4 0 2 -2");
    input >> rh;

    EXPECT_NEAR(rh.getArea(), 8.0, 1e-3);
    EXPECT_EQ(rh, Rhombus({Point{0, 0}, Point{2, 2}, Point{4, 0}, Point{2, -2}}));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
