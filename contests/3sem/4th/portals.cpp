//
// Created by Vladimir on 16.11.2020.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Portal {
    Portal() = default;
    explicit Portal(int time, int to, int w) : time(time), to(to), weight(w) {}
    int time, to, weight;
};

struct Graph {
    explicit Graph(size_t size) : dist(size, numeric_limits<int>::max()), adj(size) {}
    vector<vector<Portal>> adj;
    mutable vector<int> dist;
    void AddPortal(int from_id, int to_id, int weight, int time);
    bool RelaxPortal(int from_id, const Portal &p) const;
};

void Graph::AddPortal(int from_id, int to_id, int weight, int time) {
    adj[from_id].emplace_back(time, to_id, weight);
}

bool Graph::RelaxPortal(int from_id, const Portal &p) const {
    auto new_dist = dist[from_id] + p.weight + p.time - dist[from_id];
    if (dist[from_id] != numeric_limits<int>::max() && new_dist < dist[p.to]) {
        dist[p.to] = new_dist;
        return true;
    }
    return false;
}

void processSingleSource(const Graph &graph, const int &src, const int &dest);

int main() {
    int n, m, start, finish;
    cin >> n >> start >> finish >> m;
    Graph graph(n);
    for (int i = 0; i < m; ++i) {
        int f, t, end, begin;
        cin >> f >> begin >> t >> end;
        graph.AddPortal(f - 1, t - 1, end - begin, begin);
    }
    processSingleSource(graph, start - 1, finish - 1);
    auto condition = (graph.dist[finish - 1] == numeric_limits<int>::max());
    cout << ((!condition) ? graph.dist[finish - 1] : -1) << ' ';
    cout << endl;
    return 0;
}

void processSingleSource(const Graph &graph, const int &src, const int &dest) {
    vector<bool> used(graph.dist.size(), false);
    graph.dist[src] = 0;
    queue<int> q;
    q.push(src);
    used[src] = true;
    while (!q.empty()) {
        auto v = q.front();
        used[v] = false;
        q.pop();
        for (const auto &p : graph.adj[v]) {
            if (graph.dist[v] > p.time) continue;
            if (graph.RelaxPortal(v, p) && !used[p.to]) {
                q.push(p.to);
                used[p.to] = true;
            }
        }
    }
}