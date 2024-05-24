#pragma once
#include "Lambda-NFA.h"

class Transducer : public LambdaNFA {
private:
    std::string outputTape;

public:
    Transducer(std::shared_ptr<State> input_initial_state, std::vector<std::shared_ptr<State>>&input_states);

    std::string parseOutput(const std::string& str);
    std::string parseInput(const std::string& str);

    bool relation(const std::string& word1, const std::string& word2);
};