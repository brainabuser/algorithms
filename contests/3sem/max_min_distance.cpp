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
    auto l = 1;
    auto r = *tables.rbegin() - *tables.begin();
    auto mid = r;
    while (r - l > 1) {
        auto cnt = k - 1;
        auto prev = tables.begin();
        for (auto it = next(tables.begin()); it != tables.end(); it = next(it)) {
            if ((*it - *prev) >= mid) {
                --cnt;
                prev = it;
            }
        }
        ans = (cnt <= 0) ? max(mid, ans) : ans;
        l = (cnt <= 0) ? mid : l;
        r = (cnt <= 0) ? r : mid;
        mid = (l + r) / 2;
    }
    cout << ans << endl;
    return 0;
}