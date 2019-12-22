#include <iostream>

using namespace std;

int main() {
    //GCD
    int a, b;
    cout << "Enter \"a\" value:" << endl;
    cin >> a;
    cout << "Enter \"b\" value:" << endl;
    cin >> b;
    while (b != 0) {
        if (b < a) {
            swap(a, b);
        }
        b %= a;
    }
    cout << "Greatest common divisor is " << a << endl;
    return 0;
}


