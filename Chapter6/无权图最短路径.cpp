// 使用广度优先遍历求得最短路径
#include <bits/stdc++.h>
using namespace std;

vector<int> shortestPath(int start, int end, const vector<vector<int>> &graph) {
  vector<int> dist(graph.size(), INT_MAX);
  vector<int> prev(graph.size(), -1);
  queue<int> q;

  dist[start] = 0;
  q.push(start);

  while (!q.empty()) {
    int node = q.front();
    q.pop();

    for (int neighbor : graph[node]) {
      if (dist[neighbor] == INT_MAX) { // 未访问过
        dist[neighbor] = dist[node] + 1;
        prev[neighbor] = node;
        q.push(neighbor);
      }
    }
  }

  // 回溯路径
  vector<int> path;
  for (int at = end; at != -1; at = prev[at]) {
    path.push_back(at);
  }
  reverse(path.begin(), path.end());

  return path;
}

void testShortestPath() {
  cout << "========== 最短路径测试 ==========" << endl;

  // 创建一个简单的图
  vector<vector<int>> graph = {
      {1, 2},    // 0
      {0, 3, 4}, // 1
      {0, 3},    // 2
      {1, 2, 4}, // 3
      {1, 3}     // 4
  };

  int start = 0;
  int end = 4;

  vector<int> path = shortestPath(start, end, graph);

  cout << "从 " << start << " 到 " << end << " 的最短路径: ";
  for (int node : path) {
    cout << node << " ";
  }
  cout << endl;
}

int main() {
  testShortestPath();
  return 0;
}