#include <iostream>

using namespace std;

struct Node {
    int value = -1;
    Node *next = nullptr;
    Node *prev = nullptr;
};

struct Dequeue {
    int size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
};

void pushBack(Dequeue *dequeue, int data);

void pushMid(Dequeue *dequeue, int data);

int popFront(Dequeue *dequeue);

void clear(Dequeue *dequeue);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto *goblin = new Dequeue;
    int request_number;
    cin >> request_number;
    for (int i = 0; i < request_number; ++i) {
        char request;
        cin >> request;
        if (request != '-') {
            int number;
            cin >> number;
            if (request == '+') {
                pushBack(goblin, number);
            } else {
                pushMid(goblin, number);
            }
        } else {
            cout << popFront(goblin) << endl;
        }
    }
    clear(goblin);
    delete goblin;
    return 0;
}

void pushBack(Dequeue *dequeue, int data) {
    Node *new_node = new Node;
    new_node->value = data;
    new_node->next = dequeue->head;
    if (dequeue->size == 0) {
        dequeue->tail = new_node;
    } else {
        dequeue->head->prev = new_node;
    }
    dequeue->head = new_node;
    ++(dequeue->size);
}

void pushMid(Dequeue *dequeue, int data) {
    if (dequeue->size <= 1) {
        pushBack(dequeue, data);
        return;
    }
    int needed_pos = dequeue->size / 2;
    int curr = 1;
    Node *curr_node = dequeue->head;
    while (curr != needed_pos) {
        ++curr;
        curr_node = curr_node->next;
    }
    Node *new_node = new Node;
    new_node->value = data;
    new_node->next = curr_node->next;
    new_node->prev = curr_node;
    curr_node->next->prev = new_node;
    curr_node->next = new_node;
    ++(dequeue->size);
}

int popFront(Dequeue *dequeue) {
    if (dequeue->size == 0) {
        return -1;
    }
    Node *old_tail = dequeue->tail;
    int return_value = old_tail->value;
    if (dequeue->size == 1) {
        dequeue->head = nullptr;
        dequeue->tail = nullptr;
    } else {
        dequeue->tail->prev->next = nullptr;
        dequeue->tail = dequeue->tail->prev;
    }
    delete old_tail;
    --(dequeue->size);
    return return_value;
}

void clear(Dequeue *dequeue) {
    while (popFront(dequeue) != -1);
}