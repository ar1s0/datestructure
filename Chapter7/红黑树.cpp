#include <fstream>
#include <iostream>

using namespace std;

enum Color { RED, BLACK };

template <typename T> struct Node {
  T data;
  Color color;
  Node *left, *right, *parent;

  Node(T data)
      : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {
  }
};

template <typename T> class RedBlackTree {
private:
  Node<T> *root;
  Node<T> *NIL;

  void leftRotate(Node<T> *x) {
    Node<T> *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
      y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NIL)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node<T> *y) {
    Node<T> *x = y->left;
    y->left = x->right;
    if (x->right != NIL)
      x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NIL)
      root = x;
    else if (y == y->parent->right)
      y->parent->right = x;
    else
      y->parent->left = x;

    x->right = y;
    y->parent = x;
  }

  void insertFix(Node<T> *z) {
    while (z->parent->color == RED) {
      if (z->parent == z->parent->parent->left) {
        Node<T> *y = z->parent->parent->right;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->right) {
            z = z->parent;
            leftRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          rightRotate(z->parent->parent);
        }
      } else {
        Node<T> *y = z->parent->parent->left;
        if (y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        } else {
          if (z == z->parent->left) {
            z = z->parent;
            rightRotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          leftRotate(z->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

public:
  RedBlackTree() {
    NIL = new Node<T>(0);
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
    root = NIL;
  }

  void insert(T data) {
    Node<T> *z = new Node<T>(data);
    z->left = z->right = z->parent = NIL;

    Node<T> *y = NIL;
    Node<T> *x = root;

    while (x != NIL) {
      y = x;
      if (z->data < x->data)
        x = x->left;
      else
        x = x->right;
    }

    z->parent = y;
    if (y == NIL)
      root = z;
    else if (z->data < y->data)
      y->left = z;
    else
      y->right = z;

    z->color = RED;
    insertFix(z);
  }

  void inorderHelper(Node<T> *node) {
    if (node != NIL) {
      inorderHelper(node->left);
      cout << node->data << "(" << (node->color == RED ? "R" : "B") << ") ";
      inorderHelper(node->right);
    }
  }

  void inorder() {
    inorderHelper(root);
    cout << endl;
  }

  Node<T> *getRoot() { return root; }

  Node<T> *search(T key) {
    Node<T> *current = root;
    while (current != NIL && current->data != key) {
      if (key < current->data)
        current = current->left;
      else
        current = current->right;
    }
    return current != NIL ? current : nullptr;
  }

  void exportToDot(const std::string &filename) {
    std::ofstream fout(filename);
    fout << "digraph RedBlackTree {\n";
    fout << "    node [shape=circle, style=filled, fontname=\"Arial\"];\n";
    if (root != NIL)
      exportDotHelper(root, fout);
    fout << "}\n";
    fout.close();
    std::cout << "Graph exported to " << filename << std::endl;
  }

  void exportDotHelper(Node<T> *node, std::ofstream &fout) {
    if (node == NIL)
      return;

    fout << "    \"" << node << "\" [label=\"" << node->data
         << "\", fillcolor=" << (node->color == RED ? "red" : "black")
         << ", fontcolor=" << (node->color == RED ? "black" : "white")
         << "];\n";

    if (node->left != NIL) {
      fout << "    \"" << node << "\" -> \"" << node->left << "\";\n";
      exportDotHelper(node->left, fout);
    } else {

      static int nilCount = 0;
      fout << "    nil" << nilCount << " [shape=point];\n";
      fout << "    \"" << node << "\" -> nil" << nilCount++ << ";\n";
    }

    if (node->right != NIL) {
      fout << "    \"" << node << "\" -> \"" << node->right << "\";\n";
      exportDotHelper(node->right, fout);
    } else {
      static int nilCount = 1000;
      fout << "    nil" << nilCount << " [shape=point];\n";
      fout << "    \"" << node << "\" -> nil" << nilCount++ << ";\n";
    }
  }
};

int main() {
  RedBlackTree<int> rbt;
  rbt.insert(10);
  rbt.insert(20);
  rbt.insert(30);
  rbt.insert(15);
  rbt.insert(25);

  rbt.exportToDot("rbtree.dot");

  cout << "In-order traversal of red-black tree:" << endl;
  rbt.inorder();

  int val = 20;
  auto node = rbt.search(val);
  if (node)
    cout << "Found: " << node->data << endl;
  else
    cout << "Not found: " << val << endl;

  return 0;
}
