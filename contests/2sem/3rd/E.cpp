//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
    unordered_set<string> stringSet;
    string request;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> request) {
        if (request == "#") {
            break;
        }
        string line;
        cin >> line;
        if (request == "+") {
            stringSet.insert(line);
        } else if (request == "-") {
            stringSet.erase(line);
        } else if (request == "?") {
            cout << ((stringSet.find(line) != stringSet.end()) ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}