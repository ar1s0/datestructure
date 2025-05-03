#include <iostream>
#include <vector>
using namespace std;

// B树的阶
const int M = 3;

// B树节点结构
struct BTreeNode {
    vector<int> keys;           // 关键字数组
    vector<BTreeNode*> child;   // 子节点指针数组
    bool leaf;                  // 是否为叶节点
    int n;                      // 当前关键字个数

    BTreeNode(bool isLeaf = true) {
        leaf = isLeaf;
        n = 0;
        keys.resize(2 * M - 1);     // 最大关键字数为 2M-1
        child.resize(2 * M);        // 最大子节点数为 2M
    }
};

// B树类
class BTree {
private:
    BTreeNode* root;

    // 在非满节点x的位置i插入关键字k
    void insertNonFull(BTreeNode* x, int k) {
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
            
            if (x->child[i + 1]->n == 2 * M - 1) {
                splitChild(x, i + 1);
                if (k > x->keys[i + 1])
                    i++;
            }
            insertNonFull(x->child[i + 1], k);
        }
    }

    // 分裂子节点
    void splitChild(BTreeNode* x, int i) {
        BTreeNode* y = x->child[i];
        BTreeNode* z = new BTreeNode(y->leaf);
        
        z->n = M - 1;
        
        // 复制后半部分关键字到新节点
        for (int j = 0; j < M - 1; j++)
            z->keys[j] = y->keys[j + M];
        
        // 如果不是叶节点，复制后半部分子节点
        if (!y->leaf) {
            for (int j = 0; j < M; j++)
                z->child[j] = y->child[j + M];
        }
        
        y->n = M - 1;
        
        // 为新的子节点在x中腾出空间
        for (int j = x->n; j > i; j--)
            x->child[j + 1] = x->child[j];
        
        x->child[i + 1] = z;
        
        // 将中间关键字移动到x中
        for (int j = x->n - 1; j >= i; j--)
            x->keys[j + 1] = x->keys[j];
        
        x->keys[i] = y->keys[M - 1];
        x->n++;
    }

    // 删除关键字k
    void remove(BTreeNode* x, int k) {
        int idx = findKey(x, k);

        if (idx < x->n && x->keys[idx] == k) {
            if (x->leaf)
                removeFromLeaf(x, idx);
            else
                removeFromNonLeaf(x, idx);
        } else {
            if (x->leaf) {
                cout << "关键字 " << k << " 不存在于B树中\n";
                return;
            }

            bool flag = (idx == x->n);

            if (x->child[idx]->n < M)
                fill(x, idx);

            if (flag && idx > x->n)
                remove(x->child[idx - 1], k);
            else
                remove(x->child[idx], k);
        }
    }

    // 查找关键字位置
    int findKey(BTreeNode* x, int k) {
        int idx = 0;
        while (idx < x->n && x->keys[idx] < k)
            idx++;
        return idx;
    }

    // 从叶节点删除
    void removeFromLeaf(BTreeNode* x, int idx) {
        for (int i = idx + 1; i < x->n; i++)
            x->keys[i - 1] = x->keys[i];
        x->n--;
    }

    // 从非叶节点删除
    void removeFromNonLeaf(BTreeNode* x, int idx) {
        int k = x->keys[idx];

        if (x->child[idx]->n >= M) {
            int pred = getPred(x, idx);
            x->keys[idx] = pred;
            remove(x->child[idx], pred);
        }
        else if (x->child[idx + 1]->n >= M) {
            int succ = getSucc(x, idx);
            x->keys[idx] = succ;
            remove(x->child[idx + 1], succ);
        }
        else {
            merge(x, idx);
            remove(x->child[idx], k);
        }
    }

    // 获取前驱
    int getPred(BTreeNode* x, int idx) {
        BTreeNode* curr = x->child[idx];
        while (!curr->leaf)
            curr = curr->child[curr->n];
        return curr->keys[curr->n - 1];
    }

    // 获取后继
    int getSucc(BTreeNode* x, int idx) {
        BTreeNode* curr = x->child[idx + 1];
        while (!curr->leaf)
            curr = curr->child[0];
        return curr->keys[0];
    }

    // 填充子节点
    void fill(BTreeNode* x, int idx) {
        if (idx != 0 && x->child[idx - 1]->n >= M)
            borrowFromPrev(x, idx);
        else if (idx != x->n && x->child[idx + 1]->n >= M)
            borrowFromNext(x, idx);
        else {
            if (idx != x->n)
                merge(x, idx);
            else
                merge(x, idx - 1);
        }
    }

    // 从前一个兄弟节点借关键字
    void borrowFromPrev(BTreeNode* x, int idx) {
        BTreeNode* child = x->child[idx];
        BTreeNode* sibling = x->child[idx - 1];

        for (int i = child->n - 1; i >= 0; i--)
            child->keys[i + 1] = child->keys[i];

        if (!child->leaf) {
            for (int i = child->n; i >= 0; i--)
                child->child[i + 1] = child->child[i];
        }

        child->keys[0] = x->keys[idx - 1];

        if (!child->leaf)
            child->child[0] = sibling->child[sibling->n];

        x->keys[idx - 1] = sibling->keys[sibling->n - 1];

        child->n++;
        sibling->n--;
    }

    // 从后一个兄弟节点借关键字
    void borrowFromNext(BTreeNode* x, int idx) {
        BTreeNode* child = x->child[idx];
        BTreeNode* sibling = x->child[idx + 1];

        child->keys[child->n] = x->keys[idx];

        if (!child->leaf)
            child->child[child->n + 1] = sibling->child[0];

        x->keys[idx] = sibling->keys[0];

        for (int i = 1; i < sibling->n; i++)
            sibling->keys[i - 1] = sibling->keys[i];

        if (!sibling->leaf) {
            for (int i = 1; i <= sibling->n; i++)
                sibling->child[i - 1] = sibling->child[i];
        }

        child->n++;
        sibling->n--;
    }

    // 合并节点
    void merge(BTreeNode* x, int idx) {
        BTreeNode* child = x->child[idx];
        BTreeNode* sibling = x->child[idx + 1];

        child->keys[M - 1] = x->keys[idx];

        for (int i = 0; i < sibling->n; i++)
            child->keys[i + M] = sibling->keys[i];

        if (!child->leaf) {
            for (int i = 0; i <= sibling->n; i++)
                child->child[i + M] = sibling->child[i];
        }

        for (int i = idx + 1; i < x->n; i++)
            x->keys[i - 1] = x->keys[i];

        for (int i = idx + 2; i <= x->n; i++)
            x->child[i - 1] = x->child[i];

        child->n += sibling->n + 1;
        x->n--;

        delete sibling;
    }

