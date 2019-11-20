#include <iostream>

using namespace std;

int main() {
    double n;
    cout << "Enter a real number:" << endl;
    cin >> n;
    double *l = new double;
    *l = 0.0;
    double *r = new double;
    *r = n;
    double *mid = new double;
    const double error = 0.00001;
    while (*r - *l > error) {
        *mid = (*l + *r) / 2;
        if (*mid * *mid > n) {
            *r = *mid;
        } else if (*mid * *mid < n) {
            *l = *mid;
        } else {
            break;
        }
    }
    cout << "Square root of " << n << " is " << *mid << endl;
    return 0;
}