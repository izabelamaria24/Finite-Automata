#include "headers/Transducer.h"

// constructor
Transducer::Transducer(std::shared_ptr<State> input_initial_state, std::vector<std::shared_ptr<State>>&input_states)
        : LambdaNFA(input_initial_state, input_states), outputTape(""){};

std::string Transducer::parseOutput(const std::string &str) {
    size_t pos = str.find(':');
    return str.substr(pos + 1);
}

std::string Transducer::parseInput(const std::string &str) {
    size_t pos = str.find(':');
    return str.substr(0, pos);
}

bool Transducer::relation(const std::string &word, const std::string &word2) {
    std::stack<std::tuple<std::shared_ptr<State>, size_t, std::string>> states_to_visit;
    states_to_visit.emplace(this->m_initial_state, 0, "");

    std::unordered_map<std::shared_ptr<State>, size_t> index_to_state;

    while (!states_to_visit.empty()) {
        auto [current_state, current_index, output_string] = states_to_visit.top();
        states_to_visit.pop();

        index_to_state[current_state] = current_index;

        if (current_index == word.length() && current_state->is_final) {
            if (output_string == word2) return true;
            else continue;
        }

        if (current_index < word.length()) {
            for (auto &it : current_state->m_table) {
                if (parseInput(it.first).at(0) == word[current_index]) {
                    for (auto &next_state : it.second) {
                        states_to_visit.emplace(next_state, current_index + 1, output_string + parseOutput(it.first));
                    }

                } else if (!(parseInput(it.first) >= "a" && parseInput(it.first) <= "z")) {
                    for (auto &next_state : it.second) {
                        auto iterator = index_to_state.find(next_state);
                        if (!(iterator != index_to_state.end() && index_to_state[next_state] == current_index)) {
                            states_to_visit.emplace(next_state, current_index, output_string);
                        }
                    }
                }
            }
        }
    }

    return false;
}
