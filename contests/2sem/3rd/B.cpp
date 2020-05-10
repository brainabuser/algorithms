//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> beasts(n);
    for (auto &t : beasts) {
        cin >> t;
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        auto lower = lower_bound(beasts.begin(), beasts.end(), temp);
        cout << upper_bound(lower, beasts.end(), temp) - lower << endl;
    }
    return 0;
}