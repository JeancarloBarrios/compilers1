#include <iostream>
#include <stack>
#include "../lib/utilities.h"
#include "../lib/Lexer.h"
int main() {


    utilities utils;
    Lexer lex;
    lex.Construct("(a|b)*|c");
    lex.printNFA();
    lex.printDFA();
    bool a = lex.simulateDFA("abbabababababababababab");
    bool b = lex.simulateDFA("abbababababababababababc");
    bool c = lex.simulateDFA("av");
    bool d = lex.simulataNFA("abbabababababababababab");
    bool e = lex.simulataNFA("abbababababababababababc");
    bool f = lex.simulataNFA("av");

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;
    return 0;
}