public:
    BTree() {
        root = nullptr;
    }

    // 插入关键字
    void insert(int k) {
        if (root == nullptr) {
            root = new BTreeNode();
            root->keys[0] = k;
            root->n = 1;
        } else {
            if (root->n == 2 * M - 1) {
                BTreeNode* s = new BTreeNode(false);
                s->child[0] = root;
                splitChild(s, 0);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                insertNonFull(s->child[i], k);
                root = s;
            } else {
                insertNonFull(root, k);
            }
        }
    }

    // 删除关键字
    void remove(int k) {
        if (root == nullptr) {
            cout << "B树为空\n";
            return;
        }

        remove(root, k);

        if (root->n == 0) {
            BTreeNode* tmp = root;
            if (root->leaf)
                root = nullptr;
            else
                root = root->child[0];
            delete tmp;
        }
    }

    // 中序遍历
    void traverse() {
        if (root != nullptr)
            traverse(root);
        cout << endl;
    }

private:
    void traverse(BTreeNode* x) {
        int i;
        for (i = 0; i < x->n; i++) {
            if (!x->leaf)
                traverse(x->child[i]);
            cout << x->keys[i] << " ";
        }
        if (!x->leaf)
            traverse(x->child[i]);
    }
};

// 测试主函数
int main() {
    BTree t;

    // 插入测试
    t.insert(3);
    t.insert(7);
    t.insert(1);
    t.insert(5);
    t.insert(11);
    t.insert(17);
    t.insert(13);
    t.insert(15);

    cout << "中序遍历B树: ";
    t.traverse();

    // 删除测试
    t.remove(7);
    cout << "删除7后的中序遍历: ";
    t.traverse();

    return 0;
}