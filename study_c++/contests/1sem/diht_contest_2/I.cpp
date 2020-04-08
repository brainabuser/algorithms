#include <iostream>

#include <cstring>

using namespace std;

#define max_request_size 8

struct Node {
    int value = -1;
    Node *next = nullptr;
    int local_min = -1;
};

struct Stack {
    int size = 0;
    Node *head = nullptr;
    int front = -1;
};

struct Queue {
    Stack *left = new Stack;
    Stack *right = new Stack;
};

void enqueue(Queue *queue, int value);

int dequeue(Queue *queue);

void front(Queue *queue);

int size(Queue *queue);

void clear(Queue *queue);

void min(Queue *queue);

int main() {
    auto *queue = new Queue;
    int request_number;
    cin >> request_number;
    for (int i = 0; i < request_number; ++i) {
        char request[max_request_size];
        cin >> request;
        if (!strcmp(request, "enqueue")) {
            int value;
            cin >> value;
            enqueue(queue, value);
        } else if (!strcmp(request, "dequeue")) {
            int result = dequeue(queue);
            if (result == -1) {
                cout << "error" << endl;
            } else {
                cout << result << endl;
            }
        } else if (!strcmp(request, "front")) {
            front(queue);
        } else if (!strcmp(request, "size")) {
            cout << size(queue) << endl;
        } else if (!strcmp(request, "clear")) {
            clear(queue);
            cout << "ok" << endl;
        } else if (!strcmp(request, "min")) {
            min(queue);
        }
    }
    clear(queue);
    delete queue;
    return 0;
}

void push(Stack *stack, int data) {
    Node *new_node = new Node;
    new_node->value = data;
    new_node->next = stack->head;
    if (stack->size == 0) {
        new_node->local_min = data;
        stack->front = data;
    } else {
        new_node->local_min = (data < stack->head->local_min) ? data : stack->head->local_min;
    }
    stack->head = new_node;
    ++(stack->size);
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

int back(Stack *stack) {
    return (stack->size == 0) ? -1 : stack->head->value;
}

int min(Stack *stack) {
    return (stack->size == 0) ? -1 : stack->head->local_min;
}

int size(Stack *stack) {
    return stack->size;
}

void clear(Stack *stack) {
    while (pop(stack) != -1);
}

void enqueue(Queue *queue, int value) {
    push(queue->left, value);
    cout << "ok" << endl;
}

int dequeue(Queue *queue) {
    if (size(queue) == 0) {
        return -1;
    }
    if (queue->right->size == 0) {
        while (queue->left->size != 0) {
            push(queue->right, pop(queue->left));
        }
    }
    return pop(queue->right);
}

void front(Queue *queue) {
    if (size(queue) == 0) {
        cout << "error" << endl;
        return;
    }
    cout << ((queue->right->size != 0) ? back(queue->right) : queue->left->front) << endl;
}

int size(Queue *queue) {
    return queue->left->size + queue->right->size;
}

void clear(Queue *queue) {
    clear(queue->right);
    clear(queue->left);
}

void min(Queue *queue) {
    if (size(queue) == 0) {
        cout << "error" << endl;
        return;
    }
    if (size(queue->left) != 0 && size(queue->right) != 0) {
        cout << min(min(queue->left), min(queue->right)) << endl;
    } else if (size(queue->left) != 0) {
        cout << min(queue->left) << endl;
    } else {
        cout << min(queue->right) << endl;
    }
}