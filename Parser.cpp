#include "headers/Parser.h"

Node* Parser::parseUnion() {
    Node* root = parseConcat();

    while (index < regex.length() && regex[index] == '|') {
        Node* concatNode = new Node(NodeType::UNION);
        concatNode->left = root;
        index++;
        concatNode->right = parseConcat();
        root = concatNode;
    }

    return root;
}

Node* Parser::parseConcat() {
    Node* root = parseCharacter();

    while (index < regex.length() && regex[index] == '.') {
        index++;
        Node* newNode = new Node(NodeType::CONCAT);
        newNode->left = root;
        newNode->right = parseCharacter();
        root = newNode;
    }

    return root;
}

Node* Parser::parseCharacter() {
    char current = regex[index++];
    Node* root = nullptr;
    if (current == '(') {
        root = parseUnion();
        index++;
    } else root = new Node(current, NodeType::SYM);

    if (index < regex.length() && regex[index] == '*') {
        Node* kleeneNode = new Node(NodeType::STAR);
        kleeneNode->left = root;
        root = kleeneNode;
        index++;
    }

    return root;
}

Node* Parser::parse() {
    return parseUnion();
}

LambdaNFA computeConcat(LambdaNFA nfa1, LambdaNFA nfa2) {
    std::vector<std::shared_ptr<State>>states1 = nfa1.getStates();
    std::vector<std::shared_ptr<State>>states2 = nfa2.getStates();
    std::vector<std::shared_ptr<State>>mergedStates;

    std::shared_ptr<State> init1 = nfa1.getInitialState();
    std::shared_ptr<State> init2 = nfa2.getInitialState();

    for (auto& state: states1) {
        if (state->isFinal()) {
            state->addToTable('.', init2);
            state->markNonFinal();
        }
        mergedStates.emplace_back(state);
    }

    for (const auto& state: states2) mergedStates.emplace_back(state);

    return LambdaNFA(init1, mergedStates);
}

LambdaNFA computeUnion(LambdaNFA nfa1, LambdaNFA nfa2) {
    std::vector<std::shared_ptr<State>>states1 = nfa1.getStates();
    std::vector<std::shared_ptr<State>>states2 = nfa2.getStates();
    std::vector<std::shared_ptr<State>>mergedStates;

    std::shared_ptr<State> init1 = nfa1.getInitialState();
    std::shared_ptr<State> init2 = nfa2.getInitialState();

    std::shared_ptr<State>startState = std::make_shared<State>(std::unordered_map<char, std::vector<std::shared_ptr<State>>>());
    startState->addToTable('.', init1);
    startState->addToTable('.', init2);

    mergedStates.emplace_back(startState);
    for (const auto& state: states1) mergedStates.emplace_back(state);
    for (const auto& state: states2) mergedStates.emplace_back(state);

    return LambdaNFA(startState, mergedStates);
}

LambdaNFA computeStar(LambdaNFA nfa) {
    std::shared_ptr<State>startState = std::make_shared<State>(std::unordered_map<char, std::vector<std::shared_ptr<State>>>());
    startState->markFinal();

    std::shared_ptr<State> init = nfa.getInitialState();
    startState->addToTable('.', init);

    nfa.addState(startState);

    std::vector<std::shared_ptr<State>>states = nfa.getStates();
    for (auto& state: states) {
        if (state->isFinal())
            state->addToTable('.', init);
    }

    return nfa;
}

LambdaNFA computeCharNFA(char tag) {
    std::shared_ptr<State> initialState = std::make_shared<State>(std::unordered_map<char, std::vector<std::shared_ptr<State>>>());
    std::shared_ptr<State> finalState = std::make_shared<State>(std::unordered_map<char, std::vector<std::shared_ptr<State>>>());
    initialState->addToTable(tag, finalState);
    finalState->markFinal();

    std::vector<std::shared_ptr<State>>states;
    states.emplace_back(initialState);
    states.emplace_back(finalState);

    return LambdaNFA(initialState, states);
}

LambdaNFA constructNFA(Node* parseTree) {
    if (parseTree != nullptr) {
        if (parseTree->type == NodeType::UNION)
            return computeUnion(constructNFA(parseTree->left), constructNFA(parseTree->right));
        if (parseTree->type == NodeType::CONCAT)
            return computeConcat(constructNFA(parseTree->left), constructNFA(parseTree->right));
        if (parseTree->type == NodeType::STAR)
            return computeStar(constructNFA(parseTree->left));
        if (parseTree->type == NodeType::SYM)
            return computeCharNFA(parseTree->data);
    }
}

LambdaNFA Parser::convertRegexToNFA() {
    // STEP 1: Build the parse tree
    Node* parseTree = this->parse();

    // STEP 2: Traverse the parse tree to construct the automata
    return constructNFA(parseTree);
}