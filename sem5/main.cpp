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
    char word[] = "word";
    printWord(word);
    word[0] = '\0';
    printWord(word);
    int a = atoi("2.1la");
    cout << a;
    return 0;
}