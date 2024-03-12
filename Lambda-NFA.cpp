#include "./headers/Lamda-NFA.h"

LambdaNFA::LambdaNFA(State* input_initial_state, std::vector<State*>&input_states)
                : m_initial_state(input_initial_state), m_states(input_states){}

bool LambdaNFA::solve(std::string&word){
    // we start from initial state

    std::stack<std::pair<State*, size_t>>states_to_visit;
    states_to_visit.emplace(this->m_initial_state, 0);

//    std::set<State*>visited_states;
    std::unordered_map<State*, size_t>index_to_state; // mark the index in the word in a certain state (for lambda cycles)
    index_to_state[this->m_initial_state] = 0;

    while (!states_to_visit.empty()) {
        State* current_state = states_to_visit.top().first; // we extract the current state from the stack
        size_t current_index = states_to_visit.top().second;

        states_to_visit.pop();

        // check if we are at the end of the word, and we are in the final state
        if (current_index == word.length() && current_state->is_final)
            return true;

        if (current_index < word.length()) {
            for (auto &it: current_state->m_table) {
                // it.first -> transition character
                if (it.first == word[current_index]) {
                    // a non-lambda state will consume a character

                    // add all the next states to the stack
                    for (auto &next_state: it.second) {
                        states_to_visit.emplace(next_state, current_index + 1);
                        index_to_state[next_state] = current_index + 1;
                    }
                } else if (!(it.first >= 'a' && it.first <= 'z')) { // if we have lambda (this branch will be ignored in a DFA or a simple NFA!)
                    // add all the next states to the stack
                    for (auto &next_state: it.second) {
                        auto iterator = index_to_state.find(next_state);
                        // check for lambda cycles
                        if (!(iterator != index_to_state.end() && index_to_state[next_state] == current_index)) {
                            states_to_visit.emplace(next_state, current_index);
                            index_to_state[next_state] = current_index;
                        }
                    }
                }
            }
        }
    }

    return false;
}

// FOR DEBUGGING PURPOSES
//void LambdaNFA::print() {
//    for (auto & m_state : m_states) {
//        m_state->printMap();
//        std::cout << '\n';
//    }
//}