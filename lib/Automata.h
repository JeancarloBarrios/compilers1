//
// Created by ebon1 on 9/16/16.
//

#ifndef PROYECT1_AUTOMATA_H
#define PROYECT1_AUTOMATA_H

#include <map>
#include <set>
#include <vector>
#include <string>

class Automata {

private:
    std::set<Automata*> m_NFAStates;

public:
    typedef std::vector<Automata*> table;
    typedef std::set<Automata*>::iterator stateIterator;
    std::multimap<char, Automata*> m_transition;
    int m_stateId;
    bool m_acceptingState;
    bool m_marked;
    int m_groupId;

    Automata() : m_stateId(-1), m_acceptingState(false){};
    Automata(int sID) : m_stateId(sID), m_acceptingState(false), m_groupId(0) {};
    Automata(std::set<Automata*> NFAState, int sID);
    Automata(const Automata &other);

    virtual ~Automata();

    void addTransition(char inputChar, Automata *pState);
    void removeTransition(Automata* pState);
    void getTransition(char inputChar, table &States);
    std::set<Automata*>& getNFAState();

    bool isDeadEnd();
    Automata& operator=(const Automata& other);
    bool operator==(const Automata& other);
    std::string getStringId();

};


#endif //PROYECT1_AUTOMATA_H
