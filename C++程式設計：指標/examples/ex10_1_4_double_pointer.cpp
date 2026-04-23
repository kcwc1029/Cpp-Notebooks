// ex10_1_4_double_pointer.cpp
// 示範：雙重指標（指向指標的指標）
#include <iostream>
using namespace std;

int main() {
    int x = 5;
    int *p = &x;    // p 指向 x
    int **pp = &p;  // pp 指向 p

    cout << "=== 各層位址與值 ===" << endl;
    cout << "x   = " << x    << "，&x  = " << &x  << endl;
    cout << "*p  = " << *p   << "，p   = " << p   << "，&p  = " << &p  << endl;
    cout << "**pp= " << **pp << "，*pp = " << *pp << "，pp  = " << pp  << endl;

    cout << "\n=== 透過雙重指標修改 x ===" << endl;
    **pp = 999;
    cout << "x = " << x << endl;

    cout << "\n=== 雙重指標的實際應用：改變指向 ===" << endl;
    int y = 777;
    *pp = &y;   // 透過 pp 修改 p 的指向
    cout << "現在 p 指向 y，*p = " << *p << endl;
    cout << "x 未變：x = " << x << endl;

    return 0;
}
