#include <string>
#include <list.hpp>
#include<iostream>
#include<customMemoryResource.h>

int main() {
    // Создаем кастомный memory_resource с фиксированным размером
    CustomMemoryResource resource(2048); // Увеличен размер для демонстрации

    PmrList<int> intList(&resource);
    intList.push_back(10);
    intList.push_back(20);
    intList.push_front(5);
    intList.insert(1, 15); // Вставляем 15 на позицию 1
    intList.erase(2);      // Удаляем элемент на позиции 2

    std::cout << "Integer List:" << std::endl;
    for (const auto& val : intList) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    struct MyStruct {
        int id;
        double data;
        std::string name;

        MyStruct(int i, double d, const std::string& n)
            : id(i), data(d), name(n) {}
    };

    PmrList<MyStruct> structList(&resource);
    structList.push_back(MyStruct(1, 3.14, "First"));
    structList.push_front(MyStruct(0, 0.0, "Zero"));
    structList.insert(1, MyStruct(2, 2.71, "Inserted"));
    structList.erase(0); // Удаляем первый элемент

    std::cout << "\nStruct List:" << std::endl;
    for (const auto& val : structList) {
        std::cout << "ID: " << val.id << ", Data: " << val.data << ", Name: " << val.name << std::endl;
    }

    intList.clear();
    structList.clear();

    return 0;
}