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
    void makeTable();
    int query(size_t l, size_t r);
  private:
    vector<vector<int>> s_table;
    vector<size_t> logs;
    vector<size_t> pows;
    int getGCD(int a, int b) const;
};

void SparseTable::makeTable() {
    for (int &i : s_table[0]) {
        cin >> i;
    }
    for (int k = 1; k < s_table.size(); ++k) {
        for (int i = 0; i < s_table[k].size(); ++i) {
            if (i + pows[k - 1] >= s_table[k].size())continue;
            s_table[k][i] =
                    getGCD(s_table[k - 1][i], s_table[k - 1][i + pows[k - 1]]);
        }
    }
}

int SparseTable::query(size_t l, size_t r) {
    if (l > r) {
        swap(l, r);
    }
    auto k = logs[r - l + 1];
    auto ans = getGCD(s_table[k][l], s_table[k][r - pows[k] + 1]);
    return ans;
}

int SparseTable::getGCD(int a, int b) const {
    int numerator = abs(a);
    int denominator = abs(b);
    while (numerator > 0 && denominator > 0) {
        if (numerator > denominator) {
            numerator %= denominator;
        } else {
            denominator %= numerator;
        }
    }
    int gcd = numerator + denominator;
    return gcd;
}

int main() {
    int n;
    cin >> n;
    auto power = static_cast<size_t>(log2(n) + 1);
    SparseTable s_table(power, n);
    s_table.makeTable();
    int req_n;
    cin >> req_n;
    while (req_n--) {
        int l, r;
        cin >> l >> r;
        cout << s_table.query(l - 1, r - 1) << endl;
    }
    return 0;
}