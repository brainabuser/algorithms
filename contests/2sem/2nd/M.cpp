//
// Created by Vladimir on 27.04.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Vector {
    long double x;
    long double y;
};

struct Point {
    long double x;
    long double y;
    Vector r;
};

vector<Point> getHull(vector<Point> &points);

long double getSquare(const vector<Point> &polygon);

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (auto &p : points) {
        cin >> p.x >> p.y;
    }
    vector<Point> hull = getHull(points);
    cout << hull.size() << endl;
    cout << fixed << setprecision(0);
    for (const auto &o : hull) {
        cout << o.x << ' ' << o.y << endl;
    }
    cout << fixed << setprecision(1) << getSquare(hull) << endl;
    return 0;
}

int getPivotIndex(const vector<Point> &points) {
    int index = 0;
    size_t size = points.size();
    for (size_t i = 0; i < size; ++i) {
        if ((points.at(i).x < points.at(index).x)
            || (points.at(i).x == points.at(index).x
                && points.at(i).y < points.at(index).y)) {
            index = i;
        }
    }
    return index;
}

long double vectorProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

long double scalarProduct(const Vector &lhs, const Vector &rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

bool compareByAngle(const Point &p1, const Point &p2) {
    long double p = vectorProduct(p1.r, p2.r);
    return (p < 0.0) || (p == 0.0 && (scalarProduct(p1.r, p1.r) < scalarProduct(p2.r, p2.r)));
}

bool operator==(const Point &lhs, const Point &rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

vector<Point> getHull(vector<Point> &points) {
    swap(points.at(getPivotIndex(points)), points.front());
    size_t size = points.size();
    for (size_t i = 1; i < size; ++i) {
        points.at(i).r = Vector{points.at(i).x - points.front().x,
                                points.at(i).y - points.front().y};
    }
    sort(begin(points) + 1, end(points), compareByAngle);
    vector<Point> hull;
    hull.push_back(points.front());
    hull.push_back(points.at(1));
    for (size_t i = 2; i < size; ++i) {
        Point current = points.at(i);
        while (hull.size() >= 2 && vectorProduct(
                Vector{hull.at(hull.size() - 2).x - hull.back().x,
                       hull.at(hull.size() - 2).y - hull.back().y},
                Vector{current.x - hull.back().x,
                       current.y - hull.back().y}) <= 0.0) {
            hull.pop_back();
        }
        hull.push_back(current);
    }
    return hull;
}

long double getTriangleSquare(const Vector &lhs, const Vector &rhs) {
    return 1. / 2 * vectorProduct(lhs, rhs);
}

long double getSquare(const vector<Point> &polygon) {
    vector<Vector> vectors(polygon.size());
    size_t j = 0;
    for (auto &v : vectors) {
        v = Vector{polygon.at(j).x, polygon.at(j).y};
        ++j;
    }
    vectors.push_back(vectors.front());
    long double result = 0.0;
    for (size_t i = 1; i < vectors.size(); ++i) {
        result += getTriangleSquare(vectors.at(i - 1), vectors.at(i));
    }
    return abs(result);
}