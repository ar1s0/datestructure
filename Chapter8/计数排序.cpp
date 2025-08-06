
#include <iostream>
#include <vector>
using namespace std;

void countingSort(vector<int> &arr) {
  if (arr.empty())
    return;
  int minVal = arr[0], maxVal = arr[0];
  for (int v : arr) {
    if (v < minVal)
      minVal = v;
    if (v > maxVal)
      maxVal = v;
  }
  int range = maxVal - minVal + 1;
  vector<int> count(range, 0);
  for (int v : arr)
    count[v - minVal]++;
  for (int i = 1; i < count.size(); ++i)
    count[i] += count[i - 1];
  vector<int> output(arr.size());
  for (int i = arr.size() - 1; i >= 0; --i) {
    output[count[arr[i] - minVal] - 1] = arr[i];
    count[arr[i] - minVal]--;
  }
  arr = output;
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {4, -2, 2, 8, 3, 3, 1};
  cout << "原始数组: ";
  printArr(arr);
  countingSort(arr);
  cout << "计数排序结果: ";
  printArr(arr);
  return 0;
}
