//
// Created by Vladimir on 14.12.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string pi_to_str(const vector<int> &pi) {
    string str(pi.size(), '\0');
    if (!pi.empty()) str[0] = 'a';
    for (size_t i = 1; i < pi.size(); ++i) {
        if (pi[i] > 0) {
            str[i] = str[pi[i] - 1];
            continue;
        }
        unordered_map<char, bool> used = {};
        auto k = pi[i - 1];
        while (k > 0) {
            used[str[k]] = true;
//            cout << str[k];
            k = pi[k - 1];
        }
        for (char symbol = 'b'; symbol <= 'z'; ++symbol) {
            if (!used[symbol]) {
                str[i] = symbol;
//                used[symbol] = true;
                break;
            }
        }
    }
    return str;
}

int main() {
    size_t pi_size;
    cin >> pi_size;
    vector<int> pi(pi_size);
    for (auto &item : pi) {
        cin >> item;
    }
    cout << pi_to_str(pi) << endl;
    return 0;
}