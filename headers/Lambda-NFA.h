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
    std::shared_ptr<State> m_initial_state;
    std::unordered_map<size_t, size_t>m_cycle;
    std::vector<std::shared_ptr<State>> m_states;

public:
    LambdaNFA(std::shared_ptr<State> input_initial_state, std::vector<std::shared_ptr<State>>&input_states);

    bool solve(std::string&word);
};