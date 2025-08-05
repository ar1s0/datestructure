#include <bits/stdc++.h>
using namespace std;

struct AVLNode {
  int key;
  int height;
  AVLNode *left, *right;
  AVLNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

int Height(AVLNode *node) { return node ? node->height : 0; }

int BalanceFactor(AVLNode *node) {
  return Height(node->left) - Height(node->right);
}

void UpdateHeight(AVLNode *node) {
  node->height = max(Height(node->left), Height(node->right)) + 1;
}

AVLNode *RightRotate(AVLNode *y) {
  AVLNode *x = y->left;
  y->left = x->right;
  x->right = y;
  UpdateHeight(y);
  UpdateHeight(x);
  return x;
}

AVLNode *LeftRotate(AVLNode *x) {
  AVLNode *y = x->right;
  x->right = y->left;
  y->left = x;
  UpdateHeight(x);
  UpdateHeight(y);
  return y;
}

AVLNode *Insert(AVLNode *node, int key) {
  if (!node)
    return new AVLNode(key);
  if (key < node->key)
    node->left = Insert(node->left, key);
  else if (key > node->key)
    node->right = Insert(node->right, key);
  else
    return node; // 不允许重复
  UpdateHeight(node);
  int bf = BalanceFactor(node);
  // LL型
  if (bf > 1 && key < node->left->key)
    return RightRotate(node);
  // RR型
  if (bf < -1 && key > node->right->key)
    return LeftRotate(node);
  // LR型
  if (bf > 1 && key > node->left->key) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  // RL型
  if (bf < -1 && key < node->right->key) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

AVLNode *FindMin(AVLNode *node) {
  while (node && node->left)
    node = node->left;
  return node;
}

AVLNode *Delete(AVLNode *node, int key) {
  if (!node)
    return nullptr;
  if (key < node->key)
    node->left = Delete(node->left, key);
  else if (key > node->key)
    node->right = Delete(node->right, key);
  else {
    // 找到节点
    if (!node->left || !node->right) {
      AVLNode *tmp = node->left ? node->left : node->right;
      delete node;
      return tmp;
    } else {
      AVLNode *succ = FindMin(node->right);
      node->key = succ->key;
      node->right = Delete(node->right, succ->key);
    }
  }
  UpdateHeight(node);
  int bf = BalanceFactor(node);
  // LL型
  if (bf > 1 && BalanceFactor(node->left) >= 0)
    return RightRotate(node);
  // LR型
  if (bf > 1 && BalanceFactor(node->left) < 0) {
    node->left = LeftRotate(node->left);
    return RightRotate(node);
  }
  // RR型
  if (bf < -1 && BalanceFactor(node->right) <= 0)
    return LeftRotate(node);
  // RL型
  if (bf < -1 && BalanceFactor(node->right) > 0) {
    node->right = RightRotate(node->right);
    return LeftRotate(node);
  }
  return node;
}

AVLNode *Search(AVLNode *node, int key) {
  if (!node || node->key == key)
    return node;
  if (key < node->key)
    return Search(node->left, key);
  else
    return Search(node->right, key);
}

void InOrder(AVLNode *node) {
  if (!node)
    return;
  InOrder(node->left);
  cout << node->key << " ";
  InOrder(node->right);
}

void bfs(AVLNode *node) {
  queue<AVLNode *> q;
  if (node)
    q.push(node);
  while (!q.empty()) {
    AVLNode *current = q.front();
    q.pop();
    cout << current->key << " ";
    if (current->left)
      q.push(current->left);
    if (current->right)
      q.push(current->right);
  }
}

int main() {
  AVLNode *root = nullptr;
  int arr[] = {10, 20, 30, 40, 50, 25};
  for (int k : arr) {
    root = Insert(root, k);
  }
  cout << "中序遍历: ";
  InOrder(root);
  cout << endl;
  cout << "层序遍历: ";
  bfs(root);
  cout << endl;
  int key = 25;
  AVLNode *found = Search(root, key);
  if (found)
    cout << "找到节点: " << found->key << endl;
  else
    cout << "未找到节点" << endl;
  // 删除节点演示
  cout << "删除30后: ";
  root = Delete(root, 30);
  InOrder(root);
  cout << endl;
  cout << "层序遍历: ";
  bfs(root);
  cout << endl;
  return 0;
}
