#include <iostream>

using namespace std;

int main() {
    int x;
    int cnt;
    cin >> x;
    for (cnt = 0; x != 0; ++cnt) {
        cin >> x;
    }
    cout << cnt << endl;
    return 0;
}

