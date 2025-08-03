// 带权图最小路径算法
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 10;

// Dijkstra算法：单源最短路径
void dijkstra(int n, int src, int graph[MAXN][MAXN], int dist[MAXN],
              int pre[MAXN]) {
  bool vis[MAXN] = {false};
  for (int i = 0; i < n; i++) {
    dist[i] = graph[src][i];
    pre[i] = (graph[src][i] < INF && i != src) ? src : -1;
  }
  vis[src] = true;
  for (int i = 1; i < n; i++) {
    int u = -1, minD = INF;
    for (int j = 0; j < n; j++) {
      if (!vis[j] && dist[j] < minD) {
        minD = dist[j];
        u = j;
      }
    }
    if (u == -1)
      break;
    vis[u] = true;
    for (int v = 0; v < n; v++) {
      if (!vis[v] && graph[u][v] < INF && dist[u] + graph[u][v] < dist[v]) {
        dist[v] = dist[u] + graph[u][v];
        pre[v] = u;
      }
    }
  }
}

// Floyd算法：多源最短路径
void floyd(int n, int graph[MAXN][MAXN], int dist[MAXN][MAXN],
           int path[MAXN][MAXN]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      dist[i][j] = graph[i][j];
      path[i][j] = (i != j && graph[i][j] < INF) ? i : -1;
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][k] < INF && dist[k][j] < INF &&
            dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          path[i][j] = path[k][j];
        }
      }
    }
  }
}

int main() {
  // 测试用图（5个顶点）
  int n = 5;
  int graph[MAXN][MAXN] = {{0, 10, INF, 30, 100},
                           {INF, 0, 50, INF, INF},
                           {INF, INF, 0, INF, 10},
                           {INF, INF, 20, 0, 60},
                           {INF, INF, INF, INF, 0}};

  int dist[MAXN], pre[MAXN];
  int src = 0;
  dijkstra(n, src, graph, dist, pre);
  // 打印dijkstra
  cout << "\n===== Dijkstra路径矩阵 =====\n";
  for (int i = 0; i < n; ++i) {
    if (pre[i] != -1)
      cout << pre[i] << " <- " << i << " : " << dist[i] << "\n";
  }

  int floydDist[MAXN][MAXN], floydPath[MAXN][MAXN];
  floyd(n, graph, floydDist, floydPath);

  // 打印Floyd路径矩阵
  cout << "\n===== Floyd路径矩阵 =====\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (floydPath[i][j] == -1) {
        cout << "∞ ";
      } else {
        cout << floydPath[i][j] << " ";
      }
    }
    cout << endl;
  }
  return 0;
}
