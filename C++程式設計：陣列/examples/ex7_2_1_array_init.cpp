// ex7_2_1_array_init.cpp
// 示範陣列的各種初始化方式

#include <iostream>
using namespace std;

int globalArr[5];   // 全域陣列：自動初始化為 0

int main() {
    int a[5] = {1, 2, 3, 4, 5};    // 完整初始化
    int b[5] = {10, 20};            // 部分初始化（後面補 0）
    int c[5] = {};                   // 全部初始化為 0
    int d[]  = {100, 200, 300};     // 自動推算大小（3 個）

    cout << "a: ";
    for (int i = 0; i < 5; i++) cout << a[i] << " ";
    cout << endl;

    cout << "b: ";
    for (int i = 0; i < 5; i++) cout << b[i] << " ";
    cout << endl;

    cout << "c: ";
    for (int i = 0; i < 5; i++) cout << c[i] << " ";
    cout << endl;

    cout << "d: ";
    for (int i = 0; i < 3; i++) cout << d[i] << " ";
    cout << endl;

    cout << "global: ";
    for (int i = 0; i < 5; i++) cout << globalArr[i] << " ";
    cout << endl;

    return 0;
}
