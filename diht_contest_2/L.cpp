#include <iostream>

#include <cstring>

using namespace std;

struct Node {
    char symbol;
    Node *next = nullptr;
};

struct Stack {
    int size = 0;
    Node *head = nullptr;
};

void push(Stack *stack, char data);

char pop(Stack *stack);

bool isOpenBracket(char symbol) {
    return (symbol == '(' || symbol == '{' || symbol == '[');
}

bool isCloseBracket(char symbol) {
    return (symbol == ')' || symbol == '}' || symbol == ']');
}

char getPair(char bracket) {
    if (bracket == '(') {
        return ')';
    } else if (bracket == '{') {
        return '}';
    } else {
        return ']';
    }
}

int main() {
    auto *stack = new Stack;
    char answer[4] = "yes";
    char line[100000];
    cin.getline(line, 100000);
    int i = 0;
    if (strlen(line) % 2 != 0) {
        strcpy(answer, "no");
    } else {
        while (line[i] != '\0') {
            if (isOpenBracket(line[i])) {
                push(stack, line[i]);
            } else if (isCloseBracket(line[i])) {
                if (getPair(pop(stack)) != line[i]) {
                    strcpy(answer, "no");
                    break;
                }
            } else {
                if (line[i] != ' ') {
                    strcpy(answer, "no");
                }
                break;
            }
            ++i;
        }
    }
    cout << answer << endl;
    delete stack;
    return 0;
}

void push(Stack *stack, char data) {
    Node *new_node = new Node;
    new_node->symbol = data;
    new_node->next = stack->head;
    stack->head = new_node;
    ++(stack->size);
}

char pop(Stack *stack) {
    if (stack->size == 0) {
        return 'F';
    }
    Node *fiction_node = stack->head;
    char return_value = fiction_node->symbol;
    stack->head = stack->head->next;
    delete fiction_node;
    --(stack->size);
    return return_value;
}