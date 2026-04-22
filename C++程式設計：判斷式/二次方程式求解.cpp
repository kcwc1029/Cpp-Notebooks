// 練習 4-8：二次方程式求解
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;
    cout << "請輸入 ax² + bx + c = 0 的係數 a, b, c：";
    cin >> a >> b >> c;

    cout << fixed << setprecision(4);

    if (a == 0) {
        if (b == 0) {
            if (c == 0) cout << "無限多解（0 = 0）" << endl;
            else        cout << "無解（" << c << " = 0 矛盾）" << endl;
        } else {
            cout << "一次方程式，解：x = " << -c/b << endl;
        }
        return 0;
    }

    double delta = b*b - 4*a*c;
    cout << "判別式 Δ = " << delta << endl;

    if (delta > 0) {
        double x1 = (-b + sqrt(delta)) / (2*a);
        double x2 = (-b - sqrt(delta)) / (2*a);
        cout << "兩相異實數根：" << endl;
        cout << "  x1 = " << x1 << endl;
        cout << "  x2 = " << x2 << endl;
    } else if (delta == 0) {
        double x = -b / (2*a);
        cout << "兩相等實數根：x = " << x << endl;
    } else {
        double real = -b / (2*a);
        double imag = sqrt(-delta) / (2*a);
        cout << "兩共軛複數根：" << endl;
        cout << "  x1 = " << real << " + " << imag << "i" << endl;
        cout << "  x2 = " << real << " - " << imag << "i" << endl;
    }

    return 0;
}
