#include <iostream>
#include <stack>
#include "../lib/utilities.h"
#include "../lib/Lexer.h"
int main() {


    utilities utils;
    Lexer lex;
    lex.Construct("(a|b)*|c");
    lex.printNFA();

    return 0;
}