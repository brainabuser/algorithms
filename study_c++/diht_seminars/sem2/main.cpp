#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int result = 1;
    while (n) {
        result *= 5;
        --n;
    }
    cout << result << endl;
    return 0;
}