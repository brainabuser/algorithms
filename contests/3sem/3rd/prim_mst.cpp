//
// Created by Vladimir on 05.11.2020.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge {
    explicit Edge(int a, int b) : to(a), weight(b) {}
    mutable int to, weight;
};

bool operator>(const Edge &lhs, const Edge &rhs) {
    return lhs.weight > rhs.weight;
}

struct Graph {
    explicit Graph(const size_t &size) {
        adj.resize(size);
    }
    vector<vector<Edge>> adj;
    void addEdge(const int &from, const int &to, const int &weight);
};

void Graph::addEdge(const int &from, const int &to, const int &weight) {
    adj[from].emplace_back(to, weight);
    adj[to].emplace_back(from, weight);
}

int findMST(const Graph &graph);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph.addEdge(from - 1, to - 1, weight);
    }
    cout << findMST(graph) << '\n';
    return 0;
}

int findMST(const Graph &graph) {
    size_t result = 0;
    priority_queue<Edge, vector<Edge>, greater<>> edges;
    vector<bool> used(graph.adj.size(), false);
    edges.push(Edge(0, 0));
    while (!edges.empty()) {
        Edge uv = edges.top();
        edges.pop();
        if (used[uv.to]) continue;
        used[uv.to] = true;
        result += uv.weight;
        for (const auto &nbr : graph.adj[uv.to]) {
            if (!used[nbr.to]) {
                edges.push(nbr);
            }
        }
    }
    return result;
}