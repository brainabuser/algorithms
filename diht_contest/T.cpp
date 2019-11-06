#include <iostream>

#include <cstring>

using namespace std;

char *concat(char *lhs, char rhs);

void deleteLastChar(char *line);

void clear(char *line);

int main() {
    char password[10000];
    cin.getline(password, 10000);
    int i = 0;
    char result[10000];
    while (password[i] != '\0') {
        if (isalpha(password[i])) {
            concat(result, password[i]);
        } else if (password[i] == '#') {
            deleteLastChar(result);
        } else if (password[i] == '@') {
            clear(result);
        }
        ++i;
    }
    cout << result << endl;
    return 0;
}

char *concat(char *lhs, char rhs) {
    lhs[strlen(lhs) + 1] = '\0';
    lhs[strlen(lhs)] = rhs;
    return lhs;
}

void deleteLastChar(char *line) {
    line[strlen(line) - 1] = '\0';
}

void clear(char *line) {
    line[0] = '\0';
}
