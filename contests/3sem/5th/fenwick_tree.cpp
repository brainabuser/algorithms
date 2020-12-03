//
// Created by Vladimir on 02.12.2020.
//

#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
  public:
    FenwickTree(const vector<int64_t> &input) {
        tree.resize(input.size(), 0);
        buildTree(input);
    }
    void update(int id, int64_t delta);
    void change(int id, int64_t value);
    int64_t sum(int r);
    int64_t query(int l, int r);
    void print();
  private:
    int64_t f(int i);
    int64_t g(int i);
    void buildTree(const vector<int64_t> &input);
    vector<int64_t> tree;
};

int main() {
    int n;
    cin >> n;
    vector<int64_t> input(n);
    for (auto &i: input) {
        cin >> i;
    }
    FenwickTree f_tree(input);
//    f_tree.print();
    int req_n;
    cin >> req_n;
    while (req_n--) {
        char req;
        cin >> req;
        if (req == 'u') {
            int id;
            int64_t value;
            cin >> id >> value;
            f_tree.change(id - 1, value);
        } else if (req == 's') {
            int l, r;
            cin >> l >> r;
            cout << f_tree.query(l - 1, r - 1) << ' ';
        }
    }
    return 0;
}

int64_t FenwickTree::f(int i) {
    return i & (i + 1);
}

int64_t FenwickTree::g(int i) {
    return i | (i + 1);
}

void FenwickTree::update(int id, int64_t delta) {
    for (; id < tree.size(); id = g(id)) {
        tree[id] += delta;
    }
}

void FenwickTree::buildTree(const vector<int64_t> &input) {
    for (size_t i = 0; i < tree.size(); ++i) {
        update(i, input[i]);
    }
}

void FenwickTree::print() {
    for (const auto &t : tree) {
        cout << t << ' ';
    }
    cout << endl;
}

int64_t FenwickTree::sum(int r) {
    int64_t res = 0;
    for (; r >= 0; r = f(r) - 1) {
        res += tree[r];
    }
    return res;
}

int64_t FenwickTree::query(int l, int r) {
    return sum(r) - sum(l - 1);
}

void FenwickTree::change(int id, int64_t value) {
    update(id, value - query(id, id));
}
