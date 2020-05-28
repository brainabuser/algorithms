//
// Created by Vladimir on 26.05.2020.
//

#include <iostream>
#include <string>
#include <queue>

using namespace std;

template<class T>
class List {
  private:
    struct Node {
        int value = -1;
        Node *next = nullptr;
        Node *prev = nullptr;
    };
    size_t list_size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
  public:
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef size_t size_type;

    void push_back(const T elem) {
        Node *new_node = new Node;
        new_node->value = elem;
        new_node->next = head;
        if (list_size == 0) {
            tail = new_node;
        } else {
            head->prev = new_node;
        }
        head = new_node;
        ++list_size;
    }

    void pop_front() {
        Node *old_tail = tail;
        if (list_size == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail->prev->next = nullptr;
            tail = tail->prev;
        }
        delete old_tail;
        --list_size;
    }

    const T &front() const {
        return tail->value;
    }

    T &front() {
        return tail->value;
    }

    size_t size() const {
        return list_size;
    }
};

int main() {
    string command;
    queue<int, List<int>> infinite_queue;
    while (cin >> command) {
        if (command == "push") {
            int elem;
            cin >> elem;
            infinite_queue.push(elem);
            cout << "ok" << endl;
        } else if (command == "pop") {
            if (infinite_queue.size() == 0) {
                cout << "error" << endl;
            } else {
                cout << infinite_queue.front() << endl;
                infinite_queue.pop();
            }
        } else if (command == "front") {
            if (infinite_queue.size() == 0) {
                cout << "error" << endl;
            } else {
                cout << infinite_queue.front() << endl;
            }
        } else if (command == "size") {
            cout << infinite_queue.size() << endl;
        } else if (command == "clear") {
            while (infinite_queue.size() != 0) {
                infinite_queue.pop();
            }
            cout << "ok" << endl;
        } else if (command == "exit") {
            cout << "bye" << endl;
            break;
        }
    }
    return 0;
};