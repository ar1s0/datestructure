#include <iostream>
#include <vector>
using namespace std;

// 普通插入排序
void insertionSort(vector<int> &arr) {
  int n = arr.size();
  for (int i = 1; i < n; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

// 二分查找优化的插入排序
void binaryInsertionSort(vector<int> &arr) {
  int n = arr.size();
  for (int i = 1; i < n; ++i) {
    int key = arr[i];
    int left = 0, right = i - 1;
    // 二分查找插入位置
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (arr[mid] > key)
        right = mid - 1;
      else
        left = mid + 1;
    }
    // 移动元素
    for (int j = i - 1; j >= left; --j)
      arr[j + 1] = arr[j];
    arr[left] = key;
  }
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr1 = {5, 2, 9, 1, 5, 6};
  vector<int> arr2 = arr1;
  printArr(arr1);

  insertionSort(arr1);
  printArr(arr1);

  binaryInsertionSort(arr2);
  cout << "二分插入排序结果: \n";
  printArr(arr2);
  return 0;
}
