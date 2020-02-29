#include <iostream>
#include <cstring>

using namespace std;

class MyString {
    char *data;
  public:
    MyString() : data(nullptr) {}
    MyString(const MyString &line) {
        data = new char[strlen(line.data)];
        strcpy(data, line.data);
    }
    MyString(const char *line) {
        this->data = new char[strlen(line)];
        strcpy(this->data, line);
    }
    ~MyString() {
        delete[] this->data;
    }
    MyString &operator=(const MyString &line) {
        if (this == &line) {
            return *this;
        }
        delete this->data;
        data = new char[strlen(line.data)];
        strcpy(this->data, line.data);
        return *this;
    }
    MyString operator+(const MyString &that);
    friend istream &operator>>(istream &is, MyString &s);
    friend ostream &operator<<(ostream &os, const MyString &s);
    friend MyString operator+(const char *a, const MyString &s);
};

MyString MyString::operator+(const MyString &that) {
    return this->data + that;
}
istream &operator>>(istream &is, MyString &s) {
    is >> s.data;
    return is;
}
ostream &operator<<(ostream &os, const MyString &s) {
    os << s.data;
    return os;
}
MyString operator+(const char *a, const MyString &s) {
    char *line = new char[strlen(a) + strlen(s.data) - 1]{0};
    strcat(strcat(line, a), s.data);
    MyString string(line);
    delete[] line;
    return string;
}

int main() {
    MyString s1("Sasha"), s2("Masha"), s3("Dasha");
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s1 + s2 + s3 << endl;
    char s5[] = "pupa";
    MyString s6("lupa");
    MyString s7 = s5 + s6;
    cout << s7 << endl;
    return 0;
}