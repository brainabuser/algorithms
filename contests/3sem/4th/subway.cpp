//
// Created by Vladimir on 17.11.2020.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Edge {
    explicit Edge(int time = 0, int to = 0, int w = 0) : time(time), to(to), price(w) {}
    int time, to, price;
};

bool operator>(const Edge &lhs, const Edge &rhs) {
    return lhs.price > rhs.price;
}

struct Node {
    int id = -1, time = -1;
};

struct Graph {
    explicit Graph(size_t size, int time) :
            adj(size), parent(size, vector<Node>(time + 1)),
            time_limit(time), dist(size, vector<size_t>(time + 1, numeric_limits<size_t>::max())) {}
    mutable vector<vector<Edge>> adj;
    mutable vector<vector<Node>> parent;
    mutable vector<vector<size_t>> dist;
    const int time_limit;
    void AddEdge(int from_id, int to_id, int price, int time);
    bool RelaxEdge(const Edge &curr, Edge &e) const;
};

void Graph::AddEdge(int from_id, int to_id, int price, int time) {
    adj[from_id].emplace_back(time, to_id, price);
    adj[to_id].emplace_back(time, from_id, price);
}

bool Graph::RelaxEdge(const Edge &curr, Edge &e) const {
    auto new_dist = dist[curr.to][curr.time] + e.price;
    auto new_time = curr.time + e.time;
    if (dist[curr.to][curr.time] != numeric_limits<size_t>::max() && dist[e.to][new_time] > new_dist) {
        dist[e.to][new_time] = new_dist;
        parent[e.to][new_time] = {curr.to, curr.time};
        e.time += curr.time;
        return true;
    }
    return false;
}

void processSingleSource(const Graph &graph, const int &src);

int main() {
    int n, m, time_limit;
    cin >> n >> m >> time_limit;
    Graph graph(n, time_limit);
    for (int i = 0; i < m; ++i) {
        int f, t, price, time;
        cin >> f >> t >> price >> time;
        graph.AddEdge(f - 1, t - 1, price, time);
    }
    processSingleSource(graph, 0);
    auto min_dist = numeric_limits<size_t>::max();
    auto min_time = -1;
    for (int i = 0; i <= graph.time_limit; ++i) {
        if (graph.dist[n - 1][i] < min_dist) {
            min_dist = graph.dist[n - 1][i];
            min_time = i;
        }
    }
    if (min_time == -1) {
        cout << -1 << endl;
    } else {
        cout << min_dist << endl;
        stack<int> path;
        Node temp{n - 1, min_time};
        while (temp.id != -1) {
            path.push(temp.id);
            temp = graph.parent[temp.id][temp.time];
        }
        cout << path.size() << endl;
        while (!path.empty()) {
            cout << (path.top() + 1) << ' ';
            path.pop();
        }
        cout << endl;
    }
    return 0;
}

void processSingleSource(const Graph &graph, const int &src) {
    vector<vector<bool>> used(graph.dist.size(), vector<bool>(graph.time_limit + 1, false));
    priority_queue<Edge, vector<Edge>, greater<>> q;
    graph.dist[src][0] = 0;
    q.push(Edge(0, src, graph.dist[src][0]));
    used[src][0] = true;
    while (!q.empty()) {
        auto curr = q.top();
        q.pop();
        used[curr.to][curr.time] = false;
        for (auto &e : graph.adj[curr.to]) {
            auto time = curr.time + e.time;
            if (graph.time_limit < time) continue;
            if (graph.RelaxEdge(curr, e) && !used[e.to][time]) {
                q.push(Edge(e.time, e.to, graph.dist[e.to][e.time]));
                used[e.to][time] = true;
            }
        }
    }
}
