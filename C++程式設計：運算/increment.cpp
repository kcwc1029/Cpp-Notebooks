#include <iostream>
using namespace std;

int main() {
    int x = 10;

    // 前置遞增
    cout << "x = " << x << endl;        // 10
    cout << "++x = " << ++x << endl;    // 11（x 先加 1，再輸出）
    cout << "x = " << x << endl;        // 11

    cout << "---" << endl;

    // 後置遞增
    int y = 10;
    cout << "y = " << y << endl;        // 10
    cout << "y++ = " << y++ << endl;    // 10（先輸出 y 的舊值，再加 1）
    cout << "y = " << y << endl;        // 11

    cout << "---" << endl;

    // 前後置的差異在運算式中
    int a = 5, b = 5;
    int ra = ++a * 2;   // a 先變 6，ra = 6 * 2 = 12
    int rb = b++ * 2;   // rb = 5 * 2 = 10，b 再變 6

    cout << "前置：a=" << a << " ra=" << ra << endl;  // a=6 ra=12
    cout << "後置：b=" << b << " rb=" << rb << endl;  // b=6 rb=10

    return 0;
}