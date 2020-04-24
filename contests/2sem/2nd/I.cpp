//
// Created by Vladimir on 23.04.2020.
//

#include <iostream>
#include <cmath>
#include <vector>

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

bool isInsidePolygon(const Point &point, const vector<Point> &polygon);

bool belongsToPolygon(const Point &point, const vector<Point> &polygon);

int main() {
    int n;
    Point p{};
    cin >> n >> p.x >> p.y;
    vector<Point> polygon;
    for (int i = 0; i < n; ++i) {
        Point temp{};
        cin >> temp.x >> temp.y;
        polygon.push_back(temp);
    }
    cout << ((isInsidePolygon(p, polygon) || belongsToPolygon(p, polygon)) ? "YES" : "NO") << endl;
    return 0;
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

long double scalarProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

long double getAbs(const Vector &v) {
    return sqrt(scalarProduct(v, v));
}

long double getAngle(const Vector &v1, const Vector &v2) {
    long double result = scalarProduct(v1, v2);
    result /= getAbs(v1);
    result /= getAbs(v2);
    return result;
}

bool isInsidePolygon(const Point &point, const vector<Point> &polygon) {
    vector<Vector> vectors;
    for (const auto &i : polygon) {
        vectors.push_back(Vector{i.x - point.x,
                                 i.y - point.y});
    }
    vectors.push_back(vectors.front());
    long double sumAngle = 0.0;
    for (size_t i = 1; i < vectors.size(); ++i) {
        long double p = vectorProduct(vectors.at(i - 1), vectors.at(i));
        short sign = (signbit(p)) ? -1 : 1;
        sumAngle += sign * acos(getAngle(vectors.at(i - 1), vectors.at(i)));
    }
    return fabsl(round(sumAngle / 2.0)) > 0.0;
}

bool belongsToLine(const Point &point, const Line &line) {
    return line.a * point.x + line.b * point.y + line.c == 0.0;
}

bool belongsToRay(const Point &point, const Vector &vector, const Line &ray) {
    return belongsToLine(point, ray) && (scalarProduct(vector, ray.v) >= 0.0);
}

bool belongsToLineSegment(const Point &point, const Segment &s) {
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
    return belongsToRay(point, ap, ab) && belongsToRay(point, bp, ba);
}

bool belongsToPolygon(const Point &point, const vector<Point> &polygon) {
    vector<Segment> segments;
    for (size_t i = 1; i < polygon.size(); ++i) {
        segments.push_back(Segment{polygon.at(i - 1), polygon.at(i)});
    }
    segments.push_back(Segment{polygon.back(), polygon.front()});
    for (const auto &s: segments) {
        if (belongsToLineSegment(point, s)) {
            return true;
        }
    }
    return false;
}