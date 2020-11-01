//
// Created by Vladimir on 15.10.2020.
//

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

enum Color {
    WHITE, GRAY, BLACK
};

struct Graph {
    explicit Graph(int size) {
        adjacency_list.resize(size);
    }
    void read(const int &edge_num) {
        for (int j = 0; j < edge_num; ++j) {
            int from, to;
            cin >> from >> to;
            adjacency_list[from - 1].push_back(to);
        }
    }
    Graph getTransposed() const {
        Graph transposed(adjacency_list.size());
        for (int i = 0; i < transposed.adjacency_list.size(); ++i) {
            for (int j = 0; j < adjacency_list[i].size(); ++j) {
                transposed.adjacency_list[adjacency_list[i][j] - 1].push_back(i + 1);
            }
        }
        return transposed;
    }
    vector<vector<int>> adjacency_list;
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
        for (int i = 0; i < size; ++i) {
            order[i] = i;
        }
    }
    void start() override {}
    void process_vertex(const int &vertex) override {
        result.push_front(vertex);
    }
  private:
    deque<int> result;

    friend class CondensationVisitor;
};

class CondensationVisitor : public AbstractVisitor {
  public:
    explicit CondensationVisitor(int size, const TopSortVisitor &visitor) : component_id(0) {
        result.resize(size);
        order.resize(size);
        for (int i = 0; i < size; ++i) {
            order[i] = visitor.result[i] - 1;
        }
    }
    void start() override {
        ++component_id;
    }
    void process_vertex(const int &vertex) override {
        result[vertex - 1] = component_id;
    }
    int getComponentId() const {
        return component_id;
    }
    void print_vertices() const {
        for (const int &i : result) {
            cout << i << ' ';
        }
        cout << endl;
    }
  private:
    int component_id;
    vector<int> result;
};

void getStrongComponents(const Graph &graph);

int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    graph.read(m);
    getStrongComponents(graph);
    return 0;
}

void DFS_Visit(const Graph &graph, AbstractVisitor &visitor, vector<Color> &color, const int &vertex_id) {
    color[vertex_id] = GRAY;
    for (const auto &u : graph.adjacency_list[vertex_id]) {
        if (color[u - 1] == WHITE) {
            DFS_Visit(graph, visitor, color, u - 1);
        }
    }
    color[vertex_id] = BLACK;
    visitor.process_vertex(vertex_id + 1);
}

void DFS(const Graph &graph, AbstractVisitor &visitor) {
    vector<Color> color(graph.adjacency_list.size(), WHITE);
    for (const auto &i : visitor.order) {
        if (color[i] == WHITE) {
            visitor.start();
            DFS_Visit(graph, visitor, color, i);
        }
    }
}

void getStrongComponents(const Graph &graph) {
    TopSortVisitor sorted_graph(graph.adjacency_list.size());
    DFS(graph, sorted_graph);
    CondensationVisitor strong_components(graph.adjacency_list.size(), sorted_graph);
    DFS(graph.getTransposed(), strong_components);
    cout << strong_components.getComponentId() << endl;
    strong_components.print_vertices();
}