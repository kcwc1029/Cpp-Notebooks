// ex7_3_2_assert_bounds.cpp
// 示範用 assert 做陣列邊界檢查，防止越界存取

#include <iostream>
#include <cassert>
using namespace std;

const int SIZE = 5;

int safeGet(const int arr[], int n, int index) {
    assert(index >= 0 && index < n);   // 邊界檢查
    return arr[index];
}

void safeSet(int arr[], int n, int index, int value) {
    assert(index >= 0 && index < n);   // 邊界檢查
    arr[index] = value;
}

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50};

    cout << safeGet(arr, SIZE, 0) << endl;   // 10，合法
    cout << safeGet(arr, SIZE, 4) << endl;   // 50，合法

    safeSet(arr, SIZE, 2, 99);
    cout << safeGet(arr, SIZE, 2) << endl;   // 99

    // 取消以下注解可觸發 assert（越界）：
    // cout << safeGet(arr, SIZE, 5) << endl;   // 越界！
    // cout << safeGet(arr, SIZE, -1) << endl;  // 越界！

    return 0;
}
