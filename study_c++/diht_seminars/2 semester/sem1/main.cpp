#include <iostream>
#include "Student.h"

using namespace std;

int Student::amountGetYear = 0;

void printMarks(const Student &student) {
    const int *marks = student.getMarks();
    cout << student.getName() << "'s marks are: " << endl;
    for (int i = 0; i < Student::n; ++i) {
        cout << marks[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "Number of callings getYear = " << Student::amountGetYear << endl;

    int marks[Student::n];
    for (int i = 0; i < Student::n; ++i) {
        cin >> marks[i];
    }

    Student kolya;
    kolya.setName("Kolya");
    kolya.setMarks(marks);
    printMarks(kolya);
    cout << "Average mark is " << kolya.getAverage() << endl;

    cout << "Name of student is " << kolya.getName() << endl;
    kolya.setYear(3);
    cout << "Student's year is " << kolya.getYear() << endl;
    cout << "Number of callings getYear = " << kolya.amountGetYear << endl;

    Student vasya;
    vasya.setYear(2);
    cout << "Student's year is " << vasya.getYear() << endl;
    cout << "Number of callings getYear = " << vasya.amountGetYear << endl;
    return 0;
}