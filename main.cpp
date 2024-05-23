#include "headers/Parser.h"
#include "headers/Pushdown.h"
#include "headers/CYK.h"

void readInput() {
    std::ifstream inputFile("input.txt");

    // read the number of states
    size_t input_cnt_states;
    inputFile >> input_cnt_states;

    // read all the states
    int current_state;
    std::vector<std::shared_ptr<State>>states;
    std::unordered_map<std::string, std::vector<std::shared_ptr<State>>>m;
    std::unordered_map<int, int>state_index;
    for (int i = 0; i < input_cnt_states; i++) {
        inputFile >> current_state;
        states.emplace_back(std::make_shared<State>(current_state, m));
        state_index[current_state] = i;
    }

    // read the number of transitions
    int input_cnt_transitions;
    inputFile >> input_cnt_transitions;

    // read the transitions and store them into a map
    int x, y;
    std::string l;
    for (int i = 0; i < input_cnt_transitions; i++) {
        inputFile >> x >> y >> l;
        states[state_index[x]]->addToTable(l, states[state_index[y]]);
    }

    // read the initial state
    int initial_state_value;
    inputFile >> initial_state_value;
    std::shared_ptr<State> initial_state = states[state_index[initial_state_value]];

    // read the number of final states;
    int input_cnt_final_states;
    inputFile >> input_cnt_final_states;

    // read the final states;
    int final_state;
    for (int i = 0; i < input_cnt_final_states; i++) {
        inputFile >> final_state;
        states[state_index[final_state]]->markFinal();
    }

    // create the lambda-nfa object
    LambdaNFA lambda_nfa(initial_state, states);

    // read the number of words to check
    int input_cnt_words;
    inputFile >> input_cnt_words;

    // read the words
    std::string input_word;
    for (int i = 0; i < input_cnt_words; i++) {
        inputFile >> input_word;
        std::cout << lambda_nfa.solve(input_word) << '\n';
    }
}

void readPDAInput() {
    std::ifstream inputFile("input.txt");

    // read the number of states
    size_t input_cnt_states;
    inputFile >> input_cnt_states;

    // read all the states
    int current_state;
    std::vector<std::shared_ptr<PushdownState>>states;
    std::unordered_map<std::string, std::vector<std::shared_ptr<PushdownState>>>m;
    std::unordered_map<int, int>state_index;
    for (int i = 0; i < input_cnt_states; i++) {
        inputFile >> current_state;
        states.emplace_back(std::make_shared<PushdownState>(current_state, m));
        state_index[current_state] = i;
    }

    // read the number of transitions
    int input_cnt_transitions;
    inputFile >> input_cnt_transitions;

    // read the transitions and store them into a map
    int x, y;
    std::string l;
    for (int i = 0; i < input_cnt_transitions; i++) {
        inputFile >> x >> y >> l;
        states[state_index[x]]->addToTable(l, states[state_index[y]]);
    }

    // read the initial state
    int initial_state_value;
    inputFile >> initial_state_value;
    std::shared_ptr<PushdownState> initial_state = states[state_index[initial_state_value]];

    // read the number of final states;
    int input_cnt_final_states;
    inputFile >> input_cnt_final_states;

    // read the final states;
    int final_state;
    for (int i = 0; i < input_cnt_final_states; i++) {
        inputFile >> final_state;
        states[state_index[final_state]]->markFinal();
    }

    // create the pushdown object
    Pushdown pushdown(initial_state, states);

    // read the number of words to check
    int input_cnt_words;
    inputFile >> input_cnt_words;

    // read the words
    std::string input_word;
    for (int i = 0; i < input_cnt_words; i++) {
        inputFile >> input_word;
        std::cout << pushdown.solve(input_word) << '\n';
    }
};

void readCYK() {
    CYK cyk;
    cyk.readGrammar();
    vector<string>inputs = {"abcd"};
    for (const auto& input: inputs) {
        if (cyk.cyk(input)) cout << "WORD " << input << " ACCEPTED!\n";
        else cout << "WORD " << input << " REJECTED!\n";
    }
}

int main() {
    readCYK();
//    readPDAInput();
//    std::string regex = "a.b.c";
//
//    Parser parser(regex);
//    LambdaNFA automata = parser.convertRegexToNFA();

    return 0;
}