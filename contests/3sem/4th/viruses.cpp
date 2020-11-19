//
// Created by Vladimir on 18.11.2020.
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
    adj[to].emplace_back(from, weight);
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
    int n, m, n_cursed_counries;
    cin >> n >> m >> n_cursed_counries;
    vector<int> cursed_countries(n_cursed_counries);
    for (auto &c : cursed_countries) {
        cin >> c;
        --c;
    }
    Graph undir_graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        undir_graph.AddEdge(from - 1, to - 1, weight);
    }
    int src, dest;
    cin >> src >> dest;
    processSingleSource(undir_graph, dest - 1);
    bool win = true;
    auto res = undir_graph.dist[src - 1];
    for (auto &c : cursed_countries) {
        if (res >= undir_graph.dist[c]) {
            win = false;
            break;
        }
    }
    if (win && res != numeric_limits<size_t>::max()) {
        cout << res << '\n';
    } else {
        cout << -1 << '\n';
    }
    return 0;
}

void processSingleSource(const Graph &graph, const int &src) {
    vector<bool> used(graph.dist.size(), false);
    used[src] = true;
    graph.dist[src] = 0;
    queue<int> q;
    q.push(src);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        used[v] = false;
        for (const auto &e : graph.adj[v]) {
            if (graph.RelaxEdge(v, e) && !used[e.to]) {
                q.push(e.to);
                used[e.to] = true;
            }
        }
    }
}