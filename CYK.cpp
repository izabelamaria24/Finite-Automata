#include "headers/CYK.h"

set<string> CYK::generateCartesian(const set<string>&str1, const set<string>&str2) {
    set<string> res;
    for (const auto& ch1 : str1) {
        for (const auto&ch2 : str2) {
            res.insert(ch1 + ch2);
        }
    }
    return res;
}

void CYK::readGrammar() {
    ifstream fin("grammar.txt");
    string line;

    while (getline(fin, line)) {
        size_t arrowPos = line.find("->");

        string left = line.substr(0, arrowPos);
        string right = line.substr(arrowPos + 2);

        left.erase(remove(left.begin(), left.end(), ' '), left.end());
        right.erase(remove(right.begin(), right.end(), ' '), right.end());

        stringstream stream(right); // parse the productions
        string production;
        while (getline(stream, production, '|')) {
            production.erase(remove(production.begin(), production.end(), ' '), production.end());

            if (!production.empty()) {
                if (islower(production[0]) && production.size() == 1)
                    terminals.emplace_back(left, production); // terminal
                else if (isupper(production[0]) && production.size() == 2) {
                    non_terminals.emplace_back(left, production); // variables
                } else {
                    cerr << "ERROR! PLEASE PROVIDE VALID GRAMMAR!";
                }
            }
        }
    }

    fin.close();
}

bool CYK::cyk(const string &word) {
    // method to check if a word is accepted by the grammar

    vector<vector<set<string>>> table(word.size(), vector<set<string>>(word.size()));
    vector<string>sl, sr;
    for (const auto& var : non_terminals) {
        sl.emplace_back(var.first);
        sr.emplace_back(var.second);
    }

    // terminals:
    for (int i = 0; i < word.size(); i++) {
        for (const auto& terminal: terminals)
            if (word[i] == terminal.second[0])
                table[0][i].insert(terminal.first);
    }

    // non-terminals:
    // we consider all the lengths (from 2 to word length, length 1 already precomputed)
    // for each length, consider all the substrings of that length
    // for each substring, consider all possible partition points

    for (int l = 2; l <= word.size(); l++) {
        for (int i = 0; i <= word.size() - l; i++) {
            for (int part = 1; part < l; part++) {
                set<string> product = generateCartesian(table[part - 1][i], table[l - part - 1][i + part]);
                for (const auto& item: product) {
                    auto it = find(sr.begin(), sr.end(), item);
                    if (it != sr.end()) // if we found
                        table[l - 1][i].insert(sl[it - sr.begin()]);

                }
            }
        }
    }

    return table[word.size() - 1][0].count("S") > 0;
}