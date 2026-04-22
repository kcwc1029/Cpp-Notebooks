// ex7_4_5_bubble_sort.cpp
// 泡沫排序：相鄰元素比較交換，大值向後「浮」，O(n²)

#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;   // 最佳化：若這輪沒有交換，代表已排序

        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp     = arr[j];
                arr[j]       = arr[j + 1];
                arr[j + 1]   = temp;
                swapped = true;
            }
        }

        if (!swapped) break;   // 提早結束，最佳情況 O(n)
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    bubbleSort(arr, n);

    cout << "排序後：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
