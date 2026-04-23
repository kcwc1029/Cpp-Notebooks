// ex10_2_4_const_pointer.cpp
// 示範：const 指標的四種組合
#include <iostream>
using namespace std;

// 接受 const int*：保護陣列不被修改
void print_array(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // arr[0] = 999;  // 編譯錯誤：不能修改 const 指標的指向值
}

// 接受 int*：會修改陣列內容
void negate_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = -arr[i];
    }
}

int main() {
    int x = 10, y = 20;

    cout << "=== 1. 普通指標 int *p ===" << endl;
    int *p1 = &x;
    *p1 = 50;         // OK：可以修改值
    p1 = &y;          // OK：可以改變指向
    cout << "*p1 = " << *p1 << endl;

    cout << "\n=== 2. 指向常數的指標 const int *p ===" << endl;
    const int *p2 = &x;
    // *p2 = 50;      // 錯誤：不能修改值
    p2 = &y;          // OK：可以改變指向
    cout << "*p2 = " << *p2 << "（x=" << x << "，指向已換到 y）" << endl;

    cout << "\n=== 3. 常數指標 int * const p ===" << endl;
    int * const p3 = &x;
    *p3 = 77;         // OK：可以修改值
    // p3 = &y;       // 錯誤：不能改變指向
    cout << "*p3 = " << *p3 << "，x = " << x << endl;

    cout << "\n=== 4. 指向常數的常數指標 const int * const p ===" << endl;
    const int * const p4 = &x;
    // *p4 = 50;      // 錯誤：不能修改值
    // p4 = &y;       // 錯誤：不能改變指向
    cout << "*p4 = " << *p4 << "（唯讀，鎖死）" << endl;

    cout << "\n=== 實際應用：保護陣列 ===" << endl;
    int arr[] = {5, 3, 1, 4, 2};
    cout << "原始：";  print_array(arr, 5);
    negate_array(arr, 5);
    cout << "取負：";  print_array(arr, 5);

    return 0;
}
