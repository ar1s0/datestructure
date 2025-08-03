// Tarjan算法求解强连通分量

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int MAXN = 1000;   // 最大节点数
vector<int> graph[MAXN]; // 邻接表表示图

int idx = 0;             // 索引计数
int low[MAXN];           // 低链接值
int dfn[MAXN];           // 深度优先搜索序
bool inStack[MAXN];      // 是否在栈中
stack<int> s;            // 栈用于存储节点
vector<vector<int>> scc; // 存储强连通分量

void tarjan(int u) {
  dfn[u] = low[u] = idx++;
  s.push(u);
  inStack[u] = true;

  for (int v : graph[u]) {
    if (dfn[v] == -1) { // v未被访问
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (inStack[v]) { // v在栈中
      low[u] = min(low[u], dfn[v]);
    }
  }

  // 如果u是一个强连通分量的根节点
  if (low[u] == dfn[u]) {
    vector<int> component;
    while (true) {
      int v = s.top();
      s.pop();
      inStack[v] = false;
      component.push_back(v);
      if (v == u)
        break; // 直到回到根节点
    }
    scc.push_back(component); // 将找到的强连通分量加入结果
  }
}

void findSCC(int n) {
  // 重置全局变量
  idx = 0;
  scc.clear();
  while (!s.empty())
    s.pop(); // 清空栈

  fill(dfn, dfn + n, -1);            // 初始化dfn数组
  fill(low, low + n, 0);             // 初始化low数组
  fill(inStack, inStack + n, false); // 初始化inStack数组

  for (int i = 0; i < n; ++i) {
    if (dfn[i] == -1) {
      tarjan(i);
    }
  }
}

int main() {
  // 给出测试例子
  vector<pair<int, int>> edges = {{0, 1},  {1, 2},   {2, 0}, {1, 3}, {3, 4},
                                  {4, 5},  {5, 3},   {6, 7}, {7, 8}, {8, 6},
                                  {9, 10}, {10, 11}, {11, 9}};
  int n = 12; // 节点数
  for (auto &edge : edges) {
    graph[edge.first].push_back(edge.second);
  }
  findSCC(n);
  for (const auto &component : scc) {
    cout << "Strongly Connected Component: ";
    for (int node : component) {
      cout << node << " ";
    }
    cout << endl;
  }
  return 0;
}