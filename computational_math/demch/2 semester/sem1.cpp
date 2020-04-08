#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

int gcdNotMethod(int x, int y);

class Rational {
  private:
    int p;
    int q;
    int gcd(int x, int y);
    void reduceFraction();

  public:
    Rational(int p, int q) : p(p), q(q) {
        this->reduceFraction();
    }

    Rational(int p) : p(p), q(1) {}

    Rational() : p(0), q(1) {}

    int getNumerator() const {
        return p;
    }

    int getDenominator() const {
        return q;
    }

    friend std::istream &operator>>(std::istream &is, Rational &fraction);
    friend std::ostream &operator<<(std::ostream &os, const Rational &fraction);
    Rational operator+(const Rational &that);
    Rational operator-(const Rational &that);
    Rational operator*(const Rational &that);
    Rational operator/(const Rational &that);
    Rational operator-();
    Rational operator+();
    Rational &operator++();
    friend bool operator<(const Rational &rational1, const Rational &rational2);
    friend bool operator>(const Rational &rational1, const Rational &rational2);
    friend bool operator<=(const Rational &rational1, const Rational &rational2);
    friend bool operator>=(const Rational &rational1, const Rational &rational2);
    friend bool operator==(const Rational &rational1, const Rational &rational2);
    friend bool operator!=(const Rational &rational1, const Rational &rational2);
};

int main() {
    int p, q;
    cin >> p >> q;
    Rational r(p, q);
    cout << r.getNumerator() << " " << r.getDenominator();
    Rational rac1, rac2;
    cin >> rac1 >> rac2;
    cout << rac1 << endl;
    cout << rac1 * rac2 << endl;
    return 0;
}

Rational Rational::operator+() {
    return Rational(this->p, this->q);
}

Rational Rational::operator-() {
    Rational opposite((-1) * this->p, this->q);
    return opposite;
}
Rational Rational::operator/(const Rational &that) {
    if (that == 0) {
        cout << "ITS A DIVISION BY ZERO STOP IT" << endl;
    } else {
        Rational division(this->p * that.q, this->q * that.p);
        return division;
    }
    return 0;
}

Rational Rational::operator*(const Rational &that) {
    Rational multiplication(this->p * that.p, this->q * that.q);
    return multiplication;
}

Rational Rational::operator-(const Rational &that) {
    Rational residual(this->p * that.q - this->q * that.p, this->q * that.q);
    return residual;
}

Rational Rational::operator+(const Rational &that) {
    Rational sum(this->p * that.q + this->q * that.p, this->q * that.q);
    return sum;

}

bool operator<(const Rational &rational1,
               const Rational &rational2) { //т.к. мы изначально положили, что в знаменателе натуральное, то они положительные  и gcd тоже, но потом проверь
    int commonDenominator = rational1.q * rational2.q / gcdNotMethod(rational1.q, rational2.q);
    return rational1.p * (commonDenominator / rational1.q) <
           rational2.p * (commonDenominator / rational2.q); // заметим, что общий знаменатель можно и не считать
}

bool operator>(const Rational &rational1, const Rational &rational2) {
    return rational1.p * rational2.q > rational1.q * rational2.p;
}

bool operator<=(const Rational &rational1, const Rational &rational2) {
    return rational1.p * rational2.q <= rational1.q * rational2.p;
}

bool operator>=(const Rational &rational1, const Rational &rational2) {
    return rational1.p * rational2.q >= rational1.q * rational2.p;
}

bool operator==(const Rational &rational1, const Rational &rational2) {
    return rational1.p * rational2.q == rational1.q * rational2.p;
}

bool operator!=(const Rational &rational1, const Rational &rational2) {
    return rational1.p * rational2.q != rational1.q * rational2.p;
}

std::ostream &operator<<(std::ostream &os, const Rational &fraction) {  //потом надо добавить астные случаи, не забудь
    os << fraction.p << "/" << fraction.q;
    return os;
}

std::istream &operator>>(std::istream &is, Rational &fraction) {
    int x, y;
    is >> x >> y;
    fraction.p = x;
    fraction.q = y;
    fraction.reduceFraction();
    return is;
}

void Rational::reduceFraction() {
    int cutNumber = gcd(abs(this->q), abs(this->p));
    if (p == 0) {
        q = 1;
    }
    if (q < 0) {
        q *= -1;
        p *= -1;
    }
    q /= cutNumber;
    p /= cutNumber;
}

int gcdNotMethod(int x, int y) {
    while (y != 0) {
        int c = x % y;
        x = y;
        y = c;
    }
    return x;
}

int Rational::gcd(int x, int y) {
    while (y != 0) {
        int c = x % y;
        x = y;
        y = c;
    }
    return x;
}