#include <iostream>

using namespace std;

struct Student {
    char name[100000];
    char surname[100000];
    int math, physics, informatics;
};

int main() {
    int n;
    cin >> n;
    Student *students = new Student[n];
    for (int i = 0; i < n; ++i) {
        cin.ignore(1);
        cin.getline(students[i].surname, 100000, ' ');
        cin.getline(students[i].name, 100000, ' ');
        cin >> students[i].math >> students[i].physics >> students[i].informatics;
    }
    for (int i = 0; i < n; ++i) {
        if (students[i].math >= 4 && students[i].physics >= 4 && students[i].informatics >= 4) {
            cout << students[i].surname << ' ' << students[i].name << endl;
        }
    }
    delete[] students;
    return 0;
}