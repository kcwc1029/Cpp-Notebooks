// ex7_2_3_array_sizeof.cpp
// 示範用 sizeof 計算陣列元素個數

#include <iostream>
using namespace std;

int main() {
    int    arr[5]  = {1, 2, 3, 4, 5};
    double darr[4] = {1.1, 2.2, 3.3, 4.4};

    // sizeof(陣列) = 元素個數 × 每個元素大小
    cout << "int arr[5]:" << endl;
    cout << "  sizeof(arr)    = " << sizeof(arr)    << " bytes" << endl;
    cout << "  sizeof(arr[0]) = " << sizeof(arr[0]) << " bytes" << endl;
    cout << "  元素個數       = " << sizeof(arr) / sizeof(arr[0]) << endl;

    cout << "\ndouble darr[4]:" << endl;
    cout << "  sizeof(darr)   = " << sizeof(darr)   << " bytes" << endl;
    cout << "  元素個數       = " << sizeof(darr) / sizeof(darr[0]) << endl;

    // 常見寫法：避免寫死大小
    const int N = sizeof(arr) / sizeof(arr[0]);
    cout << "\n用 sizeof 算出大小 N=" << N << "，用迴圈遍歷：" << endl;
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
