
#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int> &arr, int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < n && arr[l] > arr[largest])
    largest = l;
  if (r < n && arr[r] > arr[largest])
    largest = r;
  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

void buildHeap(vector<int> &arr) {
  int n = arr.size();
  for (int i = n / 2 - 1; i >= 0; --i)
    heapify(arr, n, i);
}

void insertHeap(vector<int> &arr, int value) {
  arr.push_back(value);
  int i = arr.size() - 1;
  while (i > 0) {
    int parent = (i - 1) / 2;
    if (arr[parent] < arr[i]) {
      swap(arr[parent], arr[i]);
      i = parent;
    } else
      break;
  }
}

void heapSort(vector<int> &arr) {
  int n = arr.size();
  buildHeap(arr);
  for (int i = n - 1; i > 0; --i) {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {12, 11, 13, 5, 6, 7};
  printArr(arr);
  buildHeap(arr);
  printArr(arr);
  insertHeap(arr, 8);
  insertHeap(arr, 9);
  printArr(arr);
  heapSort(arr);
  printArr(arr);
  return 0;
}
