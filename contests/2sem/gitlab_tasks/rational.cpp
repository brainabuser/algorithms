//
// Created by Vladimir on 22.03.2020.
//

#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

class RationalDivisionByZero {
};


class Rational {
  private:
    int p;
    int q; // is maintained to be positive

    void reduce();

  public:
    Rational() : p(0), q(1) {}
    Rational(const int &p, const int &q = 1) : p(p), q(q) {
        reduce();
    }

    int getNumerator() const {
        return p;
    }
    int getDenominator() const {
        return q;
    }

    Rational operator-() const;
    Rational operator+() const;
    Rational &operator++();
    Rational operator++(int);
    Rational &operator--();
    Rational operator--(int);
    Rational &operator/=(const Rational &that);
    Rational &operator+=(const Rational &that);
    Rational &operator-=(const Rational &that);
    Rational &operator*=(const Rational &that);
};

istream &operator>>(istream &stream, Rational &r) {
    int p, q;
    stream >> p;
    if (stream.peek() == '/') {
        stream.ignore(1);
        stream >> q;
        r = Rational(p, q);
    } else {
        r = Rational(p, 1);
    }
    return stream;
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
    return Rational(lhs.getNumerator() * rhs.getNumerator(),
                     lhs.getDenominator() * rhs.getDenominator());
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    if (rhs.getNumerator() == 0) {
        throw RationalDivisionByZero();
    }
    return lhs * Rational(rhs.getDenominator(), rhs.getNumerator());
}

ostream &operator<<(ostream &stream, const Rational &r) {
    if (r.getDenominator() == 1) {
        stream << r.getNumerator();
    } else {
        stream << r.getNumerator() << '/' << r.getDenominator();
    }
    return stream;
}

bool operator<(const Rational &lhs, const Rational &rhs) {
    if (lhs.getDenominator() == rhs.getDenominator()) {
        return lhs.getNumerator() < rhs.getNumerator();
    } else {
        return lhs.getNumerator() * rhs.getDenominator() < rhs.getNumerator() * lhs.getDenominator();
    }
}

bool operator==(const Rational &lhs, const Rational &rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
}

bool operator!=(const Rational &lhs, const Rational &rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Rational &lhs, const Rational &rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Rational &lhs, const Rational &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Rational &lhs, const Rational &rhs) {
    return (lhs > rhs) || (lhs == rhs);
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return Rational({lhs.getNumerator() * rhs.getDenominator() + lhs.getDenominator() * rhs.getNumerator(),
                     lhs.getDenominator() * rhs.getDenominator()});
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return -rhs + lhs;
}

int main() {
    int a;
    cin >> a;

    int p, q;
    cin >> p >> q;
    const Rational rc(p, q); // q != 0 is guaranteed by author of tests
    cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

    Rational r1, r2;
    cin >> r1 >> r2;

    cout << r1 << endl;
    cout << r2 << endl;

    try {
        cout << 1 / r1 << endl;
    } catch (const RationalDivisionByZero &ex) {
        cout << "Cannot get reciprocal of r1." << endl;
    }

    try {
        cout << rc / r2 << endl;
    } catch (const RationalDivisionByZero &ex) {
        cout << "Cannot divide by r2." << endl;
    }

    cout << (r1 < r2) << endl;
    cout << (r1 <= r2) << endl;
    cout << (r1 > r2) << endl;
    cout << (r1 >= r2) << endl;
    cout << (r1 == r2) << endl;
    cout << (r1 != r2) << endl;

    cout << (r1 < a) << endl;
    cout << (r1 <= a) << endl;
    cout << (r1 > a) << endl;
    cout << (r1 >= a) << endl;
    cout << (r1 == a) << endl;
    cout << (r1 != a) << endl;

    cout << (a < r2) << endl;
    cout << (a <= r2) << endl;
    cout << (a > r2) << endl;
    cout << (a >= r2) << endl;
    cout << (a == r2) << endl;
    cout << (a != r2) << endl;

    cout << rc + a << endl
         << a + rc << endl
         << -rc * r1 << endl
         << (+r1 - r2 * rc) * a << endl;

    cout << ++r1 << endl;
    cout << r1 << endl;
    cout << r1++ << endl;
    cout << r1 << endl;
    cout << --r1 << endl;
    cout << r1 << endl;
    cout << r1-- << endl;
    cout << r1 << endl;
    cout << ++ ++r1 << endl;
    cout << r1 << endl;

    cout << ((((r1 += r2) /= Rational(-5, 3)) -= rc) *= a) << endl;
    cout << (r1 += r2 /= 3) << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    return 0;
}

Rational Rational::operator-() const {
    return Rational(-p, q);
}

Rational Rational::operator+() const {
    return Rational(p, q);
}

Rational &Rational::operator++() {
    *this = Rational(p + q, q);
    return *this;
}

Rational Rational::operator++(int) {
    Rational copy = *this;
    ++(*this);
    return copy;
}

Rational &Rational::operator--() {
    *this = Rational(p - q, q);
    return *this;;
}

Rational Rational::operator--(int) {
    Rational copy = *this;
    --(*this);
    return copy;
}

Rational &Rational::operator/=(const Rational &that) {
    *this = *this / that;
    return *this;
}

Rational &Rational::operator*=(const Rational &that) {
    *this = *this * that;
    return *this;
}

Rational &Rational::operator+=(const Rational &that) {
    *this = *this + that;
    return *this;
}

Rational &Rational::operator-=(const Rational &that) {
    *this = *this - that;
    return *this;
}

void Rational::reduce() {
    int numerator = abs(p);
    int denominator = abs(q);
    while (numerator > 0 && denominator > 0) {
        if (numerator > denominator) {
            numerator %= denominator;
        } else {
            denominator %= numerator;
        }
    }
    int gcd = numerator + denominator;
    numerator = abs(p);
    denominator = abs(q);
    int old_q = q;
    q = denominator / gcd;
    if ((p < 0 && old_q > 0) || (p > 0 && old_q < 0)) {
        p = -numerator / gcd;
    } else {
        p = numerator / gcd;
    }
}