//
// Created by Vladimir on 02.12.2020.
//

#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
  public:
    FenwickTree(size_t n, size_t m) : n(n), m(m) {
        tree.resize(n, vector<int32_t>(m, 0));
    }
    void update(int x, int y, int32_t delta);
    int32_t sum(int x, int y);
    int32_t query(int x_0, int y_0, int x, int y);
  private:
    size_t n, m;
    int32_t f(int i);
    int32_t g(int i);
    vector<vector<int32_t>> tree;
};

int main() {
    size_t n, m;
    cin >> n >> m;
    FenwickTree f_tree(n, m);
    int req_n;
    cin >> req_n;
    while (req_n--) {
        int req_id;
        int32_t x_0, y_0;
        cin >> req_id >> x_0 >> y_0;
        if (req_id == 1) {
            int32_t delta;
            cin >> delta;
            f_tree.update(x_0 - 1, y_0 - 1, delta);
        } else if (req_id == 2) {
            int32_t x, y;
            cin >> x >> y;
            cout << f_tree.query(x_0 - 1, y_0 - 1, x - 1, y - 1) << '\n';
        }
    }
    return 0;
}

int32_t FenwickTree::f(int i) {
    return i & (i + 1);
}

int32_t FenwickTree::g(int i) {
    return i | (i + 1);
}

void FenwickTree::update(int x, int y, int32_t delta) {
    for (int i = x; i < n; i = g(i)) {
        for (int j = y; j < m; j = g(j)) {
            tree[i][j] += delta;
        }
    }
}

int32_t FenwickTree::sum(int x, int y) {
    int32_t res = 0;
    for (int i = x; i >= 0; i = f(i) - 1) {
        for (int j = y; j >= 0; j = f(j) - 1) {
            res += tree[i][j];
        }
    }
    return res;
}

int32_t FenwickTree::query(int x_0, int y_0, int x, int y) {
    return sum(x, y) - sum(x_0 - 1, y) - sum(x, y_0 - 1) + sum(x_0 - 1, y_0 - 1);
}
