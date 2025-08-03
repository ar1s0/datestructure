#include <bits/stdc++.h>
using namespace std;

// 边结构
struct Edge {
  int from, to, weight;
  Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

// AOE网关键路径算法
class AOE {
public:
  int n;                    // 顶点数
  vector<vector<Edge>> adj; // 邻接表
  vector<Edge> edges;       // 边集
  vector<string> names;     // 顶点名称

  AOE(int n) : n(n), adj(n), names(n) {}

  void addEdge(int u, int v, int w) {
    adj[u].emplace_back(u, v, w);
    edges.emplace_back(u, v, w);
  }
  void setName(int i, const string &name) { names[i] = name; }

  // 关键路径算法
  void criticalPath() {
    vector<int> indegree(n, 0);
    for (auto &e : edges)
      indegree[e.to]++;
    // 拓扑排序
    queue<int> q;
    for (int i = 0; i < n; ++i)
      if (indegree[i] == 0)
        q.push(i);
    vector<int> topo;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      topo.push_back(u);
      for (auto &e : adj[u]) {
        if (--indegree[e.to] == 0)
          q.push(e.to);
      }
    }
    if (topo.size() < n) {
      cout << "图中存在环，无法进行关键路径分析！\n";
      return;
    }
    // 计算事件的最早发生时间 ve
    vector<int> ve(n, 0);
    for (int u : topo) {
      for (auto &e : adj[u]) {
        if (ve[e.to] < ve[u] + e.weight)
          ve[e.to] = ve[u] + e.weight;
      }
    }
    // 计算事件的最迟发生时间 vl
    int maxTime = *max_element(ve.begin(), ve.end());
    vector<int> vl(n, maxTime);
    for (int i = n - 1; i >= 0; --i) {
      int u = topo[i];
      for (auto &e : adj[u]) {
        if (vl[e.to] - e.weight < vl[u])
          vl[u] = vl[e.to] - e.weight;
      }
    }
    // 输出关键活动
    cout << "关键路径活动如下:\n";
    vector<vector<pair<int, int>>> keyAdj(n); // 关键活动邻接表
    for (auto &e : edges) {
      int ee = ve[e.from];
      int el = vl[e.to] - e.weight;
      if (ee == el) {
        cout << names[e.from] << " -> " << names[e.to] << " (耗时: " << e.weight
             << ")\n";
        keyAdj[e.from].emplace_back(e.to, e.weight);
      }
    }
    cout << "关键路径总长度: " << maxTime << endl;

    // 枚举所有关键路径（DFS）
    cout << "\n所有关键路径如下:\n";
    vector<int> path;
    function<void(int, int)> dfs = [&](int u, int len) {
      path.push_back(u);
      if (keyAdj[u].empty()) {
        if (len == maxTime) {
          for (size_t i = 0; i < path.size(); ++i) {
            cout << names[path[i]];
            if (i + 1 < path.size())
              cout << " -> ";
          }
          cout << " (总耗时: " << len << ")\n";
        }
      } else {
        for (auto &kv : keyAdj[u]) {
          dfs(kv.first, len + kv.second);
        }
      }
      path.pop_back();
    };
    // 从所有入度为0的点开始
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
      for (auto &kv : keyAdj[u])
        indeg[kv.first]++;
    for (int i = 0; i < n; ++i)
      if (keyAdj[i].size() && indeg[i] == 0)
        dfs(i, 0);
  }
};

int main() {
  // 测试用例：有多条关键路径的AOE网
  // 0->1(2), 0->2(2), 1->3(2), 2->3(2), 3->4(2)
  // 关键路径有两条：0-1-3-4 和 0-2-3-4
  AOE aoe(5);
  aoe.setName(0, "v0");
  aoe.setName(1, "v1");
  aoe.setName(2, "v2");
  aoe.setName(3, "v3");
  aoe.setName(4, "v4");
  aoe.addEdge(0, 1, 2);
  aoe.addEdge(0, 2, 2);
  aoe.addEdge(1, 3, 2);
  aoe.addEdge(2, 3, 2);
  aoe.addEdge(3, 4, 2);

  aoe.criticalPath();
  return 0;
}
