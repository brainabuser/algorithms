#include <iostream>

#include <cstring>

using namespace std;

int main() {
    char s1[1001];
    cin.getline(s1, 1001);
    char s2[1001];
    cin.getline(s2, 1001);
    int size1 = strlen(s1);
    ++size1;
    int size2 = strlen(s2);
    ++size2;
    int **d = new int *[size1];
    for (int i = 0; i < size1; ++i) {
        d[i] = new int[size2];
        d[i][0] = i;
    }
    for (int j = 0; j < size2; ++j) {
        d[0][j] = j;
    }
    for (int i = 1; i < size1; ++i) {
        for (int j = 1; j < size2; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                d[i][j] = min(min(d[i][j - 1] + 1, d[i - 1][j] + 1), d[i - 1][j - 1]);
            } else {
                d[i][j] = 1 + min(min(d[i][j - 1], d[i - 1][j]), d[i - 1][j - 1]);
            }
        }
    }
    cout << d[size1 - 1][size2 - 1] << endl;
    for (int i = 0; i < size1; ++i) {
        delete[] d[i];
    }
    delete[] d;
    return 0;
}