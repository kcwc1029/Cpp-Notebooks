#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

int main() {
    int color;
    cout << "請輸入 RGB 色碼（十六進位，如 FF5733）：";
    cin >> hex >> color;

    int r = (color >> 16) & 0xFF;   // 取高 8 位
    int g = (color >>  8) & 0xFF;   // 取中 8 位
    int b = (color >>  0) & 0xFF;   // 取低 8 位

    cout << "色碼：#" << uppercase << hex << setfill('0') << setw(6) << color << endl;
    cout << dec;
    cout << "R = " << setw(3) << r << " (" << bitset<8>(r) << ")" << endl;
    cout << "G = " << setw(3) << g << " (" << bitset<8>(g) << ")" << endl;
    cout << "B = " << setw(3) << b << " (" << bitset<8>(b) << ")" << endl;

    return 0;
}