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