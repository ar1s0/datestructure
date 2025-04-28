#include <iostream>
using namespace std;

void reverse(int a[], int from, int end)
{
    for (int i=0;i<(end-from)/2;++i) swap(a[from+i], a[end-i-1]); 
}

int main()
{
    int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    reverse(a, 0, 5);
    reverse(a, 5, 10);
    reverse(a, 0, 10);
    for (int i=0;i<10;++i) cout << a[i] << '\t';
    return 0;
}