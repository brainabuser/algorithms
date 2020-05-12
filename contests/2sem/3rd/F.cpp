//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main() {
    set<int> nums;
    int n;
    cin >> n;
    bool prev = false;
    int prevNum;
    for (int i = 0; i < n; ++i) {
        string request;
        int temp;
        cin >> request >> temp;
        if (request == "+") {
            if (prev) {
                nums.insert((temp + prevNum) % 1'000'000'000);
            } else {
                nums.insert(temp);
            }
            prev = false;
        } else if (request == "?") {
            auto low = nums.lower_bound(temp);
            if (low == nums.end()) {
                cout << "-1" << endl;
                prev = false;
            } else {
                prevNum = *low;
                cout << prevNum << endl;
                prev = true;
            }
        }
    }
    return 0;
}