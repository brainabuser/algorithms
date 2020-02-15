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

int main() {
    for (int i = 33; i <= 126; ++i) {
        cout << char(i) << " " << i << endl;
    }
    return 0;
}