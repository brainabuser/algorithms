//
// Created by Vladimir on 10.09.2020.
//

#include <iostream>

#include <vector>

using namespace std;

void readArray(vector<int> &array, const int &size);
void printArray(const vector<int> &array);
vector<int> merge(vector<int>::iterator a_beg, vector<int>::iterator a_end,
                  vector<int>::iterator b_beg, vector<int>::iterator b_end);
int main() {
    int n;
    cin >> n;
    vector<int> a;
    a.reserve(n);
    readArray(a, n);
    int m;
    cin >> m;
    vector<int> b;
    b.reserve(m);
    readArray(b, m);
    printArray(merge(a.begin(), a.end(), b.begin(), b.end()));
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

vector<int> merge(vector<int>::iterator a_beg, vector<int>::iterator a_end,
                  vector<int>::iterator b_beg, vector<int>::iterator b_end) {
    size_t c_size = a_end - a_beg + b_end - b_beg;
    vector<int> merged;
    merged.reserve(c_size);
    auto first_beg = a_beg;
    auto second_beg = b_beg;
    while (first_beg != a_end && second_beg != b_end) {
        if (*first_beg <= *second_beg) {
            merged.emplace_back(*first_beg);
            first_beg = next(first_beg);
        } else {
            merged.emplace_back(*second_beg);
            second_beg = next(second_beg);
        }
    }
    for (; first_beg != a_end; first_beg = next(first_beg)) {
        merged.emplace_back(*first_beg);
    }
    for (; second_beg != b_end; second_beg = next(second_beg)) {
        merged.emplace_back(*second_beg);
    }
    return merged;
}