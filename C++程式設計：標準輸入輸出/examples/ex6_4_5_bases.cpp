// ex6_4_5_bases.cpp
// 示範 hex、oct、dec 進位制輸出，以及 showbase、uppercase

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int num = 255;

    cout << "數值：" << num << endl;
    cout << "十進位：" << dec << num << endl;
    cout << "八進位：" << oct << num << endl;           // 377
    cout << "十六進位（小寫）：" << hex << num << endl; // ff
    cout << "十六進位（大寫）：" << uppercase << hex << num << endl; // FF

    cout << "\n加上前綴（showbase）：" << endl;
    cout << showbase << nouppercase;
    cout << "十進位：" << dec << num << endl;   // 255
    cout << "八進位：" << oct << num << endl;   // 0377
    cout << "十六進位：" << hex << num << endl; // 0xff

    cout << "\n回到十進位：" << noshowbase << dec << endl;
    cout << num << endl;

    // 實用應用：RGB 顏色代碼
    int r = 255, g = 128, b = 0;
    cout << "\nRGB 顏色代碼：#"
         << uppercase << hex
         << setw(2) << setfill('0') << r
         << setw(2) << setfill('0') << g
         << setw(2) << setfill('0') << b
         << endl;   // #FF8000

    return 0;
}
