#include <gtest/gtest.h>
#include "container.h"
#include "rectangle.h"
#include "rhombus.h"
#include "trapezoid.h"

TEST(ContainerTests, DefaultConstructor) {
    Container container;
    EXPECT_EQ(container.size(), 0);
}

TEST(ContainerTests, PushBackIncreasesSize) {
    Container container;

    Rectangle rect({Point{0, 0}, Point{4, 0}, Point{4, 3}, Point{0, 3}});  
    Rhombus rhomb({Point{0, 0}, Point{2, 2}, Point{0, 4}, Point{-2, 2}});   
    Trapezoid trap({Point{0, 0}, Point{4, 0}, Point{3, 2}, Point{1, 2}});

    container.push_back(rect);
    EXPECT_EQ(container.size(), 1);

    container.push_back(rhomb);
    EXPECT_EQ(container.size(), 2);

    container.push_back(trap);
    EXPECT_EQ(container.size(), 3);
}

TEST(ContainerTests, EraseDecreasesSize) {
    Container container;

    Rectangle rect({Point{0, 0}, Point{4, 0}, Point{4, 3}, Point{0, 3}});  
    Rhombus rhomb({Point{0, 0}, Point{2, 2}, Point{0, 4}, Point{-2, 2}});   
    Trapezoid trap({Point{0, 0}, Point{4, 0}, Point{3, 2}, Point{1, 2}});

    container.push_back(rect);
    container.push_back(rhomb);
    container.push_back(trap);

    container.erase(1);

    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(static_cast<double>(container), 18); 
}

TEST(ContainerTests, EraseOutOfRangeThrows) {
    Container container;

    Rectangle rect({Point{0, 0}, Point{4, 0}, Point{4, 3}, Point{0, 3}});
    container.push_back(rect);

    EXPECT_THROW(container.erase(1), std::out_of_range);
}

TEST(ContainerTests, DoubleOperatorCalculatesTotalArea) {
    Container container;

    Rectangle rect({Point{0, 0}, Point{4, 0}, Point{4, 3}, Point{0, 3}});
    Rhombus rhomb({Point{0, 0}, Point{2, 2}, Point{0, 4}, Point{-2, 2}});  
    Trapezoid trap({Point{0, 0}, Point{4, 0}, Point{3, 2}, Point{1, 2}}); 

    container.push_back(rect);
    container.push_back(rhomb);
    container.push_back(trap);

    EXPECT_EQ(static_cast<double>(container), 26.0);
}

TEST(ContainerTests, StreamOutput) {
    Container container;

    Rectangle rect({Point{0, 0}, Point{4, 0}, Point{4, 3}, Point{0, 3}});
    Rhombus rhomb({Point{0, 0}, Point{2, 2}, Point{0, 4}, Point{-2, 2}});   

    container.push_back(rect);
    container.push_back(rhomb);

    std::ostringstream os;
    os << container;

    std::string output = os.str();
    EXPECT_NE(output.find("Figure[0]"), std::string::npos);  
    EXPECT_NE(output.find("Figure[1]"), std::string::npos);
    EXPECT_NE(output.find("Area : 12"), std::string::npos);  
    EXPECT_NE(output.find("Area : 8"), std::string::npos);   
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
