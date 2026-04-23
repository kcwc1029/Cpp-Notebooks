#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int& r = x;   // r 是 x 的參考（別名）

    cout << "=== 初始狀態 ===" << endl;
    cout << "x  = " << x << endl;
    cout << "r  = " << r << endl;
    cout << "&x = " << &x << endl;   // x 的記憶體位址
    cout << "&r = " << &r << endl;   // r 的位址（與 x 完全相同！）

    // 透過參考修改值
    r = 100;
    cout << "\n透過 r 修改後：" << endl;
    cout << "x = " << x << endl;    // x 也變成 100
    cout << "r = " << r << endl;

    // 透過原變數修改
    x = 200;
    cout << "\n透過 x 修改後：" << endl;
    cout << "x = " << x << endl;
    cout << "r = " << r << endl;    // r 也是 200

    // 多個參考指向同一個變數
    int& r2 = x;
    r2 = 999;
    cout << "\n透過 r2 修改後：" << endl;
    cout << "x  = " << x  << endl;    // 999
    cout << "r  = " << r  << endl;    // 999
    cout << "r2 = " << r2 << endl;    // 999

    return 0;
}
