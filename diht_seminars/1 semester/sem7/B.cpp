#include <iostream>

using namespace std;

double power(double &a, const int &n);

int main() {
    double a;
    int n;
    cin >> a >> n;
    cout << power(a, n) << endl;
    return 0;
}

double power(double &a, const int &n) {
    if (n == 1) {
        return a;
    }else if(n == 0){
        return 1;
    }
    return (n % 2 == 0) ? power(a, n / 2) * power(a, n / 2) : a * power(a, n - 1);
}
