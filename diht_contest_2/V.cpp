#include <iostream>

using namespace std;

int main() {
    int size1;
    cin >> size1;
    ++size1;
    int *seq1 = new int[size1];
    seq1[0] = 0;
    for (int i = 1; i < size1; ++i) {
        cin >> seq1[i];
    }
    int size2;
    cin >> size2;
    ++size2;
    int *seq2 = new int[size2];
    seq2[0] = 0;
    for (int i = 1; i < size2; ++i) {
        cin >> seq2[i];
    }
    int **cls = new int *[size1];
    for (int i = 0; i < size1; ++i) {
        cls[i] = new int[size2]();
    }
    int size = min(size1, size2);
    int *seq = new int[size];
    int cnt = 0;
    for (int i = 1; i < size1; ++i) {
        for (int j = 1; j < size2; ++j) {
            if (seq1[i] == seq2[j]) {
                cls[i][j] = cls[i - 1][j - 1] + 1;
                if (cnt < cls[i][j]) {
                    seq[cnt++] = seq1[i];
                }
            } else {
                cls[i][j] = max(cls[i - 1][j], cls[i][j - 1]);
            }
        }
    }
    for (int i = 0; i < cnt; ++i) {
        cout << seq[i] << ' ';
    }
    delete[] seq;
    delete[] seq1;
    delete[] seq2;
    for (int i = 0; i < size1; ++i) {
        delete[] cls[i];
    }
    delete[] cls;
    return 0;
}