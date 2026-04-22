// ex6_2_1_cout_basic.cpp
// 示範 cout 輸出各種型別與連鎖使用

#include <iostream>
using namespace std;

int main() {
    // 輸出各種型別
    cout << 42 << endl;
    cout << 3.14 << endl;
    cout << 'A' << endl;
    cout << true << endl;          // 輸出 1
    cout << "Hello, World!" << endl;

    // 連鎖輸出（可以串多個 <<）
    int x = 10, y = 20;
    cout << "x = " << x << ", y = " << y << endl;

    // 輸出計算結果（運算式直接放入）
    cout << "x + y = " << x + y << endl;
    cout << "x * y = " << x * y << endl;

    return 0;
}
