#include <utility>
#include "./headers/Lambda-NFA.h"

// constructor
LambdaNFA::LambdaNFA(std::shared_ptr<State> input_initial_state, std::vector<std::shared_ptr<State>>&input_states)
        : m_initial_state(std::move(input_initial_state)), m_states(input_states){}

// method for process each word
bool LambdaNFA::solve(std::string&word){
    // start from the initial state

    // stack to track the states that we have to visit (we start by pushing the initial state to the stack)
    std::stack<std::pair<std::shared_ptr<State>, size_t>>states_to_visit;
    states_to_visit.emplace(this->m_initial_state, 0);

    /* this unordered map is used to mark, when visiting a state, the current index in the word that we are at
      (for detecting lambda cycles) */
    std::unordered_map<std::shared_ptr<State>, size_t>index_to_state;

    while (!states_to_visit.empty()) {
        std::shared_ptr<State> current_state = states_to_visit.top().first; // extract the current state from the stack
        size_t current_index = states_to_visit.top().second; // extract the current index from the stack

        // visit the current_state and mark that is last visited at current_index
        index_to_state[current_state] = current_index;

        states_to_visit.pop();

        /* check if we are at the end of the word and the current_state is final
        (if both conditions are true, the word is accepted) */
        if (current_index == word.length() && current_state->is_final)
            return true;

        // if the word still has characters left, iterate through all next states using the map associated with the current_state
        if (current_index <= word.length()) {
            for (auto &it: current_state->m_table) {
                // it.first -> transition character (we check if it corresponds to the current character to be processed / it is lambda)
                if (it.first == word[current_index]) {
                    // a non-lambda state will consume a character

                    // add all the next states to the stack
                    for (auto &next_state: it.second)
                        states_to_visit.emplace(next_state, current_index + 1);

                } else if (!(it.first >= 'a' && it.first <= 'z')) { // if we have lambda (this branch will be ignored in a DFA or a simple NFA!)

                    // add all the next states to the stack
                    for (auto &next_state: it.second) {
                        auto iterator = index_to_state.find(next_state); // check if we already visited next_state

                        // check for lambda cycles
                        if (!(iterator != index_to_state.end() && index_to_state[next_state] == current_index)) {
                            // if we have not visited the next_state or if we have already visited it, but at a different index,
                            // add the next_state to the stack
                            states_to_visit.emplace(next_state, current_index);
                        }
                    }
                }
            }
        }
    }

    return false;
}

void LambdaNFA::changeInitialState(std::shared_ptr<State> newInitialState) {
    m_initial_state = newInitialState;
}

std::vector<std::shared_ptr<State>>& LambdaNFA::getStates(){
    return m_states;
}

std::shared_ptr<State> LambdaNFA::getInitialState() {
    return m_initial_state;
}

void LambdaNFA::addState(std::shared_ptr<State>newState) {
    m_states.emplace_back(newState);
}

void LambdaNFA::convertNFAtoDFA() {
    std::stack<std::shared_ptr<State>>states;
    std::set<std::shared_ptr<State>>markStates;

    states.push(this->m_initial_state);

    markStates.insert(this->m_initial_state);

    while (!states.empty()) {
        std::shared_ptr<State>currentState = states.top();
        states.pop();

        for (int ch = 'a'; ch <= 'z'; ch++) {
            std::shared_ptr<State>mergedState = std::make_shared<State>(std::unordered_map<char, std::vector<std::shared_ptr<State>>>());

            if (currentState->m_table[ch].size() > 1) {
                for (auto& state : currentState->m_table[ch]) {
                    // table for each state

                    if (state->isFinal()) mergedState->markFinal();

                    for (auto it = state->m_table.begin(); it != state->m_table.end(); it++)
                    {
                        for (auto& s : state->m_table[it->first])
                            mergedState->addToTable(it->first, s);
                    }
                }

                currentState->m_table[ch] = std::vector<std::shared_ptr<State>>{mergedState};
            } else mergedState = currentState->m_table[ch][0];


            // if mergeState has not been added yet
            if (markStates.find(mergedState) == markStates.end()) {
                states.push(mergedState);
                markStates.insert(mergedState);
            }
        }
    }
}