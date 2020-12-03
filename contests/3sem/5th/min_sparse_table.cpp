//
// Created by Vladimir on 27.11.2020.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SparseTable {
  public:
    SparseTable(int n, int m) : s_table(n, vector<int>(m, numeric_limits<int>::infinity())),
                                logs(m + 1), pows(m + 1) {
        for (int i = 0; i <= m; ++i) {
            logs[i] = static_cast<size_t>(log2(i));
            pows[i] = static_cast<size_t>(pow(2, i));
        }
    }
    void makeTable(int height);
    int query(size_t l, size_t r);
  private:
    vector<vector<int>> s_table;
    vector<size_t> logs;
    vector<size_t> pows;
};

void SparseTable::makeTable(int height) {
    s_table[0][0] = height;
    for (int i = 1; i < s_table[0].size(); ++i) {
        s_table[0][i] = (23 * s_table[0][i - 1] + 21563) % 16714589;
    }
    for (int k = 1; k < s_table.size(); ++k) {
        for (int i = 0; i < s_table[k].size(); ++i) {
            if (i + pows[k - 1] >= s_table[k].size())continue;
            s_table[k][i] =
                    min(s_table[k - 1][i], s_table[k - 1][i + pows[k - 1]]);
        }
    }
}

int SparseTable::query(size_t l, size_t r) {
    if (l > r) {
        swap(l, r);
    }
    auto k = logs[r - l + 1];
    auto ans = min(s_table[k][l], s_table[k][r - pows[k] + 1]);
    return ans;
}

int main() {
    int n, req_n, height;
    cin >> n >> req_n >> height;
    auto power = static_cast<size_t>(log2(n) + 1);
    SparseTable s_table(power, n);
    s_table.makeTable(height);
    size_t l, r;
    cin >> l >> r;
    long long ans = s_table.query(l - 1, r - 1);
    for (size_t i = 1; i < req_n; ++i) {
        l = (17 * l + 751 + ans + 2 * i) % n + 1;
        r = (13 * r + 593 + ans + 5 * i) % n + 1;
        ans = s_table.query(l - 1, r - 1);
    }
    cout << l << ' ' << r << ' ' << ans << endl;
    return 0;
}