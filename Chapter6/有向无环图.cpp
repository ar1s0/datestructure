// 有向无环图的实现
#include <bits/stdc++.h>
using namespace std;

// DAG类封装
class DAG {
public:
  struct Node {
    string val;
    vector<Node *> children;
    int id;
    Node(string v, int i) : val(v), id(i) {}
  };

  map<string, Node *> nodeMap;
  int nodeId = 0;
  Node *root = nullptr;

  ~DAG() {
    for (auto &kv : nodeMap)
      delete kv.second;
  }

  Node *build(string expr) {
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
    if (nodeMap.count(expr))
      return nodeMap[expr];
    // 括号去除
    if (expr.size() >= 2 && expr.front() == '(' && expr.back() == ')') {
      int cnt = 0, ok = 1;
      for (int i = 0; i < expr.size(); ++i) {
        if (expr[i] == '(')
          cnt++;
        if (expr[i] == ')')
          cnt--;
        if (cnt == 0 && i != expr.size() - 1)
          ok = 0;
      }
      if (ok)
        expr = expr.substr(1, expr.size() - 2);
    }
    // 运算符优先级：先乘后加
    int pos = -1, par = 0;
    for (int i = expr.size() - 1; i >= 0; --i) {
      if (expr[i] == ')')
        par++;
      if (expr[i] == '(')
        par--;
      if (par == 0 && expr[i] == '+') {
        pos = i;
        break;
      }
    }
    if (pos == -1) {
      par = 0;
      for (int i = expr.size() - 1; i >= 0; --i) {
        if (expr[i] == ')')
          par++;
        if (expr[i] == '(')
          par--;
        if (par == 0 && expr[i] == '*') {
          pos = i;
          break;
        }
      }
    }
    Node *node = new Node(expr, nodeId++);
    if (pos != -1) {
      string left = expr.substr(0, pos);
      string right = expr.substr(pos + 1);
      node->val = string(1, expr[pos]);
      node->children.push_back(build(left));
      node->children.push_back(build(right));
    }
    nodeMap[expr] = node;
    return node;
  }

  void print(Node *node, int depth = 0) {
    for (int i = 0; i < depth; ++i)
      cout << "  ";
    cout << "Node[" << node->id << "]: " << node->val << "\n";
    for (auto *child : node->children)
      print(child, depth + 1);
  }

  void printAllNodes() {
    cout << "\n所有唯一子表达式节点:\n";
    for (auto &kv : nodeMap) {
      cout << "id=" << kv.second->id << ", expr=" << kv.first << "\n";
    }
  }
};

int main() {
  string input = "(A+B)*(A+B)*C";
  DAG dag;
  dag.root = dag.build(input);
  cout << "表达式: " << input << "\nDAG结构如下:\n";
  dag.print(dag.root);
  dag.printAllNodes();
  return 0;
}