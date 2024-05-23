#include "headers/PushdownState.h"

char PushdownState::parseNextChar(const std::string &str) {
    return str[0];
}

char PushdownState::parseStackTop(const std::string &str) {
    std::size_t pos = str.find("/");
    return str[pos];
}

std::string PushdownState::parseReplace(const std::string &str) {
    std::size_t pos = str.find("/");
    return str.substr (pos);
}