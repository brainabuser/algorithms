//
// Created by Vladimir on 15.12.2020.
//

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> get_cubes_count(vector<int> &cubes, const int &color_size);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    size_t cubes_size, color_size;
    cin >> cubes_size >> color_size;
    vector<int> cubes(cubes_size);
    for (auto &cube: cubes) {
        cin >> cube;
    }
    for (const auto &item : get_cubes_count(cubes, color_size)) {
        cout << item << ' ';
    }
    return 0;
}

vector<int> get_z_func(const vector<int> &line) {
    vector<int> z(line.size(), 0);
    int left, right;
    left = right = 0;
    for (size_t i = 1; i < line.size(); ++i) {
        if (right > i) {
            z[i] = min(z[i - left], right - static_cast<int>(i));
        }
        while (z[i] + i < z.size() && line[z[i]] == line[z[i] + i]) {
            ++z[i];
        }
        if (z[i]  + i> right) {
            right = z[i] + i;
            left = i;
        }
    }
    if (!line.empty())z[0] = line.size();
    return z;
}

vector<int> get_cubes_count(vector<int> &cubes, const int &color_size) {
    int cubes_size = static_cast<int>(cubes.size());
    auto rev_cubes = cubes;
    reverse(rev_cubes.rbegin(), rev_cubes.rend());
    cubes.push_back(color_size + 1);
    cubes.insert(cubes.end(), rev_cubes.begin(), rev_cubes.end());
    vector<int> z = get_z_func(cubes);
    vector<int> res = {};
    int id = cubes_size / 2 - 1;
    int rev_id = cubes_size + (cubes_size % 2 == 0 ? 1 : 2);
    while (id >= 0 && rev_id < cubes.size()) {
        if (z[rev_id] >= id + 1) {
            res.push_back(cubes_size - id - 1);
        }
        --id;
        rev_id += 2;
    }
    if (!cubes.empty()) res.push_back(cubes_size);
    return res;
}