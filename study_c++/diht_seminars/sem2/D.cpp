#include <iostream>

using namespace std;

int main() {
    int cnt, x;
    cin >> x;
    for (cnt = 0; x != 0;) {
        if (x % 2 == 0) {
            ++cnt;
        }
        cin >> x;
    }
    cout << cnt << endl;
    return 0;
}

