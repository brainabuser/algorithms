//
// Created by vladimir on 23.09.2020.
//

#include <iostream>
#include <set>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    set<int> tables;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        tables.insert(temp);
    }
    int ans = 1;
    auto left = 1;
    auto right = *tables.rbegin() - *tables.begin();
    auto mid = right;
    while (right - left > 1) {
        auto free_places = k - 1;
        auto prev = tables.begin();
        for (auto it = next(tables.begin()); it != tables.end(); it = next(it)) {
            if ((*it - *prev) >= mid) {
                --free_places;
                prev = it;
            }
        }
        ans = (free_places <= 0) ? max(mid, ans) : ans;
        left = (free_places <= 0) ? mid : left;
        right = (free_places <= 0) ? right : mid;
        mid = (left + right) / 2;
    }
    cout << ans << endl;
    return 0;
}