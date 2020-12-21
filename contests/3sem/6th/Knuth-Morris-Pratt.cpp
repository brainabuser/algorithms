//
// Created by Vladimir on 12.12.2020.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<size_t> get_sub_indices(const string &line, const string &pattern);

int main() {
    string line, pattern;
    getline(cin, line);
    getline(cin, pattern);
    vector<size_t> indices = get_sub_indices(line, pattern);
    for (const auto &item : indices) {
        cout << item << '\n';
    }
    cout << endl;
    return 0;
}

vector<int> get_prefix_func(const string &line) {
    vector<int> pi(line.size(), 0);
    for (size_t i = 1; i < pi.size(); ++i) {
        auto k = pi[i - 1];
        while (k > 0 && line[i] != line[k]) {
            k = pi[k - 1];
        }
        if (line[i] == line[k]) {
            pi[i] = k + 1;
        }
    }
    return pi;
}

vector<size_t> get_sub_indices(const string &line, const string &pattern) {
    vector<size_t> indices;
    string s_star = pattern + '#' + line;
    vector<int> pi = get_prefix_func(s_star);
    auto shift = 2 * pattern.size();
    for (size_t i = 0; i < s_star.size(); ++i) {
        if (pi[i] == pattern.size()) {
            indices.push_back(i - shift);
        }
    }
    return indices;
}