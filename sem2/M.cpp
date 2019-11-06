#include <iostream>

using namespace std;

int main() {
    int loc_max, x;
    cin >> x;
    int prev = x;
    cin >> x;
    int curr = x;
    int cnt = 0;
    while (x != 0) {
        cin >> x;
        int next = x;
        if (curr > prev && curr > next && next != 0) {
            loc_max = curr;
            ++cnt;
        }
        prev = curr;
        curr = next;
    }
    cout << cnt << endl;
    return 0;
}

