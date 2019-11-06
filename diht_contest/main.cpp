#include <iostream>

#include <cstring>

using namespace std;

int main() {
    char a[200];
    char b[200]{0};
    cin.getline(a, 200);
    int i = 0;
    while (a[i] != '\0') {
        if (a[i] == '#') {
            b[strlen(b) - 1] = '\0';
        } else if (a[i] == '@') {
            b[0] = '\0';
        } else {
            b[strlen(b) + 1] = '\0';
            b[strlen(b)] = a[i];
        }
        ++i;
    }
    cout <<b << endl;
}

// Created by rombe on 29.10.2019.
//
