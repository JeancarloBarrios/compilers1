#include <iostream>
#include <stack>
#include "../lib/utilities.h"
#include "../lib/Lexer.h"
#include "testSuite.h"
int main() {


    utilities utils;
//    Lexer lex;
//    lex.construct("((([A-Z])|([a-z])))+(([A-Z])|([a-z])|([0-9]))*");
//    lex.printNFA();
//    lex.printDFA();
//    bool a = lex.simulateDFA("BCD");
//    bool b = lex.simulateDFA("whiLe");
//    bool c = lex.simulateDFA("2girls1cup");
//    bool d = lex.simulataNFA("iF");
//    bool e = lex.simulataNFA("whiLe");
//    bool f = lex.simulataNFA("2girls1cup");
//
//    std::cout << a << std::endl;
//    std::cout << b << std::endl;
//    std::cout << c << std::endl;
//    std::cout << d << std::endl;
//    std::cout << e << std::endl;
//    std::cout << f << std::endl;
    testSuite::runTests();
    return 0;
}