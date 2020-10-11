//
// Created by vladimir on 07.10.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;

string firstPlus(string num) {
    num.front() += (num.front() != '9');
    return num;
}

string lastMinus(string num) {
    num.back() -= (num.back() != '1');
    return num;
}

string rotateLeft(string num) {
    rotate(num.begin(), num.begin() + 1, num.end());
    return num;
}

string rotateRight(string num) {
    rotate(num.rbegin(), num.rbegin() + 1, num.rend());
    return num;
}

typedef string(*func_ptr)(string);

struct Graph {
    vector<func_ptr> neighbors = {firstPlus, lastMinus, rotateLeft, rotateRight};
};

void BFS(const Graph &graph, const string &from, const string &to);

int main() {
    string from{}, to{};
    cin >> from >> to;
    Graph graph;
    BFS(graph, from, to);
    return 0;
}

void BFS(const Graph &graph, const string &from, const string &to) {
    queue<string> level = {};
    unordered_map<string, string> path;
    unordered_map<string, int> dist;
    level.push(from);
    dist[from] = 0;
    while (!level.empty()) {
        auto v = level.front();
        level.pop();
        for (const auto &u: graph.neighbors) {
            auto v_copy = u(v);
            if (v_copy != v) {
                if (dist.count(v_copy) == 0 || dist[v_copy] > dist[v] + 1) {
                    dist[v_copy] = dist[v] + 1;
                    path[v_copy] = v;
                    level.push(v_copy);
                }
            }
        }
    }
    vector<string> result(dist[to] + 1);
    auto temp = to;
    for (auto it = result.rbegin(); it < result.rend(); it = next(it)) {
        *it = temp;
        temp = path[temp];
    }
    cout << dist[to] + 1 << endl;
    for (const auto &item : result) {
        cout << item << endl;
    }
    cout << endl;
}