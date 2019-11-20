#include <iostream>
#include <cstring>

using namespace std;

void printWord(char *word) {
    int i = 0;
    while (word[i] != '\0') {
        cout << word[i];
        ++i;
    }
    cout << endl;
    cout << "Length of word = " << strlen(word) << endl;
}

bool isDigit(const char &c) {
    return ('0' <= c && c <= '9');
}

int main() {
    char c;
    cin >> c;
    if (isDigit(c)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    cout << endl;
    return 0;
}