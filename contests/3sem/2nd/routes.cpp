//
// Created by Vladimir on 15.10.2020.
//

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

#define INT_INF numeric_limits<int>::max()

using namespace std;

struct Edge {
    explicit Edge(int a, int b = 0) : value(a), weight(b) {}
    int value, weight;
};

struct Graph {
    explicit Graph(int size) {
        neighbors.resize(size);
        dist.resize(size, INT_INF);
    }
    vector<vector<Edge>> neighbors;
    mutable vector<int> dist;
};

void BFS(const Graph &graph, int from);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int f, t;
        cin >> f >> t;
        graph.neighbors[f - 1].push_back(Edge(t));
        graph.neighbors[t - 1].push_back(Edge(f, 1));
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int from, to;
        cin >> from >> to;
        BFS(graph, from);
        cout << ((graph.dist[to - 1] == INT_INF) ? -1 : graph.dist[to - 1]) << endl;
        graph.dist.assign(graph.dist.size(), INT_INF);
    }
    return 0;
}

void BFS(const Graph &graph, int from) {
    deque<int> level = {};
    level.push_front(from);
    graph.dist[from - 1] = 0;
    while (!level.empty()) {
        auto v = level.front();
        level.pop_front();
        for (const auto &u : graph.neighbors[v - 1]) {
            if (graph.dist[u.value - 1] > graph.dist[v - 1] + u.weight) {
                graph.dist[u.value - 1] = graph.dist[v - 1] + u.weight;
                if (u.weight == 0) {
                    level.push_front(u.value);
                } else {
                    level.push_back(u.value);
                }
            }
        }
    }
}