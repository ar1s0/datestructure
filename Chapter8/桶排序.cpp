
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> bucketSort(const vector<int> &arr, int bucketSize = 5) {
  if (arr.empty())
    return arr;
  int minVal = *min_element(arr.begin(), arr.end());
  int maxVal = *max_element(arr.begin(), arr.end());
  int bucketCount = (maxVal - minVal) / bucketSize + 1;
  vector<vector<int>> buckets(bucketCount);
  // 分配数据到桶
  for (int num : arr) {
    int idx = (num - minVal) / bucketSize;
    buckets[idx].push_back(num);
  }
  // 对每个桶排序并合并
  vector<int> sortedArr;
  for (auto &bucket : buckets) {
    sort(bucket.begin(), bucket.end());
    sortedArr.insert(sortedArr.end(), bucket.begin(), bucket.end());
  }
  return sortedArr;
}

int main() {
  vector<int> arr = {29, 25, 3,  49, 9,  37, 21, 43, 1,  5,  10,
                     15, 20, 30, 40, 50, 80, 60, 70, 90, 100};
  vector<int> sorted = bucketSort(arr);
  cout << "原始数组: ";
  for (int v : arr)
    cout << v << " ";
  cout << "\n桶排序结果: ";
  for (int v : sorted)
    cout << v << " ";
  cout << endl;
  return 0;
}