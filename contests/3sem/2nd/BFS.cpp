//
// Created by vladimir on 06.10.2020.
//

#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

void BFS(const vector<set<int>> &graph, int from, int to);

int main() {
    int n, m;
    cin >> n >> m;
    int from, to;
    cin >> from >> to;
    vector<set<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int f, t;
        cin >> f >> t;
        graph[f - 1].insert(t);
        graph[t - 1].insert(f);
    }
    BFS(graph, from, to);
    return 0;
}

void BFS(const vector<set<int>> &graph, int from, int to) {
    queue<int> level = {};
    vector<int> dist(graph.size(), numeric_limits<int>::max());
    vector<int> path(graph.size());
    level.push(from);
    dist[from - 1] = 0;
    while (!level.empty()) {
        int v = level.front();
        level.pop();
        for (const auto &u: graph[v - 1]) {
            if (dist[u - 1] > dist[v - 1] + 1) {
                dist[u - 1] = dist[v - 1] + 1;
                path[u - 1] = v;
                level.push(u);
            }
        }
    }
    if (dist[to - 1] == numeric_limits<int>::max()) {
        cout << -1 << endl;
        return;
    }
    vector<int> result(dist[to - 1] + 1);
    int temp = to;
    for (auto it = result.rbegin(); it < result.rend(); it = next(it)) {
        *it = temp;
        temp = path[temp - 1];
    }
    cout << dist[to - 1] << endl;
    for (const auto &item : result) {
        cout << item << ' ';
    }
    cout << endl;
}
