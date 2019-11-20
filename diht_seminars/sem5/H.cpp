#include <iostream>
#include <cstring>

using namespace std;

bool isWord(char *line) {
    size_t size = strlen(line);
    if (size < 2) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (!isalpha(line[i])) {
            return false;
        }
    }
    return true;
}

int CountWords(char *line) {
    int numberOfWords = 0;
    int i = 0;
    int numberOfLetters = 0;
    while (line[i] != '\0') {
        if(isalpha(line[i])){
            if(line[i + 1] == '\0'){
                ++numberOfWords;
            }
            ++numberOfLetters;
        }else{
            if(numberOfLetters >= 1){
                ++numberOfWords;
            }
            numberOfLetters = 0;
        }
        ++i;
    }
    return numberOfWords;
}

int main() {
    char line[1000000];
    cin.getline(line, 1000000);
    cout << CountWords(line) << endl;
    return 0;
}