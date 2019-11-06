#include <iostream>
#include <cstring>

using namespace std;

bool isDigit(const char &c) {
    return ('0' <= c && c <= '9');
}

int Evaluate(char *line) {
    int result = 0;
    int number;
    char operation;
    for (size_t i = 0; i < strlen(line); ++i) {
        if (!isDigit(line[i])) {
            operation = line[i];
        } else {
            number = atoi(&line[i]);
            if (operation == '-') {
                result -= number;
            } else if (operation == '+') {
                result += number;
            } else if (i == 0) {
                result = number;
            }
        }
    }
    return result;
}

int main() {
    char line[100000];
    cin.getline(line, 100000);
    cout << Evaluate(line) << endl;
    return 0;
}