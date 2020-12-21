//
// Created by Vladimir on 15.12.2020.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> get_z_func(const string &line);

int main() {
    string line;
    getline(cin, line);
    vector<int> z_func = get_z_func(line);
    for (const auto &item : z_func) {
        cout << item << ' ';
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