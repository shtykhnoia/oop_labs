#include "../include/check_brackets.h"

bool check_brackets(const std::string &expression) {
    int counter = 0;
    for (const char c: expression) {
        if (counter < 0 or (c != ' ' and c != '(' and c != ')'))  {
            return false;
        }
        if (c == '(') {
            counter += 1;

        } else if (c == ')') {
            counter -= 1;
        }
    }
    return !counter;
}