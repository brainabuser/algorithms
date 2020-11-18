//
// Created by Vladimir on 18.11.2020.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    explicit Edge(int t, int w, int f = -1) : from(f), to(t), weight(w) {}
    int from, to, weight;
};

bool operator>(const Edge &lhs, const Edge &rhs) {
    return lhs.weight > rhs.weight;
}

struct Graph {
    explicit Graph(int size) : adj(size), dist(size, vector<int>(size, numeric_limits<int>::max())) {}
    vector<vector<Edge>> adj;
    mutable vector<vector<int>> dist;
    vector<Edge> edges;
    void AddEdge(const int &from, const int &to, const int &weight);
    bool RelaxEdge(const int &src, const int &from, const Edge &e) const;
};

void Graph::AddEdge(const int &from, const int &to, const int &weight) {
    edges.emplace_back(to, weight, from);
    adj[from].emplace_back(to, weight);
}

bool Graph::RelaxEdge(const int &src, const int &from, const Edge &e) const {
    if (dist[src][from] != numeric_limits<int>::max() && dist[src][from] + e.weight < dist[src][e.to]) {
        dist[src][e.to] = dist[src][from] + e.weight;
        return true;
    }
    return false;
}

int processJohnson(const Graph &graph);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    Graph dir_graph(n + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int weight;
            cin >> weight;
            if (i != j && weight != -1) {
                dir_graph.AddEdge(i, j, weight);
            }
        }
    }
    int source = n;
    for (int k = 0; k < n; ++k) {
        dir_graph.AddEdge(source, k, 0);
    }
    auto ans = processJohnson(dir_graph);
    cout << ans << endl;
    return 0;
}

void processDijkstra(const Graph &graph, const int &src) {
    vector<bool> used(graph.dist.size(), false);
    priority_queue<Edge, vector<Edge>, greater<>> q;
    graph.dist[src][src] = 0;
    used[src] = true;
    q.push(Edge(src, 0));
    while (!q.empty()) {
        auto v = q.top();
        q.pop();
        used[v.to] = false;
        for (const auto &e : graph.adj[v.to]) {
            if (graph.RelaxEdge(src, v.to, e) && !used[e.to]) {
                q.push(e);
                used[e.to] = true;
            }
        }
    }
}

void processFB(const Graph &graph, const int &src) {
    graph.dist[src][src] = 0;
    for (int i = 0; i < graph.dist.size() - 1; ++i) {
        for (const auto &e : graph.edges) {
            graph.RelaxEdge(src, e.from, e);
        }
    }
}

int processJohnson(const Graph &graph) {
    int source = graph.adj.size() - 1;
    processFB(graph, source);
    for (int i = 0; i < graph.adj.size(); ++i) {
        processDijkstra(graph, i);
    }
    int max_dist = numeric_limits<int>::min();
    for (int i = 0; i < graph.adj.size(); ++i) {
        for (int j = 0; j < graph.adj.size(); ++j) {
            if (graph.dist[i][j] != numeric_limits<int>::max()) {
                max_dist = max(graph.dist[i][j], max_dist);
            }
        }
    }
    return max_dist;
}