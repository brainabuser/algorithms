//
// Created by Vladimir on 20.04.2020.
//
#include <iostream>
#include <iomanip>

using namespace std;

struct Point {
    long double x;
    long double y;
};

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

struct Segment {
    Point begin;
    Point end;
};

bool isBelongsToLine(const Point &point, const Line &line);

bool isBelongsToRay(const Point &point, const Vector &vector, const Line &ray);

bool isBelongsToLineSegment(const Point &point, const Segment &s);

int main() {
    Point c{};
    cin >> c.x >> c.y;
    Point a{};
    cin >> a.x >> a.y;
    Point b{};
    cin >> b.x >> b.y;
    long double a1 = b.y - a.y;
    long double b1 = a.x - b.x;
    long double c1 = -(a1 * a.x + b1 * a.y);
    Line ab{a1, b1, c1, {b1, -a1}};
    cout << (isBelongsToLine(c, ab) ? "YES" : "NO") << endl;
    Vector ap{a.x - c.x, a.y - c.y};
    cout << (isBelongsToRay(c, ap, ab) ? "YES" : "NO") << endl;
    Segment a_b{a, b};
    cout << (isBelongsToLineSegment(c, a_b) ? "YES" : "NO") << endl;
    return 0;
}

long double scalarProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

bool isBelongsToLine(const Point &point, const Line &line) {
    return line.a * point.x + line.b * point.y + line.c == 0.0;
}

bool isBelongsToRay(const Point &point, const Vector &vector, const Line &ray) {
    return isBelongsToLine(point, ray) && (scalarProduct(vector, ray.v) >= 0.0);
}

bool isBelongsToLineSegment(const Point &point, const Segment &s) {
    long double a = s.end.y - s.begin.y;
    long double b = s.begin.x - s.end.x;
    long double c = -(a * s.begin.x + b * s.begin.y);
    Line ab{a, b, c, {b, -a}};
    c = a * s.end.x + b * s.end.y;
    Line ba{-a, -b, c, {-b, a}};
    a = point.y - s.begin.y;
    b = s.begin.x - point.x;
    Vector ap{b, -a};
    a = point.y - s.end.y;
    b = s.end.x - point.x;
    Vector bp{b, -a};
    return isBelongsToRay(point, ap, ab) && isBelongsToRay(point, bp, ba);
}
