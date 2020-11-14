//
// Created by Vladimir on 08.11.2020.
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
}

int findMST(const Graph &graph);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    Graph graph(n + 1);
    for (int i = 1; i < graph.adj.size(); ++i) {
        for (int j = 1; j < graph.adj.size(); ++j) {
            int weight;
            cin >> weight;
            if (i != j) {
                graph.addEdge(i, j, weight);
            }
        }
    }
    vector<int> prices(graph.adj.size());
    for (int i = 1; i < prices.size(); ++i) {
        int p;
        cin >> p;
        graph.addEdge(0, i, p);
        graph.addEdge(i, 0, p);
    }
    cout << findMST(graph) << '\n';
    return 0;
}

int findMST(const Graph &graph) {
    vector<bool> used(graph.adj.size(), false);
    size_t result = 0;
    priority_queue<Edge, vector<Edge>, greater<>> edges;
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