#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val = 0) : data(val), next(nullptr) {}
};

class List {
    int size;
public:
    List(vector<int> arr) : head(new Node()), tail(head), size(0) {
        for (auto x : arr) append(x);
    };

    void append(int val) { 
        Node* newNode = new Node(val);
        tail->next = newNode; tail = newNode;
        size++;
    }

    Node *head, *tail;
};

int Pattern(List& a, List& b) {
    Node *p = a.head->next, *q = b.head->next, *pre = p;
    while (p&&q)
    {
        if (p->data == q->data) q = q -> next, p = p -> next;
        else 
        {
            q = b.head->next;
            p = pre -> next;
            pre = p;
        }
    }
    return q == NULL;
}

int main() {
    List a ({1, 2, 3, 4, 5}), b ({ 3, 4 });
    cout << (Pattern(a, b) ? "是" : "不是") << endl;
    return 0;
}