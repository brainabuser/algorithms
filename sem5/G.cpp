#include <iostream>
#include <cstring>

using namespace std;

bool isDigit(const char &c) {
    return ('0' <= c && c <= '9');
}

long long Eval(char *line) {
    char lineCopy[100000];
    strcpy(lineCopy, line);
    char *exp = strtok(lineCopy, "+-*");
    long long firstOperand = atoi(exp);
    exp = strtok(nullptr, "+-*");
    long long secondOperand = atoi(exp);
    long long result;
    if (strchr(line, '+') != nullptr) {
        result = firstOperand + secondOperand;
    } else if (strchr(line, '-') != nullptr) {
        result = firstOperand - secondOperand;
    } else if (strchr(line, '*') != nullptr) {
        result = firstOperand * secondOperand;
    } else {
        throw invalid_argument("Line is incorrect");
    }
    return result;
}

int main() {
    char line[1000000];
    cin.getline(line, 1000000);
    cout << Eval(line) << endl;
    return 0;
}