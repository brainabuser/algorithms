#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    auto *array = new unsigned long long[n];
    auto *answer = new unsigned long long[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        answer[i] = 1;
    }
    unsigned long long sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (array[j] < array[i]) {
                answer[i] += answer[j] % 1000000;
            }
        }
        sum += answer[i];
        sum %= 1000000;
    }
    cout << sum << endl;
    delete[] array;
    delete[] answer;
    return 0;
}