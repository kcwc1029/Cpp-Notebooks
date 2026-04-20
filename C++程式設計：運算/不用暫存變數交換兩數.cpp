#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "請輸入兩個整數：";
    cin >> a >> b;

    cout << "交換前：a=" << a << ", b=" << b << endl;

    // XOR 交換法（不需要暫存變數）
    a ^= b;
    b ^= a;
    a ^= b;

    cout << "交換後：a=" << a << ", b=" << b << endl;

    // 驗證：也可用算術法（加減法）
    int x = 100, y = 200;
    x = x + y;  // x = 300
    y = x - y;  // y = 100 (原本的 x)
    x = x - y;  // x = 200 (原本的 y)
    cout << "算術法交換：x=" << x << ", y=" << y << endl;

    return 0;
}