//
// Created by Vladimir on 16.11.2020.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    explicit Edge(int t, int w) : to(t), weight(w) {}
    int to, weight;
};

bool operator>(const Edge &lhs, const Edge &rhs) {
    return lhs.weight > rhs.weight;
}

struct Graph {
    explicit Graph(int size) : adj(size), dist(size, numeric_limits<size_t>::max()) {}
    vector<vector<Edge>> adj;
    mutable vector<size_t> dist;
    void AddEdge(const int &from, const int &to, const int &weight);
    bool RelaxEdge(const int &from, const Edge &e) const;
};

void Graph::AddEdge(const int &from, const int &to, const int &weight) {
    adj[from].emplace_back(to, weight);
}

bool Graph::RelaxEdge(const int &from, const Edge &e) const {
    if (dist[from] != numeric_limits<size_t>::max() && dist[from] + e.weight < dist[e.to]) {
        dist[e.to] = dist[from] + e.weight;
        return true;
    }
    return false;
}

void processSingleSource(const Graph &graph, const int &src);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, start, finish;
    cin >> n >> start >> finish;
    Graph dir_graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;
            cin >> weight;
            if (i != j && weight != -1) {
                dir_graph.AddEdge(i, j, weight);
            }
        }
    }
    processSingleSource(dir_graph, start - 1);
    auto condition = (dir_graph.dist[finish - 1] == numeric_limits<std::size_t>::max());
    auto result = (condition) ? -1 : (long long) dir_graph.dist[finish - 1];
    cout << result << endl;;
    return 0;
}

void processSingleSource(const Graph &graph, const int &src) {
    vector<bool> used(graph.dist.size(), false);
    priority_queue<Edge, vector<Edge>, greater<>> q;
    graph.dist[src] = 0;
    used[src] = true;
    q.push(Edge(src, 0));
    while (!q.empty()) {
        auto v = q.top();
        q.pop();
        used[v.to] = false;
        for (const auto &e : graph.adj[v.to]) {
            if (graph.RelaxEdge(v.to, e) && !used[e.to]) {
                q.push(e);
                used[e.to] = true;
            }
        }
    }
}