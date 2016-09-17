#include <iostream>
#include "../lib/utilities.h"
int main() {


    utilities utils;
    std::cout << utils.infix2Postfix("HolaMundo") << std::endl;

    return 0;
}