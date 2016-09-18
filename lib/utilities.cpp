//
// Created by ebon1 on 9/16/16.
//

#include "utilities.h"
#include <iostream>

#include <cstring>

std::string utilities::infix2Postfix(std::string infixRegex){
    m_preRegEx = const_cast<char*>(infixRegex.c_str());
    m_currentPreProcChar = *(m_preRegEx++);
    std::cout << m_preRegEx << std::endl;
    std::cout << m_currentPreProcChar << std::endl;
    processOr();
    std::cout << "Infix: " << infixRegex << std::endl;
    std::cout << "postFix: " << m_postFixRegex << std::endl;

    return m_postFixRegex;
}

int utilities::processOr(){
    std::cout << "processOr" << std::endl;
    processConcat();
    while (m_currentPreProcChar == '|'){
        m_currentPreProcChar = *(m_preRegEx++);
        processConcat();
        m_postFixRegex += "|";
    }
    return 0;
}
int utilities::processConcat() {
    std::cout << "processConcat" << std::endl;
    processClosure();
    while (strchr(")|*+?", m_currentPreProcChar) == NULL){
        processClosure();
        m_postFixRegex+="&";
    }
    return 0;
}

int utilities::processClosure() {
    std::cout << "processClosure" << std::endl;
    processLiteral();
    while (m_currentPreProcChar != '\0' && strchr("*+?", m_currentPreProcChar) != NULL){
        m_postFixRegex += m_currentPreProcChar;
        m_currentPreProcChar = *(m_preRegEx++);
    }
    return 0;
}

int utilities::processLiteral() {
    std::cout << "processLiteral" << std::endl;
    if (m_currentPreProcChar=='\0'){
        return -1;
    }
    if (m_currentPreProcChar=='\\'){
        m_currentPreProcChar = *(m_preRegEx++);
        if(m_currentPreProcChar=='\0'){
            return -1;
        }
        m_postFixRegex += m_currentPreProcChar;
        m_currentPreProcChar = *(m_preRegEx++);
    }
    else if (strchr("()|*+?", m_currentPreProcChar) == NULL){
        if (m_currentPreProcChar == '&'){
            m_postFixRegex += "\\&";
        }
        else {
            m_postFixRegex += m_currentPreProcChar;
        }
        m_currentPreProcChar = *(m_preRegEx++);
    }
    else if (m_currentPreProcChar == '('){
        m_currentPreProcChar = *(m_preRegEx++);
        processOr();
        if (m_currentPreProcChar != ')'){
            return -1;
        }
        m_currentPreProcChar = *(m_preRegEx++);
    }
    else {
        return -1;
    }
    return 0;
}