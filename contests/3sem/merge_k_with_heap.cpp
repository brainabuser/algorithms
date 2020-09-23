//
// Created by vladimir on 21.09.2020.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    int value;
    int array_index;
};

bool operator>(const Node &lhs, const Node &rhs) {
    return lhs.value > rhs.value;
}

void readArray(vector<int> &array);

void printArray(const vector<int> &array);

int main() {
    priority_queue<Node, vector<Node>, greater<>> mins;
    int k;
    cin >> k;
    vector<vector<int>> arrays(k);
    for (int i = 0; i < k; ++i) {
        int n;
        cin >> n;
        vector<int> temp(n);
        readArray(temp);
        mins.push({temp.back(), i});
        temp.pop_back();
        arrays[i] = (temp);
    }
    vector<int> result;
    while (!mins.empty()) {
        result.push_back(mins.top().value);
        auto id = mins.top().array_index;
        mins.pop();
        if (!arrays[id].empty()) {
            mins.push({arrays[id].back(), id});
            arrays[id].pop_back();
        }
    }
    printArray(result);
    return 0;
}

void readArray(vector<int> &array) {
    for (auto it = array.rbegin(); it < array.rend(); it = next(it)) {
        cin >> *it;
    }
}

void printArray(const vector<int> &array) {
    for (const auto &item : array) {
        cout << item << ' ';
    }
    cout << '\n';
}
