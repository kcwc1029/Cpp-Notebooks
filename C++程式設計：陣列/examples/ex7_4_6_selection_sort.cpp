// ex7_4_6_selection_sort.cpp
// 選擇排序：每輪從未排序部分找最小值，放到已排序末尾，O(n²)

#include <iostream>
using namespace std;

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int temp      = arr[i];
            arr[i]        = arr[minIdx];
            arr[minIdx]   = temp;
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "排序前：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    selectionSort(arr, n);

    cout << "排序後：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
