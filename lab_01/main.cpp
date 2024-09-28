#include "include/check_brackets.h"
#include "iostream"

int main() {
    std::string expression;
    getline(std::cin, expression);
    std::cout << check_brackets(expression) << std::endl;
    return 0;
}