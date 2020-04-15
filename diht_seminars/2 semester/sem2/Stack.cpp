//
// Created by Vladimir on 18.02.2020.
//

#include <iostream>

using namespace std;

typedef int N_TYPE;

class Stack {
  private:
    struct Node {
        N_TYPE value;
        Node *next;
    };

    Node *top;
    int size;

    void assign(const Stack &that);

  public:
    N_TYPE pop();

    void push(const N_TYPE &value);

    int getSize() const;

    void print() const;

    Stack();

    Stack(const Stack &that);

    ~Stack();

    Stack &operator=(const Stack &that);
};

int main() {
    Stack first;
    cout << "First: " << first.getSize() << endl;
    first.print();

    first.push(2);
    first.push(3);

    cout << "First: " << first.getSize() << endl;
    first.print();

    first.pop();
    cout << "First: " << first.getSize() << endl;
    first.print();

    Stack second = first;
    cout << "Second: " << second.getSize() << endl;
    second.print();

    second.push(35);
    cout << "Second: " << second.getSize() << endl;
    second.print();

    cout << "First: " << first.getSize() << endl;
    first.print();

    Stack third;
    third = second;
    cout << "Second: " << second.getSize() << endl;
    second.print();

    cout << "Third: " << third.getSize() << endl;
    third.print();

    third.push(36);
    cout << "Third: " << third.getSize() << endl;
    third.print();
    return 0;
}


void Stack::push(const N_TYPE &value) {
    Node *newNode = new Node{value, top};
    top = newNode;
    ++size;
}

N_TYPE Stack::pop() {
    Node *prevTop = top;
    top = top->next;
    N_TYPE value = prevTop->value;
    delete prevTop;
    --size;
    return value;
}

int Stack::getSize() const {
    return size;
}

void Stack::print() const {
    Node *curr = top;
    while (curr != nullptr) {
        cout << curr->value << ' ';
        curr = curr->next;
    }
    cout << endl;
}

Stack::Stack() : size(0), top(nullptr) {}

Stack::~Stack() {
    while (size > 0) {
        pop();
    }
}

void Stack::assign(const Stack &that) {
    if (that.top == nullptr) {
        this->top = nullptr;
        this->size = 0;
        return;
    }
    size = that.size;
    this->top = new Node(*that.top);
    Node *thatTemp = that.top->next;
    Node *thisTemp = this->top;
    while (thatTemp != nullptr) {
        thisTemp->next = new Node(*thatTemp);
        thatTemp = thatTemp->next;
        thisTemp = thisTemp->next;
    }
}

Stack::Stack(const Stack &that) {
    assign(that);
}

Stack &Stack::operator=(const Stack &that) {
    if (this == &that) {//Важная проверка случая x = x
        return *this;
    }
    this->~Stack();
    assign(that);
    return *this;
}
