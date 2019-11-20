#include <iostream>

using namespace std;

struct Student {
    char name[100000];
    char surname[100000];
    double avg_grade;
};

int main() {
    int n;
    cin >> n;
    Student *students = new Student[n];
    double avg_1 = 0.0, avg_2 = 0.0, avg_3 = 0.0;
    for (int i = 0; i < n; ++i) {
        double math, phys, info;
        cin >> students[i].surname >> students[i].name >> math >> phys >> info;
        double avg = (math + phys + info) / 3.0;
        students[i].avg_grade = avg;
        if (avg >= avg_1) {
            avg_3 = avg_2;
            avg_2 = avg_1;
            avg_1 = avg;
        } else if (avg >= avg_2) {
            avg_3 = avg_2;
            avg_2 = avg;
        } else if (avg > avg_3) {
            avg_3 = avg;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (students[i].avg_grade >= avg_3) {
            cout << students[i].surname << ' ' << students[i].name << endl;
        }
    }
    delete[] students;
    return 0;
}