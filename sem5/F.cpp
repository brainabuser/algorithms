#include <iostream>
#include <cstring>

using namespace std;

char *caesarDecipher(char *line, int shift){
    for(size_t i = 0; i < strlen(line); ++i){
        line[i] = 'A' + (26 + (line[i] - 'A' - shift)) % 26;
    }
    return line;
}

int main() {
    char line[100000];
    cin.getline(line, 100000);
    int shift;
    cin >> shift;
    cout << caesarDecipher(line, shift) << endl;
    return 0;
}