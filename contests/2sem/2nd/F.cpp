//
// Created by Vladimir on 20.04.2020.
//
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Vector {
    long double x;
    long double y;
};

struct Point {
    long double x;
    long double y;
};

struct Segment {
    Point begin;
    Point end;
};

bool isIntersect(const Segment &s1, const Segment &s2);

int main() {
    Segment s1{}, s2{};
    cin >> s1.begin.x >> s1.begin.y >> s1.end.x >> s1.end.y;
    cin >> s2.begin.x >> s2.begin.y >> s2.end.x >> s2.end.y;
    cout << (isIntersect(s1, s2) ? "YES" : "NO") << endl;
    return 0;
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

bool isIntersect(const Segment &s1, const Segment &s2) {
    Vector t1p1{s2.begin.x - s1.begin.x, s2.begin.y - s1.begin.y};
    Vector t1p2{s2.end.x - s1.begin.x, s2.end.y - s1.begin.y};
    Vector t1t2{s1.end.x - s1.begin.x, s1.end.y - s1.begin.y};
    bool cnd1 = (vectorProduct(t1t2, t1p1) * vectorProduct(t1t2, t1p2) <= 0.0);
    Vector p1t2{s1.end.x - s2.begin.x, s1.end.y - s2.begin.y};
    Vector p1t1{-t1p1.x, -t1p1.y};
    Vector p1p2{s2.end.x - s2.begin.x, s2.end.y - s2.begin.y};
    bool cnd2 = (vectorProduct(p1p2, p1t1) * vectorProduct(p1p2, p1t2) <= 0.0);
    long double minX1 = min(s1.begin.x, s1.end.x);
    long double minX2 = min(s2.begin.x, s2.end.x);
    long double minY1 = min(s1.begin.y, s1.end.y);
    long double minY2 = min(s2.begin.y, s2.end.y);
    long double maxX1 = max(s1.begin.x, s1.end.x);
    long double maxX2 = max(s2.begin.x, s2.end.x);
    long double maxY1 = max(s1.begin.y, s1.end.y);
    long double maxY2 = max(s2.begin.y, s2.end.y);
    bool cnd3 = minY1 > maxY2;
    bool cnd4 = minX1 > maxX2;
    bool cnd5 = maxX1 < minX2;
    bool cnd6 = maxY1 < minY2;
    return (cnd1 && cnd2) && !(cnd3 || cnd4 || cnd5 || cnd6);
}