#include <iostream>
#include <vector>
using namespace std;

// 定义三种颜色的枚举类型
enum Color {RED, WHITE, BLUE};

// 打印数组函数
void printArray(vector<Color>& arr) {
    for(const Color& c : arr) {
        switch(c) {
            case RED: cout << "红 "; break;
            case WHITE: cout << "白 "; break;
            case BLUE: cout << "蓝 "; break;
        }
    }
    cout << endl;
}

// 交换函数
void swap(Color& a, Color& b) {
    Color temp = a;
    a = b;
    b = temp;
}

// 三指针排序算法
void dutchFlagSort(vector<Color>& arr) {
    int low = 0;          // 红色区域的右边界
    int mid = 0;          // 当前遍历位置
    int high = arr.size() - 1;  // 蓝色区域的左边界
    
    while (mid <= high) {
        switch (arr[mid]) {
            case RED:
                swap(arr[low], arr[mid]);
                low++;
                mid++;
                break;
            case WHITE:
                mid++;
                break;
            case BLUE:
                swap(arr[mid], arr[high]);
                high--;
                break;
        }
    }
}

int main() {
    // 测试样例
    vector<Color> flags = {BLUE, WHITE, RED, BLUE, RED, WHITE, RED};
    
    cout << "排序前：";
    printArray(flags);
    
    dutchFlagSort(flags);
    
    cout << "排序后：";
    printArray(flags);
    
    return 0;
}