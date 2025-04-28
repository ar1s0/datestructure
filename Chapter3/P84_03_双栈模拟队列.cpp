#include <bits/stdc++.h>
using namespace std;

template<typename T>
class MyQueue {
private:
    stack<T> stackIn;   // 入队栈
    stack<T> stackOut;  // 出队栈

    // 将入队栈的元素移动到出队栈
    void moveElements() {
        if (stackOut.empty()) {
            while (!stackIn.empty()) {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
    }

public:
    // 入队操作
    void push(const T& value) {
        stackIn.push(value);
    }

    // 出队操作
    T pop() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        moveElements();
        T value = stackOut.top();
        stackOut.pop();
        return value;
    }

    // 获取队首元素
    T front() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        moveElements();
        return stackOut.top();
    }

    // 判断队列是否为空
    bool empty() const {
        return stackIn.empty() && stackOut.empty();
    }

    // 获取队列大小
    size_t size() const {
        return stackIn.size() + stackOut.size();
    }
};

int main() {
    MyQueue<int> queue;

    // 测试入队操作
    cout << "Pushing elements: 1, 2, 3, 4, 5\n";
    for (int i = 1; i <= 5; i++) {
        queue.push(i);
    }