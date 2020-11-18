//
// Created by Vladimir on 15.11.2020.
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

void processSingleSource(const Graph &graph, const int &src, const int &dest, int days_limit);

int main() {
    int n, m, days_limit, start, finish;
    cin >> n >> m >> days_limit >> start >> finish;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int f, t, w;
        cin >> f >> t >> w;
        graph.AddEdge(f - 1, t - 1, w);
    }
    processSingleSource(graph, start - 1, finish - 1, days_limit);
    auto condition = (graph.dist[finish - 1] == numeric_limits<int>::max());
    cout << ((!condition) ? graph.dist[finish - 1] : -1) << ' ';
    cout << endl;
    return 0;
}

void processSingleSource(const Graph &graph, const int &src, const int &dest, int days_limit) {
    vector<int> day(graph.dist.size(), 0);
    graph.dist[src] = 0;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        for (const auto &e : graph.adj[v]) {
            if (day[v] + 1 == days_limit && e.to != dest) continue;
            day[e.to] = day[v] + 1;
            if (graph.RelaxEdge(v, e.to, e.weight)) {
                q.push(e.to);
            }
        }
    }
}