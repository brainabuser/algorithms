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
using std::swap;

class MatrixWrongSizeError : public std::length_error {
  public:
    MatrixWrongSizeError() : length_error("Matrices have different sizes") {}
};

class MatrixIndexError : public std::out_of_range {
  public:
    MatrixIndexError() : out_of_range("Index out of bound") {}
};

class MatrixIsDegenerateError : public std::exception {
};

// non-specified functions to get "zero" and "one" of type T

template<typename T>
T getZero() {
    return T(0);
}

template<typename T>
T getOne() {
    return T(1);
}

//=============== Matrix class ===============//

template<class T>
class Matrix {
  protected:
    int rowsCnt;
    int colsCnt;
    T **array;

    void clear();
    void allocate();

  public:
    Matrix(const int &m, const int &n);
    Matrix(const Matrix &old_matrix);
    ~Matrix();

    int getRowsNumber() const;
    int getColumnsNumber() const;
    Matrix getTransposed() const;
    Matrix &transpose();

    Matrix &operator=(const Matrix &that);
    Matrix operator+(const Matrix &that) const;
    Matrix &operator+=(const Matrix &that);
    Matrix operator-(const Matrix &that) const;
    Matrix &operator-=(const Matrix &that);
    Matrix operator*(const Matrix &that) const;
    Matrix &operator*=(const Matrix &that);
    Matrix &operator*=(const T &that);
    T operator()(const int &i, const int &j) const;
    T &operator()(const int &i, const int &j);
    template<class M>
    friend istream &operator>>(istream &is, Matrix<M> &matrix);
    template<class M>
    friend ostream &operator<<(ostream &os, const Matrix<M> &matrix);
    template<class M>
    friend Matrix operator*(const M &lhs, const Matrix<M> &rhs);
    template<class M>
    friend Matrix operator*(const Matrix<M> &lhs, const M &rhs);
};


//=============== SquareMatrix class ===============//

template<typename T>
class SquareMatrix : public Matrix<T> {
  private:
    mutable unsigned swapCnt = 0;

    bool isSwapRows(T **matrix, const int &index, const int &rowsCnt) const;
    SquareMatrix<T> getSubMatrix(const int &row, const int &col) const;
    T getMinor(bool isDeterminant, const int &row, const int &col) const;

  public:
    SquareMatrix(const int &size);
    SquareMatrix(const Matrix<T> &that);

    int getSize() const;
    T getDeterminant() const;
    T getTrace() const;
    SquareMatrix<T> getInverse() const;
    SquareMatrix<T> &invert();
    SquareMatrix<T> getTransposed() const;
    SquareMatrix<T> &transpose();

    SquareMatrix &operator=(const SquareMatrix &that);
    SquareMatrix operator+(const SquareMatrix &that) const;
    SquareMatrix &operator+=(const SquareMatrix &that);
    SquareMatrix operator-(const SquareMatrix &that) const;
    SquareMatrix &operator-=(const SquareMatrix &that);
    SquareMatrix operator*(const SquareMatrix &that) const;
    SquareMatrix &operator*=(const SquareMatrix &that);
    template<class M>
    friend SquareMatrix operator*(const M &lhs, const SquareMatrix<M> &rhs);
    template<class M>
    friend SquareMatrix operator*(const int &lhs, const SquareMatrix<M> &rhs);
    template<class M>
    friend SquareMatrix operator*(const SquareMatrix<M> &lhs, const M &rhs);
    template<class M>
    friend SquareMatrix operator*(const SquareMatrix<M> &lhs, const int &rhs);
};

class RationalDivisionByZero : public std::domain_error {
  public:
    RationalDivisionByZero() : domain_error("You`ve tried to divide by zero") {};
};

//================ class Rational ===============//

class Rational {
  private:
    int p;
    int q; // is maintained to be positive

    void reduce();

  public:
    Rational();
    Rational(const int &p, const int &q = 1);

