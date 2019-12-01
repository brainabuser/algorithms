#include<iostream>
#include<cstring>

using namespace std;

struct Node {
    int value;
    Node *prev;
    Node *next;
};
struct Dequeue {
    Node *top;
    Node *end;
    int size;
};

void push_front(Dequeue *dequeue, int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->prev = dequeue->top;
    newNode->next = NULL;
    dequeue->top->next = newNode;
    dequeue->top = newNode;
    ++dequeue->size;
}

void push_back(Dequeue *dequeue, int value) {
    Node *newNode = new Node;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = dequeue->end;
    dequeue->end->prev = newNode;
    dequeue->end = newNode;
    ++(dequeue->size);
}

void front(Dequeue *dequeue) {
    cout << dequeue->top->value << endl;
}

void back(Dequeue *dequeue) {
    cout << dequeue->end->value;
}

void pop_front(Dequeue *dequeue) {
    Node *oldNode = dequeue->top;
    dequeue->top = dequeue->top->prev;
    dequeue->top->next = NULL;
    delete oldNode;
    --dequeue->size;
}

void pop_back(Dequeue *dequeue) {
    Node *oldNode = dequeue->end;
    dequeue->end = dequeue->end->next;
    dequeue->end->prev = NULL;
    delete oldNode;
    --dequeue->size;
}

void clear(Dequeue *dequeue) {
    while (dequeue->top != NULL) {
        pop_front(dequeue);
    }
}

int main() {
    Dequeue *dequeue = new Dequeue{NULL, NULL, 0};
    int numberOfCommands;
    cin >> numberOfCommands;
    char *command = new char[50];

    for (int i = 0; i < numberOfCommands; ++i) {
        cin >> command;
        if (strcmp(command, "push_front") == 0) {
            int value;
            cin >> value;
            push_front(dequeue, value);
            cout << "ok" << endl;
        }
        if (strcmp(command, "push_back") == 0) {
            int value;
            cin >> value;
            push_back(dequeue, value);
            cout << "ok" << endl;
        }
        if (strcmp(command, "pop_front") == 0) {
            if (dequeue->size > 0) {
                front(dequeue);
                pop_front(dequeue);
            } else {
                cout << "error" << endl;
            }
        }
        if (strcmp(command, "pop_back") == 0) {
            if (dequeue->size > 0) {
                back(dequeue);
                pop_back(dequeue);
            } else {
                cout << "error" << endl;
            }
        }
        if (strcmp(command, "front") == 0) {
            if (dequeue->size > 0) {
                front(dequeue);
            } else {
                cout << "error" << endl;
            }
        }
        if (strcmp(command, "back") == 0) {
            if (dequeue->size > 0) {
                back(dequeue);
            } else {
                cout << "error" << endl;
            }
        }
        if (strcmp(command, "size") == 0) {
            cout << dequeue->size << endl;
        }
        if (strcmp(command, "clear") == 0) {
            clear(dequeue);
            cout << "ok" << endl;
        }

    }

    delete[] command;
    delete dequeue;
    return 0;
}