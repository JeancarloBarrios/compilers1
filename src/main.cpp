#include <iostream>
#include <stack>
#include "../lib/utilities.h"
#include "../lib/Lexer.h"
int main() {


    utilities utils;
    Lexer lex;
    lex.Construct("av");
    lex.printNFA();
    lex.printDFA();
    bool a = lex.simulateDFA("abbabababababababababab");
    bool b = lex.simulateDFA("abbababababababababababc");
    bool c = lex.simulateDFA("av");
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    return 0;
}