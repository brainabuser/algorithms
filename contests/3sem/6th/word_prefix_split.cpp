//
// Created by Vladimir on 16.12.2020.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> get_partition(const string &first_word, const string &second_word);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string first_word, second_word;
    cin >> first_word >> second_word;
    auto res = get_partition(first_word, second_word);
    if (!res.empty()) {
        cout << "No" << '\n';
        for (auto it = res.rbegin(); it != res.rend(); it = next(it)) {
            cout << *it << ' ';
        }
    } else {
        cout << "Yes";
    }
    cout << endl;
    return 0;
}

vector<int> get_z_func(const string &line) {
    vector<int> z(line.size(), 0);
    int left, right;
    left = right = 0;
    for (size_t i = 1; i < line.size(); ++i) {
        if (right > i) {
            z[i] = min(z[i - left], right - static_cast<int>(i));
        }
        while (z[i] + i < z.size() && line[z[i]] == line[z[i] + i]) {
            ++z[i];
        }
        if (z[i]  + i> right) {
            right = z[i] + i;
            left = i;
        }
    }
    if (!line.empty())z[0] = line.size();
    return z;
}

vector<string> get_partition(const string &first_word, const string &second_word) {
    auto s_star = first_word + '#' + second_word;
    auto z = get_z_func(s_star);
    size_t counter = 0;
    vector<string> partition;
    for (size_t i = z.size() - 1; i >= first_word.size() + 1; --i) {
        ++counter;
        if (z[i] >= counter) {
            partition.push_back(s_star.substr(i, counter));
            counter = 0;
        }
    }
    if (counter > 0) {
        partition.clear();
    }
    return partition;
}