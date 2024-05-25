#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// 定义最大顶点数
const int MAXN = 100;

int n, m; // n是左边集合顶点数，m是右边集合顶点数
vector<vector<int>> adj(MAXN, vector<int>(MAXN, 0)); // 邻接矩阵
int match[MAXN]; // 记录右边集合每个顶点匹配的左边顶点
bool visited[MAXN]; // 记录右边集合顶点是否在当前搜索路径中被访问过
bool dfs(int u) {
    for (int v = 0; v < m; ++v) {
        if (adj[u][v] && !visited[v]) {
            visited[v] = true;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungarian() {
    memset(match, -1, sizeof(match));
    int result = 0;
    for (int u = 0; u < n; ++u) {
        memset(visited, false, sizeof(visited));
        if (dfs(u))   ++result;
    }
    return result;
}

int main() {
    // 这里预设邻接矩阵，可以根据需要修改
    n = 5; // 左集合顶点数
    m = 5; // 右集合顶点数

    // 邻接矩阵，u_ij表示i与(j+n)相连
    adj = {
        {1, 1, 0, 1, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1}
    };

    int maxMatch = hungarian();
    cout << "最大匹配数: " << maxMatch << endl;

    for (int v = 0; v < m; ++v) {
        if (match[v] != -1) {
            cout << "匹配顶点: (" << match[v] << ", " << v+n << ")" << endl;
        }
    }

    return 0;
}