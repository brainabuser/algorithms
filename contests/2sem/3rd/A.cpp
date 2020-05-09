//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Team {
    int tasks;
    int extra_time;
    int number;
};

bool cmp(const Team &lhs, const Team &rhs);

int main() {
    int n;
    cin >> n;
    vector<Team> teams(n);
    int cnt = 1;
    for (auto &t : teams) {
        cin >> t.tasks >> t.extra_time;
        t.number = cnt++;
    }
    sort(teams.begin(), teams.end(), cmp);
    for (const auto &t : teams) {
        cout << t.number << endl;
    }
    return 0;
}

bool cmp(const Team &lhs, const Team &rhs) {
    if (lhs.tasks == rhs.tasks) {
        if (lhs.extra_time == rhs.extra_time) {
            return lhs.number < rhs.number;
        } else {
            return lhs.extra_time < rhs.extra_time;
        }
    } else {
        return lhs.tasks > rhs.tasks;
    }
}