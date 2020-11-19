//
// Created by Vladimir on 18.11.2020.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    Edge() = default;
    explicit Edge(int f, int t, int w) : from(f), weight(w), to(t) {}
    int to, from, weight;
};

struct Graph {
    explicit Graph(size_t size) : dist(size, numeric_limits<int>::max()), parent(size, -1) {}
    vector<Edge> edges;
    mutable vector<int> dist;
    mutable vector<int> parent;
    void AddEdge(int from_id, int to_id, int weight);
    bool RelaxEdge(const Edge &edge) const;
};

void Graph::AddEdge(int from_id, int to_id, int weight) {
    edges.emplace_back(from_id, to_id, weight);
}

bool Graph::RelaxEdge(const Edge &edge) const {
    if (dist[edge.from] != numeric_limits<int>::max() && dist[edge.from] + edge.weight < dist[edge.to]) {
        dist[edge.to] = dist[edge.from] + edge.weight;
        parent[edge.to] = edge.from;
        return true;
    }
    return false;
}

bool findCycle(const Graph &graph, const int &src, vector<int> &ans);

int main() {
    int n;
    cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w;
            cin >> w;
            if (w != 100000) {
                graph.AddEdge(i, j, w);
            }
        }
    }
    vector<int> ans;
    bool has_cycle = false;
    for (int k = 0; k < n && !has_cycle; ++k) {
        has_cycle = findCycle(graph, k, ans);
    }
    if (!has_cycle) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        cout << ans.size() << endl;
        reverse(ans.begin(), ans.end());
        for (const auto &v: ans) {
            cout << (v + 1) << ' ';
        }
        cout << endl;
    }
    return 0;
}

void processSingleSource(const Graph &graph, const int &src) {
    graph.dist.assign(graph.dist.size(), numeric_limits<int>::max());
    graph.dist[src] = 0;
    for (int i = 0; i < graph.dist.size() - 1; ++i) {
        for (const auto &e : graph.edges) {
            graph.RelaxEdge(e);
        }
    }
}

bool findCycle(const Graph &graph, const int &src, vector<int> &ans) {
    processSingleSource(graph, src);
    for (const auto &e : graph.edges) {
        if (graph.RelaxEdge(e)) {
            auto v = e.to;
            for (int i = 0; i < graph.dist.size(); ++i) {
                v = graph.parent[v];
            }
            auto u = v;
            do {
                ans.push_back(v);
                v = graph.parent[v];
            } while (u != v || ans.size() <= 1);
            ans.push_back(u);
            return true;
        }
    }
    return false;
}