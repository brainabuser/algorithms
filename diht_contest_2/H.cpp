#include <iostream>

#include <cstring>

using namespace std;

#define max_request_size 6

struct Node {
    int value = -1;
    Node *next = nullptr;
    int local_min = -1;
};

struct Stack {
    int size = 0;
    Node *head = nullptr;
};

void push(Stack *stack, int data);

int pop(Stack *stack);

void back(Stack *stack);

void min(Stack *stack);

void size(Stack *stack);

void clear(Stack *stack);

void printList(const Stack *stack);

int main() {
    auto *stack = new Stack;
    int request_number;
    cin >> request_number;
    for (int i = 0; i < request_number; ++i) {
        char request[max_request_size];
        cin >> request;
        if (!strcmp(request, "push")) {
            int value;
            cin >> value;
            push(stack, value);
        } else if (!strcmp(request, "pop")) {
            int result = pop(stack);
            if (result == -1) {
                cout << "error" << endl;
            } else {
                cout << result << endl;
            }
        } else if (!strcmp(request, "back")) {
            back(stack);
        } else if (!strcmp(request, "min")) {
            min(stack);
        } else if (!strcmp(request, "size")) {
            size(stack);
        } else if (!strcmp(request, "clear")) {
            clear(stack);
        }
    }
    delete stack;
    return 0;
}

void push(Stack *stack, int data) {
    Node *new_node = new Node;
    new_node->value = data;
    new_node->next = stack->head;
    if (stack->size == 0) {
        new_node->local_min = data;
    } else {
        new_node->local_min = (data < stack->head->local_min) ? data : stack->head->local_min;
    }
    stack->head = new_node;
    ++(stack->size);
    cout << "ok" << endl;
}

int pop(Stack *stack) {
    if (stack->size == 0) {
        return -1;
    }
    Node *fiction_node = stack->head;
    int return_value = fiction_node->value;
    stack->head = stack->head->next;
    delete fiction_node;
    --(stack->size);
    return return_value;
}

void back(Stack *stack) {
    if (stack->size == 0) {
        cout << "error" << endl;
        return;
    }
    cout << stack->head->value << endl;
}

void min(Stack *stack) {
    if (stack->size == 0) {
        cout << "error" << endl;
        return;
    }
    cout << stack->head->local_min << endl;
}

void size(Stack *stack) {
    cout << stack->size << endl;
}

void clear(Stack *stack) {
    while (pop(stack) != -1);
    cout << "ok" << endl;
}

void printList(const Stack *stack) {
    Node *curr = stack->head;
    bool isFirst = true;
    cout << '[';
    while (curr) {
        if (isFirst) {
            cout << curr->value;
            isFirst = false;
        } else {
            cout << ", " << curr->value;
        }
        curr = curr->next;
    }
    cout << "]\n";
}