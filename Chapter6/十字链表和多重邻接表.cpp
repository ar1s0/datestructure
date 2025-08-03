#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==============================================
// 十字链表实现（用于有向图）
// ==============================================

// 十字链表的边结点结构
struct CrossListEdge {
  int tail, head;       // 弧的尾和头顶点
  CrossListEdge *hlink; // 指向头相同的下一条弧
  CrossListEdge *tlink; // 指向尾相同的下一条弧
  int weight;           // 边的权重（可选）

  CrossListEdge(int t, int h, int w = 1)
      : tail(t), head(h), weight(w), hlink(nullptr), tlink(nullptr) {}
};

// 十字链表的顶点结构
struct CrossListVertex {
  string data;             // 顶点数据
  CrossListEdge *firstin;  // 第一条入弧
  CrossListEdge *firstout; // 第一条出弧

  CrossListVertex(string d = "")
      : data(d), firstin(nullptr), firstout(nullptr) {}
};

// 十字链表图类
class CrossListGraph {
private:
  vector<CrossListVertex> vertices;
  int vexnum, arcnum; // 顶点数和弧数

public:
  CrossListGraph(int n) : vexnum(n), arcnum(0) { vertices.resize(n); }

  // 设置顶点数据
  void setVertexData(int index, string data) {
    if (index >= 0 && index < vexnum) {
      vertices[index].data = data;
    }
  }

  // 添加有向边
  void addArc(int tail, int head, int weight = 1) {
    if (tail < 0 || tail >= vexnum || head < 0 || head >= vexnum) {
      cout << "顶点索引超出范围！" << endl;
      return;
    }

    CrossListEdge *newEdge = new CrossListEdge(tail, head, weight);

    // 插入到tail顶点的出弧链表头部
    newEdge->tlink = vertices[tail].firstout;
    vertices[tail].firstout = newEdge;

    // 插入到head顶点的入弧链表头部
    newEdge->hlink = vertices[head].firstin;
    vertices[head].firstin = newEdge;

    arcnum++;
    cout << "添加弧: " << vertices[tail].data << " -> " << vertices[head].data
         << " (权重: " << weight << ")" << endl;
  }

  // 打印图的十字链表表示
  void printCrossList() {
    cout << "\n=== 十字链表表示 ===" << endl;

    for (int i = 0; i < vexnum; i++) {
      cout << "顶点 " << i << "(" << vertices[i].data << "):" << endl;

      // 打印出弧
      cout << "  出弧: ";
      CrossListEdge *p = vertices[i].firstout;
      if (!p) {
        cout << "无";
      } else {
        while (p) {
          cout << "-> " << vertices[p->head].data << "(" << p->weight << ") ";
          p = p->tlink;
        }
      }
      cout << endl;

      // 打印入弧
      cout << "  入弧: ";
      p = vertices[i].firstin;
      if (!p) {
        cout << "无";
      } else {
        while (p) {
          cout << "<- " << vertices[p->tail].data << "(" << p->weight << ") ";
          p = p->hlink;
        }
      }
      cout << endl << endl;
    }
  }

  // 计算顶点的入度
  int getInDegree(int vertex) {
    if (vertex < 0 || vertex >= vexnum)
      return -1;

    int count = 0;
    CrossListEdge *p = vertices[vertex].firstin;
    while (p) {
      count++;
      p = p->hlink;
    }
    return count;
  }

  // 计算顶点的出度
  int getOutDegree(int vertex) {
    if (vertex < 0 || vertex >= vexnum)
      return -1;

    int count = 0;
    CrossListEdge *p = vertices[vertex].firstout;
    while (p) {
      count++;
      p = p->tlink;
    }
    return count;
  }

  ~CrossListGraph() {
    // 释放所有边结点
    for (int i = 0; i < vexnum; i++) {
      CrossListEdge *p = vertices[i].firstout;
      while (p) {
        CrossListEdge *temp = p;
        p = p->tlink;
        delete temp;
      }
    }
  }
};

// ==============================================
// 多重邻接表实现（用于无向图）
// ==============================================

// 多重邻接表的边结点结构
struct MultiEdge {
  bool mark;        // 访问标记
  int ivex, jvex;   // 边依附的两个顶点
  MultiEdge *ilink; // 指向下一条依附于ivex的边
  MultiEdge *jlink; // 指向下一条依附于jvex的边
  int weight;       // 边的权重

  MultiEdge(int i, int j, int w = 1)
      : mark(false), ivex(i), jvex(j), weight(w), ilink(nullptr),
        jlink(nullptr) {}
};

// 多重邻接表的顶点结构
struct MultiVertex {
  string data;          // 顶点数据
  MultiEdge *firstedge; // 指向第一条边

  MultiVertex(string d = "") : data(d), firstedge(nullptr) {}
};

// 多重邻接表图类
class MultiAdjGraph {
private:
  vector<MultiVertex> vertices;
  int vexnum, edgenum; // 顶点数和边数

public:
  MultiAdjGraph(int n) : vexnum(n), edgenum(0) { vertices.resize(n); }

  // 设置顶点数据
  void setVertexData(int index, string data) {
    if (index >= 0 && index < vexnum) {
      vertices[index].data = data;
    }
  }

