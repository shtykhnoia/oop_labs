#include <iostream>
#include "include/eleven.h"

int main(){
    Eleven e1("100");
    Eleven e2("1");
    Eleven result = e1.minus(e2);
    std::cout << result.equal(Eleven("AA")) << std::endl;
}
