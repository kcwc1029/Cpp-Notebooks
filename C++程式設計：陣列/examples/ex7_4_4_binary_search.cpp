// ex7_4_4_binary_search.cpp
// 二分搜尋：O(log n)，前提：陣列必須已排序

#include <iostream>
using namespace std;

int binarySearch(const int arr[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;   // 避免 (left+right) 整數溢位

        if (arr[mid] == target) {
            return mid;            // 找到
        } else if (arr[mid] < target) {
            left = mid + 1;        // 目標在右半
        } else {
            right = mid - 1;       // 目標在左半
        }
    }
    return -1;   // 找不到
}

int main() {
    // 必須已排序！
    int arr[] = {61, 73, 78, 85, 88, 92, 95, 99};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "陣列（已排序）：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    int target;
    cout << "請輸入要搜尋的數字：";
    cin >> target;

    int idx = binarySearch(arr, n, target);

    if (idx != -1) {
        cout << target << " 在索引 " << idx << endl;
    } else {
        cout << target << " 不在陣列中" << endl;
    }

    return 0;
}
