#include <iostream>
#include <vector>
#include <algorithm>

// Havel-Hakimi算法，判断是否为图序列
bool isGraphicalSequence(std::vector<int> sequence) {
    while (true) {
        // 移除序列中的0，因为0不影响判断
        sequence.erase(std::remove(sequence.begin(), sequence.end(), 0), sequence.end());
        // 如果序列移除0后为空，证明此图全为独立点
        if (sequence.empty()) 
            return true;
        // 将剩余的度序列进行从大到小的排序
        std::sort(sequence.begin(), sequence.end(), std::greater<int>());
        // 如果第一个元素就大于剩余元素，则定不是图序列
        int n = sequence[0];
        sequence.erase(sequence.begin());
        if (n > sequence.size()) {
            return false;
        }
        for (int i = 0; i < n; i++) {
            sequence[i]--;
        }
    }
}

// 生成邻接矩阵的函数
std::vector<std::vector<int>> generateAdjacencyMatrix(std::vector<int> sequence) {
    int n = sequence.size();
    std::vector<std::vector<int>> adjMatrix(n, std::vector<int>(n, 0));
    std::vector<std::pair<int, int>> edges;
    int node = 1;
    while (!sequence.empty()) {
        sequence.erase(std::remove(sequence.begin(), sequence.end(), 0), sequence.end());
        if (sequence.empty()) break;
        std::sort(sequence.begin(), sequence.end(), std::greater<int>());
        int n = sequence[0];
        sequence.erase(sequence.begin());

        for (int i = 0; i < n; i++) {
            if (i < sequence.size()) {
                sequence[i]--;
                edges.push_back({node, node + i + 1});
            }
        }
        node++;
    }
    for (const auto& edge : edges) {
        int u = edge.first - 1;
        int v = edge.second - 1;
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }
    return adjMatrix;
}

// 输出邻接矩阵的函数
void printAdjacencyMatrix(const std::vector<std::vector<int>>& adjMatrix) {
    for (const auto& row : adjMatrix) {
        for (const auto& val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<int> sequence = {4, 3, 3, 3, 1, 0};
    std::vector<int> originalSequence = sequence;

    if (isGraphicalSequence(sequence)) {
        std::cout << "此序列是图序列。" << std::endl;
        std::vector<std::vector<int>> adjMatrix = generateAdjacencyMatrix(sequence);
        printAdjacencyMatrix(adjMatrix);
    } else {
        std::cout << "此序列不是图序列。" << std::endl;
    }

    return 0;
}