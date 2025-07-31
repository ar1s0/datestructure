#include <iostream>
using namespace std;

struct Node {
  int data;
};

void fun(Node *n) { n->data = 10; }

int main() {
  struct Node *n = new Node;
  cout << "Address of n: \t\t" << (void *)&n << endl
       << "Point address of n: \t" << (void *)n << endl;
  fun(n);
  cout << "Data in n: " << n->data << endl;
  delete n;
  return 0;
}