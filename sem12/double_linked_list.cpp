#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *next;
    Node *prev;
};

Node *first(int data);

void add(Node **head, int data);

Node *find(Node *const head, int data);

Node *insert(Node *const head, int key, int data);

bool remove(Node **head, int key);

void printList(Node *const head);

int main() {
    Node *head = first(-1);
    Node *tail = head;
    for (int i = 2; i < 6; ++i) {
        add(&tail, i);
    }
    printList(head);
    insert(head, 5, 10);
    printList(head);
    for (int i = -1; i < 11; ++i) {
        if (remove(&head, i)) {
            printList(head);
        }
    }
    return 0;
}

Node *first(int data) {
    Node *head = new Node;
    head->data = data;
    head->next = nullptr;
    head->prev = nullptr;
    return head;
}

void add(Node **tail, int data) {
    Node *new_node = new Node;
    new_node->data = data;
    new_node->next = nullptr;
    new_node->prev = *tail;
    (*tail)->next = new_node;
    *tail = new_node;
}

Node *find(Node *const head, int data) {
    Node *curr = head;
    while (curr) {
        if (curr->data == data) {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

Node *insert(Node *const head, Node *const tail, int key, int data) {
    if (Node *pKey = find(head, key)) {
        Node *new_node = new Node;
        new_node->data = data;
        new_node->next = pKey->next;
        pKey->next = new_node;
        return new_node;
    }
    return nullptr;
}

bool remove(Node **head, int key) {
    if (Node *pKey = find(*head, key)) {
        if (pKey == *head) {
            *head = (*head)->next;
        } else {
            Node *curr = *head;
            while (curr->next != pKey) {
                curr = curr->next;
            }
            curr->next = pKey->next;
        }
        delete pKey;
        return true;
    }
    return false;
}

void printList(Node *const head) {
    Node *curr = head;
    bool isFirst = true;
    cout << '[';
    while (curr) {
        if (isFirst) {
            cout << curr->data;
            isFirst = false;
        } else {
            cout << ", " << curr->data;
        }
        curr = curr->next;
    }
    cout << "]\n";
}