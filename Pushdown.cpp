#include "headers/Pushdown.h"

void Pushdown::addToStack(const std::string &str) {
    for (const auto& ch : str)
        this->m_pda_stack.push(ch);
}

void Pushdown::removeFromStack() {
    this->m_pda_stack.pop();
}

bool Pushdown::check(const char ch) const {
    return this->m_pda_stack.top() == ch;
}

bool Pushdown::solve(const std::string &word) {
    // start from the initial state

    // stack to track the states that we have to visit (we start by pushing the initial state to the stack)
    std::stack<std::pair<std::shared_ptr<PushdownState>, size_t>>states_to_visit;
    states_to_visit.emplace(this->m_initial_state, 0);

    /* this unordered map is used to mark, when visiting a state, the current index in the word that we are at
      (for detecting lambda cycles) */
    std::unordered_map<std::shared_ptr<PushdownState>, size_t>index_to_state;

    while (!states_to_visit.empty()) {
        std::shared_ptr<PushdownState> current_state = states_to_visit.top().first; // extract the current state from the stack
        size_t current_index = states_to_visit.top().second; // extract the current index from the stack

        // visit the current_state and mark that is last visited at current_index
        index_to_state[current_state] = current_index;

        states_to_visit.pop();

        /* check if we are at the end of the word and the current_state is final and the stack is empty
        (if both conditions are true, the word is accepted) */
        if (current_index == word.length() && current_state->is_final && m_pda_stack.empty())
            return true;

        // if the word still has characters left, iterate through all next states using the map associated with the current_state
        if (current_index <= word.length()) {
            for (auto &it: current_state->m_pda_table) {
                char transitionCh = current_state->parseNextChar(it.first);
                char stackCh = current_state->parseStackTop(it.first);

                if (transitionCh == word[current_index] && this->check(stackCh)) {
                    // a non-lambda state will consume a character

                    removeFromStack();
                    addToStack(current_state->parseReplace(it.first)); // we add all the characters into the stack

                    // add all the next states to the stack
                    for (auto &next_state: it.second)
                        states_to_visit.emplace(next_state, current_index + 1);

                } else if (!(transitionCh >= 'a' && transitionCh <= 'z') && this->check(stackCh)) { // if we have lambda (this branch will be ignored in a DFA or a simple NFA!)

                    // add all the next states to the stack
                    for (auto &next_state: it.second) {
                        auto iterator = index_to_state.find(next_state); // check if we already visited next_state

                        // check for lambda cycles
                        if (!(iterator != index_to_state.end() && index_to_state[next_state] == current_index)) {
                            // if we have not visited the next_state or if we have already visited it, but at a different index,
                            // add the next_state to the stack
                            // also add and remove from stack
                            removeFromStack();
                            addToStack(current_state->parseReplace(it.first));

                            states_to_visit.emplace(next_state, current_index);
                        }
                    }
                }
            }
        }
    }

    return false;
}