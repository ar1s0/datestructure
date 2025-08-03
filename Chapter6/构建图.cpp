#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
  int vertices;    // 顶点数
  bool isDirected; // 是否为有向图

public:
  // 1. 邻接矩阵表示
  vector<vector<int>> adjMatrix;

  // 2. 邻接表表示
  vector<vector<int>> adjList;

  Graph(int v, bool directed = false) : vertices(v), isDirected(directed) {
    // 初始化邻接矩阵
    adjMatrix.resize(v, vector<int>(v, 0));

    // 初始化邻接表
    adjList.resize(v);
  }

  // 添加边
  void addEdge(int from, int to, int weight = 1) {
    // 1. 邻接矩阵添加边
    adjMatrix[from][to] = weight;
    if (!isDirected) {
      adjMatrix[to][from] = weight; // 无向图需要对称
    }

    // 2. 邻接表添加边
    adjList[from].push_back(to);
    if (!isDirected) {
      adjList[to].push_back(from);
    }
  }

  // 显示邻接矩阵
  void printAdjMatrix() {
    cout << "\n=== 邻接矩阵表示 ===" << endl;
    cout << "特点：O(V²)空间，查找边O(1)，适合稠密图" << endl;
    cout << "   ";
    for (int i = 0; i < vertices; i++) {
      cout << setw(3) << i;
    }
    cout << endl;

    for (int i = 0; i < vertices; i++) {
      cout << setw(2) << i << " ";
      for (int j = 0; j < vertices; j++) {
        cout << setw(3) << adjMatrix[i][j];
      }
      cout << endl;
    }
  }

  // 显示邻接表
  void printAdjList() {
    cout << "\n=== 邻接表表示 ===" << endl;
    cout << "特点：O(V+E)空间，遍历邻接点高效，适合稀疏图" << endl;
    for (int i = 0; i < vertices; i++) {
      cout << "顶点 " << i << ": ";
      for (int neighbor : adjList[i]) {
        cout << neighbor << " ";
      }
      cout << endl;
    }
  }

  // 显示图的基本信息
  void printGraphInfo() {
    cout << "\n=== 图的基本信息 ===" << endl;
    cout << "顶点数: " << vertices << endl;
    cout << "图类型: " << (isDirected ? "有向图" : "无向图") << endl;

    // 计算边数（从邻接表计算）
    int edgeCount = 0;
    for (int i = 0; i < vertices; i++) {
      edgeCount += adjList[i].size();
    }
    if (!isDirected) {
      edgeCount /= 2; // 无向图每条边被计算了两次
    }
    cout << "边数: " << edgeCount << endl;

    // 计算每个顶点的度
    cout << "各顶点的度:" << endl;
    for (int i = 0; i < vertices; i++) {
      int degree = adjList[i].size();
      cout << "  顶点" << i << ": " << degree << endl;
    }
  }

  // 检查两点间是否有边（邻接矩阵方法）
  bool hasEdgeMatrix(int from, int to) {
    if (from >= 0 && from < vertices && to >= 0 && to < vertices) {
      return adjMatrix[from][to] != 0;
    }
    return false;
  }

  // 检查两点间是否有边（邻接表方法）
  bool hasEdgeList(int from, int to) {
    if (from >= 0 && from < vertices) {
      for (int neighbor : adjList[from]) {
        if (neighbor == to)
          return true;
      }
    }
    return false;
  }

  // 获取顶点的所有邻接点
  vector<int> getNeighbors(int vertex) {
    if (vertex >= 0 && vertex < vertices) {
      return adjList[vertex];
    }
    return vector<int>();
  }
};

int main() {
  cout << "=== 图的不同表示方法演示 ===" << endl;

  // 创建一个示例图
  int choice;
  cout << "\n选择图的类型:" << endl;
  cout << "1. 无向图示例" << endl;
  cout << "2. 有向图示例" << endl;
  cout << "3. 自定义输入" << endl;
  cout << "请选择 (1-3): ";
  cin >> choice;

  if (choice == 1) {
    // 无向图示例
    Graph g(5, false); // 5个顶点的无向图

    cout << "\n构建无向图示例:" << endl;
    cout << "边: (0-1), (0-2), (1-3), (2-3), (3-4)" << endl;

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printGraphInfo();
    g.printAdjMatrix();
    g.printAdjList();

    // 测试查找功能
    cout << "\n=== 边查找测试 ===" << endl;
    cout << "顶点0和顶点1之间有边吗? " << (g.hasEdgeMatrix(0, 1) ? "是" : "否")
         << endl;
    cout << "顶点0和顶点4之间有边吗? " << (g.hasEdgeList(0, 4) ? "是" : "否")
         << endl;

  } else if (choice == 2) {
    // 有向图示例
    Graph g(4, true); // 4个顶点的有向图

    cout << "\n构建有向图示例:" << endl;
    cout << "边: (0->1), (0->2), (1->2), (2->3), (3->1)" << endl;

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.printGraphInfo();
    g.printAdjMatrix();
    g.printAdjList();

  } else if (choice == 3) {
    // 自定义输入
    int vertices, edges;
    bool isDirected;
    int dirChoice;

    cout << "\n输入顶点数: ";
    cin >> vertices;
    cout << "输入边数: ";
    cin >> edges;
    cout << "选择图类型 (1-无向图, 2-有向图): ";
    cin >> dirChoice;
    isDirected = (dirChoice == 2);

    Graph g(vertices, isDirected);

    cout << "\n输入边 (格式: 起点 终点 [权重]):" << endl;
    for (int i = 0; i < edges; i++) {
      int from, to, weight = 1;
      cout << "边 " << (i + 1) << ": ";
      cin >> from >> to;

      // 可选择输入权重
      cout << "权重 (默认1，直接回车跳过): ";
      string input;
      cin.ignore();
      getline(cin, input);
      if (!input.empty()) {
        weight = stoi(input);
      }

      g.addEdge(from, to, weight);
    }

    g.printGraphInfo();
    g.printAdjMatrix();
    g.printAdjList();
  }

  cout << "\n=== 两种表示方法的比较 ===" << endl;
  cout << "1. 邻接矩阵:" << endl;
  cout << "   - 空间复杂度: O(V²)" << endl;
  cout << "   - 查找边: O(1)" << endl;
  cout << "   - 添加/删除边: O(1)" << endl;
  cout << "   - 适用场景: 稠密图，需要频繁查询边的存在性" << endl;

  cout << "\n2. 邻接表:" << endl;
  cout << "   - 空间复杂度: O(V+E)" << endl;
  cout << "   - 查找边: O(degree(v))" << endl;
  cout << "   - 遍历邻接点: O(degree(v))" << endl;
  cout << "   - 适用场景: 稀疏图，需要频繁遍历邻接点" << endl;

  return 0;
}
