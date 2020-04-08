#include <iostream>

#include <cmath>
#include <iomanip>

using namespace std;

double polynomValue(int a, int b, int c, int d, double value) {
    return a * pow(value, 3) + b * pow(value, 2) + c * value + d;
}

int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int max_a = max(max(abs(b), abs(c)), abs(d));
    int max_b = max(max(abs(a), abs(b)), abs(c));
    double limit = max((double) abs(d) / (abs(d) + max_b), 1.0 + (double)max_a / abs(a));
    double left = -limit;
    double right = limit;
    double middle;
    do {
        middle = (left + right) / 2.0;
        if (polynomValue(a, b, c, d, middle) == 0.0) {
            break;
        } else if (polynomValue(a, b, c, d, middle) * polynomValue(a, b, c, d, left) < 0.0) {
            right = middle;
        } else {
            left = middle;
        }
    } while (right - left > 0.000001);
    cout << setprecision(10) << middle << endl;
    return 0;
}
