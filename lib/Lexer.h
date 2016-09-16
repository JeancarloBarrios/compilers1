//
// Created by ebon1 on 9/16/16.
//

#ifndef PROYECT1_LEXER_H
#define PROYECT1_LEXER_H

#include <string>
struct NFA{

};

struct DFA{

};


class Lexer {
    NFA m_nfa;
    DFA m_dfa;
    DFA m_directDfa;
    std::string m_infixStr;


    Lexer();
    ~Lexer();

public:
    bool Construct(std::string strRegex);
    bool constructNFA();

private:
    std::string bracketPreProcessing(std::string strRegex);

};


#endif //PROYECT1_LEXER_H
