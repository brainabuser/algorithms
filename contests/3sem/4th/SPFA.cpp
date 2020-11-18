//
// Created by Vladimir on 16.11.2020.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    Edge() = default;
    explicit Edge(int to, int w) : to(to), weight(w) {}
    int to, weight;
};

struct Graph {
    explicit Graph(size_t size) : dist(size, numeric_limits<int>::max()), adj(size) {}
    vector<vector<Edge>> adj;
    mutable vector<int> dist;
    void AddEdge(int from_id, int to_id, int weight);
    bool RelaxEdge(int from_id, int to_id, int weight) const;
};

void Graph::AddEdge(int from_id, int to_id, int weight) {
    adj[from_id].emplace_back(to_id, weight);
}

bool Graph::RelaxEdge(int from_id, int to_id, int weight) const {
    if (dist[from_id] != numeric_limits<int>::max() && dist[from_id] + weight < dist[to_id]) {
        dist[to_id] = dist[from_id] + weight;
        return true;
    }
    return false;
}

void processSingleSource(const Graph &graph);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int f, t, w;
        cin >> f >> t >> w;
        graph.AddEdge(f - 1, t - 1, w);
    }
    processSingleSource(graph);
    for (int i : graph.dist) {
        auto condition = (i == numeric_limits<int>::max());
        cout << ((!condition) ? i : 30000) << ' ';
    }
    cout << endl;
    return 0;
}

void processSingleSource(const Graph &graph) {
    vector<bool> used(graph.dist.size(), false);
    graph.dist[0] = 0;
    queue<int> q;
    q.push(0);
    used[0] = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        used[v] = false;
        for (const auto &e : graph.adj[v]) {
            if (graph.RelaxEdge(v, e.to, e.weight) && !used[e.to]) {
                q.push(e.to);
                used[e.to] = true;
            }
        }
    }
}