#include <bits/stdc++.h>
using namespace std;

int SequentialSearch(int arr[], int n, int key) {
  arr[0] = key; // 哨兵法
  int i = n;
  while (arr[i] != key) {
    i--;
  }
  return i;
}

int BinarySearch(int arr[], int n, int key) {
  int low = 1, high = n;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (arr[mid] == key)
      return mid;
    else if (arr[mid] > key)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return 0;
}

int main() {
  vector<int> arr = {0, 1, 2, 3, 4, 5};
  return 0;
}
