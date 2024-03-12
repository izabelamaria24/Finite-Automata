#include "headers/State.h"
#include <iostream>

// constructors
State::State(size_t input_state_value, std::unordered_map<char, std::vector<State*>>&input_map)
                                    : m_state_value(input_state_value), m_table(input_map){}

// public methods
void State::addToTable(char l, State *state) {
    m_table[l].emplace_back(state);
}

void State::markFinal() {
    is_final = true;
}

size_t State::getState() const {
    return this->m_state_value;
}


// debugging
//void State::printMap() {
//    for (char i = 'a'; i <= 'b'; i++)
//        for (auto& state_it : m_table[i])
//            std::cout << m_state_value << " " << "transition " << i << state_it->m_state_value << '\n';
//}