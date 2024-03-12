#pragma once
#include <unordered_map>
#include <vector>
#include <memory>

class State{
private:
    bool is_initial = false;
    bool is_final = false;
    size_t m_state_value;
    std::unordered_map<char, std::vector<State*>>m_table;

public:
    State(size_t input_state_value, std::unordered_map<char, std::vector<State*>>&input_map);
    void addToTable(char l, State*state);
    void markFinal();
    size_t getState() const;

    friend class LambdaNFA;

    // debugging
    void printMap();
};
