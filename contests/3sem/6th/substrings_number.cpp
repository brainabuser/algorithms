//
// Created by Vladimir on 13.12.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

size_t get_ans(const string &line);

int main() {
    string line;
    getline(cin, line);
    cout << get_ans(line) << endl;
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

size_t get_ans(const string &line) {
    size_t counter = 0;
    string temp = string("");
    for (const auto &c: line) {
        temp += c;
        auto rev_temp = temp;
        reverse(rev_temp.begin(), rev_temp.end());
        auto pi = get_prefix_func(rev_temp);
        counter += temp.size() - *max_element(pi.begin(), pi.end());
    }
    return counter;
}