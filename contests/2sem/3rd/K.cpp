//
// Created by Vladimir on 13.05.2020.
//

#include <iostream>
#include <queue>

using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<>> nums;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int tmp;
        cin >> tmp;
        nums.push(tmp);
    }
    long double result = 0.0;
    while (nums.size() >= 2) {
        int lhs = nums.top();
        nums.pop();
        int rhs = nums.top();
        nums.pop();
        nums.push(lhs + rhs);
        result += (lhs + rhs) * 0.05;
    }
    cout << result << endl;
    return 0;
}