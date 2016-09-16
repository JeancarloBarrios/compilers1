//
// Created by ebon1 on 9/16/16.
//

#include "Lexer.h"

#define EPSILON       -1
#define CLOSURE       '*'
#define PLUS_CLOSURE  '+'
#define OPTIONAL      '?'
#define OPEN_PAREN    '('
#define CLOSE_PAREN   ')'
#define OR            '|'
#define EXPLICIT_CONCAT  '&'




bool Lexer::Construct(std::string strRegex){
    while( strRegex.find("[") != std::string::npos){
        strRegex = bracketPreProcessing(strRegex);
    }
    m_infixStr = const_cast<char*>(strRegex.c_str());

    if (!constructNFA()){
        return false;
    }

//    PopTable(m_nfa);
//    m_nfa[m_nfa.size()-1] -> m_AcceptingState;

}


bool Lexer::constructNFA() {

}





// Private Methods Go Here ---------------------------------------------------------------------------------------------
std::string Lexer::bracketPreProcessing(std::string strRegEx){
    std::string::size_type startPos, endPos, separatorPos;
    std::string ReplacedStrRegEx;

    startPos = strRegEx.find_first_of("[");
    endPos   = strRegEx.find_first_of("]");
    separatorPos = strRegEx.find_first_of("-");

    if ( startPos == std::string::npos || endPos == std::string::npos )
        return strRegEx;

    ReplacedStrRegEx += strRegEx.substr( 0, startPos );
    ReplacedStrRegEx.push_back('(');
    std::string result = strRegEx.substr( startPos + 1, endPos - startPos - 1);
    char first = result[0];
    char last  = result[result.size() - 1 ];

    if ( separatorPos != std::string::npos ) {
        while ( first != last ) {
            ReplacedStrRegEx.push_back(first);
            ReplacedStrRegEx += "|";
            first++;
        }
        ReplacedStrRegEx.push_back(first);
    } else {
        startPos++;
        while ( startPos != endPos - 1) {
            ReplacedStrRegEx.push_back(strRegEx[startPos]);
            ReplacedStrRegEx += "|";
            startPos++;
        }
        ReplacedStrRegEx.push_back(strRegEx[endPos - 1]);
    }
    ReplacedStrRegEx += strRegEx.substr( endPos + 1, strRegEx.size() - endPos );
    ReplacedStrRegEx += ")";

    return ReplacedStrRegEx;
}