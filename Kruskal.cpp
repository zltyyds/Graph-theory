#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

// 并查集数据结构
class UnionFind {
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v) {
            if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

// 邻接矩阵输出函数
void printAdjacencyMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>> kruskal(const std::vector<std::vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    std::vector<std::tuple<int, int, int>> edges;
    UnionFind uf(n);
    // 从邻接矩阵中提取所有边
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix[i][j] != 0) {
                edges.emplace_back(adjMatrix[i][j], i, j);
            }
        }
    }
    // 按权重升序排序边
    std::sort(edges.begin(), edges.end());
    std::vector<std::vector<int>> mst(n, std::vector<int>(n, 0));  // 最小生成树的邻接矩阵
    // 逐条检查并选取边
    for (const auto& [weight, u, v] : edges) {
        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst[u][v] = weight;
            mst[v][u] = weight;  // 无向图
        }
    }
    return mst;
}

int main() {
    std::vector<std::vector<int>> adjMatrix = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    std::vector<std::vector<int>> mst = kruskal(adjMatrix);

    std::cout << "最小生成树的邻接矩阵:\n";
    printAdjacencyMatrix(mst);

    return 0;
}