    int getNumerator() const;
    int getDenominator() const;

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

//=================== main() ===============//

int main() {
    int m, n, p;
    Rational r;
    cin >> m >> n >> p >> r;

    Matrix<Rational> A(m, n);
    SquareMatrix<Rational> S(p);
    cin >> A >> S;

    try {
        cout << (A * S) * A.getTransposed() << endl;
    } catch (const MatrixWrongSizeError &) {
        cout << "A and S have not appropriate sizes for multiplication." << endl;
    }

    cout << (r * (S = S) * S).getSize() << endl;

    SquareMatrix<Rational> P(S);

    cout << (P * (S + S - 3 * P)).getDeterminant() << endl;

    const SquareMatrix<Rational> &rS = S;

    cout << rS.getSize() << ' ' << rS.getDeterminant() << ' ' << rS.getTrace() << endl;
    cout << (S = S) * (S + rS) << endl;
    cout << (S *= S) << endl;

    try {
        cout << rS.getInverse() << endl;
        cout << P.invert().getTransposed().getDeterminant() << endl;
        cout << P << endl;
    } catch (const MatrixIsDegenerateError &) {
        cout << "Cannot inverse matrix." << endl;
    }
    return 0;
}

template<class T>
istream &operator>>(istream &is, Matrix<T> &matrix) {
    for (int i = 0; i < matrix.rowsCnt; ++i) {
        for (int j = 0; j < matrix.colsCnt; ++j) {
            is >> matrix.array[i][j];
        }
    }
    return is;
}

template<class T>
ostream &operator<<(ostream &os, const Matrix<T> &matrix) {
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

template<class T>
Matrix<T> operator*(const T &lhs, const Matrix<T> &rhs) {
    Matrix<T> result = rhs;
    for (int i = 0; i < rhs.rowsCnt; ++i) {
        for (int j = 0; j < rhs.colsCnt; ++j) {
            result.array[i][j] *= lhs;
        }
    }
    return result;
}

template<class T>
Matrix<T> operator*(const Matrix<T> &lhs, const T &rhs) {
    return rhs * lhs;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &that) const {
    if (rowsCnt != that.rowsCnt || colsCnt != that.colsCnt) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> result(rowsCnt, colsCnt);
    for (int i = 0; i < rowsCnt; ++i) {
        for (int j = 0; j < colsCnt; ++j) {
            result.array[i][j] = array[i][j] - that.array[i][j];
        }
    }
    return result;
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

template<class T>
Matrix<T>::Matrix(const int &m, const int &n) : rowsCnt(m), colsCnt(n) {
    allocate();
    for (int i = 0; i < rowsCnt; ++i) {
        for (int j = 0; j < colsCnt; ++j) {
            array[i][j] = getZero<T>();
        }
    }
}

template<class T>
void Matrix<T>::clear() {
    for (int i = 0; i < rowsCnt; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

template<class T>
void Matrix<T>::allocate() {
    array = new T *[rowsCnt];
    for (int i = 0; i < rowsCnt; ++i) {
        array[i] = new T[colsCnt];
    }
}

template<class T>
int Matrix<T>::getRowsNumber() const {
    return rowsCnt;
}

template<class T>
int Matrix<T>::getColumnsNumber() const {
    return colsCnt;
}

template<class T>
Matrix<T>::~Matrix() {
    clear();
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T> &that) const {
    return SquareMatrix(static_cast<Matrix<T>>(*this) + that);
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator+=(const SquareMatrix<T> &that) {
    return SquareMatrix(static_cast<Matrix<T>>(*this) += that);
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator-(const SquareMatrix<T> &that) const {
    return SquareMatrix(static_cast<Matrix<T>>(*this) - that);

}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator-=(const SquareMatrix<T> &that) {
    return SquareMatrix(static_cast<Matrix<T>>(*this) -= that);
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const SquareMatrix<T> &that) const {
    const Matrix<T> &lhs = static_cast<Matrix<T>>(*this);
    const Matrix<T> &rhs = static_cast<Matrix<T>>(that);
    return SquareMatrix(lhs * rhs);
}

template<class T>
SquareMatrix<T> operator*(const SquareMatrix<T> &lhs, const T &rhs) {
    return rhs * lhs;
}

template<class T>
SquareMatrix<T> operator*(const int &lhs, const SquareMatrix<T> &rhs) {
    return T(lhs) * rhs;
}

template<class T>
SquareMatrix<T> operator*(const T &lhs, const SquareMatrix<T> &rhs) {
    const Matrix<T> &new_rhs = static_cast<Matrix<T>>(rhs);
    return SquareMatrix<T>(lhs * new_rhs);
}

template<class T>
SquareMatrix<T> operator*(const SquareMatrix<T> &lhs, const int &rhs) {
    return T(rhs) * lhs;
}

template<typename T>
T SquareMatrix<T>::getDeterminant() const {
    return getMinor(true, 0, 0);
}

template<typename T>
T SquareMatrix<T>::getTrace() const {
    T result = getZero<T>();
    for (int i = 0; i < this->rowsCnt; ++i) {
        result += this->array[i][i];
    }
    return result;
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::getSubMatrix(const int &row, const int &col) const {
    SquareMatrix<T> subM(getSize() - 1);
    int minorRow = 0, minorCol = 0;
    for (int i = 0; i < getSize(); ++i) {
        if (i == row) {
            continue;
        }
        for (int j = 0; j < getSize(); ++j) {
            if (j != col) {
                subM.array[minorRow][minorCol++] = this->array[i][j];
            }
        }
        ++minorRow;
        minorCol = 0;
    }
    return subM;
}

template<typename T>
T SquareMatrix<T>::getMinor(bool isDeterminant, const int &row, const int &col) const {
    SquareMatrix<T> copy = (isDeterminant) ? *this : getSubMatrix(row, col);
    for (int k = 0; k < copy.rowsCnt && copy.rowsCnt > 1; ++k) {
        if (copy.array[k][k] == getZero<T>() && k != copy.rowsCnt - 1) {
            if (!isSwapRows(copy.array, k, copy.rowsCnt)) {
                swapCnt = 0;
                return getZero<T>();
            }
        }
        for (int i = k + 1; i < copy.rowsCnt; ++i) {
            T temp = copy.array[i][k] / copy.array[k][k];
            for (int j = k; j < copy.colsCnt; ++j) {
                copy.array[i][j] = copy.array[i][j] - copy.array[k][j] * temp;
            }
        }
    }
    T result = (swapCnt % 2 != 0) ? -getOne<T>() : getOne<T>();
    for (int l = 0; l < copy.rowsCnt; ++l) {
        result *= copy.array[l][l];
    }
    swapCnt = 0;
    return result;
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::getInverse() const {
    T det = getDeterminant();
    if (det == getZero<T>()) {
        throw MatrixIsDegenerateError();
    }
    SquareMatrix<T> copy = *this;
    for (int i = 0; i < getSize(); ++i) {
        for (int j = 0; j < getSize(); ++j) {
            T minor = getMinor(false, i, j);
            copy.array[i][j] = ((i + j) % 2 == 0) ? minor : -minor;
        }
    }
    copy.transpose();
    T revDet = getOne<T>() / det;
    for (int i = 0; i < copy.rowsCnt; ++i) {
        for (int j = 0; j < copy.colsCnt; ++j) {
            copy(i, j) *= revDet;
        }
    }
    return copy;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::invert() {
    *this = getInverse();
    return *this;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator*=(const SquareMatrix<T> &that) {
    *this = *this * that;
    return *this;
}

template<typename T>
bool SquareMatrix<T>::isSwapRows(T **matrix, const int &index, const int &rowsCnt) const {
    ++swapCnt;
    for (int k = index + 1; k < rowsCnt; ++k) {
        if (matrix[k][index] != 0) {
            swap(matrix[index], matrix[k]);
            return true;
        }
    }
    return false;
}

template<typename T>
SquareMatrix<T>::SquareMatrix(const int &size) : Matrix<T>(size, size) {}

template<typename T>
SquareMatrix<T>::SquareMatrix(const Matrix<T> &that) : Matrix<T>(that) {}

template<typename T>
int SquareMatrix<T>::getSize() const {
    return this->rowsCnt;
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::operator=(const SquareMatrix &that) {
    if (this != &that) {
        Matrix<T>::operator=(that);
    }
    return *this;
}

template<typename T>
SquareMatrix<T> SquareMatrix<T>::getTransposed() const {
    return SquareMatrix(Matrix<T>::getTransposed());
}

template<typename T>
SquareMatrix<T> &SquareMatrix<T>::transpose() {
    *this = getTransposed();
    return *this;
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

Rational::Rational() : p(0), q(1) {}

int Rational::getNumerator() const {
    return p;
}

Rational::Rational(const int &p, const int &q) : p(p), q(q) {
    reduce();
}

int Rational::getDenominator() const {
    return q;
}
