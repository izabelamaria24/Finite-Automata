#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class CYK {
private:
    vector<pair<string, string>> non_terminals; // productions X -> x
    vector<pair<string, string>> terminals; // productions X -> AB

    set<string> generateCartesian(const set<string>& first, const set<string>& second);

public:
    void readGrammar();
    bool cyk(const string& word);
};