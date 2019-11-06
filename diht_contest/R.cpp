#include <iostream>

#include <cstring>

using namespace std;

char *concat(char *lhs, char rhs);

bool isPalindrome(const char *word);

int main() {
    char *line = new char[255];
    cin.getline(line, 255);
    char *copy_line = line;
    while (strlen(line) != 0) {
        unsigned length = strlen(line);
        for (size_t l = length; l > 0; --l) {
            char *subword = new char[255];
            memset(subword, 0, 255);
            for (size_t i = 0; i <= length - l; ++i) {
                concat(subword, line[i]);
            }
            if (isPalindrome(subword) && strlen(subword) > 1) {
                cout << subword << endl;
                delete[] subword;
                delete[] copy_line;
                return 0;
            }
            delete[] subword;
        }
        ++line;
    }
    cout << 0 << endl;
    delete[] copy_line;
    return 0;
}

bool isPalindrome(const char *word) {
    int length = strlen(word);
    size_t size = strlen(word) / 2;
    for (size_t i = 0; i < size; ++i) {
        if (word[i] != word[length - i - 1]) {
            return false;
        }
    }
    return true;
}

char *concat(char *lhs, char rhs) {
    lhs[strlen(lhs) + 1] = '\0';
    lhs[strlen(lhs)] = rhs;
    return lhs;
}

