#include <iostream>

using namespace std;

int64_t greatest_common_divisor(int64_t a, int64_t b);

int64_t least_common_multiple(const int64_t &a, const int64_t &b, const int64_t &gcd);

int main() {
    int a, b;
    cin >> a >> b;
    int64_t gcd = greatest_common_divisor(a, b);
    int64_t lcm = least_common_multiple(a, b, gcd);
    cout << gcd << ' ' << lcm << endl;
    return 0;
}

int64_t greatest_common_divisor(int64_t a, int64_t b) {
    if(a == 0){
        return b;
    }
    while (b != 0) {
        if (b < a) {
            swap(a, b);
        }
        b %= a;
    }
    return a;
}

int64_t least_common_multiple(const int64_t &a, const int64_t &b, const int64_t &gcd) {
    if(a == 0 || b == 0){
        return 1;
    }
    return a * b / gcd;
}
