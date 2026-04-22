// ex7_4_8_reverse.cpp
// 示範就地反轉陣列（使用雙指標技巧）

#include <iostream>
using namespace std;

void reverseArray(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int temp    = arr[left];
        arr[left]   = arr[right];
        arr[right]  = temp;
        left++;
        right--;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "原始：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    reverseArray(arr, n);

    cout << "反轉後：";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
