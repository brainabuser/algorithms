//
// Created by Vladimir on 14.12.2020.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string get_encrypted_message(vector<string> messages);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    size_t messages_number;
    cin >> messages_number;
    vector<string> messages(messages_number);
    for (auto &m : messages) {
        cin >> m;
    }
    cout << get_encrypted_message(messages) << endl;
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

string get_encrypted_message(vector<string> messages) {
    string result = messages.front();
    for (auto it = next(messages.begin()); it != messages.end(); it = next(it)) {
        auto s_star = *it + '#';
        s_star += (result.size() > it->size() ? result.substr(result.size() - it->size(), it->size()) : result);
        auto pi = get_prefix_func(s_star);
        it->erase(0, pi.back());
        result += *it;
    }
    return result;
}
