//
// Created by Vladimir on 14.11.2020.
//

#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    Edge() = default;
    explicit Edge(int f, int t, int w) : from(f), weight(w), to(t) {}
    int to, from, weight;
};

struct Graph {
    explicit Graph(size_t size, size_t edge_num) : dist(size, numeric_limits<int>::max()), edges(edge_num) {}
    vector<Edge> edges;
    mutable vector<int> dist;
    void AddEdge(int from_id, int to_id, int weight);
    void RelaxEdge(int from_id, int to_id, int weight) const;
};

void Graph::AddEdge(int from_id, int to_id, int weight) {
    edges.emplace_back(from_id, to_id, weight);
}

void Graph::RelaxEdge(int from_id, int to_id, int weight) const {
    if (dist[from_id] != numeric_limits<int>::max() && dist[from_id] + weight < dist[to_id]) {
        dist[to_id] = dist[from_id] + weight;
    }
}

void processSingleSource(const Graph &graph);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n, m);
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
    graph.dist[0] = 0;
    for (int i = 0; i < graph.dist.size() - 1; ++i) {
        for (const auto &e : graph.edges) {
            graph.RelaxEdge(e.from, e.to, e.weight);
        }
    }
}