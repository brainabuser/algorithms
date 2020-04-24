//
// Created by Vladimir on 22.04.2020.
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

struct Line {
    long double a;
    long double b;
    long double c;
};

bool isIntersect(const Segment &s1, const Segment &s2);

long double getDistance(const Segment &s1, const Segment &s2);

int main() {
    Segment s1{}, s2{};
    cin >> s1.begin.x >> s1.begin.y >> s1.end.x >> s1.end.y;
    cin >> s2.begin.x >> s2.begin.y >> s2.end.x >> s2.end.y;
    cout << fixed << setprecision(7);
    cout << (isIntersect(s1, s2) ? 0.0 : getDistance(s1, s2)) << endl;
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

long double scalarProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

long double getDistance(const Point &p, const Line &line) {
    return fabsl(line.a * p.x + line.b * p.y + line.c) / sqrt(pow(line.a, 2) + pow(line.b, 2));
}

long double getDistance(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

long double getDistance(const Point &p, const Segment &s) {
    Vector ac = {p.x - s.begin.x, p.y - s.begin.y};
    Vector bc = {p.x - s.end.x, p.y - s.end.y};
    Vector ab = {s.end.x - s.begin.x, s.end.y - s.begin.y};
    if ((scalarProduct(ac, ab) >= 0.0) && (scalarProduct(bc, ab) <= 0.0)) {
        long double a = s.end.y - s.begin.y;
        long double b = s.begin.x - s.end.x;
        long double c = -(a * s.begin.x + b * s.begin.y);
        return getDistance(p, Line{a, b, c});
    } else {
        return min(getDistance(p, s.begin), getDistance(p, s.end));
    }
}

long double getDistance(const Segment &s1, const Segment &s2) {
    return min(min(getDistance(s1.begin, s2), getDistance(s1.end, s2)),
               min(getDistance(s2.begin, s1), getDistance(s2.end, s1)));
}
