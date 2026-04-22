// ex7_4_3_linear_search.cpp
// 線性搜尋：O(n)，無需排序，從頭依序比較

#include <iostream>
using namespace std;

int linearSearch(const int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;   // 找到，回傳索引
    }
    return -1;   // 找不到
}

int main() {
    int arr[] = {85, 92, 78, 95, 88, 73, 99, 61};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target;
    cout << "陣列：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    cout << "請輸入要搜尋的數字：";
    cin >> target;

    int idx = linearSearch(arr, n, target);

    if (idx != -1) {
        cout << target << " 在索引 " << idx
             << "（第 " << idx + 1 << " 個位置）" << endl;
    } else {
        cout << target << " 不在陣列中" << endl;
    }

    return 0;
}
