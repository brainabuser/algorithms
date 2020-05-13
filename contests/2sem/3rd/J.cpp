//
// Created by Vladimir on 13.05.2020.
//

#include <iostream>
#include <map>
#include <string>

using namespace std;

bool operator<(const string &lhs, const string &rhs);

struct DataBase {
    map<string, map<string, size_t>> dataBase;
    void print() {
        for (const auto &client: dataBase) {
            cout << client.first << ":" << endl;
            for (const auto &product : client.second) {
                cout << product.first << " " << product.second << endl;
            }
        }
    }
};

int main() {
    string name, prod;
    size_t num;
    DataBase db;
    while (cin >> name >> prod >> num) {
        db.dataBase[name][prod] += num;
    }
    db.print();
    return 0;
}

bool operator<(const string &lhs, const string &rhs) {
    return lexicographical_compare(lhs.begin(), lhs.end(),
                                   rhs.begin(), rhs.end()
    );
}