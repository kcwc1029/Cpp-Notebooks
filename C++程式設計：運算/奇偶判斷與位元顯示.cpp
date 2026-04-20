#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;

int main() {
    int n;
    cout << "請輸入整數（0~255）：";
    cin >> n;

    cout << "十進位：" << n << endl;
    cout << "二進位：" << bitset<8>(n) << endl;
    cout << "十六進位：" << hex << n << dec << endl;
    cout << "奇偶：" << ((n & 1) ? "奇數" : "偶數") << endl;
    cout << "最低位（bit 0）：" << (n & 1) << endl;
    cout << "最高位（bit 7）：" << ((n >> 7) & 1) << endl;

    return 0;
}