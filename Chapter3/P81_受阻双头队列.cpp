#include <bits/stdc++.h>
using namespace std;

// 判断是否为受阻双头队列可重排的序列
bool isDequePermutation(const vector<int>& input, const vector<int>& target) {
    int n = input.size();
    if (n != target.size()) return false;
    
    // 创建每个元素在目标序列中的位置映射
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++) {
        pos[target[i]] = i;
    }
    
    // 检查每个元素与其后继元素的关系
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 2; j < n; j++) {
            int a = input[i], b = input[j];
            int pa = pos[a], pb = pos[b];
            
            // 检查交叉情况
            for (int k = i + 1; k < j; k++) {
                int c = input[k];
                int pc = pos[c];
                
                // 如果存在交叉，则不可能通过受阻双头队列重排
                if ((pa < pc && pc < pb) || (pb < pc && pc < pa)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    // 测试用例
    vector<vector<int>> tests = {
        {1, 2, 3, 4},     // 输入序列
        {2, 1, 4, 3},     // 目标序列1：可以重排
        {2, 4, 1, 3},     // 目标序列2：不可重排
    };
    
    cout << "Input sequence: ";
    for (int x : tests[0]) cout << x << " ";
    cout << "\n\n";
    
    for (int i = 1; i < tests.size(); i++) {
        cout << "Testing target sequence " << i << ": ";
        for (int x : tests[i]) cout << x << " ";
        cout << "\nCan be rearranged: " 
             << (isDequePermutation(tests[0], tests[i]) ? "Yes" : "No") << "\n\n";
    }
    
    return 0;
}