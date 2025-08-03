// 实现广度优先遍历、 深度优先遍历
#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(const vector<vector<int>> &graph, int start) {
  vector<int> visited(graph.size(), 0);
  vector<int> result;
  queue<int> q;

  visited[start] = 1;
  q.push(start);

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    result.push_back(node);

    for (int neighbor : graph[node]) {
      if (!visited[neighbor]) {
        visited[neighbor] = 1;
        q.push(neighbor);
      }
    }
  }

  return result;
}

vector<int> dfs(const vector<vector<int>> &graph, int start) {
  vector<int> visited(graph.size(), 0);
  vector<int> result;
  // 使用栈来模拟递归
  // 也可以使用递归实现
  stack<int> s;

  s.push(start);
  visited[start] = 1;

  while (!s.empty()) {
    int node = s.top();
    s.pop();

    result.push_back(node);

    // 这里使用栈逆序遍历模拟递归
    for (int i = graph[node].size() - 1; i >= 0; --i) {
      int neighbor = graph[node][i];
      if (!visited[neighbor]) {
        visited[neighbor] = 1;
        s.push(neighbor);
      }
    }
  }
  return result;
}

int main() {
  // 创建一个中等规模的图
  vector<vector<int>> graph = {
      {1, 2},    // 0 -> 1, 0 -> 2
      {3},       // 1 -> 3
      {3, 6, 7}, // 2 -> 3, 2 -> 6, 2 -> 7
      {4},       // 3  -> 4
      {5},       // 4 -> 5
      {0, 1},    // 5 -> 0, 5 -> 1
      {6},       // 6 -> 6
      {4}        // 7 -> 4
  };

  int startNode = 0;

  // 广度优先遍历
  vector<int> bfsResult = bfs(graph, startNode);
  cout << "BFS Result: ";
  for (int node : bfsResult) {
    cout << node << " ";
  }
  cout << endl;

  // 深度优先遍历
  vector<int> dfsResult = dfs(graph, startNode);
  cout << "DFS Result: ";
  for (int node : dfsResult) {
    cout << node << " ";
  }
  cout << endl;
  return 0;
}