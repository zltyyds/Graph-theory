#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include<algorithm>

using namespace std;

const int INF = INT_MAX;

typedef pair<int, int> PII;

// Dijkstra算法
void Dijkstra(const vector<vector<int>>& graph, int source, vector<int>& dist, vector<int>& prev) {
    int n = graph.size();
    dist.assign(n, INF);
    prev.assign(n, -1);
    dist[source] = 0;

    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != INF) {
                int weight = graph[u][v];
                int alt = dist[u] + weight;
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push({alt, v});
                }
            }
        }
    }
}

// 生成源点到目标点的路径
vector<int> GenerateShortestPath(const vector<int>& prev, int target) {
    vector<int> path;
    for (int at = target; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n = 5;
    vector<vector<int>> graph = {
        {0, 10, 20, INF, INF},
        {10, 0, 30, 50, INF},
        {20, 30, 0, 20, INF},
        {INF, 50, 20, 0, INF},
        {INF, INF, INF, INF, 0}
    };
    int source = 0; // 源点
    int target = 4; // 目标点

    vector<int> dist, prev;
    Dijkstra(graph, source, dist, prev);

    cout << "源点 v" << source << " 到目标点 v" << target << " 的路径:\n";
    if (dist[target] == INF) {
        cout << "两者不连通，没有路径。\n";
    } else {
        cout << "两者距离为: " << dist[target] << "\n";
        vector<int> path = GenerateShortestPath(prev, target);
        cout << "路径为: ";
        for (int v : path) {
            cout << "v" << v << " ";
        }
        cout << endl;
    }

    return 0;
}