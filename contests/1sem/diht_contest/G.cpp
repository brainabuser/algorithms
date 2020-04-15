#include <iostream>

using namespace std;

int main() {
    unsigned a, b;
    cin >> a >> b;
    unsigned digits[10] = {0,};
    while (b >= a) {
        unsigned tmp = a;
        while (tmp != 0) {
            unsigned digit = tmp % 10;
            ++digits[digit];
            tmp /= 10;
        }
        ++a;
    }
    for (int i = 0; i < 10; ++i) {
        cout << digits[i] << ' ';
    }
    return 0;
}

