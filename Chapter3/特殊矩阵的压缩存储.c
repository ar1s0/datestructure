#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// 给出 对称矩阵 上三角 下三角 三对角 矩阵 的一维存储
// 使用二维数组实现

int symmetricMatrix[5][5] = {{1, 2, 3, 4, 5},
                             {2, 6, 7, 8, 9},
                             {3, 7, 10, 11, 12},
                             {4, 8, 11, 13, 14},
                             {5, 9, 12, 14, 15}}; // 对称矩阵

int upperTriangularMatrix[5][5] = {{1, 2, 3, 4, 5},
                                   {0, 6, 7, 8, 9},
                                   {0, 0, 10, 11, 12},
                                   {0, 0, 0, 13, 14},
                                   {0, 0, 0, 0, 15}}; // 上三角矩阵

int lowerTriangularMatrix[5][5] = {{1, 0, 0, 0, 0},
                                   {2, 6, 0, 0, 0},
                                   {3, 7, 10, 0, 0},
                                   {4, 8, 11, 13, 0},
                                   {5, 9, 12, 14, 15}}; // 下三角矩阵

int tridiagonalMatrix[5][5] = {{1, 2, 0, 0, 0},
                               {2, 6, 7, 0, 0},
                               {0, 7, 10, 11, 0},
                               {0, 0, 11, 13, 14},
                               {0, 0, 0, 14, 15}}; // 三对角矩阵

bool symmetricMatrixCompressed(int *compressed, int rows, int cols) {
  int index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i <= j) { // 只存储上三角部分
        compressed[index++] = symmetricMatrix[i][j];
      }
    }
  }
  return true;
}

bool upperTriangularMatrixCompressed(int *compressed, int rows, int cols) {
  int index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i <= j) { // 只存储上三角部分
        compressed[index++] = upperTriangularMatrix[i][j];
      }
    }
  }
  return true;
}

bool lowerTriangularMatrixCompressed(int *compressed, int rows, int cols) {
  int index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i >= j) { // 只存储下三角部分
        compressed[index++] = lowerTriangularMatrix[i][j];
      }
    }
  }
  return true;
}

bool tridiagonalMatrixCompressed(int *compressed, int rows, int cols) {
  int index = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == j || i == j - 1 || i == j + 1) { // 存储对角线及其上下对角线
        compressed[index++] = tridiagonalMatrix[i][j];
      }
    }
  }
  return true;
}

void printCompressed(int *compressed, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", compressed[i]);
  }
  printf("\n");
}

void testCompressedMatrices() {
  int compressed[15]; // 假设最大压缩大小为15

  printf("Compressed Symmetric Matrix: ");
  if (symmetricMatrixCompressed(compressed, 5, 5)) {
    printCompressed(compressed, 15);
  }

  printf("Compressed Upper Triangular Matrix: ");
  if (upperTriangularMatrixCompressed(compressed, 5, 5)) {
    printCompressed(compressed, 15);
  }

  printf("Compressed Lower Triangular Matrix: ");
  if (lowerTriangularMatrixCompressed(compressed, 5, 5)) {
    printCompressed(compressed, 15);
  }

  printf("Compressed Tridiagonal Matrix: ");
  if (tridiagonalMatrixCompressed(compressed, 5, 5)) {
    printCompressed(compressed, 15);
  }
}

// 实现稀疏矩阵的 十字链表
typedef struct SparseElement {
  int row;                     // 行索引
  int col;                     // 列索引
  int value;                   // 值
  struct SparseElement *right; // 指向右侧元素的指针
  struct SparseElement *down;  // 指向下方元素的指针
} SparseElement;

int sparseMatrix[5][5] = {{0, 0, 3, 0, 0},
                          {0, 0, 0, 4, 0},
                          {5, 0, 0, 0, 6},
                          {0, 7, 0, 0, 0},
                          {0, 0, 8, 9, 0}}; // 稀疏矩阵

// 十字链表头节点结构
typedef struct CrossListHeader {
  SparseElement **rowHeaders; // 行头指针数组
  SparseElement **colHeaders; // 列头指针数组
  int rows;                   // 行数
  int cols;                   // 列数
  int nonZeroCount;           // 非零元素个数
} CrossListHeader;

