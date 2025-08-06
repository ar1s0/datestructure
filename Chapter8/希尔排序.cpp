
#include <iostream>
#include <vector>
using namespace std;

void shellSort(vector<int> &arr) {
  int n = arr.size();
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; ++i) {
      int temp = arr[i];
      int j = i;
      while (j >= gap && arr[j - gap] > temp) {
        arr[j] = arr[j - gap];
        j -= gap;
      }
      arr[j] = temp;
    }
  }
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {23, 12, 1, 8, 34, 54, 2, 3};
  cout << "原始数组: ";
  printArr(arr);
  shellSort(arr);
  cout << "希尔排序结果: ";
  printArr(arr);
  return 0;
}
