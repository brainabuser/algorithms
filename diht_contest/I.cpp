#include <iostream>

using namespace std;

int fib(const int &n);

int main() {
    int n;
    cin >> n;
    int result = fib(n);
    if (n < 11) {
        cout << result << endl;
    } else {
        cout.fill('0');
        cout.width(3);
        cout << result % 1000 << endl;
    }
    return 0;
}

int fib(const int &n) {
    int first, second, third;
    first = second = third = 1;
    for (int i = 2; i < n; ++i) {
        third = (first + second) % 1000;
        int temp = second;
        second = third;
        first = temp;
    }
    return third;
}