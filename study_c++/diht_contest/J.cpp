#include <iostream>

using namespace std;

int josephWillLive(const int &n, const int &k) {
    return (n == 1) ? 1 : (1 + (josephWillLive(n - 1, k) + k - 1) % n);
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << josephWillLive(n, k) << endl;
    return 0;
}