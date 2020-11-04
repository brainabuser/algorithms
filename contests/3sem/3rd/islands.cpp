//
// Created by Vladimir on 04.11.2020.
//

#include <iostream>
#include <vector>

using namespace std;

class DSU {
  public:
    bool isAllConnected = false;
    explicit DSU(int size) {
        rank.resize(size, 0);
        parent.resize(size);
        kids.resize(size, 1);
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
            if (x != y) {
                kids[x] += kids[y];
            }
        } else {
            parent[x] = y;
            if (x != y) {
                kids[y] += kids[x];
            }
            if (rank[x] == rank[y]) {
                ++rank[y];
            }
        }
        auto s = kids.size();
        isAllConnected = (kids[x] == s || kids[y] == s);
    }
  private:
    vector<int> rank;
    vector<int> parent;
    vector<int> kids;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    DSU undir_graph(n);
    int i = 0;
    while (i++ < m && !undir_graph.isAllConnected) {
        int from, to;
        cin >> from >> to;
        undir_graph.Union(from, to);
    }
    cout << i - 1 << '\n';
    return 0;
}