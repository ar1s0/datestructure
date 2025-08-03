// 实现拓扑序列以及逆拓扑序列
#include <bits/stdc++.h>
using namespace std;

// 有向图类
class Graph {
public:
  int n;                   // 顶点数
  vector<vector<int>> adj; // 邻接表
  vector<string> names;    // 顶点名称

  Graph(int n) : n(n), adj(n), names(n) {}

  void addEdge(int u, int v) { adj[u].push_back(v); }

  void setName(int i, const string &name) { names[i] = name; }

  // 拓扑排序（Kahn算法）
  vector<int> topoSort() {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; ++u)
      for (int v : adj[u])
        indegree[v]++;
    queue<int> q;
    for (int i = 0; i < n; ++i)
      if (indegree[i] == 0)
        q.push(i);
    vector<int> order;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      order.push_back(u);
      for (int v : adj[u]) {
        if (--indegree[v] == 0)
          q.push(v);
      }
    }
    if (order.size() < n) {
      cout << "图中存在环，无法拓扑排序！\n";
      return {};
    }
    return order;
  }

  // 使用DFS实现逆拓扑序列，支持有环检测
  vector<int> reverseTopoSortDFS() {
    enum { UNVISITED, VISITING, VISITED };
    vector<int> state(n, UNVISITED);
    vector<int> order;
    bool hasCycle = false;
    function<void(int)> dfs = [&](int u) {
      state[u] = VISITING;
      for (int v : adj[u]) {
        if (state[v] == UNVISITED) {
          dfs(v);
          if (hasCycle)
            return;
        } else if (state[v] == VISITING) {
          hasCycle = true; // 检测到环
          return;
        }
      }
      state[u] = VISITED;
      order.push_back(u);
    };
    for (int i = 0; i < n; ++i) {
      if (state[i] == UNVISITED) {
        dfs(i);
        if (hasCycle)
          break;
      }
    }
    if (hasCycle) {
      cout << "图中存在环，无法进行逆拓扑序列(DFS)！\n";
      return {};
    }
    return order;
  }

  void printOrder(const vector<int> &order) {
    for (int i : order)
      cout << names[i] << " ";
    cout << endl;
  }
};

int main() {
  // 测试用例：A->B, A->C, B->D, C->D, D->E
  Graph g(5);
  g.setName(0, "A");
  g.setName(1, "B");
  g.setName(2, "C");
  g.setName(3, "D");
  g.setName(4, "E");
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 3);
  g.addEdge(3, 4);

  cout << "拓扑序列: ";
  auto topo = g.topoSort();
  g.printOrder(topo);

  cout << "逆拓扑序列(DFS): ";
  auto revTopoDFS = g.reverseTopoSortDFS();
  g.printOrder(revTopoDFS);

  return 0;
}