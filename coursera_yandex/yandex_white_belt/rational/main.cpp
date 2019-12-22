#include <iostream>
#include <sstream>
#include <cmath>
#include <map>
#include <vector>
#include <exception>

using namespace std;

class Rational {
public:
    Rational(){
        q = 1;
        p = 0;
    }
    Rational(int numerator, int denominator) {
        if(denominator == 0){
            throw invalid_argument("Invalid argument");
        }
        int n = abs(numerator);
        int d = abs(denominator);
        while (n > 0 && d > 0) {
            if (n > d) {
                n %= d;
            } else {
                d %= n;
            }
        }
        int result = n + d;
        n = abs(numerator);
        d = abs(denominator);
        q = d / result;
        if((numerator < 0 && denominator > 0) || (numerator > 0 && denominator < 0)){
            p = -n / result;
        }else {
            p = n / result;
        }
    }
    int Numerator() const {
        return p;
    }
    int Denominator() const {
        return q;
    }

private:
    int p;
    int q;
};

bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    return Rational({lhs.Numerator() * rhs.Denominator() + lhs.Denominator() * rhs.Numerator(),
                     lhs.Denominator() * rhs.Denominator()});
}

Rational operator-(const Rational& lhs, const Rational& rhs){
    return Rational({lhs.Numerator() * rhs.Denominator() - lhs.Denominator() * rhs.Numerator(),
                     lhs.Denominator() * rhs.Denominator()});
}

Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational({lhs.Numerator() * rhs.Numerator(),
                     lhs.Denominator() * rhs.Denominator()});
}

Rational operator/(const Rational& lhs, const Rational& rhs){
    if(rhs.Numerator() == 0){
        throw domain_error("Division by zero");
    }
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

ostream& operator<<(ostream& stream, const Rational& r){
    stream << r.Numerator() << '/' << r.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& r){
    if(stream.tellg() != -1){
        int p, q;
        stream >> p;
        if(stream.peek() != '/'){
            throw invalid_argument("Invalid argument");
        }
        stream.ignore(1);
        stream >> q;
        r = Rational(p, q);
    }
    return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs){
    if(lhs.Denominator() == rhs.Denominator()){
        return lhs.Numerator() < rhs.Numerator();
    }else{
        return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
    }
}


char GetOperation(stringstream& stream){
    stream.ignore(1);
    char operation;
    stream >> operation;
    stream.ignore(1);
    return operation;
}

Rational GetResult(const Rational& first_number, const char& operation, const Rational& second_number){
    if(operation == '+'){
        return first_number + second_number;
    }else if (operation == '-') {
        return first_number - second_number;
    }else if (operation == '*') {
        return first_number * second_number;
    }else{
        return first_number / second_number;
    }
}

int main() {
    string line;
    getline(cin, line);
    stringstream stream(line);
    Rational first_number;
    try {
        stream >> first_number;
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
        return 1;
    }
    char operation = GetOperation(stream);
    Rational second_number;
    try {
        stream >> second_number;
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
        return 2;
    }
    Rational result;
    try {
        result = GetResult(first_number, operation, second_number);
    } catch (domain_error& e) {
        cout << e.what() << endl;
        return 3;
    }
    cout << result << endl;
    return 0;
}
