#include <iostream>

#include <cstring>

using namespace std;

char *concat(char *lhs, char rhs);

int main() {
    char *word = new char[10000];
    cin.getline(word, 10000);
    char *line = new char[10000];
    cin.getline(line, 10000);
    char *copy_line = line;
    while (strlen(line) != 0) {
        unsigned length = strlen(line);
        for (size_t l = length; l > 0; --l) {
            char *subword = new char[10000];
            memset(subword, 0, 10000);
            for (size_t i = 0; i <= length - l; ++i) {
                concat(subword, line[i]);
            }
            if (strcmp(subword, word) == 0) {
                cout << "yes" << endl;
                delete[] subword;
                delete[] word;
                delete[] copy_line;
                return 0;
            }
            delete[] subword;
        }
        ++line;
    }
    cout << "no" << endl;
    delete[] word;
    delete[] copy_line;
    return 0;
}

char *concat(char *lhs, char rhs) {
    lhs[strlen(lhs) + 1] = '\0';
    lhs[strlen(lhs)] = rhs;
    return lhs;
}

