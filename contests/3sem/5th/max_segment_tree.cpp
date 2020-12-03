//
// Created by Vladimir on 29.11.2020.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<class T>
struct Leaf {
    size_t num = 1;
    T max = numeric_limits<T>::min();
};

template<class E>
struct MAX {
    Leaf<E> operator()(const Leaf<E> &lhs, const Leaf<E> &rhs) {
        if (lhs.max > rhs.max) {
            return lhs;
        } else if (lhs.max < rhs.max) {
            return rhs;
        } else {
            return {lhs.num + rhs.num, lhs.max};
        }
    }
};

template<class T, class Func>
class SegmentTree {
  public:
    explicit SegmentTree(size_t n) {
        auto power = static_cast<size_t>(ceil(log2(n)));
        array_size = pow(2, power);
        tree.resize(2 * array_size - 1);
        buildTree(n);
    }
    void buildTree(size_t n);
    void printTree();
    void query(size_t l, size_t r);
  private:
    vector<Leaf<T>> tree;
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
        cin >> tree[i].max;
    }
    for (int j = array_size - 2; j >= 0; --j) {
        auto left = tree[getLeftChild(j)];
        auto right = tree[getRightChild(j)];
        tree[j] = func(left, right);
    }
}

template<class T, class Func>
void SegmentTree<T, Func>::query(size_t l, size_t r) {
    l += array_size - 1;
    r += array_size - 1;
    Leaf<T> left_res, right_res;
    while (l < r) {
        if (l == getRightChild(getParent(l))) {
            left_res = func(left_res, tree[l]);
        }
        if (r == getLeftChild(getParent(r))) {
            right_res = func(right_res, tree[r]);
        }
        l = getParent(l + 1);
        r = getParent(r - 1);
    }
    if (l == r) {
        left_res = func(left_res, tree[l]);
    }
    auto ans = func(left_res, right_res);
    cout << ans.max << ' ' << ans.num << endl;
}

template<class T, class Func>
void SegmentTree<T, Func>::printTree() {
    for (const auto &t:tree) {
        cout << t.max << '(' << t.num << ')' << ' ';
    }
    cout << endl;
}

int main() {
    size_t n;
    cin >> n;
    SegmentTree<int, MAX<int>> s_tree(n);
    int req_n;
    cin >> req_n;
//    s_tree.printTree();
    while (req_n--) {
        int l, r;
        cin >> l >> r;
        s_tree.query(l - 1, r - 1);
    }
    return 0;
}