#pragma once

#include "PushdownState.h"
#include <stack>

class Pushdown {
    std::vector<std::shared_ptr<PushdownState>> m_states;
    std::shared_ptr<PushdownState> m_initial_state;
    std::unordered_map<int, int>m_cycle;
    std::stack<char>m_pda_stack;

public:
    Pushdown(std::shared_ptr<PushdownState> input_initial_state, std::vector<std::shared_ptr<PushdownState>>&input_states) : m_initial_state(input_initial_state),
        m_states(input_states) {}

    void addToStack(const std::string& str);
    void removeFromStack();
    bool check(const char ch) const;
    bool solve(const std::string& word);
};