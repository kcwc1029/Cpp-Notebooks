#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double a = 0.1 + 0.2;
    double b = 0.3;

    cout << setprecision(20);
    cout << "0.1 + 0.2 = " << a << endl;
    cout << "0.3       = " << b << endl;

    // 直接比較：通常失敗
    if (a == b) {
        cout << "相等（直接比較）" << endl;
    } else {
        cout << "不相等（直接比較）← 看！浮點數有誤差！" << endl;
    }

    // 正確做法：誤差比較
    const double EPSILON = 1e-9;
    if (fabs(a - b) < EPSILON) {
        cout << "相等（誤差比較）✅" << endl;
    } else {
        cout << "不相等（誤差比較）" << endl;
    }

    return 0;
}
