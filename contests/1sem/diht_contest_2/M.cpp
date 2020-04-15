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
    Node *tummy = nullptr;//от англ. "брюшко"
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
        dequeue->tummy = new_node;
    } else {
        dequeue->head->prev = new_node;
        if (dequeue->size % 2 != 0) {
            dequeue->tummy = dequeue->tummy->prev;
        }
    }
    dequeue->head = new_node;
    ++(dequeue->size);
}

void pushMid(Dequeue *dequeue, int data) {
    if (dequeue->size <= 1) {
        pushBack(dequeue, data);
        return;
    }
    Node *new_node = new Node;
    new_node->value = data;
    if (dequeue->size % 2 == 0) {
        new_node->next = dequeue->tummy->next;
        new_node->prev = dequeue->tummy;
        dequeue->tummy->next->prev = new_node;
        dequeue->tummy->next = new_node;
    } else {
        new_node->next = dequeue->tummy;
        new_node->prev = dequeue->tummy->prev;
        dequeue->tummy->prev->next = new_node;
        dequeue->tummy->prev = new_node;
    }
    dequeue->tummy = new_node;
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
        dequeue->tummy = nullptr;
        dequeue->tail = nullptr;
    } else {
        if (dequeue->size % 2 != 0) {
            dequeue->tummy = dequeue->tummy->prev;
        }
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