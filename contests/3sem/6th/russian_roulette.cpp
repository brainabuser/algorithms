//
// Created by Vladimir on 12.12.2020.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string get_ans(const string &drum1, const string &drum2, const size_t &drum_size);

int main() {
    size_t drum_size;
    cin >> drum_size;
    string drum1, drum2;
    cin >> drum1 >> drum2;
    cout << get_ans(drum1, drum2, drum_size) << '\n';
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

string get_ans(const string &drum1, const string &drum2, const size_t &drum_size) {
    auto zero_line = drum1 + '0' + drum1;
    auto one_line = drum1 + '1' + drum1;
    auto zero_indices = get_sub_indices(zero_line, drum2);
    auto one_indices = get_sub_indices(one_line, drum2);
    if (!zero_indices.empty() && !one_indices.empty()) {
        return "Random";
    }
    for (const auto &id : zero_indices) {
        size_t temp_id;
        if (id == 0) {
            temp_id = drum_size - 1;
        } else if (id == zero_indices.size() - 1) {
            temp_id = id - drum_size + 1;
        } else {
            temp_id = id - 1;
        }
        return (zero_line[temp_id] == '0') ? "No" : "Yes";
    }
    for (const auto &id : one_indices) {
        size_t temp_id;
        if (id == 0) {
            temp_id = drum_size - 1;
        } else if (id == one_indices.size() - 1) {
            temp_id = id - drum_size + 1;
        } else {
            temp_id = id - 1;
        }
        return (one_line[temp_id] == '0') ? "No" : "Yes";
    }
    return "LOL";
}