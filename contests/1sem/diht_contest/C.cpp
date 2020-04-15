#include <iostream>

using namespace std;

int64_t modular_pow(int64_t &base, int64_t &exponent, const int64_t &modulus);

int main() {
    int64_t x, y, p;
    cin >> x >> y >> p;
    cout << modular_pow(x, y, p) << endl;
    return 0;
}

int64_t modular_pow(int64_t &base, int64_t &exponent, const int64_t &modulus) {
    if (modulus == 1) {
        return 0;
    }
    int64_t result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * base % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

