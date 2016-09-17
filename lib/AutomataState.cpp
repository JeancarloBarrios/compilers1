//
// Created by ebon1 on 9/16/16.
//

#include "AutomataState.h"
#include <sstream>

AutomataState::~AutomataState() {
    m_NFAStates.clear();
    m_transition.clear();
}

AutomataState::AutomataState(std::set<AutomataState *> NFAState, int sID) {
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

AutomataState::AutomataState(const AutomataState &other) {
    *this = other;
}

void AutomataState::addTransition(char inputChar, AutomataState *pState) {
    m_transition.insert(std::make_pair(inputChar, pState));
}

void AutomataState::removeTransition(AutomataState *pState) {
    std::multimap<char, AutomataState*>::iterator iterator;
    for (iterator = m_transition.begin(); iterator!= m_transition.end();){
        AutomataState *toSate = iterator -> second;
        if (toSate == pState){
            m_transition.erase(iterator++);
        }
        else {
            ++iterator;
        }
    }
}

void AutomataState::getTransition(char inputChar, table &States) {
    States.clear();
    std::multimap<char, AutomataState*>::iterator iterator;
    for (iterator = m_transition.lower_bound(inputChar); iterator != m_transition.upper_bound(inputChar); ++iterator){
        AutomataState *pState = iterator -> second;
        States.push_back(pState);
    }
}

std::set<AutomataState*>& AutomataState::getNFAState() {
    return m_NFAStates;
}

bool AutomataState::isDeadEnd() {
    if(m_acceptingState){
        return false;
    }
    if(m_transition.empty()){
        return true;
    }
    std::multimap<char, AutomataState*>::iterator iterator;
    for (iterator=m_transition.begin(); iterator != m_transition.end(); ++iterator){
        AutomataState *toState = iterator->second;
        if (toState!= this){
            return false;
        }
    }
    return true;
}

AutomataState& AutomataState::operator=(const AutomataState &other) {
    this->m_transition = other.m_transition;
    this->m_stateId = other.m_stateId;
    this->m_NFAStates = other.m_NFAStates;
    return *this;
}

bool AutomataState::operator==(const AutomataState &other) {
    if(m_NFAStates.empty()){
        return(m_stateId == other.m_stateId);
    }
    else{
        return(m_NFAStates == other.m_NFAStates);
    }
}

std::string AutomataState::getStringId() {
    std::stringstream out;
    out << m_stateId;
    return out.str();
}