// 创建十字链表头节点
CrossListHeader *createCrossListHeader(int rows, int cols) {
  CrossListHeader *header = (CrossListHeader *)malloc(sizeof(CrossListHeader));
  if (!header)
    return NULL;

  header->rows = rows;
  header->cols = cols;
  header->nonZeroCount = 0;

  // 初始化行头指针数组
  header->rowHeaders = (SparseElement **)calloc(rows, sizeof(SparseElement *));
  // 初始化列头指针数组
  header->colHeaders = (SparseElement **)calloc(cols, sizeof(SparseElement *));

  if (!header->rowHeaders || !header->colHeaders) {
    free(header->rowHeaders);
    free(header->colHeaders);
    free(header);
    return NULL;
  }

  return header;
}

// 创建稀疏矩阵元素节点
SparseElement *createSparseElement(int row, int col, int value) {
  SparseElement *element = (SparseElement *)malloc(sizeof(SparseElement));
  if (!element)
    return NULL;

  element->row = row;
  element->col = col;
  element->value = value;
  element->right = NULL;
  element->down = NULL;

  return element;
}

// 将稀疏矩阵压缩为十字链表
CrossListHeader *sparseMatrixCompressed(int matrix[][5], int rows, int cols) {
  CrossListHeader *header = createCrossListHeader(rows, cols);
  if (!header)
    return NULL;

  // 遍历矩阵，找到非零元素
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (matrix[i][j] != 0) {
        // 创建新节点
        SparseElement *newElement = createSparseElement(i, j, matrix[i][j]);
        if (!newElement)
          continue;

        header->nonZeroCount++;

        // 插入到行链表中（按列索引升序）
        if (header->rowHeaders[i] == NULL || header->rowHeaders[i]->col > j) {
          // 插入到行链表头部
          newElement->right = header->rowHeaders[i];
          header->rowHeaders[i] = newElement;
        } else {
          // 找到合适位置插入
          SparseElement *current = header->rowHeaders[i];
          while (current->right != NULL && current->right->col < j) {
            current = current->right;
          }
          newElement->right = current->right;
          current->right = newElement;
        }

        // 插入到列链表中（按行索引升序）
        if (header->colHeaders[j] == NULL || header->colHeaders[j]->row > i) {
          // 插入到列链表头部
          newElement->down = header->colHeaders[j];
          header->colHeaders[j] = newElement;
        } else {
          // 找到合适位置插入
          SparseElement *current = header->colHeaders[j];
          while (current->down != NULL && current->down->row < i) {
            current = current->down;
          }
          newElement->down = current->down;
          current->down = newElement;
        }
      }
    }
  }

  return header;
}

// 按行打印十字链表
void printCrossListByRows(CrossListHeader *header) {
  if (!header) {
    printf("Cross list is empty!\n");
    return;
  }

  printf("Cross List Matrix (%dx%d, %d non-zero elements):\n", header->rows,
         header->cols, header->nonZeroCount);
  printf("Row-wise traversal:\n");

  for (int i = 0; i < header->rows; i++) {
    printf("Row %d: ", i);
    SparseElement *current = header->rowHeaders[i];
    while (current != NULL) {
      printf("(%d,%d,%d) ", current->row, current->col, current->value);
      current = current->right;
    }
    printf("\n");
  }
}

// 按列打印十字链表
void printCrossListByCols(CrossListHeader *header) {
  if (!header) {
    printf("Cross list is empty!\n");
    return;
  }

  printf("Column-wise traversal:\n");
  for (int j = 0; j < header->cols; j++) {
    printf("Col %d: ", j);
    SparseElement *current = header->colHeaders[j];
    while (current != NULL) {
      printf("(%d,%d,%d) ", current->row, current->col, current->value);
      current = current->down;
    }
    printf("\n");
  }
}

// 释放十字链表内存
void freeCrossList(CrossListHeader *header) {
  if (!header)
    return;

  // 通过行链表释放所有节点
  for (int i = 0; i < header->rows; i++) {
    SparseElement *current = header->rowHeaders[i];
    while (current != NULL) {
      SparseElement *temp = current;
      current = current->right;
      free(temp);
    }
  }

  free(header->rowHeaders);
  free(header->colHeaders);
  free(header);
}

// 测试函数
void testCrossList() {
  printf("\n=== Testing Cross List Implementation ===\n");

  CrossListHeader *crossList = sparseMatrixCompressed(sparseMatrix, 5, 5);
  if (crossList) {
    printCrossListByRows(crossList);
    printf("\n");
    printCrossListByCols(crossList);
    freeCrossList(crossList);
  } else {
    printf("Failed to create cross list!\n");
  }
}

int main() {
  testCompressedMatrices();
  testCrossList();
  return 0;
}