//
// Created by Vladimir on 25.03.2020.
//

#include <iostream>
#include <cstdlib>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class MatrixWrongSizeError : public std::length_error {
  public:
    MatrixWrongSizeError() : length_error("Matrices have different sizes")
};

class MatrixIndexError : public std::out_of_range {
  public:
    MatrixIndexError() : out_of_range("Index out of bound")
};

// non-specified functions to get "zero" of type T

template<typename T>
T getZero() {
    return T(0);
}

template<class T>
class Matrix {
  private:
    int rowsCnt;
    int colsCnt;
    T **array;

    void clear() {
        for (int i = 0; i < rowsCnt; ++i) {
            delete[] array[i];
        }
        delete[] array;
    }

    void allocate() {
        array = new T *[rowsCnt];
        for (int i = 0; i < rowsCnt; ++i) {
            array[i] = new T[colsCnt];
        }
    }

  public:
    Matrix(const int &m, const int &n) : rowsCnt(m), colsCnt(n) {
        allocate();
        for (int i = 0; i < rowsCnt; ++i) {
            for (int j = 0; j < colsCnt; ++j) {
                array[i][j] = getZero<T>();
            }
        }
    }

    Matrix(const Matrix &old_matrix);

    int getRowsNumber() const {
        return rowsCnt;
    }

    int getColumnsNumber() const {
        return colsCnt;
    }

    Matrix &operator=(const Matrix &that);

    ~Matrix() {
        clear();
    }

    template<class M>
    friend istream &operator>>(istream &is, Matrix<M> &matrix);
    template<class M>
    friend ostream &operator<<(ostream &os, const Matrix<M> &matrix);
    Matrix<T> operator+(const Matrix<T> &that) const;
    Matrix<T> &operator+=(const Matrix<T> &that);
    Matrix<T> operator-(const Matrix<T> &that) const;
    Matrix<T> &operator-=(const Matrix<T> &that);
    Matrix<T> operator*(const Matrix<T> &that) const;
    Matrix<T> &operator*=(const Matrix<T> &that);
    template<class N>
    friend Matrix<N> operator*(const N &lhs, const Matrix<N> &rhs);
    template<class N>
    friend Matrix<N> operator*(const Matrix<N> &lhs, const N &rhs);
    Matrix<T> &operator*=(const T &that);
    Matrix<T> getTransposed() const;
    Matrix<T> &transpose();
    T operator()(const int &i, const int &j) const;
    T &operator()(const int &i, const int &j);
};

class RationalDivisionByZero : public std::domain_error {
  public:
    RationalDivisionByZero() : domain_error("You`ve tried to divide by zero")
};


class Rational {
  private:
    int p;
    unsigned int q; // is maintained to be positive

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
    friend istream &operator>>(istream &is, Rational &r);
    friend ostream &operator<<(ostream &os, const Rational &r);
};

int main() {
    int m, n, p, q;
    cin >> m >> n >> p >> q;

    Matrix<int> A(m, n), B(p, q);
    cin >> A >> B;

    A = A;
    try {
        cout << A + B * 2 - m * A << endl;
        cout << (A -= B += A *= 2) << endl;
        cout << (((A -= B) += A) *= 2) << endl;
    } catch (const MatrixWrongSizeError &) {
        cout << "A and B are of different size." << endl;
    }
    B = A;

    {
        Matrix<int> AA(A);
        Matrix<int> AAA(1, 1);
        AAA = A;
        cout << AA << endl;
        cout << (AAA += Matrix<int>(m, n)) + B << endl;
    }

    Rational r;
    cin >> r;
    Matrix<Rational> C(m, n), D(p, q);
    cin >> C >> D;
    try {
        cout << C * D << endl;
        cout << (C *= D) << endl;
        cout << C << endl;
    } catch (const MatrixWrongSizeError &) {
        cout << "C and D have not appropriate sizes for multiplication." << endl;
    }
    cout << C.getTransposed() * (r * C) << endl;
    cout << C.transpose() << endl;
    try {
        (C(0, 0) *= 6) /= 3;
        cout << C(0, 0) << endl;
        cout << C(m, m) << endl;
    } catch (const MatrixIndexError &) {
        cout << "Index out of range." << endl;
    }

    {
        const Matrix<Rational> &rC = C;
        cout << rC << endl;
        cout << rC.getRowsNumber() << ' ' << rC.getColumnsNumber() << ' ' << rC(0, 0) << endl;
        cout << (C = C) * (Rational(1, 2) * rC).getTransposed() << endl;
    }
    return 0;
}

template<class M>
istream &operator>>(istream &is, Matrix<M> &matrix) {
    for (int i = 0; i < matrix.rowsCnt; ++i) {
        for (int j = 0; j < matrix.colsCnt; ++j) {
            is >> matrix.array[i][j];
        }
    }
    return is;
}

