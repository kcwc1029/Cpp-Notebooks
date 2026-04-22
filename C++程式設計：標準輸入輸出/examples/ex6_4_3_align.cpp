// ex6_4_3_align.cpp
// 示範 left、right、internal 對齊方向（黏著型操控子）

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    cout << "靠右（預設）：" << endl;
    cout << right << setfill(' ');
    cout << setw(10) << "姓名"   << setw(6) << "年齡" << setw(8) << "GPA"  << endl;
    cout << setw(10) << "陳大明" << setw(6) << 20     << setw(8) << 3.8    << endl;
    cout << setw(10) << "李小華" << setw(6) << 22     << setw(8) << 3.5    << endl;

    cout << "\n靠左：" << endl;
    cout << left;
    cout << setw(10) << "姓名"   << setw(6) << "年齡" << setw(8) << "GPA"  << endl;
    cout << setw(10) << "陳大明" << setw(6) << 20     << setw(8) << 3.8    << endl;
    cout << setw(10) << "李小華" << setw(6) << 22     << setw(8) << 3.5    << endl;

    // internal：符號靠左，數值靠右，填充在中間
    cout << "\ninternal 範例（負數）：" << endl;
    cout << internal << setfill('0') << right;
    cout << setw(8) << -42 << endl;   // -0000042
    cout << setw(8) << 42  << endl;   // 00000042

    return 0;
}
