//
// Created by vladimir on 08.10.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stack>

using namespace std;

struct Graph {
    explicit Graph(int size) {
        vertices.resize(size);
        t_in.resize(size);
        t_out.resize(size);
        color.resize(size, "white");
    }

    int timer = 0;
    bool has_cycle = false;
    int cycle_start;
    bool meet_cycle_start = false;
    stack<int> trace;
    vector<string> color;
    vector<int> t_in, t_out;
    vector<set<int>> vertices;
};

void DFS(Graph &graph);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int j = 0; j < m; ++j) {
        int from, to;
        cin >> from >> to;
        graph.vertices[from - 1].insert(to);
    }
    DFS(graph);
    cout << ((graph.has_cycle) ? "YES" : "NO") << endl;
    if (graph.has_cycle) {
        graph.trace.push(graph.cycle_start);
        while (!graph.trace.empty()) {
            cout << graph.trace.top() << ' ';
            graph.trace.pop();
        }
    }
    return 0;
}

void DFS_Visit(Graph &graph, const int &root) {
    graph.color[root - 1] = "gray";
    graph.t_in[root - 1] = graph.timer++;
    for (auto &u : graph.vertices[root - 1]) {
        if (graph.has_cycle) {
            break;
        }
        if (graph.color[u - 1] == "white") {
            DFS_Visit(graph, u);
        } else if (graph.color[u - 1] == "gray") {
            graph.has_cycle = true;
            graph.cycle_start = u;
        }
    }
    if (graph.has_cycle) {
        if (root != graph.cycle_start) {
            if (!graph.meet_cycle_start && graph.color[root - 1] == "gray") {
                graph.trace.push(root);
            }
        } else {
            graph.meet_cycle_start = true;
        }
        return;
    }
    graph.color[root - 1] = "black";
    graph.t_out[root - 1] = graph.timer++;
}

void DFS(Graph &graph) {
    for (size_t i = 0; i < graph.vertices.size(); ++i) {
        if (graph.has_cycle) {
            break;
        } else if (graph.color[i] == "white") {
            DFS_Visit(graph, i + 1);
        }
    }
}