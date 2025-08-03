#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;
} Node;

Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node *buildTree(int *preorder, int *inorder, int start, int end) {
  static int preIndex = 0;
  if (start > end)
    return NULL;

  Node *node = createNode(preorder[preIndex++]);
  if (start == end)
    return node;

  int inIndex;
  for (inIndex = start; inIndex <= end; inIndex++) {
    if (inorder[inIndex] == node->data)
      break;
  }

  node->left = buildTree(preorder, inorder, start, inIndex - 1);
  node->right = buildTree(preorder, inorder, inIndex + 1, end);

  return node;
}

void printTree(Node *node) {
  queue<Node *> q;
  if (node == NULL)
    return;
  q.push(node);
  while (!q.empty()) {
    Node *current = q.front();
    q.pop();
    printf("%d ", current->data);
    if (current->left != NULL)
      q.push(current->left);
    if (current->right != NULL)
      q.push(current->right);
  }
}

int main() {
  int preorder[] = {1, 2, 4, 5, 3};
  int inorder[] = {4, 2, 5, 1, 3};
  Node *root = buildTree(preorder, inorder, 0, 4);
  printf("In-order traversal of the constructed tree: ");
  printTree(root);
  printf("\n");
  return 0;
}