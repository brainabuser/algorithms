//
// Created by Vladimir on 26.05.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    long double x;
    long double y;
};

struct Vector {
    long double x;
    long double y;
};

struct Segment {
    Point begin;
    Point end;
};

long double getTriangleArea(const Point &pivot, const Segment &segment);

int main() {
    Point pivot{};
    cin >> pivot.x >> pivot.y;
    int n;
    cin >> n;
    vector<Segment> segments(n);
    for (auto &item : segments) {
        cin >> item.begin.x >> item.begin.y
            >> item.end.x >> item.end.y;
    }
    sort(segments.begin(), segments.end(), [pivot](const Segment &lhs,
                                                   const Segment &rhs) {
        return getTriangleArea(pivot, lhs) < getTriangleArea(pivot, rhs);
    });
    for (const auto &item : segments) {
        cout << item.begin.x << ' ' << item.begin.y << ' '
             << item.end.x << ' ' << item.end.y << endl;
    }
    return 0;
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

long double getTriangleArea(const Point &pivot, const Segment &segment) {
    Vector lhs = {segment.begin.x - pivot.x, segment.begin.y - pivot.y};
    Vector rhs = {segment.end.x - pivot.x, segment.end.y - pivot.y};
    return fabsl(1. / 2 * vectorProduct(lhs, rhs));
}