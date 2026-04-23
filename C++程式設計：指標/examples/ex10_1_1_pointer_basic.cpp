// ex10_1_1_pointer_basic.cpp
// 示範：指標的基本宣告、取址(&)、解參考(*)
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int *p = &x;   // p 指向 x

    cout << "x 的值：" << x << endl;
    cout << "x 的位址：" << &x << endl;
    cout << "p 儲存的位址：" << p << endl;
    cout << "*p（解參考）：" << *p << endl;

    *p = 100;      // 透過指標修改 x
    cout << "\n修改後：" << endl;
    cout << "x = " << x << endl;
    cout << "*p = " << *p << endl;

    cout << "\n大小比較：" << endl;
    cout << "sizeof(int) = " << sizeof(int) << " bytes" << endl;
    cout << "sizeof(p)   = " << sizeof(p) << " bytes（指標大小固定）" << endl;

    return 0;
}
