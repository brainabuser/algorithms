#include <iostream>

#include <cmath>

using namespace std;

bool *toBinary(int number, int n);

bool isPair(int a, int b, int n);

int main() {
    int n, m;
    cin >> n >> m;
    if (n > m) {
        swap(n, m);
    }
    int possibleValues = pow(2, n);
    int **tiles = new int *[m];
    for (int i = 0; i < m; ++i) {
        tiles[i] = new int[possibleValues];
    }
    bool **pairs = new bool *[possibleValues];
    for (int i = 0; i < possibleValues; ++i) {
        pairs[i] = new bool[possibleValues];
        for (int j = 0; j <= i; ++j) {
            pairs[i][j] = pairs[j][i] = isPair(i, j, n);
        }
    }
    for (int i = 0; i < possibleValues; ++i) {
        tiles[0][i] = 1;
    }
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < possibleValues; ++j) {
            tiles[i][j] = 0;
            for (int k = 0; k < possibleValues; ++k) {
                if (pairs[j][k]) {
                    tiles[i][j] += tiles[i - 1][k];
                }
            }
        }
    }
    for (int i = 0; i < possibleValues; ++i) {
        delete[] pairs[i];
    }
    delete[] pairs;
    int answer = 0;
    for (int i = 0; i < possibleValues; ++i) {
        answer += tiles[m - 1][i];
    }
    cout << answer << endl;
    for (int i = 0; i < m; ++i) {
        delete[] tiles[i];
    }
    delete[] tiles;
    return 0;
}

bool *toBinary(int number, int n) {
    bool *binary = new bool[n];
    int size = n - 1;
    while (number != 0) {
        binary[size--] = number % 2 == 1;
        number /= 2;
    }
    while (size >= 0) {
        binary[size--] = false;
    }
    return binary;
}

bool isPair(int a, int b, int n) {
    bool answer = true;
    bool *bin_a = toBinary(a, n);
    bool *bin_b = toBinary(b, n);
    for (int i = 1; i < n; ++i) {
        if ((bin_a[i] && bin_a[i - 1] && bin_b[i] && bin_b[i - 1]) ||
            (!(bin_a[i] || bin_a[i - 1]) && !(bin_b[i] || bin_b[i - 1]))) {
            answer = false;
            break;
        }
    }
    delete[] bin_a;
    delete[] bin_b;
    return answer;
}