template<class M>
ostream &operator<<(ostream &os, const Matrix<M> &matrix) {
    for (int i = 0; i < matrix.rowsCnt; ++i) {
        for (int j = 0; j < matrix.colsCnt; ++j) {
            os << matrix.array[i][j] << ' ';
        }
        os << endl;
    }
    return os;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &that) const {
    if (rowsCnt != that.rowsCnt || colsCnt != that.colsCnt) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> result(rowsCnt, colsCnt);
    for (int i = 0; i < rowsCnt; ++i) {
        for (int j = 0; j < colsCnt; ++j) {
            result.array[i][j] = array[i][j] + that.array[i][j];
        }
    }
    return result;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &that) const {
    if (colsCnt != that.rowsCnt) {
        throw MatrixWrongSizeError();
    }
    Matrix result(rowsCnt, that.colsCnt);
    for (int i = 0; i < rowsCnt; ++i) {
        for (int j = 0; j < that.colsCnt; ++j) {
            for (int k = 0; k < colsCnt; ++k) {
                result.array[i][j] += array[i][k] * that.array[k][j];
            }
        }
    }
    return result;
}

template<class N>
Matrix<N> operator*(const N &lhs, const Matrix<N> &rhs) {
    Matrix<N> result = rhs;
    for (int i = 0; i < rhs.rowsCnt; ++i) {
        for (int j = 0; j < rhs.colsCnt; ++j) {
            result.array[i][j] *= lhs;
        }
    }
    return result;
}

template<class N>
Matrix<N> operator*(const Matrix<N> &lhs, const N &rhs) {
    return rhs * lhs;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &that) const {
    return *this + T(-1) * that;
}

template<class T>
Matrix<T>::Matrix(const Matrix &old_matrix) {
    if (old_matrix.array != nullptr) {
        rowsCnt = old_matrix.rowsCnt;
        colsCnt = old_matrix.colsCnt;
        allocate();
        for (int i = 0; i < rowsCnt; ++i) {
            for (int j = 0; j < colsCnt; ++j) {
                array[i][j] = old_matrix.array[i][j];
            }
        }
    } else {
        rowsCnt = colsCnt = 0;
        array = nullptr;
    }
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix &that) {
    clear();
    if (that.array == nullptr) {
        rowsCnt = colsCnt = 0;
        array = nullptr;
    } else if (this != &that) {
        rowsCnt = that.rowsCnt;
        colsCnt = that.colsCnt;
        allocate();
        for (int i = 0; i < rowsCnt; ++i) {
            for (int j = 0; j < colsCnt; ++j) {
                array[i][j] = that.array[i][j];
            }
        }
    }
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &that) {
    *this = *this + that;
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &that) {
    *this = *this - that;
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &that) {
    *this = *this * that;
    return *this;
}

template<class T>
Matrix<T> Matrix<T>::getTransposed() const {
    Matrix<T> result(colsCnt, rowsCnt);
    for (int i = 0; i < result.rowsCnt; ++i) {
        for (int j = 0; j < result.colsCnt; ++j) {
            result.array[i][j] = array[j][i];
        }
    }
    return result;
}

template<class T>
Matrix<T> &Matrix<T>::transpose() {
    *this = getTransposed();
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(const T &that) {
    *this = *this * that;
    return *this;
}

template<class T>
T &Matrix<T>::operator()(const int &i, const int &j) {
    if ((i < 0 || i >= rowsCnt) || (j < 0 || j >= colsCnt)) {
        throw MatrixIndexError();
    }
    return array[i][j];
}

template<class T>
T Matrix<T>::operator()(const int &i, const int &j) const {
    if ((i < 0 || i >= rowsCnt) || (j < 0 || j >= colsCnt)) {
        throw MatrixIndexError();
    }
    return array[i][j];
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

istream &operator>>(istream &is, Rational &r) {
    int p, q;
    is >> p;
    if (is.peek() == '/') {
        is.ignore(1);
        is >> q;
        r = Rational(p, q);
    } else {
        r = Rational(p, 1);
    }
    return is;
}

ostream &operator<<(ostream &os, const Rational &r) {
    if (r.getDenominator() == 1) {
        os << r.getNumerator();
    } else {
        os << r.getNumerator() << '/' << r.getDenominator();
    }
    return os;
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
    int denominator = q;
    while (numerator > 0 && denominator > 0) {
        if (numerator > denominator) {
            numerator %= denominator;
        } else {
            denominator %= numerator;
        }
    }
    int gcd = numerator + denominator;
    numerator = abs(p);
    denominator = q;
    int old_q = q;
    q = denominator / gcd;
    if ((p < 0 && old_q > 0) || (p > 0 && old_q < 0)) {
        p = -numerator / gcd;
    } else {
        p = numerator / gcd;
    }
}
