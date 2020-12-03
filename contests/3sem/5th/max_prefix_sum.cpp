//
// Created by Vladimir on 26.11.2020.
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
    long long ans = partial_sum[0];
    long long min_sum = 0;
    int l = 0, r = 0, min_pos = -1;
    for (int i = 0; i < n; ++i) {
        if (partial_sum[i] - min_sum > ans) {
            r = i;
            l = min_pos + 1;
            ans = partial_sum[i] - min_sum;
        }
        if (partial_sum[i] < min_sum) {
            min_pos = i;
            min_sum = partial_sum[i];
        }
    }
    cout << l + 1 << ' ';
    cout << r + 1 << ' ';
    cout << ans << endl;
    return 0;
}