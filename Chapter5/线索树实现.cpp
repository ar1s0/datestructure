#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  struct Node *left, *right;
  bool ltag, rtag; // 左右线索标志
};

class ThreadedBinaryTree {
public:
  Node *root;
  ThreadedBinaryTree() : root(nullptr) {}
  void createNode(Node *&node, int data) {
    node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    node->ltag = node->rtag = false;
  }
  void insert(Node *&node, int data) {
    if (!node) {
      createNode(node, data);
      return;
    }
    if (data < node->data) {
      insert(node->left, data);
    } else {
      insert(node->right, data);
    }
  }
  void createTree(const vector<int> &values) {
    for (int value : values) {
      insert(root, value);
    }
    // 创建线索化
    Node *pre = nullptr;
    threadInorder(root, pre);
    if (pre) {
      pre->right = nullptr; // 最后一个节点的右线索指向nullptr
      pre->rtag = true;     // 标记为右线索
    }
  }
  void threadInorder(Node *node, Node *&pre) {
    if (!node)
      return;
    threadInorder(node->left, pre);
    if (!node->left) {
      node->ltag = true;
      node->left = pre; // 左线索指向前驱
    }
    if (pre && !pre->right) {
      pre->rtag = true;
      pre->right = node; // 右线索指向当前节点
    }
    pre = node; // 更新前驱节点
    threadInorder(node->right, pre);
  }

  void inorderTraversal(Node *node) {
    while (node) {
      while (node->ltag == false) {
        node = node->left; // 找到最左节点
      }
      printf("%d ", node->data);
      while (node->rtag == true && node->right) {
        node = node->right; // 遍历右线索
        printf("%d ", node->data);
      }
      node = node->right; // 移动到下一个节点
    }
  }
};

int main() {
  ThreadedBinaryTree tbt;
  vector<int> values = {50, 30, 70, 20, 40, 60, 80, 90};
  tbt.createTree(values);
  printf("Threaded Binary Tree created with values: ");
  tbt.inorderTraversal(tbt.root);
  printf("\n");
  return 0;
}