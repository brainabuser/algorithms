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
    char begin, end;
    cin >> begin >> end;
    for (int i = begin; i <= end; ++i) {
        cout << char(i);
    }
    return 0;
}