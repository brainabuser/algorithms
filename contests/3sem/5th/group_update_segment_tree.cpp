//
// Created by Vladimir 01.12.2020.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template<class L>
struct Leaf {
    Leaf() : promise(L{}), value(L{}) {}
    explicit Leaf(L p, L v) : promise(p), value(v) {}
    L promise;
    L value;
    size_t a{}, b{}; //borders
};

template<class E>
struct MIN {
    E operator()(const E &lhs, const E &rhs) {
        return min(lhs, rhs);
    }
};

template<class E>
struct INC {
    E operator()(const E &lhs, const E &rhs) {
        return lhs + rhs;
    }
};

template<class T, class QUERY_OP, class UPDATE_OP>
class SegmentTree {
  public:
    explicit SegmentTree(size_t n) {
        auto power = static_cast<size_t>(ceil(log2(n)));
        array_size = pow(2, power);
        tree.resize(2 * array_size - 1, Leaf<T>());
        buildTree(n);
    }
    void buildTree(size_t n);
    void update(const int &leaf_id, size_t l, size_t r, T delta);
    T query(const int &leaf_id, size_t l, size_t r);
  private:
    vector<Leaf<T>> tree;
    QUERY_OP query_op;
    UPDATE_OP update_op;
    size_t array_size;
    void push(const int &leaf_id);
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

template<class T, class QUERY_OP, class UPDATE_OP>
void SegmentTree<T, QUERY_OP, UPDATE_OP>::buildTree(size_t n) {
    for (size_t i = array_size - 1; i < tree.size(); ++i) {
        if (n > 0) {
            cin >> tree[i].value;
            --n;
        }
        tree[i].a = tree[i].b = i - array_size + 1;
    }
    for (int j = array_size - 2; j >= 0; --j) {
        tree[j].value = query_op(tree[getLeftChild(j)].value, tree[getRightChild(j)].value);
        tree[j].a = tree[getLeftChild(j)].a;
        tree[j].b = tree[getRightChild(j)].b;
    }
}

template<class T, class QUERY_OP, class UPDATE_OP>
void SegmentTree<T, QUERY_OP, UPDATE_OP>::push(const int &leaf_id) {
    auto l = getLeftChild(leaf_id);
    auto r = getRightChild(leaf_id);
    tree[l].promise = update_op(tree[l].promise, tree[leaf_id].promise);
    tree[r].promise = update_op(tree[r].promise, tree[leaf_id].promise);
    tree[leaf_id].value = update_op(tree[leaf_id].value, tree[leaf_id].promise);
    tree[leaf_id].promise = 0;
}

template<class T, class QUERY_OP, class UPDATE_OP>
T SegmentTree<T, QUERY_OP, UPDATE_OP>::query(const int &leaf_id, size_t l, size_t r) {
    auto a = tree[leaf_id].a;
    auto b = tree[leaf_id].b;
    if (b < l || a > r) {
        return 0;
    }
    if (a >= l && b <= r) {
        return update_op(tree[leaf_id].value, tree[leaf_id].promise);
    }
    if (tree[leaf_id].promise != 0)push(leaf_id);
    return update_op(query(getLeftChild(leaf_id), l, r),
                     query(getRightChild(leaf_id), l, r));
}

template<class T, class QUERY_OP, class UPDATE_OP>
void SegmentTree<T, QUERY_OP, UPDATE_OP>::update(const int &leaf_id, size_t l, size_t r, T delta) {
    auto a = tree[leaf_id].a;
    auto b = tree[leaf_id].b;
    if (b < l || a > r) {
        return;
    }
    if (a >= l && b <= r) {
        tree[leaf_id].promise = update_op(tree[leaf_id].promise, delta);
        return;
    }
    if (tree[leaf_id].promise != 0) push(leaf_id);
    update(getLeftChild(leaf_id), l, r, delta);
    update(getRightChild(leaf_id), l, r, delta);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    size_t n;
    cin >> n;
    SegmentTree<size_t, MIN<size_t>, INC<size_t>> s_tree(n);
    int req_n;
    cin >> req_n;
    while (req_n--) {
        char req;
        cin >> req;
        if (req == 'g') {
            size_t id;
            cin >> id;
            cout << s_tree.query(size_t(0), id - 1, id - 1) << '\n';
        } else if (req == 'a') {
            size_t l, r, delta;
            cin >> l >> r >> delta;
            s_tree.update(size_t(0), l - 1, r - 1, delta);
        }
    }
    return 0;
}