#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== 数据结构定义 ====================
typedef struct TreeNode {
  int data;
  struct TreeNode *l, *r, *p;
} TreeNode;

typedef struct BinaryTree {
  TreeNode *root;
  int height;
  int size;
} BinaryTree;

// 队列节点结构，用于广度遍历
typedef struct QueueNode {
  TreeNode *data;
  struct QueueNode *next;
} QueueNode;

// 队列结构
typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
  int size;
} Queue;

// ==================== 全局变量 ====================
BinaryTree *tree;

// ==================== 队列操作函数 ====================
Queue *create_queue() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = q->rear = NULL;
  q->size = 0;
  return q;
}

void enqueue(Queue *q, TreeNode *node) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  newNode->data = node;
  newNode->next = NULL;

  if (q->rear == NULL) {
    q->front = q->rear = newNode;
  } else {
    q->rear->next = newNode;
    q->rear = newNode;
  }
  q->size++;
}

TreeNode *dequeue(Queue *q) {
  if (q->front == NULL)
    return NULL;

  QueueNode *temp = q->front;
  TreeNode *data = temp->data;
  q->front = q->front->next;

  if (q->front == NULL) {
    q->rear = NULL;
  }

  free(temp);
  q->size--;
  return data;
}

int is_empty(Queue *q) { return q->front == NULL; }

void destroy_queue(Queue *q) {
  while (!is_empty(q)) {
    dequeue(q);
  }
  free(q);
}

// ==================== 二叉树基本操作 ====================
void create_tree() {
  tree = (BinaryTree *)malloc(sizeof(BinaryTree));
  tree->root = NULL;
  tree->height = 0;
  tree->size = 0;
}

void insert_node(TreeNode *node, int value, int depth) {
  if (node == NULL)
    return;

  if (value < node->data) {
    if (node->l == NULL) {
      node->l = (TreeNode *)malloc(sizeof(TreeNode));
      node->l->data = value;
      node->l->l = node->l->r = NULL;
      node->l->p = node;
      tree->size++; // 增加树的大小
      return;
    } else {
      insert_node(node->l, value, depth + 1);
    }
  } else if (value > node->data) {
    if (node->r == NULL) {
      node->r = (TreeNode *)malloc(sizeof(TreeNode));
      node->r->data = value;
      node->r->l = node->r->r = NULL;
      node->r->p = node;
      tree->size++; // 增加树的大小
      return;
    } else {
      insert_node(node->r, value, depth + 1);
    }
  }
  // 如果value == node->data，不插入重复值
}

void insert(BinaryTree *tree, int value) {
  if (tree->root == NULL) {
    tree->root = (TreeNode *)malloc(sizeof(TreeNode));
    tree->root->data = value;
    tree->root->l = tree->root->r = tree->root->p = NULL;
    tree->size++;
    return;
  }
  insert_node(tree->root, value, 0);
}

void destroy_tree(TreeNode *node) {
  if (node == NULL)
    return;
  destroy_tree(node->l);
  destroy_tree(node->r);
  free(node);
}

// ==================== 遍历函数 ====================
void preorder(TreeNode *node) {
  if (node == NULL)
    return;
  printf("%d ", node->data);
  preorder(node->l);
  preorder(node->r);
}

// 广度遍历（层序遍历）打印树的结构
void breadth_first_traversal(TreeNode *root) {
  if (root == NULL) {
    printf("Tree is empty.\n");
    return;
  }

  Queue *q = create_queue();
  enqueue(q, root);

  // 使用特殊标记来分层 - 我们用-1作为层分隔符
  TreeNode *level_separator = (TreeNode *)malloc(sizeof(TreeNode));
  level_separator->data = -1; // 特殊标记值
  level_separator->l = level_separator->r = level_separator->p = NULL;
  enqueue(q, level_separator);

  int level = 0;
  printf("Level %d: ", level);

  while (!is_empty(q)) {
    TreeNode *current = dequeue(q);

    if (current->data == -1) {
      // 当前层结束
      printf("\n");
      if (!is_empty(q)) {
        level++;
        printf("Level %d: ", level);
        enqueue(q, level_separator); // 为下一层添加分隔符
      }
    } else {
      printf("%d ", current->data);

      // 将子节点加入队列
      if (current->l != NULL) {
        enqueue(q, current->l);
      }
      if (current->r != NULL) {
        enqueue(q, current->r);
      }
    }
  }

  free(level_separator);
  destroy_queue(q);
}

// 中序遍历
void inorder(TreeNode *node) {
  if (node == NULL)
    return;
  inorder(node->l);
  printf("%d ", node->data);
  inorder(node->r);
}

// 后序遍历
void postorder(TreeNode *node) {
  if (node == NULL)
    return;
  postorder(node->l);
  postorder(node->r);
  printf("%d ", node->data);
}

// ==================== 树结构可视化 ====================
// 打印树的结构（更直观的方式）
void print_tree_structure(TreeNode *root, int space) {
  const int COUNT = 4;
  if (root == NULL)
    return;

  space += COUNT;
  print_tree_structure(root->r, space);

  printf("\n");
  for (int i = COUNT; i < space; i++) {
    printf(" ");
  }
  printf("%d\n", root->data);

  print_tree_structure(root->l, space);
}

// ==================== 主函数 ====================
int main() {
  printf("=== 二叉搜索树演示程序 ===\n\n");

  // 创建树
  create_tree();

  // 插入节点
  printf("插入节点: 5, 3, 7, 2, 4, 6, 8\n");
  insert(tree, 5);
  insert(tree, 3);
  insert(tree, 7);
  insert(tree, 2);
  insert(tree, 4);
  insert(tree, 6);
  insert(tree, 8);

  printf("树的大小: %d\n\n", tree->size);

  // 各种遍历方式
  printf("前序遍历: ");
  preorder(tree->root);
  printf("\n");

  printf("中序遍历: ");
  inorder(tree->root);
  printf("\n");

  printf("后序遍历: ");
  postorder(tree->root);
  printf("\n\n");

  // 广度优先遍历（按层级显示）
  printf("广度优先遍历（按层级显示）:\n");
  breadth_first_traversal(tree->root);
  printf("\n");

  // 树的结构图
  printf("树的结构图（右子树在上，左子树在下）:\n");
  print_tree_structure(tree->root, 0);
  printf("\n");

  // 清理内存
  destroy_tree(tree->root);
  free(tree);

  printf("程序执行完毕！\n");
  return 0;
}
