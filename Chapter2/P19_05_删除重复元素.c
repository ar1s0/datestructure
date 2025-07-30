#include <stdio.h>

struct Array {
  int *data;
  int size;
};

void deleteRepeatElem(struct Array *arr) {
  int i = 0, j = 0;
  while (i < arr->size) {
    if (arr->data[i] != arr->data[j])
      arr->data[++j] = arr->data[i];
    ++i;
  }
  arr->size = j + 1;
}

void printArray(struct Array *arr) {
  for (int i = 0; i < arr->size; i++) {
    printf("%d ", arr->data[i]);
  }
  printf("\n");
}

int main() {
  int arr[8] = {10, 20, 20, 20, 30, 30, 40, 50};
  struct Array array = {arr, 8};
  // 定义一个整数数组
  printf("Original array: \t\t");
  printArray(&array);

  // 删除重复元素
  deleteRepeatElem(&array);
  printf("Deleting repeated elements: \t");
  printArray(&array);

  return 0;
}