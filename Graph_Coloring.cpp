#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

// 图着色算法，贪心的方式
void greedyColoring(const std::vector<std::vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    std::vector<int> result(n, -1);  // 用于存储颜色结果
    std::vector<bool> available(n, false); // 用于记录哪些颜色可用，false表示该颜色可用

    result[0] = 0;
    for (int u = 1; u < n; ++u) {
        // 把所有邻接顶点的颜色标记为不可用
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] == 1 && result[v] != -1)
                available[result[v]] = true;
        }
        // 找到第一个可用颜色
        int cr;
        for (cr = 0; cr < n; ++cr) {
            if (!available[cr])     break;
        }
        result[u] = cr;  // 为当前顶点u分配颜色cr
        // 重置所有邻接顶点的颜色标记为可用
        for (int v = 0; v < n; ++v) {
            if (adjMatrix[u][v] == 1 && result[v] != -1) {
                available[result[v]] = false;
            }
        }
    }

    // 输出结果
    std::cout << "点的颜色分配:\n";
    for (int u = 0; u < n; ++u) {
        std::cout << "顶点 " << u << " ---> 颜色 " << result[u] << "\n";
    }

    // 输出同一颜色的顶点集合
    std::vector<std::list<int>> colorSet(n);
    for (int u = 0; u < n; ++u) {
        colorSet[result[u]].push_back(u);
    }

    for (int cr = 0; cr < n; ++cr) {
        if (!colorSet[cr].empty()) {
            std::cout << "颜色 " << cr << " 的顶点集合: ";
            for (int u : colorSet[cr]) {
                std::cout << u << " ";
            }
            std::cout << "\n";
        }
    }
}

int main() {
    std::vector<std::vector<int>> adjMatrix = {
        {0, 1, 1, 1, 1, 0},
        {1, 0, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 0},
        {1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    greedyColoring(adjMatrix);

    return 0;
}