// 練習 4-3：三角形判斷
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;
    cout << "請輸入三邊長（空格分隔）：";
    cin >> a >> b >> c;

    if (a <= 0 || b <= 0 || c <= 0) {
        cout << "邊長必須為正數！" << endl;
        return 1;
    }

    if (a + b <= c || a + c <= b || b + c <= a) {
        cout << "無法構成三角形。" << endl;
        return 0;
    }

    cout << "可以構成三角形！" << endl;

    if (a == b && b == c) {
        cout << "類型：等邊三角形" << endl;
    } else if (a == b || b == c || a == c) {
        cout << "類型：等腰三角形" << endl;
    } else {
        cout << "類型：一般三角形" << endl;
    }

    // 找最長邊判斷直角
    double s1 = a, s2 = b, hyp = c;
    if (b >= a && b >= c) { s1 = a; s2 = c; hyp = b; }
    else if (a >= b && a >= c) { s1 = b; s2 = c; hyp = a; }

    if (fabs(s1*s1 + s2*s2 - hyp*hyp) < 1e-9) {
        cout << "同時也是直角三角形！" << endl;
    }

    return 0;
}
