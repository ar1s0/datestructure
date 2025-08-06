
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// 模拟磁盘文件分块
vector<vector<int>> createRuns(const vector<int> &arr, int runSize) {
  vector<vector<int>> runs;
  int n = arr.size();
  for (int i = 0; i < n; i += runSize) {
    vector<int> run(arr.begin() + i, arr.begin() + min(i + runSize, n));
    sort(run.begin(), run.end());
    runs.push_back(run);
  }
  return runs;
}

// k路归并
vector<int> kWayMerge(vector<vector<int>> &runs) {
  struct Node {
    int val, runIdx, idx;
    bool operator>(const Node &other) const { return val > other.val; }
  };
  priority_queue<Node, vector<Node>, greater<Node>> pq;
  int k = runs.size();
  for (int i = 0; i < k; ++i) {
    if (!runs[i].empty()) {
      pq.push({runs[i][0], i, 0});
    }
  }
  vector<int> result;
  while (!pq.empty()) {
    Node node = pq.top();
    pq.pop();
    result.push_back(node.val);
    if (node.idx + 1 < runs[node.runIdx].size()) {
      pq.push({runs[node.runIdx][node.idx + 1], node.runIdx, node.idx + 1});
    }
  }
  return result;
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

int main() {
  vector<int> arr = {23, 12, 1,  8,  34, 54, 2,  3,  99, 17, 25, 4,  7,
                     6,  5,  10, 15, 20, 30, 40, 50, 80, 60, 70, 90, 100,
                     11, 22, 33, 44, 55, 66, 77, 88, 95, 85, 66, 77, 99};
  int runSize = 5; // 每个归并段大小
  cout << "原始数据: ";
  printArr(arr);
  // 1. 生成初始归并段
  vector<vector<int>> runs = createRuns(arr, runSize);
  cout << "初始归并段:\n";
  for (const auto &run : runs) {
    printArr(run);
  }
  // 2. 多路归并
  vector<int> sorted = kWayMerge(runs);
  cout << "归并后结果: ";
  printArr(sorted);
  return 0;
}
