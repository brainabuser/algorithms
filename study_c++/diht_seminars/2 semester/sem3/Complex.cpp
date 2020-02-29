#include <iostream>

using namespace std;

class Complex {
    double re, im;
  public:
    Complex() {
        re = im = 0.0;
    }
    Complex(const Complex &a) = default;
    Complex(double a, double b) : re(a), im(b) {}
    ~Complex() = default;
    Complex &operator=(const Complex &) = default;
    friend Complex operator+(const Complex &a, const Complex &b);
    Complex &operator+=(const Complex &that);
    Complex &operator++();
    Complex operator++(int);
    operator double() const;
    friend istream &operator>>(istream &is, Complex &c);
    friend ostream &operator<<(ostream &os, const Complex &c);
};

istream &operator>>(istream &is, Complex &c) {
    is >> c.re >> c.im;
    return is;
}
ostream &operator<<(ostream &os, const Complex &c) {
    os << c.re << '/' << c.im;
    return os;
}
Complex operator+(const Complex &a, const Complex &b) {
    return Complex(a.re + b.re, a.im + b.im);
}
Complex &Complex::operator+=(const Complex &that) {
    *this = *this + that;
    return *this;
}
Complex &Complex::operator++() {
    ++this->re;
    return *this;
}
Complex Complex::operator++(int) {
    Complex copy(*this);
    ++this->re;
    return copy;
}
Complex::operator double() const {
    return this->re;
}


int main() {
    Complex d(2, 5.7);
    Complex a, b;
    cin >> a >> b;
    cout << a << ' ' << b << endl;
    cout << ++a << endl;
    cout << "test" << endl;
    cout << b++ << endl;
    cout << b << endl;
    cout << double(b) << endl;
    cout << a + b << endl;
    Complex c = b;
    c += b;
    cout << c << ' ' << b << endl;
    return 0;
}