//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

bool cmp(const pair<int, string> &lhs, const pair<int, string> &rhs);

int main() {
    set<pair<int, string>, decltype(cmp) *> revDict(cmp);
    map<string, int> dict;
    string word;
    while (cin >> word) {
        ++dict[word];
    }
    for (const auto &i: dict) {
        revDict.insert(make_pair(i.second, i.first));
    }
    for (const auto &i: revDict) {
        cout << i.second << endl;
    }
    return 0;
}

bool cmp(const pair<int, string> &lhs, const pair<int, string> &rhs) {
    if (lhs.first == rhs.first) {
        return lexicographical_compare(lhs.second.begin(), lhs.second.end(),
                                       rhs.second.begin(), rhs.second.end()
        );
    } else {
        return lhs.first > rhs.first;
    }
}