  // 添加无向边
  void addEdge(int i, int j, int weight = 1) {
    if (i < 0 || i >= vexnum || j < 0 || j >= vexnum) {
      cout << "顶点索引超出范围！" << endl;
      return;
    }

    MultiEdge *newEdge = new MultiEdge(i, j, weight);

    // 将边插入到顶点i的边链表中
    newEdge->ilink = vertices[i].firstedge;
    vertices[i].firstedge = newEdge;

    // 将边插入到顶点j的边链表中
    newEdge->jlink = vertices[j].firstedge;
    vertices[j].firstedge = newEdge;

    edgenum++;
    cout << "添加边: " << vertices[i].data << " - " << vertices[j].data
         << " (权重: " << weight << ")" << endl;
  }

  // 打印图的多重邻接表表示
  void printMultiAdjList() {
    cout << "\n=== 多重邻接表表示 ===" << endl;

    for (int i = 0; i < vexnum; i++) {
      cout << "顶点 " << i << "(" << vertices[i].data << "): ";

      MultiEdge *p = vertices[i].firstedge;
      if (!p) {
        cout << "无邻接边";
      } else {
        while (p) {
          // 确定另一个顶点
          int other = (p->ivex == i) ? p->jvex : p->ivex;
          cout << vertices[other].data << "(" << p->weight << ") ";

          // 移动到下一条边
          p = (p->ivex == i) ? p->ilink : p->jlink;
        }
      }
      cout << endl;
    }
  }

  // 计算顶点的度数
  int getDegree(int vertex) {
    if (vertex < 0 || vertex >= vexnum)
      return -1;

    int count = 0;
    MultiEdge *p = vertices[vertex].firstedge;
    while (p) {
      count++;
      p = (p->ivex == vertex) ? p->ilink : p->jlink;
    }
    return count;
  }

  // 深度优先搜索
  void DFS(int start, vector<bool> &visited) {
    visited[start] = true;
    cout << vertices[start].data << " ";

    MultiEdge *p = vertices[start].firstedge;
    while (p) {
      int other = (p->ivex == start) ? p->jvex : p->ivex;
      if (!visited[other]) {
        DFS(other, visited);
      }
      p = (p->ivex == start) ? p->ilink : p->jlink;
    }
  }

  // 深度优先遍历
  void DFSTraverse() {
    vector<bool> visited(vexnum, false);
    cout << "\n深度优先遍历: ";
    for (int i = 0; i < vexnum; i++) {
      if (!visited[i]) {
        DFS(i, visited);
      }
    }
    cout << endl;
  }

  ~MultiAdjGraph() {
    // 释放所有边结点
    vector<bool> deleted(edgenum, false);
    for (int i = 0; i < vexnum; i++) {
      MultiEdge *p = vertices[i].firstedge;
      while (p) {
        MultiEdge *temp = p;
        p = (p->ivex == i) ? p->ilink : p->jlink;
        if (!temp->mark) {
          temp->mark = true; // 标记为已删除
          delete temp;
        }
      }
    }
  }
};

// ==============================================
// 测试函数
// ==============================================

void testCrossListGraph() {
  cout << "========== 十字链表测试 ==========" << endl;

  // 创建有向图
  CrossListGraph graph(4);

  // 设置顶点数据
  graph.setVertexData(0, "A");
  graph.setVertexData(1, "B");
  graph.setVertexData(2, "C");
  graph.setVertexData(3, "D");

  // 添加有向边
  graph.addArc(0, 1, 5); // A -> B
  graph.addArc(0, 2, 3); // A -> C
  graph.addArc(1, 2, 2); // B -> C
  graph.addArc(1, 3, 4); // B -> D
  graph.addArc(2, 3, 1); // C -> D

  // 打印十字链表
  graph.printCrossList();

  // 打印度数信息
  cout << "=== 度数信息 ===" << endl;
  for (int i = 0; i < 4; i++) {
    cout << "顶点 " << i << " 入度: " << graph.getInDegree(i)
         << ", 出度: " << graph.getOutDegree(i) << endl;
  }
}

void testMultiAdjGraph() {
  cout << "\n\n========== 多重邻接表测试 ==========" << endl;

  // 创建无向图
  MultiAdjGraph graph(5);

  // 设置顶点数据
  graph.setVertexData(0, "V0");
  graph.setVertexData(1, "V1");
  graph.setVertexData(2, "V2");
  graph.setVertexData(3, "V3");
  graph.setVertexData(4, "V4");

  // 添加无向边
  graph.addEdge(0, 1, 2); // V0 - V1
  graph.addEdge(0, 2, 4); // V0 - V2
  graph.addEdge(1, 2, 1); // V1 - V2
  graph.addEdge(1, 3, 3); // V1 - V3
  graph.addEdge(2, 3, 5); // V2 - V3
  graph.addEdge(2, 4, 2); // V2 - V4
  graph.addEdge(3, 4, 1); // V3 - V4

  // 打印多重邻接表
  graph.printMultiAdjList();

  // 打印度数信息
  cout << "\n=== 度数信息 ===" << endl;
  for (int i = 0; i < 5; i++) {
    cout << "顶点 " << i << " 度数: " << graph.getDegree(i) << endl;
  }

  // 深度优先遍历
  graph.DFSTraverse();
}

int main() {
  // 测试十字链表
  testCrossListGraph();

  // 测试多重邻接表
  testMultiAdjGraph();

  return 0;
}
