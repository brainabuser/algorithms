#include <iostream>

using namespace std;

int main() {
    int array[100], n;
    cin >> n;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
        if (array[i] > 0) {
            ++cnt;
        }
    }
    cout << cnt << endl;
    return 0;
}


