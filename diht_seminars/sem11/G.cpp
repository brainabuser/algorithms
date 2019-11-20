#include <iostream>

#include <iomanip>

#include <cmath>

using namespace std;

struct Student {
    char name[255] = "";
    char surname[255] = "";
    double math = 0.0, physics = 0.0, informatics = 0.0;
};

int main() {
    int n;
    cin >> n;
    Student *students = new Student[n];
    cin.ignore(1);
    Student middle_grade;
    for (int i = 0; i < n; ++i) {
        cin.getline(students[i].name, 255, ' ');
        cin.getline(students[i].surname, 255, ' ');
        cin >> students[i].math >> students[i].physics >> students[i].informatics;

    }
    delete[] students;
    return 0;
}