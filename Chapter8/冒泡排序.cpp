
#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int> &arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (int j = 0; j < n - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {5, 1, 4, 2, 8};
  cout << "原始数组: ";
  printArr(arr);
  bubbleSort(arr);
  cout << "冒泡排序结果: ";
  printArr(arr);
  return 0;
}
