// 最小生成树算法 prim 和 kruskal 的边结点结构
// 该代码使用 C++17 标准版本
#include <bits/stdc++.h>
using namespace std;

// ==============================================
// 边的结构定义
// ==============================================

// 用于Kruskal算法的边结构
struct Edge {
  int u, v;   // 边的两个顶点
  int weight; // 边的权重

  Edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), weight(w) {}

  // 用于排序的比较函数
  bool operator<(const Edge &other) const { return weight < other.weight; }
};

// ==============================================
// 并查集（用于Kruskal算法）
// ==============================================

class UnionFind {
private:
  vector<int> parent;
  vector<int> rank;

public:
  UnionFind(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  // 查找根节点（路径压缩）
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  // 合并两个集合（按秩合并）
  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return false; // 已经在同一个集合中
    }

    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }
    return true;
  }

  // 判断两个元素是否在同一个集合中
  bool connected(int x, int y) { return find(x) == find(y); }
};

// ==============================================
// 图的类定义
// ==============================================

class Graph {
private:
  int vertices;                  // 顶点数
  vector<vector<int>> adjMatrix; // 邻接矩阵
  vector<Edge> edges;            // 边的列表
  vector<string> vertexNames;    // 顶点名称

public:
  Graph(int v) : vertices(v) {
    adjMatrix.assign(v, vector<int>(v, INT_MAX));
    vertexNames.resize(v);

    // 初始化对角线为0
    for (int i = 0; i < v; i++) {
      adjMatrix[i][i] = 0;
    }
  }

  // 设置顶点名称
  void setVertexName(int index, const string &name) {
    if (index >= 0 && index < vertices) {
      vertexNames[index] = name;
    }
  }

  // 添加边
  void addEdge(int u, int v, int weight) {
    if (u >= 0 && u < vertices && v >= 0 && v < vertices) {
      adjMatrix[u][v] = weight;
      adjMatrix[v][u] = weight; // 无向图
      edges.push_back(Edge(u, v, weight));
    }
  }

  // 打印图
  void printGraph() {
    cout << "\n=== 图的邻接矩阵表示 ===" << endl;
    cout << "    ";
    for (int i = 0; i < vertices; i++) {
      cout << setw(6) << vertexNames[i];
    }
    cout << endl;

    for (int i = 0; i < vertices; i++) {
      cout << setw(4) << vertexNames[i];
      for (int j = 0; j < vertices; j++) {
        if (adjMatrix[i][j] == INT_MAX) {
          cout << setw(6) << "∞";
        } else {
          cout << setw(6) << adjMatrix[i][j];
        }
      }
      cout << endl;
    }

    cout << "\n=== 边的列表 ===" << endl;
    for (const auto &edge : edges) {
      cout << vertexNames[edge.u] << " - " << vertexNames[edge.v] << " : "
           << edge.weight << endl;
    }
  }

  // ==============================================
  // Prim算法实现最小生成树
  // ==============================================
  void primMST() {
    cout << "\n========== Prim算法求最小生成树 ==========" << endl;

    vector<int> key(vertices, INT_MAX);  // 到MST的最小权重
    vector<bool> inMST(vertices, false); // 是否已加入MST
    vector<int> parent(vertices, -1);    // 父节点数组

    // 从顶点0开始
    key[0] = 0;
    int totalWeight = 0;

    cout << "\nPrim算法执行过程:" << endl;

    for (int count = 0; count < vertices; count++) {
      // 找到不在MST中的最小key值的顶点
      int u = -1;
      for (int v = 0; v < vertices; v++) {
        if (!inMST[v] && (u == -1 || key[v] < key[u])) {
          u = v;
        }
      }

      inMST[u] = true;

      if (parent[u] != -1) {
        cout << "添加边: " << vertexNames[parent[u]] << " - " << vertexNames[u]
             << " (权重: " << key[u] << ")" << endl;
        totalWeight += key[u];
      }

      // 更新相邻顶点的key值
      for (int v = 0; v < vertices; v++) {
        if (!inMST[v] && adjMatrix[u][v] != INT_MAX &&
            adjMatrix[u][v] < key[v]) {
          key[v] = adjMatrix[u][v];
          parent[v] = u;
        }
      }
    }

    cout << "\nPrim算法结果:" << endl;
    cout << "最小生成树的边:" << endl;
    for (int i = 1; i < vertices; i++) {
      cout << vertexNames[parent[i]] << " - " << vertexNames[i] << " : "
           << adjMatrix[i][parent[i]] << endl;
    }
    cout << "最小生成树总权重: " << totalWeight << endl;
  }

  // ==============================================
  // Kruskal算法实现最小生成树
  // ==============================================
  void kruskalMST() {
    cout << "\n========== Kruskal算法求最小生成树 ==========" << endl;

    // 对边按权重排序
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end());

