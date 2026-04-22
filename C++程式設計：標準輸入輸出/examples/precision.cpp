// ex6_4_4_precision.cpp
// 示範 setprecision()、fixed、scientific 浮點數格式（黏著型操控子）

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi     = 3.14159265358979;
    double big    = 123456789.0;
    double small_ = 0.000012345;

    cout << "=== 預設格式（最多 6 位有效數字）===" << endl;
    cout << pi     << endl;   // 3.14159
    cout << big    << endl;   // 1.23457e+08
    cout << small_ << endl;   // 1.2345e-05

    cout << "\n=== fixed 固定小數點格式 ===" << endl;
    cout << fixed;
    cout << setprecision(2) << pi     << endl;   // 3.14
    cout << setprecision(4) << pi     << endl;   // 3.1416
    cout << setprecision(2) << big    << endl;   // 123456789.00
    cout << setprecision(6) << small_ << endl;   // 0.000012

    cout << "\n=== scientific 科學記號格式 ===" << endl;
    cout << scientific;
    cout << setprecision(3) << pi     << endl;   // 3.142e+00
    cout << setprecision(3) << big    << endl;   // 1.235e+08
    cout << setprecision(3) << small_ << endl;   // 1.235e-05

    cout << "\n=== defaultfloat 恢復預設 ===" << endl;
    cout << defaultfloat;
    cout << setprecision(6) << pi << endl;       // 3.14159

    return 0;
}
