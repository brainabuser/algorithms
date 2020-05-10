//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (auto &t : nums) {
        cin >> t;
    }
    sort(nums.begin(), nums.end());
    cin >> n;
    auto lower = lower_bound(nums.begin(), nums.end(), n);
    cout << upper_bound(lower, nums.end(), n) - lower << endl;
    return 0;
}