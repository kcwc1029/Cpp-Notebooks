// ex6_4_2_setfill.cpp
// 示範 setfill() 設定填充字元（黏著型操控子）

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 用 * 填充（黏著型，設定後持續生效）
    cout << setfill('*');
    cout << setw(10) << 123   << endl;   // *******123
    cout << setw(10) << "Hi"  << endl;   // ********Hi
    cout << setw(10) << 3.14  << endl;   // ******3.14

    cout << "---" << endl;

    // 用 0 填充（常見於編號、日期、時間格式）
    cout << setfill('0');
    cout << setw(4) << 7  << endl;   // 0007
    cout << setw(4) << 42 << endl;   // 0042

    // 模擬時鐘格式 HH:MM:SS
    int h = 9, m = 5, s = 3;
    cout << setw(2) << h << ":"
         << setw(2) << m << ":"
         << setw(2) << s << endl;   // 09:05:03

    return 0;
}
