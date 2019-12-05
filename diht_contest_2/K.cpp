#include <iostream>

#include <cstring>

#include <cstdlib>

using namespace std;

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

int computeExpression(int x, int y, char exp) {
    if (exp == '+') {
        return x + y;
    } else if (exp == '-') {
        return x - y;
    } else {
        return x * y;
    }
}

int main() {
    auto *stack = new Stack;
    char line[100000];
    cin.getline(line, 100000);
    int i = 0;
    while (line[i] != '\0') {
        if (isdigit(line[i])) {
            char c_number[100000]{0};
            int j = 0;
            while (isdigit(line[i])) {
                c_number[j++] = line[i++];
            }
            int number = strtol(c_number, nullptr, 10);
            push(stack, number);
        }
        if (line[i] == '+' || line[i] == '-' || line[i] == '*') {
            int y = pop(stack);
            int x = pop(stack);
            int result = computeExpression(x, y, line[i]);
            push(stack, result);
            ++i;
        } else {
            ++i;
        }
    }
    cout << pop(stack) << endl;
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