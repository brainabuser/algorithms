#include <iostream>

using namespace std;

int main() {
    int array[10000], n;
    cin >> n;
    int cnt = 0;
    cin >> array[0];
    cin >> array[1];
    for (int i = 2; i < n; ++i) {
        cin >> array[i];
        int prev = array[i - 2];
        int curr = array[i - 1];
        int next = array[i];
        if (curr > prev && curr > next) {
            ++cnt;
        }
    }
    cout << cnt << endl;
    return 0;
}


