
#include <iostream>
#include <vector>
using namespace std;

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int partition(vector<int> &arr, int low, int high) {
  int pivot = arr[low];
  while (low < high) {
    while (low < high && arr[high] >= pivot)
      --high;
    arr[low] = arr[high];
    while (low < high && arr[low] <= pivot)
      ++low;
    arr[high] = arr[low];
  }
  arr[low] = pivot;
  return low;
}

void quickSort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}
int main() {
  vector<int> arr = {10, 7, 8, 9, 1, 5};
  cout << "原始数组: ";
  printArr(arr);
  quickSort(arr, 0, arr.size() - 1);
  cout << "快速排序结果: ";
  printArr(arr);
  return 0;
}
