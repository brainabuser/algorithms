//
// Created by vladimir on 06.10.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Graph {
    explicit Graph(int size) {
        vertices.resize(size);
        dist.resize(size, numeric_limits<int>::max());
        path.resize(size);
    }
    mutable vector<int> dist;
    mutable vector<int> path;
    vector<vector<int>> vertices;
};

void BFS(const Graph &graph, int from);

void print_path(const Graph &graph, int from, int to);

int main() {
    int n, m;
    cin >> n >> m;
    int from, to;
    cin >> from >> to;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int f, t;
        cin >> f >> t;
        graph.vertices[f - 1].push_back(t);
        graph.vertices[t - 1].push_back(f);
    }
    BFS(graph, from);
    print_path(graph, from, to);
    return 0;
}

void BFS(const Graph &graph, int from) {
    queue<int> level = {};
    level.push(from);
    graph.dist[from - 1] = 0;
    while (!level.empty()) {
        int v = level.front();
        level.pop();
        for (const auto &u: graph.vertices[v - 1]) {
            if (graph.dist[u - 1] > graph.dist[v - 1] + 1) {
                graph.dist[u - 1] = graph.dist[v - 1] + 1;
                graph.path[u - 1] = v;
                level.push(u);
            }
        }
    }
}

void print_path(const Graph &graph, int from, int to) {
    if (graph.dist[to - 1] == numeric_limits<int>::max()) {
        cout << -1 << endl;
        return;
    }
    vector<int> result(graph.dist[to - 1] + 1);
    int temp = to;
    for (auto it = result.rbegin(); it < result.rend();
         it = next(it)) {
        *it = temp;
        temp = graph.path[temp - 1];
    }
    cout << graph.dist[to - 1] << endl;
    for (const auto &item: result) {
        cout << item << ' ';
    }
    cout << endl;
}
