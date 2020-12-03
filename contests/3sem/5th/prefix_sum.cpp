//
// Created by Vladimir on 25.11.2020.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> partial_sum(n);
    for (int i = 0; i < n; ++i) {
        cin >> partial_sum[i];
        partial_sum[i] += (i == 0) ? 0 : partial_sum[i - 1];
    }
    int req_n;
    cin >> req_n;
    while (req_n--) {
        int l, r;
        cin >> l >> r;
        --l;
        --r;
        if (r < l)continue;
        auto ans = partial_sum[r];
        ans -= (l == 0) ? 0 : partial_sum[l - 1];
        cout << ans << ' ';
    }
    return 0;
}