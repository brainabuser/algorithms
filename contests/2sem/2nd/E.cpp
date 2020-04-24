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

struct Line {
    long double a;
    long double b;
    long double c;
    Vector v;
};

struct Point {
    long double x;
    long double y;
};

long double getDistance(const Point &p, const Line &line);

long double getDistance(const Point &p1, const Point &p2, const Vector &v1, const Line &line);

long double getDistance(const Point &p1, const Point &p2,
                        const Point &p3, const Vector &v1,
                        const Vector &v2, const Line &line);

int main() {
    Point c{};
    Point a{};
    Point b{};
    cin >> c.x >> c.y
        >> a.x >> a.y
        >> b.x >> b.y;
    long double a1 = b.y - a.y;
    long double b1 = a.x - b.x;
    long double c1 = -(a1 * a.x + b1 * a.y);
    Line ab{a1, b1, c1};
    ab.v = {-b1, a1};
    Vector ac{c.x - a.x, c.y - a.y};
    Vector bc{c.x - b.x, c.y - b.y};
    cout << fixed << setprecision(7);
    cout << getDistance(c, ab) << endl;
    cout << getDistance(c, a, ac, ab) << endl;
    cout << getDistance(c, a, b, ac, bc, ab) << endl;
    return 0;
}

long double getDistance(const Point &p, const Line &line) {
    return fabsl(line.a * p.x + line.b * p.y + line.c) / sqrt(pow(line.a, 2) + pow(line.b, 2));
}

long double getDistance(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

long double scalarProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

long double getDistance(const Point &p1, const Point &p2, const Vector &v1, const Line &line) {
    return (scalarProduct(v1, line.v) >= 0.0) ? getDistance(p1, line) : getDistance(p1, p2);
}

long double getDistance(const Point &p1, const Point &p2,
                        const Point &p3, const Vector &v1,
                        const Vector &v2, const Line &line) {
    if ((scalarProduct(v1, line.v) >= 0.0) && (scalarProduct(v2, line.v) <= 0.0)) {
        return getDistance(p1, line);
    } else {
        return min(getDistance(p1, p2), getDistance(p1, p3));
    }
};