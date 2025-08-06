
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define RUN 32

// 插入排序用于小块
void insertionSort(vector<int> &arr, int left, int right) {
  for (int i = left + 1; i <= right; ++i) {
    int temp = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > temp) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = temp;
  }
}

// 合并两个有序区间
void merge(vector<int> &arr, int l, int m, int r) {
  int len1 = m - l + 1, len2 = r - m;
  vector<int> left(arr.begin() + l, arr.begin() + m + 1);
  vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
  int i = 0, j = 0, k = l;
  while (i < len1 && j < len2) {
    if (left[i] <= right[j])
      arr[k++] = left[i++];
    else
      arr[k++] = right[j++];
  }
  while (i < len1)
    arr[k++] = left[i++];
  while (j < len2)
    arr[k++] = right[j++];
}

// TimSort主函数
void timSort(vector<int> &arr) {
  int n = arr.size();
  // 1. 对每个RUN块插入排序
  for (int i = 0; i < n; i += RUN)
    insertionSort(arr, i, min(i + RUN - 1, n - 1));
  // 2. 归并块
  for (int size = RUN; size < n; size = 2 * size) {
    for (int left = 0; left < n; left += 2 * size) {
      int mid = left + size - 1;
      int right = min(left + 2 * size - 1, n - 1);
      if (mid < right)
        merge(arr, left, mid, right);
    }
  }
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {5, 21, 7, 23, 19, 10, 12, 3, 2, 1, 0, 8, 6, 4};
  cout << "原始数组: ";
  printArr(arr);
  timSort(arr);
  cout << "TimSort排序结果: ";
  printArr(arr);
  return 0;
}
