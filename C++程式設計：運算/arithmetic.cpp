
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    // 整數算術
    int a = 17, b = 5;
    cout << "=== 整數算術（a=17, b=5）===" << endl;
    cout << "a + b = " << a + b << endl;   // 22
    cout << "a - b = " << a - b << endl;   // 12
    cout << "a * b = " << a * b << endl;   // 85
    cout << "a / b = " << a / b << endl;   // 3（整數除法）
    cout << "a % b = " << a % b << endl;   // 2

    // 負數的除法與取餘
    cout << "\n=== 負數除法 ===" << endl;
    cout << "-17 /  5 = " << -17 /  5 << endl;   // -3
    cout << " 17 / -5 = " <<  17 / -5 << endl;   // -3
    cout << "-17 / -5 = " << -17 / -5 << endl;   //  3
    cout << "-17 %  5 = " << -17 %  5 << endl;   // -2
    cout << " 17 % -5 = " <<  17 % -5 << endl;   //  2

    // 浮點數運算
    cout << "\n=== 浮點數運算 ===" << endl;
    double x = 17.0, y = 5.0;
    cout << fixed << setprecision(4);
    cout << "17.0 / 5.0 = " << x / y << endl;    // 3.4000
    cout << "fmod(17.0, 5.0) = " << fmod(x, y) << endl;  // 2.0000

    // 數學函式
    cout << "\n=== 數學函式 ===" << endl;
    cout << "sqrt(144) = " << sqrt(144.0) << endl;       // 12.0000
    cout << "pow(2, 8) = " << pow(2.0, 8.0) << endl;    // 256.0000
    cout << "ceil(3.2) = " << ceil(3.2) << endl;         // 4.0000
    cout << "floor(3.9) = " << floor(3.9) << endl;       // 3.0000
    cout << "round(3.5) = " << round(3.5) << endl;       // 4.0000
    cout << "abs(-42) = " << abs(-42) << endl;            // 42.0000

    return 0;
}