    cout << "\n排序后的边:" << endl;
    for (const auto &edge : sortedEdges) {
      cout << vertexNames[edge.u] << " - " << vertexNames[edge.v] << " : "
           << edge.weight << endl;
    }

    UnionFind uf(vertices);
    vector<Edge> mstEdges;
    int totalWeight = 0;

    cout << "\nKruskal算法执行过程:" << endl;

    for (const auto &edge : sortedEdges) {
      if (uf.unite(edge.u, edge.v)) {
        mstEdges.push_back(edge);
        totalWeight += edge.weight;
        cout << "添加边: " << vertexNames[edge.u] << " - "
             << vertexNames[edge.v] << " (权重: " << edge.weight << ")" << endl;

        if (mstEdges.size() == vertices - 1) {
          break; // MST已完成
        }
      } else {
        cout << "跳过边: " << vertexNames[edge.u] << " - "
             << vertexNames[edge.v] << " (会形成环)" << endl;
      }
    }

    cout << "\nKruskal算法结果:" << endl;
    cout << "最小生成树的边:" << endl;
    for (const auto &edge : mstEdges) {
      cout << vertexNames[edge.u] << " - " << vertexNames[edge.v] << " : "
           << edge.weight << endl;
    }
    cout << "最小生成树总权重: " << totalWeight << endl;
  }

  // ==============================================
  // 优化版Prim算法（使用优先队列）
  // ==============================================
  void primMSTOptimized() {
    cout << "\n========== 优化版Prim算法（优先队列） ==========" << endl;

    vector<bool> inMST(vertices, false);
    vector<int> parent(vertices, -1);
    int totalWeight = 0;

    // 优先队列：{权重, {顶点, 父节点}}
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>,
                   greater<pair<int, pair<int, int>>>>
        pq;

    // 从顶点0开始
    pq.push({0, {0, -1}});

    cout << "\n优化版Prim算法执行过程:" << endl;

    while (!pq.empty()) {
      int weight = pq.top().first;
      int u = pq.top().second.first;
      int p = pq.top().second.second;
      pq.pop();

      if (inMST[u])
        continue;

      inMST[u] = true;
      parent[u] = p;

      if (p != -1) {
        cout << "添加边: " << vertexNames[p] << " - " << vertexNames[u]
             << " (权重: " << weight << ")" << endl;
        totalWeight += weight;
      }

      // 将相邻顶点加入优先队列
      for (int v = 0; v < vertices; v++) {
        if (!inMST[v] && adjMatrix[u][v] != INT_MAX) {
          pq.push({adjMatrix[u][v], {v, u}});
        }
      }
    }

    cout << "优化版Prim算法总权重: " << totalWeight << endl;
  }
};

// ==============================================
// 测试函数
// ==============================================

void testMST() {
  cout << "========== 最小生成树算法测试 ==========" << endl;

  // 创建图（6个顶点）
  Graph g(6);

  // 设置顶点名称
  g.setVertexName(0, "A");
  g.setVertexName(1, "B");
  g.setVertexName(2, "C");
  g.setVertexName(3, "D");
  g.setVertexName(4, "E");
  g.setVertexName(5, "F");

  // 添加边（经典的MST测试图）
  g.addEdge(0, 1, 6); // A-B: 6
  g.addEdge(0, 2, 1); // A-C: 1
  g.addEdge(0, 3, 5); // A-D: 5
  g.addEdge(1, 2, 5); // B-C: 5
  g.addEdge(1, 4, 3); // B-E: 3
  g.addEdge(2, 3, 5); // C-D: 5
  g.addEdge(2, 4, 6); // C-E: 6
  g.addEdge(2, 5, 4); // C-F: 4
  g.addEdge(3, 5, 2); // D-F: 2
  g.addEdge(4, 5, 6); // E-F: 6

  // 打印图
  g.printGraph();

  // 运行Prim算法
  g.primMST();

  // 运行Kruskal算法
  g.kruskalMST();

  // 运行优化版Prim算法
  g.primMSTOptimized();
}

void testSmallGraph() {
  cout << "\n\n========== 小图测试 ==========" << endl;

  // 创建小图（4个顶点）
  Graph g(4);

  // 设置顶点名称
  g.setVertexName(0, "1");
  g.setVertexName(1, "2");
  g.setVertexName(2, "3");
  g.setVertexName(3, "4");

  // 添加边
  g.addEdge(0, 1, 10); // 1-2: 10
  g.addEdge(0, 2, 6);  // 1-3: 6
  g.addEdge(0, 3, 5);  // 1-4: 5
  g.addEdge(1, 3, 15); // 2-4: 15
  g.addEdge(2, 3, 4);  // 3-4: 4

  // 打印图
  g.printGraph();

  // 运行算法
  g.primMST();
  g.kruskalMST();
}

int main() {
  // 测试主要的MST算法
  testMST();

  // 测试小图
  testSmallGraph();

  cout << "\n程序执行完毕!" << endl;
  return 0;
}
