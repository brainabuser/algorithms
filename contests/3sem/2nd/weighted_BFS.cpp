//
// Created by Vladimir on 12.10.2020.
//

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

#define INT_INF numeric_limits<int>::max()

using namespace std;


struct Edge {
    explicit Edge(int a, int b) : value(a), weight(b) {}
    int value, weight;
};

struct Graph {
    explicit Graph(int size) {
        neighbors.resize(size);
        dist.resize(size, INT_INF);
    }
    vector<vector<Edge>> neighbors;
    mutable vector<int> dist;
    mutable int max_weight = 1;
};

void BFS(const Graph &graph, int from);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    int from, to;
    cin >> from >> to;
    for (int i = 0; i < m; ++i) {
        int f, t, w;
        cin >> f >> t >> w;
        graph.neighbors[f - 1].push_back(Edge(t, w));
        graph.max_weight = max(graph.max_weight, w);
    }
    BFS(graph, from);
    cout << ((graph.dist[to - 1] == INT_INF) ? -1 : graph.dist[to - 1]) << endl;
    return 0;
}

void BFS(const Graph &graph, int from) {
    auto max_path_size = graph.max_weight * (graph.neighbors.size() - 1) + 1;
    vector<queue<int>> level(max_path_size);
    level[0].push(from);
    graph.dist[from - 1] = 0;
    for (int i = 0; i < max_path_size; ++i) {
        while (!level[i].empty()) {
            auto v = level[i].front();
            level[i].pop();
            if (graph.dist[v - 1] != i) {
                continue;
            }
            for (const auto &u : graph.neighbors[v - 1]) {
                if (graph.dist[u.value - 1] > graph.dist[v - 1] + u.weight) {
                    graph.dist[u.value - 1] = graph.dist[v - 1] + u.weight;
                    level[graph.dist[v - 1] + u.weight].push(u.value);
                }
            }
        }
    }
}