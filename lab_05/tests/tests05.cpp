// pmr_list_tests.cpp

#include <gtest/gtest.h>
#include "list.hpp"
#include "customMemoryResource.h"

class PmrListTest : public ::testing::Test {
protected:
    // Инициализация перед каждым тестом
    void SetUp() override {
        resource = new CustomMemoryResource(2048);
        intList = new PmrList<int>(resource);
        structList = new PmrList<MyStruct>(resource);
    }

    // Очистка после каждого теста
    void TearDown() override {
        delete intList;
        delete structList;
        delete resource;
    }

    // Используемые в тестах объекты
    CustomMemoryResource* resource;
    PmrList<int>* intList;

    struct MyStruct {
        int id;
        double data;
        std::string name;

        bool operator==(const MyStruct& other) const {
            return id == other.id && data == other.data && name == other.name;
        }
    };

    PmrList<MyStruct>* structList;
};

TEST_F(PmrListTest, PushFrontTest) {
    intList->push_front(10);
    intList->push_front(20);
    intList->push_front(30);

    std::vector<int> expected = {30, 20, 10};
    size_t index = 0;
    for (const auto& val : *intList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, PushBackTest) {
    intList->push_back(10);
    intList->push_back(20);
    intList->push_back(30);

    std::vector<int> expected = {10, 20, 30};
    size_t index = 0;
    for (const auto& val : *intList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, InsertTest) {
    intList->push_back(10);
    intList->push_back(30);
    intList->insert(1, 20); // Вставляем 20 на позицию 1

    std::vector<int> expected = {10, 20, 30};
    size_t index = 0;
    for (const auto& val : *intList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, EraseTest) {
    intList->push_back(10);
    intList->push_back(20);
    intList->push_back(30);
    intList->erase(1); // Удаляем элемент на позиции 1 (значение 20)

    std::vector<int> expected = {10, 30};
    size_t index = 0;
    for (const auto& val : *intList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, ClearTest) {
    intList->push_back(10);
    intList->push_back(20);
    intList->clear();
    EXPECT_EQ(intList->begin(), intList->end());
}

TEST_F(PmrListTest, StructPushFrontTest) {
    structList->push_front({1, 3.14, "First"});
    structList->push_front({2, 2.71, "Second"});

    std::vector<MyStruct> expected = {
        {2, 2.71, "Second"},
        {1, 3.14, "First"}
    };

    size_t index = 0;
    for (const auto& val : *structList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, StructPushBackTest) {
    structList->push_back({1, 3.14, "First"});
    structList->push_back({2, 2.71, "Second"});

    std::vector<MyStruct> expected = {
        {1, 3.14, "First"},
        {2, 2.71, "Second"}
    };

    size_t index = 0;
    for (const auto& val : *structList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, StructInsertTest) {
    structList->push_back({1, 3.14, "First"});
    structList->push_back({3, 1.61, "Third"});
    structList->insert(1, {2, 2.71, "Second"}); // Вставляем на позицию 1

    std::vector<MyStruct> expected = {
        {1, 3.14, "First"},
        {2, 2.71, "Second"},
        {3, 1.61, "Third"}
    };

    size_t index = 0;
    for (const auto& val : *structList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, StructEraseTest) {
    structList->push_back({1, 3.14, "First"});
    structList->push_back({2, 2.71, "Second"});
    structList->push_back({3, 1.61, "Third"});
    structList->erase(1); // Удаляем элемент на позиции 1

    std::vector<MyStruct> expected = {
        {1, 3.14, "First"},
        {3, 1.61, "Third"}
    };

    size_t index = 0;
    for (const auto& val : *structList) {
        EXPECT_EQ(val, expected[index++]);
    }
}

TEST_F(PmrListTest, StructClearTest) {
    structList->push_back({1, 3.14, "First"});
    structList->push_back({2, 2.71, "Second"});
    structList->clear();
    EXPECT_EQ(structList->begin(), structList->end());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}