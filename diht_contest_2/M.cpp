#include <iostream>

using namespace std;

struct Node {
    int value = -1;
    Node *next = nullptr;
};

struct Stack {
    int size = 0;
    Node *head = nullptr;
};

struct GoblinQueue {
    Stack *left = new Stack;
    Stack *right = new Stack;
};

void enqueue(GoblinQueue *queue, int value);

void midEnqueue(GoblinQueue *queue, int value);

int dequeue(GoblinQueue *queue);

int size(GoblinQueue *queue);

void clear(GoblinQueue *queue);

void printList(const Stack *stack);

int main() {
    auto *queue = new GoblinQueue;
    int request_number;
    cin >> request_number;
    for (int i = 0; i < request_number; ++i) {
        char request;
        cin >> request;
        if (request != '-') {
            int number;
            cin >> number;
            if (request == '+') {
                enqueue(queue, number);
            } else {
                midEnqueue(queue, number);
            }
        } else {
            cout << dequeue(queue) << endl;
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

int size(Stack *stack) {
    return stack->size;
}

void clear(Stack *stack) {
    while (pop(stack) != -1);
}

void enqueue(GoblinQueue *queue, int value) {
    push(queue->left, value);
}

void midEnqueue(GoblinQueue *queue, int value) {
    int needed_position = size(queue) / 2;
    if (queue->left->size >= queue->right->size) {
        Node *left_curr = queue->left->head;
        int cnt = 0;
        while (left_curr->next != nullptr) {
            ++cnt;
            if (cnt == needed_position) {
                Node *new_node = new Node;
                new_node->value = value;
                new_node->next = left_curr->next;
                left_curr->next = new_node;
                break;
            }
            left_curr = left_curr->next;
        }
        ++(queue->left->size);
    } else {
        Node *right_curr = queue->right->head;
        int cnt = 0;
        while (right_curr != nullptr) {
            ++cnt;
            if (cnt == needed_position) {
                Node *new_node = new Node;
                new_node->value = value;
                new_node->next = right_curr->next;
                right_curr->next = new_node;
                break;
            }
            right_curr = right_curr->next;
        }
        ++(queue->right->size);
    }

}

int dequeue(GoblinQueue *queue) {
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

int size(GoblinQueue *queue) {
    return queue->left->size + queue->right->size;
}

void clear(GoblinQueue *queue) {
    clear(queue->right);
    clear(queue->left);
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