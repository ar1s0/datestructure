#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

// 简单整型散列函数（除留余数法）
int hashInt(int key, int tableSize) { return key % tableSize; }

// 字符串散列函数（BKDRHash）
unsigned int hashString(const string &str, int tableSize) {
  unsigned int seed = 131;
  unsigned int hash = 0;
  for (char c : str) {
    hash = hash * seed + c;
  }
  return hash % tableSize;
}
// 拉链法哈希表实现
class HashTable {
public:
  int size;
  vector<list<int>> table;
  HashTable(int sz) : size(sz), table(sz) {}
  void insert(int key) {
    int idx = hashInt(key, size);
    table[idx].push_back(key);
  }
  bool find(int key) {
    int idx = hashInt(key, size);
    for (int v : table[idx])
      if (v == key)
        return true;
    return false;
  }

  bool remove(int key) {
    int idx = hashInt(key, size);
    auto &bucket = table[idx];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
      if (*it == key) {
        bucket.erase(it);
        return true;
      }
    }
    return false;
  }
  void print() {
    for (int i = 0; i < size; ++i) {
      cout << i << ": ";
      for (int v : table[i])
        cout << v << " -> ";
      cout << "NULL" << endl;
    }
  }
};

int main() {

  cout << "\n拉链法哈希表演示:" << endl;
  int tableSize1 = 10;
  int keys1[] = {15, 28, 19, 33, 42, 7, 10, 25, 30, 18};

  HashTable ht(tableSize1);
  for (int k : keys1)
    ht.insert(k);
  ht.print();
  cout << "查找19: " << (ht.find(19) ? "找到" : "未找到") << endl;
  cout << "查找99: " << (ht.find(99) ? "找到" : "未找到") << endl;
  cout << "删除28: " << (ht.remove(28) ? "成功" : "失败") << endl;
  ht.print();
  return 0;
}
