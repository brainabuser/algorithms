//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<string, string> words;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string w1, w2;
        cin >> w1 >> w2;
        words[w1] = w2;
        words[w2] = w1;
    }
    cin >> n;
    for (int j = 0; j < n; ++j) {
        string w;
        cin >> w;
        cout << words[w] << "\n";
    }
    return 0;
}