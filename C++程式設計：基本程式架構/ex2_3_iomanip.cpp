#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double pi = 3.14159265358979;
    int num = 42;

    // 小數位數控制
    cout << "預設輸出：" << pi << endl;
    cout << fixed << setprecision(2) << pi << endl;
    cout << fixed << setprecision(5) << pi << endl;
    cout << scientific << setprecision(3) << pi << endl;

    cout << defaultfloat;

    // 欄位寬度與對齊
    cout << "\n=== 成績單 ===" << endl;
    cout << left;
    cout << setw(15) << "學生姓名" << setw(8) << "分數" << endl;
    cout << setfill('-') << setw(23) << "" << setfill(' ') << endl;
    cout << setw(15) << "Alice"   << setw(8) << 95 << endl;
    cout << setw(15) << "Bob"     << setw(8) << 87 << endl;
    cout << setw(15) << "Charlie" << setw(8) << 72 << endl;

    // 進位制輸出
    cout << "\n=== 進位制 ===" << endl;
    cout << "十進位：" << dec << num << endl;
    cout << "十六進位：" << hex << num << endl;
    cout << "八進位：" << oct << num << endl;
    cout << dec;

    // 補零時間格式
    cout << "\n=== 時間格式 ===" << endl;
    int hour = 9, minute = 5, second = 3;
    cout << setfill('0');
    cout << setw(2) << hour   << ":"
         << setw(2) << minute << ":"
         << setw(2) << second << endl;

    return 0;
}
