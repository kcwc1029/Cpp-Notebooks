// ex6_4_1_setw.cpp
// 示範 setw() 設定輸出欄位寬度（一次型操控子）
// 需要 #include <iomanip>

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 不設定欄寬（靠左對齊，無填充）
    cout << 1 << endl;
    cout << 22 << endl;
    cout << 333 << endl;

    cout << "---" << endl;

    // 設定欄寬為 6（靠右對齊，預設空白填充）
    cout << setw(6) << 1   << endl;   // "     1"
    cout << setw(6) << 22  << endl;   // "    22"
    cout << setw(6) << 333 << endl;   // "   333"

    cout << "---" << endl;

    // setw 只影響下一個輸出，之後恢復預設
    cout << setw(8) << "Name" << setw(6) << "Age" << setw(10) << "Score" << endl;
    cout << setw(8) << "Alice" << setw(6) << 20   << setw(10) << 95.5   << endl;
    cout << setw(8) << "Bob"   << setw(6) << 22   << setw(10) << 88.0   << endl;

    return 0;
}
