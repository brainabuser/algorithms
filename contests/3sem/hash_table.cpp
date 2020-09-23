//
// Created by vladimir on 22.09.2020.
//

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <list>

using namespace std;

class UnorderedSet {
private:
    vector<list<string>> buf;
    double load_factor;
    double max_load_factor = 1.0;
    int n_elem = 0;

public:
    UnorderedSet() : buf(100) {}

    void rehash(const size_t &size);

    void Insert(const string &key);

    void Erase(const string &key);

    bool Find(const string &key) const;
};

void UnorderedSet::rehash(const size_t &size) {
    vector<list<string>> temp_buf(size);
    n_elem = 0;
    for (const auto &item: buf) {
        for (const auto &key: item) {
            auto id = hash<string>{}(key) % temp_buf.capacity();
            ++n_elem;
            temp_buf[id].push_back(key);
        }
    }
    load_factor = static_cast<double>(n_elem) / temp_buf.capacity();
    buf = temp_buf;
}

void UnorderedSet::Insert(const string &key) {
    if (load_factor == max_load_factor) {
        rehash(buf.capacity() * 2);
    }
    auto id = hash<string>{}(key) % buf.capacity();
    buf[id].push_back(key);
    ++n_elem;
    load_factor = static_cast<double>(n_elem) / buf.capacity();
}

void UnorderedSet::Erase(const string &key) {
    auto id = hash<string>{}(key) % buf.capacity();
    for (const auto &elem: buf[id]) {
        if (elem == key) {
            buf[id].remove(elem);
            --n_elem;
            load_factor = static_cast<double>(n_elem) / buf.capacity();
            return;
        }
    }
}

bool UnorderedSet::Find(const string &key) const {
    auto id = hash<string>{}(key) % buf.capacity();
    for (const auto &elem: buf[id]) {
        if (elem == key) {
            return true;
        }
    }
    return false;
}

int main() {
    UnorderedSet stringSet;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    char request;
    while (cin >> request) {
        if (request == '#') {
            break;
        }
        string line;
        cin >> line;
        if (request == '+') {
            stringSet.Insert(line);
        } else if (request == '-') {
            stringSet.Erase(line);
        } else if (request == '?') {
            cout << ((stringSet.Find(line)) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}