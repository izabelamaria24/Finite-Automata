#pragma once
#include <iostream>
#include <fstream>
#include "State.h"

#include <stack>
#include <set>
#include <unordered_map>
#include <vector>

class LambdaNFA{
private:
    State* m_initial_state;
    std::unordered_map<size_t, size_t>m_cycle;
    std::vector<State*> m_states;

public:
    LambdaNFA(State* input_initial_state, std::vector<State*>&input_states);

    bool solve(std::string&word);

    // debugging
//    void print();
};
