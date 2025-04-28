#include <iostream>
using namespace std;

const int N = 10;

class Stack
{
    int data[N], _min[N]; // 存储栈元素的数组
    int top;     // 栈顶指针
public:
    Stack() : top(-1) {}

    void push(int x) {
        if (top < N - 1) {
            data[++top] = x;
            _min[top] = (top == 0) ? x : min(_min[top - 1], x);
        } else {
            cout << "Stack overflow" << endl;
        }
    }

    int pop() {
        if (top >= 0) {
            return data[top--];
        } else {
            cout << "Stack underflow" << endl;
            return -1; // or throw an exception
        }
    }

    int getMin() const {
        if (top >= 0) {
            return _min[top];
        } else {
            cout << "Stack is empty" << endl;
            return -1; // or throw an exception
        }
    }

    bool isEmpty() const {
        return top == -1;
    }
};

int main()
{
    Stack s;
    int a[10] = { 3, 4, 5, 6, 2, 1, 7, 8, 0, 9 };
    for (int i = 0; i < 10; i++) {
        s.push(a[i]);
        cout << "Pushed: " << a[i] << ", Min: " << s.getMin() << endl;
    }

    for (int i = 0; i < 5; i++) {
        cout << "Popped: " << s.pop() << ", Min: " << (s.isEmpty() ? -1 : s.getMin()) << endl;
    }
    return 0;
}