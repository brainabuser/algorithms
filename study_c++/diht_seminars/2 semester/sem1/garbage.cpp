#include <iostream>

#include <cstring>

using namespace std;

class Student {
  public:
    const static int n = 3;
    static int amountGetYear;

  private:
    char name[40];
    int year;
    char department[10];
    int marks[n];
    const char university[5] = "MIPT";

    mutable double averageMark = 0;//может меняться в константных методах

  public:
    double countAverage() const;

    double getAverage() const {
        if (averageMark == 0) {
            averageMark = countAverage();
        }
        return averageMark;
    }

    int getYear() const {
        ++amountGetYear;
        return year;
    }

    static void increaseAmount() {
        ++amountGetYear;
        //cout << year; нельзя т.к. "year" это не статическая переменная
    }

    void setYear(const int currYear) {
        year = currYear;
    }

    const char *getName() const {
        return name;
    }

    void setName(const char *newName);

    const char *getDepartment() const;

    void setDepartment(const char *department);

    const int *getMarks() const;

    void setMarks(const int *marks);
};

int Student::amountGetYear = 0;

void printMarks(const Student &student) {
    const int *marks = student.getMarks();
    cout << student.getName() << "`s marks are:" << endl;
    for (int i = 0; i < Student::n; ++i) {
        cout << marks[i] << ' ';
    }
    cout << endl;
}

int main() {
    cout << "Number of callings getYear " << Student::amountGetYear << endl;
    int marks[Student::n];
    for (int i = 0; i < Student::n; ++i) {
        cin >> marks[i];
    }
    Student kolya;
    kolya.setName("Kolya");
    kolya.setMarks(marks);
    printMarks(kolya);
    cout << "Average mark is " << kolya.getAverage() << endl;
    kolya.setYear(3);
    cout << "Student`s year is " << kolya.getYear() << endl;
    cout << "Name of student is " << kolya.getName() << endl;
    cout << "Number of callings getYear " << Student::amountGetYear << endl;

    Student vasya;
    vasya.setYear(2);
    vasya.setName("Vasya");
    cout << "Student`s year is " << vasya.getYear() << endl;
    cout << "Name of student is " << vasya.getName() << endl;
    cout << "Number of callings getYear " << Student::amountGetYear << endl;
    return 0;
}

void Student::setName(const char *newName) {
    strcpy(name, newName);
}

const char *Student::getDepartment() const {
    return department;
}

void Student::setDepartment(const char *department) {
    strcpy(this->department, department);
}

const int *Student::getMarks() const {
    return marks;
}

double Student::countAverage() const {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += marks[i];
    }
    return sum / n;
}

void Student::setMarks(const int *marks) {
    for (int i = 0; i < n; ++i) {
        this->marks[i] = marks[i];
    }
}
