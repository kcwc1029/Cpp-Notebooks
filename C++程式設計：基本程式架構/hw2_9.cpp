// 練習 2-9：圓柱體積與表面積
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double PI = acos(-1.0);
    double r, h;

    cout << "請輸入底面半徑：";
    cin >> r;
    cout << "請輸入圓柱高度：";
    cin >> h;

    double volume  = PI * r * r * h;
    double surface = 2 * PI * r * r + 2 * PI * r * h;

    cout << fixed << setprecision(4);
    cout << "體積 = " << volume << endl;
    cout << "表面積 = " << surface << endl;

    return 0;
}
