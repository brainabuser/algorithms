//
// Created by Vladimir on 15.10.2020.
//

#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

struct Graph {
    explicit Graph(int size) {
        vertices.resize(size);
    }
    vector<vector<int>> vertices;
};

class AbstractVisitor {
  public:
    virtual void process_vertex(const int &vertex) = 0;
    virtual void start() = 0;
    vector<int> order;
};

class TopSortVisitor : public AbstractVisitor {
  public:
    explicit TopSortVisitor(int size) {
        order.resize(size);
    }
    void start() {}
    void process_vertex(const int &vertex) override {
        result.push_front(vertex);
    }
    deque<int> result;
};

class CondensationVisitor : public AbstractVisitor {
  public:
    explicit CondensationVisitor(int size) : component_id(0) {
        result.resize(size);
        order.resize(size);
    }
    void start() {
        ++component_id;
    }
    void process_vertex(const int &vertex) override {
        result[vertex - 1] = component_id;
    }
    int component_id;
    vector<int> result;
};

void DFS(const Graph &graph, AbstractVisitor &vis);

void read_graphs(Graph &graph, Graph &graph_t, const int &edge_num) {
    for (int j = 0; j < edge_num; ++j) {
        int from, to;
        cin >> from >> to;
        graph.vertices[from - 1].push_back(to);
        graph_t.vertices[to - 1].push_back(from);
    }
}

void print_answer(const CondensationVisitor &strong_components, const int &vertex_num) {
    cout << strong_components.component_id << endl;
    for (int i = 0; i < vertex_num; ++i) {
        cout << strong_components.result[i] << ' ';
    }
    cout << endl;
}

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    Graph graph_t(n);
    read_graphs(graph, graph_t, m);
    TopSortVisitor sorted_graph(n);
    for (int i = 0; i < n; ++i) {
        sorted_graph.order[i] = i + 1;
    }
    DFS(graph, sorted_graph);
    CondensationVisitor strong_components(n);
    for (int i = 0; i < n; ++i) {
        strong_components.order[i] = sorted_graph.result[i];
    }
    DFS(graph_t, strong_components);
    print_answer(strong_components, n);
    return 0;
}

void DFS_Visit(const Graph &graph, AbstractVisitor &vis, vector<string> &color, const int &root) {
    color[root - 1] = "gray";
    for (const auto &u : graph.vertices[root - 1]) {
        if (color[u - 1] == "white") {
            DFS_Visit(graph, vis, color, u);
        }
    }
    color[root - 1] = "black";
    vis.process_vertex(root);
}

void DFS(const Graph &graph, AbstractVisitor &vis) {
    vector<string> color(graph.vertices.size(), "white");
    for (const auto &i : vis.order) {
        if (color[i - 1] == "white") {
            vis.start();
            DFS_Visit(graph, vis, color, i);
        }
    }
}