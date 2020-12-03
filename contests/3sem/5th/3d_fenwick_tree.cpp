//
// Created by Vladimir on 02.12.2020.
//

#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
  public:
    explicit FenwickTree(size_t n) : n(n) {
        tree.resize(n, vector<vector<int32_t>>(n, vector<int32_t>(n, 0)));
    }
    void update(int x, int y, int z, int32_t delta);
    int32_t sum(int x, int y, int z);
    int32_t query(int x_0, int y_0, int z_0, int x, int y, int z);
  private:
    size_t n;
    int32_t f(int i);
    int32_t g(int i);
    vector<vector<vector<int32_t>>> tree;
};

int main() {
    size_t n;
    cin >> n;
    FenwickTree f_tree(n);
    while (true) {
        int req_id;
        cin >> req_id;
        int32_t x_0, y_0, z_0;
        if (req_id == 1) {
            int32_t delta;
            cin >> x_0 >> y_0 >> z_0 >> delta;
            f_tree.update(x_0, y_0, z_0, delta);
        } else if (req_id == 2) {
            int32_t x, y, z;
            cin >> x_0 >> y_0 >> z_0;
            cin >> x >> y >> z;
            cout << f_tree.query(x_0, y_0, z_0, x, y, z) << '\n';
        } else if (req_id == 3) {
            break;
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

void FenwickTree::update(int x, int y, int z, int32_t delta) {
    for (int i = x; i < n; i = g(i)) {
        for (int j = y; j < n; j = g(j)) {
            for (int k = z; k < n; k = g(k)) {
                tree[i][j][k] += delta;
            }
        }
    }
}

int32_t FenwickTree::sum(int x, int y, int z) {
    int32_t res = 0;
    for (int i = x; i >= 0; i = f(i) - 1) {
        for (int j = y; j >= 0; j = f(j) - 1) {
            for (int k = z; k >= 0; k = f(k) - 1) {
                res += tree[i][j][k];
            }
        }
    }
    return res;
}

int32_t FenwickTree::query(int x_0, int y_0, int z_0, int x, int y, int z) {
    return sum(x, y, z) - sum(x_0 - 1, y, z) - sum(x, y_0 - 1, z) - sum(x, y, z_0 - 1)
           + sum(x, y_0 - 1, z_0 - 1) + sum(x_0 - 1, y_0 - 1, z) + sum(x_0 - 1, y, z_0 - 1)
           - sum(x_0 - 1, y_0 - 1, z_0 - 1);
}
