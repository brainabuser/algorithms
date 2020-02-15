//
// Created by Vladimir on 11.02.2020.
//

#include "Student.h"
#include <cstring>

void Student::setName(const char *newName) {
    strcpy(name, newName);
}

const char *Student::getName() const {
    return name;
}

void Student::setYear(const int currYear) {
    year = currYear;
}

int Student::getYear() const {
    return year;
}

const char *Student::getDepartment() const {
    return department;
}

void Student::setDepartment(const char *department) {
    strcpy(this->department, department);
}

void Student::setMarks(const int *marks) {
    for (int i = 0; i < n; ++i) {
        this->marks[i] = marks[i];
    }
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

double Student::getAverage() const {
    if (averageMark == 0) {
        averageMark = countAverage();
    }
    return averageMark;
}