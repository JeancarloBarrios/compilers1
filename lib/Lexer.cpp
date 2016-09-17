//
// Created by ebon1 on 9/16/16.
//
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Lexer.h"
#include "utilities.h"


#define EPSILON       -1
#define CLOSURE       '*'
#define PLUS_CLOSURE  '+'
#define OPTIONAL      '?'
#define OPEN_PAREN    '('
#define CLOSE_PAREN   ')'
#define OR            '|'
#define EXPLICIT_CONCAT  '&'


Lexer::Lexer() {

}
Lexer::~Lexer() {

}


bool Lexer::Construct(std::string strRegex){
    while( strRegex.find("[") != std::string::npos){
        strRegex = bracketPreProcessing(strRegex);
    }


    if (!constructNFA(strRegex)){
        return false;
    }

    popTable(m_NFATable);
    m_NFATable[m_NFATable.size()-1] -> m_acceptingState = true;

}


bool Lexer::constructNFA(std::string strRegex) {
    utilities utils;
    m_postRegex = utils.infix2Postfix(strRegex);
    for(int i=0; i<(int)m_postRegex.size(); ++i){
        char currentChar = m_postRegex[i];
        if( !isOperator(currentChar)){
            pushOnCharStack(currentChar);
        }
        else {
            switch (currentChar){
                case CLOSURE:
                    closure();
                    break;
                case PLUS_CLOSURE:
                    closurePlus();
                    break;
                case OPTIONAL:
                    closureOptional();
                    break;
                case OR:
                    Or();
                    break;
                case EXPLICIT_CONCAT:
                    concate();
                    break;
            }
        }
    }
    return true;
}

bool Lexer::isOperator(char inputChar) {
    return(( inputChar == CLOSURE )        ||
           ( inputChar == OR )             ||
           ( inputChar == OPEN_PAREN )     ||
           ( inputChar == CLOSE_PAREN )    ||
           ( inputChar == PLUS_CLOSURE )   ||
           ( inputChar == EXPLICIT_CONCAT) ||
           ( inputChar == OPTIONAL ));
}

void Lexer::pushOnCharStack(char inputChar) {
    AutomataState *s0 = new AutomataState(m_nextStateId++);
    AutomataState *s1 = new AutomataState(m_nextStateId++);

    s0 -> addTransition(inputChar, s1);
    table subTable;
    subTable.push_back(s0);
    subTable.push_back(s1);
    m_charClassStack.push(subTable);
    m_inputSet.insert(inputChar);
}

bool Lexer::popTable(table &NFATable) {
    if(m_charClassStack.size()>0){
        NFATable = m_charClassStack.top();
        m_charClassStack.pop();
        return true;
    }
    return false;
}
// OPERATORS------------------------------------------------------------------------------------------------------------
bool Lexer::closure() {
    table prevTable;
    if (!popTable(prevTable)){
        return false;
    }
    AutomataState *table0 = new AutomataState(m_nextStateId++);
    AutomataState *table1 = new AutomataState(m_nextStateId++);
    table0 -> addTransition(EPSILON, table1);
    table0 -> addTransition(EPSILON, (*(prevTable.begin())));
    (*(prevTable.rbegin())) -> addTransition(EPSILON, table1);
    (*(prevTable.rbegin())) -> addTransition(EPSILON, (*(prevTable.begin())));

    prevTable.insert(prevTable.begin(), table0);
    prevTable.push_back(table1);

    m_charClassStack.push(prevTable);
    return true;

}

bool Lexer::closurePlus() {
    table prevTable;
    if(!popTable(prevTable)){
        return false;
    }
    AutomataState *table0 = new AutomataState(m_nextStateId++);
    AutomataState *table1 = new AutomataState(m_nextStateId++);

    table0 -> addTransition(EPSILON, (*(prevTable.begin())));
    (*(prevTable.rbegin())) -> addTransition(EPSILON, table1);
    (*(prevTable.rbegin())) -> addTransition(EPSILON, (*(prevTable.begin())));

    prevTable.insert(prevTable.begin(), table0);
    prevTable.push_back(table1);
    m_charClassStack.push(prevTable);

    return true;

}

bool Lexer::closureOptional() {
    table prevTable;
    if(!popTable(prevTable)){
        return false;
    }
    AutomataState *table0 = new AutomataState(m_nextStateId++);
    AutomataState *table1 = new AutomataState(m_nextStateId++);

    table0 -> addTransition(EPSILON, table1);
    table0 -> addTransition(EPSILON, (*(prevTable.begin())));
    (*(prevTable.rbegin())) -> addTransition(EPSILON, table1);

    prevTable.insert(prevTable.begin(), table0);
    prevTable.push_back(table1);
    m_charClassStack.push(prevTable);

    return true;
}

bool Lexer::Or() {
    table table0, table1;

    if(!popTable(table0) || !popTable(table1)){
        return false;
    }

    AutomataState *nTable0 = new AutomataState(m_nextStateId++);
    AutomataState *nTable1 = new AutomataState(m_nextStateId++);

    nTable0 -> addTransition(EPSILON, (*(table0.begin())));
    nTable0 -> addTransition(EPSILON, (*(table1.begin())));
    (*(table0.rbegin())) -> addTransition(EPSILON, nTable1);
    (*(table1.rbegin())) -> addTransition(EPSILON, nTable1);

    table1.push_back(nTable1);
    table0.insert(table0.begin(), nTable0);
    table0.insert(table0.end(), table1.begin(), table1.end());
    m_charClassStack.push(table0);

    return true;
}

bool Lexer::concate() {
    table table0, table1;

    if(!popTable(table0) || !popTable(table1)){
        return false;
    }

    (*(table0.rbegin())) -> addTransition(EPSILON, (*(table1.begin())));
    table0.insert(table0.end(), table1.begin(), table1.end());
    m_charClassStack.push(table0);
    return true;
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



void Lexer::printAutomata(table &table) {
    std::string tableString;
    bool initialState = true;
    tableString+= "Aceptence State \n";
    for (int i = 0; i < (int)table.size(); ++i) {
        AutomataState *pState = table[i];
        if(pState-> m_acceptingState){
            tableString+= "\t state: " + pState->getStringId() + "\t\n";
        }
    }
    tableString += "\n";
    for (int i = 0; i < (int)table.size(); ++i) {
        AutomataState *pState = table[i];
        std::vector<AutomataState*> State;
        pState -> getTransition(EPSILON, State);
        for (int j=0; j< (int)State.size(); ++j){
            if (j==0 && initialState){
                tableString += "Initial State \n \tstate: "+ pState->getStringId() + "\n \n";
                initialState = false;
            }
            tableString += "\t" + pState->getStringId() + "->" + State[j]->getStringId();
            tableString += "\t[Label = \"epsilon \"]\n";
        }
        std:: set<char>::iterator iterator;
        for(iterator = m_inputSet.begin(); iterator!=m_inputSet.end(); ++iterator){
            pState -> getTransition(*iterator, State);
            for (int j=0; j< (int)State.size(); ++j){
                tableString += "\t" + pState->getStringId() + "->" + State[j]->getStringId();
                std::stringstream out;
                out << *iterator;
                tableString += "\t[Label = \"" + out.str() + " \"]\n";
            }
        }
    }
    std::cout << tableString;
}

void Lexer::printNFA() {
    printAutomata(m_NFATable);
}