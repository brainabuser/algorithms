#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int *array = new int[n];
    int *answer = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        answer[i] = 1;
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (array[j] < array[i]) {
                answer[i] += answer[j];
            }
        }
        sum += answer[i] % 1000000;
    }
    cout << sum << endl;
    delete[] array;
    delete[] answer;
    return 0;
}