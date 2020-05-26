//
// Created by Vladimir on 20.04.2020.
//

#include <iostream>

using namespace std;

int f(int const *a) {
    return sizeof(a);
}

int main() {
    int a[10] = {1, 2, 3, 4, 5};
    int *b = new int[10];
    cout << f(a) << endl;
    cout << f(b) << endl;
    return 0;
}