//
// Created by Vladimir on 12.12.2020.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> get_prefix_func(const string &line);

int main() {
    string line;
    getline(cin, line);
    vector<int> prefix_func = get_prefix_func(line);
    for (const auto &item : prefix_func) {
        cout << item << ' ';
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