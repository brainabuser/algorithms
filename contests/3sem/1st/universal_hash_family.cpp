//
// Created by vladimir on 22.09.2020
//

#include <iostream>
#include <random>
#include <unordered_set>

using namespace std;

const int kPrimeNumber = 2000000011;

class CustomHash {
public:
    CustomHash() {
        mt19937 generator;
        uniform_int_distribution<int> first_distribution(1, kPrimeNumber - 1);
        this->first_parameter_ = first_distribution(generator);
        uniform_int_distribution<int> second_distribution(0, kPrimeNumber - 1);
        this->second_parameter_ = second_distribution(generator);
    }

    size_t operator()(int number) const;

private:
    int first_parameter_, second_parameter_;
};

size_t CustomHash::operator()(int number) const {
    return (first_parameter_ * number + second_parameter_);
}

int main() {
    unordered_set<int, CustomHash> numSet;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int request_number;
    cin >> request_number;
    while ((request_number--)) {
        char request;
        cin >> request;
        int num;
        cin >> num;
        if (request == '+') {
            numSet.insert(num);
        } else if (request == '-') {
            numSet.erase(num);
        } else if (request == '?') {
            cout << ((numSet.find(num) != numSet.end()) ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}
