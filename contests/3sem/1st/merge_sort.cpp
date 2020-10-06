//
// Created by Vladimir on 10.09.2020.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct Student {
    string surname, name;
    double mean{};
} Student;

void readArray(vector<Student> &array, const int &size);

void printArray(const vector<Student> &array);

void merge(vector<Student>::iterator a_beg, vector<Student>::iterator a_end,
           vector<Student>::iterator b_beg, vector<Student>::iterator b_end);

void merge_sort(vector<Student>::iterator beg, vector<Student>::iterator end);

int main() {
    int n;
    cin >> n;
    vector<Student> s;
    s.reserve(n);
    readArray(s, n);
    merge_sort(s.begin(), s.end());
    printArray(s);
    return (0);
}

void readArray(vector<Student> &array, const int &size) {
    for (int i = 0; i < size; ++i) {
        Student temp;
        cin >> temp.surname >> temp.name;
        int info, math, lang;
        cin >> info >> math >> lang;
        temp.mean = (info + math + lang) / 3.0;
        array.emplace_back(temp);
    }
}

void printArray(const vector<Student> &array) {
    for (const auto &i : array) {
        cout << i.surname << ' ' << i.name << endl;
    }
}

void merge(vector<Student>::iterator a_beg, vector<Student>::iterator a_end,
           vector<Student>::iterator b_beg, vector<Student>::iterator b_end) {
    size_t c_size = a_end - a_beg + b_end - b_beg;
    vector<Student> merged;
    merged.reserve(c_size);
    auto first_beg = a_beg;
    auto second_beg = b_beg;
    while (first_beg != a_end && second_beg != b_end) {
        if (first_beg->mean >= second_beg->mean) {
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
    copy(merged.begin(), merged.end(), a_beg);
}

void merge_sort(vector<Student>::iterator beg, vector<Student>::iterator end) {
    int shift = distance(beg, end);
    if (shift <= 1)
        return;
    auto mid = next(beg, shift / 2);
    merge_sort(beg, mid);
    merge_sort(mid, end);
    merge(beg, mid, mid, end);
}