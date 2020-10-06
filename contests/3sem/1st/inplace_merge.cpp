//
// Created by vladimir on 16.09.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void readArray(vector<int> &array, const int &size);

void printArray(const vector<int> &array);

void merge(vector<int>::iterator beg,
           vector<int>::iterator mid,
           vector<int>::iterator end);

int main() {
    int n;
    cin >> n;
    vector<int> a;
    a.reserve(n);
    readArray(a, n);
    int m;
    cin >> m;
    a.reserve(n + m);
    readArray(a, m);
    merge(a.begin(), a.begin() + n, a.end());
    printArray(a);
    return 0;
}

void readArray(vector<int> &array, const int &size) {
    for (int i = 0; i < size; ++i) {
        int temp;
        cin >> temp;
        array.emplace_back(temp);
    }
}

void printArray(const vector<int> &array) {
    for (const auto &item : array) {
        cout << item << ' ';
    }
}

void merge(vector<int>::iterator beg,
           vector<int>::iterator mid,
           vector<int>::iterator end) {
    auto l_len = distance(beg, mid);
    auto r_len = distance(mid, end);
    if (l_len == 0 || r_len == 0) {
        return;
    }
    if (l_len == 1 && r_len == 1) {
        if (*beg > *mid) {
            iter_swap(beg, mid);
        }
        return;
    }
    vector<int>::iterator l_b, r_b;
    if (l_len >= r_len) {
        l_b = next(beg, l_len / 2);
        r_b = lower_bound(mid, end, *l_b);
    } else {
        r_b = next(mid, r_len / 2);
        l_b = upper_bound(beg, mid, *r_b);
    }
    mid = rotate(l_b, mid, r_b);
    merge(beg, l_b, mid);
    merge(mid, r_b, end);
}