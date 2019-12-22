#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (array[i] > array[j]) {
                swap(array[i], array[j]);
            }
        }
    }
    int *answer = new int[n];
    answer[0] = 0;
    answer[1] = array[1] - array[0];
    for (int i = 2; i < n; ++i) {
        answer[i] = array[i] - array[i - 1];
        answer[i] += (i == 2) ? answer[i - 1] : min(answer[i - 2], answer[i - 1]);
    }
    cout << answer[n - 1] << endl;
    delete[] array;
    delete[] answer;
    return 0;
}