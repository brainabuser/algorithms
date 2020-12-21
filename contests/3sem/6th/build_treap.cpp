//
// Created by Vladimir on 16.12.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    Node() : left(nullptr), right(nullptr), parent(nullptr), order(0) {};
    int key{}, priority{}, order{};
    Node *left, *right, *parent;
};

class Treap {
  public:
    explicit Treap(vector<Node *> &sorted_nodes) : root(nullptr) {
        buildTreap(sorted_nodes);
    }
  private:
    Node *root;
    void setLeft(Node *parent, Node *left);
    void setRight(Node *parent, Node *right);
    void buildTreap(vector<Node *> &sorted_nodes);
};

int main() {
    size_t nodes_num;
    cin >> nodes_num;
    vector<Node *> nodes(nodes_num);
    size_t order = 1;
    for (auto &node : nodes) {
        node = new Node;
        cin >> node->key >> node->priority;
        node->order = order++;
    }
    sort(nodes.begin(), nodes.end(), [](const Node *lhs, const Node *rhs) {
        return lhs->key < rhs->key;
    });
    Treap treap(nodes);
    sort(nodes.begin(), nodes.end(), [](const Node *lhs, const Node *rhs) {
        return lhs->order < rhs->order;
    });
    if (!nodes.empty()) {
        cout << "YES" << endl;
    }
    for (const auto &node : nodes) {
        cout << (node->parent == nullptr ? 0 : node->parent->order) << ' ';
        cout << (node->left == nullptr ? 0 : node->left->order) << ' ';
        cout << (node->right == nullptr ? 0 : node->right->order) << '\n';
    }
    return 0;
}

void Treap::buildTreap(vector<Node *> &sorted_nodes) {
    root = nullptr;
    Node *last_added = nullptr;
    for (auto &node : sorted_nodes) {
        while (last_added != nullptr && last_added->priority > node->priority) {
            last_added = last_added->parent;
        }
        if (last_added == nullptr) {
            setLeft(node, root);
            root = node;
        } else {
            setLeft(node, last_added->right);
            setRight(last_added, node);
        }
        last_added = node;
    }
}

void Treap::setLeft(Node *parent, Node *left) {
    if (parent != nullptr) parent->left = left;
    if (left != nullptr) left->parent = parent;
}

void Treap::setRight(Node *parent, Node *right) {
    if (parent != nullptr) parent->right = right;
    if (right != nullptr) right->parent = parent;
}


