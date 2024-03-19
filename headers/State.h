#pragma once
#include <unordered_map>
#include <vector>
#include <memory>

class State{
private:
    bool is_final = false;
    size_t m_state_value;
    std::unordered_map<char, std::vector<std::shared_ptr<State>>>m_table;

public:
    State(size_t input_state_value, std::unordered_map<char, std::vector<std::shared_ptr<State>>>&input_map);
    void addToTable(char l, std::shared_ptr<State>&state);
    void markFinal();

    friend class LambdaNFA;
};