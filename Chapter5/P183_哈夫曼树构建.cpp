#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef struct Node {
  int weight;
  struct Node *left, *right;
} Node;

// 创建新节点
Node *createNode(int weight) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->weight = weight;
  node->left = node->right = NULL;
  return node;
}

// 查找权值最小的节点下标
int findMin(Node *arr[], int n, int skip) {
  int minIdx = -1;
  for (int i = 0; i < n; ++i) {
    if (arr[i] && i != skip) {
      if (minIdx == -1 || arr[i]->weight < arr[minIdx]->weight)
        minIdx = i;
    }
  }
  return minIdx;
}

// 构建哈夫曼树
Node *buildHuffman(int weights[], int n) {
  Node *arr[N] = {0};
  for (int i = 0; i < n; ++i)
    arr[i] = createNode(weights[i]);
  int size = n;
  while (size > 1) {
    int i1 = findMin(arr, n, -1);
    int i2 = findMin(arr, n, i1);
    Node *merged = createNode(arr[i1]->weight + arr[i2]->weight);
    merged->left = arr[i1];
    merged->right = arr[i2];
    arr[i1] = merged;
    arr[i2] = NULL;
    --size;
  }
  // 返回根节点
  for (int i = 0; i < n; ++i)
    if (arr[i])
      return arr[i];
  return NULL;
}

// 先序遍历打印树
void preorder(Node *root) {
  if (!root)
    return;
  printf("%d ", root->weight);
  preorder(root->left);
  preorder(root->right);
}

// 层次遍历打印树
void levelOrder(Node *root) {
  if (!root)
    return;
  Node *queue[N];
  int front = 0, rear = 0;
  queue[rear++] = root;
  while (front < rear) {
    Node *node = queue[front++];
    printf("%d ", node->weight);
    if (node->left)
      queue[rear++] = node->left;
    if (node->right)
      queue[rear++] = node->right;
  }
}

int main() {
  int n, weights[N];
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &weights[i]);
  Node *root = buildHuffman(weights, n);
  preorder(root);
  printf("\n");
  levelOrder(root); // 添加层次遍历输出
  printf("\n");
  return 0;
}