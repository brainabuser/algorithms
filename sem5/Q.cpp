#include <iostream>
#include <cstring>

using namespace std;

char *concat(char *lhs, char rhs) {
    lhs[strlen(lhs) + 1] = '\0';
    lhs[strlen(lhs)] = rhs;
    return lhs;
}

char *fixLine(char *line) {
    char *result = new char[100000];
    memset(result, 0, 100000);
    int i = 0;
    while (line[i] == ' ') {
        ++i;
    }
    while (i < strlen(line)) {
        if (isalpha(line[i])) {
            concat(result, line[i]);
        } else if (line[i] == ',' || line[i] == '.') {
            concat(result, line[i]);
            if (isalpha(line[i + 1])) {
                concat(result, ' ');
            }
        } else if (line[i] == ' ' && isalpha(line[i + 1])) {
            concat(result, ' ');
        }
        ++i;
    }
    return result;
}

int main() {
    char line[100000];
    cin.getline(line, 100000);
    cout << fixLine(line) << endl;
    return 0;
}