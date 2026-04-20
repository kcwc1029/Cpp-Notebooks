#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    // 連鎖指定：同時初始化多個變數
    a = b = c = 100;
    cout << "a=" << a << " b=" << b << " c=" << c << endl;

    // 指定的方向
    int x = 5;
    x = x * 2 + 1;  // 先算 5 * 2 + 1 = 11，再存入 x
    cout << "x = " << x << endl;

    // 型別不同時的指定（隱性轉換）
    double d = 3.99;
    int i = d;  // 小數被截斷，i = 3
    cout << "d=" << d << " 指定給 int 後=" << i << endl;

    return 0;
}