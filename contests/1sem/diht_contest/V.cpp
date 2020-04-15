#include <iostream>

#include <cstring>

using namespace std;

void toBinary(char *decimal);

int main() {
    char text[256];
    cin.getline(text, 256);
    int i = 0;
    while (text[i] != '\0') {
        char buffer[256]{0};
        if (isdigit(text[i])) {
            int j = 0;
            while (isdigit(text[i])) {
                buffer[j++] = text[i++];
            }
            toBinary(buffer);
        }
        if (!isdigit(text[i]) && text[i] != '\0') {
            cout << text[i];
            ++i;
        }
    }
    return 0;
}

char *reverse(char *line) {
    size_t length = strlen(line);
    for (size_t i = 0; i < length / 2; ++i) {
        char temp = line[i];
        line[i] = line[length - i - 1];
        line[length - i - 1] = temp;
    }
    return line;
}

void toBinary(char *decimal) {
    char binary[5000]{0};
    int j = 0;
    while (strlen(decimal) != 0) {
        int k = 0;
        size_t capacity = strlen(decimal);
        char buffer[256]{0};
        bool hasFirstChar = false;
        int z = 0;//Счетчик цифр частного
        for (size_t i = 0; i < capacity; ++i) {
            int digit = decimal[i] - '0';
            int exp = (k * 10 + digit) / 2;
            if (exp != 0 || hasFirstChar) {
                buffer[z++] = (exp) + '0';
                hasFirstChar = true;
            }
            k = digit % 2;
        }
        binary[j++] = k + '0';
        strcpy(decimal, buffer);
    }
    reverse(binary);
    size_t size = strlen(binary);
    for (size_t i = 0; i < size; ++i) {
        cout << binary[i];
    }
}