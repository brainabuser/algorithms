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

char *ExtractDigits(char *line) {
    int amount_of_digits = 0;
    for (size_t i = 0; i < strlen(line); ++i) {
        if (isDigit(line[i])) {
            ++amount_of_digits;
        }
    }
    char *output_line = new char[amount_of_digits];
    int i, j;
    i = j = 0;
    while (line[i] != '\0') {
        if (isDigit(line[i])) {
            output_line[j++] = line[i];
        }
        ++i;
    }
    return output_line;
}

int main() {
    char line[100];
    cin.getline(line, 1000);
    cout << ExtractDigits(line) << endl;
    return 0;
}