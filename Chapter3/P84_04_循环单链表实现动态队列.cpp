#include <bits/stdc++.h>
using namespace std;

template <typename T>
class CircularQueue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node() : next(nullptr) {}
        Node(const T &value) : data(value), next(nullptr) {}
    };

    Node *head; // 头节点指针
    Node *rear; // 队尾指针
    int size;   // 队列中的元素个数

public:
    // 构造函数
    CircularQueue() : size(0)
    {
        head = new Node(); // 创建头节点
        head->next = head; // 初始时指向自己
        rear = head;       // 队尾指向头节点
    }

    // 析构函数
    ~CircularQueue()
    {
        Node *current = head->next;
        while (current != head)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
    }

    // 入队操作
    void enqueue(const T &value)
    {
        if (rear->next != head)
        {
            rear->next->data = value; // 如果队列不满，直接赋值
            rear = rear->next;        // 队尾指针后移
        }
        else
        {
            Node *newNode = new Node(value); // 创建新节点
            rear->next = newNode;            // 队尾指向新节点
            newNode->next = head;            // 新节点指向头节点
            rear = newNode;                  // 更新队尾指针
        }
        ++size;
    }

    // 出队操作
    T dequeue()
    {
        if (empty())
            throw runtime_error("Queue is empty");

        Node *front = head->next; // 第一个数据节点
        T value = front->data;

        size--;
        head = front;
        return value;
    }

    // 获取队首元素
    T getFront() const
    {
        if (empty())
            throw runtime_error("Queue is empty");
        return head->next->data;
    }

    // 获取队尾元素
    T getRear() const
    {
        if (empty())
            throw runtime_error("Queue is empty");
        return rear->data;
    }

    int getSize() const { return size; }
    bool empty() const { return head == rear; }
};

int main()
{
    CircularQueue<int> queue;

    // 测试入队操作
    cout << "Enqueueing elements: 1, 2, 3, 4, 5\n";
    for (int i = 1; i <= 5; i++)
    {
        queue.enqueue(i);
        cout << "Enqueued: " << i << ", Size: " << queue.getSize()
             << ", Front: " << queue.getFront() << ", Rear: " << queue.getRear() << "\n";
    }

    // 测试出队操作
    cout << "\nDequeueing elements:\n";
    while (queue.getSize() > 2)
    {
        cout << "Front element: " << queue.getFront() << "\n";
        cout << "Dequeued: " << queue.dequeue() << ", Size: " << queue.getSize() << "\n";
    }

    // 测试空队列操作
    cout << "\nQueue is empty: " << (queue.empty() ? "true" : "false") << "\n";

    // 测试入队操作
    cout << "Enqueueing elements: 2, 4, 6, 8, 10\n";
    for (int i = 1; i <= 5; i++)
    {
        queue.enqueue(i * 2);
        cout << "Enqueued: " << i * 2 << ", Size: " << queue.getSize()
             << ", Front: " << queue.getFront() << ", Rear: " << queue.getRear() << "\n";
    }

    return 0;
}