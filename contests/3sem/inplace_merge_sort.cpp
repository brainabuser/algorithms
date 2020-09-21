//
// Created by Vladimir on 21.09.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Student {
    string surname, name;
    double mean{};
} Student;

void readArray(vector<Student> &array);

void printArray(const vector<Student> &array);

void merge_sort(vector<Student>::iterator beg, vector<Student>::iterator end);

bool operator<(const Student &lhs, const Student &rhs) {
    return lhs.mean < rhs.mean;
}

bool operator>(const Student &lhs, const Student &rhs) {
    return lhs.mean > rhs.mean;
}

int main() {
    int n;
    cin >> n;
    vector<Student> students(n);
    readArray(students);
    merge_sort(students.begin(), students.end());
    printArray(students);
    return 0;
}

void readArray(vector<Student> &array) {
    for (auto &item : array) {
        cin >> item.surname >> item.name;
        int info, math, lang;
        cin >> info >> math >> lang;
        item.mean = (info + math + lang) / 3.0;
    }
}

void printArray(const vector<Student> &array) {
    for (const auto &item : array) {
        cout << item.surname << ' ' << item.name << '\n';
    }
}

void merge(vector<Student>::iterator beg,
           vector<Student>::iterator mid,
           vector<Student>::iterator end) {
    auto l_len = distance(beg, mid);
    auto r_len = distance(mid, end);
    if (l_len == 0 || r_len == 0) {
        return;
    }
    if (l_len == 1 && r_len == 1) {
        if (*beg < *mid) {
            iter_swap(beg, mid);
        }
        return;
    }
    vector<Student>::iterator l_b, r_b;
    if (l_len >= r_len) {
        l_b = next(beg, l_len / 2);
        r_b = lower_bound(mid, end, *l_b, greater<>());
    } else {
        r_b = next(mid, r_len / 2);
        l_b = upper_bound(beg, mid, *r_b, greater<>());
    }
    mid = rotate(l_b, mid, r_b);
    merge(beg, l_b, mid);
    merge(mid, r_b, end);
}

void merge_sort(vector<Student>::iterator beg, vector<Student>::iterator end) {
    auto shift = distance(beg, end);
    if (shift < 2) {
        return;
    }
    auto mid = next(beg, shift / 2);
    merge_sort(beg, mid);
    merge_sort(mid, end);
    merge(beg, mid, end);
}