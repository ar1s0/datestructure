
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
  int val;
  Node *next;
  Node(int v) : val(v), next(nullptr) {}
};

int getMax(const vector<int> &arr) {
  int mx = arr[0];
  for (int v : arr)
    if (v > mx)
      mx = v;
  return mx;
}

int getMax(const Node *head) {
  int mx = head->val;
  while (head) {
    if (head->val > mx)
      mx = head->val;
    head = head->next;
  }
  return mx;
}

// 静态数组实现
void radixSortArray(vector<int> &arr) {
  int n = arr.size();
  int maxVal = getMax(arr);
  for (int exp = 1; maxVal / exp > 0; exp *= 10) {
    vector<int> output(n);
    int count[10] = {0};
    for (int i = 0; i < n; ++i)
      count[(arr[i] / exp) % 10]++;
    for (int i = 1; i < 10; ++i)
      count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; --i) {
      output[count[(arr[i] / exp) % 10] - 1] = arr[i];
      count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; ++i)
      arr[i] = output[i];
  }
}

Node *listToNode(const vector<int> &arr) {
  Node *head = nullptr;
  for (int v : arr) {
    Node *newNode = new Node(v);
    if (!head) {
      head = newNode;
    } else {
      Node *cur = head;
      while (cur->next)
        cur = cur->next;
      cur->next = newNode;
    }
  }
  return head;
}

// 链表桶实现
Node *radixSortList(Node *&head) {
  if (!head)
    return nullptr;
  int maxVal = getMax(head);
  for (int exp = 1; maxVal / exp > 0; exp *= 10) {
    Node *heads[10] = {nullptr};
    Node *tails[10] = {nullptr};
    Node *cur = head;
    while (cur) {
      int digit = (cur->val / exp) % 10;
      Node *next = cur->next;
      cur->next = nullptr;
      if (!heads[digit]) {
        heads[digit] = tails[digit] = cur;
      } else {
        tails[digit]->next = cur;
        tails[digit] = cur;
      }
      cur = next;
    }
    // 拼接所有桶
    head = nullptr;
    Node *tail = nullptr;
    for (int b = 0; b < 10; ++b) {
      if (heads[b]) {
        if (!head) {
          head = heads[b];
          tail = tails[b];
        } else {
          tail->next = heads[b];
          tail = tails[b];
        }
      }
    }
  }
  return head;
}

void printArr(const vector<int> &arr) {
  for (int v : arr)
    cout << v << " ";
  cout << endl;
}

void printList(Node *head) {
  while (head) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}

int main() {
  vector<int> arr1 = {170, 45, 75, 90, 802, 24, 2, 66};
  vector<int> arr2 = arr1;
  cout << "原始数组: ";
  printArr(arr1);
  radixSortArray(arr1);
  cout << "静态数组基数排序结果: ";
  printArr(arr1);
  Node *head = listToNode(arr2);
  head = radixSortList(head);
  cout << "链表桶基数排序结果: ";
  printList(head);
  return 0;
}
