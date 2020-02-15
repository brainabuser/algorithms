#include <iostream>

using namespace std;

int main() {
    int x, sum;
    sum = 0;
    cin >> x;
    while (x != 0) {
        sum += x;
        cin >> x;
    }
    cout << sum << endl;
    return 0;
}

