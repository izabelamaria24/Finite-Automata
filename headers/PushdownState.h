#pragma once
#include "State.h"

class PushdownState : public State {
private:
    std::unordered_map<std::string, std::vector<std::shared_ptr<PushdownState>>>m_pda_table;
public:
    // parse the string from the map
    // 1 -> the character from the word
    // 2 -> the character from the top of the stack
    // 3 -> replace string
    // X,Y/Z

    PushdownState(std::unordered_map<std::string, std::vector<std::shared_ptr<PushdownState>>>input_map) : m_pda_table(input_map), State(1){}
    PushdownState(size_t input_state_value, std::unordered_map<std::string, std::vector<std::shared_ptr<PushdownState>>> input_map) : State(input_state_value), m_pda_table(input_map) {}

    char parseNextChar(const std::string& str);

    char parseStackTop(const std::string& str);

    std::string parseReplace(const std::string& str);
    void addToTable(std::string l, std::shared_ptr<PushdownState>&state) {
        m_pda_table[l].emplace_back(state);
    }

    friend class Pushdown;
};