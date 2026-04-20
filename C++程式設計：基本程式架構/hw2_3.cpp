// 練習 2-3：矩形計算
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double length, width;

    cout << "請輸入長（cm）：";
    cin >> length;
    cout << "請輸入寬（cm）：";
    cin >> width;

    double area = length * width;
    double perimeter = 2 * (length + width);
    double diagonal = sqrt(length * length + width * width);

    cout << fixed << setprecision(2);
    cout << "面積：" << area << " cm²" << endl;
    cout << "周長：" << perimeter << " cm" << endl;
    cout << "對角線：" << diagonal << " cm" << endl;

    return 0;
}
