#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *prev, *next;
    Node(int val = 0) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
    Node* head;
    int size;
public:
    DoublyLinkedList(vector<int> arr) {
        head = new Node(); size = 0;
        head->next = head->prev = head;
        for (auto x : arr) append(x);
    }
    
    void append(int val) {
        Node* newNode = new Node(val), *tail = head->prev;
        newNode->prev = tail; newNode->next = head;
        tail->next = newNode; head->prev = newNode;
        size++;
    }

    void info(Node *p, Node *q)
    {
        Node* h = head->next;
        while (h != head) cout << h->data << '\t', h = h->next;
        cout << endl;
        h = head->next;

        while (h != head) {
            if (h == p) cout << "p\t";
            else if (h == q) cout << "q\t";
            else cout << "\t";
            h = h->next;
        }
        cout << endl;
    }

    bool Symmetry()
    {
        Node *p = head->next, *q = head->prev;
        while (p != q && q->next != p) {
            info(p, q);
            if (p->data != q->data) return false;
            p = p->next; q = q->prev;
        } 
        return true;
    }
};

int main() {
    DoublyLinkedList list({1, 2, 3, 4, 4, 3, 2, 1});
    cout << (list.Symmetry() ? "对称" : "不对称") << endl; 
    return 0;
}