//
// Created by Vladimir on 15.12.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string z_to_str(const vector<int> &z);

int main() {
    size_t z_size;
    cin >> z_size;
    vector<int> z(z_size);
    for (auto &item : z) {
        cin >> item;
    }
    cout << z_to_str(z) << endl;
    return 0;
}

vector<int> z_to_pi(const vector<int> &z) {
    vector<int> pi(z.size(), 0);
    for (size_t i = 1; i < z.size(); ++i) {
        for (int delta = z[i] - 1; delta >= 0; --delta) {
            if (pi[i + delta] > 0) {
                break;
            }
            pi[i + delta] = delta + 1;
        }
    }
    return pi;
}

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
            k = pi[k - 1];
        }
        for (char symbol = 'b'; symbol <= 'z'; ++symbol) {
            if (!used[symbol]) {
                str[i] = symbol;
                break;
            }
        }
    }
    return str;
}

string z_to_str(const vector<int> &z) {
    return pi_to_str(z_to_pi(z));
}