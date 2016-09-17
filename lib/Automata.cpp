//
// Created by ebon1 on 9/16/16.
//

#include "Automata.h"
#include <sstream>

Automata::~Automata() {
    m_NFAStates.clear();
    m_transition.clear();
}

Automata::Automata(std::set<Automata *> NFAState, int sID) {
    m_NFAStates = NFAState;
    m_stateId = sID;
    m_acceptingState = false;
    m_groupId = 0;
    stateIterator iterator;
    for (iterator = NFAState.begin(); iterator!= NFAState.end(); ++iterator) {
        if((*iterator) -> m_acceptingState){
            m_acceptingState = true;
        }
    }
}

Automata::Automata(const Automata &other) {
    *this = other;
}

void Automata::addTransition(char inputChar, Automata *pState) {
    m_transition.insert(std::make_pair(inputChar, pState));
}

void Automata::removeTransition(Automata *pState) {
    std::multimap<char, Automata*>::iterator iterator;
    for (iterator = m_transition.begin(); iterator!= m_transition.end();){
        Automata *toSate = iterator -> second;
        if (toSate == pState){
            m_transition.erase(iterator++);
        }
        else {
            ++iterator;
        }
    }
}

void Automata::getTransition(char inputChar, table &States) {
    States.clear();
    std::multimap<char, Automata*>::iterator iterator;
    for (iterator = m_transition.lower_bound(inputChar); iterator != m_transition.upper_bound(inputChar); ++iterator){
        Automata *pState = iterator -> second;
        States.push_back(pState);
    }
}

std::set<Automata*>& Automata::getNFAState() {
    return m_NFAStates;
}

bool Automata::isDeadEnd() {
    if(m_acceptingState){
        return false;
    }
    if(m_transition.empty()){
        return true;
    }
    std::multimap<char, Automata*>::iterator iterator;
    for (iterator=m_transition.begin(); iterator != m_transition.end(); ++iterator){
        Automata *toState = iterator->second;
        if (toState!= this){
            return false;
        }
    }
    return true;
}

Automata& Automata::operator=(const Automata &other) {
    this->m_transition = other.m_transition;
    this->m_stateId = other.m_stateId;
    this->m_NFAStates = other.m_NFAStates;
    return *this;
}

bool Automata::operator==(const Automata &other) {
    if(m_NFAStates.empty()){
        return(m_stateId == other.m_stateId);
    }
    else{
        return(m_NFAStates == other.m_NFAStates);
    }
}

std::string Automata::getStringId() {
    std::stringstream out;
    out << m_stateId;
    return out.str();
}