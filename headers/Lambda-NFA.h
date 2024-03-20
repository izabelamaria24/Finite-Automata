#pragma once

#include "State.h"

#include <iostream>
#include <fstream>
#include <stack>
#include <unordered_map>
#include <vector>

class LambdaNFA{
private:
    std::shared_ptr<State> m_initial_state;
    std::vector<std::shared_ptr<State>> m_states;

public:
    LambdaNFA(std::shared_ptr<State> input_initial_state, std::vector<std::shared_ptr<State>>&input_states);

    bool solve(std::string&word);
};
