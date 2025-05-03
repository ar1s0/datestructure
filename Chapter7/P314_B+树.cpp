#include <iostream>
#include <vector>
using namespace std;

// B+树的阶
const int M = 3;

// B+树节点结构
struct BPlusNode {
    vector<int> keys;           // 关键字数组
    vector<BPlusNode*> child;   // 子节点指针数组
    BPlusNode* next;           // 下一个叶子节点的指针
    bool leaf;                  // 是否为叶节点
    int n;                      // 当前关键字个数

    BPlusNode(bool isLeaf = true) {
        leaf = isLeaf;
        next = nullptr;
        n = 0;
        keys.resize(2 * M);      // 最大关键字数为 2M
        child.resize(2 * M + 1); // 最大子节点数为 2M+1
    }
};

// B+树类
class BPlusTree {
private:
    BPlusNode* root;
    BPlusNode* firstLeaf; // 指向第一个叶子节点

    // 在非满节点x的位置i插入关键字k
    void insertNonFull(BPlusNode* x, int k) {
        int i = x->n - 1;

        if (x->leaf) {
            // 在叶节点中插入
            while (i >= 0 && x->keys[i] > k) {
                x->keys[i + 1] = x->keys[i];
                i--;
            }
            x->keys[i + 1] = k;
            x->n++;
        } else {
            // 在内部节点中找到合适的子树
            while (i >= 0 && x->keys[i] > k)
                i--;
            i++;

            if (x->child[i]->n == 2 * M) {
                splitChild(x, i);
                if (k > x->keys[i])
                    i++;
            }
            insertNonFull(x->child[i], k);
        }
    }

    // 分裂子节点
    void splitChild(BPlusNode* x, int i) {
        BPlusNode* y = x->child[i];
        BPlusNode* z = new BPlusNode(y->leaf);

        // 复制后半部分关键字到新节点
        for (int j = 0; j < M; j++)
            z->keys[j] = y->keys[j + M];

        // 如果不是叶节点，复制后半部分子节点
        if (!y->leaf) {
            for (int j = 0; j < M + 1; j++)
                z->child[j] = y->child[j + M];
        } else {
            // 如果是叶节点，维护叶节点链表
            z->next = y->next;
            y->next = z;
        }

        y->n = M;
        z->n = M;

        // 为新的子节点在x中腾出空间
        for (int j = x->n; j > i; j--) {
            x->keys[j] = x->keys[j - 1];
            x->child[j + 1] = x->child[j];
        }

        x->child[i + 1] = z;
        x->keys[i] = z->keys[0];
        x->n++;
    }

    // 查找关键字k所在的叶子节点
    BPlusNode* findLeaf(int k) {
        BPlusNode* x = root;
        while (!x->leaf) {
            int i = 0;
            while (i < x->n && k >= x->keys[i])
                i++;
            x = x->child[i];
        }
        return x;
    }

public:
    BPlusTree() {
        root = nullptr;
        firstLeaf = nullptr;
    }

    // 插入关键字
    void insert(int k) {
        if (root == nullptr) {
            root = new BPlusNode(true);
            firstLeaf = root;
            root->keys[0] = k;
            root->n = 1;
        } else {
            if (root->n == 2 * M) {
                BPlusNode* s = new BPlusNode(false);
                s->child[0] = root;
                splitChild(s, 0);
                root = s;
            }
            insertNonFull(root, k);
        }
    }

    // 查找关键字
    bool search(int k) {
        if (root == nullptr)
            return false;

        BPlusNode* leaf = findLeaf(k);
        for (int i = 0; i < leaf->n; i++)
            if (leaf->keys[i] == k)
                return true;
        return false;
    }

    // 顺序遍历所有叶子节点
    void traverseLeaves() {
        BPlusNode* leaf = firstLeaf;
        while (leaf != nullptr) {
            for (int i = 0; i < leaf->n; i++)
                cout << leaf->keys[i] << " ";
            leaf = leaf->next;
        }
        cout << endl;
    }
};

// 测试主函数
int main() {
    BPlusTree t;

    // 插入测试
    t.insert(3);
    t.insert(7);
    t.insert(1);
    t.insert(5);
    t.insert(11);
    t.insert(17);
    t.insert(13);
    t.insert(15);

    cout << "叶子节点序列: ";
    t.traverseLeaves();

    // 查找测试
    int key = 13;
    if (t.search(key))
        cout << key << " 存在于B+树中" << endl;
    else
        cout << key << " 不存在于B+树中" << endl;

    return 0;
}