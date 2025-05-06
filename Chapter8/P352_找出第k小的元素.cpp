#include <iostream>
#include <vector>
using namespace std;

// 分区函数
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];  // 选择最右边的元素作为基准
    int i = left - 1;        // i是小于pivot的区域的边界
    
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

// 快速选择算法
int quickSelect(vector<int>& arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    
    int pivotIndex = partition(arr, left, right);
    int count = pivotIndex - left + 1;  // 计算基准元素是第几小的元素
    
    if (count == k) {
        return arr[pivotIndex];
    }
    else if (count > k) {
        return quickSelect(arr, left, pivotIndex - 1, k);
    }
    else {
        return quickSelect(arr, pivotIndex + 1, right, k - count);
    }
}

int findKthSmallest(vector<int>& arr, int k) {
    if (k < 1 || k > arr.size()) {
        return -1;  // 无效的k值
    }
    return quickSelect(arr, 0, arr.size() - 1, k);
}

int main() {
    vector<int> arr = {7, 10, 4, 3, 20, 15};
    int k = 3;  // 查找第3小的元素
    
    cout << "原始数组: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    int result = findKthSmallest(arr, k);
    cout << "第" << k << "小的元素是: " << result << endl;
    
    return 0;
}