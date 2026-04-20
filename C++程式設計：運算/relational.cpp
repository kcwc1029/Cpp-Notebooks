#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;

    cout << boolalpha;  // 讓 bool 輸出 true/false 而非 1/0

    cout << "a = " << a << ", b = " << b << endl;
    cout << "a == b : " << (a == b) << endl;   // false
    cout << "a != b : " << (a != b) << endl;   // true
    cout << "a >  b : " << (a >  b) << endl;   // false
    cout << "a <  b : " << (a <  b) << endl;   // true
    cout << "a >= b : " << (a >= b) << endl;   // false
    cout << "a <= b : " << (a <= b) << endl;   // true

    // 關係運算的結果可以存進 bool
    bool isAdult = (a >= 18);
    cout << "\n" << a << " 歲是否成年：" << isAdult << endl;  // false

    // 字元比較（依 ASCII 值）
    char c1 = 'A', c2 = 'Z';
    cout << "'A' < 'Z' : " << (c1 < c2) << endl;   // true（65 < 90）

    // 浮點數比較的陷阱
    double x = 0.1 + 0.2;
    double y = 0.3;
    cout << "\n0.1 + 0.2 == 0.3 : " << (x == y) << endl;  // false！！！

    // 正確的浮點數比較：檢查差值是否夠小
    double epsilon = 1e-9;
    cout << "誤差比較法：" << (fabs(x - y) < epsilon) << endl;  // true

    return 0;
}