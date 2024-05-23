#include "headers/State.h"

// constructors
State::State(size_t input_state_value, std::unordered_map<std::string, std::vector<std::shared_ptr<State>>>&input_map)
        : m_state_value(input_state_value), m_table(input_map){}

// public methods
void State::addToTable(std::string l, std::shared_ptr<State>&state) {
    m_table[l].emplace_back(state);
}

void State::markFinal() {
    is_final = true;
}

void State::markNonFinal() {
    is_final = false;
}

bool State::isFinal() const {
    return is_final;
}