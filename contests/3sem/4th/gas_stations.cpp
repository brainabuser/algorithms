//
// Created by Vladimir on 18.11.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    Edge() = default;
    explicit Edge(int t, int w, int f = -1) : from(f), to(t), weight(w) {}
    int from, to, weight;
};

bool operator>(const Edge &lhs, const Edge &rhs) {
    return lhs.weight > rhs.weight;
}

struct Graph {
    explicit Graph(int size, int edges_num) : adj(size), dist(size, numeric_limits<size_t>::max()), edges(edges_num) {}
    vector<vector<Edge>> adj;
    mutable vector<size_t> dist;
    vector<Edge> edges;
    void AddEdge(const int &from, const int &to, const int &weight);
    bool RelaxEdge(const int &from, const Edge &e) const;
};

void Graph::AddEdge(const int &from, const int &to, const int &weight) {
    edges.emplace_back(from, weight, to);
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

class DSU {
  public:
    explicit DSU(int size) {
        rank.resize(size, 0);
        parent.resize(size);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }
    int FindSet(int x) {
        if (x == parent[x]) {
            return x;
        }
        return parent[x] = FindSet(parent[x]);
    }
    void Union(int x, int y) {
        x = FindSet(x);
        y = FindSet(y);
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[x] = y;
            ++rank[y];
        }
    }
  private:
    vector<int> rank;
    vector<int> parent;
};

struct Query {
    int from, to, gas_tank, order;
    bool reachable;
};

bool operator>(const Query &lhs, const Query &rhs) {
    return lhs.gas_tank > rhs.gas_tank;
}

void processSingleSource(const Graph &graph, const vector<int> &sources);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, n_stations, m;
    cin >> n >> n_stations >> m;
    vector<int> gas_stations(n_stations);
    for (auto &s : gas_stations) {
        cin >> s;
        --s;
    }
    Graph undir_graph(n, m);
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        undir_graph.AddEdge(from - 1, to - 1, weight);
    }
    //Remember queries direct order and create a min_queue by car gas_tank capacity
    int n_queries;
    cin >> n_queries;
    vector<Query> queries(n_queries);
    int order = 0;
    for (auto &i : queries) {
        cin >> i.from >> i.to >> i.gas_tank;
        --i.from;
        --i.to;
        i.order = order++;
    }
    sort(queries.begin(), queries.end(), [](const Query &lhs, const Query &rhs) {
        return lhs.gas_tank < rhs.gas_tank;
    });
    //Dijkstra from all gas stations
    processSingleSource(undir_graph, gas_stations);
    //Upgrading weights
    for (auto &e : undir_graph.edges) {
        e.weight += undir_graph.dist[e.from] + undir_graph.dist[e.to];
    }
    //Sort Edges by weight
    sort(undir_graph.edges.begin(), undir_graph.edges.end(), [](const Edge &lhs, const Edge &rhs) {
        return lhs.weight < rhs.weight;
    });
    //Create DSU to track link between crossroads
    DSU components(n);
    int curr = 0;
    for (auto &query : queries) {
        while (undir_graph.edges[curr].weight <= query.gas_tank && curr < undir_graph.edges.size()) {
            components.Union(undir_graph.edges[curr].from, undir_graph.edges[curr].to);
            ++curr;
        }
        query.reachable = components.FindSet(query.from) == components.FindSet(query.to);
    }
    //Get answers in direct order
    sort(queries.begin(), queries.end(), [](const Query &lhs, const Query &rhs) {
        return lhs.order < rhs.order;
    });
    for (const auto &i : queries) {
        cout << ((i.reachable) ? "YES" : "NO") << '\n';
    }
    return 0;
}

void processSingleSource(const Graph &graph, const vector<int> &sources) {
    vector<bool> used(graph.dist.size(), false);
    priority_queue<Edge, vector<Edge>, greater<>> q;
    for (const auto &src : sources) {
        graph.dist[src] = 0;
        used[src] = true;
        q.push(Edge(src, 0));
    }
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