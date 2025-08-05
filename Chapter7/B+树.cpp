#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int DEGREE = 3; // B+树阶数（最小2）

// 前向声明
template <typename T> class BPlusTree;

template <typename T> class BPlusNode {
public:
  bool isLeaf;
  vector<T> keys;
  vector<BPlusNode<T> *> children;
  BPlusNode<T> *next; // 用于叶子节点链表

  BPlusNode(bool leaf = false) {
    isLeaf = leaf;
    next = nullptr;
  }

  friend class BPlusTree<T>;
};

template <typename T> class BPlusTree {
private:
  BPlusNode<T> *root;

  void insertInternal(const T &key, BPlusNode<T> *node, BPlusNode<T> *child);
  void traverseLeafLevel();

public:
  BPlusTree() { root = new BPlusNode<T>(true); }

  void insert(const T &key);
  void search(const T &key);
  void print();
};

template <typename T> void BPlusTree<T>::insert(const T &key) {
  BPlusNode<T> *node = root;

  // 如果根是叶子
  if (node->isLeaf) {
    // 插入到合适位置
    node->keys.insert(lower_bound(node->keys.begin(), node->keys.end(), key),
                      key);

    if (node->keys.size() >= DEGREE) {
      // 需要分裂
      BPlusNode<T> *newLeaf = new BPlusNode<T>(true);
      int mid = (DEGREE + 1) / 2;
      newLeaf->keys.assign(node->keys.begin() + mid, node->keys.end());
      node->keys.resize(mid);

      // 更新链表
      newLeaf->next = node->next;
      node->next = newLeaf;

      // 创建新根或插入父节点
      if (node == root) {
        BPlusNode<T> *newRoot = new BPlusNode<T>(false);
        newRoot->keys.push_back(newLeaf->keys[0]);
        newRoot->children.push_back(node);
        newRoot->children.push_back(newLeaf);
        root = newRoot;
      } else {
        insertInternal(newLeaf->keys[0], root, newLeaf);
      }
    }
    return;
  }

  // 如果根不是叶子，查找插入位置
  vector<BPlusNode<T> *> path;
  while (!node->isLeaf) {
    path.push_back(node);
    int i = upper_bound(node->keys.begin(), node->keys.end(), key) -
            node->keys.begin();
    node = node->children[i];
  }

  // 插入
  node->keys.insert(lower_bound(node->keys.begin(), node->keys.end(), key),
                    key);

  if (node->keys.size() >= DEGREE) {
    BPlusNode<T> *newLeaf = new BPlusNode<T>(true);
    int mid = (DEGREE + 1) / 2;
    newLeaf->keys.assign(node->keys.begin() + mid, node->keys.end());
    node->keys.resize(mid);

    newLeaf->next = node->next;
    node->next = newLeaf;

    // 向上传递分裂
    BPlusNode<T> *parent = path.back();
    insertInternal(newLeaf->keys[0], parent, newLeaf);
  }
}

template <typename T>
void BPlusTree<T>::insertInternal(const T &key, BPlusNode<T> *node,
                                  BPlusNode<T> *child) {
  // 找到插入位置
  int i = upper_bound(node->keys.begin(), node->keys.end(), key) -
          node->keys.begin();
  node->keys.insert(node->keys.begin() + i, key);
  node->children.insert(node->children.begin() + i + 1, child);

  if (node->keys.size() >= DEGREE) {
    int mid = (DEGREE + 1) / 2;
    T upKey = node->keys[mid];

    // 新建内部节点
    BPlusNode<T> *newInternal = new BPlusNode<T>(false);
    newInternal->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
    newInternal->children.assign(node->children.begin() + mid + 1,
                                 node->children.end());

    node->keys.resize(mid);
    node->children.resize(mid + 1);

    if (node == root) {
      BPlusNode<T> *newRoot = new BPlusNode<T>(false);
      newRoot->keys.push_back(upKey);
      newRoot->children.push_back(node);
      newRoot->children.push_back(newInternal);
      root = newRoot;
    } else {
      insertInternal(upKey, root, newInternal);
    }
  }
}

template <typename T> void BPlusTree<T>::search(const T &key) {
  BPlusNode<T> *node = root;
  while (!node->isLeaf) {
    int i = upper_bound(node->keys.begin(), node->keys.end(), key) -
            node->keys.begin();
    node = node->children[i];
  }

  if (find(node->keys.begin(), node->keys.end(), key) != node->keys.end()) {
    cout << "Found key: " << key << endl;
  } else {
    cout << "Key not found: " << key << endl;
  }
}

template <typename T> void BPlusTree<T>::print() {
  cout << "Leaf level traversal:" << endl;
  traverseLeafLevel();
}

template <typename T> void BPlusTree<T>::traverseLeafLevel() {
  BPlusNode<T> *node = root;
  while (!node->isLeaf) {
    node = node->children[0];
  }

  while (node) {
    for (const auto &key : node->keys) {
      cout << key << " ";
    }
    node = node->next;
  }
  cout << endl;
}

int main() {
  BPlusTree<int> bpt;
  bpt.insert(10);
  bpt.insert(20);
  bpt.insert(5);
  bpt.insert(6);
  bpt.insert(12);
  bpt.insert(30);
  bpt.insert(7);
  bpt.insert(17);

  bpt.print();

  bpt.search(6);
  bpt.search(15);

  return 0;
}
