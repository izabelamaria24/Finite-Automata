#pragma once
#include <string>
#include <utility>
#include "Lambda-NFA.h"

enum class NodeType {
    SYM, STAR, UNION, CONCAT
};

struct Node {
    char data;
    NodeType type;
    Node* left;
    Node* right;

    explicit Node(NodeType d) : data('x'), type(d), left(nullptr), right(nullptr) {}
    Node(char inputData, NodeType d) : data(inputData), type(d), left(nullptr), right(nullptr) {}
};

class Parser {
private:
    std::string regex;
    int index;

    Node* parseCharacter();

    Node* parseConcat();

    Node* parseUnion();

public:
    explicit Parser(std::string inputRegEx) : regex(std::move(inputRegEx)), index(0) {}

    Node* parse();

    LambdaNFA convertRegexToNFA();
};
