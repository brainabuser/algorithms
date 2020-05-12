//
// Created by Vladimir on 10.05.2020.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

enum BankRequest {
    EDIT_ACCOUNT = 1, CLIENT_INFO
};

int main() {
    unordered_map<string, int> bank;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int request;
        cin >> request;
        auto r = (BankRequest) request;
        string client_name;
        switch (r) {
            case EDIT_ACCOUNT:
                int value;
                cin >> client_name >> value;
                bank[client_name] += value;
                break;
            case CLIENT_INFO:
                cin >> client_name;
                try {
                    cout << bank.at(client_name) << endl;
                } catch (out_of_range &e) {
                    cout << "ERROR" << endl;
                }
                break;
        }
    }
    return 0;
}