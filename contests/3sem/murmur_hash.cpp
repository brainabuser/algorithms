//
// Created by vladimir on 23.09.2020.
//

#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

const uint64_t m = 0xc6a4a7935bd1e995;
const int r = 47;
const int seed = 2000000011;

class MurmurHash {
public:
    uint64_t operator()(string key) const;
};

uint64_t MurmurHash::operator()(string key) const {
    auto len = static_cast<int>(key.length());
    uint64_t h = seed ^(len * m);

    const auto *data = (const uint64_t *) static_cast<void *>(key.data());
    const uint64_t *end = data + (len / 8);

    while (data != end) {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const auto *data2 = (const unsigned char *) data;

    switch (len & 7) {
        case 7:
            h ^= uint64_t(data2[6]) << 48;
        case 6:
            h ^= uint64_t(data2[5]) << 40;
        case 5:
            h ^= uint64_t(data2[4]) << 32;
        case 4:
            h ^= uint64_t(data2[3]) << 24;
        case 3:
            h ^= uint64_t(data2[2]) << 16;
        case 2:
            h ^= uint64_t(data2[1]) << 8;
        case 1:
            h ^= uint64_t(data2[0]);
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

int main() {
    unordered_set<string, MurmurHash> stringSet;
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
            stringSet.insert(line);
        } else if (request == '-') {
            stringSet.erase(line);
        } else if (request == '?') {
            cout << ((stringSet.find(line) != stringSet.end()) ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}
