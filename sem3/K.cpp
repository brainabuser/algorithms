#include <iostream>

using namespace std;

int main() {
    int array[10000], n;
    cin >> n;
    cin >> array[0];
    int prev = array[0];
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
        cin >> array[i];
        if (array[i] != prev) {
            ++cnt;
            prev = array[i];
        }
    }
    cout << cnt << endl;
    return 0;
}


