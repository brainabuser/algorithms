//
// Created by Vladimir on 29.11.2020.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<class E>
struct gcd {
    E operator()(const E &lhs, const E &rhs) {
        E numerator = abs(lhs);
        E denominator = abs(rhs);
        while (numerator > 0 && denominator > 0) {
            if (numerator > denominator) {
                numerator %= denominator;
            } else {
                denominator %= numerator;
            }
        }
        E gcd = numerator + denominator;
        return gcd;
    }
};

template<class T, class Func>
class SegmentTree {
  public:
    explicit SegmentTree(size_t n) {
        auto power = static_cast<size_t>(ceil(log2(n)));
        array_size = pow(2, power);
        tree.resize(2 * array_size - 1, 0);
        buildTree(n);
    }
    void buildTree(size_t n);
    void printTree();
    T query(size_t l, size_t r);
  private:
    vector<T> tree;
    Func func;
    size_t array_size;
    size_t getParent(const size_t &id) {
        return (id - 1) / 2;
    }
    size_t getLeftChild(const size_t &id) {
        return 2 * id + 1;
    }
    size_t getRightChild(const size_t &id) {
        return 2 * id + 2;
    }
};

template<class T, class Func>
void SegmentTree<T, Func>::buildTree(size_t n) {
    for (size_t i = array_size - 1; i < tree.size() && n--; ++i) {
        cin >> tree[i];
    }
    for (int j = array_size - 2; j >= 0; --j) {
        tree[j] = func(tree[getLeftChild(j)],
                       tree[getRightChild(j)]);
    }
}

template<class T, class Func>
T SegmentTree<T, Func>::query(size_t l, size_t r) {
    l += array_size - 1;
    r += array_size - 1;
    auto left_res = 0;
    auto right_res = 0;
    while (l < r) {
        if (l == getRightChild(getParent(l))) {
            left_res = func(left_res, tree[l]);
        }
        l = getParent(l + 1);
        if (r == getLeftChild(getParent(r))) {
            right_res = func(right_res, tree[r]);
        }
        r = getParent(r - 1);
    }
    if (l == r) {
        left_res = func(left_res, tree[l]);
    }
    return func(left_res, right_res);
}

template<class T, class Func>
void SegmentTree<T, Func>::printTree() {
    for (const auto &t:tree) {
        cout << t << ' ';
    }
}

int main() {
    size_t n;
    cin >> n;
    SegmentTree<int, gcd<int>> s_tree(n);
    int req_n;
    cin >> req_n;
    while (req_n--) {
        int l, r;
        cin >> l >> r;
        cout << s_tree.query(l - 1, r - 1) << endl;
    }
    return 0;
}