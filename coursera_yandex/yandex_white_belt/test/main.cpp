#include <iostream>
using namespace std;

int main() {
    int sum = 0;    // Количество одинаковых элементов
    int k = 0;      // Счетчик
    int rem = 0;    // Remember2
    int n;
    cin >> n;
    int mass[10000];
    for (int i = 0; i < n; ++i) {
        cin >> mass[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {      // Оптимизация с началом с i, а не с нуля
            if (mass[i] == mass[j]) {
                ++k;
            }
        }
        if (k > sum) {
            sum = k;
            rem = mass[i];
        }
        if (k == sum && mass[i] < rem) {
            rem = mass[i];
        }
        k = 0;
    }
    cout << rem << endl;
}
